#include "DIALOG.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>



WM_HWIN layer[2];//��������
WM_HWIN hItem_slave;//�����ƿ��Edit�͹�װ��Edit�ľ��
WM_HWIN EDIT_botttle;//��ƿ��Edit�ؼ��������
WM_HWIN EDIT_capacity;//��װ��Edit�ؼ��������

WM_HWIN hItem_bottle;//��ƿ��Text�ؼ����
WM_HWIN hItem_capacity;//��װ��Text�ؼ����

extern GUI_CONST_STORAGE GUI_FONT GUI_FontSong24;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontSong18x18;

const char confirm[] = "\xe7\xa1\xae\xe8\xae\xa4";//ȷ��
const char totalbottles[] = "\xe6\x80\xbb\xe7\x93\xb6\xe6\x95\xb0";//��ƿ��
const char capacity[] = "\xe7\x81\x8c\xe8\xa3\x85\xe5\xae\xb9\xe9\x87\x8f";//��װ����

char Edit_buff[10];//���ּ��̴����ַ���
char bottle_buff[10];//����ƿ���������ַ���
char capacity_buff[10];//�����趨�������ַ���

extern void Write_edit(char * buff);//д��ƿ��Edit������Edit
extern void Write_Bottletext(char * buff);//������ʾ������趨ƿ������
extern void Write_Capacitytext(char * buff);//������ʾ������趨��װ����
extern void change(char* to);


