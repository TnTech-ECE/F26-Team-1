#include "sh2.h"
#include "sh2_hal.h"
#include "sh2_SensorValue.h"
#include "sh2_err.h"
#include "main.h"

extern I2C_HandleTypeDef hi2c1;

#define BNO_ADDR   (0x4A << 1)
#define BNO_RST_PORT GPIOB
#define BNO_RST_PIN  GPIO_PIN_12
#define BNO_INT_PORT GPIOB
#define BNO_INT_PIN  GPIO_PIN_2

static sh2_Hal_t hal;
static sh2_SensorValue_t sensorValue;
static volatile uint8_t resetOccurred = 0;

static int hal_open(sh2_Hal_t *self)
{
    HAL_GPIO_WritePin(BNO_RST_PORT, BNO_RST_PIN, GPIO_PIN_RESET);
    HAL_Delay(10);
    HAL_GPIO_WritePin(BNO_RST_PORT, BNO_RST_PIN, GPIO_PIN_SET);
    HAL_Delay(200);   // boot time
    return SH2_OK;
}

static void hal_close(sh2_Hal_t *self) {}

static uint32_t hal_getTimeUs(sh2_Hal_t *self)
{
    return HAL_GetTick() * 1000U;   // fine for starters
}

static int hal_write(sh2_Hal_t *self, uint8_t *buf, unsigned len)
{
    if (len > SH2_HAL_MAX_TRANSFER_OUT) len = SH2_HAL_MAX_TRANSFER_OUT;
    if (HAL_I2C_Master_Transmit(&hi2c1, BNO_ADDR, buf, len, 100) != HAL_OK)
        return 0;
    return len;
}

static int hal_read(sh2_Hal_t *self, uint8_t *buf, unsigned len, uint32_t *t_us)
{
    // Only read when the sensor signals data ready (INT low)
    if (HAL_GPIO_ReadPin(BNO_INT_PORT, BNO_INT_PIN) == GPIO_PIN_SET)
        return 0;

    // 1) Read the 4-byte SHTP header to learn the packet length
    uint8_t hdr[4];
    if (HAL_I2C_Master_Receive(&hi2c1, BNO_ADDR, hdr, 4, 100) != HAL_OK)
        return 0;

    uint16_t packet_size = (hdr[0] | (hdr[1] << 8)) & 0x7FFF;  // bit 15 = continuation
    if (packet_size == 0) return 0;
    if (packet_size > len) packet_size = len;

    // 2) Re-read the whole packet (header included)
    if (HAL_I2C_Master_Receive(&hi2c1, BNO_ADDR, buf, packet_size, 100) != HAL_OK)
        return 0;

    *t_us = hal_getTimeUs(self);
    return packet_size;
}

// --- SH-2 callbacks ---
static void eventHandler(void *cookie, sh2_AsyncEvent_t *evt)
{
    if (evt->eventId == SH2_RESET) resetOccurred = 1;
}

static void sensorHandler(void *cookie, sh2_SensorEvent_t *evt)
{
    sh2_decodeSensorEvent(&sensorValue, evt);
}

// --- Public API ---
int bno085_init(void)
{
    hal.open = hal_open;
    hal.close = hal_close;
    hal.read = hal_read;
    hal.write = hal_write;
    hal.getTimeUs = hal_getTimeUs;

    if (sh2_open(&hal, eventHandler, NULL) != SH2_OK) return -1;
    sh2_setSensorCallback(sensorHandler, NULL);
    return 0;
}

int bno085_enable(sh2_SensorId_t id, uint32_t period_us)
{
    sh2_SensorConfig_t cfg = {0};
    cfg.reportInterval_us = period_us;
    return sh2_setSensorConfig(id, &cfg);
}

void bno085_service(void) { sh2_service(); }

sh2_SensorValue_t *bno085_value(void) { return &sensorValue; }
uint8_t bno085_was_reset(void) { uint8_t r = resetOccurred; resetOccurred = 0; return r; }
