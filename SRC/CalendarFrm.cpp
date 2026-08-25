//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "MainFrm.h"
#include "CalendarFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TBorderEdit"
#pragma link "BitBtn2"
#pragma resource "*.dfm"
TCalendarForm *CalendarForm;
//---------------------------------------------------------------------------
__fastcall TCalendarForm::TCalendarForm(TComponent* Owner)
	: TForm(Owner)
{
}
//-------------------------------------------------------------
//  機能     ：OKﾎﾞﾀﾝ押下時
//
//  関数定義 ：void __fastcall OKBtnClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TCalendarForm::OKBtnClick(TObject *Sender)
{
	TControl    *pCtrl;
	TBorderEdit *pEdit;
	//指定Editに日付ｾｯﾄ
	//年
	pCtrl       = MainForm->FindControlFromMainPanel(StdComponents[scYearEdit].Name);
	pEdit       = static_cast<TBorderEdit *>(pCtrl);
	pEdit->Text = MonthCalendar->Date.FormatString("yyyy");
	//月
	pCtrl       = MainForm->FindControlFromMainPanel(StdComponents[scMonthEdit].Name);
	pEdit       = static_cast<TBorderEdit *>(pCtrl);
	pEdit->Text = MonthCalendar->Date.FormatString("m");
	//日
	pCtrl       = MainForm->FindControlFromMainPanel(StdComponents[scDayEdit].Name);
	pEdit       = static_cast<TBorderEdit *>(pCtrl);
	pEdit->Text = MonthCalendar->Date.FormatString("d");

	Close();
}
//-------------------------------------------------------------
//  機能     ：ﾌｫｰﾑ作成時
//
//  関数定義 ：void __fastcall FormCreate(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TCalendarForm::FormCreate(TObject *Sender)
{
	OSVERSIONINFO OSInf;
	bool          IsVista = false;
	//今日の日付を得る
	TDateTime Now = TDateTime::CurrentDate();
	//ｶﾚﾝﾀﾞｰにｾｯﾄ
	MonthCalendar->Date = Now;
	//OS情報の取得
	OSInf.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&OSInf);
	//Vista以外はフォームの大きさをかえる
	if(OSInf.dwPlatformId == VER_PLATFORM_WIN32_NT)
	{
		if(OSInf.dwMajorVersion == 6)
		{
			IsVista = true;
		}
	}
	if(IsVista == false)
	{
		Width  = 180;
		Height = 224;
	}

}
//---------------------------------------------------------------------------

