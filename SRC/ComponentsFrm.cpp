//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "PropertyFrm.h"
#include "ComponentsFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "BitBtn2"
#pragma resource "*.dfm"
TComponentsForm *ComponentsForm;
//---------------------------------------------------------------------------
__fastcall TComponentsForm::TComponentsForm(TComponent* Owner)
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
void __fastcall TComponentsForm::FormShow(TObject *Sender)
{
	String Str;
	//ListViewの消去
	ListView->Clear();
	//部品一覧表の作成
//	for(int Cnt = 0;Cnt < Document.DocCompo.GetCount();Cnt++)
	for(int Cnt = 0;Cnt < Document.GetCompoSize();Cnt++)
	{
		//対象部品
		typDocCompo& pDoc = Document.GetCompoFromIndex(Cnt);
//		typDocCompo *pDoc = Document.DocCompo.GetItem(Cnt);
		//用紙が一致するかチェック
//		if(pDoc->Paper != Document.Paper)
		if(pDoc.Paper != Document.Paper)
		{
			continue;
		}
		//グリッドの部品(D_で始まる)は除外
//		if(pDoc->Name.SubString(1,2) == "D_")
		if(pDoc.Name.SubString(1,2) == L"D_")
		{
			continue;
		}
		//名称が無いものは除外
//		if(pDoc->Name == L"")
		if(pDoc.Name == L"")
		{
			continue;
		}
		//ListViewアイテム作成
		TListItem *pItem = ListView->Items->Add();
		//名称
		pItem->Caption = pDoc.Name;
//		pItem->Caption = pDoc->Name;
		//表示
//		if(pDoc->Visible == true)
		if(pDoc.Visible == true)
		{
			pItem->SubItems->Add("する");
		}
		else
		{
			pItem->SubItems->Add("しない");
		}
		//印刷
//		if(pDoc->IsPrint == true)
		if(pDoc.IsPrint == true)
		{
			pItem->SubItems->Add("する");
		}
		else
		{
			pItem->SubItems->Add("しない");
		}
		//水平位置
		Str.sprintf(L"%.2Lf",pDoc.X);
//		Str.sprintf(L"%.2Lf",pDoc->X);
		pItem->SubItems->Add(Str);
		//垂直位置
		Str.sprintf(L"%.2Lf",pDoc.Y);
//		Str.sprintf(L"%.2Lf",pDoc->Y);
		pItem->SubItems->Add(Str);
		//幅
		Str.sprintf(L"%.2Lf",pDoc.Width);
//		Str.sprintf(L"%.2Lf",pDoc->Width);
		pItem->SubItems->Add(Str);
		//高さ
		Str.sprintf(L"%.2Lf",pDoc.Height);
//		Str.sprintf(L"%.2Lf",pDoc->Height);
		pItem->SubItems->Add(Str);
		//内容
		pItem->SubItems->Add(pDoc.Caption);
//		pItem->SubItems->Add(pDoc->Caption);
		//関連データ
		pItem->Data = new typDocCompo(pDoc);
	}
}
//-------------------------------------------------------------
//  機能     ：閉じるボタン
//
//  関数定義 ：void __fastcall CloseBtnClick(TObject *Sender)
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
void __fastcall TComponentsForm::CloseBtnClick(TObject *Sender)
{
	Close();
}
//-------------------------------------------------------------
//  機能     ：書式設定ボタン
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
void __fastcall TComponentsForm::FormatBtnClick(TObject *Sender)
{
	//選択ListItem
	TListItem *pItem = ListView->Selected;
	//対象データ
	PropertyForm->pDoc = static_cast<typDocCompo *>(pItem->Data);
	//書式設定フォーム表示
	PropertyForm->ShowModal();
}
//-------------------------------------------------------------
//  機能     ：部品一覧表要素削除時
//
//  関数定義 ：void __fastcall ListViewDeletion(TObject *Sender, TListItem *Item)
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
void __fastcall TComponentsForm::ListViewDeletion(TObject *Sender, TListItem *Item)
{
	typDocCompo *pDoc = reinterpret_cast<typDocCompo *>(Item->Data);

	//紐づけされたオブジェクト削除
	delete pDoc;
}
//---------------------------------------------------------------------------

