//---------------------------------------------------------------------------

#ifndef LabelModifyFrmH
#define LabelModifyFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TBaseEdit.h"
#include "BitBtn2.h"
//---------------------------------------------------------------------------
class TLabelModifyForm : public TForm
{
__published:	// IDE 管理のコンポーネント
	TBaseEdit *LabelValEdit;
	TBitBtn2 *ModifyBtn;
	TBitBtn2 *CancelBtn;
	void __fastcall CancelBtnClick(TObject *Sender);
	void __fastcall ModifyBtnClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:
	TMessageEvent pEve;
public:
	__fastcall TLabelModifyForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLabelModifyForm *LabelModifyForm;
//---------------------------------------------------------------------------
#endif
