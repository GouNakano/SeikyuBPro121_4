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
//---------------------------------------------------------------------------
class TSubSelectForm : public TForm
{
__published:	// IDE 管理のコンポーネント
	TPanel *Panel1;
	TPanel *Panel2;
	TButton *CancelBtn;
	TButton *OkBtn;
	TListBox *ItemListBox;
	TPanel *Panel3;
	TPopupMenu *PopupMenu;
	TMenuItem *DeleteMenu;
	void __fastcall CancelBtnClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall OkBtnClick(TObject *Sender);
	void __fastcall DeleteMenuClick(TObject *Sender);
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
