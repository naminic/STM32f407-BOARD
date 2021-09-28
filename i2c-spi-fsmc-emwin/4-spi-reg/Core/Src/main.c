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

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
int CX,CY;

#define	CHX 	        0x90 	/* Channel X+ command*/	
#define	CHY 	        0xd0	/* Channel Y+ command* */

#define TP_CS_Pin GPIO_ODR_OD3
#define TP_CS_GPIO_Port GPIOE

void TP_CS(char x)
{		
	if(x) 
	TP_CS_GPIO_Port->BSRR = TP_CS_Pin; 
	else 
	TP_CS_GPIO_Port->BSRR = (uint32_t)TP_CS_Pin << 16U;
}
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t SPI_Transmit (uint8_t *data, int size)
{
	
	/************** STEPS TO FOLLOW *****************
	1. Wait for the TXE bit to set in the Status Register
	2. Write the data to the Data Register
	3. After the data has been transmitted, wait for the BSY bit to reset in Status Register
	4. Clear the Overrun flag by reading DR and SR
	************************************************/		
	
	int i=0;
	while (i<size)
	{
	   while (!((SPI1->SR)&	SPI_SR_TXE)) {};  // wait for TXE bit to set -> This will indicate that the buffer is empty
	   SPI1->DR = data[i];  // load the data into the Data Register
	   i++;
	}	
	
	
/*During discontinuous communications, there is a 2 APB clock period delay between the
write operation to the SPI_DR register and BSY bit setting. As a consequence it is
mandatory to wait first until TXE is set and then until BSY is cleared after writing the last
data.
*/
	while (!((SPI1->SR)&SPI_SR_TXE)) {};  // wait for TXE bit to set -> This will indicate that the buffer is empty
	while (((SPI1->SR)& SPI_SR_BSY)) {};  // wait for BSY bit to Reset -> This will indicate that SPI is not busy in communication	
	
	//  Clear the Overrun flag by reading DR and SR
	uint8_t temp = SPI1->SR;
					temp = SPI1->DR;
		
	return temp;
}

void SPI_Receive (uint8_t *data, int size)
{
	/************** STEPS TO FOLLOW *****************
	1. Wait for the BSY bit to reset in Status Register
	2. Send some Dummy data before reading the DATA
	3. Wait for the RXNE bit to Set in the status Register
	4. Read data from Data Register
	************************************************/		

	while (size)
	{
		while (((SPI1->SR)&	SPI_SR_BSY)) {};  // wait for BSY bit to Reset -> This will indicate that SPI is not busy in communication
		SPI1->DR = 0;  // send dummy data
		while (!((SPI1->SR) & SPI_SR_RXNE)){};  // Wait for RXNE to set -> This will indicate that the Rx buffer is not empty
	  *data++ = (SPI1->DR);
		size--;
	}	
}


unsigned char WR_CMD (unsigned char cmd)  
{ 
	unsigned char DataRX = 0; 
	DataRX = SPI_Transmit(&cmd,1);
	return DataRX;
}

/**
 * @brief	delay function
 * @param	cnt: Delay value
 * @retval None
 */
static void delay_nus(int cnt)
{
	int i,us;
	for(i = 0;i<cnt;i++)
	{
		us = 400;
		while (us--)     /* delay	*/
		{
		}
	}
}

/**
 * @brief	read xpt2046 adc value
 * @param	None
 * @retval return adc value 
 */  
static int RD_AD(void)  
{ 
	unsigned short buf,temp; 

	temp = WR_CMD(0x00);
	buf = temp << 8; 
	delay_nus(1); 
	temp = WR_CMD(0x00);;
	buf |= temp; 
	buf >>= 3; 
	buf &= 0xfff; 
	return buf;
}

/**
 * @brief	read xpt2046 channel X+ adc value
 * @param	None
 * @retval return channel X+ adc value
 */  
int Read_X(void)  
{  
	unsigned short temp;
	TP_CS(0); 
	delay_nus(1); 
	WR_CMD(CHX); 
	delay_nus(1); 
	temp = RD_AD(); 
	TP_CS(1); 
	return temp;    
} 

/**
 * @brief	read xpt2046 channel Y+ adc value
 * @param	None
 * @retval return channel Y+ adc value
 */  
int Read_Y(void)  
{  
	unsigned short temp;
	TP_CS(0);
	delay_nus(1);
	WR_CMD(CHY);
	delay_nus(1);
	temp = RD_AD();
	TP_CS(1); 
	return temp;
} 

/**
 * @brief	read xpt2046 channel X+ channel Y+ adc value
 * @param	None
 * @retval return channel X+ channel Y+ adc value
 */  
void TP_GetAdXY(int *x,int *y)  
{ 
	int adx,ady; 
	adx = Read_X(); 
	delay_nus(1); 
	ady = Read_Y(); 
	*x = adx; 
	*y = ady; 
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

  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* System interrupt init*/

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	
	GPIOE->MODER |= GPIO_MODER_MODE3_0;
	GPIOE->OSPEEDR |= GPIO_OSPEEDR_OSPEED3_0 | GPIO_OSPEEDR_OSPEED3_1;
	
	GPIOB->MODER |= GPIO_MODER_MODE3_1 | GPIO_MODER_MODE4_1 | GPIO_MODER_MODE5_1;
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED3_0 | GPIO_OSPEEDR_OSPEED3_1 
									| GPIO_OSPEEDR_OSPEED4_0 | GPIO_OSPEEDR_OSPEED4_1 
									| GPIO_OSPEEDR_OSPEED5_0 | GPIO_OSPEEDR_OSPEED5_1;
									
  GPIOB->AFR[0] |= GPIO_AFRL_AFSEL3_0 | GPIO_AFRL_AFSEL3_2
									|GPIO_AFRL_AFSEL4_0 | GPIO_AFRL_AFSEL4_2
									|GPIO_AFRL_AFSEL5_0 | GPIO_AFRL_AFSEL5_2;
									
									
  /************** STEPS TO FOLLOW *****************
	1. Enable SPI clock
	2. Configure the Control Register 1
	3. Configure the CR2
	************************************************/	
	
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;  // Enable SPI1 CLock
	
	SPI1->CR1 |= SPI_CR1_MSTR;  // Master Mode
	
	SPI1->CR1 |= SPI_CR1_BR_1 | SPI_CR1_BR_0; 
	
	SPI1->CR1 |= SPI_CR1_SSI | SPI_CR1_SSM;  // SSM=1, SSi=1 -> Software Slave Management
	
	SPI1->CR2 = 0;
	
	SPI1->CR1 |= SPI_CR1_SPE;
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		TP_GetAdXY(&CX,&CY);
		delay_nus(100);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_5);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_5)
  {
  }
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {

  }
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_8, 168, LL_RCC_PLLP_DIV_2);
  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {

  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_4);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {

  }
  LL_Init1msTick(168000000);
  LL_SetSystemCoreClock(168000000);
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
