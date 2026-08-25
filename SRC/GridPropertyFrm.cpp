//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainFrm.h"
#include "GridPropertyFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGridPropertyForm *GridPropertyForm;
//---------------------------------------------------------------------------
__fastcall TGridPropertyForm::TGridPropertyForm(TComponent* Owner)
	: TForm(Owner)
{
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
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TGridPropertyForm::FormShow(TObject *Sender)
{
	String       ValStr;
	typDocCompo  pDoc;
//	typDocCompo *pDoc;
	typDocCompo  pGridDoc;
//	typDocCompo *pGridDoc;
	TComponent  *pCompo;
	TEdit       *pEW;
	TEdit       *pET;
	TCheckBox   *pFL;
	TEdit       *pFN;
	TComboBoxEx *pCB;
	//メインフォームのキーのハンドリングを停止する
	pEve = MainForm->ApplicationEvents->OnMessage;
	MainForm->ApplicationEvents->OnMessage = 0;

	//--- グリッドの設定 ---

	//グリッドの情報を得る
	Document.GetDocCompoFromName(StdComponents[scStdComponent::scGrid].Name,pGridDoc);

//	pGridDoc  = GetDocCompoFromName(StdComponents[scStdComponent::scGrid].Name);
	//行数セット
	RowNumEdit->Text = pGridDoc.RowNum;
//	RowNumEdit->Text = pGridDoc->RowNum;

	//列情報の設定
//	for(int Cnt = 0;Cnt < pGridDoc->ColNum;Cnt++)
	for(int Cnt = 0;Cnt < pGridDoc.ColNum;Cnt++)
	{
		//セルの情報(先頭行)
		ValStr.sprintf(L"D_%02d_%02d",0,Cnt);
		//セルの情報
		bool doc_valid = Document.GetDocCompoFromName(ValStr,pDoc);


//		pDoc = GetDocCompoFromName(ValStr);
		//タイトルEditを得る
		ValStr = String("CT_") + Cnt;
		pCompo = FindComponent(ValStr);
		pET    = static_cast<TEdit *>(pCompo);
		//データセット
//		if(pDoc)
		if(doc_valid == true)
		{
			pET->Text = pDoc.Caption;
//			pET->Text = pDoc->Caption;
		}
		else
		{
			pET->Text = L"";
		}
		//テキスト揃えのコンボボックスを得る
		ValStr = String("AL_") + Cnt;
		pCompo = FindComponent(ValStr);
		pCB    = static_cast<TComboBoxEx *>(pCompo);

//		if(pDoc)
		if(doc_valid == true)
		{
//			switch(pDoc->Alignment)
			switch(pDoc.Alignment)
			{
				case taLeftJustify:
				{
					pCB->ItemIndex = 0;
					break;
				}
				case taCenter:
				{
					pCB->ItemIndex = 1;
					break;
				}
				case taRightJustify:
				{
					pCB->ItemIndex = 2;
					break;
				}
				default:
				{
					pCB->ItemIndex = 0;
					break;
				}
			}
		}
		else
		{
			pCB->ItemIndex = 0;
		}

		//桁区切り線チェックボックスの設定
		ValStr = String("FL_") + Cnt;
		pCompo = FindComponent(ValStr);
		//有効な列だけ処理
		if(pCompo != nullptr)
		{
			pFL    = static_cast<TCheckBox *>(pCompo);
			//データセット
//			if(pDoc)
			if(doc_valid == true)
			{
				pFL->Checked = pDoc.FigureLine;
//				pFL->Checked = pDoc->FigureLine;
			}
			else
			{
				pFL->Checked = false;
			}
		}
		//桁数の設定
		ValStr = String("FN_") + Cnt;
		pCompo = FindComponent(ValStr);
		//有効な列だけ処理
		if(pCompo != nullptr)
		{
			pFN    = static_cast<TEdit *>(pCompo);
			//データセット
//			if(pDoc)
			if(doc_valid == true)
			{
				pFN->Text = pDoc.Figures;
//				pFN->Text = pDoc->Figures;
			}
			else
			{
				pFN->Text = DEFAULT_FIGURES;
			}
		}
	}
	//フォーカス
	RowNumEdit->SetFocus();
}
//-------------------------------------------------------------
//  機能     ：フォームを閉じる時
//
//  関数定義 ：void __fastcall FormClose(TObject *Sender,TCloseAction &Action)
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
void __fastcall TGridPropertyForm::FormClose(TObject *Sender,TCloseAction &Action)
{
	//メインフォームのキーのハンドリングを再開する
	MainForm->ApplicationEvents->OnMessage = pEve;
}
//-------------------------------------------------------------
//  機能     ：設定ボタン
//
//  関数定義 ：void __fastcall FormatBtnClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TGridPropertyForm::FormatBtnClick(TObject *Sender)
{
	typDocCompo  pDoc;
	bool         doc_valid;
//	typDocCompo *pDoc;
	typDocCompo  pGridDoc;
//	typDocCompo *pGridDoc;
	TComponent  *pCompo;
	TEdit       *pEW;
	TEdit       *pET;
	TCheckBox   *pFL;
	TEdit       *pFN;
	TComboBoxEx *pCB;
	String       ValStr;

	//行に関するデータを得る
	int  RowNum  = GridPropertyForm->RowNumEdit->Text.ToIntDef(-1);
	//行数チェック
	if(RowNum < 2 || RowNum > 50)
	{
		nsLib::ErrMsgBox(Handle,L"行数は2～50の間で設定してください。");
		return;
	}
	//グリッドの行数を保存
	Document.GetDocCompoFromName(StdComponents[scStdComponent::scGrid].Name,pGridDoc);
	pGridDoc.RowNum = RowNum;         //行数
//	pGridDoc         = GetDocCompoFromName(StdComponents[scStdComponent::scGrid].Name);
//	pGridDoc->RowNum = RowNum;         //行数

	//列情報の設定
//	for(int Cnt = 0;Cnt < pGridDoc->ColNum;Cnt++)
	for(int Cnt = 0;Cnt < pGridDoc.ColNum;Cnt++)
	{
		//セルの情報(先頭行)
		ValStr.sprintf(L"D_%02d_%02d",0,Cnt);
		doc_valid = Document.GetDocCompoFromName(ValStr,pDoc);
//		pDoc = GetDocCompoFromName(ValStr);
		//タイトルEditを得る
		ValStr = String(L"CT_") + Cnt;
		pCompo = GridPropertyForm->FindComponent(ValStr);
		pET    = static_cast<TEdit *>(pCompo);
		//セルの情報にセット
//		if(pDoc)
		if(doc_valid == true)
		{
			pDoc.Caption = pET->Text;
//			pDoc->Caption = pET->Text;
		}
		//テキスト揃えのコンボボックスを得る
		ValStr = String(L"AL_") + Cnt;
		pCompo = FindComponent(ValStr);
		pCB    = static_cast<TComboBoxEx *>(pCompo);
//		if(pDoc)
		if(doc_valid == true)
		{
			switch(pCB->ItemIndex)
			{
				case 0:
				{
					pDoc.Alignment = taLeftJustify;
//					pDoc->Alignment = taLeftJustify;
					break;
				}
				case 1:
				{
					pDoc.Alignment = taCenter;
//					pDoc->Alignment = taCenter;
					break;
				}
				case 2:
				{
					pDoc.Alignment = taRightJustify;
//					pDoc->Alignment = taRightJustify;
					break;
				}
				default:
				{
					pDoc.Alignment = taLeftJustify;
//					pDoc->Alignment = taLeftJustify;
					break;
				}
			}
		}
		//桁区切り線チェックボックスの設定
		ValStr = String("FL_") + Cnt;
		pCompo = GridPropertyForm->FindComponent(ValStr);
		//有効な列だけ処理
		if(pCompo != nullptr)
		{
			pFL = static_cast<TCheckBox *>(pCompo);
			//データセット
//			if(pDoc)
			if(doc_valid == true)
			{
				pDoc.FigureLine = pFL->Checked;
//				pDoc->FigureLine = pFL->Checked;
			}
		}
		//桁数の設定
		ValStr = String("FN_") + Cnt;
		pCompo = GridPropertyForm->FindComponent(ValStr);
		//有効な列だけ処理
		if(pCompo != nullptr)
		{
			pFN = static_cast<TEdit *>(pCompo);
			//データセット
//			if(pDoc)
			if(doc_valid == true)
			{
				pDoc.Figures = pFN->Text.ToIntDef(DEFAULT_FIGURES);
//				pDoc->Figures = pFN->Text.ToIntDef(DEFAULT_FIGURES);
			}
		}
		//セルの情報(先頭行)の更新
		Document.SetDocCompoFromName(pDoc.Name,pDoc);
	}
	//閉じる
	ModalResult = mrOk;
}
//-------------------------------------------------------------
//  機能     ：閉じるボタン
//
//  関数定義 ：void __fastcall FormatBtnClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TGridPropertyForm::CloseBtnClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

