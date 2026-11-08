/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "bno085_hal.h"
#include "vl53l5cx_api.h"
#include "tof7.h"
#include "as5600.h"
#include "motor.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* RAD2DEG and the *_PERIOD_MS / MOTOR*_CMD constants live in main.h */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;
I2C_HandleTypeDef hi2c3;
TIM_HandleTypeDef htim3;
UART_HandleTypeDef huart2;
/* USER CODE BEGIN PV */
//For debugging via Putty
static char msg[128];

/* AS5600 encoders: enc1 on I2C1, enc2 on I2C2 */
static AS5600_TypeDef enc1, enc2;
static int enc1_ok, enc2_ok;

/* VL53L5CX: tof1 on I2C1, tof2 on I2C2 */
static VL53L5CX_Configuration tof1, tof2;
static VL53L5CX_ResultsData   res1, res2;
static int tof1_ok, tof2_ok;

/* VL53L7CX on I2C3 */
static int tof3_ok;

/* BNO085 (uses hi2c1 inside bno085_hal.c)*/
static int bno_ok;
volatile float roll_deg, pitch_deg, yaw_deg;
volatile int initRes, en1, en2;
volatile uint32_t rvCount;
static uint64_t lastTs;

/* Motors: IN1/IN2 and IN3/IN4 on TIM3 CH1..CH4 */
static Motor m1 = { &htim3, TIM_CHANNEL_1, &htim3, TIM_CHANNEL_2 };
static Motor m2 = { &htim3, TIM_CHANNEL_3, &htim3, TIM_CHANNEL_4 };

/* Last-run timestamps for the non-blocking task scheduler */
static uint32_t t_bno_print, t_tof, t_enc;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2C2_Init(void);
static void MX_I2C3_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM3_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* ---- Helpers Function------------------------------------------------------------ */

/* Send a plain string over USART2 for debugging*/
void uart_print(const char *s)
{
  HAL_UART_Transmit(&huart2, (uint8_t *)s, (uint16_t)strlen(s), 100);
}

/* Format and send msg[] */
static void uart_printf_msg(int n)
{
  if (n < 0) return;
  if ((size_t)n >= sizeof(msg)) n = (int)sizeof(msg) - 1;   /* snprintf truncated */
  HAL_UART_Transmit(&huart2, (uint8_t *)msg, (uint16_t)n, 100);
}

/* Non-blocking periodic timer: true once every period_ms. Wrap-safe. */
static int task_due(uint32_t *last, uint32_t period_ms)
{
  uint32_t now = HAL_GetTick();
  if ((now - *last) < period_ms) return 0;
  *last = now;
  return 1;
}

/* Format degrees with one decimal using integers only
   (so "Use float with printf" is NOT required) */
static int fmt_tenths(char *buf, size_t n, float deg)
{
  int t = (int)lroundf(deg * 10.0f);
  int a = (t < 0) ? -t : t;
  return snprintf(buf, n, "%s%d.%d", (t < 0) ? "-" : "", a / 10, a % 10);
}

static void i2c_scan(I2C_HandleTypeDef *bus, const char *name)
{
  snprintf(msg, sizeof(msg), "%s scan:", name);
  uart_print(msg);
  for (uint8_t a = 1; a < 128; a++)
  {
    if (HAL_I2C_IsDeviceReady(bus, (uint16_t)(a << 1), 1, 5) == HAL_OK)
    {
      snprintf(msg, sizeof(msg), " 0x%02X", a);
      uart_print(msg);
    }
  }
  uart_print("\r\n");
}

/* ---- ToF (VL53L5CX / VL53L7CX) ------------------------------------------ */

/* Print a 4x4 grid: distance_mm(status).
   'stride' = entries per zone in the arrays (VL53L5CX_NB_TARGET_PER_ZONE for the
   driver's results struct, 1 for tightly packed arrays such as tof7_read()). */
static void tof_print_grid(const char *name, const int16_t *d, const uint8_t *s, int stride)
{
  snprintf(msg, sizeof(msg), "[%s]\r\n", name);
  uart_print(msg);

  for (int row = 0; row < 4; row++)
  {
    int n = 0;
    for (int col = 0; col < 4; col++)
    {
      int i = stride * (row * 4 + col); //for spacing when print out UART only
      n += snprintf(msg + n, sizeof(msg) - n, "%5d(%2d) ", d[i], s[i]);
    }
    n += snprintf(msg + n, sizeof(msg) - n, "\r\n");
    uart_printf_msg(n);
  }
  uart_print("\r\n");
}

