//---------------------------------------------------------------------------

#ifndef FirstMesFrmH
#define FirstMesFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Vcl.TitleBarCtrls.hpp>
#include "BitBtn2.h"
//---------------------------------------------------------------------------
class TFirstMesForm : public TForm
{
__published:	// IDE 管理のコンポーネント
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TCheckBox *NextCheckBox;
	TBitBtn2 *CloseBtn;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TTitleBarPanel *TitleBarPanel;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);
private:	// ユーザー宣言
public:		// ユーザー宣言
	__fastcall TFirstMesForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFirstMesForm *FirstMesForm;
//---------------------------------------------------------------------------
#endif
