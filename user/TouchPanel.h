/*
  --------------------------------------------------------------
   Arquivo......: TouchPanel.h
   descrição....: rotinas para utilização do TouchScreen com ADS7846
   usuário......: 
  --------------------------------------------------------------
  */

#ifndef _TOUCHPANEL_H_
   #define _TOUCHPANEL_H_
   
   #include "stm32f10x.h"

   /* Private typedef ---------------------------------------*/


   /* Private define ----------------------------------------*/
   #define TP_MAX_X     320
   #define X_MIN        12
   #define X_MAX        386

   #define TP_MAX_Y     240
   #define Y_MIN        11
   #define Y_MAX        389

   #define   CHX         0x90
   #define   CHY         0xd0

   #define Set_CS       GPIO_SetBits(GPIOB,GPIO_Pin_12)
   #define Reset_CS     GPIO_ResetBits(GPIOB,GPIO_Pin_12)
   #define TP_INT_IN    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)

   /* Private function prototypes ---------------------------*/   
   void TouchPanel_Init(void);   
   int TouchGetX(void);
   int TouchGetY(void);

#endif

/*************************************************************
      END FILE
**************************************************************/


