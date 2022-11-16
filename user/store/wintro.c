/*-----------------------------------------------------------------
   Copyright (c)
   file.........: intro.c
   description..: splash screen
   user.........: 
  -----------------------------------------------------------------*/
   #include "wintro.h"
   
/*---------------------------------------------------------
 function.....: 
 description..: 
 
  printf ("SD Card Drive 1 free: %lld bytes.\n", ffree("M0:"));
----------------------------------------------------------*/ 
static void cbIntro(WM_MESSAGE * pMsg) {
   WM_HWIN      hItem;
   int xSize, ySize;
   char my_buf[30];
   char my_date[] = "Data comp. " __DATE__;
   char my_time[] = "hora comp. " __TIME__;
   
   switch (pMsg->MsgId) {
   case WM_INIT_DIALOG:
      hItem = pMsg->hWin;
      WM_CreateTimer(WM_GetClientWindow(hItem), 0, 5000, 0);
   
      FRAMEWIN_SetTitleVis(hItem, 0);
   
      hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
      TEXT_SetText(hItem, "xxxxxxxxxxxx");
      TEXT_SetFont(hItem, GUI_FONT_COMIC18B_1);
      TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
      TEXT_SetTextColor(hItem, 0x0000FF00);

      sprintf(my_buf, "Firmware %s", SOFT_VERSION);
      hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
      TEXT_SetFont(hItem, GUI_FONT_13_1);
      TEXT_SetText(hItem, my_buf);
      TEXT_SetTextColor(hItem, 0x0000FFFF);

      hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
      TEXT_SetText(hItem, my_date);
      TEXT_SetTextColor(hItem, 0x0000FFFF);

      hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
      TEXT_SetText(hItem, "Lib 05.06");
      TEXT_SetTextColor(hItem, 0x00FFFFFF);

      hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
      if( !InitSDCard() ) TEXT_SetText(hItem, "SD Card Ok.");
      else                TEXT_SetText(hItem, "Sd Card - erro");
      TEXT_SetTextColor(hItem, 0x00FFFFFF);

      hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
      TEXT_SetText(hItem, "xxxxxxxxxxxxxxx");
      TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
      TEXT_SetTextColor(hItem, 0x00FFFF00);

      hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
      TEXT_SetText(hItem, "wmnjnjjj");
      TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
      TEXT_SetTextColor(hItem, 0x00FFFFFF);
   
      WM_InvalidateWindow(pMsg->hWin);
   break;
   case WM_PAINT:
      xSize = WM_GetWindowSizeX(pMsg->hWin);
      ySize = WM_GetWindowSizeY(pMsg->hWin);
      GUI_DrawGradientV(0, 0, xSize, ySize, GUI_BLUE, GUI_BLACK);
   break;   
   case WM_TIMER:
      GUI_EndDialog(pMsg->hWin, 0);
      wcreate_desktop();
      wcreate_main();
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
void wcreate_intro(void){
  WM_HWIN hWin; 
  hWin = GUI_CreateDialogBox(aIntro, GUI_COUNTOF(aIntro), cbIntro, WM_HBKWIN, 0, 0);
}
/*------------------------------------------------------------
    EOF
--------------------------------------------------------------*/