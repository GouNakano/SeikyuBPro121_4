//---------------------------------------------------------------------------

#ifndef LicenseFrmH
#define LicenseFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TLicenseForm : public TForm
{
__published:	// IDE 管理のコンポーネント
	TLabel *MesLabel;
	TButton *YesBtn;
	TButton *NoBtn;
	TButton *BuyBtn;
	TImage *Image1;
	void __fastcall FormShow(TObject *Sender);
private:	// ユーザー宣言
public:		// ユーザー宣言
	__fastcall TLicenseForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLicenseForm *LicenseForm;
//---------------------------------------------------------------------------
#endif
