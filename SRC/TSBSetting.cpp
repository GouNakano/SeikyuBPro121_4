//---------------------------------------------------------------------------
#include<Vcl.h>
#pragma hdrstop

#include "SBRegIni.h"
#include "TSBSetting.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//-------------------------------------------------------------
//  機能     ：請求書番頭の設定読み込み
//
//  関数定義 ：bool LoadSBSet(TSBSetting& ES,bool Default)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：TEditSetting& ES      取得したエディット設定
//             bool          Default ==true インストール時設定 ==false 現在の設定
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
bool TSBSetting::LoadSBSet(TSBSetting& ES,bool Default)
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

	//レジストリから請求書番頭の設定を取得
	//共通定義
	ES.IsRemain        = Ini->ReadBool   (INI_SETTING_SECTION,INI_ISREMAIN          ,true);    //前回の状態を再現
	ES.BackupFile      = Ini->ReadBool   (INI_SETTING_SECTION,INI_BACKUPFILE        ,true);    //バックアップファイルの作成
	ES.UseTemplateFile = Ini->ReadBool   (INI_SETTING_SECTION,INI_USE_TEMPLATE      ,false);   //新規作成時のテンプレートファイルの使用
	ES.TemplateFile    = Ini->ReadString (INI_SETTING_SECTION,INI_TEMPLATE_FILE     ,L"");     //新規作成時のテンプレートファイル
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
	ES.Top             = Ini->ReadInteger(C_SYSTEM_SETTING   ,V_WINDOW_TOP          ,4);
	ES.Left            = Ini->ReadInteger(C_SYSTEM_SETTING   ,V_WINDOW_LEFT         ,50);
	ES.Width           = Ini->ReadInteger(C_SYSTEM_SETTING   ,V_WINDOW_WIDTH        ,900);
	ES.Height          = Ini->ReadInteger(C_SYSTEM_SETTING   ,V_WINDOW_HEIGHT       ,756);
	ES.HistWidth       = Ini->ReadInteger(C_SYSTEM_SETTING   ,V_WINDOW_HIST_WIDTH   ,300);

	return true;
}
//-------------------------------------------------------------
//  機能     ：請求書番頭の設定保存
//
//  関数定義 ：bool SaveSBSet(const TSBSetting& ES)
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
bool TSBSetting::SaveSBSet(const TSBSetting& ES)
{
	std::unique_ptr<SBRegIni> Ini(new SBRegIni);

	//レジストリに請求書番頭の設定データをセット
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
	Ini->WriteInteger(C_SYSTEM_SETTING   ,V_WINDOW_TOP          ,ES.Top);
	Ini->WriteInteger(C_SYSTEM_SETTING   ,V_WINDOW_LEFT         ,ES.Left);
	Ini->WriteInteger(C_SYSTEM_SETTING   ,V_WINDOW_WIDTH        ,ES.Width);
	Ini->WriteInteger(C_SYSTEM_SETTING   ,V_WINDOW_HEIGHT       ,ES.Height);
	Ini->WriteInteger(C_SYSTEM_SETTING   ,V_WINDOW_HIST_WIDTH   ,ES.HistWidth);

	return true;
}

