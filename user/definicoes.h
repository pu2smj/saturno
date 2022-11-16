/*-----------------------------------------------------------------
   Copyright (c)
   file.........: definicoes.c
   description..: definitions of system
   user.........: 
-------------------------------------------------------------------*/ 

#ifndef _DEFINICOES_H
   #define _DEFINICOES_H

   #include "WM.h"
   #include "stm32f10x.h"
   /*----------------------------------------* 
    general defines
   ------------------------------------------*/ 
   #define OFF                       0x00
   #define ON                        0x01
   #define SVERSION                  "01.00"
   #define SMACHINE                  0x0C
   /*-----------------------------------------
   
   ------------------------------------------*/ 
   #define Atmosphere(x)             GPIOE->ODR = (GPIOA->ODR & ~GPIO_Pin_4) | (x ? GPIO_Pin_4 : 0);
   #define AirPump(x)                GPIOA->ODR = (GPIOA->ODR & ~GPIO_Pin_5) | (x ? GPIO_Pin_5 : 0);  
   /*-----------------------------------------
   
   ------------------------------------------*/ 
   #define MSG_KEYB_CANCEL           (WM_USER + 100)
   #define MSG_KEYB_OK               (WM_USER +  99)
   #define MSG_KEYB_SET_DATA         (WM_USER +  98)
   #define WM_CANCEL_PROCESS         (WM_USER +  97)  
   #define WM_CLOSE_PROCESS          (WM_USER +  96)
   #define WM_CLOSE_MAIN_WIN         (WM_USER +  95)
   /*-----------------------------------------
   
   ------------------------------------------*/   
   #define SetBit(REG,BIT)           ((REG) |= (1<<(BIT)))
   #define ResetBit(REG,BIT)         ((REG) &= ((1<<BIT)))
   #define ValBit(REG,BIT)           ((REG) & (1<<(BIT)) )
   #define BitIsClear(REG,BIT)       (0 == ValBit(REG,BIT))
   #define BitIsSet(REG,BIT)         (!BitIsClear(REG,BIT))
   /*-----------------------------------------
   
   ------------------------------------------*/  
   #define ADR_MIN_PRESSURE           0
   #define ADR_MAX_PRESSURE           2
   #define ADR_SET_POINT              4
   #define ADR_HISTERESE              6
   /*-----------------------------------------* 

   *------------------------------------------*/
   typedef enum{
      FALSE = 0,
      TRUE = !FALSE
   }bool;
   
   typedef enum{
      st_nil = 0x00,
      st_idle,
      st_run,
      st_pause,
      st_cancel
   }TStatus;   
   
   typedef enum{
      t_minimum = 0x0A,
      t_maximo,
      t_setpoint,
	   t_histerese,
      t_nMin,
      t_nMax
   }TNormalize;
   
   typedef enum{
      e_char = 0,
      e_decimal,
      e_float,
      e_hexa,
      e_binary
   }TTypeEdit;
   
   typedef struct xy{
      uint16_t x;
      uint16_t y;
   }Txy;

   typedef struct taskTime{
      uint8_t  sec;
      uint8_t  min;
      uint8_t  hour;
      uint16_t WorkTime;
      uint16_t WorkTask;
      char     stamp[9];       
   }TClock;

   typedef struct{
      uint8_t minimum;
      uint8_t maximo;
      uint8_t setpoint;
	   uint8_t histerese;
      uint8_t nMin;
      uint8_t nMax;
   }TPressure;

   typedef struct seed{
      WM_HWIN   win;
      TStatus   status;
      TClock    clock;
      TPressure pres;
   }TMachine;
   
#endif
/*------------------------------------------------------------
    EOF
--------------------------------------------------------------*/
