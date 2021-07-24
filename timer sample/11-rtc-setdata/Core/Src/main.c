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
#include "rtc.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;
FILE __stdin;


int fputc(int c, FILE *f) {
  return (HAL_UART_Transmit(&huart2,( uint8_t * )&c,1,1000));
}


int fgetc(FILE *f) {
	uint8_t c;
	HAL_UART_Receive(&huart2,&c,1,0xffff);
	return c;
}


int ferror(FILE *f) {
  /* Your implementation of ferror */
  return EOF;
}
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */


volatile RTC_TimeTypeDef Time1,Time2;
char str[10];
uint32_t bkp;
int i;
RTC_TimeTypeDef Time;
RTC_DateTypeDef Date;
char segment = 0;
char seg_str[4];
int counter = 0;

/* USER CODE END PM */


void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
}


/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/**
  * @brief  EXTI line detection callbacks.
  * @param  GPIO_Pin Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	  if(HAL_GPIO_ReadPin(PB2_GPIO_Port,PB2_Pin) == GPIO_PIN_RESET)
		{	
			HAL_PWR_EnterSTANDBYMode();
		}
	
}



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
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

volatile softTimer timer[TIMER_NUM]; //software timer array

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
								  timer[i].match = HAL_GetTick() + timer[i].period;
									timer[i].cb(); //Execute callback function
              }
              break;
            
          case SOFT_TIMER_TIMEOUT:
              if(timer[i].mode == MODE_ONE_SHOT) {
                  timer[i].state = SOFT_TIMER_STOPPED;
              } else {
                  //timer[i].match = HAL_GetTick() + timer[i].period;
                  timer[i].state = SOFT_TIMER_RUNNING;
              }
              break;
        
          default:    
              break;
      }
  }
		
}




void display(char digit)
{
	HAL_GPIO_WritePin(A_7SEG_GPIO_Port,A_7SEG_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(B_7SEG_GPIO_Port,B_7SEG_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(C_7SEG_GPIO_Port,C_7SEG_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D_7SEG_GPIO_Port,D_7SEG_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(E_7SEG_GPIO_Port,E_7SEG_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(F_7SEG_GPIO_Port,F_7SEG_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(G_7SEG_GPIO_Port,G_7SEG_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(H_7SEG_GPIO_Port,H_7SEG_Pin,GPIO_PIN_RESET);
 switch (digit)
 {
	 case 0:
			HAL_GPIO_WritePin(A_7SEG_GPIO_Port,A_7SEG_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_7SEG_GPIO_Port,B_7SEG_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_7SEG_GPIO_Port,C_7SEG_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_7SEG_GPIO_Port,D_7SEG_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(E_7SEG_GPIO_Port,E_7SEG_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(F_7SEG_GPIO_Port,F_7SEG_Pin,GPIO_PIN_SET);		 
		 break;
	 case 1:
			HAL_GPIO_WritePin(B_7SEG_GPIO_Port,B_7SEG_Pin,GPIO_PIN_SET);
	    HAL_GPIO_WritePin(C_7SEG_GPIO_Port,C_7SEG_Pin,GPIO_PIN_SET);
		 break;
	 case 2:
			HAL_GPIO_WritePin(A_7SEG_GPIO_Port,A_7SEG_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_7SEG_GPIO_Port,B_7SEG_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_7SEG_GPIO_Port,D_7SEG_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(E_7SEG_GPIO_Port,E_7SEG_Pin,GPIO_PIN_SET);	 
	    HAL_GPIO_WritePin(G_7SEG_GPIO_Port,G_7SEG_Pin,GPIO_PIN_SET);
		 break;
	 case 3:
		 	HAL_GPIO_WritePin(A_7SEG_GPIO_Port,A_7SEG_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_7SEG_GPIO_Port,B_7SEG_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_7SEG_GPIO_Port,C_7SEG_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_7SEG_GPIO_Port,D_7SEG_Pin,GPIO_PIN_SET);
	    HAL_GPIO_WritePin(G_7SEG_GPIO_Port,G_7SEG_Pin,GPIO_PIN_SET);
		 break;
	 case 4:
			HAL_GPIO_WritePin(B_7SEG_GPIO_Port,B_7SEG_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_7SEG_GPIO_Port,C_7SEG_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(F_7SEG_GPIO_Port,F_7SEG_Pin,GPIO_PIN_SET);
	    HAL_GPIO_WritePin(G_7SEG_GPIO_Port,G_7SEG_Pin,GPIO_PIN_SET);		 
		 break;
	 case 5:
		 	HAL_GPIO_WritePin(A_7SEG_GPIO_Port,A_7SEG_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_7SEG_GPIO_Port,C_7SEG_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_7SEG_GPIO_Port,D_7SEG_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(F_7SEG_GPIO_Port,F_7SEG_Pin,GPIO_PIN_SET);
	    HAL_GPIO_WritePin(G_7SEG_GPIO_Port,G_7SEG_Pin,GPIO_PIN_SET);		 
		 break;
	 case 6:
		 	HAL_GPIO_WritePin(A_7SEG_GPIO_Port,A_7SEG_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_7SEG_GPIO_Port,C_7SEG_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_7SEG_GPIO_Port,D_7SEG_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(E_7SEG_GPIO_Port,E_7SEG_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(F_7SEG_GPIO_Port,F_7SEG_Pin,GPIO_PIN_SET);
	    HAL_GPIO_WritePin(G_7SEG_GPIO_Port,G_7SEG_Pin,GPIO_PIN_SET);		 
		 break;
	 case 7:
		 	HAL_GPIO_WritePin(A_7SEG_GPIO_Port,A_7SEG_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_7SEG_GPIO_Port,B_7SEG_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_7SEG_GPIO_Port,C_7SEG_Pin,GPIO_PIN_SET);
		 break;	
	 case 8:
		 	HAL_GPIO_WritePin(A_7SEG_GPIO_Port,A_7SEG_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_7SEG_GPIO_Port,B_7SEG_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_7SEG_GPIO_Port,C_7SEG_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_7SEG_GPIO_Port,D_7SEG_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(E_7SEG_GPIO_Port,E_7SEG_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(F_7SEG_GPIO_Port,F_7SEG_Pin,GPIO_PIN_SET);
	    HAL_GPIO_WritePin(G_7SEG_GPIO_Port,G_7SEG_Pin,GPIO_PIN_SET);
		 break;
	 case 9:
		 	HAL_GPIO_WritePin(A_7SEG_GPIO_Port,A_7SEG_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(B_7SEG_GPIO_Port,B_7SEG_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(C_7SEG_GPIO_Port,C_7SEG_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(D_7SEG_GPIO_Port,D_7SEG_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(F_7SEG_GPIO_Port,F_7SEG_Pin,GPIO_PIN_SET);
	    HAL_GPIO_WritePin(G_7SEG_GPIO_Port,G_7SEG_Pin,GPIO_PIN_SET);		 
		 break;	 	 
 }
}




/**
  * @brief  Period elapsed callback in non blocking mode 
  * @param  htim : TIM handle
  * @retval None
  */
