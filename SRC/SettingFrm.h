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
//---------------------------------------------------------------------------
class TSettingForm : public TForm
{
__published:	// IDE 管理のコンポーネント
	TButton *OkBtn;
	TButton *CancelBtn;
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
	TEdit *Ratio00Edit;
	TGroupBox *GroupBox2;
	TLabel *Label1;
	TLabel *Label3;
	TLabel *Label4;
	TRadioButton *RB20;
	TRadioButton *RB21;
	TRadioButton *RB22;
	TEdit *Ratio02Edit;
	TGroupBox *GroupBox3;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TRadioButton *RB10;
	TRadioButton *RB11;
	TRadioButton *RB12;
	TEdit *Ratio01Edit;
	TGroupBox *GroupBox4;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label12;
	TRadioButton *RB30;
	TRadioButton *RB31;
	TRadioButton *RB32;
	TEdit *Ratio03Edit;
	TGroupBox *GroupBox5;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TRadioButton *RB40;
	TRadioButton *RB41;
	TRadioButton *RB42;
	TEdit *Ratio04Edit;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall CancelBtnClick(TObject *Sender);
	void __fastcall OkBtnClick(TObject *Sender);
	void __fastcall UseTemplateCBoxClick(TObject *Sender);
	void __fastcall FIB_01Click(TObject *Sender);
	void __fastcall RatioCNumEditKeyPress(TObject *Sender, char &Key);
private:	// ユーザー宣言
public:		// ユーザー宣言
	__fastcall TSettingForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSettingForm *SettingForm;
//---------------------------------------------------------------------------
#endif
