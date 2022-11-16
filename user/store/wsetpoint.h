/*-----------------------------------------------------------------
   Copyright (c)
   Arquivo......: 
   descrição....: 
   usuário......: 
  -----------------------------------------------------------------*/ 

#ifndef _WSETUP_H
   #define _WSETUP_H
     
   #include "definicoes.h"
   #include "stm32f10x.h"
   #include "GUI.h"
   #include "MULTIPAGE.h"
      
   /* defines--------------------------------------------*/
   #define ID_FRAMEWIN_0         (GUI_ID_USER + 0)
   #define ID_MULTIPAGE_0        (GUI_ID_USER + 1)
   #define ID_BUTTON_0           (GUI_ID_USER + 2)
   #define ID_BUTTON_1           (GUI_ID_USER + 3)
   #define ID_BUTTON_2           (GUI_ID_USER + 4)
   #define ID_BUTTON_3           (GUI_ID_USER + 5)
   #define ID_BUTTON_4           (GUI_ID_USER + 6)
   #define ID_BUTTON_5           (GUI_ID_USER + 7)
   #define ID_TEXT_0             (GUI_ID_USER + 8)
   #define ID_EDIT_10            (GUI_ID_USER + 10)
   #define ID_EDIT_11            (GUI_ID_USER + 11)
   #define ID_EDIT_12            (GUI_ID_USER + 12)
   #define ID_EDIT_20            (GUI_ID_USER + 20)
   #define ID_EDIT_21            (GUI_ID_USER + 21)   
   #define ID_EDIT_22            (GUI_ID_USER + 22)
   #define ID_EDIT_23            (GUI_ID_USER + 23)
   #define ID_EDIT_24            (GUI_ID_USER + 24)
   #define ID_EDIT_30            (GUI_ID_USER + 30) 
   #define ID_EDIT_31            (GUI_ID_USER + 31)
   #define ID_EDIT_50            (GUI_ID_USER + 50)
      
   #define ID_CHECKBOX_0         (GUI_ID_USER + 26)
   #define ID_CHECKBOX_1         (GUI_ID_USER + 27)
   #define ID_CHECKBOX_2         (GUI_ID_USER + 28)
   #define ID_CHECKBOX_3         (GUI_ID_USER + 29)
   #define ID_CHECKBOX_4         (GUI_ID_USER + 30)
   #define ID_CHECKBOX_5         (GUI_ID_USER + 31)
   #define ID_CHECKBOX_6         (GUI_ID_USER + 32)
   #define ID_CHECKBOX_7         (GUI_ID_USER + 33)

   /* local variables -----------------------------------*/ 
