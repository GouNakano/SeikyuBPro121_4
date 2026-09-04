//---------------------------------------------------------------------------
#ifndef SeikyuPrintFrmH
#define SeikyuPrintFrmH
//---------------------------------------------------------------------------
#include "QuickRpt.hpp"
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "TBorderEdit.h"
#include "nsQRepPDF.h"
#include "typDocument.h"
//---------------------------------------------------------------------------
class TSeikyuPrintForm : public TForm
{
__published:	// IDE 管理のコンポーネント
	TQuickRep *SeikyuRep;
	TQRBand *PrintBand;
	void __fastcall SeikyuRepBeforePrint(TCustomQuickRep *Sender,
          bool &PrintReport);
	void __fastcall SeikyuRepEndPage(TCustomQuickRep *Sender);
	void __fastcall SeikyuRepNeedData(TObject *Sender, bool &MoreData);
	void __fastcall SeikyuRepStartPage(TCustomQuickRep *Sender);
private:
	//現在のページ番号
	int Page;
	//現在の行番号
	int Row;
private:
	//部品情報のフォントの情報をTFontに反映
	void DocFontInfToTFont(typFontDef& FontDef,TFont *pFont,bool IsCalcSize);
	//桁区切り線ありの文字列を印刷
	void PrintColumnSeparateText(long double X,long double Y,long double W,long double H,typFontDef& FontDef,int Figures,String Str);
	//グリッドの印刷
	void PrintGrid();
	//パネルフォントサイズの計算
	int CalcPanelFontSize(int OrgFontSize);

public:
	__fastcall TSeikyuPrintForm(TComponent* Owner);
public:
	//Quick ReportをPDFにするオブジェクト
	nsQRepPDF QRepPDF;
	//書類部品情報
	typDocCompo pDoc;
	//印刷モード
    TprintMode printMode = prmPrint;
};
//---------------------------------------------------------------------------
extern PACKAGE TSeikyuPrintForm *SeikyuPrintForm;
//---------------------------------------------------------------------------
#endif
