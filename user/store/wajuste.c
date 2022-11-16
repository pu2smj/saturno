 /*-----------------------------------------------------------------
   Copyright (c)
   file.........: 
   description..: 
   user.........: 
   -----------------------------------------------------------------*/

   #include "wajuste.h"
   
   
   /* Private variables ---------------------*/
   uint8_t iEdit;
   WM_HWIN wEdit;
   char    abuffer[9];
/*---------------------------------------------------------
 function.....: 
 description..: 
----------------------------------------------------------*/
static void cbAjust(WM_MESSAGE * pMsg) {
   WM_HWIN hItem;
   int     NCode;
   int     Id;
   uint8_t itemp;
   
   switch (pMsg->MsgId) {
   case WM_INIT_DIALOG:
      FRAMEWIN_SetTitleHeight(pMsg->hWin, 17);
      FRAMEWIN_SetFont(pMsg->hWin, GUI_FONT_13_1); 
      FRAMEWIN_SetText(pMsg->hWin, "Parâmetros do Sistema");
      FRAMEWIN_AddCloseButton(pMsg->hWin, FRAMEWIN_BUTTON_RIGHT,  0);

      I2C_ReadByte((char*)abuffer, 8, ADR_MATRICULA, 0xA0);
      hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT0);
      EDIT_SetText(hItem, abuffer);
      EDIT_SetFont(hItem, &GUI_Font13_1);

      I2C_ReadByte(abuffer, 8, ADR_LOTE, 0xA0);
      hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT1);
      EDIT_SetText(hItem, abuffer);
      EDIT_SetFont(hItem, &GUI_Font13_1);

      hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_OK);
      BUTTON_SetText(hItem, "Fechar");

   break;
   case WM_PAINT:
      NCode = WM_GetWindowSizeX(pMsg->hWin);
      Id    = WM_GetWindowSizeY(pMsg->hWin);
      GUI_DrawGradientV(0, 0, NCode, Id, 0x00ffffff, 0x00B19983);
      
      GUI_SetColor(GUI_BLACK);
      GUI_SetFont(&GUI_Font13_1);
      GUI_DispStringAt("Matrícula do Operador",10, 15);
      GUI_DispStringAt("Número do Lote",       10, 40);
   break;
   case WM_NOTIFY_PARENT:
      Id    = WM_GetId(pMsg->hWinSrc);
      NCode = pMsg->Data.v;
      if(NCode == WM_NOTIFICATION_RELEASED){
         switch(Id){
         case GUI_ID_OK:
            GUI_EndDialog(pMsg->hWin, 0);
            wcreate_main();
            break;
         case GUI_ID_EDIT0:
            wEdit = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT0);
            iEdit = 1;
            EDIT_GetText(wEdit, (char*)abuffer, sizeof(abuffer));
            keyboard(e_char, (char*)abuffer, "Matrícula");
            break;
         case GUI_ID_EDIT1:
            wEdit = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT1);
            iEdit = 2;
            EDIT_GetText(wEdit, (char*)abuffer, sizeof(abuffer));
            keyboard(e_char, (char*)abuffer, "Nr. do lote");
            break;
         };
      };
      break;
   case MSG_KEYB_OK:
      EDIT_SetText(wEdit,(char*)pMsg->Data.p);
      strcpy( abuffer, (char*)pMsg->Data.p);
      switch(iEdit){
         case 1: I2C_WriteData(abuffer, 8, ADR_MATRICULA); break;
         case 2: I2C_WriteData(abuffer, 8, ADR_LOTE);      break;
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
void wcreate_ajuste(void) {
   WM_HWIN hDlg;
   Txy t;
   
   hDlg = GUI_CreateDialogBox(aajust, GUI_COUNTOF(aajust), cbAjust, WM_HBKWIN, 0, 0);
   Win_XY(hDlg, &t);
   WM_MoveWindow(hDlg, t.x, t.y);
}
/*------------------------------------------------------------
    EOF
--------------------------------------------------------------*/