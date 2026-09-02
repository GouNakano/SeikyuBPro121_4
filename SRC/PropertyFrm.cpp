//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "zbWindowDef.h"
#include "MainFrm.h"
#include "PropertyFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TBaseEdit"
#pragma link "BitBtn2"
#pragma resource "*.dfm"
TPropertyForm *PropertyForm;
//---------------------------------------------------------------------------
__fastcall TPropertyForm::TPropertyForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
//フォーム作成時
//---------------------------------------------------------------------------
void __fastcall TPropertyForm::FormCreate(TObject *Sender)
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
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TPropertyForm::FormShow(TObject *Sender)
{
	String Str;
	//--- 部品情報表示 ---
	NameLabel ->Caption = pDoc.Name;
	XEdit     ->Text    = Str.sprintf(L"%.2Lf",pDoc.X);
	YEdit     ->Text    = Str.sprintf(L"%.2Lf",pDoc.Y);
	WidthEdit ->Text    = Str.sprintf(L"%.2Lf",pDoc.Width);
	HeightEdit->Text    = Str.sprintf(L"%.2Lf",pDoc.Height);
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
void __fastcall TPropertyForm::FormatBtnClick(TObject *Sender)
{
	//データセット
	pDoc.X      = _wtold(XEdit     ->Text.c_str());
	pDoc.Y      = _wtold(YEdit     ->Text.c_str());
	pDoc.Width  = _wtold(WidthEdit ->Text.c_str());
	pDoc.Height = _wtold(HeightEdit->Text.c_str());
	//書類部品情報からコンポーネントを配置
	MainForm->SetComponentFromDocCompo(pDoc);
	//閉じる
	Close();
}
//---------------------------------------------------------------------------

