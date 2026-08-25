//---------------------------------------------------------------------------

#ifndef DispSettingFrmH
#define DispSettingFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "TListView2.h"
//---------------------------------------------------------------------------
class TDispSettingForm : public TForm
{
__published:	// IDE 管理のコンポーネント
	TPanel *Panel1;
	TPanel *Panel2;
	TButton *OkBtn;
	TButton *CancelBtn;
	TPanel *Panel3;
	TListView2 *ObjectListView;
	void __fastcall CancelBtnClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall OkBtnClick(TObject *Sender);
	void __fastcall ObjectListViewDeletion(TObject *Sender, TListItem *Item);
private:	// ユーザー宣言
public:		// ユーザー宣言
	__fastcall TDispSettingForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDispSettingForm *DispSettingForm;
//---------------------------------------------------------------------------
#endif
