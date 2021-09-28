







#include "GUI.h"
#include "GUIDRV_FlexColor.h"
#include "global_includes.h"
#include "stm32f4xx_hal.h"
#include "emwin_port.h"



/*********************************************************************
*
*       Defines, configurable
*
**********************************************************************
*/

//
// Define the available number of bytes available for the GUI
//
//#define GUI_NUMBYTES  (1024) * 10   // x KByte

#define GUI_NUMBYTES  0xf000
//
// Define the average block size
//
#define GUI_BLOCKSIZE 0x80

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/


/* 32 bit aligned memory area */
U32 extMem[GUI_NUMBYTES / 4];

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_X_Config
*
* Purpose:
*   Called during the initialization process in order to set up the
*   available memory for the GUI.
*/
void GUI_X_Config(void)
{

  GUI_ALLOC_AssignMemory(extMem, GUI_NUMBYTES);
	
	GUI_ALLOC_SetAvBlockSize(GUI_BLOCKSIZE);

}



/*********************************************************************
*
*       Global data
*/
extern __IO uint32_t uwTick;

/*********************************************************************
*
*      Timing:
*                 GUI_X_GetTime()
*                 GUI_X_Delay(int)

  Some timing dependent routines require a GetTime
  and delay function. Default time unit (tick), normally is
  1 ms.
*/

GUI_TIMER_TIME GUI_X_GetTime(void) { 
  return uwTick; 
}

void GUI_X_Delay(int ms) { 
  int tEnd = uwTick + ms;
  while ((tEnd - uwTick) > 0);
}

/*********************************************************************
*
*       GUI_X_Init()
*
* Note:
*     GUI_X_Init() is called from GUI_Init is a possibility to init
*     some hardware which needs to be up and running before the GUI.
*     If not required, leave this routine blank.
*/

void GUI_X_Init(void) {}


/*********************************************************************
*
*       GUI_X_ExecIdle
*
* Note:
*  Called if WM is in idle state
*/

void GUI_X_ExecIdle(void) {}

/*********************************************************************
*
*      Logging: OS dependent

Note:
  Logging is used in higher debug levels only. The typical target
  build does not use logging and does therefor not require any of
  the logging routines below. For a release build without logging
  the routines below may be eliminated to save some space.
  (If the linker is not function aware and eliminates unreferenced
  functions automatically)

*/

void GUI_X_Log     (const char *s) { GUI_USE_PARA(s); }
void GUI_X_Warn    (const char *s) { GUI_USE_PARA(s); }
void GUI_X_ErrorOut(const char *s) { GUI_USE_PARA(s); }

void GUI_X_InitOS(void)    {}
void GUI_X_Unlock(void)    {}
void GUI_X_Lock(void)      {}
U32  GUI_X_GetTaskId(void) { return 1; }

/*************************** End of file ****************************/

/*********************************************************************
*
*       Layer configuration (to be modified)
*
**********************************************************************
*/

//
// Physical display size
//
#define XSIZE_PHYS  240
#define YSIZE_PHYS  320

/*********************************************************************
*
*       Configuration checking
*
**********************************************************************
*/
#define VXSIZE_PHYS XSIZE_PHYS
#define VYSIZE_PHYS YSIZE_PHYS

#define DISPLAY_ORIENTATION ( GUI_SWAP_XY | GUI_MIRROR_Y )


/*********************************************************************
*
*       Defines, sfrs
*
**********************************************************************
*/
//
// COG interface register addr.
//
	


#define LCD_DATA_ADDRESS    *(volatile U16*) ((volatile U32)0x60020000) 
#define LCD_REG_ADDRESS     *(volatile U16*) ((volatile U32)0x60000000)	

void STM3210E_LCD_Init(void);

/*********************************************************************
*
*       Local functions
*
**********************************************************************
*/
/********************************************************************
*
*       LcdWriteReg
*
* Function description:
*   Sets display register
*/
//U16 Datareg;
static void LcdWriteReg(U16 Data) {
  LCD_REG_ADDRESS = Data;
}

/********************************************************************
*
*       LcdWriteData
*
* Function description:
*   Writes a value to a display register
*/
static void LcdWriteData(U16 Data) {
  LCD_DATA_ADDRESS = Data;
}

/********************************************************************
*
*       LcdWriteDataMultiple
*
* Function description:
*   Writes multiple values to a display register.
*/
static void LcdWriteDataMultiple(U16 * pData, int NumItems) {
  while (NumItems--) {
    LCD_DATA_ADDRESS = *pData++;
  }
}

/********************************************************************
*
*       LcdReadDataMultiple
*
* Function description:
*   Reads multiple values from a display register.
*/
static void LcdReadDataMultiple(U16 * pData, int NumItems) {
  while (NumItems--) {
    *pData++ = LCD_DATA_ADDRESS;
  }
}

U16 LcdReadData(void)
{
	return LCD_DATA_ADDRESS;
}

/*********************************************************************
*
*       Public functions
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_X_Config
*
* Function description:
*   Called during the initialization process in order to set up the
*   display driver configuration.
*
*/
void LCD_X_Config(void) {
  GUI_DEVICE * pDevice;
  CONFIG_FLEXCOLOR Config = {0};
  GUI_PORT_API PortAPI = {0};
  //
  // Set display driver and color conversion
  //
  pDevice = GUI_DEVICE_CreateAndLink(GUIDRV_FLEXCOLOR, GUICC_565, 0, 0);
  //
  // Display driver configuration, required for Lin-driver
  //
  LCD_SetSizeEx (0, XSIZE_PHYS , YSIZE_PHYS);
  LCD_SetVSizeEx(0, VXSIZE_PHYS, VYSIZE_PHYS);
  //
  // Orientation
  //
  Config.Orientation = DISPLAY_ORIENTATION ;
  GUIDRV_FlexColor_Config(pDevice, &Config);
  //
  // Set controller and operation mode
  //
  PortAPI.pfWrite16_A0  = LcdWriteReg;
  PortAPI.pfWrite16_A1  = LcdWriteData;
  PortAPI.pfWriteM16_A1 = LcdWriteDataMultiple;
  PortAPI.pfReadM16_A1  = LcdReadDataMultiple;
	PortAPI.pfRead16_A1 = LcdReadData;
	GUIDRV_FlexColor_SetFunc(pDevice, &PortAPI, GUIDRV_FLEXCOLOR_F66708, GUIDRV_FLEXCOLOR_M16C0B16);
	
}



/*********************************************************************
*
*       LCD_X_DisplayDriver
*
* Function description:
*   This function is called by the display driver for several purposes.
*   To support the according task the routine needs to be adapted to
*   the display controller. Please note that the commands marked with
*   'optional' are not cogently required and should only be adapted if
*   the display controller supports these features.
*
* Parameter:
*   LayerIndex - Index of layer to be configured
*   Cmd        - Please refer to the details in the switch statement below
*   pData      - Pointer to a LCD_X_DATA structure
*
* Return Value:
*   < -1 - Error
*     -1 - Command not handled
*      0 - Ok
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) {
  int r;
  (void) LayerIndex;
  (void) pData;
  
  switch (Cmd) {
  case LCD_X_INITCONTROLLER: {
    STM3210E_LCD_Init();
    return 0;
  }
  default:
    r = -1;
  }
  return r;
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

U16 driverCode;

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