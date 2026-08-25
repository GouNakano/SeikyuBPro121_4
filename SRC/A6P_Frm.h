//---------------------------------------------------------------------------
#ifndef A6P_FrmH
#define A6P_FrmH
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
class TA6P_Form : public TForm
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
	TBorderEdit *SubTotalLabel;
	TBorderEdit *TaxLabel;
	TBorderEdit *TotalLabel;
	TWinLabel *BillLabel;
	TWinLabel *YearLabel;
	TWinLabel *MonthLabel;
	TWinLabel *DayLabel;
	TWinLabel *HonorificTitleLabel;
	TWinLabel *TitleLabel;
	TWinLabel *RequestLabel;
	TWinLabel *NumberLabel;
	TWinLabel *CompanyNameLabel;
	TWinLabel *PersonLabel;
	TWinLabel *ZipCodeLabel;
	TWinLabel *AddressLabel1;
	TWinLabel *AddressLabel2;
	TWinLabel *TELLabel;
	TWinLabel *FAXLabel;
	TWinLabel *ChargedAmountLabel;
	TWinLabel *UnitLabel;
	TWinLabel *TransferLabel1;
	TWinLabel *TransferLabel2;
	TWinLabel *NoteLabel;
	XnsGrid *Grid;
	TBorderEdit *YearEdit;
	TBorderEdit *MonthEdit;
	TBorderEdit *DayEdit;
	TBorderEdit *NameEdit;
	TBorderEdit *ItemEdit;
	TBorderEdit *NoEdit;
	TBorderEdit *MoneyEdit;
	TBorderEdit *SubtotalEdit;
	TBorderEdit *TaxEdit;
	TBorderEdit *TotalEdit;
private:	// ユーザー宣言
public:		// ユーザー宣言
	__fastcall TA6P_Form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TA6P_Form *A6P_Form;
//---------------------------------------------------------------------------
#endif