static void _cbDialog5(WM_MESSAGE * pMsg);//���ּ���
static void _cbDialog(WM_MESSAGE * pMsg);//��һ��ҳ��
#define Edit_SetText(Edit_buff)  EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_50), Edit_buff) ;			//���Edit�����ּ����ϵ�Edit�ؼ����ã��������ֵд������Edit�Ϳ�����
/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
/////��һ������ؼ�����
#define ID_WINDOW_0        (GUI_ID_USER + 0x20)
#define ID_BUTTON_0        (GUI_ID_USER + 0x21)
#define ID_EDIT_0        (GUI_ID_USER + 0x22)
#define ID_EDIT_1        (GUI_ID_USER + 0x23)
#define ID_TEXT_0        (GUI_ID_USER + 0x24)
#define ID_TEXT_1        (GUI_ID_USER + 0x25)
#define ID_TEXT_2        (GUI_ID_USER + 0x26)
#define ID_TEXT_3        (GUI_ID_USER + 0x27)
/////���ּ��̿ؼ�����
#define ID_FRAMEWIN_50      (GUI_ID_USER + 0x01)
#define ID_EDIT_50			(GUI_ID_USER + 0x02)
#define ID_BUTTON_50        (GUI_ID_USER + 0x03)
#define ID_BUTTON_51        (GUI_ID_USER + 0x04)
#define ID_BUTTON_52        (GUI_ID_USER + 0x05)
#define ID_BUTTON_53        (GUI_ID_USER + 0x06)
#define ID_BUTTON_54        (GUI_ID_USER + 0x07)
#define ID_BUTTON_55        (GUI_ID_USER + 0x08)
#define ID_BUTTON_56        (GUI_ID_USER + 0x09)
#define ID_BUTTON_57        (GUI_ID_USER + 0x0A)
#define ID_BUTTON_58        (GUI_ID_USER + 0x0B)
#define ID_BUTTON_59        (GUI_ID_USER + 0x0C)
#define ID_BUTTON_5A        (GUI_ID_USER + 0x0D)
#define ID_BUTTON_5B        (GUI_ID_USER + 0x0E)
#define ID_BUTTON_5C        (GUI_ID_USER + 0x0F)
// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "moni", ID_WINDOW_0, 0, 0, 800, 480, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "ȷ��", ID_BUTTON_0, 38, 359, 129, 85, 0, 0x0, 0 },
  { EDIT_CreateIndirect, "Edit1", ID_EDIT_0, 315, 62, 115, 50, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit2", ID_EDIT_1, 315, 141, 120, 50, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "����1", ID_TEXT_0, 140, 60, 110, 40, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "����2", ID_TEXT_1, 140, 140, 80, 40, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "�ѹ�װ", ID_TEXT_2, 4, 60, 100, 40, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "��ƿ��", ID_TEXT_3, 5, 140, 100, 40, 0, 0x64, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};
static const GUI_WIDGET_CREATE_INFO _aDialogCreate5[] = {
		{ FRAMEWIN_CreateIndirect, "number", ID_FRAMEWIN_50, 400, 50, 350, 405, 0, 0x64, 0 },
		{ EDIT_CreateIndirect, "Edit", ID_EDIT_50, 5, 5, 141, 40, 0, 0x64, 0 },
		{ BUTTON_CreateIndirect, "0", ID_BUTTON_50, 134, 298, 80, 65, 0, 0x0, 0 },
		{ BUTTON_CreateIndirect, "1", ID_BUTTON_51, 20, 60, 80, 65, 0, 0x0, 0 },
		{ BUTTON_CreateIndirect, "2", ID_BUTTON_52, 130, 60, 80, 65, 0, 0x0, 0 },
		{ BUTTON_CreateIndirect, "3", ID_BUTTON_53, 240, 60, 80, 65, 0, 0x0, 0 },
		{ BUTTON_CreateIndirect, "4", ID_BUTTON_54, 20, 140, 80, 65, 0, 0x0, 0 },
		{ BUTTON_CreateIndirect, "5", ID_BUTTON_55, 130, 140, 80, 65, 0, 0x0, 0 },
		{ BUTTON_CreateIndirect, "6", ID_BUTTON_56, 240, 140, 78, 65, 0, 0x0, 0 },
		{ BUTTON_CreateIndirect, "7", ID_BUTTON_57, 20, 220, 80, 65, 0, 0x0, 0 },
		{ BUTTON_CreateIndirect, "8", ID_BUTTON_58, 130, 220, 80, 65, 0, 0x0, 0 },
		{ BUTTON_CreateIndirect, "9", ID_BUTTON_59, 240, 220, 80, 65, 0, 0x0, 0 },
		{ BUTTON_CreateIndirect, "ESC", ID_BUTTON_5A, 20, 300, 80, 65, 0, 0x0, 0 },
		{ BUTTON_CreateIndirect, "Delete", ID_BUTTON_5B, 240, 300, 80, 65, 0, 0x0, 0 },
		{ BUTTON_CreateIndirect, "OK", ID_BUTTON_5C, 160, 5, 160, 43, 0, 0x0, 0 },
		// USER START (Optionally insert additional widgets)
		// USER END
};
/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'ȷ��'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
	BUTTON_SetFont(hItem, &GUI_FontSong24);
	BUTTON_SetText(hItem, confirm);
    //
    // Initialization of 'Edit1'
    //
	EDIT_botttle = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
	EDIT_SetText(EDIT_botttle, "50");
	EDIT_SetTextAlign(EDIT_botttle, GUI_TA_LEFT | GUI_TA_VCENTER);
	EDIT_SetFont(EDIT_botttle, GUI_FONT_D32);
    //
    // Initialization of 'Edit2'
    //
	EDIT_capacity = WM_GetDialogItem(pMsg->hWin, ID_EDIT_1);
	EDIT_SetText(EDIT_capacity, "100");
	EDIT_SetTextAlign(EDIT_capacity, GUI_TA_LEFT | GUI_TA_VCENTER);
	EDIT_SetFont(EDIT_capacity, GUI_FONT_D32);
    //
    // Initialization of '����1'
    //
	hItem_bottle = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
	TEXT_SetFont(hItem_bottle, GUI_FONT_32B_1);
	TEXT_SetText(hItem_bottle, "Edit1");
    //
    // Initialization of '����2'
    //
	hItem_capacity = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
	TEXT_SetFont(hItem_capacity, GUI_FONT_32B_1);
	TEXT_SetText(hItem_capacity, "Edit2");
    //
    // Initialization of '�ѹ�װ'
    //
	hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
	TEXT_SetFont(hItem, &GUI_FontSong24);
	TEXT_SetText(hItem, totalbottles);
	TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    //
    // Initialization of '��ƿ��'
    //
	hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
	TEXT_SetFont(hItem, &GUI_FontSong24);
	TEXT_SetText(hItem, capacity);
	TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_BUTTON_0: // Notifications sent by 'ȷ��'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
		  Write_Bottletext(bottle_buff);
		  Write_Capacitytext(capacity_buff);
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_EDIT_0: // Notifications sent by 'Edit1'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
		  hItem_slave = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);//�ȵ����EDit1 �������ľ��
		  GUI_CreateDialogBox(_aDialogCreate5, GUI_COUNTOF(_aDialogCreate5), _cbDialog5, WM_HBKWIN, 0, 0);////�������ּ���
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_EDIT_1: // Notifications sent by 'Edit2'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
		  hItem_slave = WM_GetDialogItem(pMsg->hWin, ID_EDIT_1);//�ȵ����EDit2 �������ľ��
		  GUI_CreateDialogBox(_aDialogCreate5, GUI_COUNTOF(_aDialogCreate5), _cbDialog5, WM_HBKWIN, 0, 0);////�������ּ���
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}
static void _cbDialog5(WM_MESSAGE * pMsg) {
	WM_HWIN hItem;
	WM_HWIN Numbpad;//���ּ��̵ľ��
	int     NCode;
	int     Id;
	int     i;
	unsigned short int buff_length = 0;

	static U8 back = 0;
	static U16 setting_ml = 300;//Ĭ�Ϲ�װ��������λml

	Numbpad = pMsg->hWin;
	switch (pMsg->MsgId) {
	case WM_INIT_DIALOG:
		for (i = 0x01; i <= 0x0F; i++) {
			hItem = WM_GetDialogItem(Numbpad, GUI_ID_USER + i);
			BUTTON_SetFocussable(hItem, 0);/* �������а�ť���Խ� */
			// BUTTON_SetFont(hItem, GUI_FONT_24_1);
		}WM_GetDialogItem(Numbpad, GUI_ID_USER + 0XEB);

		//
		// Initialization of 'number'
		//
		hItem = pMsg->hWin;
		FRAMEWIN_SetText(hItem, "INPUT");
		FRAMEWIN_SetFont(hItem, GUI_FONT_24B_1);
		FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
		//
		// Initialization of 'Edit'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_50);
		EDIT_SetText(hItem, "");
		EDIT_SetFont(hItem, GUI_FONT_D24X32);
		EDIT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
		//
		// Initialization of '0'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_50);
		BUTTON_SetFont(hItem, GUI_FONT_D24X32);
		BUTTON_SetText(hItem, "0");
		//
		// Initialization of '1'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_51);
		BUTTON_SetText(hItem, "1");
		BUTTON_SetFont(hItem, GUI_FONT_D32);
		//
		// Initialization of '2'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_52);
		BUTTON_SetFont(hItem, GUI_FONT_D32);
		BUTTON_SetText(hItem, "2");
		//
		// Initialization of '3'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_53);
		BUTTON_SetFont(hItem, GUI_FONT_D32);
		BUTTON_SetText(hItem, "3");
		//
		// Initialization of '4'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_54);
		BUTTON_SetFont(hItem, GUI_FONT_D24X32);
		BUTTON_SetText(hItem, "4");
		//
		// Initialization of '5'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_55);
		BUTTON_SetFont(hItem, GUI_FONT_D32);
		BUTTON_SetText(hItem, "5");
		//
		// Initialization of '6'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_56);
		BUTTON_SetFont(hItem, GUI_FONT_D32);
		BUTTON_SetText(hItem, "6");
		//
		// Initialization of '7'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_57);
		BUTTON_SetText(hItem, "7");
		BUTTON_SetFont(hItem, GUI_FONT_D32);
		//
		// Initialization of '8'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_58);
		BUTTON_SetText(hItem, "8");
		BUTTON_SetFont(hItem, GUI_FONT_D32);
		//
		// Initialization of '9'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_59);
		BUTTON_SetText(hItem, "9");
		BUTTON_SetFont(hItem, GUI_FONT_D32);
		//
		// Initialization of 'ESC'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_5A);
		BUTTON_SetText(hItem, "ESC");
		BUTTON_SetFont(hItem, GUI_FONT_24B_1);
		//
		// Initialization of 'Delete'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_5B);
		BUTTON_SetText(hItem, "Delete");
		BUTTON_SetFont(hItem, GUI_FONT_24B_1);
		//
		// Initialization of 'OK'
		//
		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_5C);
		BUTTON_SetFont(hItem, GUI_FONT_32B_1);
		BUTTON_SetText(hItem, "OK");
		// USER START (Optionally insert additional code for further widget initialization)
		// USER END
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (Id) {
		case ID_EDIT_50: // Notifications sent by 'Edit'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:


				// USER END
				break;
			case WM_NOTIFICATION_RELEASED:

				// USER END
				break;
			case WM_NOTIFICATION_VALUE_CHANGED:

				// USER END
				break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
			}
			break;
		case ID_BUTTON_50: // Notifications sent by '0'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED://�ؼ������

				if (strlen(Edit_buff) < 4)//�������ֻ������4��0
					strcat(Edit_buff, "0");//����0��ʱ��ѡ�0������ַ����ŵ�Edit_buff�ַ�����������
				Edit_SetText(Edit_buff);//ͬʱ���¼�����Edit��ֵ
				// USER END
				break;
			case WM_NOTIFICATION_RELEASED://�ؼ����ͷ�

				// USER END
				break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
			}
			break;
		case ID_BUTTON_51: // Notifications sent by '1'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:

				if (strlen(Edit_buff) < 4)
					strcat(Edit_buff, "1");
				Edit_SetText(Edit_buff);
				// USER END
				break;
			case WM_NOTIFICATION_RELEASED:

				// USER END
				break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
			}
			break;
		case ID_BUTTON_52: // Notifications sent by '2'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:

				if (strlen(Edit_buff) < 10)
					strcat(Edit_buff, "2");
				Edit_SetText(Edit_buff);
				// USER END
				break;
			case WM_NOTIFICATION_RELEASED:

				// USER END
				break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
			}
			break;
		case ID_BUTTON_53: // Notifications sent by '3'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:

				if (strlen(Edit_buff) < 10)
					strcat(Edit_buff, "3");
				Edit_SetText(Edit_buff);
				// USER END
				break;
			case WM_NOTIFICATION_RELEASED:

				// USER END
				break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
			}
			break;
		case ID_BUTTON_54: // Notifications sent by '4'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:

				if (strlen(Edit_buff) < 10)
					strcat(Edit_buff, "4");
				Edit_SetText(Edit_buff);
				// USER END
				break;
			case WM_NOTIFICATION_RELEASED:

				// USER END
				break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
			}
			break;
		case ID_BUTTON_55: // Notifications sent by '5'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:

				if (strlen(Edit_buff) < 10)
					strcat(Edit_buff, "5");
				Edit_SetText(Edit_buff);
				// USER END
				break;
			case WM_NOTIFICATION_RELEASED:

				// USER END
				break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
			}
			break;
		case ID_BUTTON_56: // Notifications sent by '6'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:

				if (strlen(Edit_buff) < 10)
					strcat(Edit_buff, "6");
				Edit_SetText(Edit_buff);
				// USER END
				break;
			case WM_NOTIFICATION_RELEASED:

				// USER END
				break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
			}
			break;
		case ID_BUTTON_57: // Notifications sent by '7'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:

				if (strlen(Edit_buff) < 10)
					strcat(Edit_buff, "7");
				Edit_SetText(Edit_buff);
				// USER END
				break;
			case WM_NOTIFICATION_RELEASED:

				// USER END
				break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
			}
			break;
		case ID_BUTTON_58: // Notifications sent by '8'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:

				if (strlen(Edit_buff) < 10)
					strcat(Edit_buff, "8");
				Edit_SetText(Edit_buff);
				// USER END
				break;
			case WM_NOTIFICATION_RELEASED:

				// USER END
				break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
			}
			break;
		case ID_BUTTON_59: // Notifications sent by '9'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:

				if (strlen(Edit_buff) < 10)
					strcat(Edit_buff, "9");
				Edit_SetText(Edit_buff);
				// USER END
				break;
			case WM_NOTIFICATION_RELEASED:

				// USER END
				break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
			}
			break;
		case ID_BUTTON_5A: // Notifications sent by 'ESC'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:

				GUI_EndDialog(pMsg->hWin, 0);//������ǰ����
				// USER END
				break;
			case WM_NOTIFICATION_RELEASED:

				// USER END
				break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
			}
			break;
		case ID_BUTTON_5B: // Notifications sent by 'Delete'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:

				if (strlen(Edit_buff)> 0)//�ж��Ƿ������������ַ��������˲��ܼ�ȥ��������ܻ�����ж�
				{
					buff_length = strlen(Edit_buff);
					Edit_buff[buff_length - 1] = '\0';//��������ּ����ϴ����ַ����ģ��൱�ڼ�ȥһ���ַ�
					Edit_SetText(Edit_buff);//Ȼ����¼����ַ����Edit
				}
				// USER END
				break;
			case WM_NOTIFICATION_RELEASED:

				// USER END
				break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
			}
			break;
		case ID_BUTTON_5C: // Notifications sent by 'OK'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:

				Write_edit(Edit_buff);				//�����ּ����ϵ���ֵд�뵽Edit��	
				memset(Edit_buff, '\0', sizeof Edit_buff);//������һ���ڴ�ռ�ȫ������Ϊĳ���ַ���һ�����ڶԶ�����ַ������г�ʼ��Ϊ�� ����\0��
				EDIT_SetText(WM_GetDialogItem(pMsg->hWin, ID_EDIT_50), "");//�����ּ��̵�Edit��Ϊ�հ�

				//WM_HideWindow(layer[5]);
				GUI_EndDialog(pMsg->hWin, 0);//��������С����
				// USER END
				break;
			case WM_NOTIFICATION_RELEASED:

				// USER END
				break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
			}
			break;
			// USER START (Optionally insert additional code for further Ids)
			// USER END
		}
		break;

		// USER END
	default:
		WM_DefaultProc(pMsg);
		break;
	}
}
/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       Createmoni
*/

