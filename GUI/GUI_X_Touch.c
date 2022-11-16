/*
----------------------------------------------------------------------
File        : GUI_TOUCH_X.C
Purpose     : Config / System dependent externals for GUI
---------------------------------------------------------
*/

#include "GUI.h"
#include "TouchPanel.h"

void GUI_TOUCH_X_ActivateX(void){
   return;
}

void GUI_TOUCH_X_ActivateY(void){
   return;
}

int  GUI_TOUCH_X_MeasureX(void) {
   uint16_t prevX;
   prevX = TouchGetX();
   return (prevX);  
}

int  GUI_TOUCH_X_MeasureY(void){
   uint16_t prevY;
   prevY = TouchGetY(); 
   return (prevY);
}
