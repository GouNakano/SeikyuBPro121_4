//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainFrm.h"
#include "LabelModifyFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TBaseEdit"
#pragma link "BitBtn2"
#pragma resource "*.dfm"
TLabelModifyForm *LabelModifyForm;
//---------------------------------------------------------------------------
__fastcall TLabelModifyForm::TLabelModifyForm(TComponent* Owner)
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
void __fastcall TLabelModifyForm::FormShow(TObject *Sender)
{
	//メインフォームのキーのハンドリングを停止する
	pEve = MainForm->ApplicationEvents->OnMessage;
	MainForm->ApplicationEvents->OnMessage = 0;
	//フォーカスセット
	LabelValEdit->SetFocus();
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
void __fastcall TLabelModifyForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
	//メインフォームのキーのハンドリングを再開する
	MainForm->ApplicationEvents->OnMessage = pEve;
}
//-------------------------------------------------------------
//  機能     ：ｷｬﾝｾﾙボタン
//
//  関数定義 ：void __fastcall CancelBtnClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TLabelModifyForm::CancelBtnClick(TObject *Sender)
{
	ModalResult = mrCancel;
}
//-------------------------------------------------------------
//  機能     ：変更ボタン
//
//  関数定義 ：void __fastcall ModifyBtnClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TLabelModifyForm::ModifyBtnClick(TObject *Sender)
{
	ModalResult = mrOk;
}
//---------------------------------------------------------------------------

