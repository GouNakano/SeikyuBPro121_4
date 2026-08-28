//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SeikyuBConst.h"
#include "nsMsgFrm.h"
#include "MainFrm.h"
#include "zbWindowDef.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
//タイトルバーに標準色を設定する
//---------------------------------------------------------------------------
bool zbWindowDef::setStdTitlebarColor(TForm *form)
{
	form->CustomTitleBar->SystemButtons = false;
	form->CustomTitleBar->SystemColors  = false;
	form->CustomTitleBar->SystemHeight  = false;
	form->CustomTitleBar->Height        = STD_TITLEBAR_HEIGHT;

	form->CustomTitleBar->BackgroundColor               = STD_TITLEBAR_BACKGROUNDCOLOR;
	form->CustomTitleBar->ButtonBackgroundColor         = STD_TITLEBAR_BACKGROUNDCOLOR;
	form->CustomTitleBar->ButtonForegroundColor         = STD_TITLEBAR_FOREGROUNDCOLOR;
	form->CustomTitleBar->ButtonHoverBackgroundColor    = (TColor)0x00CE7918;
	form->CustomTitleBar->ForegroundColor               = STD_TITLEBAR_FOREGROUNDCOLOR;
	form->CustomTitleBar->InactiveBackgroundColor       = STD_TITLEBAR_INACTIVE_BACKGROUNDCOLOR;
	form->CustomTitleBar->ButtonInactiveBackgroundColor = STD_TITLEBAR_INACTIVE_BACKGROUNDCOLOR;
	form->CustomTitleBar->InactiveForegroundColor       = STD_TITLEBAR_INACTIVE_FOREGROUNDCOLOR;
	form->CustomTitleBar->SystemButtons                 = false;
	form->CustomTitleBar->SystemColors                  = false;
	form->CustomTitleBar->SystemHeight                  = false;
	form->CustomTitleBar->Height                        = STD_TITLEBAR_HEIGHT;

	return true;
}
//---------------------------------------------------------------------------
//目標パネルを用いたウィンドウの大きさ設定
//---------------------------------------------------------------------------
bool zbWindowDef::setWindowSizeFromMark(TForm *frm,const String& markName)
{
	TComponent *comp = frm->FindComponent(markName);
	if(comp != nullptr)
	{
		TControl *mark = dynamic_cast<TControl *>(comp);

		if(mark != nullptr)
		{
			frm->ClientWidth  = mark->Left;
			frm->ClientHeight = mark->Top;
			mark->Visible = false;
		}
	}
	return true;
}
//---------------------------------------------------------------------------
//青系標準BitBtn2の設定
//---------------------------------------------------------------------------
bool zbWindowDef::setStdBlueBitBtn2(TBitBtn2 *btn)
{
	//青系ボタンのフォント名
	btn->Font->Name  = STD_BLUE_BUTTON_FONTNAME;
	//青系ボタンのフォント色
	btn->Font->Color = STD_BLUE_BUTTON_FONT_COLOR;
	//青系ボタンの色
	btn->Color = STD_BLUE_BUTTON_COLOR;
	//青系ボタンマウスポインタがボタンの上にある時の色
	btn->MouseEnterColor = STD_BLUE_BUTTON_MOUSE_ENTER_COLOR;
	//青系ボタンマウスダウン時の色
	btn->DownColor = STD_BLUE_BUTTON_MOUSE_DOWN_COLOR;
	//青系ボタン境界色
	btn->BorderColor = STD_BLUE_BUTTON_BORDER_COLOR;
	// //青系ボタン使用不可時のフォントの色
	btn->DisableFontColor = STD_BLUE_BUTTON_DISABLE_FONT_COLOR;

	return true;
}
//---------------------------------------------------------------------------
//赤系標準BitBtn2の設定
//---------------------------------------------------------------------------
bool zbWindowDef::setStdRedBitBtn2(TBitBtn2 *btn)
{
	//赤系ボタンのフォント名
	btn->Font->Name  = STD_RED_BUTTON_FONTNAME;
	//赤系ボタンのフォント色
	btn->Font->Color = STD_RED_BUTTON_FONT_COLOR;
	//赤系ボタンの色
	btn->Color = STD_RED_BUTTON_COLOR;
	//赤系ボタンマウスポインタがボタンの上にある時の色
	btn->MouseEnterColor = STD_RED_BUTTON_MOUSE_ENTER_COLOR;
	//赤系ボタンマウスダウン時の色
	btn->DownColor = STD_RED_BUTTON_MOUSE_DOWN_COLOR;
	//赤系ボタン境界色
	btn->BorderColor = STD_RED_BUTTON_BORDER_COLOR;
	// //赤系ボタン使用不可時のフォントの色
	btn->DisableFontColor = STD_RED_BUTTON_DISABLE_FONT_COLOR;

	return true;
}
//---------------------------------------------------------------------------
//緑系標準BitBtn2の設定
//---------------------------------------------------------------------------
bool zbWindowDef::setStdGreenBitBtn2(TBitBtn2 *btn)
{
	//緑系ボタンのフォント名
	btn->Font->Name  = STD_GREEN_BUTTON_FONTNAME;
	//緑系ボタンのフォント色
	btn->Font->Color = STD_GREEN_BUTTON_FONT_COLOR;
	//緑系ボタンの色
	btn->Color = STD_GREEN_BUTTON_COLOR;
	//緑系ボタンマウスポインタがボタンの上にある時の色
	btn->MouseEnterColor = STD_GREEN_BUTTON_MOUSE_ENTER_COLOR;
	//緑系ボタンマウスダウン時の色
	btn->DownColor = STD_GREEN_BUTTON_MOUSE_DOWN_COLOR;
	//緑系ボタン境界色
	btn->BorderColor = STD_GREEN_BUTTON_BORDER_COLOR;
	// //緑系ボタン使用不可時のフォントの色
	btn->DisableFontColor = STD_GREEN_BUTTON_DISABLE_FONT_COLOR;

	return true;
}
//---------------------------------------------------------------------------
//青系標準SpeedButton2の設定
//---------------------------------------------------------------------------
bool zbWindowDef::setStdBlueSpeedButton2(TSpeedButton2 *btn)
{
	//青系ボタンのフォント名
	btn->Font->Name  = STD_BLUE_BUTTON_FONTNAME;
	//青系ボタンのフォント色
	btn->Font->Color = STD_BLUE_SPEEDBUTTON_FONT_COLOR;
	//青系ボタンの色
	btn->Color = STD_BLUE_SPEEDBUTTON_COLOR;
	//青系ボタンダウン時の色
	btn->DownColor = STD_BLUE_SPEEDBUTTON_DOWN_COLOR;
	//青系ボタンマウスポインタがボタンの上にある時の色
	btn->MouseEnterColor = STD_BLUE_SPEEDBUTTON_MOUSE_ENTER_COLOR;
	//青系ボタンマウスダウン時の色
	btn->MouseDownColor = STD_BLUE_SPEEDBUTTON_MOUSE_DOWN_COLOR;
	//青系ボタン使用不可時のフォントの色
	btn->DisableFontColor = STD_BLUE_SPEEDBUTTON_DISABLE_FONT_COLOR;
	//青系ボタン境界色
	btn->BorderColor = STD_BLUE_SPEEDBUTTON_BORDER_COLOR;
	//青系ボタンDown時境界色
	btn->DownBorderColor = STD_BLUE_SPEEDBUTTON_DOWN_BORDER_COLOR;
	//青系ボタンダウン時のフォントの色
	btn->DownFontColor = STD_BLUE_SPEEDBUTTON_DOWN_FONT_COLOR;

	return true;
}
//---------------------------------------------------------------------------
//ｴﾗｰﾀﾞｲｱﾛｸﾞ
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//ﾀﾞｲｱﾛｸﾞのﾀｲﾄﾙ設定
//---------------------------------------------------------------------------
void  zbWindowDef::SetMsgBoxTitle(const String& title)
{
	//ダイアログキャプション設定
	nsMsgForm->Caption = title;
}
// -------------------------------------------------------------
// 機能     ：ｴﾗｰﾀﾞｲｱﾛｸﾞを表示
//
// 関数定義 ：void  ErrMsgBox(HWND Handle,const char *Msg,...)
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
void zbWindowDef::ErrMsgBox(HWND Handle, const wchar_t *Msg, ...)
{
	wchar_t MsgStr[512];
	va_list ap;
	// ﾒｯｾｰｼﾞ組み立て
	va_start(ap, Msg);
	vswprintf(MsgStr, Msg, ap);
	va_end(ap);
	//ダイアログ表示
	nsMsgForm->ErrMsgBox(MsgStr);
}
// -------------------------------------------------------------
// 機能     ：警告ﾀﾞｲｱﾛｸﾞを表示
//
// 関数定義 ：void ExcMsgBox(HWND Handle,const wchar_t *Msg,...)
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
void  zbWindowDef::ExcMsgBox(HWND Handle,const wchar_t *Msg,...)
{
	wchar_t MsgStr[512];
	va_list ap;
	// ﾒｯｾｰｼﾞ組み立て
	va_start(ap, Msg);
	vswprintf(MsgStr, Msg, ap);
	va_end(ap);
	//ダイアログ表示
	nsMsgForm->ExcMsgBox(MsgStr);

}
// -------------------------------------------------------------
// 機能     ：ｲﾝﾌｫﾒｰｼｮﾝﾀﾞｲｱﾛｸﾞを表示
//
// 関数定義 ：void ExcMsgBox(HWND Handle,const char *Msg,...)
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
void  zbWindowDef::InfMsgBox(HWND Handle,const wchar_t *Msg,...)
{
	wchar_t MsgStr[512];
	va_list ap;
	// ﾒｯｾｰｼﾞ組み立て
	va_start(ap, Msg);
	vswprintf(MsgStr, Msg, ap);
	va_end(ap);
	//ダイアログ表示
	nsMsgForm->InfMsgBox(MsgStr);
}
// -------------------------------------------------------------
// 機能     ：YesNoﾀﾞｲｱﾛｸﾞを表示(情報)
//
// 関数定義 ：void YesNoMsgBox(HWND Handle,const wchar_t *Msg,...)
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
mbsel zbWindowDef::YesNoMsgBox(HWND Handle,const wchar_t *Msg,...)
{
	mbsel   sel;
	wchar_t MsgStr[512];
	va_list ap;
	// ﾒｯｾｰｼﾞ組み立て
	va_start(ap, Msg);
	vswprintf(MsgStr, Msg, ap);
	va_end(ap);
	//ダイアログ表示
	sel = nsMsgForm->YesNoMsgBox(MsgStr);

	return sel;
}
//-------------------------------------------------------------
// 機能     ：YesNoﾀﾞｲｱﾛｸﾞを表示(警告)
//
// 関数定義 ：void YesNoExcMsgBox(HWND Handle,const wchar_t *Msg,...)
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
//-------------------------------------------------------------
mbsel zbWindowDef::YesNoExcMsgBox(HWND Handle,const wchar_t *Msg,...)
{
	mbsel   sel;
	wchar_t MsgStr[512];
	va_list ap;
	// ﾒｯｾｰｼﾞ組み立て
	va_start(ap, Msg);
	vswprintf(MsgStr, Msg, ap);
	va_end(ap);
	//ダイアログ表示
	sel = nsMsgForm->YesNoExcMsgBox(MsgStr);

	return sel;
}
// -------------------------------------------------------------
// 機能     ：YesNoｷｬﾝｾﾙﾀﾞｲｱﾛｸﾞを表示
//
// 関数定義 ：void YesNoCancelMsgBox(HWND Handle,const wchar_t *Msg,...)
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
mbsel zbWindowDef::YesNoCancelMsgBox(HWND Handle,const wchar_t *Msg,...)
{
	mbsel   sel;
	wchar_t MsgStr[512];
	va_list ap;
	// ﾒｯｾｰｼﾞ組み立て
	va_start(ap, Msg);
	vswprintf(MsgStr, Msg, ap);
	va_end(ap);
	//ダイアログ表示
	sel = nsMsgForm->YesNoCancelMsgBox(MsgStr);

	return sel;
}

