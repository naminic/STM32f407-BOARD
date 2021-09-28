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
#include "crc.h"
#include "spi.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "gui.h"
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



//void LCD_Init(void);
//void LCD_Clear(U16 color);

//U16 driverCode;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
extern void MainTask(void);
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
  MX_SPI1_Init();
  MX_FSMC_Init();
  MX_CRC_Init();
  /* USER CODE BEGIN 2 */
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,0);
	HAL_Delay(100);
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,1);
	HAL_Delay(100);
	
	
	MainTask();
	
	GUI_Init();
	
	
	GUI_SetBkColor(GUI_RED);
	GUI_Clear();
	
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		GUI_Delay(100);
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




//#define LCD_DATA_ADDRESS    *(volatile U16*) ((volatile U32)0x60020000) 
//#define LCD_REG_ADDRESS     *(volatile U16*) ((volatile U32)0x60000000)	
//	
//static void LcdWriteReg(U16 Data) {
//  LCD_REG_ADDRESS = Data;
//}

///********************************************************************
//*
//*       LcdWriteData
//*
//* Function description:
//*   Writes a value to a display register
//*/
//static void LcdWriteData(U16 Data) {
//  LCD_DATA_ADDRESS = Data;
//}


//#define LCD_X_Write00_16 LcdWriteReg
//#define LCD_X_Write01_16 LcdWriteData

//U16 LCD_X_Read01_16(void) {
//	
//	return  LCD_DATA_ADDRESS;
//}


//static void wr_reg (U16 reg, U16 dat) {
//  LcdWriteReg(reg);
//  LcdWriteData(dat);
//}


//static U16 rd_reg (U16 reg) {
//  LcdWriteReg(reg);
//	HAL_Delay(1);
//  return LCD_X_Read01_16();
//}


//void ili9328_WriteReg(U16 reg, U16 dat) {
//	  LcdWriteReg(reg);
//  LcdWriteData(dat);
//}


///* LCD Command Codes */
//#define TS_INS_START_OSC            0x00
//#define TS_INS_DRIV_OUT_CTRL        0x01
//#define TS_INS_DRIV_WAV_CTRL        0x02
//#define TS_INS_ENTRY_MOD            0x03
//#define TS_INS_RESIZE_CTRL          0x04
//#define TS_INS_DISP_CTRL1           0x07
//#define TS_INS_DISP_CTRL2           0x08
//#define TS_INS_DISP_CTRL3           0x09
//#define TS_INS_DISP_CTRL4           0x0A
//#define TS_INS_RGB_DISP_IF_CTRL1    0x0C
//#define TS_INS_FRM_MARKER_POS       0x0D
//#define TS_INS_RGB_DISP_IF_CTRL2    0x0F
//#define TS_INS_POW_CTRL1            0x10
//#define TS_INS_POW_CTRL2            0x11
//#define TS_INS_POW_CTRL3            0x12
//#define TS_INS_POW_CTRL4            0x13
//#define TS_INS_GRAM_HOR_AD          0x20
//#define TS_INS_GRAM_VER_AD          0x21
//#define TS_INS_RW_GRAM              0x22
//#define TS_INS_POW_CTRL7            0x29
//#define TS_INS_FRM_RATE_COL_CTRL    0x2B
//#define TS_INS_GAMMA_CTRL1          0x30
//#define TS_INS_GAMMA_CTRL2          0x31
//#define TS_INS_GAMMA_CTRL3          0x32
//#define TS_INS_GAMMA_CTRL4          0x35 
//#define TS_INS_GAMMA_CTRL5          0x36
//#define TS_INS_GAMMA_CTRL6          0x37
//#define TS_INS_GAMMA_CTRL7          0x38
//#define TS_INS_GAMMA_CTRL8          0x39
//#define TS_INS_GAMMA_CTRL9          0x3C
//#define TS_INS_GAMMA_CTRL10         0x3D
//#define TS_INS_HOR_START_AD         0x50
//#define TS_INS_HOR_END_AD           0x51
//#define TS_INS_VER_START_AD         0x52
//#define TS_INS_VER_END_AD           0x53
//#define TS_INS_GATE_SCAN_CTRL1      0x60
//#define TS_INS_GATE_SCAN_CTRL2      0x61
//#define TS_INS_GATE_SCAN_CTRL3      0x6A
//#define TS_INS_PART_IMG1_DISP_POS   0x80
//#define TS_INS_PART_IMG1_START_AD   0x81
//#define TS_INS_PART_IMG1_END_AD     0x82
//#define TS_INS_PART_IMG2_DISP_POS   0x83
//#define TS_INS_PART_IMG2_START_AD   0x84
//#define TS_INS_PART_IMG2_END_AD     0x85
//#define TS_INS_PANEL_IF_CTRL1       0x90
//#define TS_INS_PANEL_IF_CTRL2       0x92
//#define TS_INS_PANEL_IF_CTRL3       0x93
//#define TS_INS_PANEL_IF_CTRL4       0x95
//#define TS_INS_PANEL_IF_CTRL5       0x97
//#define TS_INS_PANEL_IF_CTRL6       0x98  

