/*--------------------------------------------------------
  * @file........ 24C02.h
  * @author...... renato
  * @description. I2C routines
  --------------------------------------------------------
*/

#ifndef __24C02_H
   #define __24C02_H

   /* Includes ---------------------------------------------*/
   #include "stm32f10x.h"

   /* Private define ---------------------------------------*/
   #define SCL_H         GPIOB->BSRR = GPIO_Pin_6
   #define SCL_L         GPIOB->BRR  = GPIO_Pin_6
      
   #define SDA_H         GPIOB->BSRR = GPIO_Pin_7
   #define SDA_L         GPIOB->BRR  = GPIO_Pin_7

   #define SCL_read      GPIOB->IDR  & GPIO_Pin_6
   #define SDA_read      GPIOB->IDR  & GPIO_Pin_7

   #define I2C_PageSize  8
   #define ADR_24LC02    0xA0

   /* Private function prototypes ---------------------------*/
   void I2C_Configuration(void);
   FunctionalState I2C_WriteByte(uint8_t SendByte, uint16_t WriteAddress, uint8_t DeviceAddress);
   FunctionalState I2C_ReadByte(uint8_t* pBuffer,   uint16_t length,   uint16_t ReadAddress,  uint8_t DeviceAddress);
   void I2C_WriteData(uint8_t* pBuffer, uint8_t length, uint8_t addr);

   void    I2C_WriteInt(uint8_t data, uint8_t addr);
   uint8_t I2C_ReadInt(uint8_t addr);
   
   void     I2C_WriteLong(uint16_t data, uint8_t addr);
   uint16_t I2C_ReadLong(uint8_t addr);
   
   void  I2C_WriteFloat( float dado, uint8_t adr);
   float I2C_ReadFloat(uint8_t adr);
      
#endif 
/*------------------------------------------------------------
                  EOF
--------------------------------------------------------------*/
