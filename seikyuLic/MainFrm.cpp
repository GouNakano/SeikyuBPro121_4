//---------------------------------------------------------------------------

#include <vcl.h>
#include <Clipbrd.hpp>
#pragma hdrstop

#include <openssl/rsa.h>
#include <openssl/engine.h>
#include <openssl/err.h>
#include <openssl/rc4.h>

#include "strconv.h"
#include "MainFrm.h"

//ディスクシリアル文字列フォーマット
#define DISK_SERIAL_STRING   "GZB%012X"

//ディスクシリアル文字列を得る
extern AnsiString GetDiskSerialString();
//ライセンス設定文字列の作成
extern AnsiString CreateLicenceSettingString(AnsiString LicenceApplicationString);
//バイナリ配列を文字列化する
extern AnsiString SetBinToString(unsigned char bin[],int len);

const char *INI_DOK_PASSCODE     = "FIGURE_LINE";  //暗号化キー
const char *INI_DOK_PASSCODE2    = "FONT_INFO";  //暗号化キー2

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
}
//-------------------------------------------------------------
//  機能     ：発行ボタン
//
//  関数定義 ：void __fastcall IssueBtnClick(TObject *Sender)
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
void __fastcall TMainForm::IssueBtnClick(TObject *Sender)
{
	char        ReqCode[256];
	char        BinCode[256];
	char        EncCode[256];
	RC4_KEY     rc4key;
	const char *pKey  = INI_DOK_PASSCODE; //暗号化キー
	//ライセンス申請コードを得る
	std::string lic_str = wide_to_ansi(LicreqEdit->Text.Trim().c_str());
	strcpy(ReqCode,lic_str.c_str());
	//長さを得る
	int SLen = strlen(ReqCode);
	//０クリア
	memset(BinCode,0,sizeof(BinCode));
	//バイナリコードを得る
	for(int Cnt = 0,BCnt = 0;Cnt < SLen;Cnt+=2,BCnt++)
	{
		char OneChr[3];
		//１６進一文字分得る
		OneChr[0] = ReqCode[Cnt    ];
		OneChr[1] = ReqCode[Cnt + 1];
		OneChr[2] = '\0';
		//バイナリ化
		sscanf(OneChr,"%X",(int *)&BinCode[BCnt]);
	}
	//ディスクシリアル文字列を得る
	AnsiString DskStr = GetDiskSerialString();
	//復号する
	RC4_set_key(&rc4key,strlen(pKey),(unsigned char *)pKey);
	RC4(&rc4key,DskStr.Length(),(unsigned char *)BinCode,(unsigned char *)EncCode);
	EncCode[DskStr.Length()] = '\0';
	//先頭文字のチェック
	bool IsOk = (EncCode[0] == 'G' && EncCode[1] == 'Z' && EncCode[2] == 'B');
	//エラー表示
	if(IsOk == false)
	{
		ErrLabel->Visible = true;
		return;
	}
	//ディスクシリアルを得る
	DiskSerialEdit->Text = (&EncCode[3]);
	//ライセンス認証パスワードをセット
	LicPasswdEdit->Text = CreateLicenceSettingString(ReqCode);
}
//-------------------------------------------------------------
//  機能     ：コピーボタン
//
//  関数定義 ：void __fastcall CopyBtnClick(TObject *Sender)
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
void __fastcall TMainForm::CopyBtnClick(TObject *Sender)
{
	//クリップボードを得る
	TClipboard *pClip = Clipboard();
	//セット
	pClip->AsText = LicPasswdEdit->Text;
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
void __fastcall TMainForm::FormShow(TObject *Sender)
{
	unsigned short year   = 2007;
	unsigned short month  = 1;
	unsigned short day    = 3;

	//2007/1/3
	TDateTime T070103(year,month,day);
	//現在
	TDateTime Now = TDateTime::CurrentDate();

//	//ディスクシリアル文字列を得る
//	nsString DskStr = GetDiskSerialString();
/****
	//チェック
	if(DskStr != "GZB0000A496A8F0" && DskStr != "GZB00005855B514")
	{
		if(T070103 < Now)
		{
			Application->Terminate();
		}
	}
****/
}
//-------------------------------------------------------------
//  機能     ：ディスクシリアル文字列を得る
//
//  関数定義 ：nsString GetDiskSerialString()
//
//  ｱｸｾｽﾚﾍﾞﾙ ：public
//
//  引数     ：
//
//  戻り値   ：true Ok
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
AnsiString GetDiskSerialString()
{
	char       VolumeName[1000];
	char       SystemName[1000];
	DWORD      SerialNumber;
	DWORD      FileNameLength;
	DWORD      Flags;
	AnsiString Str;

	//Cドライブの情報を得る
	::GetVolumeInformationA(
		"C:\\",
		VolumeName,
		1000,
		&SerialNumber,
		&FileNameLength,
		&Flags,
		SystemName,
		1000);
	//ディスクシリアル文字列を作成
	Str.sprintf(DISK_SERIAL_STRING,SerialNumber);

	return Str;
}
//-------------------------------------------------------------
//  機能     ：ライセンス設定文字列の作成
//
//  関数定義 ：nsString CreateLicenceSettingString(nsString LicenceApplicationString)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：public
//
//  引数     ：
//
//  戻り値   ：true Ok
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
AnsiString CreateLicenceSettingString(AnsiString LicenceApplicationString)
{
	RC4_KEY        rc4key;
	const    char *pKey  = INI_DOK_PASSCODE2;    //暗号化キー
	unsigned char  encryptdata[64];              //暗号化された文字列
	AnsiString     Hex16Str;                     //暗号化された文字列を１６進文字列化
	//ディスクシリアルを確認する
	memset(encryptdata,0,sizeof(encryptdata));
	//暗号化
	RC4_set_key(&rc4key,strlen(pKey),(unsigned char *)pKey);
	RC4(&rc4key,LicenceApplicationString.Length(),(unsigned char *)LicenceApplicationString.c_str(),(unsigned char *)encryptdata);
	//バイナリから１６進文字列に変換
	Hex16Str = SetBinToString(encryptdata,LicenceApplicationString.Length());

	return Hex16Str;
}
//-------------------------------------------------------------
//  機能     ：バイナリ配列を文字列化する
//
//  関数定義 ：nsString SetBinToString(unsigned char bin[],int len)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：public
//
//  引数     ：
//
//  戻り値   ：true Ok
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
AnsiString SetBinToString(unsigned char bin[],int len)
{
	char        Buf[16];
	AnsiString  Str;
	//一バイトごとに１６進表示
	for(int Cnt = 0;Cnt < len;Cnt++)
	{
		//１６進文字列
		sprintf(Buf,"%02X",bin[Cnt]);
		//結合
		Str += Buf;
	}
	return Str;
}
//---------------------------------------------------------------------------

