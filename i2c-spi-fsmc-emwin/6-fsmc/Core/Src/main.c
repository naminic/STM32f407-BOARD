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
#include "spi.h"
#include "gpio.h"
#include "fsmc.h"

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
void STM3210E_LCD_Init(void);
void GLCD_clear (unsigned short color);
void GLCD_displayStringLn(unsigned int ln, unsigned char *s,unsigned short BackColor,unsigned short TextColor);
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
  MX_SPI1_Init();
  MX_FSMC_Init();
  /* USER CODE BEGIN 2 */
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,0);
	HAL_Delay(100);
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,1);
	HAL_Delay(100);
	
	STM3210E_LCD_Init();
	

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
			GLCD_clear(0xf800);
		  HAL_Delay(1000);
			GLCD_clear(0x7e0);
		  HAL_Delay(1000);
			GLCD_clear(0x1f);
		  HAL_Delay(1000);		
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

#define U16 uint16_t
#define U32 uint32_t

#define WIDTH       320                 /* Screen Width (in pixels)           */
#define HEIGHT      240                 /* Screen Hight (in pixels)           */

U16 driverCode;

#define LCD_DATA_ADDRESS    *(volatile U16*) ((volatile U32)0x60020000) 
#define LCD_REG_ADDRESS     *(volatile U16*) ((volatile U32)0x60000000)	


static void LcdWriteReg(U16 Data) {
  LCD_REG_ADDRESS = Data;
}

static void LcdWriteData(U16 Data) {
  LCD_DATA_ADDRESS = Data;
}

void wr_reg (U16 reg, U16 dat) {
  LcdWriteReg(reg);
  LcdWriteData(dat);
}

U16 rd_reg (U16 reg) {
  LcdWriteReg(reg);
	HAL_Delay(1);
  return LCD_DATA_ADDRESS;
}

/*******************************************************************************
* Clear display                                                                *
*   Parameter:    color:  color for clearing display                           *
*   Return:                                                                    *
*******************************************************************************/

void GLCD_clear (unsigned short color) {
  unsigned int   i;

  wr_reg(0x20, 0);
  wr_reg(0x21, 0);
  LcdWriteReg(0x22);
  for(i = 0; i < (WIDTH*HEIGHT); i++)
  {
  	LcdWriteData(color);
  } 
}

void STM3210E_LCD_Init(void)
{
	driverCode = rd_reg(0);
	
	wr_reg(0x0001, 0x0100); 
	//wr_reg(0x0001, 0x0000); 
	wr_reg(0x0002, 0x0700); 
	wr_reg(0x0003, 0x1030); 
	//wr_reg(0x0003, 0x0030); BGR
	wr_reg(0x0004, 0x0000); 
	wr_reg(0x0008, 0x0202); 
	wr_reg(0x0009, 0x0000); 
	wr_reg(0x000A, 0x0000); 
	wr_reg(0x000C, 0x0000); 
	wr_reg(0x000D, 0x0000); 
	wr_reg(0x000F, 0x0000); 
//*************Power On sequence ****************//
	wr_reg(0x0010, 0x0000); 
	wr_reg(0x0011, 0x0007);
	wr_reg(0x0012, 0x0000); 
	wr_reg(0x0013, 0x0000); 
	wr_reg(0x0007, 0x0001);
	HAL_Delay(20);
	wr_reg(0x0010, 0x1690); 
	wr_reg(0x0011, 0x0227);
	HAL_Delay(20);
	wr_reg(0x0012, 0x001A); 
	HAL_Delay(20);
	wr_reg(0x0013, 0x1400); 
	wr_reg(0x0029, 0x0024); 
	wr_reg(0x002B, 0x000C); 
	HAL_Delay(20);
	wr_reg(0x0020, 0x0000); 
	wr_reg(0x0021, 0x0000); 
// ----------- Adjust the Gamma Curve ----------//
	wr_reg(0x0030, 0x0000);
	wr_reg(0x0031, 0x0707);
	wr_reg(0x0032, 0x0307);
	wr_reg(0x0035, 0x0200);
	wr_reg(0x0036, 0x0008);
	wr_reg(0x0037, 0x0004);
	wr_reg(0x0038, 0x0000);
	wr_reg(0x0039, 0x0707);
	wr_reg(0x003C, 0x0002);
	wr_reg(0x003D, 0x1D04);
//------------------ Set GRAM area ---------------//
	wr_reg(0x0050, 0x0000);
	wr_reg(0x0051, 0x00EF); 
	wr_reg(0x0052, 0x0000); 
	wr_reg(0x0053, 0x013F); 
	wr_reg(0x0060, 0xA700); 
	wr_reg(0x0061, 0x0001);//general TFT
	//wr_reg(0x0061, 0x0000);//IPS TFT
	wr_reg(0x006A, 0x0000); 
//-------------- Partial Display Control ---------//
	wr_reg(0x0080, 0x0000);
	wr_reg(0x0081, 0x0000);
	wr_reg(0x0082, 0x0000);
	wr_reg(0x0083, 0x0000);
	wr_reg(0x0084, 0x0000);
	wr_reg(0x0085, 0x0000);
//-------------- Panel Control -------------------//
	wr_reg(0x0090, 0x0010);
	wr_reg(0x0092, 0x0600);
	wr_reg(0x0007, 0x0133); // ߪǴДʾ
	HAL_Delay(20); 	
}
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
