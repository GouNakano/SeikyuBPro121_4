//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SeikyuBDef.h"
#include "zbWindowDef.h"
#include "FirstMesFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "BitBtn2"
#pragma resource "*.dfm"
TFirstMesForm *FirstMesForm;
//---------------------------------------------------------------------------
__fastcall TFirstMesForm::TFirstMesForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
//フォーム作成時
//---------------------------------------------------------------------------
void __fastcall TFirstMesForm::FormCreate(TObject *Sender)
{
	//タイトルバーに標準色を設定する
	zbWindowDef::setStdTitlebarColor(this);
}
//---------------------------------------------------------------------------
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
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TFirstMesForm::FormClose(TObject *Sender,TCloseAction &Action)
{
	//初回起動フラグ
	bool IsFirst = (NextCheckBox->Checked == false);
	//初回起動か？
	regsp::setIsFirstUse((IsFirst == true));
}
//---------------------------------------------------------------------------

