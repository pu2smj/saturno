/*--------------------------------------------------------
  * @file........ wsetup.h
  * @author...... renato
  * @description. 
  --------------------------------------------------------
*/

#ifndef _WSETUP_H
   #define _WSETUP_H
     
   #include "definicoes.h"
   #include "stm32f10x.h"
   #include "GUI.h"
   #include "DIALOG.h"
   #include "wmain.h"
   #include "wkeyb.h"
      
   /* defines--------------------------------------------*/
   #define ID_FRAMEWIN_0         (GUI_ID_USER + 0)


  static const GUI_WIDGET_CREATE_INFO aSetup[] = {
     { FRAMEWIN_CreateIndirect,"",GUI_ID_USER+4,     0,   0, 280, 200, 0, 0x64, 0 },
     { EDIT_CreateIndirect,  "",  GUI_ID_EDIT0,    160,  43, 90, 24, 0, 0x64, 0 },
     { EDIT_CreateIndirect,  "",  GUI_ID_EDIT1,    160,  73, 90, 24, 0, 0x64, 0 },
     { EDIT_CreateIndirect,  "",  GUI_ID_EDIT2,    160, 103, 90, 24, 0, 0x64, 0 },
     { EDIT_CreateIndirect,  "",  GUI_ID_EDIT3,    160, 133, 90, 24, 0, 0x64, 0 },
     { BUTTON_CreateIndirect,"",  GUI_ID_OK,       110, 178,107, 30, 0, 0x0, 0 },
   };

   /* prototyppes --------------------------------------*/ 
   void wcreate_setup(void);
   
#endif
/*------------------------------------------------------------
    EOF
--------------------------------------------------------------*/