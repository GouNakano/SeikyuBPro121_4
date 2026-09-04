//---------------------------------------------------------------------------
#include<Vcl.h>
#pragma hdrstop

#include<string>

#include <openssl/rsa.h>
#include <openssl/engine.h>
#include <openssl/err.h>
#include <openssl/rc4.h>

#include "strconv.h"
#include "SeikyuBConst.h"
#include "SBRegIni.h"
#include "TLicense.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
//ディスクシリアル文字列を得る
//---------------------------------------------------------------------------
String TLicense::GetDiskSerialString()
{
	wchar_t VolumeName[1000];
	wchar_t SystemName[1000];
	DWORD   SerialNumber;
	DWORD   FileNameLength;
	DWORD   Flags;
	String  Str;

	//Cドライブの情報を得る
	GetVolumeInformationW(
		L"C:\\",
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
//---------------------------------------------------------------------------
//バイナリ配列を文字列化する
//---------------------------------------------------------------------------
String TLicense::SetBinToString(unsigned char bin[],int len)
{
	wchar_t Buf[16];
	String  Str;
	//一バイトごとに１６進表示
	for(int Cnt = 0;Cnt < len;Cnt++)
	{
		//１６進文字列
		swprintf(Buf,L"%02X",bin[Cnt]);
		//結合
		Str += Buf;
	}
	return Str;
}
//---------------------------------------------------------------------------
//ライセンス設定文字列の作成
//---------------------------------------------------------------------------
String TLicense::CreateLicenceSettingString(String LicenceApplicationString)
{
	RC4_KEY        rc4key;
	const    char *pKey  = INI_DOK_BTOMHEIGHT;   //暗号化キー
	unsigned char  encryptdata[64];              //暗号化された文字列
	String         Hex16Str;                     //暗号化された文字列を１６進文字列化
	std::string    LicAppStr = wide_to_ansi(LicenceApplicationString.c_str());
	//ディスクシリアルを確認する
	memset(encryptdata,0,sizeof(encryptdata));
	//暗号化
	RC4_set_key(&rc4key,strlen(pKey),(unsigned char *)pKey);
	RC4(&rc4key,LicenceApplicationString.Length(),(const unsigned char *)LicAppStr.c_str(),encryptdata);
	//バイナリから１６進文字列に変換
	Hex16Str = SetBinToString(encryptdata,LicenceApplicationString.Length());

	return Hex16Str;
}
//---------------------------------------------------------------------------
//ライセンス設定文字列を得る
//---------------------------------------------------------------------------
String TLicense::getLicenceSettingString()
{
	RC4_KEY        rc4key;
	const    char *pKey  = INI_DOK_STOCKMANAGER; //暗号化キー
	unsigned char  encryptdata[32];              //暗号化された文字列
	//ディスクシリアル文字列を得る
	String DskStr = GetDiskSerialString();
	//ディスクシリアルを確認する
	memset(encryptdata,0,sizeof(encryptdata));
	//暗号化
	std::string ansi_dsk_str = wide_to_ansi(DskStr.c_str());
	RC4_set_key(&rc4key,strlen(pKey),(unsigned char *)pKey);
	RC4(&rc4key,ansi_dsk_str.size(),(unsigned char *)ansi_dsk_str.c_str(),encryptdata);
	//バイナリから１６進文字列に変換
	String Hex16Str = SetBinToString(encryptdata,DskStr.Length());
	//ライセンス設定文字列の作成
	String LicSet = CreateLicenceSettingString(Hex16Str);

	return LicSet;
}
//---------------------------------------------------------------------------
//ライセンス申請のための文字列を作成する
//---------------------------------------------------------------------------
String TLicense::GetLicenceApplicationString()
{
	RC4_KEY        rc4key;
	const    char *pKey  = INI_DOK_STOCKMANAGER; //暗号化キー
	unsigned char  encryptdata[32];              //暗号化された文字列
	String         Hex16Str;                     //暗号化された文字列を１６進文字列化
	//ディスクシリアル文字列を得る
	String wDskStr      = GetDiskSerialString();
	std::string DskStr  = wide_to_ansi(wDskStr.c_str());
	//ディスクシリアルを確認する
	memset(encryptdata,0,sizeof(encryptdata));
	//暗号化
	RC4_set_key(&rc4key,strlen(pKey),(unsigned char *)pKey);
	RC4(&rc4key,DskStr.size(),(unsigned char *)DskStr.c_str(),encryptdata);
	//バイナリから１６進文字列に変換
	Hex16Str = SetBinToString(encryptdata,DskStr.size());

	return Hex16Str;
}
//---------------------------------------------------------------------------
//現在レジストリに設定されているライセンス文字列を得る
//---------------------------------------------------------------------------
String TLicense::getLicenceStringFromReg()
{
	String LicenseStr;

	//ライセンス文字列取得
	try
	{
		std::unique_ptr<SBRegIni> pReg(new SBRegIni);
		LicenseStr  = pReg->ReadString(C_SYSTEM_SETTING,LICENSE_STRING,L"");
	}
	catch(Exception&  e)
	{
		return L"";
	}
	return LicenseStr;
}
//---------------------------------------------------------------------------
//正解のライセンス文字列を得る
//---------------------------------------------------------------------------
String TLicense::getCorrectLicenceString()
{
	return getLicenceSettingString();
}
//---------------------------------------------------------------------------
//ライセンスの状態を得る(Trueライセンス有効)
//---------------------------------------------------------------------------
bool TLicense::isLicenceEnable()
{
	//ライセンス文字列取得
	String LicenseStr  = getLicenceStringFromReg();
	//正解のライセンス文字列取得
	String TrueLicStr = getLicenceSettingString();
	//レジストリのライセンス文字列と比較
	if(TrueLicStr == LicenseStr)
	{
		//ライセンスあり
		return true;
	}
	return false;
}
