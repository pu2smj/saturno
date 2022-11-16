/*--------------------------------------------------------
  * @file........ wmain.c
  * @author...... renato
  * @description. main screen
  --------------------------------------------------------
*/   

   #include "wmain.h"
   
   /* Private variables ----------------------------------*/
   TMachine mac;
   TMachine* pMac = &mac;

   TPressure Pres;
   TPressure *pPres = &Pres;
   
   /* prtototypes ----------------------------------------*/ 
   static void _cbwin(WM_MESSAGE * pMsg);
   static void _cbmain(WM_MESSAGE * pMsg);
   
/*---------------------------------------------------------
 function.....: 
 description..: 
 control......: 
----------------------------------------------------------*/
static void _cbdesk(WM_MESSAGE * pMsg) {
   uint16_t xSize, ySize;
   
   switch (pMsg->MsgId){
   case WM_INIT_DIALOG:

   break;   
   case WM_NOTIFY_PARENT:

   break;
   case WM_PAINT:
      if( pMac->status == st_idle){
         xSize = WM_GetWindowSizeX(pMsg->hWin);
         ySize = WM_GetWindowSizeY(pMsg->hWin);
         GUI_DrawGradientV(0, 0, xSize, ySize, GUI_BLUE, 0x00B19983);
      }else{
         xSize = WM_GetWindowSizeX(pMsg->hWin);
         ySize = WM_GetWindowSizeY(pMsg->hWin);
         GUI_DrawGradientV(0, 0, xSize, ySize, GUI_RED, GUI_BLACK);
      };
   default:
      WM_DefaultProc(pMsg);
  }
}
/*---------------------------------------------------------
 function.....: 
 description..: 
 control......: 
----------------------------------------------------------*/
void wdesktop(void){
   WM_SetDesktopColor(GUI_BLACK);
//   pMac->win = WM_CreateWindowAsChild( 0,0, 320, 240,  WM_GetDesktopWindowEx(0), WM_CF_SHOW, &_cbdesk, 0);
}
//
//
/*---------------------------------------------------------
 function.....: 
 description..: 
 control......: 
----------------------------------------------------------*/ 
static void _cbmain(WM_MESSAGE * pMsg) {
   WM_HWIN   hItem;
   int       NCode;
   int       Id;
   uint16_t  xSize, ySize;
   char      s[12];
   
   switch (pMsg->MsgId) {
   case WM_INIT_DIALOG:
      WM_CreateTimer(WM_GetClientWindow(pMsg->hWin), 0, 1000, 0);
   
      FRAMEWIN_SetTitleHeight(pMsg->hWin, 15);
      FRAMEWIN_SetText(pMsg->hWin, "Menu Principal");
      FRAMEWIN_SetTextColor(pMsg->hWin, 0x00FFFFFF);
      FRAMEWIN_SetFont(pMsg->hWin, GUI_FONT_13_1);

      hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_BUTTON0);
      BUTTON_SetFont(hItem, GUI_FONT_13_1);
      BUTTON_SetText(hItem, "Setup");

      hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_BUTTON1);
      BUTTON_SetFont(hItem, GUI_FONT_13_1);
      BUTTON_SetText(hItem, "Tratamento");
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
            wcreate_setup();
            break;
         case GUI_ID_BUTTON1:
            GUI_EndDialog(pMsg->hWin, 0);
            wqueryprocess();
            break;
         };
     };
     break;
   case WM_CLOSE_MAIN_WIN:
      GUI_EndDialog(pMsg->hWin, 0);
      break;
   default:
      WM_DefaultProc(pMsg);
   break;
  }
}
/*---------------------------------------------------------
 function.....: 
 description..: 
 control......: 
----------------------------------------------------------*/
void wmain(void){
  WM_HWIN hMain; 
  Txy t;
   
  //static WM_HWIN amain;
  //hMain = WM_CreateWindow( 50,  70, 165, 100, WM_CF_SHOW | WM_CF_MEMDEV, _cbmain, 0);
   
  hMain = GUI_CreateDialogBox(amain, GUI_COUNTOF(amain), &_cbmain, WM_HBKWIN, 0, 0);
  Win_XY(hMain, &t);
  WM_MoveWindow(hMain, t.x, t.y);
}


/*------------------------------------------------------------
    EOF
--------------------------------------------------------------*/