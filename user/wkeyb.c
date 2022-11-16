/*--------------------------------------------------------
  * @file........ wmain.c
  * @author...... renato
  * @description. main screen
  --------------------------------------------------------
*/
   #include "global_includes.h"
   #include "wkeyb.h"

/*---------------------------------------------------------
 function.....: cbKeyb
 description..: callback of keyboard
 dependencie..: keyboard
----------------------------------------------------------*/ 
void cbKeyb(WM_MESSAGE * pMsg) {
   GUI_RECT   r;
   WM_HWIN    hSource, hItem;
   WM_MESSAGE Msg;
   int        NCode, Id;   
   char       lbuffer[30];
   
   switch (pMsg->MsgId) {
   case MSG_KEYB_SET_DATA:
       hItem = WM_GetDialogItem(pMsg->hWin,GUI_ID_EDIT0);
       EDIT_SetText(hItem,(char*)pMsg->Data.p);
       hSource = pMsg->hWinSrc;
   break;
   case WM_PAINT:
       hItem = WM_GetDialogItem(pMsg->hWin, (GUI_ID_USER+16));
       BUTTON_SetBkColor(hItem, BUTTON_CI_UNPRESSED, GUI_YELLOW);
   
       hItem = WM_GetDialogItem(pMsg->hWin, (GUI_ID_USER+17));
       BUTTON_SetBkColor(hItem, BUTTON_CI_UNPRESSED, GUI_YELLOW);
   
       hItem = WM_GetDialogItem(pMsg->hWin, (GUI_ID_USER+18));
       BUTTON_SetBkColor(hItem, BUTTON_CI_UNPRESSED, GUI_YELLOW);
   
       hItem = WM_GetDialogItem(pMsg->hWin, (GUI_ID_USER+19));
       BUTTON_SetBkColor(hItem, BUTTON_CI_UNPRESSED, GUI_YELLOW);
   
       hItem = WM_GetDialogItem(pMsg->hWin, (GUI_ID_USER+20));
       BUTTON_SetBkColor(hItem, BUTTON_CI_UNPRESSED, GUI_YELLOW);
   
       hItem = WM_GetDialogItem(pMsg->hWin, (GUI_ID_USER+21));
       BUTTON_SetBkColor(hItem, BUTTON_CI_UNPRESSED, GUI_YELLOW);
   
       hItem = WM_GetDialogItem(pMsg->hWin, (GUI_ID_USER+22));
       BUTTON_SetBkColor(hItem, BUTTON_CI_UNPRESSED, GUI_YELLOW);
   
       hItem = WM_GetDialogItem(pMsg->hWin, (GUI_ID_USER+23));
       BUTTON_SetBkColor(hItem, BUTTON_CI_UNPRESSED, GUI_YELLOW);
       
       hItem = WM_GetDialogItem(pMsg->hWin, (GUI_ID_USER+24));
       BUTTON_SetBkColor(hItem, BUTTON_CI_UNPRESSED, GUI_YELLOW);
       
       hItem = WM_GetDialogItem(pMsg->hWin, (GUI_ID_USER+25));
       BUTTON_SetBkColor(hItem, BUTTON_CI_UNPRESSED, GUI_YELLOW);
       
       hItem = WM_GetDialogItem(pMsg->hWin, (GUI_ID_USER+26));
       BUTTON_SetBkColor(hItem, BUTTON_CI_UNPRESSED, GUI_YELLOW);
       
       hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_BUTTON8);
       BUTTON_SetBkColor(hItem, BUTTON_CI_UNPRESSED, GUI_GREEN);
       
       hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_BUTTON9);
       BUTTON_SetBkColor(hItem, BUTTON_CI_UNPRESSED, GUI_RED);
   break;
   case WM_INIT_DIALOG:
      BUTTON_SetFocussable(hItem, 0);               /* Set all buttons non focussable */
   break;
   case WM_NOTIFY_PARENT:
      Id    = WM_GetId(pMsg->hWinSrc);      /* Id of widget */
      NCode = pMsg->Data.v;                 /* Notification code */
      hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT0);
      switch (NCode) {
      case WM_NOTIFICATION_RELEASED:
         if ((Id >= GUI_ID_USER) && (Id <= (GUI_ID_USER + GUI_COUNTOF(aKeyb) - 1))) {
            int Key;
            char acBuffer[2];
            BUTTON_GetText(pMsg->hWinSrc, acBuffer, sizeof(acBuffer)); /* Get the text of the button */
            Key = acBuffer[0];
            EDIT_AddKey(hItem, Key); 
         };
         if (Id == GUI_ID_OK){
            //restore buffer with new value
            EDIT_GetText(hItem, lbuffer, EDIT_GetNumChars(hItem)+1 );
            Msg.MsgId  = MSG_KEYB_OK;
            Msg.Data.p = lbuffer;
            WM_BroadcastMessage(&Msg);
            GUI_EndDialog(pMsg->hWin, 0);
         };
         if(Id == GUI_ID_BUTTON9){
            EDIT_SetText(hItem,"");
         };
         if(Id == GUI_ID_BUTTON8){
            if(EDIT_GetNumChars(hItem) > 0){
               EDIT_GetText(hItem, lbuffer, EDIT_GetNumChars(hItem));
               EDIT_SetText(hItem, lbuffer);
            };
         };
      break;
     }
   default:
     WM_DefaultProc(pMsg);
   }
}
/*---------------------------------------------------------
 function.....: keyboard
 description..: numerical and key pads
 dependencie..: 
----------------------------------------------------------*/
void keyboard(TTypeEdit ted, char* buf, const char* pText){
   WM_HWIN hWin, hEdit;
   
   hWin = GUI_CreateDialogBox(aKeyb, GUI_COUNTOF(aKeyb), cbKeyb, WM_HBKWIN, 0, 0);
   FRAMEWIN_SetText(hWin, pText);
   FRAMEWIN_SetTitleHeight(hWin, 17);
   FRAMEWIN_SetFont(hWin, GUI_FONT_13_1); 
   FRAMEWIN_AddCloseButton(hWin, FRAMEWIN_BUTTON_RIGHT, 1);
   
   hEdit = EDIT_CreateEx(8, 35, 180, 25, hWin, WM_CF_SHOW, 0, GUI_ID_EDIT0, 30);
   EDIT_SetFont(hEdit, &GUI_Font8x16);
   EDIT_SetTextColor(hEdit, EDIT_CI_ENABLED, GUI_DARKMAGENTA);
   EDIT_SetTextAlign(hEdit, GUI_TA_CENTER|GUI_TA_VCENTER);
   EDIT_SetText(hEdit,(char*)buf);
   
   //if(mode == 0) EDIT_SetDecMode(hEdit, I32 Value, 0, 65535, 0, 0);
   //   return hWin;
   
   WM_MakeModal(hWin);
}
/*------------------------------------------------------------
    EOF
--------------------------------------------------------------*/