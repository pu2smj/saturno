/*--------------------------------------------------------
  * @file........ level0.h
  * @author...... renato
  * @description. 
  --------------------------------------------------------
*/

#ifndef  _LEVEL0_H
   #define  _LEVEL0_H
   

   #include "stm32f10x.h"
   #include "24C02.h"
   #include "time.h"
   #include "GUI.h"
   #include "definicoes.h"
   
   
   #define ADC_BUFF_SIZE            0x10
   #define PRESSURE_MIN             0x34     //70 mmhg
   #define PRESSURE_MAX             0x71     //150 mmhg
   #define PRESSURE_SET             100
   #define PRESSURE_HIST            10
   #define MRATE                    1.33322 
   #define PTIMEOUT                 0x12C
   
   struct TPS{
      uint16_t pressure;
      uint16_t nBits;
      uint8_t  index;
      uint16_t tick;
      uint16_t buffer[ADC_BUFF_SIZE];
   };

   /*-----------------------------------------
   functions
   ------------------------------------------*/
   void Tim3_IRQ_Handler(void);
   void Win_XY(WM_HWIN hWin, Txy *t);
   void RTCtick(void);
   void RestoreMMHG(TPressure *t);
   void NormalizeMMHG(TPressure *t, TNormalize a);
   void beep(void);
   
#endif

//EOF





