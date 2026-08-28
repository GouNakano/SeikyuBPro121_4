//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SeikyuBConst.h"
#include "zbControlDef.h"
#include "zbWindowDef.h"
#include "nsMsgFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "BitBtn2"
#pragma resource "*.dfm"
TnsMsgForm *nsMsgForm;
//---------------------------------------------------------------------------
__fastcall TnsMsgForm::TnsMsgForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
//ﾌｫｰﾑ作成時
//---------------------------------------------------------------------------
void __fastcall TnsMsgForm::FormCreate(TObject *Sender)
{
	//タイトルバーに標準色を設定する
	zbWindowDef::setStdTitlebarColor(this);
	//色設定
	zbControlDef::setWindowParam(this);
	zbControlDef::setPanelParam(BottomPanel);
	//文字列リスト
	strs.reset(new TStringList);
}
//---------------------------------------------------------------------------
//ﾌｫｰﾑ表示時
//---------------------------------------------------------------------------
void __fastcall TnsMsgForm::FormShow(TObject *Sender)
{
	//画面の大きさ等を設定
	setSize();
	//フォーカス設定
	R1Btn->SetFocus();
}
//---------------------------------------------------------------------------
//ﾌｫｰﾑを閉じるとき
//---------------------------------------------------------------------------
void __fastcall TnsMsgForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	R1Btn->Visible = true;
	R2Btn->Visible = true;
	R3Btn->Visible = true;
}
//---------------------------------------------------------------------------
//キー押下時
//---------------------------------------------------------------------------
void __fastcall TnsMsgForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == VK_ESCAPE)
	{
		Close();
		Key = 0;
	}
	else if(Key == VK_LEFT)
	{
		if(ActiveControl == R1Btn)
		{
			R2Btn->SetFocus();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TnsMsgForm::FormKeyPress(TObject *Sender, System::WideChar &Key)
{
//
}
//---------------------------------------------------------------------------
//画面の大きさ等を設定
//---------------------------------------------------------------------------
bool TnsMsgForm::setSize()
{
	TStrings *lines = strs.get();
	int w;
	int h;
	//最大幅と合計高さを得る
	int    maxW = 0;
	int    sumH = 0;
	String lstr;
	for(int ln = 0;ln < strs->Count;ln++)
	{
		lstr = strs->Strings[ln];

		int sw = Canvas->TextWidth(lstr) + 50;
		int sh = Canvas->TextHeight(lstr);

		maxW  = (sw > maxW?sw:maxW);
		sumH += sh;
	}
	//幅
	w = maxW;
	//高さ
	h = sumH;
	//大きさ補正
	w = (w < 200?200:w);
	h = (h <  30?30:h);
	//メッセージエリアの大きさ設定
	MessageArea->Width  = w;
	MessageArea->Height = h;
	//ウィンドウの大きさ設定
	ClientWidth  = 80 + w;
	ClientHeight = 120 + h;
	//メッセージエリアに文字列設定
	MessageArea->Lines->Clear();
	for(int ln = 0;ln < strs->Count;ln++)
	{
		MessageArea->Lines->Add(strs->Strings[ln]);
	}
	return true;
}
//---------------------------------------------------------------------------
//R1ボタン
//---------------------------------------------------------------------------
void __fastcall TnsMsgForm::R1BtnClick(TObject *Sender)
{
	if(mode == mmYesNo)
	{
		sel = mbselNO;
	}
	else if(mode == mmYesNoCancel)
	{
		sel = mbselCancel;
	}
	Close();
}
//---------------------------------------------------------------------------
//R2ボタン
//---------------------------------------------------------------------------
void __fastcall TnsMsgForm::R2BtnClick(TObject *Sender)
{
	if(mode == mmYesNo)
	{
		sel = mbselYES;
	}
	else if(mode == mmYesNoCancel)
	{
		sel = mbselNO;
	}
	Close();
}
//---------------------------------------------------------------------------
//R3ボタン
//---------------------------------------------------------------------------
void __fastcall TnsMsgForm::R3BtnClick(TObject *Sender)
{
	if(mode == mmYesNoCancel)
	{
		sel = mbselYES;
	}
	Close();
}
//---------------------------------------------------------------------------
//R1ボタンキーダウン
//---------------------------------------------------------------------------
void __fastcall TnsMsgForm::R1BtnKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == VK_LEFT)
	{
		R2Btn->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall TnsMsgForm::R1BtnKeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key == VK_LEFT)
	{
		R2Btn->SetFocus();
	}
}
// -------------------------------------------------------------
// 機能     ：ｴﾗｰﾀﾞｲｱﾛｸﾞを表示
//
// 関数定義 ：void  ErrMsgBox(const char *MsgStr)
//
// ｱｸｾｽﾚﾍﾞﾙ ：
//
// 引数     ：
//
// 戻り値   ：
//
// 作成者　 ：
//
// 改定者   ：
// -------------------------------------------------------------
void TnsMsgForm::ErrMsgBox(const char *MsgStr)
{
	//ダイアログモード
	mode = mmOk;
	//エラーアイコン
	MsgIconSpBtn->ImageIndex = 0;
	MsgIconSpBtn->DisabledImageIndex = 0;
	//ボタン設定
	R1Btn->Caption = L"OK";
	R2Btn->Visible = false;
	R3Btn->Visible = false;
	//ﾒｯｾｰｼﾞﾎﾞｯｸｽ設定
	MessageArea->Text = MsgStr;
	//表示
	ShowModal();
}

