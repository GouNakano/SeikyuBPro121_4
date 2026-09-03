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
#include "TBaseEdit.h"
#include "TBaseMemo.h"
#include "BitBtn2.h"
#include <Vcl.TitleBarCtrls.hpp>
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
	TBaseEdit *NameEdit;
	TBaseEdit *MailEdit;
	TBaseEdit *Yubin1Edit;
	TBaseEdit *AddressEdit;
	TBaseEdit *Phone1Edit;
	TLabel *Label10;
	TBaseEdit *Phone2Edit;
	TBaseEdit *Phone3Edit;
	TLabel *Label11;
	TLabel *Label12;
	TBaseMemo *NoteMeno;
	TBitBtn2 *LicNextBtn;
	TBaseEdit *Yubin2Edit;
	TBitBtn2 *LicPrevBtn;
	TTabSheet *SendSheet;
	TLabel *Label13;
	TBaseEdit *ToEdit;
	TLabel *Label14;
	TLabel *Label15;
	TBaseEdit *SubjectEdit;
	TLabel *Label16;
	TBaseMemo *MailTextMemo;
	TBitBtn2 *ToCopyBtn;
	TBitBtn2 *SubjectBtn;
	TBitBtn2 *MailTextBtn;
	TLabel *Label17;
	TLabel *Label18;
	TLabel *Label19;
	TBitBtn2 *SendMailBtn;
	TBitBtn2 *RetBtn;
	TLabel *Label20;
	TLabel *Label21;
	TLabel *Label22;
	TLabel *Label23;
	TBitBtn2 *EndBtn;
	TTabSheet *AuthorizationSheet;
	TLabel *Label25;
	TBaseEdit *PasswordEdit;
	TBitBtn2 *LicPasteBtn;
	TLabel *Label26;
	TBitBtn *LicAuthorizationOkBtn;
	TLabel *Label27;
	TLabel *Label28;
	TLabel *Label29;
	TLabel *Label30;
	TLabel *Label31;
	TBitBtn2 *BitBtn1;
	TBitBtn *LicOrderFromVectorBtn;
	TLabel *Label8;
	TLabel *Label24;
	TLabel *Label32;
	TLabel *Label33;
	TShape *Shape1;
	TLabel *Label34;
	TTabSheet *VectorSheet;
	TLabel *Label35;
	TBaseEdit *VectorEdit;
	TBitBtn2 *VectorCopyBtn;
	TBitBtn2 *PreBtn;
	TBitBtn2 *CloseBtn;
	TLabel *Label36;
	TLabel *Label37;
	TLabel *Label38;
	TLabel *Label39;
	TLabel *Label40;
	TLabel *Label41;
	TLabel *Label42;
	TLabel *Label43;
	TLabel *Label44;
	TTitleBarPanel *TitleBarPanel;
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
	void __fastcall FormCreate(TObject *Sender);
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
