/**
  * platform.c - VL53L5CX platform layer for STM32 HAL (STM32L476RG)
  *
  * Replaces the empty ST template. Keep platform.h as it is.
  */

#include "platform.h"
#include "main.h"

/* The I2C bus is taken from p_platform->hi2c, set per sensor in main.c */

#define VL53_TIMEOUT_MS 1000U
#define VL53_CHUNK      4096U   /* max bytes per HAL transaction */

/* Optional: LPn pin control. Uncomment and set your pin if LPn goes to a GPIO.
   If LPn is tied to 3.3 V (or pulled up on the breakout) leave these out. */
/* #define VL53_LPN_PORT  GPIOB */
/* #define VL53_LPN_PIN   GPIO_PIN_5 */

/* The sensor uses 16-bit register addresses, sent MSB first, and the
   register index auto-increments during multi-byte transfers. */

uint8_t VL53L5CX_RdMulti(
		VL53L5CX_Platform *p_platform,
		uint16_t RegisterAdress,
		uint8_t *p_values,
		uint32_t size)
{
	while (size > 0)
	{
		uint16_t n = (size > VL53_CHUNK) ? VL53_CHUNK : (uint16_t)size;

		if (HAL_I2C_Mem_Read(p_platform->hi2c, p_platform->address, RegisterAdress,
				I2C_MEMADD_SIZE_16BIT, p_values, n, VL53_TIMEOUT_MS) != HAL_OK)
		{
			return 255;
		}
		RegisterAdress += n;
		p_values += n;
		size -= n;
	}
	return 0;
}

uint8_t VL53L5CX_WrMulti(
		VL53L5CX_Platform *p_platform,
		uint16_t RegisterAdress,
		uint8_t *p_values,
		uint32_t size)
{
	while (size > 0)
	{
		uint16_t n = (size > VL53_CHUNK) ? VL53_CHUNK : (uint16_t)size;

		if (HAL_I2C_Mem_Write(p_platform->hi2c, p_platform->address, RegisterAdress,
				I2C_MEMADD_SIZE_16BIT, p_values, n, VL53_TIMEOUT_MS) != HAL_OK)
		{
			return 255;
		}
		RegisterAdress += n;
		p_values += n;
		size -= n;
	}
	return 0;
}

uint8_t VL53L5CX_RdByte(
		VL53L5CX_Platform *p_platform,
		uint16_t RegisterAdress,
		uint8_t *p_value)
{
	return VL53L5CX_RdMulti(p_platform, RegisterAdress, p_value, 1);
}

uint8_t VL53L5CX_WrByte(
		VL53L5CX_Platform *p_platform,
		uint16_t RegisterAdress,
		uint8_t value)
{
	return VL53L5CX_WrMulti(p_platform, RegisterAdress, &value, 1);
}

uint8_t VL53L5CX_Reset_Sensor(
		VL53L5CX_Platform *p_platform)
{
	(void)p_platform;
#ifdef VL53_LPN_PORT
	HAL_GPIO_WritePin(VL53_LPN_PORT, VL53_LPN_PIN, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(VL53_LPN_PORT, VL53_LPN_PIN, GPIO_PIN_SET);
	HAL_Delay(100);
#endif
	return 0;
}

void VL53L5CX_SwapBuffer(
		uint8_t 		*buffer,
		uint16_t 	 	 size)
{
	uint32_t i, tmp;

	for (i = 0; i < size; i = i + 4)
	{
		tmp = ((uint32_t)buffer[i] << 24)
		    | ((uint32_t)buffer[i + 1] << 16)
		    | ((uint32_t)buffer[i + 2] << 8)
		    |  (uint32_t)buffer[i + 3];

		memcpy(&(buffer[i]), &tmp, 4);
	}
}

uint8_t VL53L5CX_WaitMs(
		VL53L5CX_Platform *p_platform,
		uint32_t TimeMs)
{
	(void)p_platform;
	HAL_Delay(TimeMs);
	return 0;
}

/* shared transport helpers */
static uint8_t tof_rd(I2C_HandleTypeDef *h, uint16_t addr, uint16_t reg,
                      uint8_t *buf, uint32_t size)
{
    while (size > 0) {
        uint16_t n = (size > VL53_CHUNK) ? VL53_CHUNK : (uint16_t)size;
        if (HAL_I2C_Mem_Read(h, addr, reg, I2C_MEMADD_SIZE_16BIT,
                             buf, n, VL53_TIMEOUT_MS) != HAL_OK) return 255;
        reg += n; buf += n; size -= n;
    }
    return 0;
}

static uint8_t tof_wr(I2C_HandleTypeDef *h, uint16_t addr, uint16_t reg,
                      uint8_t *buf, uint32_t size)
{
    while (size > 0) {
        uint16_t n = (size > VL53_CHUNK) ? VL53_CHUNK : (uint16_t)size;
        if (HAL_I2C_Mem_Write(h, addr, reg, I2C_MEMADD_SIZE_16BIT,
                              buf, n, VL53_TIMEOUT_MS) != HAL_OK) return 255;
        reg += n; buf += n; size -= n;
    }
    return 0;
}
