/*--------------------------------------------------------
  * @file........ keyb
  * @author...... renato
  * @description. 
  --------------------------------------------------------
*/
#ifndef _WKEYB_H
   #define _WKEYB_H
     
   #include "definicoes.h"
   #include "stm32f10x.h"
   #include "GUI.h"
   
   /* local constants -----------------------------------*/ 
   static const GUI_WIDGET_CREATE_INFO aKeyb[] = {
     { FRAMEWIN_CreateIndirect, "",    GUI_ID_USER + 0, 0,   0, 320, 240, 0, 0x0, 0 },
     { BUTTON_CreateIndirect,   "<",   GUI_ID_BUTTON8, 203, 13,  30, 28, 0, 0x0,  0 },
     { BUTTON_CreateIndirect,   "CLR", GUI_ID_BUTTON9, 236, 13,  30, 28, 0, 0x0,  0 },
     { BUTTON_CreateIndirect,   "Ok",  GUI_ID_OK,      269, 13,  30, 28, 0, 0x0,  0 },
     
     /*  Function               Text    Id                   Px   Py   Dx   Dy */ 
     { BUTTON_CreateIndirect,   "7",    GUI_ID_USER + 16,   203,  48,  30,  28},
     { BUTTON_CreateIndirect,   "8",    GUI_ID_USER + 17,   236,  48,  30,  28},
     { BUTTON_CreateIndirect,   "9",    GUI_ID_USER + 18,   269,  48,  30,  28},
     { BUTTON_CreateIndirect,   "4",    GUI_ID_USER + 19,   203,  82,  30,  28},
     { BUTTON_CreateIndirect,   "5",    GUI_ID_USER + 20,   236,  82,  30,  28},
     { BUTTON_CreateIndirect,   "6",    GUI_ID_USER + 21,   269,  82,  30,  28},
     { BUTTON_CreateIndirect,   "1",    GUI_ID_USER + 22,   203, 116,  30,  28},
     { BUTTON_CreateIndirect,   "2",    GUI_ID_USER + 23,   236, 116,  30,  28},
     { BUTTON_CreateIndirect,   "3",    GUI_ID_USER + 24,   269, 116,  30,  28},
     { BUTTON_CreateIndirect,   "0",    GUI_ID_USER + 25,   203, 150,  30,  28},
     { BUTTON_CreateIndirect,   ".",    GUI_ID_USER + 26,   236, 150,  30,  28},
    };
   /* local variables -----------------------------------*/ 

   /* extern variables -----------------------------------*/ 
      
   /* prtototypes ----------------------------------------*/ 
   void keyboard(TTypeEdit ted, char* buf, const char* pText);

#endif
/*------------------------------------------------------------
    EOF
--------------------------------------------------------------*/