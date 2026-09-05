//---------------------------------------------------------------------------
#include <vcl.h>
#include <winnls.h>
#pragma hdrstop

#include <windows.h>
#include <fstream>
#include <filesystem>

#include "nsDouble.h"
#include "strconv.h"
#include "wstr.h"
#include "MainFrm.h"
#include "nsShellApi.h"
#include "TSFileCL.h"
#include "TStdColumn.h"
#include "SeikyuBDef.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//----- 共通変数定義 -----

//請求書番頭の設定
typSBSetting ES;
//繰り返し入力用ﾘｽﾄｸﾗｽのｵﾌﾞｼﾞｪｸﾄ
ClsInputDataList Inpts;

//=============================================================
//
//  ｼｽﾃﾑ名称 ：
//
//  名前空間 ：
//
//  クラス名 ：
//
//  機能     ：共通関数
//
//  継承元   ：
//
//  作成者   ：
//
//  改定者   ：
//
//=============================================================


//-------------------------------------------------------------
//  機能     ：入力文字列に対して半角にします
//
//  関数定義 ：std::string StrToHan(std::string Str)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
String sbp::StrToHan(const String& Str)
{
	String dest;
	//全角から半角
	int len = LCMapStringW(LOCALE_SYSTEM_DEFAULT,LCMAP_HALFWIDTH,Str.c_str(),Str.Length(), NULL, 0);
	dest.SetLength(len);
	LCMapStringW(LOCALE_SYSTEM_DEFAULT, LCMAP_HALFWIDTH,Str.c_str(), Str.Length(),&dest[1], len);
	//通常文字列に復帰
	return dest;
}
//-------------------------------------------------------------
//  機能     ：ライセンス状態
//
//  関数定義 ：bool CheckLicenceEnable()
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
bool sbp::CheckLicenceEnable()
{
	bool IsLicOk = (MainForm->LicenseSettingBtn->Visible == false);

	return IsLicOk;
}
//-------------------------------------------------------------
//  機能     ：メインフォーム設定読み込み
//
//  関数定義 ：void LoadMainFormSet()
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void sbp::LoadMainFormSet()
{
	String Section;

	//メインフォームを得る
	TMainForm *M = MainForm;
	//自分のﾌﾙﾊﾟｽを得る
	String MyPath = ParamStr(0);
	//自分の存在するﾃﾞｨﾚｸﾄﾘ
	String MyDir  = ExtractFileDir(MyPath);
	//EXEの場所をカレントディレクトリにする
	SetCurrentDir(MyDir);

	//Iniﾌｧｲﾙｵｰﾌﾟﾝ
	std::unique_ptr<SBRegIni> pReg(new SBRegIni());
	//EXEの位置とバージョンをレジストリに書く
	pReg->WriteString(C_SYSTEM_SETTING,V_INSTALL_EXE,MyPath);
	//レジストリから各部のデータセット
	M->Top           = pReg->ReadInteger(C_SYSTEM_SETTING,V_WINDOW_TOP ,4);
	M->Left          = pReg->ReadInteger(C_SYSTEM_SETTING,V_WINDOW_LEFT,50);
	M->Width         = pReg->ReadInteger(C_SYSTEM_SETTING,V_WINDOW_WIDTH ,900);
	M->Height        = pReg->ReadInteger(C_SYSTEM_SETTING,V_WINDOW_HEIGHT,756);
}
//-------------------------------------------------------------
//  機能     ：請求書番頭の設定読み込み
//
//  関数定義 ：void LoadSBSet(typSBSetting& ES,bool Default)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：typEditSetting& ES      取得したエディット設定
//             bool            Default ==true インストール時設定 ==false 現在の設定
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void sbp::LoadSBSet(typSBSetting& ES,bool Default)
{
	std::unique_ptr<SBRegIni> Ini;

	if(Default == false)
	{
		Ini.reset(new SBRegIni);
	}
	else
	{
		Ini.reset(new SBRegIni(L""));
	}

	//構造体にデータをセット
	//共通定義
	ES.IsRemain        = Ini->ReadBool   (INI_SETTING_SECTION,INI_ISREMAIN          ,true);    //前回の状態を再現
	ES.BackupFile      = Ini->ReadBool   (INI_SETTING_SECTION,INI_BACKUPFILE        ,true);    //バックアップファイルの作成
	ES.UseTemplateFile = Ini->ReadBool   (INI_SETTING_SECTION,INI_USE_TEMPLATE      ,false);   //新規作成時のテンプレートファイルの使用
	ES.TemplateFile    = Ini->ReadString (INI_SETTING_SECTION,INI_TEMPLATE_FILE     ,"");      //新規作成時のテンプレートファイル
	ES.IsToday         = Ini->ReadBool   (INI_SETTING_SECTION,INI_SET_TODAY         ,true);    //新規作成時、本日の日付をセットするか
	ES.RateTyp1        = (TValuateType)Ini->ReadInteger(INI_SETTING_SECTION,INIKEY_RATE_TYP01     ,tOmit);   //丸めタイプ１
	ES.AccuracyR1      = Ini->ReadInteger(INI_SETTING_SECTION,INIKEY_RATE_ACCURACY01,0);       //小数点以下精度
	ES.RateTyp2        = (TValuateType)Ini->ReadInteger(INI_SETTING_SECTION,INIKEY_RATE_TYP02     ,tOmit);   //丸めタイプ
	ES.AccuracyR2      = Ini->ReadInteger(INI_SETTING_SECTION,INIKEY_RATE_ACCURACY02,0);       //小数点以下精度
	ES.RateTyp3        = (TValuateType)Ini->ReadInteger(INI_SETTING_SECTION,INIKEY_RATE_TYP03     ,tOmit);   //丸めタイプ
	ES.AccuracyR3      = Ini->ReadInteger(INI_SETTING_SECTION,INIKEY_RATE_ACCURACY03,0);       //小数点以下精度
	ES.RateTyp4        = (TValuateType)Ini->ReadInteger(INI_SETTING_SECTION,INIKEY_RATE_TYP04     ,tOmit);   //丸めタイプ
	ES.AccuracyR4      = Ini->ReadInteger(INI_SETTING_SECTION,INIKEY_RATE_ACCURACY04,0);       //小数点以下精度
	ES.RateTyp5        = (TValuateType)Ini->ReadInteger(INI_SETTING_SECTION,INIKEY_RATE_TYP05     ,tOmit);   //丸めタイプ
	ES.AccuracyR5      = Ini->ReadInteger(INI_SETTING_SECTION,INIKEY_RATE_ACCURACY05,0);       //小数点以下精度
}
//-------------------------------------------------------------
//  機能     ：請求書番頭の設定保存
//
//  関数定義 ：void SaveSBSet()
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void sbp::SaveSBSet()
{
	std::unique_ptr<SBRegIni> Ini(new SBRegIni);

	//構造体にデータをセット
	//共通定義
	Ini->WriteBool   (INI_SETTING_SECTION,INI_ISREMAIN          ,(ES.IsRemain == true));        //前回の状態を再現
	Ini->WriteBool   (INI_SETTING_SECTION,INI_BACKUPFILE        ,(ES.BackupFile == true));      //バックアップファイルの作成
	Ini->WriteBool   (INI_SETTING_SECTION,INI_USE_TEMPLATE      ,(ES.UseTemplateFile == true)); //新規作成時のテンプレートファイルの使用
	Ini->WriteString (INI_SETTING_SECTION,INI_TEMPLATE_FILE     ,ES.TemplateFile);    //新規作成時のテンプレートファイル
	Ini->WriteBool   (INI_SETTING_SECTION,INI_SET_TODAY         ,(ES.IsToday == true));         //新規作成時、本日の日付をセットするか
	Ini->WriteInteger(INI_SETTING_SECTION,INIKEY_RATE_TYP01     ,ES.RateTyp1);        //丸めタイプ１
	Ini->WriteInteger(INI_SETTING_SECTION,INIKEY_RATE_ACCURACY01,ES.AccuracyR1);      //小数点以下精度
	Ini->WriteInteger(INI_SETTING_SECTION,INIKEY_RATE_TYP02     ,ES.RateTyp2);        //丸めタイプ
	Ini->WriteInteger(INI_SETTING_SECTION,INIKEY_RATE_ACCURACY02,ES.AccuracyR2);      //小数点以下精度
	Ini->WriteInteger(INI_SETTING_SECTION,INIKEY_RATE_TYP03     ,ES.RateTyp3);        //丸めタイプ
	Ini->WriteInteger(INI_SETTING_SECTION,INIKEY_RATE_ACCURACY03,ES.AccuracyR3);      //小数点以下精度
	Ini->WriteInteger(INI_SETTING_SECTION,INIKEY_RATE_TYP04     ,ES.RateTyp4);        //丸めタイプ
	Ini->WriteInteger(INI_SETTING_SECTION,INIKEY_RATE_ACCURACY04,ES.AccuracyR4);      //小数点以下精度
	Ini->WriteInteger(INI_SETTING_SECTION,INIKEY_RATE_TYP05     ,ES.RateTyp5);        //丸めタイプ
	Ini->WriteInteger(INI_SETTING_SECTION,INIKEY_RATE_ACCURACY05,ES.AccuracyR5);      //小数点以下精度
}