//#define TS_VAL_ENTRY_MOD            0x0030




//#define  ILI9328_LCD_PIXEL_WIDTH    ((uint16_t)320)
//#define  ILI9328_LCD_PIXEL_HEIGHT   ((uint16_t)240)
//   
///** 
//  * @brief  ILI9328 Registers  
//  */ 
//#define LCD_REG_0             0x00
//#define LCD_REG_1             0x01
//#define LCD_REG_2             0x02
//#define LCD_REG_3             0x03
//#define LCD_REG_4             0x04
//#define LCD_REG_7             0x07
//#define LCD_REG_8             0x08
//#define LCD_REG_9             0x09
//#define LCD_REG_10            0x0A
//#define LCD_REG_12            0x0C
//#define LCD_REG_13            0x0D
//#define LCD_REG_15            0x0F
//#define LCD_REG_16            0x10
//#define LCD_REG_17            0x11
//#define LCD_REG_18            0x12
//#define LCD_REG_19            0x13
//#define LCD_REG_32            0x20
//#define LCD_REG_33            0x21
//#define LCD_REG_34            0x22
//#define LCD_REG_41            0x29
//#define LCD_REG_43            0x2B
//#define LCD_REG_48            0x30
//#define LCD_REG_49            0x31
//#define LCD_REG_50            0x32
//#define LCD_REG_53            0x35
//#define LCD_REG_54            0x36
//#define LCD_REG_55            0x37
//#define LCD_REG_56            0x38
//#define LCD_REG_57            0x39
//#define LCD_REG_60            0x3C
//#define LCD_REG_61            0x3D
//#define LCD_REG_80            0x50
//#define LCD_REG_81            0x51
//#define LCD_REG_82            0x52
//#define LCD_REG_83            0x53
//#define LCD_REG_96            0x60
//#define LCD_REG_97            0x61
//#define LCD_REG_106           0x6A
//#define LCD_REG_128           0x80
//#define LCD_REG_129           0x81
//#define LCD_REG_130           0x82
//#define LCD_REG_131           0x83
//#define LCD_REG_132           0x84
//#define LCD_REG_133           0x85
//#define LCD_REG_144           0x90
//#define LCD_REG_146           0x92
//#define LCD_REG_147           0x93
//#define LCD_REG_149           0x95
//#define LCD_REG_151           0x97
//#define LCD_REG_152           0x98
//#define LCD_REG_161           0xA1
//#define LCD_REG_162           0xA2
//#define LCD_REG_165           0xA5


//void LCD_Clear(U16 color)
//{
//	unsigned int l=320,w;
//  wr_reg(TS_INS_GRAM_HOR_AD,0);
//	wr_reg(TS_INS_GRAM_VER_AD,0);
//  LcdWriteReg(TS_INS_RW_GRAM);
//	while(l--)
//	{
//	    for(w=0;w<240;w++)
//		{    
//          	LcdWriteData(color);
//		}
//	}


//}


