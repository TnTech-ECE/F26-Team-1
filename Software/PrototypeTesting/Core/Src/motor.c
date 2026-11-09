#include "motor.h"

static void set_pwm(TIM_HandleTypeDef *t, uint32_t ch, uint32_t permille)
{
  uint32_t arr = __HAL_TIM_GET_AUTORELOAD(t);
  __HAL_TIM_SET_COMPARE(t, ch, permille * (arr + 1) / 1000);
}

void motor_init(Motor *m)
{
  HAL_TIM_PWM_Start(m->tim_a, m->ch_a);
  HAL_TIM_PWM_Start(m->tim_b, m->ch_b);
  motor_set(m, 0);
}

void motor_set(Motor *m, int16_t duty)
{
  if (duty >  1000) duty =  1000;
  if (duty < -1000) duty = -1000;

  if (duty > 0)      { set_pwm(m->tim_a, m->ch_a, duty);  set_pwm(m->tim_b, m->ch_b, 0); }
  else if (duty < 0) { set_pwm(m->tim_a, m->ch_a, 0);     set_pwm(m->tim_b, m->ch_b, -duty); }
  else               { set_pwm(m->tim_a, m->ch_a, 0);     set_pwm(m->tim_b, m->ch_b, 0); }   /* coast */
}

void motor_brake(Motor *m)
{
  set_pwm(m->tim_a, m->ch_a, 1000);
  set_pwm(m->tim_b, m->ch_b, 1000);
}
