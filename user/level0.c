/*--------------------------------------------------------
  * @file........ level0
  * @author...... renato
  * @description. common routines
  --------------------------------------------------------
*/ 
  
   #include <rtl.h> 
   #include "level0.h"

   /* task id ----------------------------------------*/
   //OS_TID tid_process;
   
   /* Private variables ------------------------------*/
   struct TPS *tps;
      
   /* Extern variables -------------------------------*/
   extern TMachine *pMac;
   
   /* prototype --------------------------------------*/
   void ReleasePres(void);
   void SetTim3(uint8_t enabled);
   void RestoreMBAR(TMachine *t);
      
/*---------------------------------------------------------
 function.....: 
 description..: 
 dependencie..: 
----------------------------------------------------------*/ 
void startproc(void){
   pMac->clock.WorkTask = 0;
   pMac->clock.WorkTime = 0;
   tps->index = 0;
   tps->nBits = 0;
   tps->pressure = 0;
   tps->tick = 0;
   //
   RestoreMBAR(pMac);
   SetTim3(ENABLE);
   GPIOC->BSRR = GPIO_Pin_5;
   pMac->status = st_run;
}
/*---------------------------------------------------------
 function.....: 
 description..: 
 dependencie..: 
----------------------------------------------------------*/ 
void resumeproc(void){
   AirPump(OFF);
   pMac->status = st_pause;
}
/*---------------------------------------------------------
 function.....: 
 description..: 
 dependencie..: 
----------------------------------------------------------*/ 
void endproc(void){
   SetTim3(DISABLE);
   AirPump(OFF);
   pMac->status = st_idle;
   Atmosphere(ON);
   os_dly_wait(400);
   Atmosphere(OFF); 
}
/*---------------------------------------------------------
 function.....: 
 description..: 
 dependencie..: 
----------------------------------------------------------*/
void mppt(void){
   if( pMac->pres.setpoint > 0 ){
      if( tps->pressure <= pMac->pres.nMin ){
         AirPump(ON);
      };
      if( tps->pressure >= pMac->pres.nMax ){
         AirPump(OFF);
      };
   }else{   
      if( tps->pressure <= pMac->pres.minimum ){
         AirPump(ON);
      };
      if( tps->pressure >= pMac->pres.maximo ){
         AirPump(OFF);
      };
   };
   
   tps->tick++;
   if(tps->tick % 10){
      RTCtick();
   } 
}   
/*---------------------------------------------------------
 function.....: Set_Tim3
 description..: 
 dependence...: 
----------------------------------------------------------*/ 
void SetTim3(uint8_t enabled){
   if(enabled != 0){
      TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
      TIM_Cmd(TIM3, ENABLE);
      ADC_Cmd(ADC1, ENABLE);
   }else{
      TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
      TIM_Cmd(TIM3, DISABLE);
      ADC_Cmd(ADC1, DISABLE);
   };
}
/*---------------------------------------------------------
 function.....: Tim3_IRQ_Handler
 description..: 
 dependence...: 
----------------------------------------------------------*/ 
void Tim3_IRQ_Handler(void){
   tps->index++;                                         /*next step*/
   
   ADC_SoftwareStartConvCmd(ADC1, ENABLE);
   while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
   tps->buffer[ tps->index ] = ADC_GetConversionValue(ADC1);

   if( tps->index >= 15 ){
      tps->nBits = 0;
      for(tps->index = 0; tps->index <= 15; tps->index++ ){
         tps->nBits += tps->buffer[ tps->index ];
      };
      tps->nBits = tps->nBits / 15;
      if( tps->nBits > 0 ){
         tps->pressure = (tps->nBits *0.1274)-0.7057;
      }else{
         tps->pressure = 0;
      };
      tps->index = 0;
   };
}
/*---------------------------------------------------------
 function.....: 
 description..: 
 dependencies.: 
----------------------------------------------------------*/
void RTCtick(void){
   if(pMac->status == st_run){
      pMac->clock.WorkTime++;
      pMac->clock.hour = (pMac->clock.WorkTime/3600); 
      pMac->clock.min  = (pMac->clock.WorkTime%3600)/60;
      pMac->clock.sec  = (pMac->clock.WorkTime%60);
      sprintf(pMac->clock.stamp, "%02u:%02u:%02u", pMac->clock.hour, pMac->clock.min, pMac->clock.sec);
   };
}
/*---------------------------------------------------------
 function.....: 
 description..: restore in mBar
 dependencies.: 
----------------------------------------------------------*/
void RestoreMBAR(TMachine *t){

   t->pres.minimum   = I2C_ReadInt(ADR_MIN_PRESSURE) * MRATE;
   t->pres.maximo    = I2C_ReadInt(ADR_MAX_PRESSURE) * MRATE;
   t->pres.setpoint  = I2C_ReadInt(ADR_SET_POINT) * MRATE;
   t->pres.histerese = (ADR_HISTERESE) * MRATE;
   
   if( t->pres.setpoint > 0 ){
     t->pres.nMin = t->pres.setpoint - ((t->pres.setpoint * t->pres.histerese) / 100 );
     t->pres.nMax = t->pres.setpoint + ((t->pres.setpoint * t->pres.histerese) / 100 );
   } 
}
/*---------------------------------------------------------
 function.....: 
 description..: restore in mmhg
 dependencies.: 
----------------------------------------------------------*/
void RestoreMMHG(TPressure *t){
   t->minimum   = I2C_ReadInt(ADR_MIN_PRESSURE);
   t->maximo    = I2C_ReadInt(ADR_MAX_PRESSURE);
   t->setpoint  = I2C_ReadInt(ADR_SET_POINT);
   t->histerese = (ADR_HISTERESE);

   if( t->setpoint > 0 ){
     t->nMin = t->setpoint - ((t->setpoint * t->histerese) / 100 );
     t->nMax = t->setpoint + ((t->setpoint * t->histerese) / 100 );
   } 
}
/*---------------------------------------------------------
 function.....: 
 description..: restore in mmhg
 dependencies.: 
----------------------------------------------------------*/
void NormalizeMMHG(TPressure *t, TNormalize a){
   if( a == t_minimum ){
      if( (t->minimum < PRESSURE_MIN) | (t->minimum > PRESSURE_MAX) ){
         t->minimum = PRESSURE_MIN;
         I2C_WriteInt( t->minimum, ADR_MIN_PRESSURE);
      }; 
   }
   if( a == t_maximo ){
      if( (t->maximo < PRESSURE_MIN) | (t->maximo > PRESSURE_MAX) ){
         t->maximo = PRESSURE_MAX;
         I2C_WriteInt( t->maximo, ADR_MAX_PRESSURE); 
     }; 
   }   
   if( a == t_setpoint){
      if( (t->setpoint < PRESSURE_MIN) | (t->maximo > PRESSURE_MAX) ){
         t->setpoint = PRESSURE_SET;
         t->histerese = PRESSURE_HIST;
         I2C_WriteInt(t->setpoint, ADR_SET_POINT);
         I2C_WriteInt(t->histerese, ADR_HISTERESE);
      };
   }
   if( a == t_histerese){
      if( (t->histerese < 5) | (t->histerese > 10) ){
         t->histerese = PRESSURE_HIST;
         I2C_WriteInt(t->histerese, ADR_HISTERESE); 
      }   
   }   
}   
   
/*---------------------------------------------------------
 function.....: 
 description..: 
 input........: 
----------------------------------------------------------*/
void Win_XY(WM_HWIN hWin, Txy *t){
   uint16_t a, b;
   a = 320;
   b = WM_GetWindowSizeX(hWin);
   t->x = (a-b) / 2;

   a = 240;
   b = WM_GetWindowSizeY(hWin);
   t->y = (a-b) / 2;
}
/*---------------------------------------------------------
 function.....: beep
 description..: 
 dependence...: 
----------------------------------------------------------*/
void beep(void){
   GPIOD->BSRR = GPIO_Pin_6;
   os_dly_wait(80);
   GPIOD->BRR  = GPIO_Pin_6;
   os_dly_wait(30);
}
/*--------------------------------------------------------
  EOF
----------------------------------------------------------*/

