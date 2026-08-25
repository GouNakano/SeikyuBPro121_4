//---------------------------------------------------------------------------

#ifndef MainFrmH
#define MainFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE 管理のコンポーネント
	TLabel *Label1;
	TLabel *Label2;
	TEdit *LicreqEdit;
	TButton *IssueBtn;
	TLabel *Label3;
	TEdit *DiskSerialEdit;
	TEdit *LicPasswdEdit;
	TButton *CopyBtn;
	TLabel *ErrLabel;
	void __fastcall IssueBtnClick(TObject *Sender);
	void __fastcall CopyBtnClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// ユーザー宣言
public:		// ユーザー宣言
	__fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
