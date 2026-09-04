//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "zbWindowDef.h"
#include "SeikyuBDef.h"
#include "SubSelectFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "BitBtn2"
#pragma resource "*.dfm"
TSubSelectForm *SubSelectForm;
//---------------------------------------------------------------------------
__fastcall TSubSelectForm::TSubSelectForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
//フォーム作成時
//---------------------------------------------------------------------------
void __fastcall TSubSelectForm::FormCreate(TObject *Sender)
{
	//タイトルバーに標準色を設定する
	zbWindowDef::setStdTitlebarColor(this);
}
//-------------------------------------------------------------
//  機能     ：フォーム表示時
//
//  関数定義 ：void __fastcall FormShow(TObject *Sender)
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
void __fastcall TSubSelectForm::FormShow(TObject *Sender)
{
	//入力用情報読み込み
	Inpts.GetInputDataList(CtrlName.c_str(),ItemListBox->Items);
}
//-------------------------------------------------------------
//  機能     ：閉じるボタン
//
//  関数定義 ：void __fastcall CancelBtnClick(TObject *Sender)
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
void __fastcall TSubSelectForm::CancelBtnClick(TObject *Sender)
{
	ModalResult = mrCancel;
}

//-------------------------------------------------------------
//  機能     ：選択ボタン
//
//  関数定義 ：void __fastcall OkBtnClick(TObject *Sender)
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
void __fastcall TSubSelectForm::OkBtnClick(TObject *Sender)
{
	//選択アイテム
	int Idx = ItemListBox->ItemIndex;
	//チェック
	if(Idx < 0)return;
	//選択内容を得る
	Value = ItemListBox->Items->Strings[Idx];
	//選択終了
	ModalResult = mrOk;
}

//-------------------------------------------------------------
//  機能     ：削除メニュー
//
//  関数定義 ：void __fastcall DeleteMenuClick(TObject *Sender)
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
void __fastcall TSubSelectForm::DeleteMenuClick(TObject *Sender)
{
	//選択アイテム
	int Idx = ItemListBox->ItemIndex;
	//チェック
	if(Idx < 0)return;
	//選択内容を得る
	Value = ItemListBox->Items->Strings[Idx];
	//削除
	Inpts.DeleteInputData(CtrlName.c_str(),Value.c_str());
	//表示から削除
	ItemListBox->Items->Delete(Idx);
}
//---------------------------------------------------------------------------

