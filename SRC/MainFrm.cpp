//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <algorithm>
using std::min;
using std::max;
#include <gdiplus.h>

#include "nsDebug.h"

#include "TLicense.h"
#include "strconv.h"
#include "nsFolderDlg.h"
#include "VersionInf.h"
#include "nsQRepPDF.h"
#include "FirstMesFrm.h"
#include "SeikyuPrintFrm.h"
#include "LabelModifyFrm.h"
#include "CompanyInfoFrm.h"
#include "CalendarFrm.h"
#include "ComponentsFrm.h"
#include "GridPropertyFrm.h"
#include "FigureSettingFrm.h"
#include "LicSetting.h"
#include "LicenseFrm.h"
#include "SettingFrm.h"
#include "SubSelectFrm.h"
#include "DispSettingFrm.h"
#include "TStdComponents.h"
#include "TZooms.h"
#include "TZips.h"
#include "TStdColumn.h"
#include "MainFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "XnsGrid"
#pragma link "PaintPanel"
#pragma link "EditAlignment"
#pragma link "ImageControl"
#pragma link "TWinLabel"
#pragma link "WinShape"
#pragma link "ComboBox2"
#pragma link "TBaseEdit"
#pragma link "ActionMainMenuBar2"
#pragma link "TListView2"
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
}
//-------------------------------------------------------------
//  機能     ：フォーム作成時
//
//  関数定義 ：void __fastcall FormCreate(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	//現在の時刻
	ClockTimerTimer(ClockTimer);
	//パネルへのドラグ＆ドロップを許可
	BasePanel->SetEnableDropFile(true);
}
//-------------------------------------------------------------
//  機能     ：フォーム表示時
//
//  関数定義 ：void __fastcall FormShow(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{
	//請求書番頭の設定を読み込む
	sbp::LoadSBSet(ES,false);
	//メインフォーム設定読み込み
	sbp::LoadMainFormSet();
	//郵便番号一覧を得る
	Zips.load();
	//自社情報の読み込み
	CompanyInfo.ReadCompanyInfo();
	//メッセージボックスのタイトル
	nsLib::SetMsgBoxTitle(SYSTEM_NAME);

	//書類情報の初期設定
	Document.Zoom    = Z100;
	Document.Paper   = A4P;
	Document.DocKind = pmSeikyu;

	//書類種類ボタンの表示を設定
	SetReportKindBtnDisp();
	//MainPanelを中央に移動する
	SetCenterMainPanel();
	//初回起動時のメッセージ表示
	if(IsFirstUse == true)
	{
		//初回起動時のメッセージ表示タイマー起動
		FirstTimer->Enabled = true;
	}
	//メインパネルの表示更新
	UpdateMainPanelDisp();

	//ラバーバンドを非表示
	RubberBand1->Hide();
	RubberBand2->Hide();
	RubberBand3->Hide();
	RubberBand4->Hide();
	RubberBand1->DefaultPaint = false;
	RubberBand2->DefaultPaint = false;
	RubberBand3->DefaultPaint = false;
	RubberBand4->DefaultPaint = false;
	//書類の履歴一覧読み込み処理
	LoadReportHist();
	//前回終了時の状態の復元を行う
	RemainSetting();
	//ライセンスチェックタイマー
	LicTimer->Enabled = true;
	//現在の時刻
	ClockTimerTimer(ClockTimer);
	//フォームアクティブ変動時のイベント
	Application->OnActivate = MainFormActivate;
	Application->OnDeactivate = MainFormDeactivate;
	//フォームアクティブで無い状態からスタート
	isFormActive = false;
	//時刻表示タイマー起動
	ClockTimer->Enabled = true;
	//フォームアクティブチェックタイマー起動
	FormActiveTimer->Enabled = true;
}
//-------------------------------------------------------------
// 機能     ：書類の履歴一覧読み込み処理
//
// 関数定義 ：bool LoadReportHist()
//
// ｱｸｾｽﾚﾍﾞﾙ ：
//
// 引数     ：
//
// 戻り値   ：
//
// 改定者   ：
//-------------------------------------------------------------
bool TMainForm::LoadReportHist()
{
	// 履歴一覧を取り込む
	Histories.load();
	// ListView初期化
	HistListView->Clear();
	// 表示抑制
	HistListView->Items->BeginUpdate();
	// 件数
	int SecNum = Histories.size();
	// 履歴からリストビューをセット
	for (int Cnt = 0; Cnt < SecNum; Cnt++)
	{
		// 履歴情報を得る
		THistory hist;
		if(Histories.get(Cnt,hist) == false)
		{
			continue;
		}
		// ListViewアイテム作成
		TListItem *pItem = HistListView->Items->Add();

		// ListViewアイテムセット
		pItem->Caption = String(hist.getYear()) + L"/" + hist.getMonth() + L"/" + hist.getDay(); // 日付
		pItem->SubItems->Add(hist.getName()); // 名前
		pItem->SubItems->Add(hist.getItem()); // 件名
		//紐づけるデータセット
		pItem->Data = new THistory(hist);
	}
	// ソート
	HistListView->AlphaSort();
	// 表示再開
	HistListView->Items->EndUpdate();
	//今開いている書類のIDで履歴一覧の行を選択する
	selectHistViewFromHistID(Document.HistID);

	return true;
}
//-------------------------------------------------------------
//  機能     ：前回終了時の状態の復元を行う
//
//  関数定義 ：void RemainSetting()
//
//  アクセスレベル ：private
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void TMainForm::RemainSetting()
{
	TReopen reInf;
	String  File;
	bool    IsParamOpen=false;

	//開くﾌｧｲﾙを得る
	if(ParamCount() >= 1)
	{
		File = ParamStr(1);
	}
	File = File.Trim();
	//ﾌｧｲﾙが指定されているなら開く
	if(File != "")
	{
		//ﾌｧｲﾙを開く
		OpenFile(File);
		//コマンドラインで開かれた
		IsParamOpen = true;
	}
	//コマンドラインで開かれないばあいは、通常の再開処理
	if(IsParamOpen == false)
	{
		bool IsFileOpen = false;
		//再開処理
		ES.IsRemain = TReopen::LoadReopenSet(reInf);
		if(ES.IsRemain == true)
		{
			//再開対象ファイルを開く
			if(OpenFile(reInf.histID) == true)
			{
				IsFileOpen = true;
			}
			//ファイルが開かれない場合は新規作成する
			if(IsFileOpen == false)
			{
				NewFile();
			}
		}
		else
		{
			NewFile();
		}
	}
	//書類種類ボタンの表示を設定
	SetReportKindBtnDisp();
	//繰り返し入力用情報を読む
	Inpts.Load();
	//今開いている書類のIDで履歴一覧の行を選択する
	selectHistViewFromHistID(Document.HistID);
}
//-------------------------------------------------------------
//今開いている書類のIDで履歴一覧の行を選択する
//-------------------------------------------------------------
bool TMainForm::selectHistViewFromHistID(const String& histID)
{
	//履歴の数
	int histNum = HistListView->Items->Count;
	//IDが一致するものを探す
	for(int idx = 0;idx < histNum;idx++)
	{
		//リストビューアイテムを得る
		TListItem *pItem = HistListView->Items->Item[idx];
		//紐づけられた履歴データを得る
		THistory *pHistData = static_cast<THistory*>(pItem->Data);

		// チェック
		if(pItem == nullptr || pItem->Data == nullptr)
		{
			continue;
		}
		//IDの比較
		if(pHistData->getID() == histID)
		{
			//一致するのでその行を選択して処理完了
			HistListView->Selected = pItem;

			return true;
		}
	}
	return false;
}
//-------------------------------------------------------------
//  機能     ：フォームを閉じる時
//
//  関数定義 ：void __fastcall FormClose(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	TReopen reInf;
	//再開処理のための保存
	if(Document.File != L"" && Document.HistID != L"")
	{
		//開いているファイルがある場合は追加
		reInf.sdoPath = Document.File;
		reInf.histID  = Document.HistID;
	}
	//再開情報保存処理
	TReopen::SaveReopenSet(ES.IsRemain,reInf);
	//繰り返し入力データの追加
	AddInputData();
	//繰り返し入力用情報を保存
	Inpts.Save();

	//レジストリ
	std::unique_ptr<SBRegIni> pReg(new SBRegIni);
	//レジストリから各部のデータセット
	pReg->WriteInteger(C_SYSTEM_SETTING,V_WINDOW_TOP ,Top);
	pReg->WriteInteger(C_SYSTEM_SETTING,V_WINDOW_LEFT,Left);
	pReg->WriteInteger(C_SYSTEM_SETTING,V_WINDOW_WIDTH ,Width);
	pReg->WriteInteger(C_SYSTEM_SETTING,V_WINDOW_HEIGHT,Height);
	//編集対象のコントロールを削除
	ResizeList.clear(MainPanel);
	//タイマーをとめる
	ClockTimer->Enabled = false;
	FormActiveTimer->Enabled = false;
}
//-------------------------------------------------------------
//  機能     ：初回起動時のメッセージ表示タイマー
//
//  関数定義 ：void __fastcall FirstTimerTimer(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::FirstTimerTimer(TObject *Sender)
{
	//タイマーを止める
	FirstTimer->Enabled = false;
	//メッセージ表示
	FirstMesForm->ShowModal();
}
//-------------------------------------------------------------
//  機能     ：印刷メニュー
//
//  関数定義 ：void __fastcall PrintBtnClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::PrintBtnClick(TObject *Sender)
{
	int          FontHeight;
	long double  dcy;
	long double  x,y,w,h;
	String       ValStr;

	//繰り返し入力データの追加
	AddInputData();
	//移動・大きさ変更を取りやめる
	CancelResizeMode(true);
	//リサイズモードを不許可にする
	SetResizeMode(false);
	//MainPanel上の値をデータにセット
	SetDocDataFromMainPanel();
	//印刷フォームの作成
	SeikyuPrintForm = new TSeikyuPrintForm(this);
	SeikyuPrintForm->Parent = this;
	//用紙の設定
	SeikyuPrintForm->SeikyuRep->Page->PaperSize    = PaperDef[Document.Paper].PaperSize;
	SeikyuPrintForm->SeikyuRep->Page->Orientation  = PaperDef[Document.Paper].Orientation;
	SeikyuPrintForm->SeikyuRep->Zoom               = 300;

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
	//パネル上のコンポーネントを印刷対象とする
	for(int Cnt = 0;Cnt < MainPanel->ControlCount;Cnt++)
	{


		TWinShape      *pShape;
		TWinLabel      *pWinLabel;
		TBorderEdit    *pBorderEdit;
		TImageControl  *pImage;
		XnsGrid        *pGrid;

		//パネル上のコントロールを得る
		TControl *pCtrl = MainPanel->Controls[Cnt];

		//コントロールのインデックス取得
		int resize_idx = ResizeList.findResizeCtrl(pCtrl);
		//あればば処理しない
		if(resize_idx >= 0)
		{
			continue;
		}
		//書類部品情報取得
		typDocCompo pDoc;
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
	//テストShape削除
	delete pQRTestShape;

	//ライセンス未設定の印刷
	if(LicenseSettingBtn->Visible == true)
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

	//印刷実行
	if(Sender == PDFBtn || Sender == PDFSaveMenu)
	{
		String FileName;
		//ファイル名設定処理
		if(PDFSaveDialog->Execute()==true)
			FileName = PDFSaveDialog->FileName;
		else
			return;
		//仮出力実行
		SeikyuPrintForm->SeikyuRep->Prepare();
		//PDF出力データ取得
		nsQRepPDF& QRepPDF = SeikyuPrintForm->QRepPDF;
		//PDFファイル出力を実行
		if(QRepPDF.MakePdfFile(FileName) == false)
		{
			nsLib::ErrMsgBox(Handle,"PDFファイル[%s]の保存に失敗しました。",FileName.c_str());
			return;
		}
	}
	else if(Sender == PrintPreviewMenu || Sender == PrintBtn)
	{
		//プレビュー
		SeikyuPrintForm->SeikyuRep->PreviewModal();
	}
	else
	{
		//印刷
		SeikyuPrintForm->SeikyuRep->Print();
	}
	//フォームの破棄
	delete SeikyuPrintForm;
}

//-------------------------------------------------------------
//  機能     ：部品情報のフォントの情報をTFontに反映
//
//  関数定義 ：void DocFontInfToTFont(typFontDef& FontDef,TFont *pFont,bool IsCalcSize)
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
void TMainForm::DocFontInfToTFont(typFontDef& FontDef,TFont *pFont,bool IsCalcSize)
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
//  機能     ：TFontのフォント情報を部品情報に反映
//
//  関数定義 ：void TFontToDocFontInf(typFontDef& FontDef,TFont *pFont,bool IsCalcSize)
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
void TMainForm::TFontToDocFontInf(typFontDef& FontDef,TFont *pFont,bool IsCalcSize)
{
	//フォント名
	FontDef.Name   = pFont->Name;
	//フォントサイズ
	if(IsCalcSize == true)
	{
		FontDef.Size = CalcPrintFontSize(pFont->Size);
	}
	else
	{
		FontDef.Size = pFont->Size;
	}
	//色
	FontDef.Color  = pFont->Color;
	//太字
	FontDef.Bold   = pFont->Style.Contains(fsBold);
	//イタリック
	FontDef.Italic = pFont->Style.Contains(fsItalic);
	//下線
	FontDef.Under  = pFont->Style.Contains(fsUnderline);
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
void TMainForm::PrintGrid()
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
	for(int Col = 0;Col < Grid->ColCount;Col++)
	{
		//列の情報
		typDocCompo pColDoc;

		ValStr.sprintf(L"D_%02d_%02d",0,Col);
		Document.GetDocCompoFromName(ValStr,pColDoc);

		for(int Row = 0;Row < Grid->RowCount;Row++)
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
			String DispStr = Grid->GetDispCellStr(Row,Col);

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
//  機能     ：桁区切り線ありの文字列を印刷
//
//  関数定義 ：void PrintColumnSeparateText(long double X,long double Y,long double W,long double H,typFontDef& FontDef,int Figures,String Str)
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
void TMainForm::PrintColumnSeparateText(long double X,long double Y,long double W,long double H,typFontDef& FontDef,int Figures,String Str)
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
//  機能     ：移動・大きさ変更が可能かチェックする
//
//  関数定義 ：bool CheckResizeMode()
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
bool TMainForm::CheckResizeMode()
{
	bool Res = ResizeEnableBtn->Down;

	return Res;
}
//-------------------------------------------------------------
//  機能     ：移動・大きさ変更が可能かセット
//
//  関数定義 ：void SetResizeMode(bool IsEnable)
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
void TMainForm::SetResizeMode(bool IsEnable)
{
	//不許可の場合はリサイズをキャンセル
	CancelResizeMode(true);

	//グリッドの列幅設定の許可
	if(IsEnable == true)
	{
		//編集ツールバー表示
		EditToolBar->Visible = true;
		//グリッドの列幅変更可能
		Grid->Options << goColSizing;
	}
	else
	{
		//編集ツールバー非表示
		EditToolBar->Visible = false;
		//グリッドの列幅変更不可
		Grid->Options >> goColSizing;
	}
	//ボタン状態設定
	ResizeEnableBtn->Down = IsEnable;
	//編集ツールバーの状態設定
	SetEditToolBarCondition();
}
//-------------------------------------------------------------
//  機能     ：移動・大きさ変更のコントロール追加
//
//  関数定義 ：nsResizeCtrl *AddResizeControl(TControl *pCtrl,bool IsLock)
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
nsResizeCtrl *TMainForm::AddResizeControl(TControl *pCtrl)
{
	nsResizeCtrl *pResizeCtrl;
	TBorderEdit  *pEdit;
	//除外コントロール
	if(pCtrl == RubberBand1 || pCtrl == RubberBand2 || pCtrl == RubberBand3 || pCtrl == RubberBand4)
	{
		return nullptr;
	}
	//既に同じコントロールがあるかチェック
	int resize_idx = ResizeList.findResizeCtrl(pCtrl);

	if(resize_idx >= 0)
	{
		return 0;
	}
	//リサイズコントロールの追加
	ResizeList.add(MainPanel,pCtrl,ResizeHide,ResizeCtrlMove,ResizeCtrlMouseDown,ResizeCtrlMouseUp);

	return pResizeCtrl;
}
//-------------------------------------------------------------
//  機能     ：移動・大きさ変更のコントロール削除
//
//  関数定義 ：bool DeleteResizeControl(nsResizeCtrl *pResizeCtrl,bool IsLock)
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
bool TMainForm::DeleteResizeControl(nsResizeCtrl *pResizeCtrl,bool IsLock)
{
	//既に同じコントロールがあるかチェック
	int resize_idx = ResizeList.findResizeCtrl(pResizeCtrl);

	//無ければ処理しない
	if(resize_idx < 0)
	{
		return true;
	}
	//リサイズコントロールの削除
	ResizeList.erase(resize_idx);

	return true;
}
//-------------------------------------------------------------
//  機能     ：コントロール移動・大きさ変更コントロールのマウスダウンイベント
//
//  関数定義 ：void __fastcall ResizeCtrlMouseDown(TObject *Sender, TMouseButton Button, Classes::TShiftState Shift, int X, int Y)
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
void __fastcall TMainForm::ResizeCtrlMouseDown(TObject *Sender,TMouseButton Button,Classes::TShiftState Shift, int X, int Y)
{
	//リサイズコントロールを得る
	nsResizeCtrl *pResizeCtrl = static_cast<nsResizeCtrl *>(Sender);
	//右クリックか？
	if(Button == mbRight)
	{
		//座標変換
		TPoint Pos = pResizeCtrl->ClientToScreen(TPoint(X,Y));
		//対象コントロール
		ModifyLabelPopupMenu->PopupComponent = pResizeCtrl;
		//ポップアップ表示
		ModifyLabelPopupMenu->Popup(Pos.x,Pos.y);
	}
}
//-------------------------------------------------------------
//  機能     ：コントロール移動・大きさ変更コントロールのマウスアップイベント
//
//  関数定義 ：void __fastcall ResizeCtrlMouseUp(TObject *Sender, TMouseButton Button, Classes::TShiftState Shift, int X, int Y)
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
void __fastcall TMainForm::ResizeCtrlMouseUp(TObject *Sender,TMouseButton Button,Classes::TShiftState Shift, int X, int Y)
{
	//リサイズコントロールを得る
	nsResizeCtrl *pResizeCtrl = static_cast<nsResizeCtrl *>(Sender);
	//右クリックか？
	if(Button == mbLeft)
	{
		//SHIFT押下チェック
		if(Shift.Contains(ssShift) == true)
		{
			//コントロール移動・大きさ変更コントロールの削除
			DeleteResizeControl(pResizeCtrl,true);
		}
	}
}
//-------------------------------------------------------------
//  機能     ：コントロール移動・大きさ変更のイベント
//
//  関数定義 ：void __fastcall ResizeCtrlMove(TObject *Sender,bool& IsUserMove,int dx,int dy,int dw,int dh)
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
void __fastcall TMainForm::ResizeCtrlMove(TObject *Sender,bool& IsUserMove,int dx,int dy,int dw,int dh,bool CtrlMove)
{
	//このイベントで移動を処理する
	IsUserMove = true;
	//リストに登録されているコントロールの移動
	for(int Cnt = 0;Cnt < ResizeList.size();Cnt++)
	{
		//移動・サイズ変更実行
		ResizeList[Cnt]->DMove(dx,dy,dw,dh,CtrlMove);
		//グリッド場合
		if(ResizeList[Cnt]->Control == Grid)
		{
			//グリッド行高さの調整
			AdjustRowHeights();
		}
	}
}
//-------------------------------------------------------------
//  機能     ：移動・大きさ変更を取りやめる
//
//  関数定義 ：bool CancelResizeMode(bool IsLock)
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
bool TMainForm::CancelResizeMode(bool IsLock)
{
	//対象の有無チェック
	if(ResizeList.size() == 0)
	{
		return true;
	}
	//リサイズコンポーネント削除
	try
	{
		ResizeList.clear(MainPanel);
	}
	__finally
	{
		//MainPanel上にデータをセット
		SetDataFromDocData();
		//編集ツールバーの状態設定
		SetEditToolBarCondition();
	}
	return true;
}
//-------------------------------------------------------------
//  機能     ：現在の用紙の縦、横ピクセル数を得る
//
//  関数定義 ：bool GetPaperPixel()
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
bool TMainForm::GetPaperPixel()
{
	//印刷フォームの作成
	SeikyuPrintForm = new TSeikyuPrintForm(this);
	SeikyuPrintForm->Parent = this;
	//印刷対象レポート
	TQuickRep *pRep = SeikyuPrintForm->SeikyuRep;
	//サイズの変更
	pRep->Page->PaperSize    = PaperDef[Document.Paper].PaperSize;
	pRep->Page->Orientation  = PaperDef[Document.Paper].Orientation;
	//ズーム
	pRep->Zoom               = ZoomDef[Document.Zoom].Zoom;
	//カスタムの時のサイズ設定処理
	if(PaperDef[Document.Paper].PaperSize == Custom)
	{
		pRep->Page->Length = PaperDef[Document.Paper].PaperLength;
		pRep->Page->Width  = PaperDef[Document.Paper].PaperWidth;
	}
	//ピクセル数取得
	PaperWidthPixel  = pRep->Width;
	PaperHeightPixel = pRep->Height;
	//用紙幅、高さ取得
	PaperWidth       = pRep->Page->Width;
	PaperHeight      = pRep->Page->Length;
	//印刷フォーム削除
	delete SeikyuPrintForm;

	return true;
}
//-------------------------------------------------------------
//  機能     ：用紙上の位置からパネル上のX座標ピクセルを計算
//
//  関数定義 ：int GetPanelPixelFromPaperPosX(long double PX)
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
int TMainForm::GetPanelPixelFromPaperPosX(long double PX)
{
	long double dx;
	int         X;
	char        buf[64];
	char       *p;
	//long doble型でパネル上のピクセルを計算
	dx = (static_cast<long double>(PaperWidthPixel) * PX) / PaperWidth;
	//dxを四捨五入する
	sprintf(buf,"%Lf",dx);
	p = strchr(buf,'.');
	if(p == 0)
	{
		//そのまま整数にする
		X = atoi(buf);
	}
	else
	{
		//繰上げするか？
		if(p[1] >= '5' && p[1] <= '9')
		{
			//小数点以下削除
			p[0] = '\0';
			//繰上げ
			X = atoi(buf) + 1;
		}
		else
		{
			//小数点以下削除
			p[0] = '\0';
			//切捨て
			X = atoi(buf);
		}
	}
	return X;
}
//-------------------------------------------------------------
//  機能     ：用紙上の位置からパネル上のY座標ピクセルを計算
//
//  関数定義 ：int GetPanelPixelFromPaperPosY(long double PY)
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
int TMainForm::GetPanelPixelFromPaperPosY(long double PY)
{
	long double dy;
	int         Y;
	char        buf[64];
	char       *p;
	//long doble型でパネル上のピクセルを計算
	dy = (static_cast<long double>(PaperHeightPixel) * PY) / PaperHeight;
	//dyを四捨五入する
	dy = std::round(dy);

	return dy;
}
//-------------------------------------------------------------
//  機能     ：パネル上のX座標ピクセルから用紙上の位置を計算
//
//  関数定義 ：long double GetPaperPosXFromPanelPixel(int dx)
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
long double TMainForm::GetPaperPosXFromPanelPixel(int dx)
{
	long double PX;
	//long doble型で用紙上の位置
	PX = (static_cast<long double>(dx) * PaperWidth) / static_cast<long double>(PaperWidthPixel);

	return PX;
}
//-------------------------------------------------------------
//  機能     ：パネル上のY座標ピクセルから用紙上の位置を計算
//
//  関数定義 ：long double GetPaperPosYFromPanelPixel(int dy)
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
long double TMainForm::GetPaperPosYFromPanelPixel(int dy)
{
	long double PY;
	//long doble型で用紙上の位置
	PY = (static_cast<long double>(dy) * PaperHeight) / static_cast<long double>(PaperHeightPixel);

	return PY;
}
//-------------------------------------------------------------
//  機能     ：書類部品情報からグリッドを配置
//
//  関数定義 ：bool SetGridFromDocCompo()
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
bool TMainForm::SetGridFromDocCompo()
{
	String       ValStr;
	typDocCompo  pFirstCellDoc;
	typDocCompo  pGridDoc;
	typDocCompo  pDoc;
	bool         Res;

	//--- グリッド行の表示更新 ---

	//グリッドの情報
	if(Document.GetDocCompoFromName(StdComponents[scStdComponent::scGrid].Name,pGridDoc) == false)
	{
		//見つからない場合はテンプレートフォームからセット
		Res = SetComponentFromTemplateForm(StdComponents[scStdComponent::scGrid].Name);

		return Res;
	}
	//行数と列数
	Grid->RowCount  = pGridDoc.RowNum;
	Grid->ColCount  = pGridDoc.ColNum;

	//グリッドの左上座標決定
	Grid->Left    = GetPanelPixelFromPaperPosX(pGridDoc.X);
	Grid->Top     = GetPanelPixelFromPaperPosY(pGridDoc.Y);
	//フォントの設定
	DocFontInfToTFont(pGridDoc.Font,Grid->Font,true);
	//最初のセルの情報
	Document.GetDocCompoFromName(L"D_00_00",pFirstCellDoc);
	//グリッドの下位置
	long double  GridBottom = pGridDoc.Y + pGridDoc.Height;
	//グリッドの高さ変更
	Grid->Height = GetPanelPixelFromPaperPosY(pGridDoc.Y + pGridDoc.Height) - Grid->Top + 1;
	//グリッド行高さの調整
	AdjustRowHeights();

	//--- グリッド列の表示更新 ---
	int         SumGridWidth = 0;
	int         ColWidthSum  = 0;
	//グリッドの列幅変更イベントをハンドリングしない
	SetGridColWidthsChangedEvent(false);
	//一列目のタイトル
	Grid->Cells[0][0] = pFirstCellDoc.Caption;
	//列幅と２列目以降のタイトル
	for(int Cnt = 1;Cnt < Grid->ColCount;Cnt++)
	{
		//セルの情報(先頭行)
		ValStr.sprintf(L"D_%02d_%02d",0,Cnt);
		Document.GetDocCompoFromName(ValStr,pDoc);
		//データセット
		Grid->Cells[Cnt][0]     = pDoc.Caption;
		Grid->ColWidths[Cnt-1]  = GetPanelPixelFromPaperPosX(pDoc.X) - Grid->Left - SumGridWidth;
		SumGridWidth           += Grid->ColWidths[Cnt-1];
	}
	ValStr.sprintf(L"D_%02d_%02d",0,Grid->ColCount - 1);
	Document.GetDocCompoFromName(ValStr,pDoc);
	Grid->ColWidths[Grid->ColCount - 1] = GetPanelPixelFromPaperPosX(pDoc.X + pDoc.Width)  - Grid->Left - SumGridWidth + 1;
	//各列の幅の合計を得る
	for(int Cnt = 0;Cnt < Grid->ColCount;Cnt++)
	{
		//加算
		ColWidthSum += Grid->ColWidths[Cnt];
	}
	//グリッド本体の幅設定
	Grid->Width = ColWidthSum;
	//グリッドの列幅変更イベントをハンドリングする
	SetGridColWidthsChangedEvent(true);

	return true;
}
//-------------------------------------------------------------
//  機能     ：グリッド行高さの調整
//
//  関数定義 ：bool AdjustRowHeights()
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
bool TMainForm::AdjustRowHeights()
{
	//デフォルト行高さ
	Grid->DefaultRowHeight = (Grid->Height / Grid->RowCount);
	//調整値を得る
	int DiffY = Grid->Height - Grid->RowCount * Grid->DefaultRowHeight;
	//調整
	if(DiffY > 0)
	{
		for(int Cnt = 0;Cnt < DiffY;Cnt++)
		{
			Grid->RowHeights[Cnt] = Grid->RowHeights[Cnt] + 1;
		}
	}
	else if(DiffY < 0)
	{
		DiffY = -DiffY;

		for(int Cnt = 0;Cnt < DiffY;Cnt++)
		{
			Grid->RowHeights[Cnt] = Grid->RowHeights[Cnt] - 1;
		}
	}
	return true;
}
//-------------------------------------------------------------
//  機能     ：コントロールを作成する
//
//  関数定義 ：TControl *CreateControl(String CtrlName,dcDocComponent Type)
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
TControl *TMainForm::CreateControl(String CtrlName,dcDocComponent Type)
{
	TControl *pCtrl = nullptr;
	//部品の種類ごとに作成
	switch(Type)
	{
		case dcLabel:
		{
			TWinLabel *pLbl = new TWinLabel(MainPanel);

			pLbl->Parent      = MainPanel;
			pLbl->Name        = CtrlName;
			pLbl->Layout      = tlCenter;
			pLbl->Pen->Color  = clBlack;
			pLbl->OnMouseDown = ObjectMouseDown;
			pLbl->OnDblClick  = ObjectDblClick;
			pCtrl             = pLbl;
			break;
		}
		case dcEdit:
		{
			TBorderEdit *pEdit = new TBorderEdit(MainPanel);

			pEdit->Parent        = MainPanel;
			pEdit->Name          = CtrlName;
			pEdit->BorderDraw    = false;
			pEdit->Color         = MainPanel->Color;
			pEdit->Pen->Color    = clBlack;
			pEdit->Alignment     = taLeftJustify;
			pEdit->TabStop       = true;
			pEdit->OnMouseDown   = ObjectMouseDown;
			pEdit->OnEnter       = EditEnter;
			pEdit->OnExit        = EditExit;
			pEdit->OnKeyDown     = EditKeyDown;
			pEdit->OnKeyPress    = EditKeyPress;
			pEdit->OnChange      = EditChange;
			pEdit->OnDblClick    = EditDblClick;
			pEdit->Text          = "";
			pEdit->ColPen->Color = clBlack;
			pEdit->ColPen->Style = psDot;
			pCtrl                = pEdit;
			break;
		}
		case dcDayEdit:
		{
			TBorderEdit *pEdit = new TBorderEdit(MainPanel);

			pEdit->Parent        = MainPanel;
			pEdit->Name          = CtrlName;
			pEdit->BorderDraw    = false;
			pEdit->Color         = MainPanel->Color;
			pEdit->Pen->Color    = clBlack;
			pEdit->Alignment     = taRightJustify;
			pEdit->OnMouseDown   = ObjectMouseDown;
			pEdit->OnEnter       = EditEnter;
			pEdit->OnExit        = EditExit;
			pEdit->OnKeyDown     = EditKeyDown;
			pEdit->OnKeyPress    = EditKeyPress;
			pEdit->OnChange      = EditChange;
			pEdit->OnDblClick    = ObjectDblClick;
			pEdit->Text          = "";
			pEdit->ColPen->Color = clBlack;
			pEdit->ColPen->Style = psDot;
			pCtrl                = pEdit;
			break;
		}
		case dcMoneyEdit:
		{
			TBorderEdit *pEdit = new TBorderEdit(MainPanel);

			pEdit->Parent        = MainPanel;
			pEdit->Name          = CtrlName;
			pEdit->BorderDraw    = false;
			pEdit->Color         = MainPanel->Color;
			pEdit->Pen->Color    = clBlack;
			pEdit->Alignment     = taRightJustify;
			pEdit->OnMouseDown   = ObjectMouseDown;
			pEdit->OnEnter       = EditEnter;
			pEdit->OnExit        = DecimalPointModificationMoneyExit;
			pEdit->OnKeyDown     = EditKeyDown;
			pEdit->OnKeyPress    = InputRelatedMoneyKeyPress;
			pEdit->OnChange      = EditChange;
			pEdit->OnDispStr     = MoneyDispStr;
			pEdit->ColPen->Color = clBlack;
			pEdit->ColPen->Style = psDot;
			pCtrl                = pEdit;

			break;
		}
		case dcImage:
		{
			TImageControl *pImage = new TImageControl(MainPanel);

			pImage->Parent      = MainPanel;
			pImage->Name        = CtrlName;
			pImage->OnMouseDown = ObjectMouseDown;
			pImage->OnDblClick  = ObjectDblClick;
			pCtrl               = pImage;
			break;
		}
		case dcCLine:
		case dcVLine:
		{
			TWinShape *pShape = new TWinShape(MainPanel);

			pShape->Parent       = MainPanel;
			pShape->Name         = CtrlName;
			pShape->Shape        = wsHorLine;
			pShape->Pen->Color   = clBlack;
			pShape->OnMouseDown  = ObjectMouseDown;
			pCtrl                = pShape;
			break;
		}
		default:
		{
			break;
		}
	}
	return pCtrl;
}
//-------------------------------------------------------------
//  機能     ：MainPanelから指定Nameのコントロールを得る
//
//  関数定義 ：TControl *FindControlFromMainPanel(String Name)
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
TControl *TMainForm::FindControlFromMainPanel(String Name)
{
	for(int Cnt=0;Cnt < MainPanel->ControlCount;Cnt++)
	{
		TControl *pCtrl = MainPanel->Controls[Cnt];

		if(pCtrl->Name == Name)
		{
			return pCtrl;
		}
	}
	return 0;
}
//-------------------------------------------------------------
//  機能     ：書類部品情報からコンポーネントを配置
//
//  関数定義 ：bool SetComponentFromDocCompo(typDocCompo& pDoc)
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
bool TMainForm::SetComponentFromDocCompo(typDocCompo& pDoc)
{
	String         ValStr;
	TWinLabel     *pWinLabel;
	TBorderEdit   *pBorderEdit;
	TWinShape     *pShape;
	TImageControl *pImage;

	//名前からコントロールを得る
	TControl *pCtrl = FindControlFromMainPanel(pDoc.Name);
	//コンポーネントの型を得る
	dcDocComponent Type = GetComponentType(pCtrl);
	//コンポーネント名から標準コンポーネント情報を得る
	typStdComponentDef pStdCompo;
	bool std_vaild = typDocKindDefs::GetStdComponentDefFromName(pDoc.Name,pStdCompo,Document.DocKind);

	//コンポーネントの作成・書類部品の型設定
	if(Type == dcUnknown && pDoc.Type == dcUnknown && std_vaild == false)
	{
		//作成不可
		return false;
	}
	else if(pDoc.Type == dcUnknown && Type != dcUnknown)
	{
		pDoc.Type = Type;
	}
	else if(std_vaild == true && (Type == dcUnknown || Type != pStdCompo.Type))
	{
		bool IsBorderEdit    = (Type == dcEdit            || Type == dcDayEdit            || Type == dcMoneyEdit);
		bool IsStdBorderEdit = (pStdCompo.Type == dcEdit  || pStdCompo.Type == dcDayEdit  || pStdCompo.Type == dcMoneyEdit);

		if((IsBorderEdit == true && IsStdBorderEdit == true) == false)
		{
			//コンポーネント削除
			delete pCtrl;
			//部品の種類ごとに作成
			pCtrl = CreateControl(pDoc.Name,pStdCompo.Type);
		}
	}
	else if(pDoc.Type != Type)
	{
		bool IsBorderEdit    = (Type == dcEdit            || Type == dcDayEdit            || Type == dcMoneyEdit);
		bool IsStdBorderEdit = (pStdCompo.Type == dcEdit  || pStdCompo.Type == dcDayEdit  || pStdCompo.Type == dcMoneyEdit);

		if((IsBorderEdit == true && IsStdBorderEdit == true) == false)
		{
			//コンポーネント削除
			delete pCtrl;
			//部品の種類ごとに作成
			pCtrl = CreateControl(pDoc.Name,pStdCompo.Type);
		}
	}
	//ヒントの設定
	if(std_vaild == true)
	{
		pCtrl->Hint     = pStdCompo.Explain;
		pCtrl->ShowHint = true;
	}
	//ラベルかチェックする
	if((pWinLabel = dynamic_cast<TWinLabel *>(pCtrl)) != 0)
	{
		//設定
		pWinLabel->Left          = GetPanelPixelFromPaperPosX(pDoc.X);
		pWinLabel->Top           = GetPanelPixelFromPaperPosY(pDoc.Y);
		pWinLabel->Width         = GetPanelPixelFromPaperPosX(pDoc.X + pDoc.Width) - pWinLabel->Left + 1;
		pWinLabel->Height        = GetPanelPixelFromPaperPosY(pDoc.Y + pDoc.Height) - pWinLabel->Top + 1;
		DocFontInfToTFont(pDoc.Font,pWinLabel->Font,true);
		pWinLabel->Alignment     = pDoc.Alignment;
		pWinLabel->BorderDraw    = pDoc.Border;
		pWinLabel->Caption       = pDoc.Caption;
		pWinLabel->Visible       = pDoc.Visible;
		pWinLabel->NoCaptionDraw = true;
		if(std_vaild == true)
		{
			pWinLabel->NoCaption = pStdCompo.NoCaption;
		}
	}
	//BorderEditかチェックする
	else if((pBorderEdit = dynamic_cast<TBorderEdit *>(pCtrl)) != 0)
	{
		//設定
		pBorderEdit->Left          = GetPanelPixelFromPaperPosX(pDoc.X);
		pBorderEdit->Top           = GetPanelPixelFromPaperPosY(pDoc.Y);
		pBorderEdit->Width         = GetPanelPixelFromPaperPosX(pDoc.X + pDoc.Width ) - pBorderEdit->Left + 1;
		pBorderEdit->Height        = GetPanelPixelFromPaperPosY(pDoc.Y + pDoc.Height) - pBorderEdit->Top + 1;
		DocFontInfToTFont(pDoc.Font,pBorderEdit->Font,true);
		pBorderEdit->Alignment     = pDoc.Alignment;
		pBorderEdit->BorderDraw    = (pDoc.Border == true);
		pBorderEdit->Visible       = pDoc.Visible;
		pBorderEdit->NoCaptionDraw = true;
		//金額入力関連設定
		if(pDoc.Type == dcMoneyEdit)
		{
			pBorderEdit->ColSeparateNum  = pDoc.Figures;
			pBorderEdit->ColSeparateDraw = pDoc.FigureLine;
		}
		if(std_vaild == true)
		{
			pBorderEdit->NoCaption = pStdCompo.NoCaption;
		}
	}
	else if((pShape = dynamic_cast<TWinShape *>(pCtrl)) != 0)
	{
		//設定
		pShape->Left       = GetPanelPixelFromPaperPosX(pDoc.X);
		pShape->Top        = GetPanelPixelFromPaperPosY(pDoc.Y);
		//縦線か横線か決定
		if(pDoc.Type == dcUnknown)
		{
			if(pDoc.Width <= pDoc.Height / 20.0)
			{
				pDoc.Type = dcVLine;
			}
			else if(pDoc.Height <= pDoc.Width / 20.0)
			{
				pDoc.Type = dcCLine;
			}
		}
		//幅の設定
		if(pDoc.Type == dcCLine)
		{
			int W = GetPanelPixelFromPaperPosX(pDoc.Width);
			pShape->Width      = (W < 2)?2:W;
			pShape->Height     = 1;
		}
		else if(pDoc.Type == dcVLine)
		{
			pShape->Width      = 2;
			int H = GetPanelPixelFromPaperPosY(pDoc.Height);
			pShape->Height     = (H < 2)?2:H;
		}
		else
		{
			int W = GetPanelPixelFromPaperPosX(pDoc.Width);
			pShape->Width      = (W < 2)?2:W;
			int H = GetPanelPixelFromPaperPosY(pDoc.Height);
			pShape->Height     = (H < 2)?2:H;
		}

		pShape->Visible    = pDoc.Visible;
	}
	//イメージかチェックする
	else if((pImage = dynamic_cast<TImageControl *>(pCtrl)) != 0)
	{
		bool IsDrawImage = true;
		//設定
		pImage->Left       = GetPanelPixelFromPaperPosX(pDoc.X);
		pImage->Top        = GetPanelPixelFromPaperPosY(pDoc.Y);
		pImage->Width      = GetPanelPixelFromPaperPosX(pDoc.X + pDoc.Width ) - pImage->Left + 1;
		pImage->Height     = GetPanelPixelFromPaperPosY(pDoc.Y + pDoc.Height) - pImage->Top + 1;
		pImage->Center     = true;
		pImage->Zoom       = ZoomDef[Document.Zoom].Zoom;

		if(pDoc.Border == true)
		{
			pImage->Pen->Color = clBlack;
			pImage->Pen->Style = psSolid;
			pImage->BorderDraw = true;
		}
		else
		{
			pImage->Pen->Color = clBlack;
			pImage->Pen->Style = psDot;
			pImage->BorderDraw = true;
		}
		pImage->Visible    = pDoc.Visible;
	}

	return true;
}
//-------------------------------------------------------------
//  機能     ：書類情報からコンポーネントを配置
//
//  関数定義 ：bool SetComponentFromDocumentInfo()
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
bool TMainForm::SetComponentFromDocumentInfo()
{
	TForm       *pTemplateForm;
	bool         IsUseTemplate;

	//部品情報からコンポーネント配置
	for(int Cnt = 0;Cnt < Document.GetCompoSize();Cnt++)
	{
		//対象部品
		typDocCompo& pDoc = Document.GetCompoFromIndex(Cnt);
		//用紙のチェック
		if(pDoc.Paper != Document.Paper)
		{
			continue;
		}
		//書類種類のチェック
		if(pDoc.DocKind != Document.DocKind)
		{
			continue;
		}
		//グリッド関連は省く
		if(pDoc.Type == dcGrid || pDoc.Type == dcCell)
		{
			continue;
		}
		//書類部品情報からコンポーネントを配置
		SetComponentFromDocCompo(pDoc);
	}
	//現在の用紙に対応するテンプレートフォームを得る
	pTemplateForm = TPaperDefs::getTemplateFormPaper(Document.Paper);

	//テンプレートパネル上のコンポーネントを設定対象とする
	for(int Cnt = 0;Cnt < STD_COMPONENT_NUM;Cnt++)
	{
		try
		{
			//コントロールの名前を得る
			String CtrlName = StdComponents[Cnt].Name;
			//書類部品情報があるか
			typDocCompo pDoc;
			bool doc_valid = Document.GetDocCompoFromName(CtrlName,pDoc);
			//コンポーネントはあるか
			TControl *pCtrl = FindControlFromMainPanel(CtrlName);
			//コンポーネントの配置
			if(doc_valid == false || pCtrl == nullptr)
			{
				//テンプレートを使用した
				IsUseTemplate = true;
				//見つからない場合はテンプレートフォームからセット
				SetComponentFromTemplateForm(CtrlName);
			}
		}
		catch(...)
		{
		}
	}
	//TabOrderの設定
	SetTabOrder(MainPanel);

	return true;
}
//-------------------------------------------------------------
//  機能     ：テンプレートフォームからコンポーネントをセット
//
//  関数定義 ：bool SetComponentFromTemplateForm(String CtrlName)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：String  CtrlName   コンポーネント名
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
bool TMainForm::SetComponentFromTemplateForm(String CtrlName)
{
	TForm           *pTemplateForm;
	bool             IsGrid          = false;
	TWinLabel       *pWinLabel       = 0;
	TWinLabel       *pTWinLabel      = 0;
	TBorderEdit     *pBorderEdit     = 0;
	TBorderEdit     *pTBorderEdit    = 0;
	TImageControl   *pImage          = 0;
	TImageControl   *pTImage         = 0;
	TWinShape       *pTShape         = 0;
	TWinShape       *pShape          = 0;
	XnsGrid         *pTGrid          = 0;
	XnsGrid         *pGrid           = 0;
	dcDocComponent   TType;
	dcDocComponent   Type;
	TFormBorderStyle BorderStyle = bsNone;
	int              OrgFontSize;

	//グリッドの特別処理
	if(CtrlName == StdComponents[scStdComponent::scGrid].Name)
	{
		IsGrid   = true;
	}

	//現在の用紙に対応するテンプレートフォームを得る
	pTemplateForm = TPaperDefs::getTemplateFormPaper(Document.Paper);

	//名前に一致するテンプレートのコンポーネントを得る
	TComponent *pTCompo = pTemplateForm->FindComponent(CtrlName);
	//一致しない場合は処理しない
	if(pTCompo == nullptr || pTCompo->Name != CtrlName)
	{
		return false;
	}
	//名前に一致するコンポーネントを得る
	TControl   *pCtrl  = FindControlFromMainPanel(CtrlName);
	//コンポーネント名から標準コンポーネント情報を得る
	typStdComponentDef  pStdCompo;
	bool std_valid = typDocKindDefs::GetStdComponentDefFromName(CtrlName,pStdCompo,Document.DocKind);
	//該当しない場合は処理しない
	if(std_valid == false)
	{
		return false;
	}
	else if((pTWinLabel = dynamic_cast<TWinLabel *>(pTCompo))!=nullptr)
	{
		//ラベル
		TType = dcLabel;
		//枠あり
		BorderStyle = bsSingle;
		//元のフォントサイズ
		OrgFontSize = pTWinLabel->Font->Size;
	}
	else if((pTBorderEdit = dynamic_cast<TBorderEdit *>(pTCompo))!=nullptr)
	{
		//枠つきEdit
		TType = dcMoneyEdit;
		//元のフォントサイズ
		OrgFontSize = pTBorderEdit->Font->Size;
	}
	else if((pTImage = dynamic_cast<TImageControl *>(pTCompo))!=nullptr)
	{
		//画像
		TType = dcImage;
	}
	else if((pTShape = dynamic_cast<TWinShape *>(pTCompo))!=nullptr)
	{
		//Shape
		if(pTShape->Height <= 2)
			TType = dcCLine;
		else
			TType = dcVLine;
	}
	else if((pTGrid = dynamic_cast<XnsGrid *>(pTCompo))!=nullptr)
	{
		//Grid
		TType = dcGrid;
	}
	else
	{
		//不明
		TType = dcUnknown;
	}
	//コンポーネントの型を得る
	Type = GetComponentType(pCtrl);
	//型が一致しない場合は、一旦破棄して作成する
	if(TType != Type || pStdCompo.Type != Type)
	{
		//破棄
		delete pCtrl;
		//コントロールを作成する
		pCtrl = CreateControl(CtrlName,pStdCompo.Type);
		//型セット
		Type = pStdCompo.Type;
	}
	//テンプレートフォームのズーム
	int TZoom = pTemplateForm->Tag;
	//現在のズーム
	int Zoom  = ZoomDef[Document.Zoom].Zoom;
	//コントロールにキャスト
	TControl *pTCtrl = dynamic_cast<TControl *>(pTCompo);
	//コントロールにキャスト出来ない場合は処理しない
	if(pTCtrl == 0 || pCtrl == 0)
	{
		return false;
	}
	int CtrlBottom;
	int CtrlLeft;

	//座標セット
	pCtrl->Left   = (Zoom * pTCtrl->Left  )/TZoom;
	pCtrl->Top    = (Zoom * pTCtrl->Top   )/TZoom;
	//幅の設定
	CtrlLeft = pTCtrl->Left + pTCtrl->Width - 1;
	pCtrl->Width  = (Zoom * CtrlLeft)/TZoom - pCtrl->Left + 1;
	//高さの設定
	CtrlBottom = pTCtrl->Top + pTCtrl->Height - 1;
	pCtrl->Height  = (Zoom * CtrlBottom)/TZoom - pCtrl->Top + 1;

	//書類部品情報の取得
	typDocCompo pDoc;
	bool doc_valid = Document.GetDocCompoFromName(CtrlName,pDoc);
	//見つからない場合は作成する
	if(doc_valid == false)
	{
		//作成する
		pDoc.Paper    = Document.Paper;
		pDoc.DocKind  = Document.DocKind;
		pDoc.Name     = CtrlName;
		pDoc.Visible  = pStdCompo.Visible;
		pDoc.IsPrint  = true;
	}
	pDoc.Type       = pStdCompo.Type;
	pDoc.Alignment  = pStdCompo.Alignment;
	pDoc.Border     = pStdCompo.Border;
	pDoc.Font.Size  = CalcPrintFontSize((Zoom * OrgFontSize)/TZoom);
	pDoc.Caption    = pStdCompo.Value;
	pDoc.Figures    = DEFAULT_FIGURES;
	pDoc.FigureLine = false;
	//書類部品情報のセット
	Document.SetDocCompoFromName(CtrlName,pDoc);

	//グリッドの列幅変更イベントをハンドリングしない
	SetGridColWidthsChangedEvent(false);
	//グリッドの特別処理
	if(IsGrid == true)
	{
		//グリッドを得る
		XnsGrid *pGrid  = static_cast<XnsGrid *>(pCtrl);
		XnsGrid *pTGrid = static_cast<XnsGrid *>(pTCtrl);
		//行数
		pGrid->RowCount = pTGrid->RowCount;
		//列数
		pGrid->ColCount = pTGrid->ColCount;
		//フォント
		pGrid->Font->Size = (Zoom * pTGrid->Font->Size)/TZoom;
		//各列の幅
		for(int Col = 0,TColSum=0,ColSum=0;Col < pTGrid->ColCount;Col++)
		{
			if(Col < pTGrid->ColCount - 1)
			{
				//右端
				int cw    = pTGrid->ColWidths[Col];
				int Right = pTGrid->Left + TColSum + cw;
				//幅セット
				int wi = (Zoom * Right)/TZoom - ColSum - pGrid->Left;
				pGrid->ColWidths[Col]  = wi;
				TColSum               += pTGrid->ColWidths[Col];
				ColSum                += pGrid ->ColWidths[Col];
			}
			else
			{
				//最終列
				//右端
				int Right = pTGrid->Left + pTGrid->Width - 1;
				//幅セット
				pGrid->ColWidths[Col]  = (Zoom * Right)/TZoom - ColSum - pGrid->Left + 1;
			}
		}
		//グリッド行高さの調整
		AdjustRowHeights();
	}
	//グリッドの列幅変更イベントをハンドリングする
	SetGridColWidthsChangedEvent(true);
	//ドキュメント情報にコントロールの情報セット
	SetDocControl(pCtrl);

	return true;
}
//-------------------------------------------------------------
//  機能     ：コントロールのTextまたはCaptionを得る
//
//  関数定義 ：String GetControlStrValue(TControl *pCtrl)
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
String TMainForm::GetControlStrValue(TControl *pCtrl)
{
	TWinLabel    *pWinLabel;
	TBorderEdit *pBorderEdit;
	String       Val;
	//型別処理
	if((pWinLabel = dynamic_cast<TWinLabel *>(pCtrl))!=nullptr)
	{
		Val = pWinLabel->Caption;
	}
	else if((pBorderEdit = dynamic_cast<TBorderEdit *>(pCtrl))!=nullptr)
	{
		Val = pBorderEdit->Text;
	}
	return Val;
}
//-------------------------------------------------------------
//  機能     ：コンポーネントの型を得る
//
//  関数定義 ：dcDocComponent GetComponentType(TComponent *pCompo)
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
dcDocComponent TMainForm::GetComponentType(TComponent *pCompo)
{
	TWinLabel       *pWinLabel   = nullptr;
	TBorderEdit     *pBorderEdit = nullptr;
	TImageControl   *pImage      = nullptr;
	TWinShape       *pShape      = nullptr;
	XnsGrid         *pGrid       = nullptr;
	dcDocComponent   Type;
	//コンポーネントの型を得る
	if(pCompo == nullptr)
	{
		//不明
		Type = dcUnknown;
	}
	else if((pWinLabel = dynamic_cast<TWinLabel *>(pCompo)) != nullptr)
	{
		//ラベル
		Type = dcLabel;
	}
	else if((pBorderEdit = dynamic_cast<TBorderEdit *>(pCompo)) != nullptr)
	{
		//枠つきEdit
		Type = dcMoneyEdit;
	}
	else if((pImage = dynamic_cast<TImageControl *>(pCompo)) != nullptr)
	{
		//画像
		Type = dcImage;
	}
	else if((pShape = dynamic_cast<TWinShape *>(pCompo)) != nullptr)
	{
		//Shape
		if(pShape->Height <= 2)
		{
			//横線
			Type = dcCLine;
		}
		else
		{
			//縦線
			Type = dcVLine;
		}
	}
	else if((pGrid = dynamic_cast<XnsGrid *>(pCompo)) != nullptr)
	{
		//画像
		Type = dcGrid;
	}
	else
	{
		//不明
		Type = dcUnknown;
	}
	return Type;
}
//-------------------------------------------------------------
//  機能     ：印刷フォントサイズの計算
//
//  関数定義 ：int CalcPrintFontSize(int OrgFontSize)
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
int TMainForm::CalcPrintFontSize(int OrgFontSize)
{
	int NewFontSize;
	//印刷対象レポート
	TQuickRep *pRep = SeikyuPrintForm->SeikyuRep;
	//印刷フォントサイズ
	NewFontSize   = (100 * OrgFontSize)/ZoomDef[Document.Zoom].Zoom;

	return NewFontSize;
}
//-------------------------------------------------------------
//  機能     ：パネルフォントサイズの計算
//
//  関数定義 ：int CalcPanelFontSize(int OrgFontSize)
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
int TMainForm::CalcPanelFontSize(int OrgFontSize)
{
	int NewFontSize;
	//印刷対象レポート
	TQuickRep *pRep = SeikyuPrintForm->SeikyuRep;
	//印刷フォントサイズ
	NewFontSize   = (ZoomDef[Document.Zoom].Zoom * OrgFontSize)/100;

	return NewFontSize;
}
//-------------------------------------------------------------
//  機能     ：セル属性設定(在庫一覧)
//
//  関数定義 ：void __fastcall StockGridCellAttr(...)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::GridCellAttr(TObject *Sender, int ARow,
	  int ACol, TColor &BackColor, int &FontNumber, StrPosX &PosX,
	  StrPosY &PosY, VARIANT_BOOL &CellMerge, int &cmLeft, int &cmRight,
	  int &cmTop, int &cmBottom, VARIANT_BOOL &ImgView, int &ImgID)
{
	String       ValStr;
	typDocCompo  pDoc;
	//表題部の属性を設定
	if(ARow == 0)
	{
		PosX = spCenter;
		PosY = spMiddle;
		return;
	}

	//セルの情報(先頭行)
	ValStr.sprintf(L"D_%02d_%02d",0,ACol);
	//列ごとに表示位置設定
	if(Document.GetDocCompoFromName(ValStr,pDoc) == true)
	{
		//Y方向は中央
		PosY = spMiddle;
		//X方向はテキスト揃えに従う
		if(pDoc.Alignment == taCenter)
		{
			PosX = spCenterWrap;
		}
		else if(pDoc.Alignment == taRightJustify)
		{
			PosX = spRightWrap;
		}
		else
		{
			PosX = spLeftWrap;
		}
	}
	else
	{
		switch(ACol)
		{
			case 0: //項目
			case 2: //数量
			case 4: //単価
			case 5: //金額
			{
				PosX = spRightWrap;
				PosY = spMiddle;
				break;
			}
			case 1: //商品名
			{
				PosX = spLeftWrap;
				PosY = spMiddle;
				break;
			}
			case 3: //単位
			{
				PosX = spCenterWrap;
				PosY = spMiddle;
				break;
			}
		}
	}
}
//-------------------------------------------------------------
//  機能     ：ラベル内容変更メニュー
//
//  関数定義 ：void __fastcall ModifyLabelClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::ModifyLabelClick(TObject *Sender)
{
	nsResizeCtrl *pResizeCtrl;
	TWinLabel     *pLbl;
	//ポップアップ元を得る
	TComponent *pC = ModifyLabelPopupMenu->PopupComponent;
	//ポップアップ元による処理
	if((pResizeCtrl = dynamic_cast<nsResizeCtrl *>(pC)) != nullptr)
	{
		//現在選択中のコントロールの種類を調べる
		for(int Cnt1 = 0;Cnt1 < ResizeList.size();Cnt1++)
		{
			//コントロールを得る
			TControl *pCtrl = ResizeList[0]->Control;
			//対象ラベル
			pLbl  = static_cast<TWinLabel *>(pCtrl);
		}
	}
	else
	{
		//コントロールを得る
		TControl *pCtrl = static_cast<TControl *>(pC);
		//対象ラベル
		pLbl  = static_cast<TWinLabel *>(pC);
	}

	//ラベル内容変更
	ModifyLabel(pLbl);
}
//-------------------------------------------------------------
//  機能     ：印刷対象メニュー
//
//  関数定義 ：void __fastcall PrintObjectMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::PrintObjectMenuClick(TObject *Sender)
{
	nsResizeCtrl *pResizeCtrl;
	typDocCompo   pDoc;
	bool          doc_valid = false;
	String        name;
	//ポップアップ元を得る
	TComponent *pC = ModifyLabelPopupMenu->PopupComponent;
	//ポップアップ元による処理
	if((pResizeCtrl = dynamic_cast<nsResizeCtrl *>(pC)) != 0)
	{
		//コントロールを得る
		TControl *pCtrl = ResizeList[0]->Control;
		//コントロールの名前
		name = pCtrl->Name;
		//書類部品情報名から書類部品情報を得る
		doc_valid = Document.GetDocCompoFromName(name,pDoc);
	}
	else
	{
		//コントロールを得る
		TControl *pCtrl = static_cast<TControl *>(pC);
		//コントロールの名前
		name = pCtrl->Name;
		//書類部品情報名から書類部品情報を得る
		doc_valid = Document.GetDocCompoFromName(name,pDoc);
	}
	//印刷対象を反転
	if(doc_valid == true)
	{
		pDoc.IsPrint = (pDoc.IsPrint == false);
		//書類部品情報セット
		Document.SetDocCompoFromName(name,pDoc);
	}
	//書類の変更の有無を設定
	SetDocumentChange(true);
}
//-------------------------------------------------------------
//  機能     ：非表示メニュー
//
//  関数定義 ：void __fastcall NonDispObjectMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::NonDispObjectMenuClick(TObject *Sender)
{
	nsResizeCtrl *pResizeCtrl;
	typDocCompo   pDoc;
	bool          doc_valid = false;
	String        name;
	//ポップアップ元を得る
	TComponent *pC = ModifyLabelPopupMenu->PopupComponent;
	//ポップアップ元による処理
	if((pResizeCtrl = dynamic_cast<nsResizeCtrl *>(pC)) != 0)
	{
		//コントロールを得る
		TControl *pCtrl = ResizeList[0]->Control;
		//書類部品情報名
		name = pCtrl->Name;
		//書類部品情報名から書類部品情報を得る
		doc_valid = Document.GetDocCompoFromName(name,pDoc);
	}
	else
	{
		//コントロールを得る
		TControl *pCtrl = static_cast<TControl *>(pC);
		//書類部品情報名
		name = pCtrl->Name;
		//書類部品情報名から書類部品情報を得る
		doc_valid = Document.GetDocCompoFromName(name,pDoc);
	}
	//印刷対象を反転
	if(doc_valid == true)
	{
		pDoc.Visible = false;

		//書類部品情報名から書類部品情報を更新
		Document.SetDocCompoFromName(name,pDoc);
	}
	//書類部品情報からコンポーネントを配置
	SetComponentFromDocCompo(pDoc);
	//書類の変更の有無を設定
	SetDocumentChange(true);
}
//-------------------------------------------------------------
//  機能     ：印刷対象メニュー
//
//  関数定義 ：void __fastcall PrintEditMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::PrintEditMenuClick(TObject *Sender)
{
	typDocCompo   pDoc;
	String        name;
	//ポップアップ元を得る
	TComponent *pC = ModifyEditPopupMenu->PopupComponent;
	//コントロールを得る
	TControl *pCtrl = static_cast<TControl *>(pC);
	//書類部品情報名から書類部品情報を得る
	name = pCtrl->Name;
	//印刷対象を反転
	if(Document.GetDocCompoFromName(name,pDoc) == true)
	{
		pDoc.IsPrint = (pDoc.IsPrint == false);
		//書類部品情報名から書類部品情報を更新
		Document.SetDocCompoFromName(name,pDoc);
	}
	//書類の変更の有無を設定
	SetDocumentChange(true);
}
//-------------------------------------------------------------
//  機能     ：ラベル内容変更
//
//  関数定義 ：void ModifyLabel(TWinLabel *pLbl)
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
void TMainForm::ModifyLabel(TWinLabel *pLbl)
{
	//ラベルの値
	String LblVal = pLbl->Caption;
	//変更ダイアログ表示
	LabelModifyForm->LabelValEdit->Text = LblVal;
	int Res = LabelModifyForm->ShowModal();
	//変更処理
	if(Res == mrOk)
	{
		//ラベルの設定
		pLbl->Caption = LabelModifyForm->LabelValEdit->Text;
		//書類部品情報名から書類部品情報を得る
		typDocCompo  pDoc;
		Document.GetDocCompoFromName(pLbl->Name,pDoc);
		//内容設定
		pDoc.Caption = pLbl->Caption;
		//書類部品情報名から書類部品情報を更新
		Document.SetDocCompoFromName(pLbl->Name,pDoc);
		//MainPanel上の値をデータにセット
		SetDocDataFromMainPanel();
		//書類の変更の有無を設定
		SetDocumentChange(true);
	}
}
//-------------------------------------------------------------
//  機能     ：Editがフォーカスを得た時
//
//  関数定義 ：void __fastcall EditEnter(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::EditEnter(TObject *Sender)
{
	//使用可能なMemoかEditなら色を変える
	TBorderEdit *BorderEdit = dynamic_cast<TBorderEdit *>(Sender);
	//ﾁｪｯｸ
	if(BorderEdit)
	{
		//色変更
		BorderEdit->Color = (TColor)0x0080FFFF;
		//金額の場合
		if(BorderEdit->Name == StdComponents[scMoneyEdit].Name)
		{
			//文字列を得る
			String ValStr = BorderEdit->Text.Trim();
			//空文字列か
			if(ValStr == "")
			{
				BorderEdit->Text = "";
			}
			else
			{
				//先頭が数字以外の場合は除去
				if(ValStr[1] < '0' || ValStr[1] > '9')
				{
					ValStr = ValStr.SubString(2,ValStr.Length());
				}
				//最終文字が数字以外の時は除去
				if(ValStr[ValStr.Length()] < '0' || ValStr[ValStr.Length()] > '9')
				{
					ValStr = ValStr.SubString(1,ValStr.Length()-1);
				}
				//数値入力の場合はｶﾝﾏを取る
				nsDouble Val = ValStr.c_str();
				//数字セット
				BorderEdit->Text = Val.ToStr();
			}
		}
		//全選択
		BorderEdit->SelectAll();
	}
}
//-------------------------------------------------------------
//  機能     ：Editがフォーカスを失うとき
//
//  関数定義 ：void __fastcall EditEnter(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::EditExit(TObject *Sender)
{
	nsDouble nVal;

	//使用可能なEditなら色を変える
	TBorderEdit *BorderEdit = dynamic_cast<TBorderEdit *>(Sender);
	//ﾁｪｯｸ
	if(BorderEdit)
	{
		if(ActiveControl == MainPanel)
		{
			return;
		}
		//色
		BorderEdit->Color = clWindow;
	}
}
//-------------------------------------------------------------
//  機能     ：金額関連入力の抑制
//
//  関数定義 ：void __fastcall MoneyEditKeyPress(TObject *Sender, char &Key)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::MoneyEditKeyPress(TObject *Sender, char &Key)
{
	//Enterは入力不可
	if(Key == '\r')Key = 0;
	//入力可能文字をﾁｪｯｸ
	if(Key < ' ' ||  Key == ',' || Key == '-' || (Key >= '0' && Key <= '9'))
	{
		return;
	}
	//入力できない文字は捨てる
	Key = 0;
}
//-------------------------------------------------------------
//  機能     ：自社情報の設定ボタン
//
//  関数定義 ：void __fastcall CompanyInfoBtnClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::CompanyInfoBtnClick(TObject *Sender)
{
	//移動・大きさ変更を取りやめる
	CancelResizeMode(true);
	//リサイズモードを不許可にする
	SetResizeMode(false);
	//ダイアログ表示
	int Res = CompanyInfoForm->ShowModal();
}
//-------------------------------------------------------------
//  機能     ：印影イメージ解除メニュー
//
//  関数定義 ：void __fastcall CancelStampImageClick(TObject *Sender)
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
void __fastcall TMainForm::CancelStampImageClick(TObject *Sender)
{
	//ポップアップをしたイメージ
	TImageControl *pImage = (TImageControl *)ModifyLabelPopupMenu->PopupComponent;
	//書類部品情報名から書類部品情報を得る
	typDocCompo  pDoc;
	Document.GetDocCompoFromName(pImage->Name,pDoc);
	//対象データを得る
	typDocData& DocData = Document.Data[Document.DocKind];
	//標準コンポーネントかチェック
	typStdComponentDef pStdInf;

	if(typDocKindDefs::GetStdComponentDefFromName(pDoc.Name,pStdInf,Document.DocKind) == true)
	{
		//画像セット
		switch(pStdInf.Number)
		{
			case scStampImage1:
			{
				DocData.StampImage1.reset();
				break;
			}
			case scStampImage2:
			{
				DocData.StampImage2.reset();
				break;
			}
			case scLogoImage:
			{
				DocData.LogoImage.reset();
				break;
			}
			default:
			{
				break;
			}
		}
	}
	//画像を消去
	pImage->Picture = nullptr;
	//画像ファイル名セット
	pDoc.Caption = L"";
	//書類部品情報名から書類部品情報を更新
	Document.SetDocCompoFromName(pImage->Name,pDoc);
	//書類の変更の有無を設定
	SetDocumentChange(true);
}
//-------------------------------------------------------------
//  機能     ：印影クリック時
//
//  関数定義 ：void __fastcall StampImageClick(TObject *Sender)
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
void __fastcall TMainForm::StampImageClick(TObject *Sender)
{
	String         ImageFile;
	TImageControl *pImage;
	//対象イメージ
	pImage = dynamic_cast<TImageControl *>(Sender);
	//ポップアップをしたイメージ
	if(pImage == 0)
	{
		pImage = (TImageControl *)ModifyLabelPopupMenu->PopupComponent;
	}
	//書類部品情報名から書類部品情報を得る
	typDocCompo pDoc;
	if(Document.GetDocCompoFromName(pImage->Name,pDoc) == false)
	{
		return;
	}
	//対象画像ファイル
	ImageFile = pDoc.Caption;
	//初期ファイルセット
	OpenPictureDialog->FileName = ImageFile;
	//ダイアログを開く
	if(OpenPictureDialog->Execute() == false)
	{
		return;
	}
	//画像ファイル名
	ImageFile = OpenPictureDialog->FileName;
	//開いてみる
	nsBitmap pBitmap;
	try
	{
		//読み込む
		pBitmap->LoadFromFile(ImageFile);
	}
	catch(...)
	{
		//エラー表示
		nsLib::ErrMsgBox(Handle,"画像ファイル[%s]はビットマップ形式ではありません。",ImageFile.c_str());

		return;
	}
	//対象データを得る
	typDocData& DocData = Document.Data[Document.DocKind];
	//コンポーネント名から標準コンポーネント情報を得る
	typStdComponentDef pStdInf;

	//標準コンポーネントかチェック
	if(typDocKindDefs::GetStdComponentDefFromName(pDoc.Name,pStdInf,Document.DocKind) == true)
	{
		//画像セット
		switch(pStdInf.Number)
		{
			case scStampImage1:
			{
				DocData.StampImage1->Assign(pBitmap.get());
				break;
			}
			case scStampImage2:
			{
				DocData.StampImage2->Assign(pBitmap.get());
				break;
			}
			case scLogoImage:
			{
				DocData.LogoImage->Assign(pBitmap.get());
				break;
			}
			default:
			{
				break;
			}
		}
	}
	//画像の設定
	pImage->Picture->Bitmap->Assign(pBitmap.get());
	pImage->Invalidate();
	//画像ファイル名セット
	pDoc.Caption = ImageFile;
	//書類部品情報名から書類部品情報を更新
	Document.SetDocCompoFromName(pImage->Name,pDoc);
	//書類の変更の有無を設定
	SetDocumentChange(true);
}
//-------------------------------------------------------------
//  機能     ：文字列関連入力の抑制
//
//  関数定義 ：void __fastcall EditKeyPress(TObject *Sender, wchar_t &Key)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::EditKeyPress(TObject *Sender, wchar_t &Key)
{
	//Enterは入力不可
	if(Key == '\r')
	{
		Key = 0;
	}
}
//-------------------------------------------------------------
//  機能     ：ｷｰ押下時
//
//  関数定義 ：void __fastcall EditKeyDown(TObject *Sender,WORD &Key, TShiftState Shift)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::EditKeyDown(TObject *Sender, WORD &Key,TShiftState Shift)
{
	//Enter入力時、次の入力ｺﾝﾄﾛｰﾙにﾌｫｰｶｽを移行
	if(Key == 13)
	{
		TWinControl *Ctrl;
		TWinControl *NextC;
		//対象ｺﾝﾄﾛｰﾙを得る
		Ctrl  = (TWinControl *)Sender;
		//次のｺﾝﾄﾛｰﾙを得る
		NextC = FindNextControl(Ctrl,true,true,false);
		//次のｺﾝﾄﾛｰﾙにﾌｫｰｶｽｾｯﾄ
		if(NextC != nullptr)
		{
			NextC->SetFocus();
		}
		//Enter無効
		Key = 0;
	}
	//↑入力時、次の入力ｺﾝﾄﾛｰﾙにﾌｫｰｶｽを移行
	else if(Key == VK_UP)
	{
		TWinControl *Ctrl;
		TWinControl *NextC;
		//対象ｺﾝﾄﾛｰﾙを得る
		Ctrl  = (TWinControl *)Sender;
		//次のｺﾝﾄﾛｰﾙを得る
		NextC = FindNextControl(Ctrl,false,true,false);
		//次のｺﾝﾄﾛｰﾙにﾌｫｰｶｽｾｯﾄ
		NextC->SetFocus();
		//Enter無効
		Key = 0;
	}
}
//-------------------------------------------------------------
//  機能     ：開くメニュー
//
//  関数定義 ：void __fastcall SaveBtnClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::OpenMenuClick(TObject *Sender)
{
	String File;
	//移動・大きさ変更を取りやめる
	CancelResizeMode(true);
	//MainPanel上の値をデータにセット
	SetDocDataFromMainPanel();
	//変更がある場合は問い合わせて保存処理を行う
	if(ChangedSave() == nsLib::mbselCancel)
	{
		return;
	}
	//開くダイアログ表示
	if(OpenDialog->Execute() == true)
	{
		//繰り返し入力データの追加
		AddInputData();
		//指定ファイルパス
		File = OpenDialog->FileName;
		//ファイルを開く
		if(OpenFile(File) == false)
		{
			nsLib::ErrMsgBox(Handle,L"請求書番頭ファイル[%s]のオープンに失敗しました。",File.c_str());
			return;
		}
	}
}
//-------------------------------------------------------------
//  機能     ：履歴IDからsdoファイルを開く
//
//  関数定義 ：bool OpenFile(const String& histID)
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
bool TMainForm::OpenFile(const String& histID)
{
	//書類ファイルの読み込み
	if(Sdo.readSDO(histID,Document) == false)
	{
		return false;
	}
	//メインパネルの表示更新
	UpdateMainPanelDisp();

	//現在の履歴をセット
	Histories.get(histID,NowHistory);
	//今開いている書類のIDで履歴一覧の行を選択する
	selectHistViewFromHistID(histID);

	return true;
}
//-------------------------------------------------------------
//  機能     ：名前をつけてメニュー
//
//  関数定義 ：void __fastcall SaveBtnClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::SaveBtnClick(TObject *Sender)
{
	Save();

	return;
}
//-------------------------------------------------------------
//  機能     ：名前をつけて保存
//
//  関数定義 ：bool Save()
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
bool TMainForm::Save()
{
	bool Res;
	//書類情報のZオーダを決定する
	SetDocumentCtrlZOrder();
	//移動・大きさ変更を取りやめる
	CancelResizeMode(true);
	//MainPanel上の値をデータにセット
	SetDocDataFromMainPanel();
	//--- 現在のファイルのパスをデフォルトにする ----
	//ファイルパスを得る
	String FilePath = Document.File.Trim();
	//無題チェック
	if(FilePath != "")
	{
		SaveDialog->InitialDir = ExtractFileDir(FilePath);
		SaveDialog->FileName   = ExtractFileName(FilePath);
	}
	//保存ダイアログ表示
	Res = SaveDialog->Execute();
	//有効か？
	if(Res == false)
	{
		return false;
	}
	//対象ファイル
	String File = SaveDialog->FileName;
	//保存
	Sdo.writeSDO(Document,File);
	//書類の変更の有無を設定
	SetDocumentChange(false);

	return true;
}
//-------------------------------------------------------------
//  機能     ：変更がある場合は問い合わせて保存処理を行う
//
//  関数定義 ：nsLib::mbsel ChangedSave()
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
nsLib::mbsel TMainForm::ChangedSave()
{
	String       FileName;
	nsLib::mbsel Res;
	//変更があるか？
	if(Document.Edited == false)
	{
		//変更なし
		return nsLib::mbselYES;
	}

	//表示ファイル名の設定
	if(Document.File != "")
	{
		FileName = Document.File;
	}
	else
	{
		FileName = L"無題";
	}
	//問合せ
	nsLib::mbsel Sel = nsLib::YesNoCancelMsgBox(Handle,L"[%s]は変更されています、保存しますか？",FileName.c_str());
	//選択別処理
	switch(Sel)
	{
		case nsLib::mbselYES:
		{
			if(OverWrite() == true)
			{
				Res = nsLib::mbselYES;
			}
			else
			{
				Res = nsLib::mbselCancel;
			}
			break;
		}
		case nsLib::mbselCancel:
		{
			Res = nsLib::mbselCancel;
			break;
		}
		case nsLib::mbselNO:
		{
			Res = nsLib::mbselNO;
			break;
		}
	}
	return Res;
}
//-------------------------------------------------------------
//  機能     ：新規作成ボタン
//
//  関数定義 ：void __fastcall NewBtnClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::NewBtnClick(TObject *Sender)
{
	//移動・大きさ変更を取りやめる
	CancelResizeMode(true);
	//リサイズモードを不許可にする
	SetResizeMode(false);

	//変更がある場合は問い合わせて保存処理を行う
	if(ChangedSave() == nsLib::mbselCancel)
	{
		return;
	}
	//繰り返し入力データの追加
	AddInputData();
	//新規作成処理
	NewFile();
}
//-------------------------------------------------------------
//  機能     ：新規作成処理
//
//  関数定義 ：void NewFile()
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
void TMainForm::NewFile()
{
	//テンプレートの有無をチェック
	if(ES.UseTemplateFile == true)
	{
		//--- テンプレートを元に新規作成 ---
		//テンプレートファイルを読む
		if(Sdo.readTemplateSDO(ES.TemplateFile,Document) == false)
		{
			nsLib::ErrMsgBox(Handle,L"テンプレートファイル[%s]のオープンに失敗しました。",ES.TemplateFile.c_str());
			return;
		}
		//ファイルパスは空
		Document.File = L"";
		//メインパネルの表示更新
		UpdateMainPanelDisp();

		//履歴情報初期化
		NowHistory.init_hist();
		//書類の変更の有無を設定
		SetDocumentChange(false);
	}
	else
	{
		//空の書類にする(日付は本日)
		setVoidDocument();
	}
}
//---------------------------------------------------------------------------
//空の書類にする(日付は本日)
//---------------------------------------------------------------------------
bool TMainForm::setVoidDocument()
{
	//書類情報を消す
	Document.ClearDocCompo();
	//データを消す
	Document.ClearData();
	//ファイルパスは空
	Document.File = L"";
	//データを空読み
	Sdo.readVoid(Document);
	//再表示
	UpdateMainPanelDisp();
	//書類の変更の有無を設定
	SetDocumentChange(false);

	return true;
}
//-------------------------------------------------------------
//  機能     ：請求書ボタン
//
//  関数定義 ：void __fastcall BillBtnClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::BillBtnClick(TObject *Sender)
{
	//同じ書類の時は処理しない
	if(Document.DocKind == pmSeikyu)
	{
		return;
	}
	//繰り返し入力データの追加
	AddInputData();
	//書類情報のZオーダを決定する
	SetDocumentCtrlZOrder();
	//移動・大きさ変更を取りやめる
	CancelResizeMode(true);
	//リサイズモードを不許可にする
	SetResizeMode(false);
	//MainPanel上の値をデータにセット
	SetDocDataFromMainPanel();
	//現在の対象書類
	const typDocKindDef& NowDocKind = DocKindDef[Document.DocKind];
	//現在の対象データ構造体
	typDocData& NowDocData = Document.Data[NowDocKind.Number];
	//移動先の対象書類
	const typDocKindDef& NewDocKind = DocKindDef[pmSeikyu];
	//移動先の対象データ構造体
	typDocData& NewDocData = Document.Data[NewDocKind.Number];
	//データコピー
	NewDocData.DataCopy(NowDocData);
	//現在選択の書類
	Document.DocKind = pmSeikyu;
	//メインパネルの表示更新
	UpdateMainPanelDisp();
	//書類種類ボタンの表示を設定
	SetReportKindBtnDisp();
	//スクロールBOXにフォーカスセット
	ScrollBox->SetFocus();
}
//-------------------------------------------------------------
//  機能     ：納品書ボタン
//
//  関数定義 ：void __fastcall DeliveredBtnClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::DeliveredBtnClick(TObject *Sender)
{
	//同じ書類の時は処理しない
	if(Document.DocKind == pmNouhin)
	{
		return;
	}
	//繰り返し入力データの追加
	AddInputData();
	//書類情報のZオーダを決定する
	SetDocumentCtrlZOrder();
	//移動・大きさ変更を取りやめる
	CancelResizeMode(true);
	//リサイズモードを不許可にする
	SetResizeMode(false);
	//MainPanel上の値をデータにセット
	SetDocDataFromMainPanel();
	//現在の対象書類
	const typDocKindDef& NowDocKind = DocKindDef[Document.DocKind];
	//現在の対象データ構造体
	typDocData& NowDocData = Document.Data[NowDocKind.Number];
	//移動先の対象書類
	const typDocKindDef& NewDocKind = DocKindDef[pmNouhin];
	//移動先の対象データ構造体
	typDocData& NewDocData = Document.Data[NewDocKind.Number];
	//データコピー
	NewDocData.DataCopy(NowDocData);
	//現在選択の書類
	Document.DocKind = pmNouhin;
	//メインパネルの表示更新
	UpdateMainPanelDisp();
	//書類種類ボタンの表示を設定
	SetReportKindBtnDisp();
	//スクロールBOXにフォーカスセット
	ScrollBox->SetFocus();
}
//-------------------------------------------------------------
//  機能     ：見積書ボタン
//
//  関数定義 ：void __fastcall EstimateBtnClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::EstimateBtnClick(TObject *Sender)
{
	//同じ書類の時は処理しない
	if(Document.DocKind == pmMitsumori)
	{
		return;
	}
	//繰り返し入力データの追加
	AddInputData();
	//書類情報のZオーダを決定する
	SetDocumentCtrlZOrder();
	//移動・大きさ変更を取りやめる
	CancelResizeMode(true);
	//リサイズモードを不許可にする
	SetResizeMode(false);
	//MainPanel上の値をデータにセット
	SetDocDataFromMainPanel();
	//現在の対象書類
	const typDocKindDef& NowDocKind = DocKindDef[Document.DocKind];
	//現在の対象データ構造体
	typDocData& NowDocData = Document.Data[NowDocKind.Number];
	//移動先の対象書類
	const typDocKindDef& NewDocKind = DocKindDef[pmMitsumori];
	//移動先の対象データ構造体
	typDocData& NewDocData = Document.Data[NewDocKind.Number];
	//データコピー
	NewDocData.DataCopy(NowDocData);
	//現在選択の書類
	Document.DocKind = pmMitsumori;
	//メインパネルの表示更新
	UpdateMainPanelDisp();
	//書類種類ボタンの表示を設定
	SetReportKindBtnDisp();
	//スクロールBOXにフォーカスセット
	ScrollBox->SetFocus();
}
//-------------------------------------------------------------
//  機能     ：終了ボタン
//
//  関数定義 ：void __fastcall EndBtnClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::EndBtnClick(TObject *Sender)
{
	//移動・大きさ変更を取りやめる
	CancelResizeMode(true);
	//リサイズモードを不許可にする
	SetResizeMode(false);
	//閉じる
	Close();
}
//-------------------------------------------------------------
//  機能     ：ｷｰ押下時
//
//  関数定義 ：void __fastcall EditKeyDown(TObject *Sender,WORD &Key, TShiftState Shift)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::GridKeyDown(TObject *Sender, WORD &Key,TShiftState Shift)
{
	//リサイズ表示時は何もしない
	if(ResizeList.size() > 0)
	{
		Key = 0;
		return;
	}
	//キーの状態
	bool IsShift = Shift.Contains(ssShift);
	bool IsCtrl  = Shift.Contains(ssCtrl);
	bool IsAlt   = Shift.Contains(ssAlt);

	//Enter入力時、次の入力セルにﾌｫｰｶｽを移行
	if(IsCtrl == false && Key == 13 && Grid->EditorMode == false)
	{
		int NextRow;
		int NextCol;
		//現在の位置
		int NowRow = Grid->Row;
		int NowCol = Grid->Col;
		//次の位置
		if(NowRow == Grid->RowCount - 1 && NowCol == Grid->ColCount - 1)
		{
			NextRow = NowRow;
			NextCol = NowCol;
		}
		else if(NowCol == Grid->ColCount - 1)
		{
			NextRow = NowRow + 1;
			NextCol = Grid->FixedCols;
		}
		else
		{
			NextRow = NowRow;
			NextCol = NowCol + 1;
		}
		//次の位置
		Grid->Row = NextRow;
		Grid->Col = NextCol;
		//Enter無効
		Key = 0;
	}
	else if((Key == VK_DELETE || Key == VK_BACK) && Grid->EditorMode == false)
	{
		//現在の位置
		int NowRow = Grid->Row;
		int NowCol = Grid->Col;
		//現在の内容
		String NowStr   = "";
		String AfterStr = NowStr;
		//値セット
		Grid->WriteCell(NowRow,NowCol,NowStr);
		//イベント
		GridAfterEdit(Grid,NowRow,NowCol,AfterStr);
		//変更チェック
		if(NowStr != AfterStr)
		{
			Grid->WriteCell(NowRow,NowCol,AfterStr);
		}
		//再表示
		Grid->Invalidate();
	}
	//↑入力時、前にﾌｫｰｶｽを移行
	else if(Key == VK_UP && Grid->EditorMode == false)
	{
		//現在の位置
		int NowRow = Grid->Row;
		int NowCol = Grid->Col;
		//一行目
		if(NowRow == Grid->FixedRows)
		{
			//MainPanelから指定Nameのコントロールを得る
			TControl    *pCtrl = FindControlFromMainPanel(StdComponents[scMoneyEdit].Name);
			//MainPanelから指定Nameのコントロールを得る
			TWinControl *pMoneyEdit = static_cast<TWinControl *>(pCtrl);
			//金額欄にフォーカス
			if(pMoneyEdit)
				pMoneyEdit->SetFocus();
			//キー無効
			Key = 0;
		}
	}
	//↓入力時、小計にﾌｫｰｶｽを移行
	else if(Key == VK_DOWN && Grid->EditorMode == false)
	{
		//現在の位置
		int NowRow = Grid->Row;
		int NowCol = Grid->Col;
		//一行目
		if(NowRow == Grid->RowCount - 1)
		{
			//MainPanelから指定Nameのコントロールを得る
			TControl    *pCtrl = FindControlFromMainPanel(StdComponents[scSubtotalEdit].Name);
			//MainPanelから指定Nameのコントロールを得る
			TWinControl *pSubtotalEdit = static_cast<TWinControl *>(pCtrl);
			//小計欄にフォーカス
			if(pSubtotalEdit)
				pSubtotalEdit->SetFocus();
			//キー無効
			Key = 0;
		}
	}
	//→入力時、前の入力セルにﾌｫｰｶｽを移行
	else if(Key == VK_RIGHT && Grid->EditorMode == false)
	{
		int NextRow;
		int NextCol;
		//現在の位置
		int NowRow = Grid->Row;
		int NowCol = Grid->Col;
		//次の位置
		if(NowRow == Grid->RowCount - 1 && NowCol == Grid->ColCount - 1)
		{
			NextRow = NowRow;
			NextCol = NowCol;
		}
		else if(NowCol == Grid->ColCount - 1)
		{
			NextRow = NowRow + 1;
			NextCol = Grid->FixedCols;
		}
		else
		{
			NextRow = NowRow;
			NextCol = NowCol + 1;
		}
		//次の位置
		Grid->Row = NextRow;
		Grid->Col = NextCol;
		//Enter無効
		Key = 0;
	}
	//←入力時、前の入力セルにﾌｫｰｶｽを移行
	else if(Key == VK_LEFT && Grid->EditorMode == false)
	{
		int NextRow;
		int NextCol;
		//現在の位置
		int NowRow = Grid->Row;
		int NowCol = Grid->Col;
		//次の位置
		if(NowRow == Grid->FixedRows && NowCol == Grid->FixedCols)
		{
			NextRow = NowRow;
			NextCol = NowCol;
		}
		else if(NowCol == Grid->FixedCols)
		{
			NextRow = NowRow - 1;
			NextCol = Grid->ColCount - 1;
		}
		else
		{
			NextRow = NowRow;
			NextCol = NowCol - 1;
		}
		//次の位置
		Grid->Row = NextRow;
		Grid->Col = NextCol;
		//Enter無効
		Key = 0;
	}
	//Ctrl+Shift押下時編集モード移行
	else if(Shift.Contains(ssShift) == true && Shift.Contains(ssCtrl) == true && Grid->EditorMode == false)
	{
		Grid->StartEditorMode(false);
	}
}
//-------------------------------------------------------------
//  機能     ：グリッドフォーカス取得時
//
//  関数定義 ：void __fastcall GridEnter(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::GridEnter(TObject *Sender)
{
	Grid->ActiveCellColor = (TColor)0x0080FFFF;
}
//-------------------------------------------------------------
//  機能     ：グリッドフォーカス喪失時
//
//  関数定義 ：void __fastcall GridExit(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::GridExit(TObject *Sender)
{
	Grid->ActiveCellColor = clWhite;
}
//-------------------------------------------------------------
//  機能     ：グリッドエディット開始時
//
//  関数定義 ：void __fastcall GridStartEdit(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::GridStartEdit(TObject *Sender, int ARow,int ACol, String &EditStr, TImeMode &imode)
{
	TInplaceEditEX *pInplaceEdit = static_cast<TInplaceEditEX *>(Grid->InplaceEditor);

	//--- インプレースエディタのAlignment の設定 -----　
	//現在のスタイル
	LONG Style = ::GetWindowLong(pInplaceEdit->Handle,GWL_STYLE);
	//スタイルを削除
	Style &= (~ES_LEFT);
	Style &= (~ES_RIGHT);
	Style &= (~ES_CENTER);
	//列ごとの処理
	switch(ACol)
	{
		case 0:
		case 1:
		{
			//左寄せ
			Style |= ES_LEFT;
			break;
		}
		case 2:
		case 3:
		case 4:
		{
			//右寄せ
			Style |= ES_RIGHT;
			break;
		}
	}
	//ウィンドウに反映
	::SetWindowLong(pInplaceEdit->Handle,GWL_STYLE,Style);
}
//-------------------------------------------------------------
//  機能     ：セル編集後処理
//
//  関数定義 ：void __fastcall GridAfterEdit(TObject *Sender, int ARow,int ACol, String &DispStr)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::GridAfterEdit(TObject *Sender, int ARow,int ACol, String &DispStr)
{
	//列ごとの処理
	switch(ACol)
	{
		case 0:  //項目
		case 1:  //商品名
		case 3:  //単位
		{
			break;
		}
		case 2:  //数量
		case 4:  //単価
		{
			nsDouble Val;
			nsDouble NumVal;
			nsDouble UnitVal;
			nsDouble MoneyVal;
			String   Str;

			//半角にする
			Str = sbp::StrToHan(DispStr);
			//数値にする
			Val = Str.c_str();
			//セルにセット
			Str = Val.ToStr();
			Grid->Cells[ACol][ARow] = Str;
			//数量、単価文字列
			NumVal  = Grid->GetDispCellStr(ARow,2).c_str();
			UnitVal = Grid->GetDispCellStr(ARow,4).c_str();
			//チェック
			if(NumVal.IsNull() == true || UnitVal.IsNull() == true)
			{
				//金額は無し
				Grid->Cells[5][ARow] = "";
			}
			else
			{
				//金額＝数量×単価
				MoneyVal = NumVal.GetValue() * UnitVal.GetValue();
				//金額セット
				Grid->Cells[5][ARow] = MoneyVal.ToStr();
				//再描画
				Grid->Invalidate();
			}
			//小計、消費税、合計金額の表示
			DispTotalInfo();

			break;
		}
		case 5:  //金額
		{
			nsDouble Val;
			//半角にする
			String Str = sbp::StrToHan(DispStr);
			//数値にする
			Val = Str.c_str();
			//セルにセット
			Grid->Cells[ACol][ARow] = Val.ToStr();
			//小計、消費税、合計金額の表示
			DispTotalInfo();

			break;
		}
	}
}
//-------------------------------------------------------------
//  機能     ：小計、消費税、合計金額の計算
//
//  関数定義 ：void DispTotalInfo()
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
void TMainForm::DispTotalInfo()
{
	nsDouble      SubTotal;
	nsDouble      Tax;
	bool          IsEffect = false;
	TControl     *pCtrl;
	TBorderEdit  *pSubtotalEdit;
	TBorderEdit  *pTaxEdit;
	TBorderEdit  *pTotalEdit;
	TBorderEdit  *pMoneyEdit;
	String        SubTotalStr;
	String        TaxStr;
	nsDouble      SubTotalVal;
	nsDouble      TaxVal;
	nsDouble      MoneyVal;
	String        Str;
	//金額の合計値を得る
	for(int Cnt = Grid->FixedRows;Cnt < Grid->RowCount;Cnt++)
	{
		//金額の合計値を得る
		//セルの文字列
		Str = Grid->GetDispCellStr(Cnt,5);
		//値を得る
		nsDouble Val = Str.c_str();
		//加算
		if(Val.IsNull() == false)
		{
			//加算
			SubTotal = SubTotal.GetValue() + Val.GetValue();
			//データは有効
			IsEffect = true;
		}
	}
	//小計、消費税、合計金額、金額のEditを得る
	pCtrl               = FindControlFromMainPanel(StdComponents[scSubtotalEdit].Name);
	pSubtotalEdit       = static_cast<TBorderEdit *>(pCtrl);
	pCtrl               = FindControlFromMainPanel(StdComponents[scTaxEdit].Name);
	pTaxEdit            = static_cast<TBorderEdit *>(pCtrl);
	pCtrl               = FindControlFromMainPanel(StdComponents[scTotalEdit].Name);
	pTotalEdit          = static_cast<TBorderEdit *>(pCtrl);
	pCtrl               = FindControlFromMainPanel(StdComponents[scMoneyEdit].Name);
	pMoneyEdit          = static_cast<TBorderEdit *>(pCtrl);
	//データが無効の時
	if(IsEffect == false)
	{
		//小計、消費税、合計金額は空欄
		pSubtotalEdit->Text = "";
		pTaxEdit     ->Text = "";
		pTotalEdit   ->Text = "";
		pMoneyEdit   ->Text = "";

		return;
	}
	//該当データを得る
	typDocData& DocData = Document.Data[Document.DocKind];
	//小計のセット
	pSubtotalEdit->Text = SubTotal.ToStrEX(ES.AccuracyR3,ES.RateTyp3,true);

	//消費税、合計金額の計算
	SetTaxAndTotalInfo();
}
//-------------------------------------------------------------
//  機能     ：消費税、合計金額の計算
//
//  関数定義 ：void SetTaxAndTotalInfo()
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
void TMainForm::SetTaxAndTotalInfo()
{
	nsDouble      SubTotal;
	nsDouble      Tax;
	nsDouble      MoneyVal;
	nsDouble      TaxVal;
	TControl     *pCtrl;
	TBorderEdit  *pSubtotalEdit;
	TBorderEdit  *pTaxEdit;
	TBorderEdit  *pTotalEdit;
	TBorderEdit  *pMoneyEdit;

	//小計、消費税、合計金額、金額のEditを得る
	pCtrl               = FindControlFromMainPanel(StdComponents[scSubtotalEdit].Name);
	pSubtotalEdit       = static_cast<TBorderEdit *>(pCtrl);
	pCtrl               = FindControlFromMainPanel(StdComponents[scTaxEdit].Name);
	pTaxEdit            = static_cast<TBorderEdit *>(pCtrl);
	pCtrl               = FindControlFromMainPanel(StdComponents[scTotalEdit].Name);
	pTotalEdit          = static_cast<TBorderEdit *>(pCtrl);
	pCtrl               = FindControlFromMainPanel(StdComponents[scMoneyEdit].Name);
	pMoneyEdit          = static_cast<TBorderEdit *>(pCtrl);
	//該当データを得る
	typDocData& DocData = Document.Data[Document.DocKind];
	//小計の取得
	SubTotal = pSubtotalEdit->Text.c_str();
	//消費税率を得る
	TaxVal = DocData.ConsumptionTaxRatio.c_str();
	//消費税のセット
	if(TaxVal.IsNull() == false)
	{
		if(SubTotal.IsNull() == false)
		{
			Tax            = ((typ_nsdouble)TaxVal * (typ_nsdouble)SubTotal) / 100.0;
			pTaxEdit->Text = Tax.ToStrEX(ES.AccuracyR4,ES.RateTyp4,true);
			Tax            = pTaxEdit->Text.c_str();
		}
		else
		{
			pTaxEdit->Text = "";
			Tax.SetNULL();
		}
	}

	//合計金額の計算
	SetTotalInfo();
}
//-------------------------------------------------------------
//  機能     ：合計金額の計算
//
//  関数定義 ：void SetTotalInfo()
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
void TMainForm::SetTotalInfo()
{
	nsDouble      SubTotal;
	nsDouble      Tax;
	nsDouble      MoneyVal;
	TControl     *pCtrl;
	TBorderEdit  *pSubtotalEdit;
	TBorderEdit  *pTaxEdit;
	TBorderEdit  *pTotalEdit;
	TBorderEdit  *pMoneyEdit;

	//小計、消費税、合計金額、金額のEditを得る
	pCtrl               = FindControlFromMainPanel(StdComponents[scSubtotalEdit].Name);
	pSubtotalEdit       = static_cast<TBorderEdit *>(pCtrl);
	pCtrl               = FindControlFromMainPanel(StdComponents[scTaxEdit].Name);
	pTaxEdit            = static_cast<TBorderEdit *>(pCtrl);
	pCtrl               = FindControlFromMainPanel(StdComponents[scTotalEdit].Name);
	pTotalEdit          = static_cast<TBorderEdit *>(pCtrl);
	pCtrl               = FindControlFromMainPanel(StdComponents[scMoneyEdit].Name);
	pMoneyEdit          = static_cast<TBorderEdit *>(pCtrl);
	//該当データを得る
	typDocData& DocData = Document.Data[Document.DocKind];
	//小計の取得
	SubTotal = pSubtotalEdit->Text.c_str();
	//消費税の取得
	Tax      = pTaxEdit->Text.c_str();
	//合計金額のセット
	if(SubTotal.IsNull() == false || Tax.IsNull() == false)
	{
		MoneyVal         = (typ_nsdouble)SubTotal + (typ_nsdouble)Tax;
		pTotalEdit->Text = MoneyVal.ToStrEX(ES.AccuracyR5,ES.RateTyp5,true);
		pMoneyEdit->Text = MoneyVal.ToStrEX(ES.AccuracyR5,ES.RateTyp5,true);
	}
	else
	{
		pTotalEdit->Text = "";
		pMoneyEdit->Text = "";
	}
}
//-------------------------------------------------------------
//  機能     ：表題の合計金額のセット
//
//  関数定義 ：void SetMainTotalInfo()
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
void TMainForm::SetMainTotalInfo()
{
	TControl     *pCtrl;
	TBorderEdit  *pTotalEdit;
	TBorderEdit  *pMoneyEdit;

	//小計、消費税、合計金額、金額のEditを得る
	pCtrl               = FindControlFromMainPanel(StdComponents[scTotalEdit].Name);
	pTotalEdit          = static_cast<TBorderEdit *>(pCtrl);
	pCtrl               = FindControlFromMainPanel(StdComponents[scMoneyEdit].Name);
	pMoneyEdit          = static_cast<TBorderEdit *>(pCtrl);
	//合計金額のセット
	pMoneyEdit->Text = pTotalEdit->Text;
}
//-------------------------------------------------------------
//  機能     ：セル表示内容の設定
//
//  関数定義 ：void __fastcall GridDispCellStr(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::GridDispCellStr(TObject *Sender, int ARow,int ACol, String &DispStr)
{
	//列ごとの処理
	switch(ACol)
	{
		case 0:  //項目
		case 1:  //商品名
		case 3:  //単位
		{
			break;
		}
		case 2: //数量
		{
			nsDouble nVal;
			//行のチェック
			if(ARow < Grid->FixedRows)break;
			//セルの文字列
			String Str = Grid->Cells[ACol][ARow].Trim();
			//nsDoubleにセット
			nVal = Str.c_str();

			//内容チェック
			if(nVal.IsNull() == true)
			{
				DispStr = "";
			}
			else
			{
				//位取りする
				DispStr = nVal.ToStrEX(ES.AccuracyR1,ES.RateTyp1,true);
			}
			break;
		}
		case 4: //単価
		{
			nsDouble nVal;
			//行のチェック
			if(ARow < Grid->FixedRows)break;
			//セルの文字列
			String Str = Grid->Cells[ACol][ARow].Trim();
			//nsDoubleにセット
			nVal = Str.c_str();

			//内容チェック
			if(nVal.IsNull() == true)
			{
				DispStr = "";
			}
			else
			{
				//位取りする
				DispStr = nVal.ToStrEX(ES.AccuracyR2,ES.RateTyp2,true);
			}
			break;
		}
		case 5: //金額
		{
			nsDouble nVal;
			//行のチェック
			if(ARow < Grid->FixedRows)break;
			//セルの文字列
			String Str = Grid->Cells[ACol][ARow].Trim();
			//nsDoubleにセット
			nVal = Str.c_str();

			//内容チェック
			if(nVal.IsNull() == true)
			{
				DispStr = "";
			}
			else
			{
				//位取りする
				DispStr = nVal.ToStrEX(ES.AccuracyR3,ES.RateTyp3,true);
			}
			break;
		}
	}
}
//-------------------------------------------------------------
//  機能     ：日付関連ダブルクリック
//
//  関数定義 ：void __fastcall YearEditDblClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::YearEditDblClick(TObject *Sender)
{
	//移動・大きさ変更を取りやめる
	CancelResizeMode(true);
	//リサイズモードを不許可にする
	SetResizeMode(false);
	//カレンダー表示
	CalendarForm->ShowModal();
}
//-------------------------------------------------------------
//  機能     ：バージョン情報メニュー
//
//  関数定義 ：void __fastcall VersionInfMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::VersionInfMenuClick(TObject *Sender)
{
	AboutBox->ShowModal();
}
//---------------------------------------------------------------------------
//  機能     ：さくら電算ページにジャンプするメニュー
//
//  関数定義 ：void __fastcall SakuraDensanMenuClick(TObject *Sender)
//
//  アクセスレベル ：__published
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::SakuraDensanMenuClick(TObject *Sender)
{
	ShellExecuteW(Handle,L"open",L"http://www.sakura-densan.com/",L"",L"",SW_SHOW);
}
//---------------------------------------------------------------------------
//  機能     ：請求書番頭 プロ版ページにジャンプするメニュー
//
//  関数定義 ：void __fastcall SupportPageMenuClick(TObject *Sender)
//
//  アクセスレベル ：__published
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::SupportPageMenuClick(TObject *Sender)
{
	::ShellExecuteW(Handle,L"open",L"http://www.sakura-densan.com/seikyusyo_bantou/",L"",L"",SW_SHOW);
}
//-------------------------------------------------------------
//  機能     ：ヘルプメニュー
//
//  関数定義 ：void __fastcall HelpMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::HelpMenuClick(TObject *Sender)
{
	//自分のﾌﾙﾊﾟｽを得る
	String MyPath = ParamStr(0);
	//自分の存在するﾃﾞｨﾚｸﾄﾘ
	String MyDir  = ExtractFileDir(MyPath);
	//フルパスを得る
	String   Path = MyDir + HELPFILE;
	//ﾍﾙﾌﾟﾌｧｲﾙを開く
	if(::ShellExecuteW(Handle,L"open",Path.c_str(),L"",L"",SW_SHOW) < (void *)32)
	{
		nsLib::ErrMsgBox(Handle,L"ヘルプファイル[%s]のオープンに失敗しました。",Path.c_str());
	}
}
//-------------------------------------------------------------
//  機能     ：書類種類ボタンの表示を設定
//
//  関数定義 ：void SetReportKindBtnDisp()
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void TMainForm::SetReportKindBtnDisp()
{
	//ボタンのDown状態でフォントの色を設定する
	if(Document.DocKind == pmSeikyu)
	{
		BillBtn     ->Down        = true;
		DeliveredBtn->Down        = false;
		EstimateBtn ->Down        = false;
		BillBtn     ->Font->Color = clBlue;
		DeliveredBtn->Font->Color = clBlack;
		EstimateBtn ->Font->Color = clBlack;
	}
	if(Document.DocKind == pmNouhin)
	{
		DeliveredBtn->Down        = true;
		BillBtn     ->Down        = false;
		EstimateBtn ->Down        = false;
		BillBtn     ->Font->Color = clBlack;
		DeliveredBtn->Font->Color = clBlue;
		EstimateBtn ->Font->Color = clBlack;
	}
	if(Document.DocKind == pmMitsumori)
	{
		EstimateBtn ->Down        = true;
		DeliveredBtn->Down        = false;
		BillBtn     ->Down        = false;
		BillBtn     ->Font->Color = clBlack;
		DeliveredBtn->Font->Color = clBlack;
		EstimateBtn ->Font->Color = clBlue;
	}
}
//-------------------------------------------------------------
//Formキー押下時
//-------------------------------------------------------------
void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &Key,TShiftState Shift)
{
	//ESCキー押下
	if(Key == VK_ESCAPE)
	{
		if(ResizeEnableBtn->Down == true)
		{
			//ボタン状態設定
			ResizeEnableBtn->Down = false;
		}
	}
}
//-------------------------------------------------------------
//  機能     ：表示メニュー
//
//  関数定義 ：void VisialMenuClick()
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::VisialMenuClick(TObject *Sender)
{
//
}
//-------------------------------------------------------------
//  機能     ：メインパネルクリック時
//
//  関数定義 ：void MainPanelClick()
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::MainPanelClick(TObject *Sender)
{
	//スクロールボックスにフォーカス
	ScrollBox->SetFocus();
	//移動・大きさ変更を取りやめる
	CancelResizeMode(true);
}
//-------------------------------------------------------------
//  機能     ：スクロールボックスクリック時
//
//  関数定義 ：void ScrollBoxClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::ScrollBoxClick(TObject *Sender)
{
	//自分にフォーカスを移動
	ScrollBox->SetFocus();
	//移動・大きさ変更を取りやめる
	CancelResizeMode(true);
}
//-------------------------------------------------------------
//  機能     ：スクロールボックスMouseWheelDown時
//
//  関数定義 ：void __fastcall ScrollBoxMouseWheelDown(TObject *Sender,...)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::ScrollBoxMouseWheelDown(TObject *Sender,TShiftState Shift, TPoint &MousePos, bool &Handled)
{
	//スクロール
	ScrollBox->VertScrollBar->Position = ScrollBox->VertScrollBar->Position + 8;
	MainPanel->Refresh();
}
//-------------------------------------------------------------
//  機能     ：スクロールボックスMouseWheelUp時
//
//  関数定義 ：void __fastcall ScrollBoxMouseWheelUp(TObject *Sender,...)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::ScrollBoxMouseWheelUp(TObject *Sender,TShiftState Shift, TPoint &MousePos, bool &Handled)
{
	//スクロール
	ScrollBox->VertScrollBar->Position = ScrollBox->VertScrollBar->Position - 8;
	MainPanel->Refresh();
}
//-------------------------------------------------------------
//  機能     ：MainPanel MouseDown時　
//
//  関数定義 ：void __fastcall MainPanelMouseDown(TObject *Sender,...)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::MainPanelMouseDown(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft)
	{
		//移動・大きさ変更が可能かチェックする
		bool IsResizeModeEnable = (ResizeList.size() == 0 || Shift.Contains(ssShift) == true);
		//移動・大きさ変更の範囲指定開始
		if(CheckResizeMode() == true)
		{

			if(IsResizeModeEnable == false)
			{
				//移動・大きさ変更を取りやめる
				CancelResizeMode(true);
			}

			OriginX = X;
			OriginY = Y;

			RubberBand1->Left   = OriginX;
			RubberBand1->Top    = OriginY;
			RubberBand1->Width  = 1;
			RubberBand1->Height = 1;

			RubberBand4->Left   = OriginX;
			RubberBand4->Top    = OriginY;
			RubberBand4->Width  = 1;
			RubberBand4->Height = 1;

			RubberBand2->Left   = OriginX;
			RubberBand2->Top    = OriginY;
			RubberBand2->Width  = 1;
			RubberBand2->Height = 1;

			RubberBand3->Left   = OriginX;
			RubberBand3->Top    = OriginY;
			RubberBand3->Width  = 1;
			RubberBand3->Height = 1;

			RubberBand1->Show();
			RubberBand4->Show();
			RubberBand2->Show();
			RubberBand3->Show();

			try
			{
				//Winodw表示中断
				LockWindowUpdate(MainPanel->Handle);
				//ドラッグは開始していない
				IsDragging = false;
				//ドラッグ開始
				MainPanel->BeginDrag(false);
			}
			__finally
			{
				//Winodw表示再開
				LockWindowUpdate(0);
			}
		}
		else if(ResizeList.size() > 0)
		{
			//スクロールボックスにフォーカス
			ScrollBox->SetFocus();
			//移動・大きさ変更を取りやめる
			CancelResizeMode(true);
		}
	}
}
//-------------------------------------------------------------
//  機能     ：MainPanel DragOver時　
//
//  関数定義 ：void __fastcall MainPanelDragOver(TObject *Sender,...)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::MainPanelDragOver(TObject *Sender,TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
	//ドラッグ中か？
	if(IsDragging == false)
	{
		try
		{
			//Winodw表示中断
			LockWindowUpdate(MainPanel->Handle);
			//パネル上のコントロールのEnableをfalseにする
			for(int Cnt = 0;Cnt < MainPanel->ControlCount;Cnt++)
			{
				MainPanel->Controls[Cnt]->Enabled = false;
			}
		}
		__finally
		{
			//ドラッグ中
			IsDragging = true;
			//Winodw表示再開
			LockWindowUpdate(0);
			//MainPanel描画
			MainPanel->Update();
		}
	}

	if (X >= OriginX)
	{
		RubberBand1->Width = X - OriginX;
		RubberBand2->Left  = RubberBand1->Left + RubberBand1->Width;
		RubberBand3->Width = RubberBand1->Width;
	}
	else
	{
		RubberBand1->Left  = X;
		RubberBand1->Width = OriginX - X;
		RubberBand4->Left  = X;
		RubberBand2->Left  = OriginX;
		RubberBand3->Left  = RubberBand1->Left;
		RubberBand3->Width = RubberBand1->Width;
	}

	if (Y >= OriginY)
	{
		RubberBand4->Height = Y - OriginY;
		RubberBand2->Height = RubberBand4->Height;
		RubberBand3->Top    = RubberBand4->Top + RubberBand4->Height;
	}
	else
	{
		RubberBand4->Top    = Y;
		RubberBand4->Height = OriginY - Y;
		RubberBand1->Top    = Y;
		RubberBand2->Top    = RubberBand4->Top;
		RubberBand2->Height = RubberBand4->Height;
		RubberBand3->Top    = OriginY;
	}

	RubberBand1->Update();
	RubberBand2->Update();
	RubberBand3->Update();
	RubberBand4->Update();
}
//-------------------------------------------------------------
//  機能     ：MainPanel EndDrag時　
//
//  関数定義 ：void __fastcall MainPanelDragOver(TObject *Sender,...)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::MainPanelEndDrag(TObject *Sender,TObject *Target, int X, int Y)
{
	//EndDragが有効かチェック
	if(Target == nullptr)
	{
		return;
	}
	//ドラッグ終了
	IsDragging = false;
	//範囲をチェック
	int MinX = (OriginX <= X)?OriginX:X;
	int MaxX = (OriginX >  X)?OriginX:X;
	int MinY = (OriginY <= Y)?OriginY:Y;
	int MaxY = (OriginY >  Y)?OriginY:Y;
	//コントロールのリストを作成
	std::vector<TControl *> CtrlList;

	for(int Cnt = 0;Cnt < MainPanel->ControlCount;Cnt++)
	{
		//リストに追加
		CtrlList.push_back(MainPanel->Controls[Cnt]);
	}
	//範囲内にあるコントロールを残す
	for(int Cnt = CtrlList.size() - 1;Cnt >= 0;Cnt--)
	{
		//コントロールを得る
		TControl *pCtrl = CtrlList[Cnt];
		//コントロールの範囲をチェック
		int CMinX = pCtrl->Left;
		int CMaxX = pCtrl->Left + pCtrl->Width - 1;
		int CMinY = pCtrl->Top;
		int CMaxY = pCtrl->Top + pCtrl->Height - 1;
		//X座標チェック
		bool IsX = ((CMinX >= MinX && CMinX <= MaxX) || (CMaxX >= MinX && CMaxX <= MaxX));
		//Y座標チェック
		bool IsY = ((CMinY >= MinY && CMinY <= MaxY) || (CMaxY >= MinY && CMaxY <= MaxY));
		//X,Y両方範囲内なら選択する
		if(!(IsX == true && IsY == true))
		{
			//移動・大きさ変更のコントロールの対象から削除
			CtrlList.erase(CtrlList.begin() + Cnt);
		}
	}
	//数チェック
	if(CtrlList.size() < 1)
	{
		return;
	}
	//範囲内にあるコントロールを選択する
	try
	{
		//Window表示中断
		LockWindowUpdate(MainPanel->Handle);
		//ラバーバンドを消す
		RubberBand1->Hide();
		RubberBand2->Hide();
		RubberBand3->Hide();
		RubberBand4->Hide();
		//パネル上のコントロールのEnableをtrueにする
		for(int Cnt = 0;Cnt < MainPanel->ControlCount;Cnt++)
		{
			MainPanel->Controls[Cnt]->Enabled = true;
		}
		//SHIFT押下中か
		if(::GetKeyState(VK_SHIFT) == 0)
		{
			//移動・大きさ変更を取りやめる
			CancelResizeMode(false);
		}
		//範囲内にあるコントロールを選択する
		for(int Cnt = 0;Cnt < CtrlList.size();Cnt++)
		{
			//コントロールを得る
			TControl *pCtrl = CtrlList[Cnt];
			//移動・大きさ変更のコントロール追加
			AddResizeControl(pCtrl);
		}
	}
	__finally
	{
		//編集ツールバーの状態設定
		SetEditToolBarCondition();
		//Window表示再開
		LockWindowUpdate(0);
	}
}
//-------------------------------------------------------------
//  機能     ：メインパネルの表示更新
//
//  関数定義 ：void UpdateMainPanelDisp()
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void TMainForm::UpdateMainPanelDisp()
{
	try
	{
		//Window表示中断
		LockWindowUpdate(MainPanel->Handle);
		//現在の用紙の縦、横ピクセル数を得る
		GetPaperPixel();
		//一旦パネルの表示を消す
		MainPanel->Visible = false;
		//メインパネルのサイズ変更
		MainPanel->Width  = PaperWidthPixel;
		MainPanel->Height = PaperHeightPixel;
		//書類部品情報からグリッドを配置
		SetGridFromDocCompo();
		//書類情報からコンポーネントを配置
		SetComponentFromDocumentInfo();
		//書類情報Zオーダーを設定
		SetZOrderFromDocumentInfo();
		//MainPanel上にデータをセット
		SetDataFromDocData();
		//MainPanelを中央に移動する
		SetCenterMainPanel();
		//パネルの表示を再開
		MainPanel->Visible = true;
		//ステータスバーの表示
		DispStatus();

	}
	__finally
	{
		//Window表示再開
		LockWindowUpdate(0);
	}
}
//-------------------------------------------------------------
//  機能     ：書類情報Zオーダーを設定
//
//  関数定義 ：void SetZOrderFromDocumentInfo()
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void TMainForm::SetZOrderFromDocumentInfo()
{
	std::vector<typZOrderDocCompo> ZOrders;
	//現在の用紙・書類種類の書類部品情報を集める
	for(int Cnt = 0;Cnt < Document.GetCompoSize();Cnt++)
	{
		//書類部品情報
		typDocCompo& pDoc = Document.GetCompoFromIndex(Cnt);
		//現在の用紙・書類種類への一致をチェック
		if(pDoc.Paper == Document.Paper && pDoc.DocKind == Document.DocKind)
		{
			//Zオーダーのリストに追加
			typZOrderDocCompo pZ(pDoc);
			ZOrders.push_back(pZ);
		}
	}
	//Zオーダー順にソート
	std::sort(ZOrders.begin(),ZOrders.end());
	//Zオーダ設定
	for(int Cnt = 0;Cnt < ZOrders.size();Cnt++)
	{
		typZOrderDocCompo& pZ = ZOrders[Cnt];
		//書類部品情報
		typDocCompo& pDoc = pZ;
		//名前を得る
		String CtrlName = pDoc.Name;
		//コントロールを得る
		TControl *pCtrl = FindControlFromMainPanel(CtrlName);
		//有効か？
		if(pCtrl != nullptr)
		{
			//前面に移動
			pCtrl->BringToFront();
		}
	}
}
//-------------------------------------------------------------
//標準Editの内容をセット
//-------------------------------------------------------------
bool TMainForm::setStdEdit(scStdComponent comp_typ,const String& val)
{
	TControl    *pCtrl = FindControlFromMainPanel(StdComponents[comp_typ].Name);
	TBorderEdit *pEdit = static_cast<TBorderEdit *>(pCtrl);
	//数値と
	pEdit->Text = val;

	return true;
}
bool TMainForm::setStdEdit(scStdComponent comp_typ,const nsLong& val)
{
	TControl    *pCtrl = FindControlFromMainPanel(StdComponents[comp_typ].Name);
	TBorderEdit *pEdit = static_cast<TBorderEdit *>(pCtrl);
	//数値と
	pEdit->Text = val.ToStr();

	return true;
}
bool TMainForm::setStdEdit(scStdComponent comp_typ,const nsDouble& val)
{
	TControl    *pCtrl = FindControlFromMainPanel(StdComponents[comp_typ].Name);
	TBorderEdit *pEdit = static_cast<TBorderEdit *>(pCtrl);
	//数値と
	pEdit->Text = val.ToStr();

	return true;
}

