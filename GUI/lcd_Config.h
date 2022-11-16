/*-----------------------------------------------------------------
   Copyright (c)
   file.........: 
   description..: 
   user.........: 
   -----------------------------------------------------------------*/

#ifndef _LCD_CONFIG_H
#define _LCD_CONFIG_H

/* Display Driver to use with Graphic LCD Interface */

#define LCD_USE_COMPACT_COLOR_16

static void LcdWriteReg(uint16_t reg_adr);
static void LcdWriteData(uint16_t reg_val);
static void LcdWriteDataMultiple(uint16_t * pData, int NumItems);
static void LcdReadDataMultiple(uint16_t * pData, int NumItems) ;
static void delay(vu32 nCount);
void lcdReset(void);
void _InitController(void); 
void LCD_ssd1963_config(void);
void LCD_ssd1289_config(void);
void LCD_X_Config(void);
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData);

#endif /* LCDCONF_H */

/*************************** End of file ****************************/
