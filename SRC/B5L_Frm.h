//---------------------------------------------------------------------------
#ifndef B5L_FrmH
#define B5L_FrmH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include "XnsGrid.h"
#include "TWinLabel.h"
#include "WinShape.h"
#include "TBorderEdit.h"
//---------------------------------------------------------------------------
class TB5L_Form : public TForm
{
__published:	// IDE 管理のコンポーネント
	TImage *StampImage1;
	TImage *StampImage2;
	TImage *LogoImage;
	TWinShape *DayUnderShape;
	TWinShape *NameUnderShape;
	TWinShape *ItemShape;
	TWinShape *NumberShape;
	TWinShape *MoneyShape;
	TWinShape *NoteShape;
	TWinLabel *HonorificTitleLabel;
	TWinLabel *SubTotalLabel;
	TWinLabel *TaxLabel;
	TWinLabel *TotalLabel;
	TWinLabel *CompanyNameLabel;
	TWinLabel *PersonLabel;
	TWinLabel *ZipCodeLabel;
	TWinLabel *AddressLabel1;
	TWinLabel *AddressLabel2;
	TWinLabel *TELLabel;
	TWinLabel *FAXLabel;
	TWinLabel *NumberLabel;
	TWinLabel *UnitLabel;
	TWinLabel *YearLabel;
	TWinLabel *MonthLabel;
	TWinLabel *DayLabel;
	TWinLabel *BillLabel;
	TWinLabel *RequestLabel;
	TWinLabel *TitleLabel;
	TWinLabel *ChargedAmountLabel;
	TWinLabel *NoteLabel;
	TWinLabel *TransferLabel1;
	TWinLabel *TransferLabel2;
	XnsGrid *Grid;
	TBorderEdit *SubtotalEdit;
	TBorderEdit *TaxEdit;
	TBorderEdit *TotalEdit;
	TBorderEdit *NoEdit;
	TBorderEdit *ItemEdit;
	TBorderEdit *MoneyEdit;
	TBorderEdit *NameEdit;
	TBorderEdit *YearEdit;
	TBorderEdit *MonthEdit;
	TBorderEdit *DayEdit;
private:	// ユーザー宣言
public:		// ユーザー宣言
	__fastcall TB5L_Form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TB5L_Form *B5L_Form;
//---------------------------------------------------------------------------
#endif
