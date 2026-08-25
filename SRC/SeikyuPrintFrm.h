//---------------------------------------------------------------------------

#ifndef SeikyuPrintFrmH
#define SeikyuPrintFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QuickRpt.hpp>
#include <qrctrls.hpp>
#include "nsQRepPDF.h"
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
private:	// ユーザー宣言
	//現在のページ番号
	int Page;
	//現在の行番号
	int Row;
public:		// ユーザー宣言
	__fastcall TSeikyuPrintForm(TComponent* Owner);
public:
	nsQRepPDF QRepPDF;
};

//---------------------------------------------------------------------------
extern PACKAGE TSeikyuPrintForm *SeikyuPrintForm;
//---------------------------------------------------------------------------
#endif
