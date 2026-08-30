//---------------------------------------------------------------------------
#ifndef CompanyInfoFrmH
#define CompanyInfoFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include "TBaseEdit.h"
#include "BitBtn2.h"
#include <Vcl.TitleBarCtrls.hpp>
//---------------------------------------------------------------------------
class TCompanyInfoForm : public TForm
{
__published:	// IDE 管理のコンポーネント
	TBitBtn2 *CancelBtn;
	TBitBtn2 *ResistBtn;
	TPageControl *CPageCtrl;
	TTabSheet *C1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TBaseEdit *CompanyNameEdit_1;
	TBaseEdit *RepresentEdit_1;
	TBaseEdit *ZipNumberEdit_1;
	TBaseEdit *AddressEdit1_1;
	TBaseEdit *AddressEdit2_1;
	TBaseEdit *TELEdit_1;
	TBaseEdit *FAXEdit_1;
	TBaseEdit *TransferEdit1_1;
	TBaseEdit *TransferEdit2_1;
	TBaseEdit *TaxEdit_1;
	TBitBtn2 *ZipToAddressBtn;
	TLabel *Label7;
	TTabSheet *C2;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label17;
	TLabel *Label18;
	TLabel *Label19;
	TLabel *Label20;
	TBaseEdit *CompanyNameEdit_2;
	TBaseEdit *RepresentEdit_2;
	TBaseEdit *ZipNumberEdit_2;
	TBaseEdit *AddressEdit1_2;
	TBaseEdit *AddressEdit2_2;
	TBaseEdit *TELEdit_2;
	TBaseEdit *FAXEdit_2;
	TBaseEdit *TransferEdit1_2;
	TBaseEdit *TransferEdit2_2;
	TBaseEdit *TaxEdit_2;
	TBitBtn2 *ZipBtn2;
	TLabel *Label22;
	TTabSheet *C3;
	TLabel *Label23;
	TLabel *Label24;
	TLabel *Label25;
	TLabel *Label26;
	TLabel *Label27;
	TLabel *Label28;
	TLabel *Label29;
	TLabel *Label30;
	TLabel *Label31;
	TLabel *Label32;
	TBaseEdit *CompanyNameEdit_3;
	TBaseEdit *RepresentEdit_3;
	TBaseEdit *ZipNumberEdit_3;
	TBaseEdit *AddressEdit1_3;
	TBaseEdit *AddressEdit2_3;
	TBaseEdit *TELEdit_3;
	TBaseEdit *FAXEdit_3;
	TBaseEdit *TransferEdit1_3;
	TBaseEdit *TransferEdit2_3;
	TBaseEdit *TaxEdit_3;
	TBitBtn2 *ZipBtn3;
	TLabel *Label33;
	TLabel *Label34;
	TLabel *Label35;
	TLabel *Label21;
	TLabel *Label36;
	TLabel *Label37;
	TLabel *Label11;
	TLabel *Label38;
	TLabel *Label39;
	TTitleBarPanel *TitleBarPanel;
	void __fastcall ZipToAddressBtnClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ResistBtnClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall CPageCtrlDrawTab(TCustomTabControl *Control, int TabIndex, const TRect &Rect,
		  bool Active);
private:
	//郵便番号文字列の補正
	void ModifyInputZipStr(TBaseEdit *ZipNumberEdit);
public:
	__fastcall TCompanyInfoForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TCompanyInfoForm *CompanyInfoForm;
//---------------------------------------------------------------------------
#endif
