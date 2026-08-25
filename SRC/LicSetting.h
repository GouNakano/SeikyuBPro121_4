//---------------------------------------------------------------------------

#ifndef LicSettingH
#define LicSettingH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "SendMail.hpp"
//---------------------------------------------------------------------------
class TLicSettingForm : public TForm
{
__published:	// IDE 管理のコンポーネント
	TPageControl *PageControl;
	TTabSheet *MainSheet;
	TLabel *Label1;
	TBitBtn *LicOrderBtn;
	TBitBtn *AuthorizationBtn;
	TTabSheet *LicOrderSheet;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label9;
	TEdit *NameEdit;
	TEdit *MailEdit;
	TEdit *Yubin1Edit;
	TEdit *AddressEdit;
	TEdit *Phone1Edit;
	TLabel *Label10;
	TEdit *Phone2Edit;
	TEdit *Phone3Edit;
	TLabel *Label11;
	TLabel *Label12;
	TMemo *NoteMeno;
	TBitBtn *LicNextBtn;
	TEdit *Yubin2Edit;
	TBitBtn *LicPrevBtn;
	TTabSheet *SendSheet;
	TLabel *Label13;
	TEdit *ToEdit;
	TLabel *Label14;
	TLabel *Label15;
	TEdit *SubjectEdit;
	TLabel *Label16;
	TMemo *MailTextMemo;
	TBitBtn *ToCopyBtn;
	TBitBtn *SubjectBtn;
	TBitBtn *MailTextBtn;
	TLabel *Label17;
	TLabel *Label18;
	TLabel *Label19;
	TBitBtn *SendMailBtn;
	TBitBtn *RetBtn;
	TLabel *Label20;
	TLabel *Label21;
	TLabel *Label22;
	TLabel *Label23;
	TBitBtn *EndBtn;
	TTabSheet *AuthorizationSheet;
	TLabel *Label25;
	TEdit *PasswordEdit;
	TBitBtn *LicPasteBtn;
	TLabel *Label26;
	TBitBtn *LicAuthorizationOkBtn;
	TLabel *Label27;
	TLabel *Label28;
	TLabel *Label29;
	TLabel *Label30;
	TLabel *Label31;
	TBitBtn *BitBtn1;
	TBitBtn *LicOrderFromVectorBtn;
	TLabel *Label8;
	TLabel *Label24;
	TLabel *Label32;
	TLabel *Label33;
	TShape *Shape1;
	TLabel *Label34;
	TTabSheet *VectorSheet;
	TLabel *Label35;
	TEdit *VectorEdit;
	TButton *VectorCopyBtn;
	TBitBtn *BitBtn2;
	TBitBtn *BitBtn3;
	TLabel *Label36;
	TLabel *Label37;
	TLabel *Label38;
	TLabel *Label39;
	TLabel *Label40;
	TLabel *Label41;
	TLabel *Label42;
	TLabel *Label43;
	TLabel *Label44;
	void __fastcall LicOrderBtnClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall LicNextBtnClick(TObject *Sender);
	void __fastcall SendMailBtnClick(TObject *Sender);
	void __fastcall RetBtnClick(TObject *Sender);
	void __fastcall LicPrevBtnClick(TObject *Sender);
	void __fastcall EndBtnClick(TObject *Sender);
	void __fastcall ToCopyBtnClick(TObject *Sender);
	void __fastcall AuthorizationBtnClick(TObject *Sender);
	void __fastcall LicPasteBtnClick(TObject *Sender);
	void __fastcall LicAuthorizationOkBtnClick(TObject *Sender);
	void __fastcall Yubin1EditKeyPress(TObject *Sender, char &Key);
	void __fastcall LicOrderFromVectorBtnClick(TObject *Sender);
	void __fastcall VectorCopyBtnClick(TObject *Sender);
private:	// ユーザー宣言
	//メール送信
	bool sendMail();
public:		// ユーザー宣言
	__fastcall TLicSettingForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLicSettingForm *LicSettingForm;
//---------------------------------------------------------------------------
#endif