//-------------------------------------------------------------
//標準Labelの内容をセット
//-------------------------------------------------------------
bool TMainForm::setStdLabel(scStdComponent comp_typ,const String& val)
{
	TControl  *pCtrl  = FindControlFromMainPanel(StdComponents[comp_typ].Name);
	TWinLabel *pLabel = static_cast<TWinLabel *>(pCtrl);
	pLabel->Caption  = val;

	return true;
}
//-------------------------------------------------------------
//標準Imageの内容をセット
//-------------------------------------------------------------
bool TMainForm::setStdImage(scStdComponent comp_typ,const nsBitmap& bmp)
{
	TControl      *pCtrl   = FindControlFromMainPanel(StdComponents[scStampImage1].Name);
	TImageControl *pImage  = static_cast<TImageControl *>(pCtrl);
	pImage->LoadFromBitmap(bmp.get());

	return true;
}
//-------------------------------------------------------------
//  機能     ：MainPanel上にデータをセット
//
//  関数定義 ：void SetDataFromDocData()
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void TMainForm::SetDataFromDocData()
{
	TControl        *pCtrl;
	TBorderEdit     *pEdit;
	TWinLabel       *pLabel;
	TImageControl   *pImage;
	//データをMainPanel上の各部品にセット
	//対象書類
	const typDocKindDef& DocKind = DocKindDef[Document.DocKind];
	//対象データ構造体
	typDocData& DocData = Document.Data[DocKind.Number];

	//---- データセット ----
	//年
	setStdEdit(scYearEdit,DocData.Year);
	//月
	setStdEdit(scMonthEdit,DocData.Month);
	//日
	setStdEdit(scDayEdit,DocData.Day);
	//番号
	setStdEdit(scNoEdit,DocData.No);
	//名前
	setStdEdit(scNameEdit,DocData.Name);
	//件名
	setStdEdit(scItemEdit,DocData.Item);
	//請求金額
	setStdEdit(scMoneyEdit,DocData.Money);
	//小計
	setStdEdit(scSubtotalEdit,DocData.Subtotal);
	//消費税
	setStdEdit(scTaxEdit,DocData.Tax);
	//合計
	setStdEdit(scTotalEdit,DocData.Total);
	//客先郵便番号
	setStdEdit(scCustomerZipCodeEdit,DocData.CustomerZipCode);
	//客先住所１
	setStdEdit(scCustomerAddress1Edit,DocData.CustomerAddress1);
	//客先住所２
	setStdEdit(scCustomerAddress2Edit,DocData.CustomerAddress2);
	//客先電話番号
	setStdEdit(scCustomerTELEdit,DocData.CustomerTEL);
	//客先電話番号
	setStdEdit(scCustomerFAXEdit,DocData.CustomerFAX);

	//グリッド内容のセット
	if(Grid->FixedRows >= 0)
	{

		for(int Row = Grid->FixedRows;Row < Grid->RowCount;Row++)
		{
			//一行分のデータ取得
			if(Row - Grid->FixedRows < DocData.GridData.size())
			{
				//一行分のデータ取得
				typDocOneRowData& RowData = DocData.GridData[Row - Grid->FixedRows];
				//一行分のデータセット
				Grid->Cells[0][Row] = RowData.Item     .c_str();
				Grid->Cells[1][Row] = RowData.Name     .c_str();
				Grid->Cells[2][Row] = RowData.Num      .ToStr();
				Grid->Cells[3][Row] = RowData.Unit     .c_str();
				Grid->Cells[4][Row] = RowData.PriceUnit.ToStr();
				Grid->Cells[5][Row] = RowData.Money    .ToStr();
			}
			else
			{
				//一行分のデータセット
				Grid->Cells[0][Row] = "";
				Grid->Cells[1][Row] = "";
				Grid->Cells[2][Row] = "";
				Grid->Cells[3][Row] = "";
				Grid->Cells[4][Row] = "";
				Grid->Cells[5][Row] = "";
			}
		}
	}
	//---- ラベルセット ----
	//年
	setStdLabel(scYearLabel,DocData.YearLabel);
	//月
	setStdLabel(scMonthLabel,DocData.MonthLabel);
	//日
	setStdLabel(scDayLabel,DocData.DayLabel);
	//書類番号ラベル
	setStdLabel(scNumberLabel,DocData.NumberLabel);
	//件名ラベル
	setStdLabel(scTitleLabel,DocData.TitleLabel);
	//敬称ラベル
	setStdLabel(scHonorificTitleLabel,DocData.HonorificTitleLabel);
	//金額ラベル
	setStdLabel(scChargedAmountLabel,DocData.ChargedAmountLabel);
	//会社名ラベル
	setStdLabel(scCompanyNameLabel,DocData.CompanyNameLabel);
	//代表者ラベル
	setStdLabel(scPersonLabel,DocData.PersonLabel);
	//郵便番号ラベル
	setStdLabel(scZipCodeLabel,DocData.ZipCodeLabel);
	//住所１ラベル
	setStdLabel(scAddressLabel1,DocData.AddressLabel1);
	//住所2ラベル
	setStdLabel(scAddressLabel2,DocData.AddressLabel2);
	//電話番号ラベル
	setStdLabel(scTELLabel,DocData.TELLabel);
	//ＦＡＸ番号ラベル
	setStdLabel(scFAXLabel,DocData.FAXLabel);
	//単位ラベル
	setStdLabel(scUnitLabel,DocData.UnitLabel);
	//小計ラベル
	setStdLabel(scSubTotalLabel,DocData.SubTotalLabel);
	//消費税ラベル
	setStdLabel(scTaxLabel,DocData.TaxLabel);
	//合計金額ラベル
	setStdLabel(scTotalLabel,DocData.TotalLabel);
	//備考ラベル
	setStdLabel(scNoteLabel,DocData.NoteLabel);
	//書類種類名ラベル
	setStdLabel(scBillLabel,DocData.BillLabel);
	//用件ラベル
	setStdLabel(scRequestLabel,DocData.RequestLabel);
	//振込先１ラベル
	setStdLabel(scTransferLabel1,DocData.TransferLabel1);
	//振込先2ラベル
	setStdLabel(scTransferLabel2,DocData.TransferLabel2);

	//---- 画像セット ----
	//印影１
	setStdImage(scStampImage1,DocData.StampImage1);
	//印影２
	setStdImage(scStampImage2,DocData.StampImage2);
	//ロゴ
	setStdImage(scLogoImage,DocData.LogoImage);
}

