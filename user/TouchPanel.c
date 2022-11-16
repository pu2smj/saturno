/*--------------------------------------------------------
  * @file........ TouchPanel.c
  * @author...... renato
  * @description. TouchScreen com ADS7846
  --------------------------------------------------------
*/

   /* Includes ----------------------------------------------*/
   #include "TouchPanel.h"
   #include "stm32f10x.h"
   #include "GUI.h"      /*to calibrate touch*/

   /* Private define -----------------------------------------*/
   #define THRESHOLD 2
   
 
void SpiDelay(void){
   uint8_t nCount = 15;
   for(; nCount != 0; nCount--);  
} 
/*----------------------------------------------------------
 Function Name  : ADS7843_SPI_Init
 Description    : ADS7843 SPI
 Input          : None
 Output         : None
----------------------------------------------------------*/
static void ADS7843_SPI_Init(void){ 
   SPI_InitTypeDef  SPI_InitStructure;
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
   /* DISABLE SPI2 */ 
   SPI_Cmd(SPI2, DISABLE); 
   /* SPI2 Config */ 
   SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; 
   SPI_InitStructure.SPI_Mode      = SPI_Mode_Master; 
   SPI_InitStructure.SPI_DataSize  = SPI_DataSize_8b; 
   SPI_InitStructure.SPI_CPOL      = SPI_CPOL_Low; 
   SPI_InitStructure.SPI_CPHA      = SPI_CPHA_1Edge; 
   SPI_InitStructure.SPI_NSS       = SPI_NSS_Soft; 
   SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64; 
   SPI_InitStructure.SPI_FirstBit  = SPI_FirstBit_MSB; 
   SPI_InitStructure.SPI_CRCPolynomial = 7; 
   SPI_Init(SPI2, &SPI_InitStructure); 
   SPI_Cmd(SPI2, ENABLE); /* Enable SPI2 */ 
} 
/*----------------------------------------------------------
 Function Name  : TP_Init
 Description    : 
 Input          : None
 Output         : None
----------------------------------------------------------*/
void TouchPanel_Init(void){ 
   GPIO_InitTypeDef GPIO_InitStructure;
   RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
   /* Configure SPI2 pins: SCK, MISO and MOSI */ 
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13  | GPIO_Pin_14 | GPIO_Pin_15; 
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOB, &GPIO_InitStructure); 
   /* TP_CS */
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
   /* TP_IRQ Configure PB0 pin in input mode */
   GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
 
   Set_CS; 
   ADS7843_SPI_Init(); 
} 
/*----------------------------------------------------------
 Function Name  : WR_CMD
 Description    : 
 Input          : - cmd:
 Output         : None
----------------------------------------------------------*/
static void WR_CMD (uint8_t cmd){ 
   while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET); /* Wait for SPI2 Tx buffer empty */
   SPI_I2S_SendData(SPI2,cmd);                                     /* Send SPI2 data */
   while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);/* Wait for SPI2 data reception */ 
   SPI_I2S_ReceiveData(SPI2);                                      /* Read SPI2 received data */ 
}     
/*----------------------------------------------------------
 Function Name  : RD_AD
 Description    : 
 Input          : None
 Output         : None
----------------------------------------------------------*/
static int RD_AD(void){ 
   unsigned short buf,temp; 
    
   while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET); /* Wait for SPI2 Tx buffer empty */
   SPI_I2S_SendData(SPI2,0x0000);                                  /* Send SPI2 data */
   while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);/* Wait for SPI2 data reception */ 
   temp=SPI_I2S_ReceiveData(SPI2);                                 /* Read SPI2 received data */ 
   buf=temp<<8; 
   SpiDelay(); 
   while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET); 
   SPI_I2S_SendData(SPI2,0x0000);                                  /* Send SPI2 data */ 
   while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);/* Wait for SPI2 data reception */
   temp=SPI_I2S_ReceiveData(SPI2);                                 /* Read SPI2 received data */ 
   buf |= temp; 
   buf>>=3; 
   buf&=0xfff; 
   return buf; 
}    
/*----------------------------------------------------------
 Function Name  : Read_X
 Description    : 
 Input          : None
 Output         : None
----------------------------------------------------------*/
int Read_X(void){  
   int i; 
   Reset_CS; 
   SpiDelay(); 
   WR_CMD(CHY); 
   SpiDelay(); 
   i=RD_AD(); 
   Set_CS; 
   return i;    
}               
/*----------------------------------------------------------
 Function Name  : Read_Y
 Description    : 
 Input          : None
 Output         : None
----------------------------------------------------------*/
int Read_Y(void){  
   int i; 
   Reset_CS; 
   SpiDelay(); 
   WR_CMD(CHX); 
   SpiDelay(); 
   i=RD_AD(); 
   Set_CS; 
   return i;     
}               
/*----------------------------------------------------------
 Function Name  :
 Description    :
 Input          : None
 Output         : None
----------------------------------------------------------*/
int TouchGetX(void){
   uint16_t adx;
   adx = Read_X();
   return adx;
}
/*----------------------------------------------------------
 Function Name  :
 Description    :
 Input          : None
 Output         : None
----------------------------------------------------------*/
int TouchGetY(void){
   uint16_t ady;
   ady = Read_Y();
   return ady;
}
/*----------------------------------------------------------
 Function Name  :
 Description    :
 Input          : None
 Output         : None
----------------------------------------------------------*/
void calibrateToucPanel(void) {
  int ax_Phys[2],ay_Phys[2];
   
   //GUI_PID_STATE TS_State
  #define TP_MAX_X    320
  #define TP_MAX_y    240   
   
  //calculate log. Positions */
  const int ax[2] = { 15, (TP_MAX_X -1) -15};
  const int ay[2] = { 15, (TP_MAX_Y -1) -15};
  GUI_TOUCH_SetDefaultCalibration();
/* Calibrate upper left */
  GUI_SetBkColor(GUI_RED);
  GUI_Clear();
  GUI_SetColor(GUI_WHITE);  GUI_FillCircle(ax[0], ay[0], 10);
  GUI_SetColor(GUI_RED);    GUI_FillCircle(ax[0], ay[0], 5);
  GUI_SetColor(GUI_WHITE);
  GUI_DispStringAt("Toque aqui", ax[0]+20, ay[0]);
  do {
    GUI_PID_STATE State;
    GUI_PID_GetState(&State);
    if (State.Pressed) {
      ax_Phys[0] = GUI_TOUCH_GetxPhys();
      ay_Phys[0] = GUI_TOUCH_GetyPhys();
      break;
    }
    GUI_Delay (100);
  } while (1);
/* Tell user to release */
  GUI_Clear();
  GUI_DispStringAt("OK", ax[0]+20, ay[0]);
  do {
    GUI_PID_STATE State;
    GUI_PID_GetState(&State);
    if (State.Pressed==0) {
      break;
    }
    GUI_Delay (100);
  } while (1);
/* Calibrate lower right */
  GUI_SetBkColor(GUI_RED);
  GUI_Clear();
  GUI_SetColor(GUI_WHITE);  GUI_FillCircle(ax[1], ay[1], 10);
  GUI_SetColor(GUI_RED);    GUI_FillCircle(ax[1], ay[1], 5);
  GUI_SetColor(GUI_WHITE);
  GUI_SetTextAlign(GUI_TA_RIGHT);
  GUI_DispStringAt("Toque aqui", ax[1]-20, ay[1]);
  do {
    GUI_PID_STATE State;
    GUI_PID_GetState(&State);
    if (State.Pressed) {
      ax_Phys[1] = GUI_TOUCH_GetxPhys();
      ay_Phys[1] = GUI_TOUCH_GetyPhys();
      break;
    }
    GUI_Delay (100);
  } while (1);
  GUI_TOUCH_Calibrate(GUI_COORD_X, ax[0], ax[1], ax_Phys[0], ax_Phys[1]);
  GUI_TOUCH_Calibrate(GUI_COORD_Y, ay[0], ay[1], ay_Phys[0], ay_Phys[1]);
}

