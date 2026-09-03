//---------------------------------------------------------------------------

#ifndef FigureSettingFrmH
#define FigureSettingFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Vcl.TitleBarCtrls.hpp>
#include "BitBtn2.h"
//---------------------------------------------------------------------------
class TFigureSettingForm : public TForm
{
__published:	// IDE 管理のコンポーネント
	TLabel *Label1;
	TEdit *FigureEdit;
	TLabel *Label2;
	TBitBtn2 *OkBtn;
	TBitBtn2 *CancelBtn;
	TTitleBarPanel *TitleBarPanel;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall OkBtnClick(TObject *Sender);
	void __fastcall CancelBtnClick(TObject *Sender);
private:
	TMessageEvent pEve;
public:
	__fastcall TFigureSettingForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFigureSettingForm *FigureSettingForm;
//---------------------------------------------------------------------------
#endif