//-------------------------------------------------------------
//MainFormパネル上のEditコンポーネントからDocDataのメンバの値をセット
//-------------------------------------------------------------
bool TMainForm::setDocValFrom(String& val,scStdComponent comp_typ)
{
	TControl    *pCtrl  = FindControlFromMainPanel(StdComponents[comp_typ].Name);
	TBorderEdit *pEdit  = static_cast<TBorderEdit *>(pCtrl);
	//値をセット
	val = pEdit->Text;

	return true;
}
bool TMainForm::setDocValFrom(nsLong& val,scStdComponent comp_typ)
{
	TControl    *pCtrl  = FindControlFromMainPanel(StdComponents[comp_typ].Name);
	TBorderEdit *pEdit  = static_cast<TBorderEdit *>(pCtrl);
	//値をセット
	val = pEdit->Text.c_str();

	return true;
}
bool TMainForm::setDocValFrom(nsDouble& val,scStdComponent comp_typ)
{
	TControl    *pCtrl  = FindControlFromMainPanel(StdComponents[comp_typ].Name);
	TBorderEdit *pEdit  = static_cast<TBorderEdit *>(pCtrl);
	//値をセット
	val = pEdit->Text.c_str();

	return true;
}
//-------------------------------------------------------------
//MainFormパネル上のLabelコンポーネントからDocDataのメンバの値をセット
//-------------------------------------------------------------
bool TMainForm::setDocValFromLabel(String& val,scStdComponent comp_typ)
{
	TControl * pCtrl  = FindControlFromMainPanel(StdComponents[comp_typ].Name);
	TWinLabel *pLabel = static_cast<TWinLabel *>(pCtrl);
	val = pLabel->Caption;

	return true;
}
//-------------------------------------------------------------
//MainFormパネル上ImageコンポーネントからDocDataのメンバの値をセット
//-------------------------------------------------------------
bool TMainForm::setDocValFromImage(nsBitmap& val,scStdComponent comp_typ)
{
	TControl      *pCtrl  = FindControlFromMainPanel(StdComponents[comp_typ].Name);
	TImageControl *pImage = static_cast<TImageControl *>(pCtrl);
	//値をセット
	val.get()->Assign(pImage->Picture);

	return true;
}
//-------------------------------------------------------------
//  機能     ：MainPanel上の値をデータにセット
//
//  関数定義 ：void SetDocDataFromMainPanel()
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void TMainForm::SetDocDataFromMainPanel()
{
	TControl       *pCtrl;
	TBorderEdit    *pEdit;
	TWinLabel      *pLabel;
	TImageControl  *pImage;
	//データをMainPanel上の各部品にセット
	//対象書類
	const typDocKindDef& DocKind = DocKindDef[Document.DocKind];
	//対象データ構造体
	typDocData& DocData = Document.Data[DocKind.Number];
	//データセット
	//年
	setDocValFrom(DocData.Year,scYearEdit);
	//月
	setDocValFrom(DocData.Month,scMonthEdit);
	//日
	setDocValFrom(DocData.Day,scDayEdit);
	//番号
	setDocValFrom(DocData.No,scNoEdit);
	//名前
	setDocValFrom(DocData.Name,scNameEdit);
	//件名
	setDocValFrom(DocData.Item,scItemEdit);
	//請求金額
	setDocValFrom(DocData.Money,scMoneyEdit);
	//小計
	setDocValFrom(DocData.Subtotal,scSubtotalEdit);
	//消費税
	setDocValFrom(DocData.Tax,scTaxEdit);
	//合計
	setDocValFrom(DocData.Total,scTotalEdit);
	//客先郵便番号
	setDocValFrom(DocData.CustomerZipCode,scCustomerZipCodeEdit);
	//客先住所１
	setDocValFrom(DocData.CustomerAddress1,scCustomerAddress1Edit);
	//客先住所２
	setDocValFrom(DocData.CustomerAddress2,scCustomerAddress2Edit);
	//客先電話番号
	setDocValFrom(DocData.CustomerTEL,scCustomerTELEdit);
	//客先FAX番号
	setDocValFrom(DocData.CustomerFAX,scCustomerFAXEdit);

	//印影１
	setDocValFromImage(DocData.StampImage1,scStampImage1);
	//印影２
	setDocValFromImage(DocData.StampImage2,scStampImage2);
	//ロゴ
	setDocValFromImage(DocData.LogoImage,scLogoImage);

	//グリッド内容の初期化
	DocData.GridData.clear();
	//グリッド内容のセット
	for(int Row = Grid->FixedRows;Row < Grid->RowCount;Row++)
	{
		//一行分のデータ作成
		typDocOneRowData RowData;
		//一行分のデータセット
		RowData.Item       = Grid->Cells[0][Row];
		RowData.Name       = Grid->Cells[1][Row];
		RowData.Num        = Grid->Cells[2][Row].c_str();
		RowData.Unit       = Grid->Cells[3][Row].c_str();
		RowData.PriceUnit  = Grid->Cells[4][Row].c_str();
		RowData.Money      = Grid->Cells[5][Row].c_str();
		//データ追加
		DocData.GridData.push_back(std::move(RowData));
	}
	//---- ラベルセット ----
	//年
	setDocValFromLabel(DocData.YearLabel,scYearLabel);
	//月
	setDocValFromLabel(DocData.MonthLabel,scMonthLabel);
	//日
	setDocValFromLabel(DocData.DayLabel,scDayLabel);
	//書類番号ラベル
	setDocValFromLabel(DocData.NumberLabel,scNumberLabel);
	//件名ラベル
	setDocValFromLabel(DocData.TitleLabel,scTitleLabel);
	//敬称ラベル
	setDocValFromLabel(DocData.HonorificTitleLabel,scHonorificTitleLabel);
	//金額ラベル
	setDocValFromLabel(DocData.ChargedAmountLabel,scChargedAmountLabel);
	//会社名ラベル
	setDocValFromLabel(DocData.CompanyNameLabel,scCompanyNameLabel);
	//代表者ラベル
	setDocValFromLabel(DocData.PersonLabel,scPersonLabel);
	//郵便番号ラベル
	setDocValFromLabel(DocData.ZipCodeLabel,scZipCodeLabel);
	//住所１ラベル
	setDocValFromLabel(DocData.AddressLabel1,scAddressLabel1);
	//住所2ラベル
	setDocValFromLabel(DocData.AddressLabel2,scAddressLabel2);
	//電話番号ラベル
	setDocValFromLabel(DocData.TELLabel,scTELLabel);
	//ＦＡＸ番号ラベル
	setDocValFromLabel(DocData.FAXLabel,scFAXLabel);
	//単位ラベル
	setDocValFromLabel(DocData.UnitLabel,scUnitLabel);
	//小計ラベル
	setDocValFromLabel(DocData.SubTotalLabel,scSubTotalLabel);
	//消費税ラベル
	setDocValFromLabel(DocData.TaxLabel,scTaxLabel);
	//合計金額ラベル
	setDocValFromLabel(DocData.TotalLabel,scTotalLabel);
	//備考ラベル
	setDocValFromLabel(DocData.NoteLabel,scNoteLabel);
	//書類種類名ラベル
	setDocValFromLabel(DocData.BillLabel,scBillLabel);
	//用件ラベル
	setDocValFromLabel(DocData.RequestLabel,scRequestLabel);
	//振込先１ラベル
	setDocValFromLabel(DocData.TransferLabel1,scTransferLabel1);
	//振込先2ラベル
	setDocValFromLabel(DocData.TransferLabel2,scTransferLabel2);
}
//-------------------------------------------------------------
//  機能     ：MainPanelを中央に移動する
//
//  関数定義 ：void SetCenterMainPanel()
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void TMainForm::SetCenterMainPanel()
{
	//スクロール調整用のダミーパネル設定
	DummyPanel->Color = ScrollBox->Color;
	DummyPanel->Width  = 8;
	DummyPanel->Height = 8;
	DummyPanel->Left   = MainPanel->Left;
	DummyPanel->Top    = MainPanel->Top + MainPanel->Height;
	//横スクロールの設定
	if(ScrollBox->Width > MainPanel->Width + 8)
	{
		MainPanel->Left = (ScrollBox->Width - MainPanel->Width)/2;
	}
	else
	{
		MainPanel->Left = 4;
	}
	//立てスクロールの設定
	MainPanel->Top  = 4 - ScrollBox->VertScrollBar->Position;

}
//-------------------------------------------------------------
//  機能     ：スクロールボックスリサイズ時
//
//  関数定義 ：void __fastcall ScrollBoxResize(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::ScrollBoxResize(TObject *Sender)
{
	//MainPanelを中央に移動する
	SetCenterMainPanel();
}
//-------------------------------------------------------------
//  機能     ：部品一覧表を表示
//
//  関数定義 ：void __fastcall DispComponentsMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::DispComponentsMenuClick(TObject *Sender)
{
	//移動・大きさ変更を取りやめる
	CancelResizeMode(true);
	//部品一覧表
	ComponentsForm->ShowModal();
}
//-------------------------------------------------------------
//  機能     ：表の設定メニュー
//
//  関数定義 ：void __fastcall DispComponentsMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::GridSettingMenuClick(TObject *Sender)
{
	//設定画面表示
	if(GridPropertyForm->ShowModal() == mrOk)
	{
		//書類部品情報からグリッドを配置
		SetGridFromDocCompo();
		//書類の変更の有無を設定
		SetDocumentChange(true);
	}
}
//-------------------------------------------------------------
//  機能     ：	ラベルの移動・サイズ変更メニュー
//
//  関数定義 ：void __fastcall MoveLabelMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::ModifyFontMenuClick(TObject *Sender)
{
	typDocCompo   pDoc;
	String        FontName = "ＭＳ Ｐゴシック";
	int           FontSize = 9;
	TControl     *pCtrl;
	typFontDef    FontDef;

	//設定情報
	//リサイズを使用か？
	if(ResizeList.size() > 0)
	{
		//リサイズを対象に処理する
		if(ResizeList.size() == 1)
		{
			//対象コントロール
			pCtrl = ResizeList[0]->Control;

			//書類部品情報を得れた場合デフォルトフォント情報セット
			if(Document.GetDocCompoFromName(pCtrl->Name,pDoc) == true)
			{
				FontDef = pDoc.Font;
			}
		}
		//フォントダイアログのフォント設定
		DocFontInfToTFont(FontDef,FontDialog->Font,false);
		//フォントダイアログ表示
		if(FontDialog->Execute() == false)
		{
			return;
		}
		//現在選択中のコントロールにフォントセット
		for(int Cnt = 0;Cnt < ResizeList.size();Cnt++)
		{
			//コントロールを得る
			pCtrl = ResizeList[Cnt]->Control;
			//名前を得る
			String CtrlName = pCtrl->Name;

			//書類部品情報名から書類部品情報を得られ無い場合は処理をキャンセル
			if(Document.GetDocCompoFromName(CtrlName,pDoc) == false)
			{
				continue;
			}
			//フォントセット
			TFontToDocFontInf(pDoc.Font,FontDialog->Font,false);
			//表示の更新
			if(pDoc.Name == StdComponents[scStdComponent::scGrid].Name)
			{
				//書類部品情報からグリッドを配置
				SetGridFromDocCompo();
			}
			else
			{
				//書類部品情報からコンポーネントを再配置
				SetComponentFromDocCompo(pDoc);
			}
			//書類部品情報名から書類部品情報を更新
			Document.SetDocCompoFromName(CtrlName,pDoc);
		}
	}
	else
	{
		//移動先の対象データ構造体
		//現在の対象書類
		const typDocKindDef& NowDocKind = DocKindDef[Document.DocKind];
		//現在の対象データ構造体
		typDocData& NowDocData = Document.Data[NowDocKind.Number];

		//コントロールを得る
		TControl *pCtrl = static_cast<TControl *>(ModifyLabelPopupMenu->PopupComponent);

		//書類部品情報名から書類部品情報を得る
		if(Document.GetDocCompoFromName(pCtrl->Name,pDoc) == false)
		{
			return;
		}
		//デフォルトフォント情報セット
		FontDef  = pDoc.Font;
		//フォントダイアログのフォント設定
		DocFontInfToTFont(FontDef,FontDialog->Font,false);
		//フォントダイアログ表示
		if(FontDialog->Execute() == false)
		{
			return;
		}
		//フォントセット
		TFontToDocFontInf(pDoc.Font,FontDialog->Font,false);

		//表示の更新
		if(pDoc.Name == StdComponents[scStdComponent::scGrid].Name)
		{
			//書類部品情報からグリッドを配置
			SetGridFromDocCompo();
		}
		else
		{
			//書類部品情報からコンポーネントを再配置
			SetComponentFromDocCompo(pDoc);
		}
	}
	//書類の変更の有無を設定
	SetDocumentChange(true);
}
//-------------------------------------------------------------
//  機能     ：Editのコピーメニュー
//
//  関数定義 ：void __fastcall EditCopyMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::EditCopyMenuClick(TObject *Sender)
{
	TBorderEdit *pEdit;
	XnsGrid     *pGrid;

	//対象コンポーネントを得る
	TComponent *pCompo = ModifyLabelPopupMenu->PopupComponent;
	//Editを得る
	if((pEdit  = dynamic_cast<TBorderEdit *>(pCompo)) != nullptr)
	{
		//コピー
		pEdit->CopyToClipboard();
	}
	else if((pGrid  = dynamic_cast<XnsGrid *>(pCompo)) != nullptr)
	{
		//コピー
		pGrid->CopyOnClipboard(pGrid->Col,pGrid->Col,pGrid->Row,pGrid->Row);
	}
}
//-------------------------------------------------------------
//  機能     ：EditのUndoメニュー
//
//  関数定義 ：void __fastcall EditUndoMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::EditUndoMenuClick(TObject *Sender)
{
	//対象コンポーネントを得る
	TComponent  *pCompo = ModifyLabelPopupMenu->PopupComponent;
	//Editを得る
	TBorderEdit *pEdit  = static_cast<TBorderEdit *>(pCompo);
	//Undo
	pEdit->Undo();
}
//-------------------------------------------------------------
//  機能     ：Editの切り取りメニュー
//
//  関数定義 ：void __fastcall EditUndoMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::EditCutMenuClick(TObject *Sender)
{
	//対象コンポーネントを得る
	TComponent  *pCompo = ModifyLabelPopupMenu->PopupComponent;
	//Editを得る
	TBorderEdit *pEdit  = static_cast<TBorderEdit *>(pCompo);
	//切り取り
	pEdit->CutToClipboard();
}
//-------------------------------------------------------------
//  機能     ：Editの貼り付けメニュー
//
//  関数定義 ：void __fastcall EditPasteMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::EditPasteMenuClick(TObject *Sender)
{
	TBorderEdit *pEdit;
	XnsGrid     *pGrid;

	//対象コンポーネントを得る
	TComponent *pCompo = ModifyLabelPopupMenu->PopupComponent;
	//Editを得る
	if((pEdit  = dynamic_cast<TBorderEdit *>(pCompo)) != nullptr)
	{
		//貼り付け
		pEdit->PasteFromClipboard();
	}
	else if((pGrid  = dynamic_cast<XnsGrid *>(pCompo)) != nullptr)
	{
		//貼り付け
		pGrid->PasteFromClipboard(pGrid->Row,pGrid->Col);
	}
}
//-------------------------------------------------------------
//  機能     ：Editの削除メニュー
//
//  関数定義 ：void __fastcall EditDeleteMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::EditDeleteMenuClick(TObject *Sender)
{
	//対象コンポーネントを得る
	TComponent *pCompo = ModifyLabelPopupMenu->PopupComponent;
	//Editを得る
	TBorderEdit *pEdit  = static_cast<TBorderEdit *>(pCompo);
	//削除
	pEdit->ClearSelection();
}
//-------------------------------------------------------------
//  機能     ：Editの全て選択メニュー
//
//  関数定義 ：void __fastcall EditDeleteMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::EditSelectAllMenuClick(TObject *Sender)
{
	//対象コンポーネントを得る
	TComponent  *pCompo = ModifyLabelPopupMenu->PopupComponent;
	//Editを得る
	TBorderEdit *pEdit  = static_cast<TBorderEdit *>(pCompo);
	//削除
	pEdit->SelectAll();
}
//-------------------------------------------------------------
//  機能     ：	Editポップアップメニュー表示時
//
//  関数定義 ：void __fastcall ModifyEditPopupMenuPopup(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::ModifyEditPopupMenuPopup(TObject *Sender)
{
	//対象コンポーネントを得る
	TComponent  *pCompo = ModifyLabelPopupMenu->PopupComponent;
	//Editを得る
	TBorderEdit *pBorderEdit  = dynamic_cast<TBorderEdit *>(pCompo);
	//部品情報を得る
	typDocCompo pDoc;
	bool doc_valid = Document.GetDocCompoFromName(pBorderEdit->Name,pDoc);

	//種類別処理
	if(pBorderEdit == nullptr)
	{
		//選択文字列があるか？
		bool IsSeltxt = (pBorderEdit->SelLength > 0);
		//メニューの使用可否
		EditUndoMenu     ->Enabled = pBorderEdit->CanUndo;
		EditCutMenu      ->Enabled = IsSeltxt;
		EditCopyMenu     ->Enabled = IsSeltxt;
		EditDeleteMenu   ->Enabled = IsSeltxt;
		EditSelectAllMenu->Enabled = (pBorderEdit->Text != "");
		//カレンダーメニュー
		if(doc_valid == true && pDoc.Type == dcDayEdit)
		{
			CalendarMenu->Visible = true;
		}
		else
		{
			CalendarMenu->Visible = false;
		}
		//印刷対象メニュー
		if(doc_valid == true)
		{
			PrintEditMenu->Visible = true;
			PrintEditMenu->Checked = pDoc.IsPrint;
		}
	}
}
//-------------------------------------------------------------
//  機能     ：	グリッドの列幅変更時
//
//  関数定義 ：void __fastcall GridColWidthsChanged(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::GridColWidthsChanged(TObject *Sender)
{
	String       ValStr;
	int          ColWidthSum = 0;
	typDocCompo *pDoc;
	//各列の幅の合計を得る
	for(int Cnt = 0;Cnt < Grid->ColCount;Cnt++)
	{
		//加算
		ColWidthSum += Grid->ColWidths[Cnt];
	}
	//グリッド本体の幅設定
	Grid->Width = ColWidthSum;
	//指定コントロールの配置を行う
	SetDocControl(Grid);
	//書類の変更の有無を設定
	SetDocumentChange(true);
}
//-------------------------------------------------------------
//  機能     ：グリッドの列幅変更イベントをハンドリングするか設定
//
//  関数定義 ：void SetGridColWidthsChangedEvent(bool IsEnable)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void TMainForm::SetGridColWidthsChangedEvent(bool IsEnable)
{
	if(IsEnable == true)
	{
		Grid->OnColWidthsChanged = GridColWidthsChanged;
	}
	else
	{
		Grid->OnColWidthsChanged = 0;
	}
}
//-------------------------------------------------------------
//  機能     ：リサイズコントロールHide時イベント
//
//  関数定義 ：void __fastcall ResizeHide(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::ResizeHide(TObject *Sender)
{
	String       ValStr;
	String       CtrlName;
	//呼び出しもとのnsResizeCtrl
	nsResizeCtrl *pResizeCtrl = static_cast<nsResizeCtrl *>(Sender);
	//対象となっているコントロール
	TControl *pCtrl = pResizeCtrl->Control;
	//指定コントロールの配置を行う
	SetDocControl(pCtrl);
	//書類の変更の有無を設定
	SetDocumentChange(true);
}
//-------------------------------------------------------------
//  機能     ：指定コントロールの配置を行う
//
//  関数定義 ：bool SetDocControl(TControl *pCtrl)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
bool TMainForm::SetDocControl(TControl *pCtrl)
{
	String       ValStr;
	String       CtrlName;
	typDocCompo  pDoc;
	bool         doc_valid = false;
	//コントロールが有効かチェック
	if(pCtrl == nullptr)
	{
		return false;
	}
	//名前を得る
	CtrlName = pCtrl->Name;
	//名前チェック
	if(CtrlName == L"")
	{
		return false;
	}
	//グリッドの場合
	if(pCtrl == Grid)
	{
		//書類部品情報名から書類部品情報を得る
		doc_valid = Document.GetDocCompoFromName(CtrlName,pDoc);

		//見つからない場合は作成する
		if(doc_valid == false)
		{
			//作成する
			pDoc.Paper    = Document.Paper;
			pDoc.DocKind  = Document.DocKind;
			pDoc.Type     = dcGrid;
			pDoc.Name     = CtrlName;
			pDoc.Visible  = true;
			pDoc.IsPrint  = true;
		}
		//左
		pDoc.X         = GetPaperPosXFromPanelPixel(Grid->Left);
		//上
		pDoc.Y         = GetPaperPosYFromPanelPixel(Grid->Top);
		//行数
		pDoc.RowNum    = Grid->RowCount;
		//列数
		pDoc.ColNum    = Grid->ColCount;
		//幅
		pDoc.Width   = GetPaperPosXFromPanelPixel(Grid->Left + Grid->Width - 1) - pDoc.X;
		//高さ
		pDoc.Height  = GetPaperPosYFromPanelPixel(Grid->Top + Grid->Height - 1) - pDoc.Y;

		//フォント情報
		TFontToDocFontInf(pDoc.Font,Grid->Font,true);

		//書類部品情報名から書類部品情報を更新
		Document.SetDocCompoFromName(CtrlName,pDoc);

		//高さ・幅の合計
		int SumH = Grid->Top;
		int SumW = Grid->Left;

		//データセット
		for(int c = 0;c < Grid->ColCount;c++)
		{
			//セルの書類情報を得る
			ValStr.sprintf(L"D_%02d_%02d",0,c);
			doc_valid    = Document.GetDocCompoFromName(ValStr,pDoc);
			//見つからない場合は作成する
			if(doc_valid == false)
			{
				//作成する
				pDoc.Paper      = Document.Paper;
				pDoc.DocKind    = Document.DocKind;
				pDoc.Type       = dcCell;
				pDoc.Name       = ValStr;
				pDoc.Visible    = true;
				pDoc.IsPrint    = true;
				pDoc.Caption    = Grid->Cells[c][0];
				TFontToDocFontInf(pDoc.Font,Grid->Font,true);
				pDoc.FigureLine = false;
				pDoc.Figures    = DEFAULT_FIGURES;
				pDoc.Caption    = StdColumn[c].Name;
				pDoc.Alignment  = StdColumn[c].Alignment;
			}
			//セルのデータを得る
			pDoc.X      = GetPaperPosXFromPanelPixel(SumW);
			pDoc.Y      = GetPaperPosXFromPanelPixel(SumH);

			if(c == Grid->ColCount - 1)
			{
				//列幅
				int ColW = Grid->ColWidths[c];
				//最終列
				pDoc.Width  = GetPaperPosXFromPanelPixel(SumW + ColW-1) - pDoc.X;
			}
			else
			{
				//列幅
				int ColW = Grid->ColWidths[c];
				//通常列
				pDoc.Width  = GetPaperPosXFromPanelPixel(SumW + ColW) - pDoc.X;
			}

			long double Bottom = GetPaperPosYFromPanelPixel(SumH + Grid->RowHeights[0]);

			pDoc.Height = Bottom - pDoc.Y;

			//幅の合計の更新
			SumW        += Grid->ColWidths[c];

			//書類部品情報名から書類部品情報を更新
			Document.SetDocCompoFromName(ValStr,pDoc);

		}
		//書類部品情報からグリッドを配置
		SetGridFromDocCompo();
	}
	//通常コントロールの場合
	else
	{
		//対象情報
		doc_valid = Document.GetDocCompoFromName(CtrlName,pDoc);
		//見つからない場合は作成する
		if(doc_valid == false)
		{
			TWinLabel     *pAALbl;
			TBorderEdit  *pBorderEdit;
			//作成する
			pDoc.Paper    = Document.Paper;
			pDoc.DocKind  = Document.DocKind;
			pDoc.Name     = CtrlName;
			pDoc.Visible  = true;
			pDoc.IsPrint  = true;
			//キャプションセット
			if((pAALbl = dynamic_cast<TWinLabel *>(pCtrl)) != 0)
			{
				pDoc.Caption  = pAALbl->Caption;
				TFontToDocFontInf(pDoc.Font,pAALbl->Font,true);
			}
			else if((pBorderEdit = dynamic_cast<TBorderEdit *>(pCtrl)) != 0)
			{
				pDoc.Caption  = L"";
				TFontToDocFontInf(pDoc.Font,pBorderEdit->Font,true);
			}
		}
		//左
		pDoc.X      = GetPaperPosXFromPanelPixel(pCtrl->Left);
		//上
		pDoc.Y      = GetPaperPosYFromPanelPixel(pCtrl->Top);
		//幅
		pDoc.Width  = GetPaperPosXFromPanelPixel(pCtrl->Left + pCtrl->Width - 1) - pDoc.X;
		//高さ
		pDoc.Height = GetPaperPosYFromPanelPixel(pCtrl->Top + pCtrl->Height - 1) - pDoc.Y;

		//書類部品情報名から書類部品情報を更新
		Document.SetDocCompoFromName(CtrlName,pDoc);

		//書類部品情報からコンポーネントを配置
		SetComponentFromDocCompo(pDoc);
	}
	return true;
}
//-------------------------------------------------------------
//  機能     ：上書き保存メニュー
//
//  関数定義 ：void __fastcall OverWriteMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::OverWriteMenuClick(TObject *Sender)
{
	//上書き保存
	OverWrite();
	//書類の履歴一覧読み込み処理
	LoadReportHist();

	return;
}
//-------------------------------------------------------------
//  機能     ：上書き保存メニュー
//
//  関数定義 ：bool OverWrite()
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
bool TMainForm::OverWrite()
{
	bool Res;
	//ファイルパスを得る
	String FilePath = Document.File.Trim();
	//無題チェック
	if(FilePath == L"")
	{
		//名前をつけて保存
		Res = Save();
		return Res;
	}
	//書類情報のZオーダを決定する
	SetDocumentCtrlZOrder();
	//移動・大きさ変更を取りやめる
	CancelResizeMode(true);
	//リサイズモードを不許可にする
	SetResizeMode(false);
	//MainPanel上の値をデータにセット
	SetDocDataFromMainPanel();
	//存在しないなら名前をつけて保存
	if(FilePath == L"")
	{
		//名前をつけて保存
		Res = Save();
		return Res;
	}
	//上書きする
	Sdo.writeSDO(Document,FilePath);
	//書類の変更の有無を設定
	SetDocumentChange(false);
	//今開いている書類のIDで履歴一覧の行を選択する
	selectHistViewFromHistID(Document.HistID);

	return true;
}
//-------------------------------------------------------------
//  機能     ：アプリケーションイベントのハンドリング
//
//  関数定義 ：void __fastcall ApplicationEventsMessage(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::ApplicationEventsMessage(tagMSG &Msg,bool &Handled)
{

	if(Msg.message == WM_KEYDOWN)
	{
		TShiftState    Shift;
		WORD           Key = Msg.wParam;
		bool           IsResizeCtrlVisible = (ResizeList.size() > 0);
		bool           IsUserMove = true;

		//ハンドルの必要があるか
		if(IsResizeCtrlVisible == false)
		{
			return;
		}
		//キーはこちらで処理する事にする
		Handled = true;
		//Shift状態
		bool IsShift = ((GetKeyState(VK_SHIFT) & 0x80) != 0);

		//キーによる操作
		if(IsShift == false)
		{
			switch(Key)
			{
				case VK_RIGHT:
				{
					ResizeCtrlMove(this,IsUserMove,1,0,0,0);
					Key = 0;
					break;
				}
				case VK_LEFT:
				{
					ResizeCtrlMove(this,IsUserMove,-1,0,0,0);
					Key = 0;
					break;
				}
				case VK_DOWN:
				{
					ResizeCtrlMove(this,IsUserMove,0,1,0,0);
					Key = 0;
					break;
				}
				case VK_UP:
				{
					ResizeCtrlMove(this,IsUserMove,0,-1,0,0);
					Key = 0;
					break;
				}
				case VK_ESCAPE:
				{
					//編集対象のコントロール
					if(ResizeList.size() > 0)
					{
						//移動・大きさ変更を取りやめる
						CancelResizeMode(true);
						Key = 0;
						break;
					}
				}
			}
		}
		else
		{
			//Shiftキー押下時
			switch(Key)
			{
				case VK_RIGHT:
				{
					ResizeCtrlMove(this,IsUserMove,0,0,1,0);
					Key = 0;
					break;
				}
				case VK_LEFT:
				{
					ResizeCtrlMove(this,IsUserMove,0,0,-1,0);
					Key = 0;
					break;
				}
				case VK_DOWN:
				{
					ResizeCtrlMove(this,IsUserMove,0,0,0,1);
					Key = 0;
					break;
				}
				case VK_UP:
				{
					ResizeCtrlMove(this,IsUserMove,0,0,0,-1);
					Key = 0;
					break;
				}
			}
		}
	}
}
//-------------------------------------------------------------
//  機能     ：ズームセットメニュー(10%～)
//
//  関数定義 ：void __fastcall ZoomSetMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::ZoomSetMenuClick(TObject *Sender)
{
	//移動・大きさ変更を取りやめる
	CancelResizeMode(true);
	//リサイズモードを不許可にする
	SetResizeMode(false);
	//MainPanel上の値をデータにセット
	SetDocDataFromMainPanel();
	//対象メニュー
	TMenuItem *pMenu = static_cast<TMenuItem *>(Sender);
	//名前を得る
	String MenuName = pMenu->Name;
	//アンダーバー以前の文字列
	int    UBPos   = MenuName.Pos(L"_");
	String ZoomStr = MenuName.SubString(1,UBPos-1);
	//ズーム名からズーム情報を得る
	typZoomDef pZoomDef;
	TZooms::GetZoomDefFromName(ZoomStr,pZoomDef);
	//現在選択のズーム
	Document.Zoom = pZoomDef.Number;
	//メインパネルの表示更新
	UpdateMainPanelDisp();
	//スクロールBOXにフォーカスセット
	ScrollBox->SetFocus();
}
//-------------------------------------------------------------
//  機能     ：ズーム親メニュー
//
//  関数定義 ：void __fastcall ZoomMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::ZoomMenuClick(TObject *Sender)
{
	//現在のズームを得る
	const typZoomDef& NowZoom = ZoomDef[Document.Zoom];
	//対象となるメニュー名を作成
	String MenuName = String(NowZoom.ZoomName) + "_Menu";
	//子のメニューのチェックの有無を設定
	for(int Cnt = 0;Cnt < TZooms::size();Cnt++)
	{
		typZoomDef zoom;
		//コンポーネント名を作成
		TZooms::get(Cnt,zoom);
		String comp_nm = String(zoom.ZoomName) + "_Menu";
		//対応TActionを得る
		TComponent *pComp = FindComponent(comp_nm);
		if(pComp == nullptr)
		{
			continue;
		}
		TAction *pAction = dynamic_cast<TAction *>(pComp);
		if(pAction == nullptr)
		{
			continue;
		}
		//名前の一致をチェック
		if(pAction->Name == MenuName)
		{
			//チェック表示
			pAction->Checked = true;
		}
		else
		{
			//チェック表示しない
			pAction->Checked = false;
		}
	}
}
//-------------------------------------------------------------
//  機能     ：用紙選択メニュー
//
//  関数定義 ：void __fastcall PaperSelectMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::PaperSelectMenuClick(TObject *Sender)
{
	//移動・大きさ変更を取りやめる
	CancelResizeMode(true);
	//リサイズモードを不許可にする
	SetResizeMode(false);
	//MainPanel上の値をデータにセット
	SetDocDataFromMainPanel();
	//対象メニュー
	TMenuItem *pMenu = static_cast<TMenuItem *>(Sender);
	//名前を得る
	String menuName = pMenu->Name;

	//メインフォームクリックされたメニューの名前から用紙種類を得る
	typPaperDef paperInfo;
	TPaperDefs::getPaperFromMenyName(menuName,paperInfo);
	//現在選択の用紙
	Document.Paper = paperInfo.Number;
	//メインパネルの表示更新
	UpdateMainPanelDisp();
	//スクロールBOXにフォーカスセット
	ScrollBox->SetFocus();
}
//-------------------------------------------------------------
//  機能     ：用紙選択親メニュー
//
//  関数定義 ：void __fastcall PaperSelectParentMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::PaperSelectParentMenuClick(TObject *Sender)
{
	//アクションにキャスト
	TAction *PaperMenu = static_cast<TAction *>(Sender);

	//オブジェクト名が用紙選択のものかチェック
	if(PaperMenu->Name != L"PaperSelectParentMenu")
	{
		return;
	}

	//現在の用紙を得る
	const typPaperDef& NowPaper = PaperDef[Document.Paper];
	//対象となるメニュー名を作成
	String MenuName = String(NowPaper.PaperName) + L"_Menu";

	//用紙選択のメニューから現在の用紙のメニューにチェックをつける
	for(int paper_cnt = 0;paper_cnt < TPaperDefs::size();paper_cnt++)
	{
		typPaperDef paper;
		//用紙情報を得る
		TPaperDefs::get(paper_cnt,paper);
		//メニューのオブジェクト名
		String menu_name = String(paper.PaperName) + L"_Menu";
		//用紙に対応するTActionを得る
		TComponent *pComp = FindComponent(menu_name);
		if(pComp == nullptr)
		{
			continue;
		}
		TAction *action = dynamic_cast<TAction *>(pComp);
		//名前の一致をチェック
		if(action->Name == MenuName)
		{
			//チェック表示
			action->Checked = true;
		}
		else
		{
			//チェック表示しない
			action->Checked = false;
		}
	}
}
//-------------------------------------------------------------
//  機能     ：オブジェクトMouseDown時
//
//  関数定義 ：void __fastcall ObjectMouseDown(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::ObjectMouseDown(TObject *Sender,TMouseButton Button, TShiftState Shift, int X, int Y)
{
	//ボタンの種類
	if(Button == mbLeft)
	{
		//リサイズモード別処理
		if(CheckResizeMode() == false)
		{
			//移動・大きさ変更を取りやめる
			CancelResizeMode(true);
		}
		else
		{
			//対象コントロール
			TControl *pCtrl = static_cast<TControl *>(Sender);
			//SHIFTが押下されているか？
			if(Shift.Contains(ssShift) == true)
			{
				//リサイズ対象を追加
				AddResizeControl(pCtrl);
			}
			else
			{
				//リサイズ対象を追加
				try
				{
					//Window表示中断
					LockWindowUpdate(MainPanel->Handle);
					//移動・大きさ変更を取りやめる
					CancelResizeMode(false);
					//リサイズ対象を追加
					AddResizeControl(pCtrl);
					//編集ツールバーの状態設定
					SetEditToolBarCondition();
				}
				__finally
				{
					//Window表示再開
					LockWindowUpdate(0);
				}
			}
		}
	}
	if(Button == mbRight)
	{
		nsResizeCtrl *pResizeCtrl;
		//対象コントロール
		TControl    *pCtrl = static_cast<TControl *>(Sender);
		//エディットか？
		TBorderEdit *pEdit = dynamic_cast<TBorderEdit *>(pCtrl);
		//スクリーン座標
		TPoint Pos = pCtrl->ClientToScreen(TPoint(X,Y));

		//現在リサイズ対象のコントロールがあるか
		if(CheckResizeMode() == true && ResizeList.size() == 0)
		{
//			//リサイズ対象を追加
//			pResizeCtrl = AddResizeControl(pCtrl);
//			//対象コントロール
//			ModifyLabelPopupMenu->PopupComponent = pResizeCtrl;
//			//ポップアップ表示
//			ModifyLabelPopupMenu->Popup(Pos.x,Pos.y);
		}
		else if(CheckResizeMode() == false && pEdit != 0)
		{
			//フォーカスセット
			pEdit->SetFocus();
			//対象コントロール
			ModifyLabelPopupMenu->PopupComponent = pCtrl;
			//ポップアップ表示
			ModifyLabelPopupMenu->Popup(Pos.x,Pos.y);
		}
		else
		{
			//グリッドの場合はそのセルを選択
			if(pCtrl == Grid)
			{
				//セルの位置を得る
				Grid->MouseToCell(X,Y,SelACol,SelARow);
				//選択する
				if(SelARow >= Grid->FixedRows)
				{
					Grid->Row = SelARow;
					Grid->Col = SelACol;
					Grid->Invalidate();
				}
			}
			//対象コントロール
			ModifyLabelPopupMenu->PopupComponent = pCtrl;
			//ポップアップ表示
			ModifyLabelPopupMenu->Popup(Pos.x,Pos.y);
		}
	}
}
//-------------------------------------------------------------
//  機能     ：オブジェクトダブルクリック時
//
//  関数定義 ：void __fastcall ObjectDblClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::ObjectDblClick(TObject *Sender)
{
	//対象コントロール
	TControl    *pCtrl = static_cast<TControl *>(Sender);
	//対象部品情報を得る
	typDocCompo pDoc;
	Document.GetDocCompoFromName(pCtrl->Name,pDoc);
	//ラベルか？
	TWinLabel *pLabel = dynamic_cast<TWinLabel *>(pCtrl);
	//ラベルの処理
	if(pLabel != nullptr)
	{
		//ラベル内容変更
		ModifyLabel(pLabel);
	}
	//カレンダー表示
	else if(pDoc.Type == dcDayEdit)
	{
		YearEditDblClick(Sender);
	}
	//画像設定
	else if(pDoc.Type == dcImage)
	{
		StampImageClick(Sender);
	}
}
//-------------------------------------------------------------
//  機能     ：ラベルポップアップメニュー表示時
//
//  関数定義 ：void __fastcall ModifyLabelPopupMenuPopup(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::ModifyLabelPopupMenuPopup(TObject *Sender)
{
	nsResizeCtrl *pResizeCtrl;
	TControl     *pCtrl;
	typDocCompo   pDoc;
	bool          isDocValid = false;
	bool          IsLabel  = false;
	bool          IsEdit   = false;
	bool          IsShape  = false;
	bool          IsImage  = false;
	bool          IsGrid   = false;

	//ポップアップ元を得る
	TComponent *pC = ModifyLabelPopupMenu->PopupComponent;
	//ポップアップ元による処理
	if((pResizeCtrl = dynamic_cast<nsResizeCtrl *>(pC)) != 0)
	{
		//現在選択中のコントロールの種類を調べる
		for(int Cnt = 0;Cnt < ResizeList.size();Cnt++)
		{
			//コントロールを得る
			pCtrl = ResizeList[Cnt]->Control;
			//種類判定
			if(dynamic_cast<TWinLabel *>(pCtrl) != 0)
			{
				IsLabel = true;
			}
			else if(dynamic_cast<TBorderEdit *>(pCtrl) != 0)
			{
				IsEdit = true;
			}
			else if(dynamic_cast<TWinShape *>(pCtrl) != 0)
			{
				IsShape = true;
			}
			else if(dynamic_cast<TImageControl *>(pCtrl) != 0)
			{
				IsImage = true;
			}
			else if(pCtrl == Grid)
			{
				IsGrid = true;
			}
		}
		//各メニューの表示設定
		ModifyValueMenu             ->Visible = (ResizeList.size() == 1 && IsLabel == true);
		LabelAnotherSamePositionMenu->Visible = true;
		ModifyFontMenu              ->Visible = ((IsLabel == true || IsEdit == true || IsGrid == true) && IsShape == false && IsImage == false);
		GridSettingMenu             ->Visible = (ResizeList.size() == 1 && IsGrid == true);
		SetStampImage               ->Visible = (ResizeList.size() == 1 && (pCtrl->Name == StdComponents[scStampImage1].Name || pCtrl->Name == StdComponents[scStampImage2].Name || pCtrl->Name == StdComponents[scLogoImage].Name));
		CancelStampImage            ->Visible = SetStampImage->Visible;
		BringToFrontMenu            ->Visible = (ResizeList.size() == 1);
		SendToBackMenu              ->Visible = (ResizeList.size() == 1);
		ColSeparateLineMenu         ->Visible = false;
		FigureMenu                  ->Visible = false;
		BorderMenu                  ->Visible = false;
		LeftJustifyMenu             ->Visible = false;
		CenterMenu                  ->Visible = false;
		RightJustifyMenu            ->Visible = false;
		//関連データを得る
		if(ResizeList.size() == 1)
		{
			isDocValid = Document.GetDocCompoFromName(pCtrl->Name,pDoc);
		}
		//左右、中央揃えの設定
		if(ResizeList.size() == 1 && (IsEdit == true || IsLabel == true))
		{
			//枠線設定メニュー
			LeftJustifyMenu  ->Visible = true;
			CenterMenu       ->Visible = true;
			RightJustifyMenu ->Visible = true;
			LeftJustifyMenu  ->Checked = (pDoc.Alignment == taLeftJustify);
			CenterMenu       ->Checked = (pDoc.Alignment == taCenter);
			RightJustifyMenu ->Checked = (pDoc.Alignment == taRightJustify);
		}
		//枠線の使用
		if(ResizeList.size() == 1 && (IsEdit == true || IsLabel == true || IsImage == true))
		{
			//枠線設定メニュー
			BorderMenu->Visible = true;
			BorderMenu->Checked = pDoc.Border;
		}
		//桁区切り関連設定
		if(IsEdit == true && ResizeList.size() == 1)
		{
			if(pDoc.Type == dcMoneyEdit)
			{
				ColSeparateLineMenu->Visible = true;
				ColSeparateLineMenu->Checked = pDoc.FigureLine;
				FigureMenu         ->Visible = pDoc.FigureLine;
			}
		}
		//印刷対象
		if(isDocValid == true)
		{
			PrintObjectMenu->Visible = true;
			PrintObjectMenu->Checked = pDoc.IsPrint;
		}

		//表示設定
		if(isDocValid == true && IsGrid == false)
		{
			NonDispObjectMenu->Visible = true;
		}

		//ポップアップ元の設定
		if(ResizeList.size() < 2)
		{
			ModifyLabelPopupMenu->PopupComponent = pResizeCtrl->Control;
		}
	}
	else
	{
		//コントロールを得る
		TControl *pCtrl = static_cast<TControl *>(pC);
		//種類判定
		if(dynamic_cast<TWinLabel *>(pCtrl) != 0)
		{
			IsLabel = true;
		}
		else if(dynamic_cast<TBorderEdit *>(pCtrl) != 0)
		{
			IsEdit = true;
		}
		else if(dynamic_cast<TWinShape *>(pCtrl) != 0)
		{
			IsShape = true;
		}
		else if(dynamic_cast<TImageControl *>(pCtrl) != 0)
		{
			IsImage = true;
		}
		else if(pCtrl == Grid)
		{
			IsGrid = true;
		}
		//全てのメニューを非表示にする
		for(int Cnt = 0;Cnt < ModifyLabelPopupMenu->Items->Count;Cnt++)
		{
			ModifyLabelPopupMenu->Items->Items[Cnt]->Visible = false;
		}
		//関連データを得る

		//印刷対象メニュー
		if(Document.GetDocCompoFromName(pCtrl->Name,pDoc) == true)
		{
			PrintObjectMenu->Visible = true;
			PrintObjectMenu->Checked = pDoc.IsPrint;
		}

		//表示設定
		if(isDocValid == true && IsGrid == false)
		{
			NonDispObjectMenu->Visible = true;
		}
		//タイプ別処理
		if(IsLabel == true)
		{
			ModifyValueMenu ->Visible = (ResizeList.size() == 0);
			LeftJustifyMenu ->Visible = (ResizeList.size() == 0);
			CenterMenu      ->Visible = (ResizeList.size() == 0);
			RightJustifyMenu->Visible = (ResizeList.size() == 0);
			BorderMenu      ->Visible = (ResizeList.size() == 0);
			ModifyFontMenu  ->Visible = (ResizeList.size() == 0);

			LeftJustifyMenu ->Checked = (pDoc.Alignment == taLeftJustify);
			CenterMenu      ->Checked = (pDoc.Alignment == taCenter);
			RightJustifyMenu->Checked = (pDoc.Alignment == taRightJustify);
			BorderMenu      ->Checked = (pDoc.Border == true);
		}
		else if(IsImage == true)
		{
			SetStampImage               ->Visible = true;
			CancelStampImage            ->Visible = true;
			BorderMenu       ->Visible = (ResizeList.size() == 0);

			BorderMenu       ->Checked = (pDoc.Border == true);
		}
		else if(IsEdit == true)
		{
			LeftJustifyMenu  ->Visible = (ResizeList.size() == 0);
			CenterMenu       ->Visible = (ResizeList.size() == 0);
			RightJustifyMenu ->Visible = (ResizeList.size() == 0);

			LeftJustifyMenu  ->Checked = (pDoc.Alignment == taLeftJustify);
			CenterMenu       ->Checked = (pDoc.Alignment == taCenter);
			RightJustifyMenu ->Checked = (pDoc.Alignment == taRightJustify);

			EditUndoMenu     ->Visible = (ResizeList.size() == 0);
			EditCutMenu      ->Visible = (ResizeList.size() == 0);
			EditCopyMenu     ->Visible = (ResizeList.size() == 0);
			EditPasteMenu    ->Visible = (ResizeList.size() == 0);
			EditDeleteMenu   ->Visible = (ResizeList.size() == 0);
			EditSelectAllMenu->Visible = (ResizeList.size() == 0);
			BorderMenu       ->Visible = (ResizeList.size() == 0);

			BorderMenu       ->Checked = (pDoc.Border == true);
			ModifyFontMenu   ->Visible = (ResizeList.size() == 0);
			ZipToAddressMenu ->Visible = (ResizeList.size() == 0 && (pCtrl->Name == StdComponents[scCustomerZipCodeEdit].Name));

			if(pDoc.Type == dcMoneyEdit)
			{
				ColSeparateLineMenu->Visible = (ResizeList.size() == 0);

				ColSeparateLineMenu->Checked = pDoc.FigureLine;
				FigureMenu         ->Visible = (ResizeList.size() == 0 && pDoc.FigureLine == true);
			}
		}
		else if(IsGrid == true)
		{
			GridSettingMenu->Visible = (ResizeList.size() == 0);
			ModifyFontMenu ->Visible = (ResizeList.size() == 0);
			EditCopyMenu   ->Visible = (ResizeList.size() == 0 && SelARow >= Grid->FixedRows);
			EditPasteMenu  ->Visible = (ResizeList.size() == 0 && SelARow >= Grid->FixedRows);
		}
	}
}
//-------------------------------------------------------------
//  機能     ：他の書類でも同じ位置(ラベルメニュー)
//
//  関数定義 ：void __fastcall LabelAnotherSamePositionMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::LabelAnotherSamePositionMenuClick(
	  TObject *Sender)
{
	nsResizeCtrl *pResizeCtrl;
	//ポップアップ元を得る
	TComponent *pC = ModifyLabelPopupMenu->PopupComponent;
	//ポップアップ元による処理
	if((pResizeCtrl = dynamic_cast<nsResizeCtrl *>(pC)) != 0)
	{
		//現在選択中のコントロールの種類を調べる
		for(int Cnt = 0;Cnt < ResizeList.size();Cnt++)
		{
			//コントロールを得る
			TControl *pCtrl = ResizeList[Cnt]->Control;
			//名前を得る
			String CompoName = pCtrl->Name;
			//指定書類部品を書類間で同じ位置にする
			if(pCtrl == Grid)
			{
				SetSamePosionInDocuments("GRID");
			}
			else
			{
				SetSamePosionInDocuments(CompoName);
			}
		}
	}
	else
	{
		//コントロールを得る
		TControl *pCtrl = static_cast<TControl *>(pC);
		//名前を得る
		String CompoName = pCtrl->Name;
		//指定書類部品を書類間で同じ位置にする
		SetSamePosionInDocuments(CompoName);
	}
	//書類の変更の有無を設定
	SetDocumentChange(true);
}
//-------------------------------------------------------------
//  機能     ：指定書類部品を書類間で同じ位置にする
//
//  関数定義 ：void SetSamePosionInDocuments(String CompoName)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void TMainForm::SetSamePosionInDocuments(String CompoName)
{
	typDocCompo pDoc;

	//指定部品情報
	if(Document.GetDocCompoFromName(CompoName,pDoc) == false)
	{
		return;
	}
	//用紙は同じで書類が違う部品を同じ位置にする
	for(int Cnt = 0;Cnt < Document.GetCompoSize();Cnt++)
	{
		//対象部品
		typDocCompo& pTargetDoc = Document.GetCompoFromIndex(Cnt);
		//該当チェック
		if(pTargetDoc.Name == CompoName && pTargetDoc.Paper == pDoc.Paper && pTargetDoc.DocKind != pDoc.DocKind)
		{
			//同じ位置にデータセット
			pTargetDoc.X      = pDoc.X;
			pTargetDoc.Y      = pDoc.Y;
			pTargetDoc.Width  = pDoc.Width;
			pTargetDoc.Height = pDoc.Height;
		}
		else if(CompoName == StdComponents[scStdComponent::scGrid].Name && pTargetDoc.Name.SubString(1,2) == "D_" &&  pTargetDoc.Paper == pDoc.Paper && pTargetDoc.DocKind != pDoc.DocKind)
		{
			//グリッドセル情報
			typDocCompo pCellDoc;
			Document.GetDocCompoFromName(pTargetDoc.Name,pCellDoc);
			//グリッドのセルを同じ位置にデータセット
			pTargetDoc.X      = pCellDoc.X;
			pTargetDoc.Y      = pCellDoc.Y;
			pTargetDoc.Width  = pCellDoc.Width;
			pTargetDoc.Height = pCellDoc.Height;
		}
	}
}
//-------------------------------------------------------------
//  機能     ：リサイズモードボタンクリック
//
//  関数定義 ：void __fastcall ResizeEnableBtnClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::ResizeEnableBtnClick(TObject *Sender)
{
	TWinControl *pWinCtrl;

	//現在の状態の逆
	bool IsResizeEnable = ResizeEnableBtn->Down;

	//書類情報のZオーダを決定する
	SetDocumentCtrlZOrder();
	//MainPanel上の値をデータにセット
	SetDocDataFromMainPanel();
	//移動・大きさ変更が可能かセット
	SetResizeMode(IsResizeEnable);

	//自分にフォーカスを移動
	ScrollBox->SetFocus();
}
//-------------------------------------------------------------
//  機能     ：リサイズモードメニュー
//
//  関数定義 ：void __fastcall ResizeModeMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::ResizeModeMenuClick(TObject *Sender)
{
	//現在の状態
	bool IsEnable  = CheckResizeMode();
	//反転する
	bool NewEnable = (IsEnable == false);
	//移動・大きさ変更が可能かを反転してセット
	SetResizeMode(NewEnable);
}
//-------------------------------------------------------------
//  機能     ：編集メニュー
//
//  関数定義 ：void __fastcall EditMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::EditMenuClick(TObject *Sender)
{
	//移動・大きさ変更が可能かをチェック
	ResizeModeMenu->Checked = CheckResizeMode();
}
//-------------------------------------------------------------
//  機能     ：右寄せメニュー
//
//  関数定義 ：void __fastcall AliginRightMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::AliginRightMenuClick(TObject *Sender)
{
	int RightMax;
	//選択されているオブジェクトの数
	if(ResizeList.size() < 1)
	{
		return;
	}
	//もっとも右の座標を得る
	RightMax = ResizeList[0]->Control->Left + ResizeList[0]->Control->Width - 1;
	for(int Cnt = 1;Cnt < ResizeList.size();Cnt++)
	{
		if(RightMax < ResizeList[Cnt]->Control->Left + ResizeList[Cnt]->Control->Width - 1)
		{
			RightMax = ResizeList[Cnt]->Control->Left + ResizeList[Cnt]->Control->Width - 1;
		}
	}
	//右寄せ移動
	for(int Cnt = 0;Cnt < ResizeList.size();Cnt++)
	{
		//対象コントロール
		TControl *pCtrl = ResizeList[Cnt]->Control;
		//左位置の修正
		pCtrl->Left = RightMax - pCtrl->Width + 1;
		//リサイズコントロールの再描画
		ResizeList[Cnt]->Control = pCtrl;
	}
}
//-------------------------------------------------------------
//  機能     ：左寄せメニュー
//
//  関数定義 ：void __fastcall AliginLeftMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::AliginLeftMenuClick(TObject *Sender)
{
	int LeftMin;
	//選択されているオブジェクトの数
	if(ResizeList.size() < 1)
	{
		return;
	}
	//もっとも左の座標を得る
	LeftMin = ResizeList[0]->Control->Left;
	for(int Cnt = 1;Cnt < ResizeList.size();Cnt++)
	{
		if(LeftMin > ResizeList[Cnt]->Control->Left)
		{
			LeftMin = ResizeList[Cnt]->Control->Left;
		}
	}
	//左寄せ移動
	for(int Cnt = 0;Cnt < ResizeList.size();Cnt++)
	{
		//対象コントロール
		TControl *pCtrl = ResizeList[Cnt]->Control;

		//左位置の修正
		pCtrl->Left = LeftMin;
		//リサイズコントロールの再描画
		ResizeList[Cnt]->Control = pCtrl;
	}
}
//-------------------------------------------------------------
//  機能     ：上に寄せるメニュー
//
//  関数定義 ：void __fastcall AliginTopMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::AliginTopMenuClick(TObject *Sender)
{
	int TopMin;
	//選択されているオブジェクトの数
	if(ResizeList.size() < 1)
	{
		return;
	}
	//もっとも左の座標を得る
	TopMin = ResizeList[0]->Control->Top;
	for(int Cnt = 1;Cnt < ResizeList.size();Cnt++)
	{
		if(TopMin > ResizeList[Cnt]->Control->Top)
		{
			TopMin = ResizeList[Cnt]->Control->Top;
		}
	}
	//左寄せ移動
	for(int Cnt = 0;Cnt < ResizeList.size();Cnt++)
	{
		//対象コントロール
		TControl *pCtrl = ResizeList[Cnt]->Control;
		//左位置の修正
		pCtrl->Top = TopMin;
		//リサイズコントロールの再描画
		ResizeList[Cnt]->Control = pCtrl;
	}
}
//-------------------------------------------------------------
//  機能     ：下に寄せるメニュー
//
//  関数定義 ：void __fastcall AliginBottomMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::AliginBottomMenuClick(TObject *Sender)
{
	int BottomMax;
	//選択されているオブジェクトの数
	if(ResizeList.size() < 1)
	{
		return;
	}
	//もっとも右の座標を得る
	BottomMax = ResizeList[0]->Control->Top + ResizeList[0]->Control->Height - 1;
	for(int Cnt = 1;Cnt < ResizeList.size();Cnt++)
	{
		if(BottomMax < ResizeList[Cnt]->Control->Top + ResizeList[Cnt]->Control->Height - 1)
		{
			BottomMax = ResizeList[Cnt]->Control->Top + ResizeList[Cnt]->Control->Height - 1;
		}
	}
	//右寄せ移動
	for(int Cnt = 0;Cnt < ResizeList.size();Cnt++)
	{
		//対象コントロール
		TControl *pCtrl = ResizeList[Cnt]->Control;
		//左位置の修正
		pCtrl->Top = BottomMax - pCtrl->Height + 1;
		//リサイズコントロールの再描画
		ResizeList[Cnt]->Control = pCtrl;
	}
}
//-------------------------------------------------------------
//  機能     ：最小の幅に合わせるメニュー
//
//  関数定義 ：void __fastcall MinWidthMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::MinWidthMenuClick(TObject *Sender)
{
	int WidthMin;
	//選択されているオブジェクトの数
	if(ResizeList.size() < 1)
	{
		return;
	}
	//もっとも最小の幅を得る
	WidthMin = ResizeList[0]->Control->Width;
	for(int Cnt = 1;Cnt < ResizeList.size();Cnt++)
	{
		if(WidthMin > ResizeList[Cnt]->Control->Width)
		{
			WidthMin = ResizeList[Cnt]->Control->Width;
		}
	}
	//最小の幅に合わせる
	for(int Cnt = 0;Cnt < ResizeList.size();Cnt++)
	{
		//対象コントロール
		TControl *pCtrl = ResizeList[Cnt]->Control;
		//左位置の修正
		pCtrl->Width = WidthMin;
		//リサイズコントロールの再描画
		ResizeList[Cnt]->Control = pCtrl;
	}
}
//-------------------------------------------------------------
//  機能     ：最大の幅に合わせるメニュー
//
//  関数定義 ：void __fastcall MaxWidthMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::MaxWidthMenuClick(TObject *Sender)
{
	int WidthMax;
	//選択されているオブジェクトの数
	if(ResizeList.size() < 1)
	{
		return;
	}
	//もっとも最小の幅を得る
	WidthMax = ResizeList[0]->Control->Width;
	for(int Cnt = 1;Cnt < ResizeList.size();Cnt++)
	{
		if(WidthMax < ResizeList[Cnt]->Control->Width)
		{
			WidthMax = ResizeList[Cnt]->Control->Width;
		}
	}
	//最大の幅に合わせる
	for(int Cnt = 0;Cnt < ResizeList.size();Cnt++)
	{
		//対象コントロール
		TControl *pCtrl = ResizeList[Cnt]->Control;
		//左位置の修正
		pCtrl->Width = WidthMax;
		//リサイズコントロールの再描画
		ResizeList[Cnt]->Control = pCtrl;
	}
}
//-------------------------------------------------------------
//  機能     ：最小の高さに合わせるメニュー
//
//  関数定義 ：void __fastcall MinHeightMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::MinHeightMenuClick(TObject *Sender)
{
	int HeightMin;
	//選択されているオブジェクトの数
	if(ResizeList.size() < 1)
	{
		return;
	}
	//もっとも最小の幅を得る
	HeightMin = ResizeList[0]->Control->Height;
	for(int Cnt = 1;Cnt < ResizeList.size();Cnt++)
	{
		if(HeightMin > ResizeList[Cnt]->Control->Height)
		{
			HeightMin = ResizeList[Cnt]->Control->Height;
		}
	}
	//最小の幅に合わせる
	for(int Cnt = 0;Cnt < ResizeList.size();Cnt++)
	{
		//対象コントロール
		TControl *pCtrl = ResizeList[Cnt]->Control;
		//高さ修正
		pCtrl->Height = HeightMin;
		//リサイズコントロールの再描画
		ResizeList[Cnt]->Control = pCtrl;
	}
}
//-------------------------------------------------------------
//  機能     ：最大の高さに合わせるメニュー
//
//  関数定義 ：void __fastcall MaxHeightMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::MaxHeightMenuClick(TObject *Sender)
{
	int HeightMax;
	//選択されているオブジェクトの数
	if(ResizeList.size() < 1)
	{
		return;
    }
	//もっとも最小の幅を得る
	HeightMax = ResizeList[0]->Control->Height;
	for(int Cnt = 1;Cnt < ResizeList.size();Cnt++)
	{
		if(HeightMax < ResizeList[Cnt]->Control->Height)
		{
			HeightMax = ResizeList[Cnt]->Control->Height;
		}
	}
	//最小の幅に合わせる
	for(int Cnt = 0;Cnt < ResizeList.size();Cnt++)
	{
		//対象コントロール
		TControl *pCtrl = ResizeList[Cnt]->Control;
		//高さ修正
		pCtrl->Height = HeightMax;
		//リサイズコントロールの再描画
		ResizeList[Cnt]->Control = pCtrl;
	}
}
//-------------------------------------------------------------
//  機能     ：ラバーバンドの描画
//
//  関数定義 ：void __fastcall RubberBandPaint(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::RubberBandPaint(TObject *Sender)
{
	//PaintPanelを得る
	TPaintPanel *pPPanel = static_cast<TPaintPanel *>(Sender);
	//幅と高さ
	int W = pPPanel->Width;
	int H = pPPanel->Height;
	//描画
	if(W > 1 && H == 1)
	{
		pPPanel->Canvas->Pen->Style = psDot;
		pPPanel->Canvas->MoveTo(0,0);
		pPPanel->Canvas->LineTo(W,0);
	}
	else if(H > 1 && W == 1)
	{
		pPPanel->Canvas->Pen->Style = psDot;
		pPPanel->Canvas->MoveTo(0,0);
		pPPanel->Canvas->LineTo(0,H);
	}
}
//-------------------------------------------------------------
//  機能     ：ステータスバーの表示
//
//  関数定義 ：void DispStatus()
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void TMainForm::DispStatus()
{
	String PaperStr;
	String ZoomStr;
	String TitleStr;

	//アプリケーションタイトルの作成
	if(Document.File == L"")
	{
		//タイトル
		TitleStr = String(L"無題 - ") + SYSTEM_NAME;
	}
	else
	{
		//ファイル名を得る
		String FileName = ExtractFileName(Document.File);
		//タイトル
		TitleStr = FileName + L" - " + SYSTEM_NAME;
	}
	//アプリケーションタイトルの表示
	Caption            = TitleStr;
	Application->Title = TitleStr;
	//用紙の表示
	PaperStr = String(L"用紙:") + PaperDef[Document.Paper].DispName;
	StatusBar->Panels->Items[0]->Text = PaperStr;
	//ズームの表示
	ZoomStr = String(L"ズーム:") + String(ZoomDef[Document.Zoom].Zoom) + L"%";
	StatusBar->Panels->Items[1]->Text = ZoomStr;
	//変更状態の表示
	if(Document.Edited == true)
	{
		StatusBar->Panels->Items[2]->Text = L"変更";
	}
	else
	{
		StatusBar->Panels->Items[2]->Text = L"";
	}
}
//-------------------------------------------------------------
//自社情報の一つをラベルにセットする
//-------------------------------------------------------------
bool TMainForm::setLabelFromCompanyInfo(scStdComponent comp,const String& inf)
{
	typDocCompo  pDoc;

	Document.GetDocCompoFromName(StdComponents[comp].Name,pDoc);
	pDoc.Caption = inf;
	Document.SetDocCompoFromName(StdComponents[comp].Name,pDoc);
	SetComponentFromDocCompo(pDoc);

	return true;
}
//-------------------------------------------------------------
//自社情報の反映メニュー
//-------------------------------------------------------------
void __fastcall TMainForm::ApplyCompanyInfoMenuClick(TObject *Sender)
{
	typDocCompo  pDoc;
	//対象メニュー
	TMenuItem *pMenu = static_cast<TMenuItem *>(Sender);
	//対象データ
	typCompanyInfoDef& Inf = CompanyInfo[pMenu->Tag];

	//会社名
	setLabelFromCompanyInfo(scCompanyNameLabel,Inf.CompanyName);
	//代表者
	setLabelFromCompanyInfo(scPersonLabel,Inf.Represent);
	//郵便番号
	setLabelFromCompanyInfo(scZipCodeLabel,Inf.ZipNumber);
	//住所１
	setLabelFromCompanyInfo(scAddressLabel1,Inf.Address1);
	//住所２
	setLabelFromCompanyInfo(scAddressLabel2,Inf.Address2);
	//電話番号
	setLabelFromCompanyInfo(scTELLabel,Inf.TEL);
	//FAX番号
	setLabelFromCompanyInfo(scFAXLabel,Inf.FAX);
	//振込先１
	setLabelFromCompanyInfo(scTransferLabel1,Inf.Transfer1);
	//振込先１
	setLabelFromCompanyInfo(scTransferLabel2,Inf.Transfer2);
	//消費税
	setLabelFromCompanyInfo(scTransferLabel2,Inf.Transfer2);

	//該当データを得る
	typDocData& DocData = Document.Data[Document.DocKind];
	//消費税率設定
	DocData.ConsumptionTaxRatio = Inf.TaxRatio;

	//MainPanel上の値をデータにセット
	SetDocDataFromMainPanel();
	//書類の変更の有無を設定
	SetDocumentChange(true);
}
//-------------------------------------------------------------
//  機能     ：BaseControl上のコントロールのTabOrderを動的に決定する
//
//  関数定義 ：TWinControl *ApplyCompanyInfoMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
TWinControl *TMainForm::SetTabOrder(TWinControl *BaseControl)
{
	std::vector<TWinControl *> Ctrls;
	TWinControl               *pRes = nullptr;
	//リスト開放時にオブジェクトを削除しない
	//TabOrderを持つ(TWinControlを継承)するコントロールを抽出
	for(int Cnt = 0;Cnt < BaseControl->ControlCount;Cnt++)
	{
		//コントロールを得る
		TControl    *pCtrl    = BaseControl->Controls[Cnt];
		//TWinControl *へキャストを試みる
		TWinControl *pWinCtrl = dynamic_cast<TWinControl *>(pCtrl);
		//TWinLabel *へキャストを試みる
		TWinLabel  *pWinLabel = dynamic_cast<TWinLabel   *>(pCtrl);
		//TWinControl継承ならリストに追加
		if(pWinCtrl != nullptr && pWinCtrl->TabStop == true)
		{
			Ctrls.push_back(pWinCtrl);
		}
	}
	//セットするTabOrder
	int SeiingTabOrder = 0;
	//TabOrder設定
	while(true)
	{
		TWinControl *pMinCtrl = nullptr;

		//チェック対象コントロールがあるか
		if(Ctrls.size() == 0)
		{
			break;
		}
		//一番左上のコントロールを得る
		for(int Cnt = 0;Cnt < Ctrls.size();Cnt++)
		{
			//コントロールを得る
			TWinControl *pW = Ctrls[Cnt];
			//左上座標
			int WLeft = pW->Left;
			int WTop  = pW->Top;
			//チェック
			if(pMinCtrl == nullptr)
			{
				pMinCtrl = pW;
			}
			else if(pW->Top + pW->Height - 1 < pMinCtrl->Top)
			{
				pMinCtrl = pW;
			}
			else if(pW->Left < pMinCtrl->Left && (pW->Top <= pMinCtrl->Top && pW->Top + pW->Height >= pMinCtrl->Top))
			{
				pMinCtrl = pW;
			}
		}
		//返却値の設定
		if(pRes == nullptr)
		{
			pRes = pMinCtrl;
		}
		//TabOrderの設定
		pMinCtrl->TabOrder = SeiingTabOrder;
		SeiingTabOrder++;
		//リストから削除
		decltype(Ctrls)::iterator it = std::find(Ctrls.begin(),Ctrls.end(),pMinCtrl);
		if(it != Ctrls.end())
		{
			Ctrls.erase(it);
		}
	}
	return pRes;
}
//-------------------------------------------------------------
//  機能     ：桁区切り線の有無を設定するメニュー
//
//  関数定義 ：void __fastcall ColSeparateLineMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::ColSeparateLineMenuClick(TObject *Sender)
{
	TControl *pCtrl;
	//対象コントロール
	if(ResizeList.size() > 0)
	{
		pCtrl = ResizeList[0]->Control;
	}
	else
	{
		pCtrl = static_cast<TControl *>(ModifyLabelPopupMenu->PopupComponent);
	}
	//書類部品情報名から書類部品情報を得る
	typDocCompo pDoc;
	Document.GetDocCompoFromName(pCtrl->Name,pDoc);
	//桁区切り線の有無を反転
	pDoc.FigureLine = (pDoc.FigureLine == false);
	//枠が無い場合でも桁区切り線がある場合は強制表示
	if(pDoc.FigureLine == true)
	{
		pDoc.Border = true;
	}
	//書類部品情報名から書類部品情報をセット
	Document.SetDocCompoFromName(pCtrl->Name,pDoc);
	//再表示
	SetComponentFromDocCompo(pDoc);
	//書類の変更の有無を設定
	SetDocumentChange(true);
}
//-------------------------------------------------------------
//  機能     ：桁数指定メニュー
//
//  関数定義 ：void __fastcall FigureMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::FigureMenuClick(TObject *Sender)
{
	TControl *pCtrl;
	//対象コントロール
	if(ResizeList.size() > 0)
	{
		pCtrl = ResizeList[0]->Control;
	}
	else
	{
		pCtrl = static_cast<TControl *>(ModifyLabelPopupMenu->PopupComponent);
	}
	//書類部品情報名から書類部品情報を得る
	typDocCompo pDoc;
	Document.GetDocCompoFromName(pCtrl->Name,pDoc);
	//現在の桁数
	int Figure = pDoc.Figures;
	//画面に設定
	FigureSettingForm->FigureEdit->Text = Figure;
	//画面表示
	if(FigureSettingForm->ShowModal() == mrOk)
	{
		//設定された桁数
		pDoc.Figures = FigureSettingForm->FigureEdit->Text.ToIntDef(7);
		//書類部品情報名から書類部品情報をセット
		Document.SetDocCompoFromName(pCtrl->Name,pDoc);
		//再表示
		SetComponentFromDocCompo(pDoc);
		//書類の変更の有無を設定
		SetDocumentChange(true);
	}
}
//-------------------------------------------------------------
//  機能     ：枠線の使用メニュー
//
//  関数定義 ：void __fastcall BorderMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::BorderMenuClick(TObject *Sender)
{
	TControl *pCtrl;
	//対象コントロール
	if(ResizeList.size() > 0)
	{
		pCtrl = ResizeList[0]->Control;
	}
	else
	{
		pCtrl = static_cast<TControl *>(ModifyLabelPopupMenu->PopupComponent);
	}
	//書類部品情報名から書類部品情報を得る
	typDocCompo pDoc;
	Document.GetDocCompoFromName(pCtrl->Name,pDoc);
	//部品種別処理
	if(pDoc.Type == dcLabel || pDoc.Type == dcEdit || pDoc.Type == dcDayEdit || pDoc.Type == dcImage)
	{
		//枠の有無を反転
		pDoc.Border = (pDoc.Border == false);

		//書類部品情報名から書類部品情報をセット
		Document.SetDocCompoFromName(pCtrl->Name,pDoc);

		//再表示
		SetComponentFromDocCompo(pDoc);
	}
	else if(pDoc.Type == dcMoneyEdit)
	{
		//枠を消す場合は桁区切り線も消去
		if(pDoc.Border == true)
		{
			pDoc.Border     = false;
			pDoc.FigureLine = false;
		}
		else
		{
			pDoc.Border     = true;
		}
		//書類部品情報名から書類部品情報をセット
		Document.SetDocCompoFromName(pCtrl->Name,pDoc);
		//再表示
		SetComponentFromDocCompo(pDoc);
	}
	//書類の変更の有無を設定
	SetDocumentChange(true);
}
//-------------------------------------------------------------
//  機能     ：左揃えメニュー
//
//  関数定義 ：void __fastcall LeftJustifyMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::LeftJustifyMenuClick(TObject *Sender)
{
	TControl *pCtrl;
	//対象コントロール
	if(ResizeList.size() > 0)
	{
		pCtrl = ResizeList[0]->Control;
	}
	else
	{
		pCtrl = static_cast<TControl *>(ModifyLabelPopupMenu->PopupComponent);
	}
	//書類部品情報名から書類部品情報を得る
	typDocCompo pDoc;
	Document.GetDocCompoFromName(pCtrl->Name,pDoc);
	//左揃えに設定
	pDoc.Alignment = taLeftJustify;

	//書類部品情報名から書類部品情報をセット
	Document.SetDocCompoFromName(pCtrl->Name,pDoc);

	//再表示
	SetComponentFromDocCompo(pDoc);
	//書類の変更の有無を設定
	SetDocumentChange(true);
}
//-------------------------------------------------------------
//  機能     ：中央揃えメニュー
//
//  関数定義 ：void __fastcall CenterMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::CenterMenuClick(TObject *Sender)
{
	TControl *pCtrl;
	//対象コントロール
	if(ResizeList.size() > 0)
	{
		pCtrl = ResizeList[0]->Control;
	}
	else
	{
		pCtrl = static_cast<TControl *>(ModifyLabelPopupMenu->PopupComponent);
	}
	//書類部品情報名から書類部品情報を得る
	typDocCompo pDoc;
	Document.GetDocCompoFromName(pCtrl->Name,pDoc);
	//左揃えに設定
	pDoc.Alignment = taCenter;

	//書類部品情報名から書類部品情報をセット
	Document.SetDocCompoFromName(pCtrl->Name,pDoc);

	//再表示
	SetComponentFromDocCompo(pDoc);
	//書類の変更の有無を設定
	SetDocumentChange(true);
}
//-------------------------------------------------------------
//  機能     ：右揃えメニュー
//
//  関数定義 ：void __fastcall RightJustifyMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::RightJustifyMenuClick(TObject *Sender)
{
	TControl *pCtrl;
	//対象コントロール
	if(ResizeList.size() > 0)
	{
		pCtrl = ResizeList[0]->Control;
	}
	else
	{
		pCtrl = static_cast<TControl *>(ModifyLabelPopupMenu->PopupComponent);
	}
	//書類部品情報名から書類部品情報を得る
	typDocCompo pDoc;
	Document.GetDocCompoFromName(pCtrl->Name,pDoc);
	//左揃えに設定
	pDoc.Alignment = taRightJustify;

	//書類部品情報名から書類部品情報をセット
	Document.SetDocCompoFromName(pCtrl->Name,pDoc);

	//再表示
	SetComponentFromDocCompo(pDoc);
	//書類の変更の有無を設定
	SetDocumentChange(true);
}
//-------------------------------------------------------------
//  機能     ：前面へ移動
//
//  関数定義 ：void __fastcall BringToFrontMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::BringToFrontMenuClick(TObject *Sender)
{
	//対象コントロール
	TControl *pCtrl = ResizeList[0]->Control;
	//前面に移動
	pCtrl->BringToFront();
	//書類情報のZオーダを決定する
	SetDocumentCtrlZOrder();
	//書類の変更の有無を設定
	SetDocumentChange(true);
}
//-------------------------------------------------------------
//  機能     ：背面へ移動
//
//  関数定義 ：void __fastcall SendToBackMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::SendToBackMenuClick(TObject *Sender)
{
	//対象コントロール
	TControl *pCtrl = ResizeList[0]->Control;
	//前面に移動
	pCtrl->SendToBack();
	//書類情報のZオーダを決定する
	SetDocumentCtrlZOrder();
	//書類の変更の有無を設定
	SetDocumentChange(true);
}
//-------------------------------------------------------------
//  機能     ：書類情報のZオーダを決定する
//
//  関数定義 ：void SetDocumentCtrlZOrder();
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void TMainForm::SetDocumentCtrlZOrder()
{
	int ZOrder = 1;

	typDocCompo pDoc;

	//パネル上のコントロールの順番にZオーダーをセット
	for(int Cnt = 0;Cnt <  MainPanel->ControlCount;Cnt++)
	{
		//対象コントロール
		TControl *pCtrl = MainPanel->Controls[Cnt];
		//名前を得る
		String CtrlName = pCtrl->Name;
		//書類部品情報を得る
		if(Document.GetDocCompoFromName(CtrlName,pDoc) == true)
		{
			//Zオーダの設定
			pDoc.ZOrder = ZOrder;
			//書類部品情報保存
			Document.SetDocCompoFromName(CtrlName,pDoc);
			//次のZオーダー
			ZOrder++;
		}
	}
}
//-------------------------------------------------------------
//  機能     ：ユーザグリッドセル描画
//
//  関数定義 ：void __fastcall GridUserDrawCell(TObject *Sender,...)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::GridUserDrawCell(TObject *Sender,
	  bool &DefaultDraw, int ACol, int ARow, const TRect &ARect,
	  TGridDrawState AState)
{
	TGridRect    G;
	String       ValStr;
	typDocCompo  pDoc;
	bool         doc_valid = false;

	//デフォルトの描画のセルかチェック
	if(ARow < Grid->FixedRows)
	{
		return;
	}
	else if(Grid->Focused() == true && AState.Contains(gdSelected) == true)
	{
		return;
	}

	//セル(列)情報を得る
	ValStr.sprintf(L"D_%02d_%02d",0,ACol);
	doc_valid = Document.GetDocCompoFromName(ValStr,pDoc);
	//列情報を得たか？
	if(doc_valid == false)
	{
		return;
	}
	//桁区切り線の描画の有無
	if(pDoc.FigureLine == false)
	{
		return;
	}
	//セルの範囲
	G.Left   = ACol;
	G.Top    = ARow;
	G.Right  = ACol;
	G.Bottom = ARow;
	//塗りつぶし
	Grid->Canvas->Brush->Color = Grid->Color;
	Grid->Canvas->FillRect(ARect);

	//境界線描画
	Grid->SetCellBorderLine(G,ARect);

	//--- 桁区切り線あり ---
	//桁数
	int ColSeparateNum = pDoc.Figures;
	//描画Canvas
	TCanvas *pCanvas = Grid->Canvas;
	//描画文字列
	String Str = Grid->Cells[ACol][ARow];
	//文字数
	int SLen = Str.Length();
	//Penの設定
	pCanvas->Pen->Style = psDot;
	pCanvas->Pen->Color = Grid->CellBorderColor;
	//一つあたりの幅
	int OneWidth  = ARect.Width() / ColSeparateNum;
	//余り幅
	int MoreWidth = ARect.Width() % ColSeparateNum;
	//描画X座標
	int X = ARect.Left;
	//線を引く
	for(int Cnt = 0;Cnt < ColSeparateNum;Cnt++)
	{
		//現在のX座標
		int X0 = X;
		//最後かを判定
		if(Cnt < ColSeparateNum - 1)
		{
			//X座標
			X += OneWidth;
			X += (Cnt < MoreWidth);
			//線を引く
			pCanvas->MoveTo(X,ARect.Top);
			pCanvas->LineTo(X,ARect.Bottom);
		}
		else
		{
			//X座標
			X = ARect.Right;
		}
		//文字の描画
		if(ColSeparateNum - Cnt -1 < SLen)
		{
			int dx = 0;
			int dy = 0;

			//フォントの設定
			pCanvas->Font->Assign(Grid->Font);
			//描画文字
			String S = Str.SubString(Cnt - (ColSeparateNum - SLen) + 1,1);
			//描画幅
			int TxtWidth  = pCanvas->TextWidth(S);
			//描画高さ
			int TxtHeight = pCanvas->TextHeight(S);
			//X,Yずらしを算出
			if(TxtWidth < X - X0)
				dx = ((X - X0) - TxtWidth)/2;
			if(TxtHeight < Height)
				dy = ((ARect.Height() - TxtHeight) / 2) - 1;
			//描画範囲
			TRect R(X0+1,ARect.Top+1,X-1,ARect.Bottom-1);
			//文字描画
			pCanvas->TextRect(R,X0 + dx,ARect.Top + dy,S);
		}
	}
	//Penの設定
	pCanvas->Pen->Style = psSolid;

	//デフォルトの描画は行わない
	DefaultDraw = false;
}
//-------------------------------------------------------------
//  機能     ：編集ツールバーの状態設定
//
//  関数定義 ：void SetEditToolBarCondition()
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void TMainForm::SetEditToolBarCondition()
{
	nsResizeCtrl *pResizeCtrl;
	TControl     *pCtrl;
	typDocCompo   pDoc;
	bool          IsLabel  = false;
	bool          IsEdit   = false;
	bool          IsShape  = false;
	bool          IsImage  = false;
	bool          IsGrid   = false;

	//オブジェクトの選択状態
	if(ResizeList.size() == 0)
	{
		LeftJustifyBtn ->Enabled = false;
		CenterBtn      ->Enabled = false;
		RightJustifyBtn->Enabled = false;
		FontBtn        ->Enabled = false;
		ColSeparateBtn ->Enabled = false;
		BorderBtn      ->Enabled = false;
	}

	//現在選択中のコントロールの種類を調べる
	for(int Cnt = 0;Cnt < ResizeList.size();Cnt++)
	{
		//コントロールを得る
		pCtrl = ResizeList[Cnt]->Control;
		//種類判定
		if(dynamic_cast<TWinLabel *>(pCtrl) != nullptr)
		{
			IsLabel = true;
		}
		else if(dynamic_cast<TBorderEdit *>(pCtrl) != nullptr)
		{
			IsEdit = true;
		}
		else if(dynamic_cast<TWinShape *>(pCtrl) != nullptr)
		{
			IsShape = true;
		}
		else if(dynamic_cast<TImageControl *>(pCtrl) != nullptr)
		{
			IsImage = true;
		}
		else if(pCtrl == Grid)
		{
			IsGrid = true;
		}
	}
	//各メニューの表示設定
	FontBtn              ->Enabled = ((IsLabel == true || IsEdit == true || IsGrid == true) && IsShape == false && IsImage == false);
	ColSeparateBtn       ->Enabled = false;
	BorderBtn            ->Enabled = false;
	LeftJustifyBtn       ->Enabled = false;
	CenterBtn            ->Enabled = false;
	RightJustifyBtn      ->Enabled = false;
	//関連データを得る
	if(ResizeList.size() == 1)
	{
		Document.GetDocCompoFromName(pCtrl->Name,pDoc);
	}
	//左右、中央揃えの設定
	if(ResizeList.size() == 1 && (IsEdit == true || IsLabel == true))
	{
		//枠線設定メニュー
		LeftJustifyBtn   ->Enabled = true;
		CenterBtn        ->Enabled = true;
		RightJustifyBtn  ->Enabled = true;

		LeftJustifyBtn   ->Down    = (pDoc.Alignment == taLeftJustify);
		CenterBtn        ->Down    = (pDoc.Alignment == taCenter);
		RightJustifyBtn  ->Down    = (pDoc.Alignment == taRightJustify);
	}
	//枠線の使用
	if(ResizeList.size() == 1 && (IsEdit == true || IsLabel == true || IsImage == true))
	{
		//枠線設定メニュー
		BorderBtn->Enabled = true;
		BorderBtn->Down    = pDoc.Border;
	}
	//桁区切り関連設定
	if(IsEdit == true && ResizeList.size() == 1)
	{
		if(pDoc.Type == dcMoneyEdit)
		{
			ColSeparateBtn->Enabled = true;
			ColSeparateBtn->Down    = pDoc.FigureLine;
		}
	}
}
//-------------------------------------------------------------
//  機能     ：ライセンス設定ボタン
//
//  関数定義 ：void __fastcall LicenseSettingBtnClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::LicenseSettingBtnClick(TObject *Sender)
{
	//ライセンス設定フォーム表示
	LicSettingForm->ShowModal();
	//ライセンスチェックタイマー
	LicTimer->Enabled = true;
}
//-------------------------------------------------------------
//  機能     ：ライセンスのチェック
//
//  関数定義 ：void __fastcall LicTimerTimer(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::LicTimerTimer(TObject *Sender)
{
	//タイマーをとめる
	LicTimer->Enabled = false;

	//ライセンスオブジェクト
	TLicense license;

	//ライセンス文字列取得
	LicenseStr  = license.getLicenceStringFromReg();
	//正解のライセンス文字列取得
	String TrueLicStr = license.getLicenceSettingString();
	//レジストリのライセンス文字列と比較
	if(TrueLicStr == LicenseStr)
	{
		//ライセンスあり
		//ボタン非表示
		LicenseSettingBtn->Visible = false;
	}
	else
	{
		//=== ライセンスなし ===
		//ボタン表示
		LicenseSettingBtn->Visible = true;

		//メッセージ表示
		int Res = LicenseForm->ShowModal();

		//選択結果
		if(Res == mrOk)
		{
		}
		else if(Res == mrYesToAll)
		{
			//ライセンス設定に進む
			LicenseSettingBtnClick(LicenseSettingBtn);
		}
		else
		{
			Close();
		}
	}
	return;
}
//-------------------------------------------------------------
//  機能     ：オプションメニュー
//
//  関数定義 ：void __fastcall OptionMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::OptionMenuClick(TObject *Sender)
{
	//設定フォーム表示
	SettingForm->ShowModal();
}
//-------------------------------------------------------------
//  機能     ：編集内容の変更時
//
//  関数定義 ：void __fastcall EditChange(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::EditChange(TObject *Sender)
{
	TEdit       *pEdit  = 0;
	TBorderEdit *pBEdit = 0;
	//変更ありにする
	SetDocumentChange(true);
	//対象エディットを得る
	pEdit  = dynamic_cast<TEdit *>(Sender);
	if(pEdit)
	{
		pBEdit = dynamic_cast<TBorderEdit *>(pEdit->Parent);
	}
	//エディットが有効？
	if(pBEdit)
	{
		//名前
		String EditName = pBEdit->Name;
		//内容
		String Val      = pBEdit->Text.Trim();
		//書類部品情報名から書類部品情報を得る
		typDocCompo pDoc;
		Document.GetDocCompoFromName(EditName,pDoc);
		//小計か？
		if(pDoc.Name == StdComponents[scSubtotalEdit].Name)
		{
			//消費税や合計金額の計算
			SetTaxAndTotalInfo();
		}
		//消費税か？
		else if(pDoc.Name == StdComponents[scTaxEdit].Name)
		{
			//合計金額の計算
			SetTotalInfo();
		}
		//合計金額か？
		else if(pDoc.Name == StdComponents[scTotalEdit].Name)
		{
			//表題の合計金額のセット
			SetMainTotalInfo();
		}
	}
}
//-------------------------------------------------------------
//  機能     ：書類の変更の有無を設定
//
//  関数定義 ：void SetDocumentChange(bool chg)
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
void TMainForm::SetDocumentChange(bool chg)
{
	//変更ありにする
	Document.Edited = chg;
	//ステータスバーの表示
	DispStatus();
}
//-------------------------------------------------------------
//  機能     ：フォームを閉じるときの問合せ
//
//  関数定義 ：void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose)
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
void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	//変更があるか？
	if(Document.Edited == true)
	{
		String FileName;
		//表示ファイル名の設定
		if(Document.File != L"")
		{
			FileName = Document.File;
		}
		else
		{
			FileName = L"無題";
		}
		//問合せ
		nsLib::mbsel Sel = nsLib::YesNoCancelMsgBox(Handle,L"[%s]は変更されています、保存しますか？",FileName.c_str());
		//選択別処理
		switch(Sel)
		{
			case nsLib::mbselYES:
			{
				if(OverWrite() == true)
				{
					break;
				}
				else
				{
					CanClose = false;
					break;
				}
			}
			case nsLib::mbselCancel:
			{
				CanClose = false;
				break;
			}
			case nsLib::mbselNO:
			{
				break;
			}
		}
	}
}
//-------------------------------------------------------------
//  機能     ：ﾛｽﾄﾌｫｰｶｽ時金額の位取り修正
//
//  関数定義 ：void DecimalPointModificationMoneyExit(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::DecimalPointModificationMoneyExit(TObject *Sender)
{
	//ﾌｫｰｶｽ取得時の共通処理
	EditExit(Sender);
}
//-------------------------------------------------------------
//  機能     ：金額関連の表示文字列
//
//  関数定義 ：void __fastcall MoneyDispStr(TObject *Sender,String& DispStr)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::MoneyDispStr(TObject *Sender,String& DispStr)
{
	TBorderEdit *Edit;
	nsDouble     Val;
	//TEdit *にｷｬｽﾄ
	Edit = static_cast<TBorderEdit *>(Sender);
	//文字列を取得してnsLongに代入
	Val = Edit->Text.c_str();

	//請求金額欄か？
	if(Edit->Name == StdComponents[scMoneyEdit].Name)
	{
		//文字列化
		String ValStr = Val.ToStrEX(ES.AccuracyR1,ES.RateTyp1,true);
		//前後の文字を付加
		if(ValStr != "")
		{
			DispStr = String("\\") + ValStr;
		}
	}
	else
	{
		//位取りして戻す
		DispStr = Val.ToStrEX(ES.AccuracyR1,ES.RateTyp1,true);
	}
}
//-------------------------------------------------------------
//  機能     ：金額関連入力の抑制
//
//  関数定義 ：void __fastcall InputRelatedMoneyKeyPress(TObject *Sender,wchar_ &Key)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::InputRelatedMoneyKeyPress(TObject *Sender,wchar_t &Key)
{
	//Enterは入力不可
	if(Key == '\r')
	{
		Key = 0;
	}
	//入力可能文字をﾁｪｯｸ
	if(Key < ' ' ||  Key == ',' || Key == '-' || Key == '.' || (Key >= '0' && Key <= '9'))
	{
		return;
	}
	//入力できない文字は捨てる
	Key = 0;
}
//-------------------------------------------------------------
//  機能     ：さくら電算への問合せページにジャンプするメニュー
//
//  関数定義 ：void __fastcall AskMenuClick(TObject *Sender)
//
//  アクセスレベル ：__published
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::AskMenuClick(TObject *Sender)
{
	ShellExecuteW(Handle,L"open",L"http://www.sakura-densan.com/mail.htm",L"",L"",SW_SHOW);
}
//-------------------------------------------------------------
//  機能     ：ファイル格納フォルダメニュー
//
//  関数定義 ：void __fastcall FileFolderMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::FileFolderMenuClick(TObject *Sender)
{
	//ファイルパスを得る
	String FilePath = Document.File;
	//ディレクトリを得る
	String Dir = ExtractFileDir(FilePath);
	//プロジェクトフォルダを開く
	ShellExecuteW(Handle,L"open",Dir.c_str(),NULL,NULL,SW_SHOWNORMAL);
}
//-------------------------------------------------------------
//  機能     ：請求書番頭 フリー版のデータ取り込み
//
//  関数定義 ：void __fastcall SaveReportHist_Free_MenuClick(TObject *Sender)
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
void __fastcall TMainForm::SaveReportHist_Free_MenuClick(TObject *Sender)
{
	TSBFreeDataList SBFreeDataList;
	//読み込み
	if(SBFreeDataList.load() == false)
	{
		return;
	}
	//データの数をチェック
	if(SBFreeDataList.size() == 0)
	{
		nsLib::InfMsgBox(Handle,L"請求書番頭 フリー版のデータは存在しません、処理を中止します。");
		return;
	}
	//フォルダ参照ダイアログを出す
	wchar_t  SelFolder[512];

	if(nsLib::ShowBrowseFolderDlg(Handle,L"データを保存するフォルダを選択してください",L"C:\\",SelFolder,true) == 0)
	{
		//選択されなかった
		return;
	}
	//表示フォルダーの組み立て
	String DispFolder = String(SelFolder);
	//問合せ
	nsLib::mbsel Sel = nsLib::YesNoMsgBox(Handle,L"フォルダ[%s]に請求書番頭 フリー版のデータを保存します、よろしいですか？",DispFolder.c_str());
	//チェック
	if(Sel == nsLib::mbselNO)
	{
		//処理中止
		return;
	}
	//移動・大きさ変更を取りやめる
	CancelResizeMode(true);
	//リサイズモードを不許可にする
	SetResizeMode(false);
	//メインパネルの表示更新
	UpdateMainPanelDisp();
	//新規作成処理
	NewFile();
	//保存する請求書番頭プロ版のデータのひな形
	typDocument pDoc(Document);
	//現在選択の用紙(A4縦固定)
	pDoc.Paper = A4P;
	//請求書番頭 フリー版のデータを反映しながら、ファイル保存処理を行う
	for(int Cnt = 0;Cnt < SBFreeDataList.size();Cnt++)
	{
		//インデックスを指定して書類情報に反映
		if(SBFreeDataList.reflectToDoc(Cnt,pDoc) == false)
		{
			continue;
		}

		String FileName;
		String FullPath;
		//請求書番頭フリー版の対象データ
		typReportData& pData = SBFreeDataList[Cnt];
		//出力ファイルのフルパス作成
		for(int cnt = 0;;cnt++)
		{
			if(cnt == 0)
			{
				//ファイル名を作成する
				FileName.sprintf(L"%04d%02d%02d-%s-%s%s",pData.Year,pData.Month,pData.Day,pData.NameStr.c_str(),pData.ItemStr.c_str(),STD_FILEXT);
				//フルパスを作成する
				FullPath = DispFolder + "\\" + FileName;
			}
			else
			{
				//ファイル名を作成する
				FileName.sprintf(L"%04d%02d%02d-%s-%s_%d%s",pData.Year,pData.Month,pData.Day,pData.NameStr.c_str(),pData.ItemStr.c_str(),cnt,STD_FILEXT);
				//フルパスを作成する
				FullPath = DispFolder + "\\" + FileName;
			}
			if(FileExists(FullPath) == false)
			{
				//ファイルが存在しないのでフルパス作成完了
				break;
			}
		}
		//IDのリセット
		NowHistory.renumberID();
		//ファイルの保存
		Sdo.writeSDO(pDoc,FullPath);
	}
	//書類の変更の有無を設定
	SetDocumentChange(false);
	//書類の履歴一覧読み込み処理
	LoadReportHist();
	//終了メッセージ
	nsLib::InfMsgBox(Handle,L"請求書番頭 フリー版のデータ取り込みが完了しました。");

	return;
}
//-------------------------------------------------------------
//  機能     ：ﾌｧｲﾙのドロップ時
//
//  関数定義 ：void __fastcall BasePanelFileDrop(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::BasePanelFileDrop(TObject *Sender,
      TStrings *Files)
{
	//拡張子 .sdo のファイルを一つ開く
	for(int Cnt = 0;Cnt < Files->Count;Cnt++)
	{
		//ファイルパス
		String FilePath = Files->Strings[Cnt];
		//拡張子
		String Ext = ExtractFileExt(FilePath);
		//.sdoか？
		if(Ext.CompareIC(STD_FILEXT) == 0)
		{
			//変更がある場合は問い合わせて保存処理を行う
			if(ChangedSave() == nsLib::mbselCancel)
			{
				break;
			}
			//ファイルを開く
			OpenFile(FilePath);
			//処理終了
			break;
		}
	}
}
//-------------------------------------------------------------
//  機能     ：エディットダブルクリック時
//
//  関数定義 ：void __fastcall EditDblClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::EditDblClick(TObject *Sender)
{
	//コンポーネントを得る
	TComponent  *pCompo  = static_cast<TComponent *>(Sender);
	//Editを得る
	TBorderEdit *pEdit   = static_cast<TBorderEdit *>(pCompo);
	//Editの名前を得る
	String      CtrlName = pCompo->Name;
	//コンポーネント名から標準コンポーネント情報を得る
	typStdComponentDef pStdCompo;
	bool std_valid = typDocKindDefs::GetStdComponentDefFromName(CtrlName,pStdCompo,Document.DocKind);
	//情報はある？
	if(std_valid == false)
	{
		return;
	}
	//名前か件名のEditか？
	if(pStdCompo.Number == scNameEdit)
	{
		//名前入力の場合
		SubSelectForm->CtrlName = CtrlName;
		//選択入力画面タイトル
		SubSelectForm->Caption = L"名前入力";
		//選択入力画面表示
		if(SubSelectForm->ShowModal() == mrOk)
		{
			//データをセット
			pEdit->Text = SubSelectForm->Value;
		}
	}
	else if(pStdCompo.Number == scItemEdit)
	{
		//件名入力の場合
		SubSelectForm->CtrlName = CtrlName;
		//選択入力画面タイトル
		SubSelectForm->Caption = L"件名入力";
		//選択入力画面表示
		if(SubSelectForm->ShowModal() == mrOk)
		{
			//データをセット
			pEdit->Text = SubSelectForm->Value;
		}
	}
}
//-------------------------------------------------------------
//  機能     ：繰り返し入力データの追加
//
//  関数定義 ：void AddInputData()
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void TMainForm::AddInputData()
{
	TControl *pCtrl;
	String    NameEditName;
	String    ItemEditName;
	String    Txt;
	//---- 繰り返し入力用ﾃﾞｰﾀ更新(名前) ----
	NameEditName = StdComponents[scNameEdit].Name;
	//MainPanelから指定Nameのコントロールを得る
	pCtrl        = FindControlFromMainPanel(NameEditName);
	//コントロールのTextまたはCaptionを得る
	Txt          = GetControlStrValue(pCtrl);
	Inpts.AddInputData(NameEditName.c_str(),Txt.c_str());

	//---- 繰り返し入力用ﾃﾞｰﾀ更新(件名) ----
	ItemEditName = StdComponents[scItemEdit].Name;
	//MainPanelから指定Nameのコントロールを得る
	pCtrl        = FindControlFromMainPanel(ItemEditName);
	//コントロールのTextまたはCaptionを得る
	Txt          = GetControlStrValue(pCtrl);
	Inpts.AddInputData(ItemEditName.c_str(),Txt.c_str());
}
//-------------------------------------------------------------
//  機能     ：郵便番号から住所を検索ボタン
//
//  関数定義 ：void __fastcall ZipToAddressBtnClick(TObject *Sender,...)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::ZipToAddressMenuClick(TObject *Sender)
{
	String       Prefecture;
	String       City;
	String       Address;
	String       AllAddrStr;
	String       InputZipStr;
	String       ZipStr;
	String       NumStr;
	int          HyphenPos;
	TControl    *pCtrl;
	TBorderEdit *pZipEdit;
	TBorderEdit *pAdr1Edit;

	//客先郵便番号
	pCtrl       = FindControlFromMainPanel(StdComponents[scCustomerZipCodeEdit].Name);
	pZipEdit    = static_cast<TBorderEdit *>(pCtrl);

	//客先住所１
	pCtrl       = FindControlFromMainPanel(StdComponents[scCustomerAddress1Edit].Name);
	pAdr1Edit   = static_cast<TBorderEdit *>(pCtrl);

	//入力された郵便番号を得る
	InputZipStr = pZipEdit->Text.Trim();
	//半角にする
	InputZipStr = sbp::StrToHan(InputZipStr);
	//数字文字だけを抽出(全角も)
	for(int Cnt = 0;Cnt < (int)InputZipStr.Length();Cnt++)
	{
		//指定位置の文字を得る
		NumStr = InputZipStr.SubString(Cnt+1,1);
		//数字なら追加
		if(NumStr.ToIntDef(-1) >= 0)
		{
			ZipStr += NumStr;
		}
	}
	//長さチェック
	if(ZipStr.Length() != 7)
	{
		nsLib::ErrMsgBox(Handle,"郵便番号の桁数が７桁ではありません。\n処理を中止します。");
		return;
	}
	//数字だけで構成されているか？
	if(ZipStr.ToIntDef(-1) == -1)
	{
		nsLib::ErrMsgBox(Handle,"郵便番号に不要な文字が入力されています。\n処理を中止します。");
		return;
	}
	//郵便番号検索
	Zips.getAdress(ZipStr,Prefecture,City,Address);
	//住所を作成
	AllAddrStr = Prefecture + City + Address;
	//セット
	pAdr1Edit->Text = AllAddrStr;
}
//-------------------------------------------------------------
//  機能     ：書類部品表示設定メニュー
//
//  関数定義 ：void __fastcall DispSettingMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::DispSettingMenuClick(TObject *Sender)
{
	//移動・大きさ変更を取りやめる
	CancelResizeMode(true);
	//リサイズモードを不許可にする
	SetResizeMode(false);
	//書類部品表示設定画面表示
	if(DispSettingForm->ShowModal() == mrOk)
	{
		//メインパネルの表示更新
		UpdateMainPanelDisp();
	}
}
//-------------------------------------------------------------
//  機能     ：編集メニュークリック時
//
//  関数定義 ：void __fastcall EditMenuExecute(TBasicAction *Action, bool &Handled)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::EditMenuExecute(TBasicAction *Action, bool &Handled)
{
	//移動・大きさ変更が可能かをチェック
	ResizeModeMenu->Checked = CheckResizeMode();
}
//-------------------------------------------------------------
// 機能     ：書類の一覧(OnDeletion イベントは，リストビュー内の項目が削除されようとしたときに発生します。)
//
// 関数定義 ：void __fastcall HistListViewDeletion(TObject *Sender,TListItem *Item)
//
// ｱｸｾｽﾚﾍﾞﾙ ：
//
// 引数     ：
//
// 戻り値   ：
//
//
//
// 改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::HistListViewDeletion(TObject *Sender, TListItem *Item)
{
	// 関連データ
	THistory *pData = (THistory*)Item->Data;
	// 開放
	delete pData;
	Item->Data = nullptr;
}
//-------------------------------------------------------------
// 機能     ：履歴一覧カラムクリック時
//
// 関数定義 ：void __fastcall HistListViewColumnClick(TObject *Sender)
//
// ｱｸｾｽﾚﾍﾞﾙ ：__published
//
// 引数     ：TObject *Sender
//
// 戻り値   ：
//
// 改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::HistListViewColumnClick(TObject *Sender, TListColumn *Column)
{
	// 現在のソート対象と比較
	if(ColumnToSort == Column->Index)
	{
		// 同じならソート方向逆転
		SortVect[ColumnToSort] = -SortVect[ColumnToSort];
	}
	else
	{
		// ソート列変更
		ColumnToSort = Column->Index;
	}
	//ソートを行う
	HistListView->AlphaSort();
}
//-------------------------------------------------------------
// 機能     ：履歴一覧ソート時比較
//
// 関数定義 ：void __fastcall HistListViewCompare(TObject *Sender)
//
// ｱｸｾｽﾚﾍﾞﾙ ：__published
//
// 引数     ：TObject *Sender
//
// 戻り値   ：
//
// 改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::HistListViewCompare(TObject *Sender, TListItem *Item1,TListItem *Item2, int Data, int &Compare)
{
	if (ColumnToSort == 0)
	{
		String DateStr1;
		String DateStr2;

		// 日付の取得
		try
		{
			TDateTime Date1 = TDateTime(Item1->Caption, TDateTime::Date);

			DateStr1 = Date1.FormatString("yyyy/mm/dd");
		}
		catch (...)
		{
			DateStr1 = TDateTime::CurrentDate().FormatString("yyyy/mm/dd");
		}

		try
		{
			TDateTime Date2 = TDateTime(Item2->Caption, TDateTime::Date);

			DateStr2 = Date2.FormatString("yyyy/mm/dd");
		}
		catch (...)
		{
			DateStr2 = TDateTime::CurrentDate().FormatString("yyyy/mm/dd");
		}

		// 比較
		Compare = SortVect[ColumnToSort] * CompareText(DateStr1, DateStr2);
	}
	else
	{
		// サブアイテムのインデックス
		int ix = ColumnToSort - 1;
		// 比較
		Compare = SortVect[ColumnToSort] * CompareText(Item1->SubItems->Strings[ix], Item2->SubItems->Strings[ix]);
	}
}
//-------------------------------------------------------------
// 機能     ：リスト描画時
//
// 関数定義 ：void __fastcall HistListViewCustomDrawItem(TObject *Sender,...)
//
// ｱｸｾｽﾚﾍﾞﾙ ：private
//
// 引数     ：
//
// 戻り値   ：
//
// 改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::HistListViewCustomDrawItem(TCustomListView *Sender, TListItem *Item,TCustomDrawState State, bool &DefaultDraw)
{
	int DRight;
	int DLeft;
	String DispStr;
	RECT rc;
	// 描画対象ListView
	TListView *pLV = HistListView;
	// カスタム描画
	DefaultDraw = false;
	// 表示領域
	TRect R = Item->DisplayRect(drBounds);
	// 列数
	int ColNum = pLV->Columns->Count;
	// 消去
	pLV->Canvas->FillRect(R);

	// 描画の左端
	DLeft = R.Left;
	// 今回のカラム情報
	TListColumn *pCol = pLV->Columns->Items[0];
	// 右端を得る
	if(pCol->Width > 0)
	{
		DRight = DLeft + pCol->Width;
	}
	else
	{
		DRight = R.Right;
	}
	// 選択列か？
	bool SelRow = (pLV->ItemIndex == Item->Index);
	// 各列の描画を行う
	if (SelRow)
	{
		pLV->Canvas->Brush->Color = clSkyBlue;
		pLV->Canvas->FillRect(R);

		// -----   一列目 -----
		// カラム情報
		TListColumn *pCol = pLV->Columns->Items[0];
		// 描画範囲
		ListView_GetItemRect(pLV->Handle, Item->Index, &rc, LVIR_LABEL);
		// 色
		pLV->Canvas->Font->Color = clBlue;
		// ロック解除
		pLV->Canvas->Refresh();

		// -----  日付 ------
		// カラム情報
		pCol = pLV->Columns->Items[0];
		// 表示文字列
		DispStr = Item->Caption;
		// 描画範囲
		ListView_GetSubItemRect(pLV->Handle, Item->Index, 0, LVIR_LABEL, &rc);
		// 色
		pLV->Canvas->Font->Color = clBlue;
		// 描画
		pLV->Canvas->TextRect(rc, rc.left + 4, rc.top, DispStr);
		// //表示非表示の描画
		// pImgList->Draw(pLV->Canvas,rc.left,rc.top,0);
		// ロック解除
		pLV->Canvas->Refresh();

		// -----  客先名 ------
		// カラム情報
		pCol = pLV->Columns->Items[1];
		// 表示文字列
		DispStr = String(" ") + Item->SubItems->Strings[0];
		// 描画範囲
		ListView_GetSubItemRect(pLV->Handle, Item->Index, 1, LVIR_LABEL, &rc);
		// 色
		pLV->Canvas->Font->Color = clBlack;
		// 描画
		pLV->Canvas->TextRect(rc, rc.left + 4, rc.top, DispStr);
		// ロック解除
		pLV->Canvas->Refresh();

		// -----  件名 ------
		// カラム情報
		pCol = pLV->Columns->Items[2];
		// 表示文字列
		DispStr = String(" ") + Item->SubItems->Strings[1];
		// 描画範囲
		ListView_GetSubItemRect(pLV->Handle, Item->Index, 2, LVIR_LABEL, &rc);
		// 色
		pLV->Canvas->Font->Color = clBlack;
		// 描画
		pLV->Canvas->TextRect(rc, rc.left + 4, rc.top, DispStr);
		// ロック解除
		pLV->Canvas->Refresh();
	}
	else
	{
		// チェックの有無による背景の設定
		if (Item->Checked == false)
		{
			pLV->Canvas->Brush->Color = TColor(0x00E8E8E8);
			pLV->Canvas->FillRect(R);
		}
		// -----   一列目 -----
		// カラム情報
		TListColumn *pCol = pLV->Columns->Items[0];
		// 描画範囲
		ListView_GetItemRect(pLV->Handle, Item->Index, &rc, LVIR_LABEL);
		// ロック解除
		pLV->Canvas->Refresh();

		// -----  日付 ------
		// カラム情報
		pCol = pLV->Columns->Items[0];
		// 表示文字列
		DispStr = Item->Caption;
		// 描画範囲
		ListView_GetSubItemRect(pLV->Handle, Item->Index, 0, LVIR_LABEL, &rc);
		// 色
		pLV->Canvas->Font->Color = clBlue;
		// 描画
		pLV->Canvas->TextRect(rc, rc.left + 4, rc.top, DispStr);
		// //表示非表示の描画
		// pImgList->Draw(pLV->Canvas,rc.left,rc.top,0);
		// ロック解除
		pLV->Canvas->Refresh();

		// -----  客先名 ------
		// カラム情報
		pCol = pLV->Columns->Items[1];
		// 表示文字列
		DispStr = String(" ") + Item->SubItems->Strings[0];
		// 描画範囲
		ListView_GetSubItemRect(pLV->Handle, Item->Index, 1, LVIR_LABEL, &rc);
		// 色
		pLV->Canvas->Font->Color = clBlack;
		// 描画
		pLV->Canvas->TextRect(rc, rc.left + 4, rc.top, DispStr);
		// ロック解除
		pLV->Canvas->Refresh();

		// -----  件名 ------
		// カラム情報
		pCol = pLV->Columns->Items[2];
		// 表示文字列
		DispStr = String(" ") + Item->SubItems->Strings[1];
		// 描画範囲
		ListView_GetSubItemRect(pLV->Handle, Item->Index, 2, LVIR_LABEL, &rc);
		// 色
		pLV->Canvas->Font->Color = clBlack;
		// 描画
		pLV->Canvas->TextRect(rc, rc.left + 4, rc.top, DispStr);
		// ロック解除
		pLV->Canvas->Refresh();
	}
}
//-------------------------------------------------------------
//履歴一覧MouseDown時
//-------------------------------------------------------------
void __fastcall TMainForm::HistListViewMouseDown(TObject *Sender, TMouseButton Button,TShiftState Shift, int X, int Y)
{
	//右クリックか？
	if(Button == mbRight)
	{
		// 対応するアイテム
		TListItem *pItem = HistListView->GetItemAt(X, Y);
		// アイテムがあるならポップアップ表示
		if(pItem != nullptr)
		{
			// 座標変換
			TPoint SPos = HistListView->ClientToScreen(TPoint(X, Y));
			// ポップアップ表示
			HistPopupMenu->Popup(SPos.x, SPos.y);
		}
	}
	//左クリックか？
	else if(Button == mbLeft)
	{
		// 対応するアイテム
		TListItem *pItemAtMouse = HistListView->GetItemAt(X, Y);
		//アイテムの存在チェック
		if(pItemAtMouse == nullptr)
		{
			return;
		}

		try
		{
			// 関連データを得る
			TListItem *pItem = HistListView->Selected;
			// チェック
			if(pItem == nullptr)
			{
				if(pItemAtMouse != nullptr)
				{
					pItem = pItemAtMouse;
					HistListView->Selected = pItemAtMouse;
				}
				else
				{
					return;
				}
			}
			//選択状態チェック
			if(pItem->Data == nullptr)
			{
				return;
			}
			// 関連データ
			THistory *pData = static_cast<THistory*>(pItem->Data);
			//履歴IDを得る
			String FileID = pData->getID();
			// 書類を読む
			if(OpenFile(FileID) == false)
			{
				nsLib::ErrMsgBox(Handle,L"請求書番頭ファイル[%s]のオープンに失敗しました。",pData->getFilePath().c_str());
				return;
			}
			//現在の履歴をセット
			NowHistory = (*pData);
		}
		catch(...)
		{
			//空の書類にする(日付は本日)
			setVoidDocument();

			return;
		}
	}
}
//-------------------------------------------------------------
// 機能     ：履歴の削除メニュー
//
// 関数定義 ：void __fastcall DeleteHistMenuClick(TObject *Sender)
//
// ｱｸｾｽﾚﾍﾞﾙ ：__published
//
// 引数     ：TObject *Sender
//
// 戻り値   ：
//
// 改定者   ：
//-------------------------------------------------------------
void __fastcall TMainForm::DeleteHistMenuClick(TObject *Sender)
{
	//空の書類にする(日付は本日)
	setVoidDocument();
	// 選択アイテム
	TListItem *pItem = HistListView->Selected;
	// チェック
	if(pItem == nullptr)
	{
		return;
	}
	// 関連データ
	THistory *pData = static_cast<THistory*>(pItem->Data);
	//レジストリから履歴情報を削除
	Histories.deleteHistReg(*pData);
	//書類の履歴一覧読み込み処理
	LoadReportHist();
	//無選択状態にする
	HistListView->Selected = nullptr;
}
//-------------------------------------------------------------
//時間表示タイマー
//-------------------------------------------------------------
void __fastcall TMainForm::ClockTimerTimer(TObject *Sender)
{
	String timeStr;
	//現在の時刻を表示
	TDateTime tm = TDateTime::CurrentTime();
	timeStr = tm.FormatString(L"hh:nn:ss");
	ClockPanel->Caption = timeStr;
}
//---------------------------------------------------------------------------
//フォームがアクティブかチェックしてタイトルバーの色設定
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormActiveTimerTimer(TObject *Sender)
{
	if(Application->Active == true)
	{
		//現在のアクティブフォームがTMainFormかチェック
		if(Handle == Application->ActiveFormHandle)
		{
			//現在の色設定がアクティブ用かチェック
			if(isFormActive == false)
			{
				//フォームがアクティブになった時の色設定
				setFormActiveColor();
			}
		}
		else
		{
			//現在の色設定が非アクティブ用かチェック
			if(isFormActive == true)
			{
				//フォームが非アクティブになった時の色設定
				setFormDeactiveColor();
			}
		}
	}
}
//---------------------------------------------------------------------------
//フォームがアクティブになった時
//---------------------------------------------------------------------------
void __fastcall TMainForm::MainFormActivate(TObject *Sender)
{
	setFormActiveColor();
}
//---------------------------------------------------------------------------
//フォームが非アクティブになった時
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormDeactivate(TObject *Sender)
{
	setFormDeactiveColor();
}
//---------------------------------------------------------------------------
//フォームが非アクティブになった時
//---------------------------------------------------------------------------
void __fastcall TMainForm::MainFormDeactivate(TObject *Sender)
{
	setFormDeactiveColor();
}
//---------------------------------------------------------------------------
//フォームがアクティブになった時の色設定
//---------------------------------------------------------------------------
void TMainForm::setFormActiveColor()
{
	TColor active_col = CustomTitleBar->BackgroundColor;

	ClockPanel      ->Color       = active_col;
	ClockBorder1    ->Color       = (TColor)0x00B58242;
	ClockBorder2    ->Color       = (TColor)0x00B58242;
	//フォームがアクティブか記録
	isFormActive = true;
}
//---------------------------------------------------------------------------
//フォームが非アクティブになった時の色設定
//---------------------------------------------------------------------------
void TMainForm::setFormDeactiveColor()
{
	TColor deactive_col = CustomTitleBar->InactiveBackgroundColor;

	ClockPanel      ->Color       = deactive_col;
	ClockBorder1    ->Color       = (TColor)0x00C99D67;
	ClockBorder2    ->Color       = (TColor)0x00C99D67;
	//フォームがアクティブか記録
	isFormActive = false;
}
//---------------------------------------------------------------------------