void TestFisicalTouch(void) {
  GUI_Init();
  GUI_CURSOR_Show();
  GUI_CURSOR_Select(&GUI_CursorCrossL);
  GUI_SetBkColor(GUI_WHITE);
  GUI_SetColor(GUI_BLACK);
  GUI_Clear();

  while (1) {
    GUI_PID_STATE TouchState;
    int xPhys, yPhys;
    GUI_TOUCH_GetState(&TouchState);  /* Get the touch position in pixel */
    xPhys = GUI_TOUCH_GetxPhys();     /* Get the A/D mesurement result in x */
    yPhys = GUI_TOUCH_GetyPhys();     /* Get the A/D mesurement result in y */
    /* Display the measurement result */
    GUI_SetColor(GUI_BLUE);
    GUI_DispStringAt("Analog input:\n", 0, 20);
    GUI_GotoY(GUI_GetDispPosY() + 2);
    GUI_DispString("x:");
    GUI_DispDec(xPhys, 4);
    GUI_DispString(", y:");
    GUI_DispDec(yPhys, 4);
    /* Display the according position */
    GUI_SetColor(GUI_RED);
    GUI_GotoY(GUI_GetDispPosY() + 4);
    GUI_DispString("\nPosition:\n");
    GUI_GotoY(GUI_GetDispPosY() + 2);
    GUI_DispString("x:");
    GUI_DispDec(TouchState.x,4);
    GUI_DispString(", y:");
    GUI_DispDec(TouchState.y,4);
    /* Wait a while */
    GUI_Delay(100);
  };
}

/*----------------------------------------------------------
      END FILE
----------------------------------------------------------*/