void TnsMsgForm::ErrMsgBox(const wchar_t *MsgStr)
{
	//ダイアログモード
	mode = mmOk;
	//エラーアイコン
	MsgIconSpBtn->ImageIndex = 0;
	MsgIconSpBtn->DisabledImageIndex = 0;
	//ボタン設定
	R1Btn->Caption = L"OK";
	R2Btn->Visible = false;
	R3Btn->Visible = false;
	//改行分解
	strs->Text = MsgStr;
	//表示
	ShowModal();
}
// -------------------------------------------------------------
// 機能     ：警告ﾀﾞｲｱﾛｸﾞを表示
//
// 関数定義 ：void  ExcMsgBox(const char *MsgStr)
//
// ｱｸｾｽﾚﾍﾞﾙ ：
//
// 引数     ：
//
// 戻り値   ：
//
// 作成者　 ：
//
// 改定者   ：
// -------------------------------------------------------------
void TnsMsgForm::ExcMsgBox(const char *MsgStr)
{
	//ダイアログモード
	mode = mmOk;
	//警告アイコン
	MsgIconSpBtn->ImageIndex = 2;
	MsgIconSpBtn->DisabledImageIndex = 2;
	//ボタン設定
	R1Btn->Caption = L"OK";
	R2Btn->Visible = false;
	R3Btn->Visible = false;
	//改行分解
	strs->Text = MsgStr;
	//表示
	ShowModal();
}

void TnsMsgForm::ExcMsgBox(const wchar_t *MsgStr)
{
	//ダイアログモード
	mode = mmOk;
	//警告アイコン
	MsgIconSpBtn->ImageIndex = 2;
	MsgIconSpBtn->DisabledImageIndex = 2;
	//ボタン設定
	R1Btn->Caption = L"OK";
	R2Btn->Visible = false;
	R3Btn->Visible = false;
	//改行分解
	strs->Text = MsgStr;
	//表示
	ShowModal();
}
// -------------------------------------------------------------
// 機能     ：ｲﾝﾌｫﾒｰｼｮﾝﾀﾞｲｱﾛｸﾞを表示
//
// 関数定義 ：void  InfMsgBox(const char *MsgStr)
//
// ｱｸｾｽﾚﾍﾞﾙ ：
//
// 引数     ：
//
// 戻り値   ：
//
// 作成者　 ：
//
// 改定者   ：
// -------------------------------------------------------------
void TnsMsgForm::InfMsgBox(const char *MsgStr)
{
	//ダイアログモード
	mode = mmOk;
	//警告アイコン
	MsgIconSpBtn->ImageIndex = 1;
	MsgIconSpBtn->DisabledImageIndex = 1;
	//ボタン設定
	R1Btn->Caption = L"OK";
	R2Btn->Visible = false;
	R3Btn->Visible = false;
	//改行分解
	strs->Text = MsgStr;
	//表示
	ShowModal();
}

