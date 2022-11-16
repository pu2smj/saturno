/*--------------------------------------------------------
  * @file........ wmain.h
  * @author...... renato
  * @description. 
  --------------------------------------------------------
*/

#ifndef _WMAIN_H
   #define _WMAIN_H
     
   #include "stm32f10x.h"
   #include "GUI.h"
   #include "DIALOG.h"
   #include "wsetup.h"
   #include "wprocess.h"
   #include "level0.h"
   #include "definicoes.h"
   
   /* local defines -------------------------------------*/ 
   
   /* local variables -----------------------------------*/ 
   static const GUI_WIDGET_CREATE_INFO amain[] = {
     { FRAMEWIN_CreateIndirect,"", GUI_ID_USER+1,    0,   0, 280, 200, 0, 0x64, 0 },
     { TEXT_CreateIndirect,    "", GUI_ID_TEXT0,    20, 160, 260,  15, 0, 0, 0 },
     { BUTTON_CreateIndirect,  "", GUI_ID_BUTTON0,  65,  20, 140,  35, 0, 0, 0 },
     { BUTTON_CreateIndirect,  "", GUI_ID_BUTTON1,  65,  60, 140,  35, 0, 0, 0 },
     { BUTTON_CreateIndirect,  "", GUI_ID_BUTTON2,  65, 100, 140,  35, 0, 0, 0 },
   };

   /* extern variables -----------------------------------*/ 
  
   /* prtototypes ----------------------------------------*/ 
   void wdesktop(void);
   void wmain(void);
     
   
#endif
/*------------------------------------------------------------
    EOF
--------------------------------------------------------------*/