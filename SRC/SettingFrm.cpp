//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SeikyuBDef.h"
#include "SettingFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSettingForm *SettingForm;
//---------------------------------------------------------------------------
__fastcall TSettingForm::TSettingForm(TComponent* Owner)
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
void __fastcall TSettingForm::FormShow(TObject *Sender)
{
	//アクティブページ
	PageControl->ActivePage = GeneralTabSheet;
	//フォーカス
	RemainCBox->SetFocus();
	//設定を画面に反映
	RemainCBox      ->Checked = ES.IsRemain;
	BackupFileCBox  ->Checked = ES.BackupFile;
	UseTemplateCBox ->Checked = ES.UseTemplateFile;
	TodayCBox       ->Checked = ES.IsToday;
	TemplateFileEdit->Text    = ES.TemplateFile;

	//小数点関係の設定
	Ratio00Edit    ->Text = ES.AccuracyR1;
	Ratio01Edit    ->Text = ES.AccuracyR2;
	Ratio02Edit    ->Text = ES.AccuracyR3;
	Ratio03Edit    ->Text = ES.AccuracyR4;
	Ratio04Edit    ->Text = ES.AccuracyR5;

	     if(ES.RateTyp1 == tOmit   )RB00->Checked = true;
	else if(ES.RateTyp1 == tRevalue)RB01->Checked = true;
	else if(ES.RateTyp1 == tRound  )RB02->Checked = true;

	     if(ES.RateTyp2 == tOmit   )RB10->Checked = true;
	else if(ES.RateTyp2 == tRevalue)RB11->Checked = true;
	else if(ES.RateTyp2 == tRound  )RB12->Checked = true;

	     if(ES.RateTyp3 == tOmit   )RB20->Checked = true;
	else if(ES.RateTyp3 == tRevalue)RB21->Checked = true;
	else if(ES.RateTyp3 == tRound  )RB22->Checked = true;

	     if(ES.RateTyp4 == tOmit   )RB30->Checked = true;
	else if(ES.RateTyp4 == tRevalue)RB31->Checked = true;
	else if(ES.RateTyp4 == tRound  )RB32->Checked = true;

	     if(ES.RateTyp5 == tOmit   )RB40->Checked = true;
	else if(ES.RateTyp5 == tRevalue)RB41->Checked = true;
	else if(ES.RateTyp5 == tRound  )RB42->Checked = true;

	//テンプレートファイル関連の設定
	UseTemplateCBoxClick(UseTemplateCBox);
}

//-------------------------------------------------------------
//  機能     ：OKボタン
//
//  関数定義 ：void __fastcall OkBtnClick(TObject *Sender)
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
void __fastcall TSettingForm::OkBtnClick(TObject *Sender)
{
	//画面の設定を反映
	ES.IsRemain        = RemainCBox      ->Checked;
	ES.BackupFile      = BackupFileCBox  ->Checked;
	ES.UseTemplateFile = UseTemplateCBox ->Checked;
	ES.IsToday         = TodayCBox       ->Checked;
	ES.TemplateFile    = TemplateFileEdit->Text;

	//小数点関係の設定
	ES.AccuracyR1 = Ratio00Edit->Text.ToIntDef(0);
	ES.AccuracyR2 = Ratio01Edit->Text.ToIntDef(0);
	ES.AccuracyR3 = Ratio02Edit->Text.ToIntDef(0);
	ES.AccuracyR4 = Ratio03Edit->Text.ToIntDef(0);
	ES.AccuracyR5 = Ratio04Edit->Text.ToIntDef(0);
	//小数点有効桁以下処理タイプ
	if(RB00->Checked == true)ES.RateTyp1 = tOmit;
	if(RB01->Checked == true)ES.RateTyp1 = tRevalue;
	if(RB02->Checked == true)ES.RateTyp1 = tRound;

	if(RB10->Checked == true)ES.RateTyp2 = tOmit;
	if(RB11->Checked == true)ES.RateTyp2 = tRevalue;
	if(RB12->Checked == true)ES.RateTyp2 = tRound;

	if(RB20->Checked == true)ES.RateTyp3 = tOmit;
	if(RB21->Checked == true)ES.RateTyp3 = tRevalue;
	if(RB22->Checked == true)ES.RateTyp3 = tRound;

	if(RB30->Checked == true)ES.RateTyp4 = tOmit;
	if(RB31->Checked == true)ES.RateTyp4 = tRevalue;
	if(RB32->Checked == true)ES.RateTyp4 = tRound;

	if(RB40->Checked == true)ES.RateTyp5 = tOmit;
	if(RB41->Checked == true)ES.RateTyp5 = tRevalue;
	if(RB42->Checked == true)ES.RateTyp5 = tRound;

	//保存する
	sbp::SaveSBSet();
	//閉じる
	Close();
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
void __fastcall TSettingForm::CancelBtnClick(TObject *Sender)
{
	//閉じる
	Close();
}

//-------------------------------------------------------------
//  機能     ：テンプレートファイルを使用するをチェック時
//
//  関数定義 ：void __fastcall UseTemplateCBoxClick(TObject *Sender)
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
void __fastcall TSettingForm::UseTemplateCBoxClick(TObject *Sender)
{
	if(UseTemplateCBox->Checked == true)
	{
		TemplateFileEdit->ReadOnly = false;
		TemplateFileEdit->Color    = clWindow;
		FIB_01          ->Enabled  = true;
	}
	else
	{
		TemplateFileEdit->ReadOnly = true;
		TemplateFileEdit->Color    = clSilver;
		FIB_01          ->Enabled  = false;
	}
}

//-------------------------------------------------------------
//  機能     ：テンプレートファイル参照ボタン
//
//  関数定義 ：void __fastcall FIB_01Click(TObject *Sender)
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
void __fastcall TSettingForm::FIB_01Click(TObject *Sender)
{
	//参照ダイアログを開く
	if(OpenDialog->Execute() == true)
	{
		//ファイルパスをセット
		TemplateFileEdit->Text = OpenDialog->FileName;
	}
}
//-------------------------------------------------------------
//  機能     ：入力の抑制(0,1,2のみ)
//
//  関数定義 ：void __fastcall RatioCNumEditKeyPress(TObject *Sender,char &Key)
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
//---------------------------------------------------------------------------
void __fastcall TSettingForm::RatioCNumEditKeyPress(TObject *Sender,
      char &Key)
{
	//Enterは入力不可
	if(Key == '\r')Key = 0;
	//入力可能文字をﾁｪｯｸ
	if(Key < ' ' ||  (Key >= '0' && Key <= '2'))return;
	//入力できない文字は捨てる
	Key = 0;
}
//---------------------------------------------------------------------------