/* Bring up one VL53L5CX on the given I2C bus. Returns 0 on success. */
static int tof_start(VL53L5CX_Configuration *dev, I2C_HandleTypeDef *bus, const char *name)
{
  uint8_t alive = 0;

  dev->platform.address = VL53L5CX_DEFAULT_I2C_ADDRESS;   /* 0x52 */
  dev->platform.hi2c    = bus;

  VL53L5CX_Reset_Sensor(&dev->platform);

  if (vl53l5cx_is_alive(dev, &alive) || !alive)
  {
    snprintf(msg, sizeof(msg), "%s not found\r\n", name);
    uart_print(msg);
    return -1;
  }

  snprintf(msg, sizeof(msg), "%s alive, loading FW...\r\n", name);
  uart_print(msg);

  if (vl53l5cx_init(dev))                      /* uploads ~85 KB firmware */
  {
    snprintf(msg, sizeof(msg), "%s init FAILED\r\n", name);
    uart_print(msg);
    return -2;
  }

  vl53l5cx_set_resolution(dev, VL53L5CX_RESOLUTION_4X4);
  vl53l5cx_set_ranging_frequency_hz(dev, 10);
  vl53l5cx_start_ranging(dev);

  snprintf(msg, sizeof(msg), "%s ranging\r\n", name);
  uart_print(msg);
  return 0;
}

/* If new data is ready, read it and print it */
static void tof_poll(VL53L5CX_Configuration *dev, VL53L5CX_ResultsData *res, const char *name)
{
  uint8_t ready = 0;

  vl53l5cx_check_data_ready(dev, &ready);
  if (!ready) return;

  vl53l5cx_get_ranging_data(dev, res);
  tof_print_grid(name, res->distance_mm, res->target_status, VL53L5CX_NB_TARGET_PER_ZONE);
}

/* ---- AS5600 encoders ---------------------------------------------------- */

/* Probe one AS5600 and report magnet status. Returns 0 on success. */
static int as5600_start(AS5600_TypeDef *e, I2C_HandleTypeDef *bus, const char *name)
{
  uint8_t st = 0;

  e->i2cHandle = bus;
  e->i2cAddr   = AS5600_SLAVE_ADDRESS << 1;

  if (HAL_I2C_IsDeviceReady(bus, e->i2cAddr, 3, 20) != HAL_OK)
  {
    snprintf(msg, sizeof(msg), "%s not found\r\n", name);
    uart_print(msg);
    return -1;
  }
  if (AS5600_GetMagnetStatus(e, &st) != HAL_OK)
  {
    snprintf(msg, sizeof(msg), "%s status read FAILED\r\n", name);
    uart_print(msg);
    return -2;
  }

  snprintf(msg, sizeof(msg), "%s found, status=0x%02X (MD=%d ML=%d MH=%d)\r\n", name, st,
           (st & AS5600_MAGNET_DETECTED) != 0,
           (st & AS5600_AGC_MAX_GAIN_OVERFLOW) != 0,   /* ML: magnet too weak   */
           (st & AS5600_AGC_MIN_GAIN_OVERFLOW) != 0);  /* MH: magnet too strong */
  uart_print(msg);
  return 0;
}

/* Read and print raw angle, angle and magnet state */
static void as5600_poll(AS5600_TypeDef *e, const char *name)
{
  uint16_t raw = 0, ang = 0;
  uint8_t st = 0;

  if (AS5600_GetRawAngle(e, &raw)    != HAL_OK ||
      AS5600_GetAngle(e, &ang)       != HAL_OK ||
      AS5600_GetMagnetStatus(e, &st) != HAL_OK)
  {
    snprintf(msg, sizeof(msg), "[%s] read ERROR\r\n", name);
    uart_print(msg);
    return;
  }

  raw &= 0x0FFF;
  ang &= 0x0FFF;
  uint32_t t = (uint32_t)ang * 3600U / 4096U;     /* tenths of a degree, integer only */

  const char *mag = (st & AS5600_MAGNET_DETECTED)       ? "magnet OK"
                  : (st & AS5600_AGC_MAX_GAIN_OVERFLOW) ? "too weak"
                  : (st & AS5600_AGC_MIN_GAIN_OVERFLOW) ? "too strong"
                                                        : "NO MAGNET";

  snprintf(msg, sizeof(msg), "[%s] raw=%4u angle=%4u (%lu.%lu deg) %s\r\n",
           name, raw, ang, (unsigned long)(t / 10), (unsigned long)(t % 10), mag);
  uart_print(msg);
}

/* ---- BNO085 ------------------------------------------------------------- */

static void bno_enable_reports(void)
{
  en1 = bno085_enable(SH2_ROTATION_VECTOR, 10000);      /* 100 Hz */
  en2 = bno085_enable(SH2_LINEAR_ACCELERATION, 20000);  /* 50 Hz  */
}