void TnsMsgForm::InfMsgBox(const wchar_t *MsgStr)
{
	//ダイアログモード
	mode = mmOk;
	//警告アイコン
	MsgIconSpBtn->ImageIndex = 1;
	MsgIconSpBtn->DisabledImageIndex = 1;
	//ダイアログモード
	mode = mmOk;
	//ボタン設定
	R1Btn->Caption = L"OK";
	R2Btn->Visible = false;
	R3Btn->Visible = false;
	//改行分解
	strs->Text = MsgStr;
	//表示
	ShowModal();
}
// -------------------------------------------------------------
// 機能     ：YesNoﾀﾞｲｱﾛｸﾞを表示(通常)
//
// 関数定義 ：mbsel YesNoMsgBox(const char *MsgStr)
//
// ｱｸｾｽﾚﾍﾞﾙ ：
//
// 引数     ：
//
// 戻り値   ：
//
// 作成者　 ：
//
// 改定者   ：
// -------------------------------------------------------------
mbsel TnsMsgForm::YesNoMsgBox(const char *MsgStr)
{
	//ダイアログモード
	mode = mmYesNo;
	sel  = mbselNO;
	//Infoアイコン
	MsgIconSpBtn->ImageIndex = 1;
	MsgIconSpBtn->DisabledImageIndex = 1;
	//ボタン設定
	R1Btn->Caption = L"いいえ";
	R2Btn->Caption = L"はい";
	R3Btn->Visible = false;
	//ﾒｯｾｰｼﾞﾎﾞｯｸｽ設定
	MessageArea->Text = MsgStr;
	//表示
	ShowModal();

	return sel;
}

mbsel TnsMsgForm::YesNoMsgBox(const wchar_t *MsgStr)
{
	//ダイアログモード
	mode = mmYesNo;
	sel  = mbselNO;
	//Infoアイコン
	MsgIconSpBtn->ImageIndex = 1;
	MsgIconSpBtn->DisabledImageIndex = 1;
	//ボタン設定
	R1Btn->Caption = L"いいえ";
	R2Btn->Caption = L"はい";
	R3Btn->Visible = false;
	//改行分解
	strs->Text = MsgStr;
	//表示
	ShowModal();

	return sel;
}
// -------------------------------------------------------------
// 機能     ：YesNoﾀﾞｲｱﾛｸﾞを表示(警告)
//
// 関数定義 ：mbsel YesNoExcMsgBox(const char *MsgStr)
//
// ｱｸｾｽﾚﾍﾞﾙ ：
//
// 引数     ：
//
// 戻り値   ：
//
// 作成者　 ：
//
// 改定者   ：
// -------------------------------------------------------------
mbsel TnsMsgForm::YesNoExcMsgBox(const char *MsgStr)
{
	//ダイアログモード
	mode = mmYesNo;
	sel  = mbselCancel;
	//警告アイコン
	MsgIconSpBtn->ImageIndex = 2;
	MsgIconSpBtn->DisabledImageIndex = 2;
	//ボタン設定
	R1Btn->Caption = L"いいえ";
	R2Btn->Caption = L"はい";
	R3Btn->Visible = false;
	//ﾒｯｾｰｼﾞﾎﾞｯｸｽ設定
	MessageArea->Text = MsgStr;
	//表示
	ShowModal();

	return sel;
}

mbsel TnsMsgForm::YesNoExcMsgBox(const wchar_t *MsgStr)
{
	//ダイアログモード
	mode = mmYesNo;
	sel  = mbselCancel;
	//警告アイコン
	MsgIconSpBtn->ImageIndex = 2;
	MsgIconSpBtn->DisabledImageIndex = 2;
	//ボタン設定
	R1Btn->Caption = L"いいえ";
	R2Btn->Caption = L"はい";
	R3Btn->Visible = false;
	//改行分解
	strs->Text = MsgStr;
	//表示
	ShowModal();

	return sel;
}
// -------------------------------------------------------------
// 機能     ：YesNoｷｬﾝｾﾙﾀﾞｲｱﾛｸﾞを表示
//
// 関数定義 ：mbsel YesNoCancelMsgBox(const char *MsgStr)
//
// ｱｸｾｽﾚﾍﾞﾙ ：
//
// 引数     ：
//
// 戻り値   ：
//
// 作成者　 ：
//
// 改定者   ：
// -------------------------------------------------------------
mbsel TnsMsgForm::YesNoCancelMsgBox(const char *MsgStr)
{
	mode = mmYesNoCancel;
	sel  = mbselCancel;
	//ボタン設定
	R1Btn->Caption = L"ｷｬﾝｾﾙ";
	R2Btn->Caption = L"いいえ";
	R3Btn->Caption = L"はい";
	//改行分解
	strs->Text = MsgStr;
	//表示
	ShowModal();

	return sel;
}

mbsel TnsMsgForm::YesNoCancelMsgBox(const wchar_t *MsgStr)
{
	//ダイアログモード
	mode = mmYesNoCancel;
	sel  = mbselCancel;
	//ボタン設定
	R1Btn->Caption = L"ｷｬﾝｾﾙ";
	R2Btn->Caption = L"いいえ";
	R3Btn->Caption = L"はい";
	//改行分解
	strs->Text = MsgStr;
	//表示
	ShowModal();

	return sel;
}
//---------------------------------------------------------------------------

