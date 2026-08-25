//---------------------------------------------------------------------------

#ifndef GridPropertyFrmH
#define GridPropertyFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <System.ImageList.hpp>
//---------------------------------------------------------------------------
class TGridPropertyForm : public TForm
{
__published:	// IDE 管理のコンポーネント
	TPanel *Panel1;
	TPanel *Panel2;
	TBitBtn *CloseBtn;
	TBitBtn *FormatBtn;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label4;
	TEdit *RowNumEdit;
	TGroupBox *GroupBox2;
	TLabel *Label7;
	TLabel *Label9;
	TEdit *CT_0;
	TLabel *Label8;
	TLabel *Label11;
	TEdit *CT_1;
	TLabel *Label15;
	TLabel *Label16;
	TEdit *CT_2;
	TLabel *Label19;
	TLabel *Label20;
	TEdit *CT_4;
	TLabel *Label23;
	TLabel *Label24;
	TEdit *CT_5;
	TCheckBox *FL_2;
	TLabel *Label2;
	TEdit *FN_2;
	TCheckBox *FL_4;
	TLabel *Label3;
	TEdit *FN_4;
	TCheckBox *FL_5;
	TLabel *Label5;
	TEdit *FN_5;
	TLabel *Label6;
	TLabel *Label10;
	TEdit *CT_3;
	TComboBoxEx *AL_0;
	TImageList *AlignmentImageList;
	TComboBoxEx *AL_1;
	TComboBoxEx *AL_2;
	TComboBoxEx *AL_3;
	TComboBoxEx *AL_4;
	TComboBoxEx *AL_5;
	void __fastcall FormatBtnClick(TObject *Sender);
	void __fastcall CloseBtnClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:
	TMessageEvent pEve;
public:
	__fastcall TGridPropertyForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGridPropertyForm *GridPropertyForm;
//---------------------------------------------------------------------------
#endif