void segment_callback(void)
{
        switch(segment)
				{
					case 0:
								HAL_GPIO_WritePin(K1_7SEG_GPIO_Port,K1_7SEG_Pin,GPIO_PIN_RESET);
								HAL_GPIO_WritePin(K1_7SEG_GPIO_Port,K2_7SEG_Pin | K3_7SEG_Pin | K4_7SEG_Pin,GPIO_PIN_SET);
								display(seg_str[3] - 0x30);
						break;
					case 1:
								HAL_GPIO_WritePin(K2_7SEG_GPIO_Port,K2_7SEG_Pin,GPIO_PIN_RESET);
								HAL_GPIO_WritePin(K1_7SEG_GPIO_Port,K1_7SEG_Pin | K3_7SEG_Pin | K4_7SEG_Pin,GPIO_PIN_SET);
								display(seg_str[2] - 0x30);
						break;
					case 2:
								HAL_GPIO_WritePin(K3_7SEG_GPIO_Port,K3_7SEG_Pin,GPIO_PIN_RESET);
								HAL_GPIO_WritePin(K1_7SEG_GPIO_Port,K1_7SEG_Pin | K2_7SEG_Pin | K4_7SEG_Pin,GPIO_PIN_SET);
								display(seg_str[1] - 0x30);
						break;
					case 3:
								HAL_GPIO_WritePin(K4_7SEG_GPIO_Port,K4_7SEG_Pin,GPIO_PIN_RESET);
								HAL_GPIO_WritePin(K1_7SEG_GPIO_Port,K1_7SEG_Pin | K2_7SEG_Pin | K3_7SEG_Pin,GPIO_PIN_SET);
								display(seg_str[0] - 0x30);
						break;
				
				}
					segment++;
					if(segment == 4) segment = 0;
}



