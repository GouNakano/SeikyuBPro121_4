//---------------------------------------------------------------------------

#ifndef ComponentsFrmH
#define ComponentsFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "SeikyuBDef.h"
#include "BitBtn2.h"
#include <Vcl.TitleBarCtrls.hpp>
#include "TListView2.h"
//---------------------------------------------------------------------------
class TComponentsForm : public TForm
{
__published:	// IDE 管理のコンポーネント
	TPanel *Panel1;
	TPanel *Panel2;
	TBitBtn2 *CloseBtn;
	TBitBtn2 *FormatBtn;
	TListView2 *ListView;
	TTitleBarPanel *TitleBarPanel;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall CloseBtnClick(TObject *Sender);
	void __fastcall FormatBtnClick(TObject *Sender);
	void __fastcall ListViewDeletion(TObject *Sender, TListItem *Item);
	void __fastcall FormCreate(TObject *Sender);
private:	// ユーザー宣言
public:		// ユーザー宣言
	__fastcall TComponentsForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TComponentsForm *ComponentsForm;
//---------------------------------------------------------------------------
#endif
