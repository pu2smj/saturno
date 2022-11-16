/**
  ******************************************************************************
  * @file    stm3210e_eval_lcd.h
  * @author  MCD Application Team
  * @version V5.1.0
  * @date    18-January-2013
  * @brief   This file contains all the functions prototypes for the stm3210e_eval_lcd
  *          firmware driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _lcd_driver_H
#define _lcd_driver_H

   #ifdef __cplusplus
    extern "C" {
   #endif 

   /* Includes ------------------------------------------------------------------*/
   #include "stm32f10x.h"
    
   /*LCD_Exported_Types*/
   //typedef struct{
   //   uint16_t X;
   //   uint16_t Y;
   //}Point, * pPoint;   

   #define RESET_PORT          GPIOD
   #define RESET_Pin           GPIO_Pin_12

       
   /**
   * @brief Uncomment the line below if you want to use user defined Delay function
   *        (for precise timing), otherwise default _delay_ function defined within
   *         this driver is used (less precise timing).  
   */
   /* #define USE_Delay */

//#ifdef USE_Delay
   //  #define _delay_     Delay  /* !< User can provide more timing precise _delay_ function
   //                                   (with 10ms time base), using SysTick for example */
   //#else
   //   #define _delay_     delay      /* !< Default _delay_ function with less precise timing */
   //#endif
 
   /*LCD Registers*/ 
   #define SSD1963_NOP                       0x0000
   #define SSD1963_SOFT_RESET                0x0001
   #define SSD1963_GET_POWER_MODE            0x000A
   #define SSD1963_GET_ADDRESS_MODE          0x000B
   #define SSD1963_GET_DISPLAY_MODE          0x000D
   #define SSD1963_GET_TEAR_EFFECT_STATUS    0x000E
   #define SSD1963_ENTER_SLEEP_MODE          0x0010
   #define SSD1963_EXIT_SLEEP_MODE           0x0011
   #define SSD1963_ENTER_PARTIAL_MODE        0x0012
   #define SSD1963_ENTER_NORMAL_MODE         0x0013
   #define SSD1963_EXIT_INVERT_MODE          0x0020
   #define SSD1963_ENTER_INVERT_MODE         0x0021
   #define SSD1963_SET_GAMMA_CURVE           0x0026
   #define SSD1963_SET_DISPLAY_OFF           0x0028
   #define SSD1963_SET_DISPLAY_ON            0x0029
   #define SSD1963_SET_COLUMN_ADDRESS        0x002A
   #define SSD1963_SET_PAGE_ADDRESS          0x002B
   #define SSD1963_WRITE_MEMORY_START        0x002C
   #define SSD1963_READ_MEMORY_START         0x002E
   #define SSD1963_SET_PARTIAL_AREA          0x0030
   #define SSD1963_SET_SCROLL_AREA           0x0033
   #define SSD1963_SET_TEAR_OFF              0x0034
   #define SSD1963_SET_TEAR_ON               0x0035
   #define SSD1963_SET_ADDRESS_MODE          0x0036
   #define SSD1963_SET_SCROLL_START          0x0037
   #define SSD1963_EXIT_IDLE_MODE            0x0038
   #define SSD1963_ENTER_IDLE_MODE           0x0039
   #define SSD1963_SET_PIXEL_FORMAT          0x003A
   #define SSD1963_WRITE_MEMORY_CONTINUE     0x003C
   #define SSD1963_READ_MEMORY_CONTINUE      0x003E
   #define SSD1963_SET_TEAR_SCANLINE         0x0044
   #define SSD1963_GET_SCANLINE              0x0045
   #define SSD1963_READ_DDB                  0x00A1
   #define SSD1963_SET_LCD_MODE              0x00B0
   #define SSD1963_GET_LCD_MODE              0x00B1
   #define SSD1963_SET_HORI_PERIOD           0x00B4
   #define SSD1963_GET_HORI_PERIOD           0x00B5
   #define SSD1963_SET_VERT_PERIOD           0x00B6
   #define SSD1963_GET_VERT_PERIOD           0x00B7
   #define SSD1963_SET_GPIO_CONF             0x00B8
   #define SSD1963_GET_GPIO_CONF             0x00B9
   #define SSD1963_SET_GPIO_VALUE            0x00BA
   #define SSD1963_GET_GPIO_STATUS           0x00BB
   #define SSD1963_SET_POST_PROC             0x00BC
   #define SSD1963_GET_POST_PROC             0x00BD
   #define SSD1963_SET_PWM_CONF              0x00BE
   #define SSD1963_GET_PWM_CONF              0x00BF
   #define SSD1963_GET_LCD_GEN0              0x00C0
   #define SSD1963_SET_LCD_GEN0              0x00C1
   #define SSD1963_GET_LCD_GEN1              0x00C2
   #define SSD1963_SET_LCD_GEN1              0x00C3
   #define SSD1963_GET_LCD_GEN2              0x00C4
   #define SSD1963_SET_LCD_GEN2              0x00C5
   #define SSD1963_GET_LCD_GEN3              0x00C6
   #define SSD1963_SET_LCD_GEN3              0x00C7
   #define SSD1963_SET_GPIO0_ROP             0x00C8
   #define SSD1963_GET_GPIO0_ROP             0x00C9
   #define SSD1963_SET_GPIO1_ROP             0x00CA
   #define SSD1963_GET_GPIO1_ROP             0x00CB
   #define SSD1963_SET_GPIO2_ROP             0x00CC
   #define SSD1963_GET_GPIO2_ROP             0x00CD
   #define SSD1963_SET_GPIO3_ROP             0x00CE
   #define SSD1963_GET_GPIO3_ROP             0x00CF
   #define SSD1963_SET_DBC_CONF              0x00D0
   #define SSD1963_GET_DBC_CONF              0x00D1
   #define SSD1963_SET_DBC_TH                0x00D4
   #define SSD1963_GET_DBC_TH                0x00D5
   #define SSD1963_SET_PLL                   0x00E0
   #define SSD1963_SET_PLL_MN                0x00E2
   #define SSD1963_GET_PLL_MN                0x00E3
   #define SSD1963_GET_PLL_STATUS            0x00E4
   #define SSD1963_SET_DEEP_SLEEP            0x00E5
   #define SSD1963_SET_PIXCLK_FREQ           0x00E6
   #define SSD1963_GET_PIXCLK_FREQ           0x00E7
   #define SSD1963_SET_PIXEL_DATA_INTERFACE  0x00F0
      #define SSD1963_PDI_8BIT          0
      #define SSD1963_PDI_12BIT         1
      #define SSD1963_PDI_16BIT         2
      #define SSD1963_PDI_16BIT565      3
      #define SSD1963_PDI_18BIT         4
      #define SSD1963_PDI_24BIT         5
      #define SSD1963_PDI_9BIT          6
   #define SSD1963_GET_PIXEL_DATA_INTERFACE 0x00F1

   /** 
     * @brief  LCD color  
     */ 
   #define LCD_COLOR_WHITE          0xFFFF
   #define LCD_COLOR_BLACK          0x0000
   #define LCD_COLOR_GREY           0xF7DE
   #define LCD_COLOR_BLUE           0x001F
   #define LCD_COLOR_BLUE2          0x051F
   #define LCD_COLOR_RED            0xF800
   #define LCD_COLOR_MAGENTA        0xF81F
   #define LCD_COLOR_GREEN          0x07E0
   #define LCD_COLOR_CYAN           0x7FFF
   #define LCD_COLOR_YELLOW         0xFFE0


   /** 
     * @brief  LCD Direction  
     */ 
   #define LCD_DIR_HORIZONTAL       0x0000
   #define LCD_DIR_VERTICAL         0x0001

   /** 
     * @brief  LCD Size (Width and Height)  
     */ 
   #define LCD_PIXEL_WIDTH          0x0140
   #define LCD_PIXEL_HEIGHT         0x00F0

   #define ASSEMBLE_RGB(R, G, B)    ((((R)& 0xF8) << 8) | (((G) & 0xFC) << 3) | (((B) & 0xF8) >> 3))  


   void LCD_Init_Controler(void);
   
  // static void LcdWriteReg(uint16_t Data);
  // static void LcdWriteData(uint16_t Data);
  // static void LcdWriteDataMultiple(uint16_t * pData, int NumItems);
  // static void LcdReadDataMultiple(uint16_t * pData, int NumItems);

   void LCD_CtrlLinesConfig(void);
   void LCD_FSMCConfig(void);


   #ifdef __cplusplus
   }
   #endif

#endif /* __STM3210E_EVAL_LCD_H */

  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
