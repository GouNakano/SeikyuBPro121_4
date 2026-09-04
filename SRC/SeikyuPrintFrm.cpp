//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SeikyuBConst.h"
#include "TStdComponents.h"
#include "TLicense.h"
#include "TZooms.h"
#include "MainFrm.h"
#include "SeikyuPrintFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "QuickRpt"
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
void __fastcall TSeikyuPrintForm::SeikyuRepBeforePrint(TCustomQuickRep *Sender, bool &PrintReport)
{
	long double  dcy;

	//ページ番号初期化
	Page = -1;
	//用紙の設定
	SeikyuRep->Page->PaperSize    = PaperDef[Document.Paper].PaperSize;
	SeikyuRep->Page->Orientation  = PaperDef[Document.Paper].Orientation;
	SeikyuRep->Zoom               = 300;
	//用紙サイズ設定
	QRepPDF.SetPaperSize(SeikyuRep->Page->PaperSize,SeikyuRep->Page->Orientation);
	//座標系設定
	QRepPDF.SetOrgSize(SeikyuRep->Width,SeikyuRep->Height);
	//ズーム率設定
	QRepPDF.SetZoom(SeikyuRep->Zoom);
	//印刷対象レポート
	TQuickRep *pRep = SeikyuPrintForm->SeikyuRep;
	//印刷対象バンド
	TQRBand *pBand = SeikyuPrintForm->PrintBand;


	//大きさを得るためのテストShape
	TQRShape *pQRTestShape = new TQRShape(pBand);
	pQRTestShape->Parent = pBand;
	pQRTestShape->Name   = "pQRTestShape";
	pQRTestShape->Left   = 0;
	pQRTestShape->Top    = 0;
	pQRTestShape->Width  = 5;
	pQRTestShape->Height = 5;

	try
	{
		//パネル上のコンポーネントを印刷対象とする
		for(int Cnt = 0;Cnt < MainForm->MainPanel->ControlCount;Cnt++)
		{
			TWinShape      *pShape;
			TWinLabel      *pWinLabel;
			TBorderEdit    *pBorderEdit;
			TImageControl  *pImage;
			XnsGrid        *pGrid;

			//パネル上のコントロールを得る
			TControl *pCtrl = MainForm->MainPanel->Controls[Cnt];

			//書類部品情報取得
			bool res = Document.GetDocCompoFromName(pCtrl->Name,pDoc);
			//部品情報が得られなければ次にいく
			if(res == false)
			{
				continue;
			}
			//印刷対象でなければ次にいく
			if(pDoc.Visible == false || pDoc.IsPrint == false)
			{
				continue;
			}
			//TShapeの場合
			if((pShape = dynamic_cast<TWinShape *>(pCtrl)) != 0)
			{
				//TQRShape作成
				TQRShape *pQRShape     = new TQRShape(pBand);
				pQRShape->Parent       = pBand;
				if(pDoc.Type == dcCLine)
				{
					//横線Shape
					pQRShape->Size->Left      = pDoc.X;
					pQRShape->Size->Top       = pDoc.Y;
					pQRShape->Size->Width     = pDoc.Width;
					pQRShape->Size->Height    = 0.5;
					pQRShape->Shape           = qrsHorLine;
				}
				else
				{
					//四角形Shape
					pQRShape->Size->Left         = pDoc.X;
					pQRShape->Size->Top          = pDoc.Y;

					//テストShapeの配置
					pQRTestShape->Size->Left = (pDoc.X + pDoc.Width);
					pQRTestShape->Size->Top  = (pDoc.Y + pDoc.Height);
					//pQRShapeの補正
					pQRShape->Width  = (pQRTestShape->Left - pQRShape->Left);
					pQRShape->Height = (pQRTestShape->Top  - pQRShape->Top);
				}
			}
			else if((pWinLabel = dynamic_cast<TWinLabel *>(pCtrl)) != 0)
			{

				if(pWinLabel->BorderDraw == true)
				{
					//枠線あり
					TQRShape *pQRShape     = new TQRShape(pBand);
					pQRShape->Parent       = pBand;
					pQRShape->Brush->Style = bsSolid;
					pQRShape->Size->Left   = pDoc.X;
					pQRShape->Size->Top    = pDoc.Y;

					//テストShapeの配置
					pQRTestShape->Size->Left = (pDoc.X + pDoc.Width);
					pQRTestShape->Size->Top  = (pDoc.Y + pDoc.Height);
					//pQRShapeの補正
					pQRShape->Width  = (pQRTestShape->Left - pQRShape->Left);
					pQRShape->Height = (pQRTestShape->Top  - pQRShape->Top);

				}
				//TQRLabel作成
				TQRLabel *pQRLabel     = new TQRLabel(pBand);
				pQRLabel->Parent       = pBand;
				pQRLabel->AutoSize     = true;
				DocFontInfToTFont(pDoc.Font,pQRLabel->Font,false);
				pQRLabel->Alignment    = pDoc.Alignment;
				pQRLabel->Caption      = pWinLabel->Caption;
				//高さを得る
				long double LblHeight = pQRLabel->Size->Height;
				//自動サイズをやめる
				pQRLabel->AutoSize     = false;
				//横位置と幅決定
				pQRLabel->Size->Left   = pDoc.X     + ((pWinLabel->BorderDraw == true)?PRINT_BORDER_MARGIN      :0.0);
				pQRLabel->Size->Width  = pDoc.Width - ((pWinLabel->BorderDraw == true)?PRINT_BORDER_MARGIN * 2.0:0.0);
				//Top,Heightの決定
				if(LblHeight == pDoc.Height)
				{
					pQRLabel->Size->Height       = pDoc.Height;
					pQRLabel->Size->Top          = pDoc.Y;
				}
				else if(LblHeight > pDoc.Height)
				{
					//ラベルの高さよりフォントが大きい
					pQRLabel->Size->Height       = pDoc.Height;
					pQRLabel->Size->Top          = pDoc.Y;
				}
				else
				{
					//補正量
					dcy = (pDoc.Height - LblHeight) / 2.0;
					//中段に寄せる
					pQRLabel->Size->Height  = LblHeight;
					pQRLabel->Size->Top     = pDoc.Y + dcy;
				}
			}
			else if((pBorderEdit = dynamic_cast<TBorderEdit *>(pCtrl)) != 0)
			{
				//桁区切り線の有無を確認
				if(pBorderEdit->ColSeparateDraw == true)
				{
					//桁区切り線あり
					PrintColumnSeparateText(pDoc.X,pDoc.Y,pDoc.Width,pDoc.Height,pDoc.Font,pDoc.Figures,pBorderEdit->GetDispStr());
				}
				else
				{
					//---- 桁区切り線なし----

					if(pBorderEdit->BorderDraw == true)
					{
						TQRShape *pQRShape     = new TQRShape(pBand);
						pQRShape->Parent       = pBand;
						pQRShape->Brush->Style = bsSolid;
						pQRShape->Size->Left   = pDoc.X;
						pQRShape->Size->Top    = pDoc.Y;

						//テストShapeの配置
						pQRTestShape->Size->Left = (pDoc.X + pDoc.Width);
						pQRTestShape->Size->Top  = (pDoc.Y + pDoc.Height);
						//pQRShapeの補正
						pQRShape->Width  = (pQRTestShape->Left - pQRShape->Left);
						pQRShape->Height = (pQRTestShape->Top  - pQRShape->Top);
					}
					//TQRLabel作成
					long double LblHeight;
					TQRLabel *pQRLabel     = new TQRLabel(pBand);
					pQRLabel->Parent       = pBand;
					pQRLabel->AutoSize     = true;

					pQRLabel->Alignment    = pDoc.Alignment;
					DocFontInfToTFont(pDoc.Font,pQRLabel->Font,false);

					pQRLabel->Caption      = pBorderEdit->GetDispStr();
					LblHeight              = pQRLabel->Size->Height;
					pQRLabel->AutoSize     = false;

					pQRLabel->Size->Left   = pDoc.X     + ((pBorderEdit->BorderDraw==true) ? PRINT_BORDER_MARGIN      :0.0);
					pQRLabel->Size->Width  = pDoc.Width - ((pBorderEdit->BorderDraw==true) ? PRINT_BORDER_MARGIN * 2.0:0.0);

					//Top,Heightの決定
					if(LblHeight == pDoc.Height)
					{
						pQRLabel->Size->Height = pDoc.Height;
						pQRLabel->Size->Top    = pDoc.Y;
					}
					else if(LblHeight > pDoc.Height)
					{
						//エディットの高さよりフォントが大きい
						pQRLabel->Size->Height       = LblHeight;
						pQRLabel->Size->Top          = pDoc.Y - (LblHeight - pDoc.Height);
					}
					else
					{
						//補正量
						long double dcy = (pDoc.Height - LblHeight) / 2.0;
						//中段に寄せる
						pQRLabel->Size->Height       = LblHeight;
						pQRLabel->Size->Top          = pDoc.Y + dcy;
					}
				}
			}
			else if((pImage = dynamic_cast<TImageControl *>(pCtrl)) != nullptr)
			{
				String ImgName;
				String ValStr;

				//TQRShape作成
				if(pDoc.Border == true)
				{
					TQRShape *pQRShape      = new TQRShape(pBand);
					pQRShape->Parent        = pBand;
					pQRShape->Brush->Style  = bsSolid;
					pQRShape->Size->Left    = pDoc.X;
					pQRShape->Size->Top     = pDoc.Y;

					//テストShapeの配置
					pQRTestShape->Size->Left = (pDoc.X + pDoc.Width);
					pQRTestShape->Size->Top  = (pDoc.Y + pDoc.Height);
					//pQRShapeの補正
					pQRShape->Width  = (pQRTestShape->Left - pQRShape->Left);
					pQRShape->Height = (pQRTestShape->Top  - pQRShape->Top);
				}
				//TQRImage作成
				TQRImage *pQRImage     = new TQRImage(pBand);
				pQRImage->Parent       = pBand;
				pQRImage->AutoSize     = false;
				pQRImage->Center       = true;

				pQRImage->Size->Left   = pDoc.X;
				pQRImage->Size->Top    = pDoc.Y;
				pQRImage->Size->Width  = pDoc.Width;
				pQRImage->Size->Height = pDoc.Height;
				//イメージ取り込み
				bool IsDrawImage = true;
				try
				{
					//イメージが有効かチェック
					if(pImage->Picture != nullptr)
					{
						//イメージの設定
						if(pImage->Picture->Width > 0 && pImage->Picture->Height > 0 )
						{
							pQRImage->Picture->Assign(pImage->Picture);
						}
					}
				}
				catch(...)
				{
				}
			}
			else if((pGrid = dynamic_cast<XnsGrid *>(pCtrl)) != 0)
			{
				//グリッドの印刷
				PrintGrid();
			}
		}
	}
	__finally
	{
		//テストShape削除
		delete pQRTestShape;
	}
	//ライセンスオブジェクト
	TLicense license;
	//ライセンス未設定の印刷
	if(license.isLicenceEnable() == false)
	{
		TQRLabel *pQRLabel     = new TQRLabel(pBand);
		pQRLabel->Parent       = pBand;
		pQRLabel->AutoSize     = false;
		pQRLabel->Alignment    = taCenter;
		pQRLabel->Brush->Style = (decltype(pQRLabel->Brush->Style))bsNone;
		pQRLabel->Font->Size   = 16;
		pQRLabel->Width        = pBand->Width;
		pQRLabel->Top          = pRep->Height / 2;
		pQRLabel->Caption      = L"この請求書番頭 プロ版には正規ライセンスが設定されていません。";
	}
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
void __fastcall TSeikyuPrintForm::SeikyuRepStartPage(TCustomQuickRep *Sender)
{
	//行番号初期化
	Row = 0;
	//ページ番号初期化
	if(Page < 0)
	{
		Page = 0;
	}
}
//-------------------------------------------------------------
//部品情報のフォントの情報をTFontに反映
//-------------------------------------------------------------
void TSeikyuPrintForm::DocFontInfToTFont(typFontDef& FontDef,TFont *pFont,bool IsCalcSize)
{
	//フォント名
	pFont->Name   = FontDef.Name;
	//フォントサイズ
	if(IsCalcSize == true)
	{
		pFont->Size   = CalcPanelFontSize(FontDef.Size); //パネルに合わせて計算
	}
	else
	{
		pFont->Size   = FontDef.Size;
	}
	//色
	pFont->Color  = FontDef.Color;
	//太字
	if(FontDef.Bold == true)
	{
		pFont->Style = (pFont->Style << fsBold);
	}
	else
	{
		pFont->Style = (pFont->Style >> fsBold);
	}
	//イタリック
	if(FontDef.Italic == true)
	{
		pFont->Style = (pFont->Style << fsItalic);
	}
	else
	{
		pFont->Style = (pFont->Style >> fsItalic);
	}
	//下線
	if(FontDef.Under == true)
	{
		pFont->Style = (pFont->Style << fsUnderline);
	}
	else
	{
		pFont->Style = (pFont->Style >> fsUnderline);
	}
}
//-------------------------------------------------------------
//桁区切り線ありの文字列を印刷
//-------------------------------------------------------------
void TSeikyuPrintForm::PrintColumnSeparateText(long double X,long double Y,long double W,long double H,typFontDef& FontDef,int Figures,String Str)
{
	TQRShape *pQRShape;

	//印刷対象バンド
	TQRBand *pBand = SeikyuPrintForm->PrintBand;
	//大きさを得るためのテストShapeを得る
	TQRShape *pQRTestShape = (TQRShape *)pBand->FindComponent("pQRTestShape");
	//文字数
	int SLen = Str.Length();
	//文字の作成
	for(int Cnt = 0;Cnt < Figures;Cnt++)
	{
		//文字の作成
		if(Figures - Cnt -1 < SLen)
		{
			int dx = 0;
			int dy = 0;
			long double LblHeight;
			//作成X座標
			long double X0 = X + ((W * static_cast<long double>(Cnt)) / static_cast<long double>(Figures));
			//TQRLabel作成
			TQRLabel *pQRLabel     = new TQRLabel(pBand);
			pQRLabel->Parent       = pBand;
			pQRLabel->AutoSize     = true;
			pQRLabel->Alignment    = taCenter;
			DocFontInfToTFont(FontDef,pQRLabel->Font,false);
			pQRLabel->Caption      = Str.SubString(Cnt - (Figures - SLen) + 1,1);
			LblHeight              = pQRLabel->Size->Height;
			pQRLabel->AutoSize     = false;
			pQRLabel->Size->Left   = X0 + PRINT_ADJUST_DIFF;
			pQRLabel->Size->Width  = W / static_cast<long double>(Figures) - PRINT_ADJUST_DIFF * 2.0;
			//Top,Heightの決定
			if(LblHeight == H)
			{
				pQRLabel->Size->Height = H;
				pQRLabel->Size->Top    = Y;
			}
			else if(LblHeight > H)
			{
				//エディットの高さよりフォントが大きい
				pQRLabel->Size->Height       = LblHeight;
				pQRLabel->Size->Top          = Y - (LblHeight - H);
			}
			else
			{
				//補正量
				long double dcy = (H - LblHeight) / 2.0;
				//中段に寄せる
				pQRLabel->Size->Height       = LblHeight;
				pQRLabel->Size->Top          = Y + dcy;
			}
		}
	}
	//区切り線の作成
	for(int Cnt = 1;Cnt < Figures;Cnt++)
	{
		pQRShape               = new TQRShape(pBand);
		pQRShape->Parent       = pBand;
		pQRShape->Shape        = qrsVertLine; //縦線
		pQRShape->Pen->Style   = psDot;
		pQRShape->Size->Left   = X + ((W * static_cast<long double>(Cnt)) / static_cast<long double>(Figures));
		pQRShape->Size->Top    = Y;
		pQRShape->Size->Width  = 0.5;
		pQRShape->Size->Height = H;
	}
	//枠線の作成
	pQRShape               = new TQRShape(pBand);
	pQRShape->Parent       = pBand;
	pQRShape->Brush->Style = bsClear;
	pQRShape->Size->Left   = X;
	pQRShape->Size->Top    = Y;
	pQRShape->Size->Width  = W;
	pQRShape->Size->Height = H;
	//テストShapeの配置
	pQRTestShape->Size->Left = (X + W);
	pQRTestShape->Size->Top  = (Y + H);
	//pQRShapeの補正
	pQRShape->Width  = (pQRTestShape->Left - pQRShape->Left);
	pQRShape->Height = (pQRTestShape->Top  - pQRShape->Top);
}
//-------------------------------------------------------------
//  機能     ：グリッドの印刷
//
//  関数定義 ：void PrintGrid()
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void TSeikyuPrintForm::PrintGrid()
{
	long double  x,y,w,h;
	String       ValStr;

	//印刷対象レポート
	TQuickRep *pRep = SeikyuPrintForm->SeikyuRep;
	//印刷対象バンド
	TQRBand  *pBand = SeikyuPrintForm->PrintBand;

	//グリッドの情報
	typDocCompo pGridDoc;
	Document.GetDocCompoFromName(StdComponents[scStdComponent::scGrid].Name,pGridDoc);

	//大きさを得るためのテストShapeを得る
	TQRShape *pQRTestShape = (TQRShape *)pBand->FindComponent("pQRTestShape");

	//Shapeの作成
	for(int Col = 0;Col < MainForm->Grid->ColCount;Col++)
	{
		//列の情報
		typDocCompo pColDoc;

		ValStr.sprintf(L"D_%02d_%02d",0,Col);
		Document.GetDocCompoFromName(ValStr,pColDoc);

		for(int Row = 0;Row < MainForm->Grid->RowCount;Row++)
		{
			//座標作成
			x = pColDoc.X;
			y = pGridDoc.Y + ((static_cast<long double>(Row) * pGridDoc.Height) / static_cast<long double>(pGridDoc.RowNum));
			w = pColDoc.Width;
			h = pGridDoc.Height / static_cast<long double>(pGridDoc.RowNum);

			//TQRShape作成
			TQRShape *pQRShape     = new TQRShape(pBand);
			pQRShape->Parent       = pBand;
			pQRShape->Brush->Style = bsSolid;
			pQRShape->Size->Left   = x;
			pQRShape->Size->Top    = y;
			//テストShapeの配置
			pQRTestShape->Size->Left = (x + w);
			pQRTestShape->Size->Top  = (y + h);
			//pQRShapeの補正
			pQRShape->Width  = (pQRTestShape->Left - pQRShape->Left);
			pQRShape->Height = (pQRTestShape->Top - pQRShape->Top);

			//表示文字列の取得
			String DispStr = MainForm->Grid->GetDispCellStr(Row,Col);

			//寄せの設定
			if(Row == 0)
			{
				//TQRLabel作成
				TQRLabel *pQRLabel     = new TQRLabel(pBand);
				pQRLabel->Parent       = pBand;

				DocFontInfToTFont(pGridDoc.Font,pQRLabel->Font,false);

				pQRLabel->AutoSize     = false;
				//タイトルは真ん中
				pQRLabel->Alignment = taCenter;
				//ラベルの設定
				pQRLabel->AutoSize     = false;
				pQRLabel->Caption      = DispStr;
				pQRLabel->Size->Left   = x + PRINT_BORDER_MARGIN;
				pQRLabel->Size->Top    = y + PRINT_BORDER_MARGIN;
				pQRLabel->Size->Width  = w - PRINT_BORDER_MARGIN * 2.0;
				pQRLabel->Size->Height = h - PRINT_BORDER_MARGIN * 2.0;
			}
			else
			{
				if(Col == 0) //項目
				{
					//TQRLabel作成
					TQRLabel *pQRLabel     = new TQRLabel(pBand);
					pQRLabel->Parent       = pBand;

					DocFontInfToTFont(pGridDoc.Font,pQRLabel->Font,false);

					pQRLabel->AutoSize  = false;
					//寄せ
					pQRLabel->Alignment = pColDoc.Alignment;
					//ラベルの設定
					pQRLabel->Caption      = DispStr;
					pQRLabel->Size->Left   = x + PRINT_BORDER_MARGIN;
					pQRLabel->Size->Top    = y + PRINT_BORDER_MARGIN;
					pQRLabel->Size->Width  = w - PRINT_BORDER_MARGIN * 2.0;
					pQRLabel->Size->Height = h - PRINT_BORDER_MARGIN * 2.0;
				}
				else if(Col == 1)  //商品名
				{
					//TQRLabel作成
					TQRLabel *pQRLabel     = new TQRLabel(pBand);
					pQRLabel->Parent       = pBand;

					DocFontInfToTFont(pGridDoc.Font,pQRLabel->Font,false);

					pQRLabel->AutoSize     = false;
					//寄せ
					pQRLabel->Alignment = pColDoc.Alignment;
					//ラベルの設定
					pQRLabel->Caption      = DispStr;
					pQRLabel->Size->Left   = x + PRINT_BORDER_MARGIN;
					pQRLabel->Size->Top    = y + PRINT_BORDER_MARGIN;
					pQRLabel->Size->Width  = w - PRINT_BORDER_MARGIN * 2.0;
					pQRLabel->Size->Height = h - PRINT_BORDER_MARGIN * 2.0;
				}
				else if(Col == 3)  //単位
				{
					//TQRLabel作成
					TQRLabel *pQRLabel     = new TQRLabel(pBand);
					pQRLabel->Parent       = pBand;

					DocFontInfToTFont(pGridDoc.Font,pQRLabel->Font,false);

					pQRLabel->AutoSize     = false;
					//寄せ
					pQRLabel->Alignment = pColDoc.Alignment;
					//ラベルの設定
					pQRLabel->Caption      = DispStr;
					pQRLabel->Size->Left   = x + PRINT_BORDER_MARGIN;
					pQRLabel->Size->Top    = y + PRINT_BORDER_MARGIN;
					pQRLabel->Size->Width  = w - PRINT_BORDER_MARGIN * 2.0;
					pQRLabel->Size->Height = h - PRINT_BORDER_MARGIN * 2.0;
				}
				else
				{
					if(pColDoc.FigureLine == true)
					{
						//桁区切り線印刷
						PrintColumnSeparateText(x,y,w,h,pGridDoc.Font,pColDoc.Figures,DispStr);
					}
					else
					{
						//TQRLabel作成
						TQRLabel *pQRLabel     = new TQRLabel(pBand);
						pQRLabel->Parent       = pBand;

						DocFontInfToTFont(pGridDoc.Font,pQRLabel->Font,false);

						pQRLabel->AutoSize     = false;
						//寄せ
						pQRLabel->Alignment = pColDoc.Alignment;
						//ラベルの設定
						pQRLabel->Caption      = DispStr;
						pQRLabel->Size->Left   = x + PRINT_BORDER_MARGIN;
						pQRLabel->Size->Top    = y + PRINT_BORDER_MARGIN;
						pQRLabel->Size->Width  = w - PRINT_BORDER_MARGIN * 2.0;
						pQRLabel->Size->Height = h - PRINT_BORDER_MARGIN * 2.0;
					}
				}
			}
		}
	}
}
//-------------------------------------------------------------
//パネルフォントサイズの計算
//-------------------------------------------------------------
int TSeikyuPrintForm::CalcPanelFontSize(int OrgFontSize)
{
	int NewFontSize;
	//印刷対象レポート
	TQuickRep *pRep = SeikyuPrintForm->SeikyuRep;
	//印刷フォントサイズ
	NewFontSize   = (ZoomDef[Document.Zoom].Zoom * OrgFontSize)/100;

	return NewFontSize;
}
//---------------------------------------------------------------------------