///**
//  * @brief  Enables the Display.
//  * @param  None
//  * @retval None
//  */
//void ili9328_DisplayOn(void)
//{
//  /* Power On sequence ---------------------------------------------------------*/
//  ili9328_WriteReg(LCD_REG_16, 0x0000); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
//  ili9328_WriteReg(LCD_REG_17, 0x0000); /* DC1[2:0], DC0[2:0], VC[2:0] */
//  ili9328_WriteReg(LCD_REG_18, 0x0000); /* VREG1OUT voltage */
//  ili9328_WriteReg(LCD_REG_19, 0x0000); /* VDV[4:0] for VCOM amplitude */
//  HAL_Delay(20);
//  ili9328_WriteReg(LCD_REG_16, 0x14B0); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
//  HAL_Delay(5);
//  ili9328_WriteReg(LCD_REG_17, 0x0007); /* DC1[2:0], DC0[2:0], VC[2:0] */
//  HAL_Delay(5);
//  ili9328_WriteReg(LCD_REG_18, 0x0018); /* VREG1OUT voltage */
//  HAL_Delay(5);    
//  ili9328_WriteReg(LCD_REG_19, 0x1000); /* VDV[4:0] for VCOM amplitude */
//  ili9328_WriteReg(LCD_REG_41, 0x0015); /* VCM[4:0] for VCOMH */
//  HAL_Delay(5);    
// 
//  /* Display On */
//  ili9328_WriteReg(LCD_REG_7, 0x0133); /* 262K color and display ON */
//  HAL_Delay(50);
//}


///**
//  * @brief  Sets a display window
//  * @param  Xpos:   specifies the X bottom left position.
//  * @param  Ypos:   specifies the Y bottom left position.
//  * @param  Height: display window height.
//  * @param  Width:  display window width.
//  * @retval None
//  */
//void ili9328_SetDisplayWindow(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
//{
//  /* Horizontal GRAM Start Address */
//  ili9328_WriteReg(LCD_REG_80, (Xpos));
//  /* Horizontal GRAM End Address */
//  ili9328_WriteReg(LCD_REG_81, (Xpos + Height - 1));
//  
//  /* Vertical GRAM Start Address */
//  ili9328_WriteReg(LCD_REG_82, (Ypos));
//  /* Vertical GRAM End Address */
//  ili9328_WriteReg(LCD_REG_83, (Ypos + Width - 1));  
//}


///**
//  * @brief  Get the LCD pixel Width.
//  * @param  None
//  * @retval The Lcd Pixel Width
//  */
//uint16_t ili9328_GetLcdPixelWidth(void)
//{
// return (uint16_t)ILI9328_LCD_PIXEL_WIDTH;
//}

///**
//  * @brief  Get the LCD pixel Height.
//  * @param  None
//  * @retval The Lcd Pixel Height
//  */
//uint16_t ili9328_GetLcdPixelHeight(void)
//{
// return (uint16_t)ILI9328_LCD_PIXEL_HEIGHT;
//}


//void LCD_Init(void)
//{

//  driverCode = rd_reg(0);
//	if( driverCode == 0x9328 )
//	{
////			wr_reg(0x0000,0x0001);
////			wr_reg(0x001A, 0x0004); // BT[3:0]=0100, VCL=-VCI; VGH=VCI+2DDVDH; VGL=-2DDVDH
////			wr_reg(0x001B, 0x000C); // VRH[4:0]=0Ch, VREG1=(2.5v*1.9)=4.75V		VCIRE=1;// VCOM offset
////			wr_reg(0x0023, 0x0000); // SELVCM=0, R24h and R25h selects VCOM
////			wr_reg(0x0024, 0x0040); // VCM[6:0]=1000000, VCOMH voltage=VREG1*0.748 (originally 5F)
////			wr_reg(0x0025, 0x000F); // VDV[4:0]=01111, VCOMH amplitude=VREG*1.00
////			wr_reg(0x002D, 0x0006); // NOW[2:0]=110, Gate output non-overlap period = 6 clocks
////			HAL_Delay(20);
////			// Power on Setting
////			wr_reg(0x0018, 0x0008); // RADJ[3:0]=1000, Display frame rate 60Hz 100%
////			wr_reg(0x0019, 0x0001); // OSC_EN=1, start OSC
////			HAL_Delay(20);
////			wr_reg(0x0001, 0x0000); // DSTB=0, out deep sleep
////			wr_reg(0x001F, 0x0088); // STB=0
////			wr_reg(0x001C, 0x0006); // AP[2:0]=110, High OPAMP current (default 011)
////			HAL_Delay(10);
////			wr_reg(0x001F, 0x0080); // DK=0
////			HAL_Delay(10);
////			wr_reg(0x001F, 0x0090); // PON=1
////			HAL_Delay(5);
////			wr_reg(0x001F, 0x00D0); // VCOMG=1
////			HAL_Delay(10);
////			wr_reg(0x0017, 0x0005); // IFPF[2:0]=101, 16-bit/pixel
////			// Panel Configuration
////			//wr_reg(0x0036, 0x0011); // REV_PANEL=1, SM_PANEL=1, GS_PANEL=1, SS_PANEL=1
////			//wr_reg(0x0029, 0x0031); // NL[5:0]=110001, 400 lines
////			//wr_reg(0x0071, 0x001A); // RTN0
////			//Gamma 2.2 Setting
////			wr_reg(0x0040, 0x0000);
////			wr_reg(0x0041, 0x0009);
////			wr_reg(0x0042, 0x0012);
////			wr_reg(0x0043, 0x0004);
////			wr_reg(0x0044, 0x0000);
////			wr_reg(0x0045, 0x0023);//
////			wr_reg(0x0046, 0x0003);
////			wr_reg(0x0047, 0x005E);//
////			wr_reg(0x0048, 0x0000);
////			wr_reg(0x0049, 0x0000);
////			wr_reg(0x004A, 0x0000);
////			wr_reg(0x004B, 0x0000);
////			wr_reg(0x004C, 0x0000);
////			wr_reg(0x004D, 0x0000);
////			wr_reg(0x004E, 0x0000);
////			wr_reg(0x0057, 0x004F);//
////		#ifdef ORIENTATION_VERTICAL
////			wr_reg(0x0016, 0x00C8);
////		#else
////			wr_reg(0x0016, 0x00A8);//A8
////		#endif
////			wr_reg(0x0028, 0x0038); //GON=1; DTE=1; D[1:0]=10
////			HAL_Delay(40);
////			wr_reg(0x0028, 0x003C); //GON=1; DTE=1; D[1:0]=11

