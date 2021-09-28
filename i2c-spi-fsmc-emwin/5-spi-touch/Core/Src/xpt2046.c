/****************************************Copyright (c)****************************************************
**                                      
**                        http://www.powermcu.com & http://www.hotmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               xpt2046.c
** Descriptions:            resistive touch screen, compatible ads7843
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             AVRman
** Modified date:           2015-7-2
** Version:                 V1.1
** Descriptions:            add english description
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
//#include "GLCD.h"
#include "xpt2046.h"
#include "spi.h"



extern unsigned int GlobalX;
extern unsigned int GlobalY;
/* Private define ------------------------------------------------------------*/
#define THRESHOLD 2   /* The bigger of the value, the lower the sensitivity */

/**
 * @brief	XPT2046 SPI initialization
 * @param	None
 * @retval None
 */  
void xpt2046_init(void)
{ 

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
 * @brief	SPI bus transmit and receive data
 * @param	cmd: send value
 * @retval return receive data 
 */  
static unsigned char WR_CMD (unsigned char cmd)  
{ 
	unsigned char DataRX = 0; 
	HAL_SPI_TransmitReceive(&hspi1,&cmd,&DataRX,1,1000);
	return DataRX;
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
