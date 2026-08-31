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
#include <Vcl.TitleBarCtrls.hpp>
#include "BitBtn2.h"
#include "TBaseEdit.h"
//---------------------------------------------------------------------------
class TGridPropertyForm : public TForm
{
__published:	// IDE 管理のコンポーネント
	TPanel *Panel1;
	TPanel *Panel2;
	TBitBtn2 *CloseBtn;
	TBitBtn2 *FormatBtn;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label4;
	TBaseEdit *RowNumEdit;
	TGroupBox *GroupBox2;
	TLabel *Label7;
	TLabel *Label9;
	TBaseEdit *CT_0;
	TLabel *Label8;
	TLabel *Label11;
	TBaseEdit *CT_1;
	TLabel *Label15;
	TLabel *Label16;
	TBaseEdit *CT_2;
	TLabel *Label19;
	TLabel *Label20;
	TBaseEdit *CT_4;
	TLabel *Label23;
	TLabel *Label24;
	TBaseEdit *CT_5;
	TCheckBox *FL_2;
	TLabel *Label2;
	TBaseEdit *FN_2;
	TCheckBox *FL_4;
	TLabel *Label3;
	TBaseEdit *FN_4;
	TCheckBox *FL_5;
	TLabel *Label5;
	TBaseEdit *FN_5;
	TLabel *Label6;
	TLabel *Label10;
	TBaseEdit *CT_3;
	TComboBoxEx *AL_0;
	TImageList *AlignmentImageList;
	TComboBoxEx *AL_1;
	TComboBoxEx *AL_2;
	TComboBoxEx *AL_3;
	TComboBoxEx *AL_4;
	TComboBoxEx *AL_5;
	TTitleBarPanel *TitleBarPanel;
	void __fastcall FormatBtnClick(TObject *Sender);
	void __fastcall CloseBtnClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);
private:
	TMessageEvent pEve;
public:
	__fastcall TGridPropertyForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGridPropertyForm *GridPropertyForm;
//---------------------------------------------------------------------------
#endif