////			HAL_Delay(10); 

//    /* Start Initial Sequence ------------------------------------------------*/
////    ili9328_WriteReg(LCD_REG_0, 0x0001); /* Start internal OSC. */
////    ili9328_WriteReg(LCD_REG_1, 0x0100); /* Set SS and SM bit */
////    ili9328_WriteReg(LCD_REG_2, 0x0700); /* Set 1 line inversion */
////    ili9328_WriteReg(LCD_REG_3, 0x1018); /* Set GRAM write direction and BGR=1. */
////    ili9328_WriteReg(LCD_REG_4, 0x0000); /* Resize register */
////    ili9328_WriteReg(LCD_REG_8, 0x0302); /* Set the back porch and front porch */
////    ili9328_WriteReg(LCD_REG_9, 0x0000); /* Set non-display area refresh cycle ISC[3:0] */
////    ili9328_WriteReg(LCD_REG_10, 0x0000); /* FMARK function */
////    ili9328_WriteReg(LCD_REG_12, 0x0000); /* RGB interface setting */
////    ili9328_WriteReg(LCD_REG_13, 0x0000); /* Frame marker Position */
////    ili9328_WriteReg(LCD_REG_15, 0x0000); /* RGB interface polarity */
////    
////    ili9328_DisplayOn();
////    
////    /* Adjust the Gamma Curve (ILI9328)---------------------------------------*/
////    ili9328_WriteReg(LCD_REG_48, 0x0000);
////    ili9328_WriteReg(LCD_REG_49, 0x0107);
////    ili9328_WriteReg(LCD_REG_50, 0x0000);
////    ili9328_WriteReg(LCD_REG_53, 0x0203);
////    ili9328_WriteReg(LCD_REG_54, 0x0402);
////    ili9328_WriteReg(LCD_REG_55, 0x0000);
////    ili9328_WriteReg(LCD_REG_56, 0x0207);
////    ili9328_WriteReg(LCD_REG_57, 0x0000);
////    ili9328_WriteReg(LCD_REG_60, 0x0203);
////    ili9328_WriteReg(LCD_REG_61, 0x0403);
////    
////    /* Set GRAM area ---------------------------------------------------------*/
////    ili9328_SetDisplayWindow(0, 0, ili9328_GetLcdPixelWidth(), ili9328_GetLcdPixelHeight());
////    
////    ili9328_WriteReg(LCD_REG_96,  0xA700); /* Gate Scan Line(GS=1, scan direction is G320~G1) */
////    ili9328_WriteReg(LCD_REG_97,  0x0003); /* NDL,VLE, REV */
////    ili9328_WriteReg(LCD_REG_106, 0x0000); /* set scrolling line */
////    
////    /* Partial Display Control -----------------------------------------------*/
////    ili9328_WriteReg(LCD_REG_128, 0x0000);
////    ili9328_WriteReg(LCD_REG_129, 0x0000);
////    ili9328_WriteReg(LCD_REG_130, 0x0000);
////    ili9328_WriteReg(LCD_REG_131, 0x0000);
////    ili9328_WriteReg(LCD_REG_132, 0x0000);
////    ili9328_WriteReg(LCD_REG_133, 0x0000);
////    
////    /* Panel Control ---------------------------------------------------------*/
////    ili9328_WriteReg(LCD_REG_144, 0x0010);
////    ili9328_WriteReg(LCD_REG_146, 0x0000);
////    ili9328_WriteReg(LCD_REG_147, 0x0003);
////    ili9328_WriteReg(LCD_REG_149, 0x0110);
////    ili9328_WriteReg(LCD_REG_151, 0x0000);
////    ili9328_WriteReg(LCD_REG_152, 0x0000);