/* Service the sensor, update roll/pitch/yaw on each new rotation vector, print at ~20 Hz */
static void bno_task(void)
{
  bno085_service();   /* call as often as possible */

  if (bno085_was_reset())
  {
    bno_enable_reports();
    uart_print("sensor reset, reports re-enabled\r\n");
  }

  sh2_SensorValue_t *v = bno085_value();

  /* Only act on a NEW rotation vector event */
  if (v->sensorId != SH2_ROTATION_VECTOR || v->timestamp == lastTs) return;

  lastTs = v->timestamp;
  rvCount++;

  float qi = v->un.rotationVector.i;
  float qj = v->un.rotationVector.j;
  float qk = v->un.rotationVector.k;
  float qr = v->un.rotationVector.real;

  float sinp = 2.0f * (qr * qj - qk * qi);
  if (sinp >  1.0f) sinp =  1.0f;    /* clamp to avoid NaN from asinf */
  if (sinp < -1.0f) sinp = -1.0f;

  roll_deg  = atan2f(2.0f * (qr * qi + qj * qk),
                     1.0f - 2.0f * (qi * qi + qj * qj)) * RAD2DEG;
  pitch_deg = asinf(sinp) * RAD2DEG;
  yaw_deg   = atan2f(2.0f * (qr * qk + qi * qj),
                     1.0f - 2.0f * (qj * qj + qk * qk)) * RAD2DEG;

  if (task_due(&t_bno_print, BNO_PRINT_PERIOD_MS))
  {
    char r[16], p[16], y[16];
    fmt_tenths(r, sizeof(r), roll_deg);
    fmt_tenths(p, sizeof(p), pitch_deg);
    fmt_tenths(y, sizeof(y), yaw_deg);

    uart_printf_msg(snprintf(msg, sizeof(msg), "R:%s P:%s Y:%s\r\n", r, p, y));
  }
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_I2C3_Init();
  MX_USART2_UART_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  uart_print("boot\r\n");

  /* ---- Motors ---- */
  motor_init(&m1);
  motor_init(&m2);
  motor_set(&m1, MOTOR1_CMD);
  motor_set(&m2, MOTOR2_CMD);

  /* ---- BNO085. A failure disables it but does not halt the rest of the system ---- */
  initRes = bno085_init();
  bno_ok  = (initRes == 0);
  if (bno_ok)
  {
    uart_print("bno085_init OK\r\n");
    bno_enable_reports();
    snprintf(msg, sizeof(msg), "enable RV=%d LA=%d\r\n", en1, en2);
    uart_print(msg);
  }
  else
  {
    uart_print("bno085_init FAILED\r\n");
  }

  /* ---- ToF sensors, one per bus. A failure here does not stop the others ---- */
  tof1_ok = (tof_start(&tof1, &hi2c1, "ToF1") == 0);
  tof2_ok = (tof_start(&tof2, &hi2c2, "ToF2") == 0);
  int r3  = tof7_start(&hi2c3);
  tof3_ok = (r3 == 0);
  snprintf(msg, sizeof(msg), "ToF3 %s\r\n",
           r3 == 0 ? "ranging" : (r3 == -1 ? "not found" : "init FAILED"));
  uart_print(msg);

  /* ---- Bus scan + encoders ---- */
  i2c_scan(&hi2c1, "I2C1");
  i2c_scan(&hi2c2, "I2C2");
  enc1_ok = (as5600_start(&enc1, &hi2c1, "ENC1") == 0);
  enc2_ok = (as5600_start(&enc2, &hi2c2, "ENC2") == 0);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* Nothing below blocks: each task runs when its period elapses,
       and the BNO085 is serviced on every pass. */

    if (bno_ok) bno_task();

    if (task_due(&t_tof, TOF_POLL_PERIOD_MS))
    {
      if (tof1_ok) tof_poll(&tof1, &res1, "ToF1");
      if (tof2_ok) tof_poll(&tof2, &res2, "ToF2");
      if (tof3_ok)
      {
        int16_t d3[16]; uint8_t s3[16];
        if (tof7_read(d3, s3)) tof_print_grid("ToF3", d3, s3, 1);
      }
    }

    if (task_due(&t_enc, ENC_PRINT_PERIOD_MS))
    {
      if (enc1_ok) as5600_poll(&enc1, "ENC1");
      if (enc2_ok) as5600_poll(&enc2, "ENC2");
    }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00100D14;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.Timing = 0x00100D14;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief I2C3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C3_Init(void)
{

  /* USER CODE BEGIN I2C3_Init 0 */

  /* USER CODE END I2C3_Init 0 */

  /* USER CODE BEGIN I2C3_Init 1 */

  /* USER CODE END I2C3_Init 1 */
  hi2c3.Instance = I2C3;
  hi2c3.Init.Timing = 0x00100D14;
  hi2c3.Init.OwnAddress1 = 0;
  hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c3.Init.OwnAddress2 = 0;
  hi2c3.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c3) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c3, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c3, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C3_Init 2 */

  /* USER CODE END I2C3_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 399;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin : PB2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PB12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PA10 */
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
