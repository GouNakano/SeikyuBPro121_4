//---------------------------------------------------------------------------
#ifndef SettingFrmH
#define SettingFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include "TSBSetting.h"
#include <Vcl.TitleBarCtrls.hpp>
#include "BitBtn2.h"
#include "TBaseEdit.h"
//---------------------------------------------------------------------------
class TSettingForm : public TForm
{
__published:	// IDE 管理のコンポーネント
	TBitBtn2 *OkBtn;
	TBitBtn2 *CancelBtn;
	TOpenDialog *OpenDialog;
	TPageControl *PageControl;
	TTabSheet *GeneralTabSheet;
	TCheckBox *BackupFileCBox;
	TCheckBox *RemainCBox;
	TGroupBox *GroupBox1;
	TCheckBox *UseTemplateCBox;
	TEdit *TemplateFileEdit;
	TBitBtn *FIB_01;
	TCheckBox *TodayCBox;
	TTabSheet *TabSheet2;
	TGroupBox *StockingTaxGBox;
	TLabel *Label2;
	TLabel *Label10;
	TLabel *Label11;
	TRadioButton *RB00;
	TRadioButton *RB01;
	TRadioButton *RB02;
	TBaseEdit *Ratio00Edit;
	TGroupBox *GroupBox2;
	TLabel *Label1;
	TLabel *Label3;
	TLabel *Label4;
	TRadioButton *RB20;
	TRadioButton *RB21;
	TRadioButton *RB22;
	TBaseEdit *Ratio02Edit;
	TGroupBox *GroupBox3;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TRadioButton *RB10;
	TRadioButton *RB11;
	TRadioButton *RB12;
	TBaseEdit *Ratio01Edit;
	TGroupBox *GroupBox4;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label12;
	TRadioButton *RB30;
	TRadioButton *RB31;
	TRadioButton *RB32;
	TBaseEdit *Ratio03Edit;
	TGroupBox *GroupBox5;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TRadioButton *RB40;
	TRadioButton *RB41;
	TRadioButton *RB42;
	TBaseEdit *Ratio04Edit;
	TTitleBarPanel *TitleBarPanel;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall CancelBtnClick(TObject *Sender);
	void __fastcall OkBtnClick(TObject *Sender);
	void __fastcall UseTemplateCBoxClick(TObject *Sender);
	void __fastcall FIB_01Click(TObject *Sender);
	void __fastcall RatioCNumEditKeyPress(TObject *Sender, char &Key);
	void __fastcall FormCreate(TObject *Sender);
private:
	//請求書番頭の設定
	TSBSetting ES;
public:
	__fastcall TSettingForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSettingForm *SettingForm;
//---------------------------------------------------------------------------
#endif
