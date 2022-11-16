 /*-----------------------------------------------------------------
   Copyright (c)
   file.........: 
   description..: 
   user.........: 
   -----------------------------------------------------------------*/
  
/*
//void lcdReset(void);
//void lcdInit(void);
//void lcdWriteData(uint16_t data);
//void lcdWriteReg(uint16_t data);
//uint16_t lcdReadData(void);
*/


   /* Includes ----------------------------------------------*/
   #include "LCD_driver.h"
   #include "stm32f10x.h"

   #define LCD_HX8347D        0x0047
   #define LCD_SSD1289        0x8989

   /*LCD_Private_Macros*/
   #define ABS(X)  ((X) > 0 ? (X) : -(X))    

/*---------------------------------------------------------
 function.....:
 description..: Configures LCD Control lines (FSMC Pins)
----------------------------------------------------------*/ 
void LCD_CtrlLinesConfig(void){
   GPIO_InitTypeDef GPIO_InitStructure;

   /* Enable GPIOs clock */
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO, ENABLE);
   
   /* Set PD.00(D2), PD.01(D3), PD.04(NOE), PD.05(NWE), PD.08(D13), PD.09(D14), PD.7 (NE1),
    PD.10(D15), PD.11(A16), PD.14(D0), PD.15(D1) as alternate function push pull */
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4  | GPIO_Pin_5  | GPIO_Pin_7  |
                                 GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_14 | 
                                 GPIO_Pin_15;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
   GPIO_Init(GPIOD, &GPIO_InitStructure);
   
   /* Set PE.07(D4), PE.08(D5), PE.09(D6), PE.10(D7), PE.11(D8), PE.12(D9), PE.13(D10),
    PE.14(D11), PE.15(D12) as alternate function push pull */
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | 
                                 GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
                                 GPIO_Pin_15;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
   GPIO_Init(GPIOE, &GPIO_InitStructure);
   
   /* Backlight(GPIO output) - port B.1 */
 //  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;   /* PB.1 - BACKLIGHT */
 //  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 //  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 //  GPIO_Init(GPIOB, &GPIO_InitStructure); 

/*placa renato*****************************************/
   /*D.13(A24) 74HC139 EN LCD*/ 
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(GPIOD, &GPIO_InitStructure);
   
   /*LCD reset*/
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;   /* PD.12 reset*/
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(GPIOD, &GPIO_InitStructure);

   GPIO_SetBits(GPIOD, GPIO_Pin_12);                /*lcd reset*/
}
/*---------------------------------------------------------
 function.....:
 description..: Configures the Parallel interface (FSMC)
----------------------------------------------------------*/ 
void LCD_FSMCConfig(void){
   FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
   FSMC_NORSRAMTimingInitTypeDef FSMC_NORSRAMTimingInitStructure;

    /* Enable FSMC clock */
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE); 

   FSMC_NORSRAMTimingInitStructure.FSMC_AddressSetupTime = 5;
   FSMC_NORSRAMTimingInitStructure.FSMC_AddressHoldTime  = 0;
   FSMC_NORSRAMTimingInitStructure.FSMC_DataSetupTime    = 10;
   FSMC_NORSRAMTimingInitStructure.FSMC_BusTurnAroundDuration = 0;
   FSMC_NORSRAMTimingInitStructure.FSMC_CLKDivision      = 0;
   FSMC_NORSRAMTimingInitStructure.FSMC_DataLatency      = 0;
   FSMC_NORSRAMTimingInitStructure.FSMC_AccessMode       = FSMC_AccessMode_A; 

   FSMC_NORSRAMInitStructure.FSMC_Bank            = FSMC_Bank1_NORSRAM1;
   FSMC_NORSRAMInitStructure.FSMC_DataAddressMux  = FSMC_DataAddressMux_Disable;
   FSMC_NORSRAMInitStructure.FSMC_MemoryType      = FSMC_MemoryType_SRAM;
   FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
   FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
   FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
   FSMC_NORSRAMInitStructure.FSMC_WrapMode        = FSMC_WrapMode_Disable;
   FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive= FSMC_WaitSignalActive_BeforeWaitState;
   FSMC_NORSRAMInitStructure.FSMC_WriteOperation  = FSMC_WriteOperation_Enable;
   FSMC_NORSRAMInitStructure.FSMC_WaitSignal      = FSMC_WaitSignal_Disable;
   FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait= FSMC_AsynchronousWait_Disable;
   FSMC_NORSRAMInitStructure.FSMC_ExtendedMode    = FSMC_ExtendedMode_Disable;
   FSMC_NORSRAMInitStructure.FSMC_WriteBurst      = FSMC_WriteBurst_Disable;
   
   FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &FSMC_NORSRAMTimingInitStructure;
   FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &FSMC_NORSRAMTimingInitStructure;

   FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 
   FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);  
}

/*------------------------------------------------------------

--------------------------------------------------------------*/
