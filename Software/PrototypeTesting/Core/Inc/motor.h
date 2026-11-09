#ifndef MOTOR_H
#define MOTOR_H

#include "main.h"

typedef struct {
  TIM_HandleTypeDef *tim_a;  uint32_t ch_a;   /* IN1 (or IN3) */
  TIM_HandleTypeDef *tim_b;  uint32_t ch_b;   /* IN2 (or IN4) */
} Motor;

void motor_init(Motor *m);
void motor_set(Motor *m, int16_t duty);   /* -1000 .. +1000 */
void motor_brake(Motor *m);

#endif
