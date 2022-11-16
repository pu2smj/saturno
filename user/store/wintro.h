/*-----------------------------------------------------------------
   Copyright (c)
   Arquivo......: intro.h
   descrição....: 
   usuário......: 
  -----------------------------------------------------------------*/ 

#ifndef _WINTRO_H
   #define _WINTRO_H
     
   #include "definicoes.h"
   #include "stm32f10x.h"
   #include "GUI.h"
   #include "DIALOG.h"

   #define ID_FRAMEWIN_0 (GUI_ID_USER + 0x00)
   #define ID_TEXT_0     (GUI_ID_USER + 0x01)
   #define ID_TEXT_1     (GUI_ID_USER + 0x02)
   #define ID_TEXT_2     (GUI_ID_USER + 0x03)
   #define ID_TEXT_3     (GUI_ID_USER + 0x04)
   #define ID_TEXT_4     (GUI_ID_USER + 0x05)
   #define ID_TEXT_5     (GUI_ID_USER + 0x06)
   #define ID_TEXT_6     (GUI_ID_USER + 0x07)
   /* local variables -----------------------------------*/ 

   static const GUI_WIDGET_CREATE_INFO aIntro[] = {
     { FRAMEWIN_CreateIndirect, "", ID_FRAMEWIN_0, 0, 0, 320, 240, 0, 0x0, 0 },
     { TEXT_CreateIndirect, "", ID_TEXT_0, 23, 17, 272, 24, 0, 0x64, 0 },
     { TEXT_CreateIndirect, "", ID_TEXT_1, 25, 110, 80, 30, 0, 0x64, 0 },
     { TEXT_CreateIndirect, "", ID_TEXT_2, 25, 130,200, 30, 0, 0x64, 0 },
     { TEXT_CreateIndirect, "", ID_TEXT_3, 25, 150,200, 30, 0, 0x64, 0 },
     { TEXT_CreateIndirect, "", ID_TEXT_4, 25, 170, 80, 30, 0, 0x64, 0 },
     { TEXT_CreateIndirect, "", ID_TEXT_5, 19, 50, 274, 30, 0, 0x64, 0 },
     { TEXT_CreateIndirect, "", ID_TEXT_6, 158, 193, 118, 20, 0, 0x64, 0 },
   };
   /* extern variables -----------------------------------*/ 

   /* prototypes -----------------------------------------*/ 
   void CreateIntro(void);

#endif
/*------------------------------------------------------------
    EOF
--------------------------------------------------------------*/