void Write_edit(char * edit_buff)
{
	if (Edit_buff[0] != '\0')
		edit_buff = Edit_buff;
	if (EDIT_botttle == hItem_slave)
	{
		strcpy(bottle_buff, Edit_buff);//����������ƿ��Edit�����Eidt��ֵ��ֵ��bottle_buff����
	}
	else if (EDIT_capacity == hItem_slave)
	{
		strcpy(capacity_buff, Edit_buff);////�������˹�װ��Edit�����Eidt��ֵ��ֵ��capacity_buff����
	}
	EDIT_SetText(hItem_slave, edit_buff);//�����ּ��̵�ֵ���µ���ǰ�����Edit��
}
void Write_Bottletext(char * Bottle_buff)//��bottle_buff��������ַ������µ�Text����ʾ��������ʾ�趨��ƿ��
{
	if (bottle_buff[0] != '\0')
		Bottle_buff = bottle_buff;
	TEXT_SetText(hItem_bottle, Bottle_buff);

}

void Write_Capacitytext(char * Capacity_buff)//��capacity_buff��������ַ������µ�Text����ʾ��������ʾ��װ����
{
	if (capacity_buff[0] != '\0')
		Capacity_buff = capacity_buff;
	
	TEXT_SetText(hItem_capacity, Capacity_buff);
}
WM_HWIN Createmoni(void);
WM_HWIN Createmoni(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}
WM_HWIN Createnumber(void);
WM_HWIN Createnumber(void) {
	WM_HWIN hWin;

	hWin = GUI_CreateDialogBox(_aDialogCreate5, GUI_COUNTOF(_aDialogCreate5), _cbDialog5, WM_HBKWIN, 0, 0);
	return hWin;
}
void MainTask(void)
{
	GUI_Init();		//GUI��ʼ��	
	GUI_UC_SetEncodeUTF8();
	//Createmoni();//�Զ�������ƣ������޸�
	layer[1] = Createnumber();
	layer[0] = Createmoni();
	WM_HideWindow(layer[1]);//�������ּ���
	while (1)
	{
		GUI_Delay(200);

	}
}
// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
