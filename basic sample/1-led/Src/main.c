

#include "stm32f4xx.h"


int main(void)
{
	
  RCC->AHB1ENR = RCC_AHB1ENR_GPIOBEN;
	GPIOB->MODER = GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0;
	GPIOB->ODR = GPIO_ODR_ODR_14 ; 
	
	while(1);	
	return 0;
}	
	