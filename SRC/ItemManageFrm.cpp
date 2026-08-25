//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SeikyuBDef.h"
#include "MainFrm.h"
#include "ItemManageFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TItemManageForm *ItemManageForm;
//---------------------------------------------------------------------------
__fastcall TItemManageForm::TItemManageForm(TComponent* Owner)
	: TForm(Owner)
{
}
//-------------------------------------------------------------
//  機能     ：フォーム作成時
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
void __fastcall TItemManageForm::FormCreate(TObject *Sender)
{
	//ソート対象の列(日付)
	ColumnToSort = 0;
	//ソートの順位(昇順、降順)
	SortVect[0]     = -1;  //日付は降順
	SortVect[1]     =  1;  //名前は昇順
	SortVect[2]     =  1;  //件名は昇順
}
//-------------------------------------------------------------
//  機能     ：履歴一覧カラムクリック時
//
//  関数定義 ：void __fastcall HistListViewColumnClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TItemManageForm::HistListViewColumnClick(TObject *Sender,
      TListColumn *Column)
{
	//現在のソート対象と比較
	if(ColumnToSort == Column->Index)
	{
		//同じならソート方向逆転
		SortVect[ColumnToSort] = -SortVect[ColumnToSort];
	}
	else
	{
		//ソート列変更
		ColumnToSort = Column->Index;
	}
	//ソートを行う
	HistListView->AlphaSort();
}
//-------------------------------------------------------------
//  機能     ：履歴一覧ソート時比較
//
//  関数定義 ：void __fastcall HistListViewCompare(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TItemManageForm::HistListViewCompare(TObject *Sender,
      TListItem *Item1, TListItem *Item2, int Data, int &Compare)
{
	if (ColumnToSort == 0)
	{
		//比較
		Compare = SortVect[ColumnToSort] * CompareText(Item1->Caption,Item2->Caption);
	}
	else
	{
		//サブアイテムのインデックス
    	int ix = ColumnToSort - 1;
		//比較
		Compare = SortVect[ColumnToSort] * CompareText(Item1->SubItems->Strings[ix],Item2->SubItems->Strings[ix]);
	}
}
//-------------------------------------------------------------
//  機能     ：書類の一覧(OnDeletion イベントは，リストビュー内の項目が削除されようとしたときに発生します。)
//
//  関数定義 ：void __fastcall HistListViewDeletion(TObject *Sender,TListItem *Item)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TItemManageForm::HistListViewDeletion(TObject *Sender,
      TListItem *Item)
{
//	//関連データ
//	typReportData *pData = (typReportData *)Item->Data;
//	//開放
//	delete pData;
}
//-------------------------------------------------------------
//  機能     ：年、月、日からレジストリキー用日付文字列を作成
//
//  関数定義 ：String MakeRegDateString(int Year,int Month,int Day)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
String TItemManageForm::MakeRegDateString(int Year,int Month,int Day)
{
	String KeyName;
	//キー名の作成
	KeyName.sprintf(L"%04d%02d%02d",Year,Month,Day);

	return KeyName;
}
//-------------------------------------------------------------
//  機能     ：履歴削除メニュー
//
//  関数定義 ：void __fastcall DeleteHistMenuClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TItemManageForm::DeleteHistMenuClick(TObject *Sender)
{
	//選択アイテム
	TListItem *pItem = HistListView->Selected;
	//チェック
	if(pItem == 0)return;
	//関連データ
//	typReportData *pData = (typReportData *)pItem->Data;
	typReadReportInf *pData = static_cast<typReadReportInf *>(pItem->Data);
	//削除を試みる
	if(DeleteReportValue(pData->ID) == true)
	{
		//履歴の表示から削除
		HistListView->Items->Delete(pItem->Index);
    }

//	//レジストリキー
//	String RegKeyStr = pData->Key;
//	//レジストリ
//	SBHistRegIni *pReg = new SBHistRegIni;
//	//セクションの削除
//	try
//	{
//		//削除を試みる
//		pReg->EraseSection(RegKeyStr);
//	}
//	catch(...)
//	{
//		return;
//	}
//	//履歴の表示から削除
//	HistListView->Items->Delete(pItem->Index);
}
//-------------------------------------------------------------
//  機能     ：履歴一覧MouseDown時
//
//  関数定義 ：void __fastcall HistListViewMouseDown(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TItemManageForm::HistListViewMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
	//右クリックか？
	if(Button == mbRight)
	{
		//対応するアイテム
		TListItem *pItem = HistListView->GetItemAt(X,Y);
		//アイテムがあるならポップアップ表示
		if(pItem)
		{
			//座標変換
			TPoint SPos = HistListView->ClientToScreen(TPoint(X,Y));
			//ポップアップ表示
			HistPopupMenu->Popup(SPos.x,SPos.y);
		}
	}
}
//-------------------------------------------------------------
//  機能     ：履歴クリック時
//
//  関数定義 ：void __fastcall HistListViewClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TItemManageForm::HistListViewClick(TObject *Sender)
{
	//関連データを得る
	TListItem *pItem = HistListView->Selected;
	//チェック
	if(pItem == 0)return;
	//関連データ
//	typReportData *pData = (typReportData *)pItem->Data;
	typReadReportInf *pData = static_cast<typReadReportInf *>(pItem->Data);
//	//日付文字列を得る
//	String DateRegStr = MakeRegDateString(pData->Year,pData->Month,pData->Day);
	//書類を読む
//	MainForm->LoadReport(false,DateRegStr,pData->NameStr,pData->ItemStr);
//	MainForm->LoadReport(pData->Key);
}
//---------------------------------------------------------------------------
