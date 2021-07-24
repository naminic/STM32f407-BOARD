/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

typedef void callback(void);

typedef struct softTimer {
 uint8_t state; //state
 uint8_t mode; //mode
 uint32_t match; //expiration time
 uint32_t period; // timing period
 callback *cb; //callback function pointer
}softTimer;

typedef enum tmrState {
 SOFT_TIMER_STOPPED = 0, //stop
 SOFT_TIMER_RUNNING, //Run
 SOFT_TIMER_TIMEOUT // timeout
}tmrState;

typedef enum tmrMode {
 MODE_ONE_SHOT = 0, // single mode
 MODE_PERIODIC, //cycle mode
}tmrMode;

#define TIMER_NUM 2

static softTimer timer[TIMER_NUM]; //software timer array

void softTimer_Init(void)
{
		uint16_t i;
	
		for(i=0; i<TIMER_NUM; i++) 
		{
				timer[i].state = SOFT_TIMER_STOPPED;
				timer[i].mode = MODE_ONE_SHOT;
				timer[i].match = 0;
				timer[i].period = 0;
				timer[i].cb = NULL;
		}
}

void softTimer_Start(uint16_t id, tmrMode mode, uint32_t delay, callback *cb)
{
    timer[id].match = HAL_GetTick() + delay;
    timer[id].period = delay;
    timer[id].state = SOFT_TIMER_RUNNING;
    timer[id].mode = mode;
    timer[id].cb = cb;
}


void softTimer_Stop(uint16_t id)
{
    assert_param(id < TIMER_NUM);
    timer[id].state = SOFT_TIMER_STOPPED;
}


uint8_t softTimer_GetState(uint16_t id)
{
    return timer[id].state;
}

void softTimer_Update(void)
{
    uint16_t i;
    
    for(i=0; i<TIMER_NUM; i++) {
      switch (timer[i].state) {
          case SOFT_TIMER_STOPPED:
              break;
        
          case SOFT_TIMER_RUNNING:
              if(timer[i].match <= HAL_GetTick()) 
							{
                  timer[i].state = SOFT_TIMER_TIMEOUT;
									timer[i].cb(); //Execute callback function
              }
              break;
            
          case SOFT_TIMER_TIMEOUT:
              if(timer[i].mode == MODE_ONE_SHOT) {
                  timer[i].state = SOFT_TIMER_STOPPED;
              } else {
                  timer[i].match = HAL_GetTick() + timer[i].period;
                  timer[i].state = SOFT_TIMER_RUNNING;
              }
              break;
        
          default:    
              break;
      }
  }
		
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM6)
    {
        softTimer_Update();
    }
}

void LED1_Blink(void)
{
	HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
}
	
void LED2_Blink(void)
{
	HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
}	
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
   
	softTimer_Start(0, MODE_PERIODIC, 1000, LED1_Blink);
	softTimer_Start(1, MODE_PERIODIC, 100,  LED2_Blink);

  HAL_TIM_Base_Start_IT(&htim6);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		 //softTimer_Update();
		 //HAL_Delay(50);

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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
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

#ifdef  USE_FULL_ASSERT
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
