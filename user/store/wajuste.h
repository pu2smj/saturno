/*-----------------------------------------------------------------
   Copyright (c)
   Arquivo......: ajuste.h
   descrição....: 
   usuário......: 
  -----------------------------------------------------------------*/ 

#ifndef _WAJUSTE_H
   #define _WAJUSTE_H
     
   #include "definicoes.h"
   #include "stm32f10x.h"
   #include "GUI.h"
   #include "DIALOG.h"
   
   static const GUI_WIDGET_CREATE_INFO aajust[] = {
      { FRAMEWIN_CreateIndirect, "", GUI_ID_USER+8,  0,  0,  275, 175, 0, 0x64, 0 },
      { BUTTON_CreateIndirect,   "", GUI_ID_OK,     90, 110, 100,  30, 0, 0x0, 0 },
      { EDIT_CreateIndirect,     "", GUI_ID_EDIT0, 135,  10, 100,  20, 0, 0x64, 0 },
      { EDIT_CreateIndirect,     "", GUI_ID_EDIT1, 135,  35, 100,  20, 0, 0x64, 0 },
      { EDIT_CreateIndirect,     "", GUI_ID_EDIT2, 135,  60, 100,  20, 0, 0x64, 0 },
   };

   /* local variables -----------------------------------*/ 

   /* extern variables -----------------------------------*/ 
   void wcreate_ajuste(void);
   
#endif
/*------------------------------------------------------------
    EOF
--------------------------------------------------------------*/