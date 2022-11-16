/*--------------------------------------------------------
  * @file........ board.c
  * @author...... renato
  * @description. 
  --------------------------------------------------------
*/

/* Includes --------------------------------------------*/
   #include "Board.h"

/*---------------------------------------------------------
 function.....: GPIO_Config
 description..: configure GPIO for external rele module
 dependencie..: BoardInit
----------------------------------------------------------*/ 
void GPIO_Config(void){
   GPIO_InitTypeDef GPIO_InitStructure;

   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 |  //PA.4 (Despressurizacao)
                                 GPIO_Pin_5;   //PA.5 (Compressor) 
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                     
   GPIO_Init(GPIOA, &GPIO_InitStructure);
   
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;   //pressure sensor
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AIN;
   GPIO_Init(GPIOC, &GPIO_InitStructure);
   
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;  //Buzzer
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(GPIOD, &GPIO_InitStructure);
   
   GPIOA->ODR = 0x0000;
   GPIOB->ODR = 0x0000;
   GPIOC->ODR = 0x0000;
   GPIOD->ODR = 0x0000;
}
/*---------------------------------------------------------
 function.....: TIM3_Config
 description..: Configure TIM3
 dependence...: 
----------------------------------------------------------*/
void TIM3_Config(void){
   TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
   NVIC_InitTypeDef NVIC_InitStructure;
   
   NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
   
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
      
   TIM_TimeBaseStructure.TIM_Period = 10000-1;
   TIM_TimeBaseStructure.TIM_Prescaler = (SystemCoreClock / 1000000) - 1;
   TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
   TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
   TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
   TIM_Cmd(TIM3, DISABLE);
}
/*---------------------------------------------------------
 function.....: ADC_PressureConfig
 description..: Configure the ADC123_IN10
 dependence...: 
----------------------------------------------------------*/
void ADC_PressureConfig(void){
   ADC_InitTypeDef  ADC_InitStructure; 
   
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);   

   ADC_DeInit(ADC1);
   ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
   ADC_InitStructure.ADC_ScanConvMode = DISABLE;
   ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
   ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
   ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
   ADC_InitStructure.ADC_NbrOfChannel = 1;
   //ADC_InitStructure.ADC_Resolution = 10;`
   ADC_Init(ADC1, &ADC_InitStructure);

   ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_28Cycles5);  
 
   ADC_Cmd(ADC1, ENABLE);
  
   ADC_ResetCalibration(ADC1);
   while(ADC_GetResetCalibrationStatus(ADC1));
   ADC_StartCalibration(ADC1);
   while(ADC_GetCalibrationStatus(ADC1));
   
   ADC_Cmd(ADC1, DISABLE);
}
/*---------------------------------------------------------
 function.....: BoardInit
 description..: 
 dependence...: 
----------------------------------------------------------*/
void BoardInit(void){
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                          RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
                          RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO, ENABLE);

   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);

   GPIO_Config();
   I2C_Configuration();
   _InitController();
   TouchPanel_Init();
   TIM3_Config();
   ADC_PressureConfig();
}
/*------------------------------------------------------------
    EOF
--------------------------------------------------------------*/