//    static const GUI_WIDGET_CREATE_INFO aSetup[] = {
//      { FRAMEWIN_CreateIndirect, "", GUI_ID_USER + 1, 0, 0, 320, 240, 0, 0x0, 0 }
//    };
   
   /*password*/
   static const GUI_WIDGET_CREATE_INFO aPasword[] = {
     { WINDOW_CreateIndirect, "", 0, 0, 0, 280, 180, FRAMEWIN_CF_MOVEABLE},
     { EDIT_CreateIndirect,   "",  GUI_ID_EDIT2,     175,  23, 80, 20, 0, 0x64, 0 },
     { BUTTON_CreateIndirect, "7", GUI_ID_USER + 50,  20,  20, 35, 35, 0, 0x0, 0 },
     { BUTTON_CreateIndirect, "8", GUI_ID_USER + 51,  20,  70, 35, 35, 0, 0x0, 0 },
     { BUTTON_CreateIndirect, "9", GUI_ID_USER + 52,  20, 120, 35, 35, 0, 0x0, 0 },
     { BUTTON_CreateIndirect, "4", GUI_ID_USER + 53,  65,  20, 35, 35, 0, 0x0, 0 },
     { BUTTON_CreateIndirect, "5", GUI_ID_USER + 54,  65,  70, 35, 35, 0, 0x0, 0 },
     { BUTTON_CreateIndirect, "6", GUI_ID_USER + 55,  65, 120, 35, 35, 0, 0x0, 0 },
     { BUTTON_CreateIndirect, "1", GUI_ID_USER + 56, 115,  20, 35, 35, 0, 0x0, 0 },
     { BUTTON_CreateIndirect, "2", GUI_ID_USER + 57, 115,  70, 35, 35, 0, 0x0, 0 },
     { BUTTON_CreateIndirect, "3", GUI_ID_USER + 58, 115, 120, 35, 35, 0, 0x0, 0 },
     { BUTTON_CreateIndirect, "0", GUI_ID_USER + 59, 170,  70, 35, 35, 0, 0x0, 0 },
     { BUTTON_CreateIndirect, "",  GUI_ID_OK,        220,  70, 35, 35, 0, 0x0, 0 },
     { BUTTON_CreateIndirect, "",  GUI_ID_CANCEL,    170, 120, 80, 35, 0, 0x0, 0 }
   };
   /*calibration fator k of flow sensor*/
   static const GUI_WIDGET_CREATE_INFO _aPage1[] = {
      { WINDOW_CreateIndirect, "", 0, 0, 0, 280, 180, FRAMEWIN_CF_MOVEABLE},
      { EDIT_CreateIndirect,   "", ID_EDIT_10,  150,  10,  50, 20, 0, 0x64, 0 },  /*4,75*/
      { EDIT_CreateIndirect,   "", ID_EDIT_11,  150,  35,  50, 20, 0, 0x64, 0 },  /*7*/
      { EDIT_CreateIndirect,   "", ID_EDIT_12,  150,  60,  50, 20, 0, 0x64, 0 },  /*1000*/
      { TEXT_CreateIndirect,   "", GUI_ID_TEXT0,150,  85,  50, 20, 0, 0x64, 0 },
      { BUTTON_CreateIndirect, "", ID_BUTTON_0, 115, 110,  80, 25, 0, 0x0, 0 },   /*testar*/
   };
   /*ajust of peristaltic pump*/
   static const GUI_WIDGET_CREATE_INFO _aPage2[] = {
      { WINDOW_CreateIndirect, "", 0, 0, 0, 280, 180, FRAMEWIN_CF_MOVEABLE},
      { EDIT_CreateIndirect,   "", ID_EDIT_20,    170,  10,  60, 20, 0, 0x64, 0 }, //
      { EDIT_CreateIndirect,   "", ID_EDIT_21,    170,  35,  60, 20, 0, 0x64, 0 }, //
      { EDIT_CreateIndirect,   "", ID_EDIT_22,    170,  60,  60, 20, 0, 0x64, 0 }, //
      { EDIT_CreateIndirect,   "", ID_EDIT_23,    170,  85,  60, 20, 0, 0x0, 0 },  //10 ml
      { BUTTON_CreateIndirect, "", ID_BUTTON_1,   170, 133, 85, 25, 0, 0x0, 0 },  //teste
   };
   /*ajust volume and concentration*/
   static const GUI_WIDGET_CREATE_INFO _aPage3[] = {
      { WINDOW_CreateIndirect, "", 0, 0, 0, 280, 180, FRAMEWIN_CF_MOVEABLE},
      { EDIT_CreateIndirect,   "", ID_EDIT_30, 170, 10,  70, 20, 0, 0x64, 0 },   //
      { EDIT_CreateIndirect,   "", ID_EDIT_31, 170, 35,  70, 20, 0, 0x64, 0 },   //
   };
   /*option page*/
   static const GUI_WIDGET_CREATE_INFO _aPage4[] = {
      { WINDOW_CreateIndirect,   "", 0, 0, 0, 280, 180, FRAMEWIN_CF_MOVEABLE},
      { CHECKBOX_CreateIndirect, "", ID_CHECKBOX_0,  10, 10, 99, 20, 0, 0x0, 0 },  //etiqueta
      { CHECKBOX_CreateIndirect, "", ID_CHECKBOX_1,  10, 35, 99, 20, 0, 0x0, 0 },  //log
      { CHECKBOX_CreateIndirect, "", ID_CHECKBOX_2,  10, 62, 99, 20, 0, 0x0, 0 },  //radio
      { CHECKBOX_CreateIndirect, "", ID_CHECKBOX_3,  10, 88, 99, 20, 0, 0x0, 0 },  //can
      { CHECKBOX_CreateIndirect, "", ID_CHECKBOX_4, 159, 10, 99, 20, 0, 0x0, 0 },  //sd card
      { CHECKBOX_CreateIndirect, "", ID_CHECKBOX_5, 159, 35, 99, 20, 0, 0x0, 0 },  //timer
      { CHECKBOX_CreateIndirect, "", ID_CHECKBOX_6, 159, 62, 99, 20, 0, 0x0, 0 },  //skin
      { CHECKBOX_CreateIndirect, "", ID_CHECKBOX_7, 159, 88, 99, 20, 0, 0x0, 0 },  //capacitivo
      { TEXT_CreateIndirect,     "", ID_TEXT_0,      10,115, 80, 20, 0, 0x64, 0 },
   };
   /*test of devices*/
   static const GUI_WIDGET_CREATE_INFO _aPage5[] = {
      { WINDOW_CreateIndirect,   "", 0, 0, 0, 280, 180, FRAMEWIN_CF_MOVEABLE},
      { EDIT_CreateIndirect,     "", ID_EDIT_50,  70,  10,  50, 20, 0, 0x64, 0 },  /*250005*/
      { BUTTON_CreateIndirect,   "", ID_BUTTON_3, 180,  20, 80, 35, 0, 0x0, 0 },  //valv
      { BUTTON_CreateIndirect,   "", ID_BUTTON_4, 180,  60, 80, 35, 0, 0x0, 0 },  //bomba
      { BUTTON_CreateIndirect,   "", ID_BUTTON_5, 180, 100, 80, 35, 0, 0x0, 0 },  //sair
   };

   /* prototyppes --------------------------------------*/ 
   void wcreate_setup(void);
   
#endif
/*------------------------------------------------------------
    EOF
--------------------------------------------------------------*/