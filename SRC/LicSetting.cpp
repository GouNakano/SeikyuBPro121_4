//---------------------------------------------------------------------------
#include <vcl.h>
#include <Clipbrd.hpp>
#pragma hdrstop

#include <mapi.h>
#include "strconv.h"
#include "TLicense.h"
#include "nsSendMail.h"
#include "nsMsgBox.h"
#include "nsShellApi.h"
#include "SeikyuBDef.h"
#include "zbWindowDef.h"
#include "LicSetting.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TBaseEdit"
#pragma link "TBaseMemo"
#pragma link "BitBtn2"
#pragma resource "*.dfm"
TLicSettingForm *LicSettingForm;
//---------------------------------------------------------------------------
__fastcall TLicSettingForm::TLicSettingForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
//フォーム作成時
//---------------------------------------------------------------------------
void __fastcall TLicSettingForm::FormCreate(TObject *Sender)
{
	//タイトルバーに標準色を設定する
	zbWindowDef::setStdTitlebarColor(this);
}
//-------------------------------------------------------------
//  機能     ：フォームが表示された時
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
void __fastcall TLicSettingForm::FormShow(TObject *Sender)
{
	//タブは表示しない
	for(int Cnt = 0;Cnt < PageControl->PageCount;Cnt++)
	{
		PageControl->Pages[Cnt]->TabVisible = false;
	}
	//アクティブシート
	PageControl->ActivePage = MainSheet;
}
//-------------------------------------------------------------
//  機能     ：ライセンス注文ボタン
//
//  関数定義 ：void __fastcall LicTimerTimer(TObject *Sender)
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
void __fastcall TLicSettingForm::LicOrderBtnClick(TObject *Sender)
{
	//ライセンス注文フォーム表示
	PageControl->ActivePage = LicOrderSheet;
}
//-------------------------------------------------------------
//  機能     ：メール送信
//
//  関数定義 ：bool TLicSettingForm::sendMail(String mailText)
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
bool TLicSettingForm::sendMail()
{

	std::string subj = wide_to_ansi(SubjectEdit->Text.c_str());
	std::string body = wide_to_ansi(MailTextMemo->Lines->Text.c_str());

	TMailData MailData;
	//送信メールのデータセット
	MailData.ToName      = L"さくら電算";
	MailData.ToAddress   = L"sakura-densan <reception_desk@sakura-densan.com>";
	MailData.CCName      = "";
	MailData.CCAddress   = "";
	MailData.BCCName     = "";
	MailData.BCCAddress  = "";
	MailData.FromName    = "";
	MailData.FromAddress = "";
	MailData.SubjectStr  = subj;
	MailData.DataStr     = body;
	MailData.fDialog     = true;
	//メールを送信する
//	if(nsSendMail(MailData) == false)
	if(MailData.send() == false)
	{
		return false;
	}
	return true;
}
//-------------------------------------------------------------
//  機能     ：注文フォームの「進む」ボタン
//
//  関数定義 ：bool LicNextBtnClick(TObject *Sender)
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
void __fastcall TLicSettingForm::LicNextBtnClick(TObject *Sender)
{
	const wchar_t *pLicStr =
			L"請求書番頭 プロ版 ライセンス注文メール\n\n"
			"お名前：%s\n"
			"メールアドレス：%s\n"
			"郵便番号：%s-%s\n"
			"住所：%s\n"
			"電話番号：%s-%s-%s\n"
			"ライセンス注文キー：%s\n"
			"備考：\n%s\n";

	String MailStr;
	//値取得
	String LName   = NameEdit    ->Text.Trim();
	String Mail    = MailEdit    ->Text.Trim();
	String Yubin1  = Yubin1Edit  ->Text.Trim();
	String Yubin2  = Yubin2Edit  ->Text.Trim();
	String Address = AddressEdit ->Text.Trim();
	String Phone1  = Phone1Edit  ->Text.Trim();
	String Phone2  = Phone2Edit  ->Text.Trim();
	String Phone3  = Phone3Edit  ->Text.Trim();
	String Note    = NoteMeno    ->Lines->Text.Trim();
	//チェック
	if(LName == "")
	{
		nsLib::ErrMsgBox(Handle,"お名前が入力されていません。");
		return;
	}
	if(Mail == "")
	{
		nsLib::ErrMsgBox(Handle,"メールアドレスが入力されていません。");
		return;
	}
	//ライセンス申請文字列
	TLicense license;
	String LicStr = license.getCorrectLicenceString();
	//メールの送信内容組み立て
	MailStr.sprintf(pLicStr,
		LName  .c_str(),
		Mail   .c_str(),
		Yubin1 .c_str(),Yubin2.c_str(),
		Address.c_str(),
		Phone1 .c_str(),Phone2.c_str(),Phone3.c_str(),
		LicStr .c_str(),
		Note   .c_str());
	//メール送信内容セット
	MailTextMemo->Lines->Text = MailStr;
	//送信先のセット
	ToEdit     ->Text = "reception_desk@sakura-densan.com";
	//件名のセット
	SubjectEdit->Text = "ライセンス注文(請求書番頭 プロ版)";
	//メール送信フォーム表示
	PageControl->ActivePage = SendSheet;
}
//-------------------------------------------------------------
//  機能     ：メール送信ボタン
//
//  関数定義 ：bool SendMailBtn(TObject *Sender)
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
void __fastcall TLicSettingForm::SendMailBtnClick(TObject *Sender)
{
	//メールの送信を行う
	if(sendMail() == false)
	{
		nsLib::ErrMsgBox(Handle,"メールの送信に失敗しました。");
		return;
	}
}
//-------------------------------------------------------------
//  機能     ：送信フォームの「戻る」ボタン
//
//  関数定義 ：bool LicNextBtnClick(TObject *Sender)
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
void __fastcall TLicSettingForm::RetBtnClick(TObject *Sender)
{
	//ライセンス注文フォーム表示
	PageControl->ActivePage = LicOrderSheet;
}
//-------------------------------------------------------------
//  機能     ：注文フォームの「戻る」ボタン
//
//  関数定義 ：bool LicPrevBtnClick(TObject *Sender)
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
void __fastcall TLicSettingForm::LicPrevBtnClick(TObject *Sender)
{
	//メインフォーム表示
	PageControl->ActivePage = MainSheet;
}
//-------------------------------------------------------------
//  機能     ：終了ボタン
//
//  関数定義 ：bool EndBtnClick(TObject *Sender)
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
void __fastcall TLicSettingForm::EndBtnClick(TObject *Sender)
{
	Close();
}
//-------------------------------------------------------------
//  機能     ：宛先コピーボタン
//
//  関数定義 ：bool ToCopyBtnClick(TObject *Sender)
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
void __fastcall TLicSettingForm::ToCopyBtnClick(TObject *Sender)
{
	String CopyStr;
	//クリップボードを得る
	TClipboard *pClip = Clipboard();
	//コピーする文字列を得る
	if(Sender == ToCopyBtn)
	{
		CopyStr = ToEdit->Text;
	}
	else if(Sender == SubjectBtn)
	{
		CopyStr = SubjectEdit->Text;
	}
	else if(Sender == MailTextBtn)
	{
		CopyStr = MailTextMemo->Text;
	}
	//コピー
	pClip->AsText = CopyStr;
}
//-------------------------------------------------------------
//  機能     ：ライセンス認証ボタン
//
//  関数定義 ：bool ToCopyBtnClick(TObject *Sender)
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
void __fastcall TLicSettingForm::AuthorizationBtnClick(TObject *Sender)
{
	//メインフォーム表示
	PageControl->ActivePage = AuthorizationSheet;
}
//-------------------------------------------------------------
//  機能     ：ライセンス認証パスワード貼付ボタン
//
//  関数定義 ：bool LicPasteBtnClick(TObject *Sender)
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
void __fastcall TLicSettingForm::LicPasteBtnClick(TObject *Sender)
{
	String CopyStr;
	//クリップボードを得る
	TClipboard *pClip = Clipboard();
	//クリップボードに設定されている文字列
	CopyStr = pClip->AsText.Trim();
	//セット
	if(CopyStr != L"")
	{
		PasswordEdit->Text = CopyStr;
	}
}
//-------------------------------------------------------------
//  機能     ：ライセンス認証実行ボタン
//
//  関数定義 ：bool LicAuthorizationOkBtnClick(TObject *Sender)
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
void __fastcall TLicSettingForm::LicAuthorizationOkBtnClick(TObject *Sender)
{
	wchar_t LicPath[512];
	//入力されたパスワード
	String Passwd = PasswordEdit->Text.Trim();
	//正しいライセンス設定文字列の作成
	TLicense license;
	String LicSet = license.getCorrectLicenceString();
	//比較をする
	if(Passwd != LicSet)
	{
		nsLib::ErrMsgBox(Handle,"入力されたライセンス認証パスワードは正しくありません。\n正しいライセンス認証パスワードを入力してください。");
		return;
	}
	//レジストリ
	std::unique_ptr<SBRegIni> pReg(new SBRegIni);
	//ライセンスパスワード書き込み
	pReg->WriteString(C_SYSTEM_SETTING,LICENSE_STRING,LicSet);
	//ベリファイ文字列
	String chk_lic_str = pReg->ReadString(C_SYSTEM_SETTING,LICENSE_STRING,L"");
	//書き込みチェック
	if(chk_lic_str != LicSet)
	{
		nsLib::ErrMsgBox(Handle,"ライセンス設定の書き込みに失敗しました。インストール時と同じユーザで無いか可能性があります。");
		return;
	}
	//メッセージ
	nsLib::InfMsgBox(Handle,"ライセンス認証が完了しました。\nライセンスのご購入ありがとうございました。");

	Close();
}
//-------------------------------------------------------------
//  機能     ：数字以外入力不可
//
//  関数定義 ：bool Yubin1EditKeyPress(TObject *Sender)
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
void __fastcall TLicSettingForm::Yubin1EditKeyPress(TObject *Sender,char &Key)
{
	//Enterは入力不可
	if(Key == '\r')Key = 0;
	//入力可能文字をﾁｪｯｸ
	if(Key < ' ' || (Key >= '0' && Key <= '9'))
	{
		return;
	}
	//入力できない文字は捨てる
	Key = 0;
}
//-------------------------------------------------------------
//  機能     ：ベクターから注文ボタン
//
//  関数定義 ：void __fastcall LicOrderFromVectorBtnClick(TObject *Sender)
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
void __fastcall TLicSettingForm::LicOrderFromVectorBtnClick(TObject *Sender)
{
	//メインフォーム表示
	PageControl->ActivePage = VectorSheet;
	//ライセンス申請文字列
	TLicense license;
	String LicStr = license.getCorrectLicenceString();
	//セット
	VectorEdit->Text = LicStr;
	//URL作成
	String URL = L"https://s.shop.vector.co.jp/cart_purchase2/add.php?ITEM_NO=SR168620";
	//注文ＷＥＢページを開く
	nsShellApi::Shell(URL.c_str());
}
//-------------------------------------------------------------
//  機能     ：Vectorコピーボタン
//
//  関数定義 ：void __fastcall  VectorCopyBtnClick(TObject *Sender)
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
void __fastcall TLicSettingForm::VectorCopyBtnClick(TObject *Sender)
{
	VectorEdit->SelectAll();
    VectorEdit->CopyToClipboard();
}
//---------------------------------------------------------------------------

