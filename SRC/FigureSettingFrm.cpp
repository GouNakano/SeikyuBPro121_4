//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "nsMsgBox.h"
#include "MainFrm.h"
#include "FigureSettingFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "BitBtn2"
#pragma resource "*.dfm"
TFigureSettingForm *FigureSettingForm;
//---------------------------------------------------------------------------
__fastcall TFigureSettingForm::TFigureSettingForm(TComponent* Owner)
	: TForm(Owner)
{
}
//-------------------------------------------------------------
//  機能     ：フォーム表示時
//
//  関数定義 ：void __fastcall FormShow(TObject *Sender)
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
void __fastcall TFigureSettingForm::FormShow(TObject *Sender)
{
	//メインフォームのキーのハンドリングを停止する
	pEve = MainForm->ApplicationEvents->OnMessage;
	MainForm->ApplicationEvents->OnMessage = 0;
	//フォーカス
	FigureEdit->SetFocus();
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
void __fastcall TFigureSettingForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
	//メインフォームのキーのハンドリングを再開する
	MainForm->ApplicationEvents->OnMessage = pEve;
}

//-------------------------------------------------------------
//  機能     ：設定ボタン
//
//  関数定義 ：void __fastcall OkBtnClick(TObject *Sender)
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
void __fastcall TFigureSettingForm::OkBtnClick(TObject *Sender)
{
	//設定値
	int Val = FigureEdit->Text.ToIntDef(0);
	//範囲チェック
	if(Val < 4 || Val > 12)
	{
		nsLib::ErrMsgBox(Handle,"桁数は4～12の間で設定してください。");
		return;
	}
	//OKで閉じる
	ModalResult = mrOk;
}
//-------------------------------------------------------------
//  機能     ：キャンセルボタン
//
//  関数定義 ：void __fastcall CancelBtnClick(TObject *Sender)
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
void __fastcall TFigureSettingForm::CancelBtnClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
