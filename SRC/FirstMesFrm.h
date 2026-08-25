//---------------------------------------------------------------------------

#ifndef FirstMesFrmH
#define FirstMesFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFirstMesForm : public TForm
{
__published:	// IDE 管理のコンポーネント
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TCheckBox *NextCheckBox;
	TButton *CloseBtn;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// ユーザー宣言
public:		// ユーザー宣言
	__fastcall TFirstMesForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFirstMesForm *FirstMesForm;
//---------------------------------------------------------------------------
#endif
