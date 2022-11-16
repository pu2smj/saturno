/*--------------------------------------------------------
  * @file........ wsetup.c
  * @author...... renato
  * @description. 
  --------------------------------------------------------
*/
   #include "RTL.h"
   #include "wsetup.h"
   #include "definicoes.h" 
   
   /*extern variables ----------------------------------*/
   extern TMachine *pMac;
   extern TPressure *pPres;
   
   WM_HWIN hEdit;
   uint8_t nEdit;

/*---------------------------------------------------------
 function.....: 
 description..: 
----------------------------------------------------------*/
void cbSetup(WM_MESSAGE * pMsg) {
   WM_HWIN hItem;
   int     NCode;
   int     Id;
   
   static uint8_t itemp;
   static char  buffer[20]; 
   
   switch (pMsg->MsgId) {
   case WM_INIT_DIALOG:
      FRAMEWIN_SetTitleHeight(pMsg->hWin, 17);
      FRAMEWIN_SetFont(pMsg->hWin, GUI_FONT_13_1); 
      FRAMEWIN_SetText(pMsg->hWin, "Dados da Pressão");

      RestoreMMHG(pPres);
   
      sprintf(buffer, "%02u", pPres->minimum);
      hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT0);
      EDIT_SetText(hItem, buffer);
      EDIT_SetFont(hItem, &GUI_Font13_1);

      sprintf(buffer, "%02u", pPres->maximo);
      hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT1);
      EDIT_SetText(hItem, buffer);
      EDIT_SetFont(hItem, &GUI_Font13_1);

      //setpoint = 0 == modo mim/max
      //setpoint > 0 == setpoint/histerese
      sprintf(buffer, "%02u", pPres->setpoint);
      hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT2);
      EDIT_SetText(hItem, buffer);
      EDIT_SetFont(hItem, &GUI_Font13_1);

      sprintf(buffer, "%02u", pPres->histerese);
      hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT3);
      EDIT_SetText(hItem, buffer);
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
      GUI_DispStringAt("Pressão Minima", 12, 43);
      GUI_DispStringAt("Pressão Máxima", 12, 73);
      GUI_DispStringAt("Set Point",      12, 103);
	   GUI_DispStringAt("Histerese",      12, 133);
      GUI_DispStringAt("P Minima",       12, 133);
	   GUI_DispStringAt("P Máxima",       12, 163);
//      GUI_DispStringAt(pPres->nMin,      50, 133);
//	   GUI_DispStringAt(pPres->nMax,     50, 163);
   break;
   case WM_NOTIFY_PARENT:
      Id    = WM_GetId(pMsg->hWinSrc);
      NCode = pMsg->Data.v;
      if(NCode == WM_NOTIFICATION_RELEASED){
         switch(Id){
         case GUI_ID_OK:
            GUI_EndDialog(pMsg->hWin, 0);
            wmain();
            break;
         case GUI_ID_EDIT0:
            hEdit = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT0);
            nEdit = 1;
            EDIT_GetText(hEdit, (char*)buffer, sizeof(buffer));
            keyboard(e_char, (char*)buffer, "Pressão (mmHg)");
            break;
         case GUI_ID_EDIT1:
            hEdit = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT1);
            nEdit = 2;
            EDIT_GetText(hEdit, (char*)buffer, sizeof(buffer));
            keyboard(e_char, (char*)buffer, "Pressão (mmHg)");
            break;
         case GUI_ID_EDIT2:
            hEdit = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT2);
            nEdit = 3;
            EDIT_GetText(hEdit, (char*)buffer, sizeof(buffer));
            keyboard(e_char, (char*)buffer, "SetPoint");
            break;
         case GUI_ID_EDIT3:
            hEdit = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT3);
            nEdit = 4;
            EDIT_GetText(hEdit, (char*)buffer, sizeof(buffer));
            keyboard(e_char, (char*)buffer, "Histerese");
            break;			
         };
      };
   break;
   case MSG_KEYB_OK:
      strcpy(buffer, (char*)pMsg->Data.p);
      EDIT_SetText(hEdit,(char*)pMsg->Data.p);
      switch(nEdit){
         case 1:
            pPres->minimum = atoi( (char*)pMsg->Data.p );
            NormalizeMMHG(pPres, t_minimum);
         break;
         case 2:
            pPres->maximo = atoi( (char*)pMsg->Data.p );
            NormalizeMMHG(pPres, t_maximo);
         break;
         case 3: 
            pPres->setpoint = atoi( (char*)pMsg->Data.p );
            NormalizeMMHG(pPres, t_setpoint);
         break;
		   case 4:
            pPres->histerese = atoi( (char*)pMsg->Data.p );
            NormalizeMMHG(pPres, t_histerese);
         break;
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
   
   hDlg = GUI_CreateDialogBox(aSetup, GUI_COUNTOF(aSetup), cbSetup, WM_HBKWIN, 0, 0);
   Win_XY(hDlg, &t);
   WM_MoveWindow(hDlg, t.x, t.y);
}
/*---------------------------------------------------------

----------------------------------------------------------*/
