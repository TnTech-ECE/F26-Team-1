#ifndef TOF7_H
#define TOF7_H

#include <stdint.h>
#include "main.h"

/* Returns 0 on success, -1 not found, -2 init failed */
int tof7_start(I2C_HandleTypeDef *bus);

/* Returns 1 and fills 16 zones (4x4) if new data was ready, else 0 */
int tof7_read(int16_t dist[16], uint8_t status[16]);

#endif
