/*-----------------------------------------------------------------
   Copyright (c)
   Arquivo......: wsuccao.c
   descrição....: 
   usuário......: 
------------------------------------------------------------------*/
   
   /* includes ------------------------------------------*/   
   #include "wsuccao.h"
   #include "wmain.h"                 /*const messages*/
   
   #define TIME_SUCCAO    60;

   /* variables -----------------------------------------*/ 
   uint8_t isec;

/*--------------------------------------------------------
 function.....: 
 description..: 
 dependencie..: 
----------------------------------------------------------*/
void cbsuccao(WM_MESSAGE * pMsg) {
   WM_HWIN  hItem;
   int      NCode;
   int      Id;
   TClock   myTime;
   char     ebuffer[20];
   
   switch (pMsg->MsgId) {
   case WM_INIT_DIALOG:
      WM_CreateTimer(WM_GetClientWindow(pMsg->hWin), 0, 1000, 0);
   
      FRAMEWIN_SetTitleHeight(pMsg->hWin, 17);
      FRAMEWIN_SetText(pMsg->hWin, "Sucção de produto concentrado");
      FRAMEWIN_SetTextColor(pMsg->hWin, GUI_WHITE);
      FRAMEWIN_SetFont(pMsg->hWin, GUI_FONT_13_1);

      hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT0);
      TEXT_SetFont(hItem, GUI_FONT_16_1);
      TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
      TEXT_SetText(hItem, "tempo: 00:01:00");
   
      hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_CANCEL);
      BUTTON_SetFont(hItem, GUI_FONT_13_1);
      BUTTON_SetText(hItem, "Cancelar");
   
      isec = TIME_SUCCAO;
      RelaySet(BombaPeristaltica, ON);
   break;
   case WM_NOTIFY_PARENT:
      Id    = WM_GetId(pMsg->hWinSrc);
      NCode = pMsg->Data.v;
      if( Id == GUI_ID_CANCEL){
         if( NCode == WM_NOTIFICATION_RELEASED){
            RelaySet(BombaPeristaltica, OFF);
            GUI_EndDialog(pMsg->hWin, 0);
            wcreate_tools();
         };
      };
   break;
   case WM_TIMER:
      isec--;
      if( SensorProduto() )  isec = 0;
      
      if(isec == 0){
         RelaySet(BombaPeristaltica, OFF); 
         GUI_EndDialog(pMsg->hWin, 0);
         wcreate_tools();
      };
      ConvertTime(isec, &myTime);
      sprintf(ebuffer," tempo: %02u:%02u:%02u", myTime.hour, myTime.min, myTime.sec );
      hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT0);
      TEXT_SetText(hItem, ebuffer);

      WM_RestartTimer( (WM_HMEM)(pMsg->Data.v), 1000);
   break;   
   default:
      WM_DefaultProc(pMsg);
   break;
   }
}

void wcreate_succao(void){
  WM_HWIN hWin;
  Txy t;
  hWin = GUI_CreateDialogBox(aLiteMsg, GUI_COUNTOF(aLiteMsg), cbsuccao, WM_HBKWIN, 0, 0);
  Win_XY(hWin, &t);
  WM_MoveWindow(hWin, t.x, t.y);
}
/*------------------------------------------------------------
    EOF
--------------------------------------------------------------*/
