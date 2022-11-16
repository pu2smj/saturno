/*--------------------------------------------------------
  * @file........ intro.h
  * @author...... renato
  * @description. 
  --------------------------------------------------------
*/

#ifndef _WINTRO_H
   #define _WINTRO_H

   #include "stm32f10x.h"
   #include "GUI.h"
   #include "DIALOG.h"
   #include "wmain.h"
   #include "definicoes.h"
      
   /* local defines -------------------------------------*/ 
   #define ID_WINDOW_0  (GUI_ID_USER + 0x00)
   
   /* local variables -----------------------------------*/ 
   static const GUI_WIDGET_CREATE_INFO aIntro[] = {
     { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 1, 320, 240, 0, 0x0, 0 },
   };
   /* extern variables -----------------------------------*/ 

   /* prototypes -----------------------------------------*/ 
   void wintro(void);

#endif
/*------------------------------------------------------------
    EOF
--------------------------------------------------------------*/