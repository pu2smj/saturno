 /*-----------------------------------------------------------------
   Copyright (c)
   file.........: 
   description..: 
   user.........:
   -----------------------------------------------------------------*/
 /*
Configurable options include the following:
LCD_XSIZE 	horizontal resolution
LCD_YSIZE 	vertical resolution
LCD_XORG 	horizontal position on the logical screen
LCD_YORG 	vertical position on the logical screen
LCD_MIRROR_X 	mirrors horizontal axis if activated
LCD_MIRROR_Y 	mirrors vertical axis if activated
LCD_SWAP_XY 	swaps x/y axes

*/


//https://code.google.com/p/smileos/source/browse/trunk/emWin/src/gui/?r=339

   #include <rtl.h> 
   #include "GUI.h"
   #include "GUIDRV_FlexColor.h"

   #include "lcd_driver.h"
   #include "lcd_config.h"
   #include "stm32f10x.h"
   
   //#include "GUIDRV_Generic.h"

/*********************************************************************
*       Layer configuration
*********************************************************************/
   /* Physical display size */
   #define XSIZE_PHYS 240
   #define YSIZE_PHYS 320
  
   /* Color conversion */
   #define COLOR_CONVERSION    GUICC_M565
   // Orientation
   //#define DISPLAY_ORIENTATION (0)
   //#define DISPLAY_ORIENTATION (GUI_MIRROR_X)                     //vertical 180
   //#define DISPLAY_ORIENTATION (GUI_MIRROR_Y)                      //vert espelhado
   //#define DISPLAY_ORIENTATION (GUI_MIRROR_X | GUI_MIRROR_Y)     //vert 90
   //#define DISPLAY_ORIENTATION (GUI_SWAP_XY)                        //0 espelhado
   /////////////////////#define DISPLAY_ORIENTATION (GUI_MIRROR_X | GUI_SWAP_XY)
   #define DISPLAY_ORIENTATION (GUI_MIRROR_Y | GUI_SWAP_XY)         //0 normal
   //#define DISPLAY_ORIENTATION (GUI_MIRROR_X | GUI_MIRROR_Y | GUI_SWAP_XY)
   
//    #define TOUCH_X_MIN   350
//    #define TOUCH_X_MAX   3730
//    #define TOUCH_Y_MIN   330
//    #define TOUCH_Y_MAX   3750

   #define TOUCH_X_MIN   240
   #define TOUCH_X_MAX   3850
   #define TOUCH_Y_MIN   220
   #define TOUCH_Y_MAX   3840
   
/*********************************************************************
*       Configuration checking
**********************************************************************
*/
#ifndef   VXSIZE_PHYS
  #define VXSIZE_PHYS XSIZE_PHYS
#endif
#ifndef   VYSIZE_PHYS
  #define VYSIZE_PHYS YSIZE_PHYS
#endif
#ifndef   XSIZE_PHYS
  #error Physical X size of display is not defined!
#endif
#ifndef   YSIZE_PHYS
  #error Physical Y size of display is not defined!
#endif
#ifndef   GUICC_565
  #error Color conversion not defined!
#endif
#ifndef   GUIDRV_FLEXCOLOR
  #error No display driver defined!
#endif

/* #define FSMC_BASEADR_NORSRAM1         0x60000000
   #define FSMC_BASEADR_NORSRAM2         0x64000000
   #define FSMC_BASEADR_NORSRAM3         0x68000000
   #define FSMC_BASEADR_NORSRAM4         0x6C000000
   #define FSMC_BASEADR_NAND2            0x70000000
   #define FSMC_BASEADR_NAND3            0x80000000
   FSMC use NOR(BANK1) interface with A16 as RS
   ------------------------------------------------------*/
   #define LCD_REG       (*((volatile unsigned short *) 0x60000000)) /* RS = 0 */
   #define LCD_RAM       (*((volatile unsigned short *) 0x60020000)) /* RS = 1 */
   
  // #define LCD_SSD1963
