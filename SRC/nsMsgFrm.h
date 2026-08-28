//---------------------------------------------------------------------------
#ifndef nsMsgFrmH
#define nsMsgFrmH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.TitleBarCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include "BitBtn2.h"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TnsMsgForm : public TForm
{
__published:	// IDE で管理されるコンポーネント
	TTitleBarPanel *TitleBarPanel;
	TSpeedButton *MsgIconSpBtn;
	TImageList *MsgIconImageList;
	TMemo *MessageArea;
	TPanel *BottomPanel;
	TPanel *BottomRightPanel;
	TBitBtn2 *R1Btn;
	TBitBtn2 *R2Btn;
	TBitBtn2 *R3Btn;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall R1BtnClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall R2BtnClick(TObject *Sender);
	void __fastcall R3BtnClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall R1BtnKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall R1BtnKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);
private:
	mbsel   sel;
	msgMode mode;
	std::unique_ptr<TStringList> strs;
private:
	//画面の大きさ等を設定
	bool setSize();
public:
	__fastcall TnsMsgForm(TComponent* Owner);
public:
	//ｴﾗｰﾀﾞｲｱﾛｸﾞ
	void  ErrMsgBox(const char *MsgStr);
	void  ErrMsgBox(const wchar_t *MsgStr);
	//警告ﾀﾞｲｱﾛｸﾞを表示
	void  ExcMsgBox(const char *MsgStr);
	void  ExcMsgBox(const wchar_t *MsgStr);
	//ｲﾝﾌｫﾒｰｼｮﾝﾀﾞｲｱﾛｸﾞ
	void  InfMsgBox(const char *MsgStr);
	void  InfMsgBox(const wchar_t *MsgStr);
	//YesNoﾀﾞｲｱﾛｸﾞ(通常)
	mbsel YesNoMsgBox(const char *MsgStr);
	mbsel YesNoMsgBox(const wchar_t *MsgStr);
	//YesNoﾀﾞｲｱﾛｸﾞを表示(警告)
	mbsel YesNoExcMsgBox(const char *MsgStr);
	mbsel YesNoExcMsgBox(const wchar_t *MsgStr);
	//YesNoｷｬﾝｾﾙﾀﾞｲｱﾛｸﾞを表示
	mbsel YesNoCancelMsgBox(const char *MsgStr);
	mbsel YesNoCancelMsgBox(const wchar_t *MsgStr);
};
//---------------------------------------------------------------------------
extern PACKAGE TnsMsgForm *nsMsgForm;
//---------------------------------------------------------------------------
#endif
