//---------------------------------------------------------------------------

#ifndef PropertyFrmH
#define PropertyFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SeikyuBDef.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include "TBaseEdit.h"
#include "BitBtn2.h"
//---------------------------------------------------------------------------
class TPropertyForm : public TForm
{
__published:	// IDE 管理のコンポーネント
	TPanel *Panel1;
	TPanel *Panel2;
	TBitBtn2 *CloseBtn;
	TBitBtn2 *FormatBtn;
	TPanel *Panel3;
	TLabel *Label1;
	TLabel *NameLabel;
	TLabel *Label2;
	TBaseEdit *XEdit;
	TLabel *Label3;
	TBaseEdit *YEdit;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TBaseEdit *WidthEdit;
	TLabel *Label7;
	TLabel *Label8;
	TBaseEdit *HeightEdit;
	TLabel *Label9;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormatBtnClick(TObject *Sender);
private:
public:
	__fastcall TPropertyForm(TComponent* Owner);
public:
	//対象部品
	typDocCompo *pDoc;
};
//---------------------------------------------------------------------------
extern PACKAGE TPropertyForm *PropertyForm;
//---------------------------------------------------------------------------
#endif