/*---------------------------------------------------------
 function.....: LcdWriteReg
 description..: Sets display register
 input........: nil
 output.......: nil
----------------------------------------------------------*/ 
static void LcdWriteReg(uint16_t reg_adr){
  LCD_REG = reg_adr; 
}
/*---------------------------------------------------------
 function.....: LcdWriteData
 description..: Writes a value to a display register
 input........: nil
 output.......: nil
----------------------------------------------------------*/ 
static void LcdWriteData(uint16_t reg_val){
  LCD_RAM = reg_val;
}
/*---------------------------------------------------------
 function.....: LcdWriteDataMultiple
 description..: Writes multiple values to a display register.
 input........: nil
 output.......: nil
----------------------------------------------------------*/ 
static void LcdWriteDataMultiple(uint16_t * pData, int NumItems) {
  while (NumItems--) {
    LCD_RAM = *pData++;
  }
}
/*---------------------------------------------------------
 function.....: LcdReadDataMultiple
 description..: Reads multiple values from a display register.
 input........: nil
 output.......: nil
----------------------------------------------------------*/ 
static void LcdReadDataMultiple(uint16_t * pData, int NumItems) {
  while (NumItems--) {
    *pData++ = LCD_RAM;
  }
}

__inline uint16_t LcdReadReg(uint16_t LCD_Reg){
   LcdWriteReg(LCD_Reg);   /*Write 16-bit Index (then Read Reg) */
   return LCD_RAM;            /*Read 16-bit Reg */
}
/*---------------------------------------------------------
 function.....:delay
 description..:
 input........: nil
 output.......: nil
----------------------------------------------------------*/ 
static void delay(vu32 nCount){
  vu32 index = 0; 
  for(index = (100000 * nCount); index != 0; index--) {}
}
/*---------------------------------------------------------
 function.....: lcdReset
 description..:
 dependencies.:
----------------------------------------------------------*/ 
void lcdReset(void){
    GPIO_ResetBits(GPIOD, GPIO_Pin_12);//GPIO_ResetBits(RESET_PORT, RESET_Pin);
    os_dly_wait(100); 
    GPIO_SetBits(GPIOD, GPIO_Pin_12);//GPIO_SetBits(RESET_PORT, RESET_Pin);
}
/*---------------------------------------------------------
 function.....:
 description..:
 dependencies.:
----------------------------------------------------------*/ 
void _InitController(void){ 
   uint16_t DeviceCode;
   /* Configure the LCD Control pins */
   LCD_CtrlLinesConfig();
   /* Configure the FSMC Parallel interface */
   LCD_FSMCConfig();
   /* delay 50 ms */
   os_dly_wait(50);
   /*hardware reset*/
   GPIO_ResetBits(GPIOD, GPIO_Pin_12);//GPIO_ResetBits(RESET_PORT, RESET_Pin);
   os_dly_wait(100); 
   GPIO_SetBits(GPIOD, GPIO_Pin_12);//GPIO_SetBits(RESET_PORT, RESET_Pin);
   
   DeviceCode = 0x00;
   DeviceCode = LcdReadReg(0x0000);
   
 //  #ifdef LCD_SSD1963
 //     LCD_ssd1963_config();
 //  #else
    //DeviceCode = 0x8989;
      LCD_ssd1289_config();
 //  #endif
}
/*---------------------------------------------------------
 function.....:
 description..:
 dependencies.:
----------------------------------------------------------*/ 
void LCD_ssd1963_config(void){

   /*0x0001*/
   LcdWriteReg(SSD1963_SOFT_RESET);
   LcdWriteReg(SSD1963_SOFT_RESET);      
   LcdWriteReg(SSD1963_SOFT_RESET);
   os_dly_wait(10);
   
   /*PLL multiplier, set PLL clock to 120M*/
   LcdWriteReg(SSD1963_SET_PLL_MN);      /*0x00E2*/
   LcdWriteData(0x23);                   /*Divider N = 0x0036 for 6.5MHz, 0x0023 for 10MHz crystal*/
   LcdWriteData(0x02);                   /*Multiplier M = 2*/
   LcdWriteData(0x04);                   /*dummy value, can be anything*/ 

   LcdWriteReg(SSD1963_SET_PLL);         /*0x00E0*/
   LcdWriteData(0x01);                   /*Use PLL output as system clock*/
   os_dly_wait(10);                            /*this is allows the PLL to stabilize*/
   LcdWriteReg(SSD1963_SET_PLL);         /*0x00E0*/
   LcdWriteData(0x03);                   /*SSD1963 is switched to PLL output after PLL has stabilized.*/
   os_dly_wait(10);                            /*this is allows the PLL to stabilize*/

   LcdWriteReg(SSD1963_SOFT_RESET);      /*0x0001*/
   os_dly_wait(5);

   /*0xB0 SET TFT modes*/
   LcdWriteReg(SSD1963_SET_LCD_MODE);/*TFT FRC enable, 18-bit data */
   LcdWriteData(0x08);                //TFT FRC enable, 18-bit data 
   LcdWriteData(0x00);  //TFT mode
   LcdWriteData(0x03);  //SET horizontal size=800-1 HightByte
   LcdWriteData(0x1f);  //SET horizontal size=800-1 LowByte 
   LcdWriteData(0x01);  //SET vertical size=480-1 HightByte 
   LcdWriteData(0xdf);  //SET vertical size=480-1 LowByte 
   LcdWriteData(0x00);  //SET even/odd line RGB seq.=RGB

   /*pixel data interface (host) pg. 78*/
   LcdWriteReg(SSD1963_SET_PIXEL_DATA_INTERFACE);
   LcdWriteData(SSD1963_PDI_16BIT565); 
   //0x01     //SET pixel 12 bit
   //0x02     //SET pixel 16 bit (packed)
   //0x03     //SET pixel 16 bit 565
   //0x04     //SET pixel 18 bit
   //0x05     //SET pixel 24 bit
   //0x06     //SET pixel 9 bit

   /*Selects the gamma curve used by the display panel*/
//   LcdWriteReg(0x26);
 //  LcdWriteData(0x04);    /*1,2,4,8*/

   /*0x00E6 set pixel clock frequency
   * pll frequency	: 110MHz
   * target frequency : 33.3MHz
   * LCDC_FPR			: 317433 (0x04D7F9)
   */
   LcdWriteReg(SSD1963_SET_PIXCLK_FREQ);
   LcdWriteData(0x04);
   LcdWriteData(0xD7);
   LcdWriteData(0xF9);      

   /* set horizontal timing
   * P1(0x03): HT - horizontal period : tHP+tHW-1 = 975 (0x3CF)
   * P2(0xCF): HT - horizontal period : tHP+tHW-1 = 975 (0x3CF)
   * P3(0x00): HPS - hsync width + front pouch : tHW + tHFP = 88 (0x58)
   * P4(0x58): HPS - hsync width + front pouch : tHW + tHFP = 88 (0x58)
   * P5(0x2F): HPW - horizontal sync pulse width : tHW -1 = 47 (0x2F)
   * P6(0x00): LPS - horizontal sync pulse location : 0 (0x00)
   * P7(0x00): LPS - horizontal sync pulse location : 0 (0x00)
   * P8(0x00): horizontal sync pulse subpixel start position(LPSPP) : N/A
   */
   LcdWriteReg(SSD1963_SET_HORI_PERIOD);
   LcdWriteData(0x03);  /*0x00B4*/
   LcdWriteData(0xCF);
   LcdWriteData(0x00);
   LcdWriteData(0x58);
   LcdWriteData(0x2F);
   LcdWriteData(0x00);
   LcdWriteData(0x00);
   LcdWriteData(0x00);
   /* 
   * set vertical timing
   * P1(0x02): VT - vertical period : tVP-1 = 524 (0x20C)
   * P2(0x0C): VT - vertical period : tVP-1 = 524 (0x20C)
   * P3(0x00): VPS - vsync width + front poch : tVW + tVFP = 16 (0x10)
   * P4(0x10): VPS - vsync width + front poch : tVW + tVFP = 16 (0x10)
   * P5(0x02): VPW - vertical sync pulse width : tVW-1 = 2 (0x02)
   * P6(0x00): FPS - vertical sync pulse location : 0 (0x00)
   * P7(0x00): FPS - vertical sync pulse location : 0 (0x00)
   */
   LcdWriteReg(SSD1963_SET_VERT_PERIOD);
   LcdWriteData(0x02);  /*0x00B6*/
   LcdWriteData(0x0C);
   LcdWriteData(0x00);
   LcdWriteData(0x10);
   LcdWriteData(0x02);
   LcdWriteData(0x00);
   LcdWriteData(0x00);

   LcdWriteReg(SSD1963_SET_LCD_MODE);
   LcdWriteData(0x10);    //SET start column address=0 
   LcdWriteData(0x00); 
   LcdWriteData(0x03);    //SET end column address=800 
   LcdWriteData(0x1f); 
   LcdWriteData(0x01);    //SET end page address=480 
   LcdWriteData(0xdf); 
   LcdWriteData(0x00); 

   /* rotation, see p.18
   * flip vertical, flip horizontal
   */
   LcdWriteReg(0x36);
   LcdWriteData(0x01);

   /*liga o display e reseta a ram*/
   LcdWriteReg(0x29);
   LcdWriteReg(0x2C);
}
/*---------------------------------------------------------
 function.....: WriteReg
 description..:
 dependencies.: LCD_ssd1289_config
----------------------------------------------------------*/
void WriteReg(uint16_t r, uint16_t d){
   LcdWriteReg(r);
   LcdWriteData(d);
   os_dly_wait(50);
}
/*---------------------------------------------------------
 function.....:
 description..:
 dependencies.:
----------------------------------------------------------*/ 
void LCD_ssd1289_config(void){
   WriteReg(0x0000,0x0001);
   WriteReg(0x0003,0xA8A4);
   WriteReg(0x000C,0x0000);
   WriteReg(0x000D,0x080C);
   WriteReg(0x000E,0x2B00);
   WriteReg(0x001E,0x00B0);
   WriteReg(0x0001,0x2B3F);
   WriteReg(0x0002,0x0600);
   WriteReg(0x0010,0x0000);
   WriteReg(0x0011,0x6070);
   WriteReg(0x0005,0x0000);
   WriteReg(0x0006,0x0000);
   WriteReg(0x0016,0xEF1C);
   WriteReg(0x0017,0x0003);
   WriteReg(0x0007,0x0133);
   WriteReg(0x000B,0x0000);
   WriteReg(0x000F,0x0000);
   WriteReg(0x0041,0x0000);
   WriteReg(0x0042,0x0000);
   WriteReg(0x0048,0x0000);
   WriteReg(0x0049,0x013F);
   WriteReg(0x004A,0x0000);
   WriteReg(0x004B,0x0000);
   WriteReg(0x0044,0xEF00);
   WriteReg(0x0045,0x0000);
   WriteReg(0x0046,0x013F);
   WriteReg(0x0030,0x0707);
   WriteReg(0x0031,0x0204);
   WriteReg(0x0032,0x0204);
   WriteReg(0x0033,0x0502);
   WriteReg(0x0034,0x0507);
   WriteReg(0x0035,0x0204);
   WriteReg(0x0036,0x0204);
   WriteReg(0x0037,0x0502);
   WriteReg(0x003A,0x0302);
   WriteReg(0x003B,0x0302);
   WriteReg(0x0023,0x0000);
   WriteReg(0x0024,0x0000);
   WriteReg(0x0025,0x8000);
   WriteReg(0x004f,0);
   WriteReg(0x004e,0);
}
/*---------------------------------------------------------
 function.....: LCD_X_Config
 description..: Called during the initialization process in order to
                set up the display driver configuration.
 input........: nil
 output.......: nil
----------------------------------------------------------*/ 
void LCD_X_Config(void){
   GUI_DEVICE * pDevice;
   CONFIG_FLEXCOLOR Config = {0};
   GUI_PORT_API PortAPI = {0};

   // Set display driver and color conversion //GUIDRV_COMPACT_COLOR_16
   pDevice = GUI_DEVICE_CreateAndLink(GUIDRV_FLEXCOLOR, GUICC_M565, 0, 0);

   LCD_SetSizeEx (0, XSIZE_PHYS, YSIZE_PHYS);
   LCD_SetVSizeEx(0, XSIZE_PHYS, YSIZE_PHYS);

   // Orientation
   Config.Orientation = DISPLAY_ORIENTATION;
   GUIDRV_FlexColor_Config(pDevice, &Config);

   // Set controller and operation mode
   PortAPI.pfWrite16_A0  = LcdWriteReg;
   PortAPI.pfWrite16_A1  = LcdWriteData;
   PortAPI.pfWriteM16_A1 = LcdWriteDataMultiple;
   PortAPI.pfReadM16_A1  = LcdReadDataMultiple;
   /*GUIDRV_FLEXCOLOR_M16C0B16 - 16bpp, no cache, 16 bit bus*/
   //GUIDRV_FlexColor_SetFunc(pDevice, &PortAPI, GUIDRV_FLEXCOLOR_F66720, GUIDRV_FLEXCOLOR_M16C0B16);

   //ssd1289
   GUIDRV_FlexColor_SetFunc(pDevice, &PortAPI, GUIDRV_FLEXCOLOR_F66702, GUIDRV_FLEXCOLOR_M16C0B16);
   // Set orientation of touch screen
   //GUI_TOUCH_SetOrientation( GUI_MIRROR_X | GUI_MIRROR_Y );     GUI_MIRROR_X |
   //renato
   GUI_TOUCH_SetOrientation( GUI_SWAP_XY ); 
   // Calibrate touch screen
 //  GUI_TOUCH_SetOrientation((GUI_MIRROR_X * LCD_GetMirrorXEx(0)) |
 //             (GUI_MIRROR_Y * LCD_GetMirrorYEx(0)) |
 //             (GUI_SWAP_XY  * LCD_GetSwapXYEx (0)));
              
   GUI_TOUCH_Calibrate(GUI_COORD_X, 0, XSIZE_PHYS - 1, TOUCH_X_MIN, TOUCH_X_MAX);
   GUI_TOUCH_Calibrate(GUI_COORD_Y, 0, YSIZE_PHYS - 1, TOUCH_Y_MIN, TOUCH_Y_MAX);
}
/*---------------------------------------------------------
 function.....: LCD_X_DisplayDriver
 description..: This function is called by the display driver for several purposes.
                To support the according task the routine needs to be adapted to
                the display controller. Please note that the commands marked with
                'optional' are not cogently required and should only be adapted if 
                the display controller supports these features.
 input........: LayerIndex - Index of layer to be configured
                Cmd - Please refer to the details in the switch statement below
                pData - Pointer to a LCD_X_DATA structure
  output.......: nil
----------------------------------------------------------*/ 
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData){
   int r;
   switch (Cmd){
      case LCD_X_INITCONTROLLER: 
         _InitController();
         r = 0;
      break;
      case LCD_X_ON:
         // Required if the display controller should support switching on and off
         return 0;
      break;
      case LCD_X_OFF:
         // Required if the display controller should support switching on and off
         return 0;
      break;
      default:
         r = -1;
      break;
   }
   return r;
}
/*------------------------------------------------------------
     eof
--------------------------------------------------------------*/
