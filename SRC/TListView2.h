//---------------------------------------------------------------------------
#ifndef TListView2H
#define TListView2H
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
//---------------------------------------------------------------------------
class PACKAGE TListView2 : public TListView
{
protected:
	//通知のウィンドウメッセージ
	void __fastcall WMNotify(TMessage& Msg);
	//左ボタンクリック
	void __fastcall WMLButtonDown(TWMLButtonDown &Message);
	//ダブルクリック時
	void __fastcall WMLButtonDblClk(TWMLButtonDblClk &Message);

	BEGIN_MESSAGE_MAP
		MESSAGE_HANDLER(WM_NOTIFY,TMessage,WMNotify)
		VCL_MESSAGE_HANDLER(WM_LBUTTONDOWN, TWMLButtonDown, WMLButtonDown)
		VCL_MESSAGE_HANDLER(WM_LBUTTONDBLCLK, TWMLButtonDblClk, WMLButtonDblClk)
	END_MESSAGE_MAP(TListView)

protected:
	TColor FDisableFontColor;
	TColor FHeaderColor;
protected:
	//Windows コントロールを作成します
	void __fastcall CreateWnd();
	//使用不可時のフォントの色
	void __fastcall SetDisableFontColor(TColor col);
	//ヘッダーの背景色
	void __fastcall SetHeaderColor(TColor Value);
public:
	__fastcall TListView2(TComponent* Owner);
__published:
	__property TColor DisableFontColor = {read=FDisableFontColor,write=SetDisableFontColor ,default=clGray};
	__property TColor HeaderColor      = {read=FHeaderColor     , write=SetHeaderColor };
};
//---------------------------------------------------------------------------
#endif
