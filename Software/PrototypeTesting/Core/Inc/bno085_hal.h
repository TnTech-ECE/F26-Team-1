#ifndef BNO085_HAL_H
#define BNO085_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "sh2.h"
#include "sh2_SensorValue.h"

/**
 * Reset the sensor and open the SH-2 session.
 * @return 0 on success, -1 on failure
 */
int bno085_init(void);

/**
 * Enable a sensor report.
 * @param id         e.g. SH2_ROTATION_VECTOR
 * @param period_us  report interval in microseconds (10000 = 100 Hz)
 * @return SH2_OK on success
 */
int bno085_enable(sh2_SensorId_t id, uint32_t period_us);

/** Call as often as possible from the main loop. */
void bno085_service(void);

/** Pointer to the most recently decoded sensor event. */
sh2_SensorValue_t *bno085_value(void);

/** Returns 1 once after the sensor has reset, then 0 until the next reset. */
uint8_t bno085_was_reset(void);

/** Returns 1 once after a new sensor event arrives, then 0 until the next one. */
uint8_t bno085_has_new(void);

#ifdef __cplusplus
}
#endif

#endif /* BNO085_HAL_H */
