//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SeikyuBDef.h"
#include "DispSettingFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TListView2"
#pragma resource "*.dfm"
TDispSettingForm *DispSettingForm;
//---------------------------------------------------------------------------
__fastcall TDispSettingForm::TDispSettingForm(TComponent* Owner)
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
void __fastcall TDispSettingForm::FormShow(TObject *Sender)
{
	//リストクリア
	ObjectListView->Items->Clear();
	//部品情報からコンポーネントの情報表示
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
		//コンポーネント名から標準コンポーネント情報を得る
		typStdComponentDef pStdCompo;
		bool std_valid = typDocKindDefs::GetStdComponentDefFromName(pDoc.Name,pStdCompo,Document.DocKind);
		//リストアイテムの作成
		TListItem *pItem = ObjectListView->Items->Add();
		//部品情報を関連付け
		pItem->Data = new typDocCompo(pDoc);
		//表示の有無
		pItem->Checked = pDoc.Visible;
		//部品タイプの表示
		switch(pDoc.Type)
		{
			case dcLabel:
			{
				pItem->SubItems->Add("ラベル");
				break;
			}
			case dcEdit:
			case dcDayEdit:
			case dcMoneyEdit:
			{
				pItem->SubItems->Add("入力エディット");
				break;
			}
			case dcImage:
			{
				pItem->SubItems->Add("画像");
				break;
			}
			case dcVLine:
			{
				pItem->SubItems->Add("縦線");
				break;
			}
			case dcCLine:
			{
				pItem->SubItems->Add("横線");
				break;
			}
			default:
			{
				pItem->SubItems->Add("不明");
				break;
			}
		}
		//部品名称
		if(std_valid == true)
		{
			pItem->SubItems->Add(pStdCompo.Explain);
		}
		else
		{
			pItem->SubItems->Add(pDoc.Name);
		}
	}
}
//-------------------------------------------------------------
//  機能     ：OKボタン
//
//  関数定義 ：void __fastcall CancelBtnClick(TObject *Sender)
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
void __fastcall TDispSettingForm::OkBtnClick(TObject *Sender)
{
	typDocCompo *pDoc;

	//部品の表示情報をセット
	for(int Cnt = 0;Cnt < ObjectListView->Items->Count;Cnt++)
	{
		//リストアイテム情報
		TListItem *pItem = ObjectListView->Items->Item[Cnt];
		//関連情報取得
		pDoc = static_cast<typDocCompo *>(pItem->Data);
		//表示設定
        pDoc->Visible = pItem->Checked;
	}
	//閉じる
	ModalResult = mrOk;
}
//-------------------------------------------------------------
//  機能     ：キャンセルボタン
//
//  関数定義 ：void __fastcall CancelBtnClick(TObject *Sender)
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
void __fastcall TDispSettingForm::CancelBtnClick(TObject *Sender)
{
	//閉じる
	ModalResult = mrCancel;
}
//-------------------------------------------------------------
//  機能     ：リストビューの行削除時
//
//  関数定義 ：void __fastcall ObjectListViewDeletion(TObject *Sender, TListItem *Item)
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
void __fastcall TDispSettingForm::ObjectListViewDeletion(TObject *Sender, TListItem *Item)
{
	typDocCompo *pDoc = reinterpret_cast<typDocCompo *>(Item->Data);
	//紐づけ情報の削除
	delete pDoc;
}
//---------------------------------------------------------------------------

