/*--------------------------------------------------------
  * @file........ 24C02.c
  * @author...... renato
  * @description. I2C routines
  --------------------------------------------------------
*/

   typedef union v{
      float f;
      char  s[4];
   }fval;


   /* Includes ------------------------------------------*/
   #include <rtl.h> 
   #include "24C02.h"

/*---------------------------------------------------------
 function.....: I2C_Configuration
 description..: 
 input........: 
 output.......: 
 last edition.: 02/02/13
----------------------------------------------------------*/
void I2C_Configuration(void){
  GPIO_InitTypeDef  GPIO_InitStructure; 
  /* Configure I2C2 pins: PB6->SCL and PB7->SDA */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}
/*---------------------------------------------------------
 function.....: I2C_delay
 description..: 
 input........: 
 output.......: 
 last edition.: 02/02/13
----------------------------------------------------------*/
static void I2C_delay(void){   
  uint8_t i=50;
  while(i){ 
     i--; 
   }
  // os_dly_wait(10);
}
/*---------------------------------------------------------
 function.....: I2C_Start
 description..: 
 input........: 
 output.......: 
 last edition.: 02/02/13
----------------------------------------------------------*/
static FunctionalState I2C_Start(void){
   SDA_H;
   SCL_H;
   I2C_delay();
   if(!SDA_read)return DISABLE;
   SDA_L;
   I2C_delay();
   if(SDA_read) return DISABLE;
   SDA_L;
   I2C_delay();
   return ENABLE;
}
/*---------------------------------------------------------
 function.....: I2C_Stop
 description..: 
 input........: 
 output.......: 
 last edition.: 02/02/13
----------------------------------------------------------*/
static void I2C_Stop(void){
   SCL_L;
   I2C_delay();
   SDA_L;
   I2C_delay();
   SCL_H;
   I2C_delay();
   SDA_H;
   I2C_delay();
}
/*---------------------------------------------------------
 function.....: I2C_Ack
 description..: 
 input........: 
 output.......: 
 last edition.: 02/02/13
----------------------------------------------------------*/
static void I2C_Ack(void){   
   SCL_L;
   I2C_delay();
   SDA_L;
   I2C_delay();
   SCL_H;
   I2C_delay();
   SCL_L;
   I2C_delay();
}
/*---------------------------------------------------------
 function.....:  I2C_NoAck
 description..: 
 input........: 
 output.......: 
 last edition.: 02/02/13
----------------------------------------------------------*/
static void I2C_NoAck(void){   
   SCL_L;
   I2C_delay();
   SDA_H;
   I2C_delay();
   SCL_H;
   I2C_delay();
   SCL_L;
   I2C_delay();
}
/*---------------------------------------------------------
 function.....: I2C_WaitAck
 description..: 
 input........: 
 output.......: 
 last edition.: 02/02/13
----------------------------------------------------------*/
static FunctionalState I2C_WaitAck(void){
   SCL_L;
   I2C_delay();
   SDA_H;         
   I2C_delay();
   SCL_H;
   I2C_delay();
   if(SDA_read){
      SCL_L;
      return DISABLE;
   }
   SCL_L;
   return ENABLE;
}
/*---------------------------------------------------------
 function.....: I2C_SendByte
 description..: 
 input........: 
 output.......: 
 last edition.: 02/02/13
----------------------------------------------------------*/
static void I2C_SendByte(uint8_t SendByte){
    uint8_t i=8;
    while(i--){
        SCL_L;
        I2C_delay();
      if(SendByte&0x80)
        SDA_H;  
      else 
        SDA_L;   
        SendByte<<=1;
        I2C_delay();
        SCL_H;
        I2C_delay();
    }
    SCL_L;
}
/*---------------------------------------------------------
 function.....: I2C_ReceiveByte
 description..: 
 input........: 
 output.......: 
 last edition.: 02/02/13
----------------------------------------------------------*/
static uint8_t I2C_ReceiveByte(void){ 
    uint8_t i=8;
    uint8_t ReceiveByte=0;

    SDA_H;            
    while(i--){
      ReceiveByte<<=1;      
      SCL_L;
      I2C_delay();
     SCL_H;
      I2C_delay();   
      if(SDA_read){
        ReceiveByte|=0x01;
      }
    }
    SCL_L;
    return ReceiveByte;
}
/*---------------------------------------------------------
 function.....: I2C_WriteByte
 description..: 
 input........: - SendByte, 
                - WriteAddress:
                - DeviceAddress:
 output.......: 
 last edition.: 02/02/13
----------------------------------------------------------*/
FunctionalState I2C_WriteByte(uint8_t SendByte, uint16_t WriteAddress, uint8_t DeviceAddress){		
    if(!I2C_Start())return DISABLE;
    I2C_SendByte(((WriteAddress & 0x0700) >>7) | DeviceAddress & 0xFFFE);
    if(!I2C_WaitAck()){I2C_Stop(); return DISABLE;}
    I2C_SendByte((uint8_t)(WriteAddress & 0x00FF));
    I2C_WaitAck();
    I2C_SendByte(SendByte);
    I2C_WaitAck();
    I2C_Stop();
    os_dly_wait(20);
    return ENABLE;
}
/*---------------------------------------------------------
 function.....: I2C_ReadByte
 description..: 
 input........: - pBuffer:
                - length:
                - ReadAddress:
                - DeviceAddress:
 output.......: 
 last edition.: 02/02/13
----------------------------------------------------------*/
FunctionalState I2C_ReadByte(uint8_t* pBuffer,   uint16_t length,   uint16_t ReadAddress,  uint8_t DeviceAddress){		
    if(!I2C_Start())return DISABLE;
    I2C_SendByte(((ReadAddress & 0x0700) >>7) | DeviceAddress & 0xFFFE);
    if(!I2C_WaitAck()){I2C_Stop(); return DISABLE;}
    I2C_SendByte((uint8_t)(ReadAddress & 0x00FF));      
    I2C_WaitAck();
    I2C_Start();
    I2C_SendByte(((ReadAddress & 0x0700) >>7) | DeviceAddress | 0x0001);
    I2C_WaitAck();
    while(length){
      *pBuffer = I2C_ReceiveByte();
      if(length == 1)I2C_NoAck();
      else I2C_Ack(); 
      pBuffer++;
      length--;
    }
    I2C_Stop();
    return ENABLE;
}
/*---------------------------------------------------------
 function.....: I2C_WriteData
 description..: 
 input........: data, len, address
 output.......: 
 last edition.: 02/02/13
----------------------------------------------------------*/
void I2C_WriteData(uint8_t* pBuffer, uint8_t length, uint8_t addr){
   uint8_t n;
   for(n=0; n<= length; n++){
      I2C_WriteByte( *pBuffer++, addr++, ADR_24LC02);
   };  
}
/*---------------------------------------------------------
 function.....: 
 description..: 
 input........: data, address
 output.......: 
 last edition.: 02/02/13
----------------------------------------------------------*/
void I2C_WriteInt(uint8_t data, uint8_t addr){
  I2C_WriteByte(data, addr,  ADR_24LC02); 
}   
/*---------------------------------------------------------
 function.....: 
 description..: 
 input........: address
 output.......: 
 last edition.: 02/02/13
----------------------------------------------------------*/
uint8_t I2C_ReadInt(uint8_t addr){
  uint8_t val[1]; 
  uint8_t ret;
  I2C_ReadByte(val, 1, addr, ADR_24LC02);
  ret = val[0];
  os_dly_wait(10);
  return ret; 
}
//
/*---------------------------------------------------------
 function.....: I2C_WriteLong
 description..: 
 input........: data, address
 output.......: 
 last edition.: 02/02/13
----------------------------------------------------------*/
void I2C_WriteLong(uint16_t data, uint8_t addr){
   uint8_t auxl, auxh, addrh;
   auxl = data % 256;
   auxh = data >> 8;
   addrh = addr +1;
   I2C_WriteByte(auxl, addr,  ADR_24LC02);
   I2C_WriteByte(auxh, addrh, ADR_24LC02);
}
/*---------------------------------------------------------
 function.....: I2C_ReadLong
 description..: 
 input........: address
 output.......: 
----------------------------------------------------------*/
uint16_t I2C_ReadLong(uint8_t addr){
   uint16_t temp;
   uint8_t buf[2]=0;
   
   I2C_ReadByte(buf, 2, addr, ADR_24LC02);
   temp = buf[1];
   temp = (temp<<8) + buf[0];   
   return temp;
}
//
/*---------------------------------------------------------
 function.....: 
 description..: 
 input........: 
----------------------------------------------------------*/
void I2C_WriteFloat( float dado, uint8_t adr){
   fval val;
   /*Float - Little Endian (DCBA)*/
   val.f = dado;
   I2C_WriteInt(val.s[0], adr+0);
   I2C_WriteInt(val.s[1], adr+1);
   I2C_WriteInt(val.s[2], adr+3);
   I2C_WriteInt(val.s[3], adr+2);
}
/*---------------------------------------------------------
 function.....: 
 description..: ±1.175494E-38 to ±3.402823E+38
 input........: 
 output.......: 
----------------------------------------------------------*/
float I2C_ReadFloat(uint8_t adr){
   fval val;
   //Float - Little Endian (DCBA)
   val.f = 0.0;
   val.s[0] = I2C_ReadInt(adr+0);
   val.s[1] = I2C_ReadInt(adr+1);
   val.s[2] = I2C_ReadInt(adr+3);
   val.s[3] = I2C_ReadInt(adr+2);
   
   return val.f;
}
/*------------------------------------------------------------
    EOF
--------------------------------------------------------------*/
