/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "string.h"
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
const unsigned char digit[10]= {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};  //COMMON ANODE
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
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

char segment = 0;


char str[4];

int counter = 0;
/**
  * @brief  Period elapsed callback in non blocking mode 
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	
    if(htim->Instance == TIM6)
    {
        switch(segment)
				{
					case 0:
								HAL_GPIO_WritePin(K1_7SEG_GPIO_Port,K1_7SEG_Pin,GPIO_PIN_RESET);
								HAL_GPIO_WritePin(K1_7SEG_GPIO_Port,K2_7SEG_Pin | K3_7SEG_Pin | K4_7SEG_Pin,GPIO_PIN_SET);
								display(str[3] - 0x30);
						break;
					case 1:
								HAL_GPIO_WritePin(K2_7SEG_GPIO_Port,K2_7SEG_Pin,GPIO_PIN_RESET);
								HAL_GPIO_WritePin(K1_7SEG_GPIO_Port,K1_7SEG_Pin | K3_7SEG_Pin | K4_7SEG_Pin,GPIO_PIN_SET);
								display(str[2] - 0x30);
					      HAL_GPIO_WritePin(H_7SEG_GPIO_Port,H_7SEG_Pin,GPIO_PIN_SET);
						break;
					case 2:
								HAL_GPIO_WritePin(K3_7SEG_GPIO_Port,K3_7SEG_Pin,GPIO_PIN_RESET);
								HAL_GPIO_WritePin(K1_7SEG_GPIO_Port,K1_7SEG_Pin | K2_7SEG_Pin | K4_7SEG_Pin,GPIO_PIN_SET);
								display(str[1] - 0x30);
						break;
					case 3:
								HAL_GPIO_WritePin(K4_7SEG_GPIO_Port,K4_7SEG_Pin,GPIO_PIN_RESET);
								HAL_GPIO_WritePin(K1_7SEG_GPIO_Port,K1_7SEG_Pin | K2_7SEG_Pin | K3_7SEG_Pin,GPIO_PIN_SET);
								display(str[0] - 0x30);
						break;
				
				}
					segment++;
					if(segment == 4) segment = 0;
    }
		
		
		if(htim->Instance == TIM7)
    {
        counter++;
			  if(counter == 10000) counter = 0;
			  sprintf(str,"%4d",counter);
    }
		
}
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
  MX_TIM7_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim6);
	HAL_TIM_Base_Start_IT(&htim7);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

		HAL_Delay(10);
				
		
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
