/*--------------------------------------------------------
  * @file........ wprocess.h
  * @author...... renato
  * @description. 
  --------------------------------------------------------
*/
#ifndef _WPROCESS_H
   #define _WPROCESS_H
     
   #include "definicoes.h"
   #include "stm32f10x.h"
   #include "GUI.h"
   #include "DIALOG.h"
   #include "level0.h"
   #include "wmain.h"
   
   /* local defines--------------------------------------*/
   #define ID_WINDOW_1     (GUI_ID_USER + 0x01)
   #define ID_GRAPH_0      (GUI_ID_USER + 0x02)
   #define ID_TEXT_0       (GUI_ID_USER + 0x03)
   #define ID_TEXT_1       (GUI_ID_USER + 0x04)
   #define ID_TEXT_2       (GUI_ID_USER + 0x05)

   /* local constants -----------------------------------*/
   static const GUI_WIDGET_CREATE_INFO aLiteConf[] = {
      { FRAMEWIN_CreateIndirect, "", GUI_ID_USER+6, 0,  0, 280, 150, 0, 0x64, 0 },
      { BUTTON_CreateIndirect,   "", GUI_ID_NO,    40, 80, 120, 40, 0, 0, 0 },
      { BUTTON_CreateIndirect,   "", GUI_ID_YES,  160, 80, 120, 40, 0, 0, 0 },
   };
 
   static const GUI_WIDGET_CREATE_INFO aProcess[] = {
      { WINDOW_CreateIndirect, "Window", ID_WINDOW_1, 0, 0, 320, 240, 0, 0x0, 0 },
      { GRAPH_CreateIndirect, "Graph", ID_GRAPH_0,  6, 6, 303, 132, 0, 0x0, 0 },
      { TEXT_CreateIndirect, "Text",   ID_TEXT_0, 100, 159, 80, 20, 0, 0x64, 0 },
      { TEXT_CreateIndirect, "Text",   ID_TEXT_1, 100, 192, 80, 20, 0, 0x64, 0 },
      { TEXT_CreateIndirect, "Text",   ID_TEXT_2, 100, 208, 80, 20, 0, 0x64, 0 },
      { BUTTON_CreateIndirect, "Button", GUI_ID_CANCEL, 180, 148, 125, 78, 0, 0x0, 0 },
   };
   /* local variables -----------------------------------*/ 

   /* extern variables -----------------------------------*/ 
   
   /* prototypes -----------------------------------------*/
   void wprocess(void);
   void wqueryprocess(void);

#endif

/*------------------------------------------------------------
    EOF
--------------------------------------------------------------*/
   
