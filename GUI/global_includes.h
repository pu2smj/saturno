 /*-----------------------------------------------------------------
   Copyright (c)
   Arquivo......: 
   descrição....: 
   usuário......: 
-----------------------------------------------------------------*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GLOBAL_INCLUDES_H__
#define __GLOBAL_INCLUDES_H__

   /* Includes -------------------------------------------*/
   
   #include "GUI.h"
   #include "DIALOG.h"
   #include "definicoes.h"
   #include "stm32f10x.h"
   
   /* Exported macro --------------------------------------*/
   #define LOBYTE(x)  ((uint8_t)(x & 0x00FF))
   #define HIBYTE(x)  ((uint8_t)((x & 0xFF00) >>8)) 


#endif /* __GLOBAL_INCLUDES_H__ */



