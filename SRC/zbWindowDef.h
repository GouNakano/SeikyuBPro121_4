//---------------------------------------------------------------------------
#ifndef zbWindowDefH
#define zbWindowDefH
#include "BitBtn2.h"
#include "SpeedButton2.h"
//#include "SeikyuBConst.h"
//---------------------------------------------------------------------------
class zbWindowDef
{
public:
	//タイトルバーに標準色を設定する
	static bool setStdTitlebarColor(TForm *form);
	//目標パネルを用いたウィンドウの大きさ設定
	static bool setWindowSizeFromMark(TForm *frm,const String& markName);
	//青系標準BitBtn2の設定
	static bool setStdBlueBitBtn2(TBitBtn2 *btn);
	//赤系標準BitBtn2の設定
	static bool setStdRedBitBtn2(TBitBtn2 *btn);
	//緑系標準BitBtn2の設定
	static bool setStdGreenBitBtn2(TBitBtn2 *btn);
	//青系標準SpeedButton2の設定
	static bool setStdBlueSpeedButton2(TSpeedButton2 *btn);
public:
	//ﾀﾞｲｱﾛｸﾞのﾀｲﾄﾙ設定
	static void  SetMsgBoxTitle(const String& title);
	//ｴﾗｰﾀﾞｲｱﾛｸﾞ
	static void  ErrMsgBox(HWND Handle,const wchar_t *Msg,...);
	//警告ﾀﾞｲｱﾛｸﾞを表示
	static void  ExcMsgBox(HWND Handle,const wchar_t *Msg,...);
	//ｲﾝﾌｫﾒｰｼｮﾝﾀﾞｲｱﾛｸﾞ
	static void  InfMsgBox(HWND Handle,const wchar_t *Msg,...);
	//YesNoﾀﾞｲｱﾛｸﾞ(通常)
	static mbsel YesNoMsgBox(HWND Handle,const wchar_t *Msg,...);
	//YesNoﾀﾞｲｱﾛｸﾞを表示(警告)
	static mbsel YesNoExcMsgBox(HWND Handle,const wchar_t *Msg,...);
	//YesNoｷｬﾝｾﾙﾀﾞｲｱﾛｸﾞを表示
	static mbsel YesNoCancelMsgBox(HWND Handle,const wchar_t *Msg,...);
};

#endif
