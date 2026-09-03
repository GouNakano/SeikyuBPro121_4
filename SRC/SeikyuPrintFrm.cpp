//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SeikyuPrintFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSeikyuPrintForm *SeikyuPrintForm;
//---------------------------------------------------------------------------
__fastcall TSeikyuPrintForm::TSeikyuPrintForm(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------
//  機能     ：印刷開始時
//
//  関数定義 ：void __fastcall SeikyuRepBeforePrint(TCustomQuickRep *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：private
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TSeikyuPrintForm::SeikyuRepBeforePrint(
      TCustomQuickRep *Sender, bool &PrintReport)
{
	//ページ番号初期化
	Page = -1;
	//用紙サイズ設定
	QRepPDF.SetPaperSize(SeikyuRep->Page->PaperSize,SeikyuRep->Page->Orientation);
	//座標系設定
	QRepPDF.SetOrgSize(SeikyuRep->Width,SeikyuRep->Height);
	//ズーム率設定
	QRepPDF.SetZoom(SeikyuRep->Zoom);
}

//---------------------------------------------------------------------------
//  機能     ：ページ終了時
//
//  関数定義 ：void __fastcall SeikyuRepStartPage(TCustomQuickRep *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：private
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TSeikyuPrintForm::SeikyuRepEndPage(TCustomQuickRep *Sender)
{
	//行番号初期化
	Row = 0;
	//ページ番号更新
	Page++;
}

//---------------------------------------------------------------------------
//  機能     ：データ要求時
//
//  関数定義 ：void __fastcall SeikyuRepNeedData(TObject *Sender,bool &MoreData)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：private
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TSeikyuPrintForm::SeikyuRepNeedData(TObject *Sender,bool &MoreData)
{
	//行番号チェック
	if(Row > 0)
	{
		MoreData = false;
		return;
	}
	//ページ番号チェック
	if(Page < 0)
	{
		return;
	}
	//バンド上のコントロールの数
	int CtrlCount = PrintBand->ControlCount;
	//リストに登録する
	for(int Cnt = 0;Cnt < CtrlCount;Cnt++)
	{
		//バンド上のコントロールを得る
		TControl *pCtrl = PrintBand->Controls[Cnt];
		//印刷対象コントロールにキャスト
		TQRPrintable *pQRPrintable = dynamic_cast<TQRPrintable *>(pCtrl);
		//印刷対象コントロールか？
        if(pQRPrintable != 0)
		{
			//印刷データ追加
			QRepPDF.AddQRepPDFData(Page,pQRPrintable,PrintBand,Row);
		}
	}
	//行番号更新
	Row++;
	//次のデータ
	MoreData = true;
}

//---------------------------------------------------------------------------
//  機能     ：ページ開始時
//
//  関数定義 ：void __fastcall SeikyuRepStartPage(TCustomQuickRep *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：private
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TSeikyuPrintForm::SeikyuRepStartPage(
      TCustomQuickRep *Sender)
{
	//行番号初期化
	Row = 0;
	//ページ番号初期化
	if(Page < 0)
	{
		Page = 0;
	}
}
//---------------------------------------------------------------------------