//		LCD_X_Write00_16(0x00E3);
//		LCD_X_Write01_16(0x3008); 					//set the internal timing
//		LCD_X_Write00_16(0x00E7);
//		LCD_X_Write01_16(0x0012); 					//set the internal timing
//		LCD_X_Write00_16(0x00EF);
//		LCD_X_Write01_16(0x1231); 					//set the internal timing
//		LCD_X_Write00_16(TS_INS_START_OSC);
//		LCD_X_Write01_16(0x0001); 					//start oscillator
//		HAL_Delay(50);

//		LCD_X_Write00_16(TS_INS_DRIV_OUT_CTRL);
//		LCD_X_Write01_16(0x0100); 					//set SS, SM
//		LCD_X_Write00_16(TS_INS_DRIV_WAV_CTRL);
//		LCD_X_Write01_16(0x0700); 					//set 1 line inversion
//	
//		LCD_X_Write00_16(TS_INS_ENTRY_MOD);
//		LCD_X_Write01_16(TS_VAL_ENTRY_MOD);			//set GRAM write direction, BGR=0

//		LCD_X_Write00_16(TS_INS_RESIZE_CTRL);
//		LCD_X_Write01_16(0x0000); 					//no resizing

//		LCD_X_Write00_16(TS_INS_DISP_CTRL2);
//		LCD_X_Write01_16(0x0202); 					//front & back porch periods = 2
//		LCD_X_Write00_16(TS_INS_DISP_CTRL3);
//		LCD_X_Write01_16(0x0000); 					
//		LCD_X_Write00_16(TS_INS_DISP_CTRL4);
//		LCD_X_Write01_16(0x0000); 					
//		LCD_X_Write00_16(TS_INS_RGB_DISP_IF_CTRL1);
//		LCD_X_Write01_16(0x0000); 					//select system interface				
//		LCD_X_Write00_16(TS_INS_FRM_MARKER_POS);
//		LCD_X_Write01_16(0x0000); 					
//		LCD_X_Write00_16(TS_INS_RGB_DISP_IF_CTRL2);
//		LCD_X_Write01_16(0x0000);					
//	
//		LCD_X_Write00_16(TS_INS_POW_CTRL1);
//		LCD_X_Write01_16(0x0000);
//		LCD_X_Write00_16(TS_INS_POW_CTRL2);
//		LCD_X_Write01_16(0x0007); 					
//		LCD_X_Write00_16(TS_INS_POW_CTRL3);
//		LCD_X_Write01_16(0x0000);
//		LCD_X_Write00_16(TS_INS_POW_CTRL4);
//		LCD_X_Write01_16(0x0000); 					
//		HAL_Delay(200);

//		LCD_X_Write00_16(TS_INS_POW_CTRL1);
//		LCD_X_Write01_16(0x1690);
//		LCD_X_Write00_16(TS_INS_POW_CTRL2);
//		LCD_X_Write01_16(0x0227); //LCD_X_Write01_16(0x0137); 					
//		HAL_Delay(50);

//		LCD_X_Write00_16(TS_INS_POW_CTRL3);
//		LCD_X_Write01_16(0x001A); //LCD_X_Write01_16(0x013C);
//		HAL_Delay(50);

//		LCD_X_Write00_16(TS_INS_POW_CTRL4);
//		LCD_X_Write01_16(0x1800); //LCD_X_Write01_16(0x1400);
//		LCD_X_Write00_16(TS_INS_POW_CTRL7);
//		LCD_X_Write01_16(0x002A); //LCD_X_Write01_16(0x0007);
//		HAL_Delay(50);

