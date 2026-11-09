#include "tof7.h"
#include <string.h>

#define TOF7_ADDR   (0x33u << 1)   /* HAL wants the 7-bit address shifted */
#define TOF7_TMO    100U
#define CMD_SETMODE 1
#define CMD_ALLDATA 2
#define ST_OK       0x53
#define ST_FAIL     0x63

static I2C_HandleTypeDef *bus;

static int send_cmd(uint8_t cmd, const uint8_t *args, uint8_t n)
{
  uint8_t pkt[12];
  pkt[0] = 0x55; pkt[1] = 0; pkt[2] = (uint8_t)(n + 1); pkt[3] = cmd;  /* DFRobot quirk: length is n+1 */
  if (n) memcpy(&pkt[4], args, n);
  return HAL_I2C_Master_Transmit(bus, TOF7_ADDR, pkt, (uint16_t)(4 + n), TOF7_TMO) == HAL_OK ? 0 : -1;
}

static int rx(uint8_t *buf, uint16_t len)
{
  while (len)
  {
    uint16_t c = (len > 32) ? 32 : len;      /* library reads in <=32 byte chunks */
    if (HAL_I2C_Master_Receive(bus, TOF7_ADDR, buf, c, TOF7_TMO) != HAL_OK) return -1;
    buf += c; len -= c;
  }
  return 0;
}

static int recv_pkt(uint8_t cmd, uint8_t *payload, uint16_t max, uint32_t timeout_ms)
{
  uint32_t t0 = HAL_GetTick();
  while (HAL_GetTick() - t0 < timeout_ms)
  {
    uint8_t st, c, l[2];
    if (rx(&st, 1)) return -1;
    if (st == 0xFF) { HAL_Delay(5); continue; }            /* not ready yet */
    if (st != ST_OK && st != ST_FAIL) { HAL_Delay(10); continue; }
    if (rx(&c, 1) || c != cmd) return -2;
    if (rx(l, 2)) return -1;
    uint16_t len = (uint16_t)(l[0] | (l[1] << 8));
    if (len > max) return -3;
    if (len && rx(payload, len)) return -1;
    return (st == ST_OK) ? 0 : -4;
  }
  return -5;                                                /* timeout */
}

int tof7_start(I2C_HandleTypeDef *b)
{
  bus = b;
  if (HAL_I2C_IsDeviceReady(bus, TOF7_ADDR, 3, 20) != HAL_OK) return -1;   /* not found */

  uint8_t args[4] = {0, 0, 0, 4};                           /* 4 = 4x4, 8 = 8x8 */
  if (send_cmd(CMD_SETMODE, args, 4)) return -2;
  if (recv_pkt(CMD_SETMODE, NULL, 0, 8000)) return -2;
  HAL_Delay(5000);                                          /* the library waits 5 s here too */
  return 0;
}

int tof7_read(int16_t dist[16], uint8_t status[16])
{
  uint8_t buf[32];
  if (send_cmd(CMD_ALLDATA, NULL, 0)) return 0;
  if (recv_pkt(CMD_ALLDATA, buf, sizeof(buf), 300)) return 0;

  for (int z = 0; z < 16; z++)
  {
    dist[z]   = (int16_t)(buf[2*z] | (buf[2*z + 1] << 8));  /* little-endian mm */
    status[z] = 0;                                          /* this module gives no per-zone status */
  }
  return 1;
}
