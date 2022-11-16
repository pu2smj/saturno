 /*-----------------------------------------------------------------
   Copyright (c)
   file.........: 
   description..: 
   user.........: 
   -----------------------------------------------------------------*/
   #include "RTL.h"
   #include "wsetup.h"
   #include <wmain.h>

/*---------------------------------------------------------
 function.....: 
 description..: 
----------------------------------------------------------*/
void cbSetup(WM_MESSAGE * pMsg) {
   WM_HWIN hItem;
   int     NCode;
   int     Id;
   
   switch (pMsg->MsgId) {
   case WM_INIT_DIALOG:
      FRAMEWIN_SetTitleHeight(pMsg->hWin, 17);
      FRAMEWIN_SetFont(pMsg->hWin, GUI_FONT_13_1); 
      FRAMEWIN_SetText(pMsg->hWin, "Ajustes da Pressão");
      //FRAMEWIN_AddCloseButton(pMsg->hWin, FRAMEWIN_BUTTON_RIGHT,  0);

      hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_BUTTON0);
      BUTTON_SetText(hItem, "Pressão");
    
      hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_BUTTON1);
      BUTTON_SetText(hItem, "Set-Point");
   
      hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_OK);
      BUTTON_SetText(hItem, "Fechar");

   break;
   case WM_PAINT:
      NCode = WM_GetWindowSizeX(pMsg->hWin);
      Id    = WM_GetWindowSizeY(pMsg->hWin);
      GUI_DrawGradientV(0, 0, NCode, Id, 0x00ffffff, 0x00B19983);
   break;
   case WM_NOTIFY_PARENT:
      Id    = WM_GetId(pMsg->hWinSrc);
      NCode = pMsg->Data.v;
      if(NCode == WM_NOTIFICATION_RELEASED){
         switch(Id){
         case GUI_ID_BUTTON0:
            GUI_EndDialog(pMsg->hWin, 0);
            wcreate_setup_pressao();
            break;
         case GUI_ID_BUTTON1:
            GUI_EndDialog(pMsg->hWin, 0);
            wcreate_setup_setpoint();
            break;
         case GUI_ID_OK:
            GUI_EndDialog(pMsg->hWin, 0);
            wcreate_main();
            break;
         };
      };
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
void wcreate_setup(void){
   WM_HWIN hDlg;
   Txy t;
   
   hDlg = GUI_CreateDialogBox(aSetup, GUI_COUNTOF(aSetup), &cbSetup, WM_HBKWIN, 0, 0);
   Win_XY(hDlg, &t);
   WM_MoveWindow(hDlg, t.x, t.y);
}
/*---------------------------------------------------------
   EOF
----------------------------------------------------------*/