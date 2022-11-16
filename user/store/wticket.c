/*-----------------------------------------------------------------
   Copyright (c)
   file.........: 
   description..: 
   user.........: 
  -----------------------------------------------------------------*/
   #include <RTL.h>           /*RTL kernel functions & defines*/
   #include "File_Config.h"   /**/ 
   #include "wticket.h"
   #include "usart.h"
   #include "stdio.h"   
   
   #define tSCREEN        0x00
   #define tPRINT         0x01
   
   /* Extern variables ------------------------------------*/
   extern Ted ed;

/*---------------------------------------------------------
 function.....: cbTicket
 description..:
 dependence...: wcreate_ticket
----------------------------------------------------------*/
void cbTicket(WM_MESSAGE * pMsg) {
   WM_HWIN hItem;
   int     NCode;
   int     Id;
   char  abuffer[10];

   switch (pMsg->MsgId) {
   case WM_INIT_DIALOG:
      FRAMEWIN_SetTitleHeight(pMsg->hWin, 15);
      FRAMEWIN_SetTextColor(pMsg->hWin, 0x00ffffff);
      FRAMEWIN_SetText(pMsg->hWin, "Impressão de ticket");
      FRAMEWIN_SetFont(pMsg->hWin, GUI_FONT_13_1);
      
      hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_OK);
      BUTTON_SetFont(hItem, GUI_FONT_13_1);
      BUTTON_SetText(hItem, "Imprimir");
   
      hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_CANCEL);
      BUTTON_SetFont(hItem, GUI_FONT_13_1);
      BUTTON_SetText(hItem, "Fechar");
   
      hItem = MULTIEDIT_CreateEx(10, 60, 300, 170, pMsg->hWin,  WM_CF_SHOW, MULTIEDIT_CF_AUTOSCROLLBAR_V, GUI_ID_MULTIEDIT0, 0, "");
      MULTIEDIT_SetFont(hItem, &GUI_Font6x8_ASCII); //GUI_Font8x16);
      break;
   case WM_PAINT:
      GUI_SetColor(GUI_BLACK);
      GUI_SetFont(&GUI_Font13_1);
      GUI_DispStringAt("Ticket nr.", 8, 8);
      break;
   case WM_NOTIFY_PARENT:
      Id    = WM_GetId(pMsg->hWinSrc);
      NCode = pMsg->Data.v;
      switch(Id){
      case GUI_ID_OK:
         if( NCode == WM_NOTIFICATION_RELEASED){
            hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT0);
            EDIT_GetText(hItem, abuffer, EDIT_GetNumChars(hItem)+1 );
            
            hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_MULTIEDIT0);
            pticket_a(hItem, tPRINT, (char*)abuffer);
         };
         break;
      case GUI_ID_CANCEL:
         if( NCode == WM_NOTIFICATION_RELEASED){
            GUI_EndDialog(pMsg->hWin, 0);
            wcreate_setup();
         };
         break;
      case GUI_ID_EDIT0:
         if( NCode == WM_NOTIFICATION_RELEASED){
            hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT0);
            EDIT_GetText(hItem, (char*)abuffer, sizeof(abuffer));
            keyboard(e_char, (char*)abuffer, "Ticket nr.");
         };
         break;
      };
      break;
   case MSG_KEYB_OK:
      hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT0);
      EDIT_SetText(hItem,(char*)pMsg->Data.p);
      strcpy( abuffer, (char*)pMsg->Data.p);
   
      hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_MULTIEDIT0);
      pticket_a(hItem, tSCREEN, (char*)abuffer);
      break;
   default:
     WM_DefaultProc(pMsg);
   }
}
/*---------------------------------------------------------
 function.....: wcreate_ticket
 description..:
 dependence...: wcreate_tools, cb_wtools
----------------------------------------------------------*/ 
void wcreate_ticket(void) {
   WM_HWIN hWin;
   Txy t;
   hWin = GUI_CreateDialogBox(aTicket, GUI_COUNTOF(aTicket), &cbTicket, WM_HBKWIN, 0, 0);
   
   Win_XY(hWin, &t);
   WM_MoveWindow(hWin, t.x, t.y);
}
/*---------------------------------------------------------
 function.....: pticket
 description..:
 dependence...: cbTicket
----------------------------------------------------------*/ 
void pticket_a(WM_HWIN h, uint8_t m, const char* pbuf){
   FILE    *fin;
   uint8_t ncount;
   char    line[40];
   char    sfilename[20];

   if(m == tSCREEN) MULTIEDIT_SetText(h, "");
   
   set_rs232( IMPLOG );
   
   sprintf(sfilename, "M0:\\log\\%06s.dat", pbuf);
   fin = fopen( sfilename, "r");
   if (fin != NULL) {
      ncount = 0;
      while( !feof (fin)){
         fgets(line, sizeof(line), fin);
         if( m != tSCREEN){
            Uart2WriteStr( line );
            os_dly_wait(time_of_printer);
         }else{
            MULTIEDIT_AddText(h, line);
         };
         ncount++;
         if(ncount > 100) break;
      };
      if(m != tSCREEN) Uart2WriteStr("\n\n\n\n\n");
      fclose(fin);
   };
}