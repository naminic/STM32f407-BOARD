

#include "stm32f4xx_hal.h"
#include "LiquidCrystal.h"
#include "string.h"

extern "C"
{
	/**
		* @brief  This function handles SysTick Handler.
		* @param  None
		* @retval None
		*/
	void SysTick_Handler(void)
	{
		HAL_IncTick();
	}
}

#define BIN_TO_BYTE(b7,b6,b5,b4,b3,b2,b1,b0) ((b7 << 7)+(b6 << 6)+(b5 << 5)+(b4 << 4)+(b3 << 3)+(b2 << 2)+(b1 << 1)+b0)

// make some custom characters:
uint8_t heart[8] = {
	BIN_TO_BYTE(0,0,0,0,0,0,0,0),
	BIN_TO_BYTE(0,0,0,0,1,0,1,0),
	BIN_TO_BYTE(0,0,0,1,1,1,1,1),
	BIN_TO_BYTE(0,0,0,1,1,1,1,1),
	BIN_TO_BYTE(0,0,0,1,1,1,1,1),
	BIN_TO_BYTE(0,0,0,0,1,1,1,0),
	BIN_TO_BYTE(0,0,0,0,0,1,0,0),
	BIN_TO_BYTE(0,0,0,0,0,0,0,0),	
};


int main(void)
{
	int thisChar = 'a';
	 char str[20]; 
	 int i;
	
	 HAL_Init();
	
	 __HAL_RCC_GPIOB_CLK_ENABLE();
	
	LiquidCrystal lcd;
	lcd.begin(16, 2);
	lcd.cursor();
//	lcd.setCursor(0,0);
	  // create a new character
  //lcd.createChar(0, heart);
//	sprintf(str,"sina kalani");
//	lcd.print(str);
	//lcd.blink();
	//lcd.print("hello, world!");
	
	
	
	  while(1)
		{
			
  // reverse directions at 'm':
  if (thisChar == 'm') {
    // go right for the next letter
    lcd.rightToLeft();
  }
  // reverse again at 's':
  if (thisChar == 's') {
    // go left for the next letter
    lcd.leftToRight();
  }
  // reset at 'z':
  if (thisChar > 'z') {
    // go to (0,0):
    lcd.home();
    // start again at 0
    thisChar = 'a';
  }
  // print the character
  lcd.write(thisChar);
  // wait a second:
  HAL_Delay(1000);
  // increment the letter:
  thisChar++;
		
		}


return 0;
}	