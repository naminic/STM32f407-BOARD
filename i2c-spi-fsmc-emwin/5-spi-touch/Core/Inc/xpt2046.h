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

#ifndef _XPT2046_H_
#define _XPT2046_H_

/* Includes ------------------------------------------------------------------*/
//#include "stm32f4xx.h"
//#include "GLCD.h" 
#include "main.h"

typedef	struct POINT 
{
   int x;
   int y;
}Coordinate;

/* Private define ------------------------------------------------------------*/
/* AD channel selection command */
#define	CHX 	        0x90 	/* Channel X+ command*/	
#define	CHY 	        0xd0	/* Channel Y+ command* */

#define TP_CS(x)		HAL_GPIO_WritePin(TP_CS_GPIO_Port,TP_CS_Pin,x)

#define TP_INT_IN   (HAL_GPIO_ReadPin(TP_INT_GPIO_Port,TP_INT_Pin))


/* Private function prototypes -----------------------------------------------*/				
void xpt2046_init(void);	
void TP_GetAdXY(int *x,int *y);
#endif

/************************ (C) COPYRIGHT HAOYU Electronics *****END OF FILE****/