//		LCD_X_Write00_16(TS_INS_GRAM_HOR_AD);
//		LCD_X_Write01_16(0x0000);
//		LCD_X_Write00_16(TS_INS_GRAM_VER_AD);
//		LCD_X_Write01_16(0x0000);

//		LCD_X_Write00_16(TS_INS_GAMMA_CTRL1);
//		LCD_X_Write01_16(0x0007);
//		LCD_X_Write00_16(TS_INS_GAMMA_CTRL2);
//		LCD_X_Write01_16(0x0605);
//		LCD_X_Write00_16(TS_INS_GAMMA_CTRL3);
//		LCD_X_Write01_16(0x0106);
//		LCD_X_Write00_16(TS_INS_GAMMA_CTRL4);
//		LCD_X_Write01_16(0x0206);
//		LCD_X_Write00_16(TS_INS_GAMMA_CTRL5);
//		LCD_X_Write01_16(0x0808);
//		LCD_X_Write00_16(TS_INS_GAMMA_CTRL6);
//		LCD_X_Write01_16(0x0007);
//		LCD_X_Write00_16(TS_INS_GAMMA_CTRL7);
//		LCD_X_Write01_16(0x0201);
//		LCD_X_Write00_16(TS_INS_GAMMA_CTRL8);
//		LCD_X_Write01_16(0x0007);
//		LCD_X_Write00_16(TS_INS_GAMMA_CTRL9);
//		LCD_X_Write01_16(0x0602);
//		LCD_X_Write00_16(TS_INS_GAMMA_CTRL10);
//		LCD_X_Write01_16(0x0808);

//		LCD_X_Write00_16(TS_INS_HOR_START_AD);
//		LCD_X_Write01_16(0x0000);
//		LCD_X_Write00_16(TS_INS_HOR_END_AD);
//		LCD_X_Write01_16(0x00EF);
//		LCD_X_Write00_16(TS_INS_VER_START_AD);
//		LCD_X_Write01_16(0x0000);
//		LCD_X_Write00_16(TS_INS_VER_END_AD);
//		LCD_X_Write01_16(0x013F);
//		LCD_X_Write00_16(TS_INS_GATE_SCAN_CTRL1);
//		LCD_X_Write01_16(0xA700);
//		LCD_X_Write00_16(TS_INS_GATE_SCAN_CTRL2);
//		LCD_X_Write01_16(0x0001);
//		LCD_X_Write00_16(TS_INS_GATE_SCAN_CTRL3);
//		LCD_X_Write01_16(0x0000);

//		LCD_X_Write00_16(TS_INS_PART_IMG1_DISP_POS);
//		LCD_X_Write01_16(0x0000);
//		LCD_X_Write00_16(TS_INS_PART_IMG1_START_AD);
//		LCD_X_Write01_16(0x0000);
//		LCD_X_Write00_16(TS_INS_PART_IMG1_END_AD);
//		LCD_X_Write01_16(0x0000);
//		LCD_X_Write00_16(TS_INS_PART_IMG2_DISP_POS);
//		LCD_X_Write01_16(0x0000);
//		LCD_X_Write00_16(TS_INS_PART_IMG2_START_AD);
//		LCD_X_Write01_16(0x0000);
//		LCD_X_Write00_16(TS_INS_PART_IMG2_END_AD);
//		LCD_X_Write01_16(0x0000);

//		LCD_X_Write00_16(TS_INS_PANEL_IF_CTRL1);
//		LCD_X_Write01_16(0x0010);
//		LCD_X_Write00_16(TS_INS_PANEL_IF_CTRL2);
//		LCD_X_Write01_16(0x0000);
//		LCD_X_Write00_16(TS_INS_PANEL_IF_CTRL3);
//		LCD_X_Write01_16(0x0003);
//		LCD_X_Write00_16(TS_INS_PANEL_IF_CTRL4);
//		LCD_X_Write01_16(0x0110);
//		LCD_X_Write00_16(TS_INS_PANEL_IF_CTRL5);
//		LCD_X_Write01_16(0x0000);
//		LCD_X_Write00_16(TS_INS_PANEL_IF_CTRL6);
//		LCD_X_Write01_16(0x0000);

//		LCD_X_Write00_16(TS_INS_DISP_CTRL1);
//		LCD_X_Write01_16(0x0133);
//	}


//}
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
