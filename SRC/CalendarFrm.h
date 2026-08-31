//---------------------------------------------------------------------------

#ifndef CalendarFrmH
#define CalendarFrmH
#include <System.Classes.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.StdCtrls.hpp>
#include "TBorderEdit.h"
#include "BitBtn2.h"
#include <Vcl.TitleBarCtrls.hpp>
////---------------------------------------------------------------------------
//#include <Classes.hpp>
//#include <Controls.hpp>
//#include <StdCtrls.hpp>
//#include <Forms.hpp>
//#include <ComCtrls.hpp>
//#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TCalendarForm : public TForm
{
__published:	// IDE 管理のコンポーネント
	TMonthCalendar *MonthCalendar;
	TPanel *Panel1;
	TPanel *Panel2;
	TBitBtn2 *OKBtn;
	TBitBtn2 *CancelBtn;
	TTitleBarPanel *TitleBarPanel;
	void __fastcall OKBtnClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:
public:		// ユーザー宣言
	__fastcall TCalendarForm(TComponent* Owner);
public:
	//日付設定対象Edit
	TEdit *RefEdit;
};
//---------------------------------------------------------------------------
extern PACKAGE TCalendarForm *CalendarForm;
//---------------------------------------------------------------------------
#endif
