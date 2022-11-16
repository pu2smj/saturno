 /*-----------------------------------------------------------------
   Copyright (c)
   file.........: 
   description..: 
   user.........: 
   -----------------------------------------------------------------*/
   #include "RTL.h"
   #include "wmain.h"
   #include "definicoes.h" 
 
   WM_HWIN h_Edit;
   uint8_t n_Edit;

/*---------------------------------------------------------
 function.....: 
 description..: 
----------------------------------------------------------*/
void cbSoluto(WM_MESSAGE * pMsg) {
   WM_HWIN hItem;
   int     NCode;
   int     Id;
   uint8_t ftemp;
   char abuffer[30];
   
   switch (pMsg->MsgId) {
   case WM_INIT_DIALOG:
      FRAMEWIN_SetTitleHeight(pMsg->hWin, 17);
      FRAMEWIN_SetFont(pMsg->hWin, GUI_FONT_13_1); 
      FRAMEWIN_SetText(pMsg->hWin, "Dados do Soluto");
    //  FRAMEWIN_AddCloseButton(pMsg->hWin, FRAMEWIN_BUTTON_RIGHT,  0);

      sprintf(abuffer, "%4.2f", I2C_ReadFloat(ADR_PUMP_CONC));
      hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT0);
      EDIT_SetText(hItem, abuffer);
      EDIT_SetFont(hItem, &GUI_Font13_1);

      sprintf(abuffer, "%4.2f", I2C_ReadFloat(ADR_PUMP_FLOW));
      hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT1);
      EDIT_SetText(hItem, abuffer);
      EDIT_SetFont(hItem, &GUI_Font13_1);

      sprintf(abuffer, "%2.5f", I2C_ReadFloat(ADR_PUMP_J));
      hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT2);
      EDIT_SetText(hItem, abuffer);
      EDIT_SetFont(hItem, &GUI_Font13_1);

      sprintf(abuffer, "%2.5f", I2C_ReadFloat(ADR_PUMP_P));
      hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT3);
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
      GUI_DispStringAt("Nome do Soluto",  10, 19);
      GUI_DispStringAt("Concentração (%)",10, 44);
      GUI_DispStringAt("Fator J",         10, 68);
      GUI_DispStringAt("Fator P",         10, 93);
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
            h_Edit = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT0);
            n_Edit = 1;
            EDIT_GetText(h_Edit, (char*)abuffer, sizeof(abuffer));
            keyboard(e_char, (char*)abuffer, "Produto");
            break;
         case GUI_ID_EDIT1:
            h_Edit = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT1);
            n_Edit = 2;
            EDIT_GetText(h_Edit, (char*)abuffer, sizeof(abuffer));
            keyboard(e_char, (char*)abuffer, "Concentracao");
            break;
         case GUI_ID_EDIT2:
            h_Edit = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT2);
            n_Edit = 3;
            EDIT_GetText(h_Edit, (char*)abuffer, sizeof(abuffer));
            keyboard(e_char, (char*)abuffer, "Fator J");
            break;
         case GUI_ID_EDIT3:
            h_Edit = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT3);
            n_Edit = 4;
            EDIT_GetText(h_Edit, (char*)abuffer, sizeof(abuffer));
            keyboard(e_char, (char*)abuffer, "Fator P");
            break;
         };
      };
      break;
   case MSG_KEYB_OK:
      EDIT_SetText(h_Edit,(char*)pMsg->Data.p);
      //ftemp = atof((char*)pMsg->Data.p);
      switch(n_Edit){
         case 1: I2C_WriteFloat((char*)pMsg->Data.p, ADR_PUMP_CONC); break;
         case 2: I2C_WriteFloat((char*)pMsg->Data.p, ADR_PUMP_FLOW); break;
         case 3: I2C_WriteFloat((char*)pMsg->Data.p, ADR_PUMP_J);    break;
         case 4: I2C_WriteFloat((char*)pMsg->Data.p, ADR_PUMP_P);    break;
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
void wcreate_setup_soluto(void){
   WM_HWIN hDlg;
   Txy t;
   
   hDlg = GUI_CreateDialogBox(aSoluto, GUI_COUNTOF(aSoluto), cbSoluto, WM_HBKWIN, 0, 0);
   Win_XY(hDlg, &t);
   WM_MoveWindow(hDlg, t.x, t.y);
}
/*---------------------------------------------------------

----------------------------------------------------------*/
