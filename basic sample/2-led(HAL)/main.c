

#include "stm32f4xx_hal.h"


	/**
		* @brief  This function handles SysTick Handler.
		* @param  None
		* @retval None
		*/
	void SysTick_Handler(void)
	{
		HAL_IncTick();
	}

static GPIO_InitTypeDef  GPIO_InitStruct;


int main(void)
{
	
	  HAL_Init();
	
	  __HAL_RCC_GPIOB_CLK_ENABLE();
	
		GPIO_InitStruct.Pin = GPIO_PIN_14 |  GPIO_PIN_15;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct); 


	
	
	  while(1)
		{ 		
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
			HAL_Delay(100);	
      HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_15);
      HAL_Delay(100);				
		
		}


return 0;
}	