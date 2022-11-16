/*--------------------------------------------------------
  * @file........ wintro
  * @author...... renato
  * @description. splash screen
  --------------------------------------------------------
*/  
  
   #include "wintro.h"
   
/*---------------------------------------------------------
 function.....: 
 description..: 
----------------------------------------------------------*/ 
static void _cbIntro(WM_MESSAGE * pMsg) {
   WM_HWIN      hItem;
   
   switch (pMsg->MsgId) {
   case WM_INIT_DIALOG:
      WM_CreateTimer(WM_GetClientWindow(hItem), 0, 5000, 0);
   break;
   case WM_PAINT:
      GUI_SetBkColor(0x00D88643);
   
      GUI_Clear();
      GUI_SetColor(GUI_WHITE); 
      GUI_SetFont(&GUI_Font20_1);
      GUI_DispStringHCenterAt("machine", 37, WM_GetWindowSizeX(pMsg->hWin)/2);
   
      GUI_SetColor(GUI_WHITE);
      GUI_SetFont(&GUI_Font16_1);
      GUI_DispStringHCenterAt("brand", 87, WM_GetWindowSizeX(pMsg->hWin)/2);
      GUI_DispStringHCenterAt("name", 132, WM_GetWindowSizeX(pMsg->hWin)/2);
   
      GUI_SetColor(GUI_YELLOW);
      GUI_SetFont(&GUI_Font6x8);
      GUI_DispStringAt("firmware 01.02", 12, 215);
   break;   
   case WM_TIMER:
      GUI_EndDialog(pMsg->hWin, 0);
      wdesktop();
      wmain();
   break;
   default:
      WM_DefaultProc(pMsg);
   break;
   }
}
/*---------------------------------------------------------
 function.....: 
 description..: 
----------------------------------------------------------*/ 
//WM_HWIN wintro(void) {
void wintro(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(aIntro, GUI_COUNTOF(aIntro), _cbIntro, WM_HBKWIN, 0, 0);
  //return hWin;
}
/*------------------------------------------------------------
   EOF
--------------------------------------------------------------*/