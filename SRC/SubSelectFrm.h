//---------------------------------------------------------------------------

#ifndef SubSelectFrmH
#define SubSelectFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Vcl.TitleBarCtrls.hpp>
#include "BitBtn2.h"
//---------------------------------------------------------------------------
class TSubSelectForm : public TForm
{
__published:	// IDE 管理のコンポーネント
	TPanel *Panel1;
	TPanel *Panel2;
	TBitBtn2 *CancelBtn;
	TBitBtn2 *OkBtn;
	TListBox *ItemListBox;
	TPanel *Panel3;
	TPopupMenu *PopupMenu;
	TMenuItem *DeleteMenu;
	TTitleBarPanel *TitleBarPanel;
	void __fastcall CancelBtnClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall OkBtnClick(TObject *Sender);
	void __fastcall DeleteMenuClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:
public:
	__fastcall TSubSelectForm(TComponent* Owner);
public:
	String CtrlName;
	String Value;
};
//---------------------------------------------------------------------------
extern PACKAGE TSubSelectForm *SubSelectForm;
//---------------------------------------------------------------------------
#endif
