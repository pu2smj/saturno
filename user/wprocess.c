/*--------------------------------------------------------
  * @file........ wprocess.c
  * @author...... renato
  * @description. 
  --------------------------------------------------------
*/
   #include <rtl.h> 
   #include "global_includes.h"
   #include "wprocess.h"
   
   /*extern variables ----------------------------------*/
   extern TMachine *pMac;
 
   /* prototypes -----------------------------------------*/
   void _cbQuery(WM_MESSAGE * pMsg);
   void _cbCancel(WM_MESSAGE * pMsg);
   void _cbProcess(WM_MESSAGE * pMsg);
   void wcancelprocess(void);


/*---------------------------------------------------------
 function.....: _cbQuery
 description..: confirmation of process
 dependencie..: wcreate_confprocess
----------------------------------------------------------*/
void _cbQuery(WM_MESSAGE * pMsg) {
   WM_HWIN  hItem;
   int      NCode;
   int      Id;
   int8_t   nCount = 0;
   static   WM_MESSAGE msg;
   
   switch (pMsg->MsgId) {
   case WM_INIT_DIALOG:
      WM_CreateTimer(WM_GetClientWindow(pMsg->hWin), 0, 10000, 0);
   
      FRAMEWIN_SetTitleHeight(pMsg->hWin, 17);
      FRAMEWIN_SetClientColor(pMsg->hWin, GUI_WHITE);
      FRAMEWIN_SetText(pMsg->hWin, "Pressurização");
      FRAMEWIN_SetFont(pMsg->hWin, GUI_FONT_13_1);
    
      hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_YES);
      BUTTON_SetText(hItem, "Sim");   

      hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_NO);
      BUTTON_SetText(hItem, "Não");
   break;
   case WM_NOTIFY_PARENT:
      Id    = WM_GetId(pMsg->hWinSrc);
      NCode = pMsg->Data.v;
      if(NCode == WM_NOTIFICATION_RELEASED){
         switch(Id) {
         case GUI_ID_YES:
               GUI_EndDialog(pMsg->hWin, 0);        /*close confirm*/
               msg.MsgId = WM_CLOSE_MAIN_WIN;       /*message to close screen*/
               WM_BroadcastMessage(&msg);           /*process message*/
               wprocess();
               startproc();
               //os_tsk_create(task_process, 8);
         break;
         case GUI_ID_NO:
            GUI_EndDialog(pMsg->hWin, 0);
            wmain();
         break;
         };
      };
   break;
   case WM_PAINT:
      //NCode = WM_GetWindowSizeX(pMsg->hWin);
      //Id    = WM_GetWindowSizeY(pMsg->hWin);
      //GUI_DrawGradientV(0, 0, NCode, Id, 0x00ffffff, 0x00B19983);
      //GUI_SetBkColor(0x00D88643);
      GUI_SetBkColor(GUI_GRAY);
      GUI_Clear();
      GUI_SetColor(GUI_BLACK);
      GUI_SetFont(&GUI_Font16_1);
      GUI_DispStringHCenterAt("Iniciar o Processo?", 15, WM_GetWindowSizeX(pMsg->hWin)/2);
   break;
   case WM_TIMER:
      nCount++;
      if(nCount > 10){
         GUI_EndDialog(pMsg->hWin, 0);
         wmain();
      };   
   break; 
   default:
      WM_DefaultProc(pMsg);
   break;
   }
}
/*---------------------------------------------------------
 function.....: wcreate_confprocess
 description..: screen confirmation of process
 dependencie..: wcreate_main
----------------------------------------------------------*/ 
void wqueryprocess(void){
   WM_HWIN hDlg;
   Txy t;
   hDlg = GUI_CreateDialogBox(aLiteConf, GUI_COUNTOF(aLiteConf), &_cbQuery, WM_HBKWIN, 0, 0);
   
   Win_XY(hDlg, &t);
   WM_MoveWindow(hDlg, t.x, t.y);
};
//
//
/*---------------------------------------------------------
 function.....: _cbCancel
 description..: callbackof screen
 dependencie..: wmessagestopprocess
----------------------------------------------------------*/  
void _cbCancel(WM_MESSAGE * pMsg) {
   WM_HWIN hItem;
   int     NCode;
   int     Id;
   static  WM_MESSAGE msg;
   
   switch (pMsg->MsgId) {
   case WM_INIT_DIALOG:
      WM_CreateTimer(WM_GetClientWindow(pMsg->hWin), 0, 5000, 0);
   
      FRAMEWIN_SetTitleHeight(pMsg->hWin, 20);
      FRAMEWIN_SetClientColor(pMsg->hWin, GUI_YELLOW);
      FRAMEWIN_SetText(pMsg->hWin, "Atenção");
      FRAMEWIN_SetTextColor(pMsg->hWin, GUI_WHITE);
      FRAMEWIN_SetFont(pMsg->hWin, GUI_FONT_13_1);
    
      hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_YES);
      BUTTON_SetText(hItem, "Sim");

      hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_NO);
      BUTTON_SetText(hItem, "Não");
   
      hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT0);
      TEXT_SetFont(hItem,  GUI_FONT_16_1);
      TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
      TEXT_SetText(hItem, "Cancelar o processo?");
   break;
   case WM_NOTIFY_PARENT:
      Id    = WM_GetId(pMsg->hWinSrc);
      NCode = pMsg->Data.v;
      if(NCode == WM_NOTIFICATION_RELEASED){
         switch(Id) {
         case GUI_ID_YES:
            msg.MsgId = WM_CANCEL_PROCESS;
            msg.Data.p = pMsg->Data.p;
            WM_BroadcastMessage(&msg);
            GUI_EndDialog(pMsg->hWin, 0);
         break;   
         case GUI_ID_NO:
            GUI_EndDialog(pMsg->hWin, 0);
         break;   
         };
      };
   break;
   case WM_PAINT:
      //NCode = WM_GetWindowSizeX(pMsg->hWin);
      //Id    = WM_GetWindowSizeY(pMsg->hWin);
      //GUI_DrawGradientV(0, 0, NCode, Id, 0x00ffffff, 0x00B19983);
      GUI_SetBkColor(GUI_DARKRED);
      GUI_Clear();
      GUI_SetColor(GUI_WHITE);
      GUI_SetFont(&GUI_Font16_1);
      GUI_DispStringHCenterAt("Iniciar o Processo?", 15, WM_GetWindowSizeX(pMsg->hWin)/2);
   break;
   case WM_TIMER:
      GUI_EndDialog(pMsg->hWin, 0);
   break;     
   default:
      WM_DefaultProc(pMsg);
   }
}
/*---------------------------------------------------------
 function.....: wmessagestopprocess
 description..: query to stop process
 dependencie..: cbProcess
----------------------------------------------------------*/  
void wcancelprocess(void){
   WM_HWIN hDlg;   
   Txy t;
   hDlg = GUI_CreateDialogBox(aLiteConf, GUI_COUNTOF(aLiteConf), &_cbCancel, WM_HBKWIN, 0, 0);
   Win_XY(hDlg, &t);
   WM_MoveWindow(hDlg, t.x, t.y);
};
//
//
/*---------------------------------------------------------
 function.....: cbProcess
 description..: callback of screeen
 dependencie..: wscreen_process
----------------------------------------------------------*/
void _cbProcess(WM_MESSAGE * pMsg) {
   WM_HWIN  hItem;
   int      NCode;
   int      Id;
   TClock   myTime;
   char     mybuf[30];
   
   switch (pMsg->MsgId) {
   case WM_INIT_DIALOG:
      WM_CreateTimer(WM_GetClientWindow(pMsg->hWin), 0, 100, 0);
   
      hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
      TEXT_SetText(hItem, "0");
      TEXT_SetFont(hItem, GUI_FONT_16_1);
      //
      hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
      TEXT_SetText(hItem, "ON");
      TEXT_SetFont(hItem, GUI_FONT_16_1);
       //
      hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
      TEXT_SetText(hItem, "00:00:00");
      TEXT_SetFont(hItem, GUI_FONT_16_1);
    
      hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_CANCEL);
      BUTTON_SetText(hItem, "Parar");
   break;
   case WM_NOTIFY_PARENT:
      Id    = WM_GetId(pMsg->hWinSrc);
      NCode = pMsg->Data.v;
      if(NCode == WM_NOTIFICATION_RELEASED){
         if(Id == GUI_ID_CANCEL){
            wcancelprocess();
         };
      };
   break;
   case WM_PAINT:
      NCode = WM_GetWindowSizeX(pMsg->hWin);
      Id    = WM_GetWindowSizeY(pMsg->hWin);
      GUI_DrawGradientV(0, 0, NCode, Id, 0x00ffffff, 0x00B19983);
      
      GUI_SetColor(GUI_BLACK);
      GUI_SetFont(&GUI_Font13_1);
      GUI_DispStringAt("Pressão", 12, 159);
      GUI_DispStringAt("Status",  12, 182);
      GUI_DispStringAt("Tempo",   12, 208);
   break;
   case WM_CANCEL_PROCESS:
      WM_InvalidateWindow(pMac->win);
      GUI_EndDialog(pMsg->hWin, 0);
      endproc();
      wmain();
   break;
   case WM_CLOSE_PROCESS:
      GUI_EndDialog(pMsg->hWin, 0);
   break;   
   case WM_TIMER:
      WM_RestartTimer( (WM_HMEM)(pMsg->Data.v), 100);
      mppt();
      hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
      TEXT_SetText(hItem, pMac->clock.stamp);
      
      if(pMac->clock.WorkTime > PTIMEOUT){
   
      };
   break;
   default:
      WM_DefaultProc(pMsg);
   break;
   }
}
/*---------------------------------------------------------
 function.....: wscreen_process
 description..: screen to dilution process
 dependencie..: wcreate_confprocess
----------------------------------------------------------*/ 
void wprocess(void){
   WM_HWIN hWin;
   Txy t;
   hWin = GUI_CreateDialogBox(aProcess, GUI_COUNTOF(aProcess), &_cbProcess, WM_HBKWIN, 0, 0);
   Win_XY(hWin, &t);
   WM_MoveWindow(hWin, t.x, t.y);
}
/*------------------------------------------------------------
    EOF
--------------------------------------------------------------*/