void rtc_show(void)
{
    HAL_RTC_GetTime(&hrtc,&Time2,RTC_FORMAT_BIN);
	  sprintf(seg_str,"%2d%2d",Time2.Minutes,Time2.Seconds);
}



void  segment_init(void) {
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, E_7SEG_Pin|F_7SEG_Pin|G_7SEG_Pin|H_7SEG_Pin
                          |K1_7SEG_Pin|K3_7SEG_Pin|K2_7SEG_Pin|K4_7SEG_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, A_7SEG_Pin|B_7SEG_Pin|C_7SEG_Pin|D_7SEG_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PEPin PEPin PEPin PEPin
                           PEPin PEPin PEPin PEPin */
  GPIO_InitStruct.Pin = E_7SEG_Pin|F_7SEG_Pin|G_7SEG_Pin|H_7SEG_Pin
                          |K1_7SEG_Pin|K3_7SEG_Pin|K2_7SEG_Pin|K4_7SEG_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PDPin PDPin PDPin PDPin */
  GPIO_InitStruct.Pin = A_7SEG_Pin|B_7SEG_Pin|C_7SEG_Pin|D_7SEG_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);	
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
  MX_RTC_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_Delay(100);
	segment_init();
//	seg_str[0] = '0';
	//HAL_RTCEx_BKUPWrite(&hrtc,0,0);
	bkp = HAL_RTCEx_BKUPRead(&hrtc,0);
	if( bkp != 20 )
	{
		printf("plz set time & date of systeam \n\r");
		
		printf ("Enter Hour: ");
		scanf ("%x",&i);
		Time.Hours = (uint8_t)i;	
		
		printf ("Enter Minutes: ");
		scanf ("%x",&i);
		Time.Minutes = (uint8_t)i;	

		printf ("Enter Seconds: ");
		scanf ("%x",&i);
		Time.Seconds = (uint8_t)i;	
		
		HAL_RTC_SetTime(&hrtc,&Time,RTC_FORMAT_BCD);
		
		
		printf ("Enter Year: ");
		scanf ("%x",&i);
		Date.Year = (uint8_t)i;	
		
		printf ("Enter Month: ");
		scanf ("%x",&i);
		Date.Month = (uint8_t)i;	

		printf ("Enter Date: ");
		scanf ("%x",&i);
		Date.Date = (uint8_t)i;

		HAL_RTC_SetDate(&hrtc,&Date,RTC_FORMAT_BCD);

		HAL_RTCEx_BKUPWrite(&hrtc,0,20);
  }
	
	softTimer_Start(0, MODE_PERIODIC, 1000, rtc_show);
  softTimer_Start(1, MODE_PERIODIC, 2,  segment_callback);	
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

		softTimer_Update();
		//HAL_Delay(100);
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
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
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
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
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
