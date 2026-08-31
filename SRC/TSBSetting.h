//---------------------------------------------------------------------------
#ifndef TSBSettingH
#define TSBSettingH
//---------------------------------------------------------------------------
#include "SeikyuBConst.h"

//請求書番頭設定格納
struct typSBSetting
{
public:
	//共通定義
	bool         IsRemain        = true;   //前回のを再現
	bool         BackupFile      = true;   //バックアップファイルの作成
	bool         UseTemplateFile = false;  //新規作成時のテンプレートファイルの使用
	String       TemplateFile;             //新規作成時のテンプレートファイル
	bool         IsToday         = true;   //新規作成時、本日の日付をセットするか
	int          AccuracyR1      = 0;      //小数点以下の桁数
	int          AccuracyR2      = 0;      //小数点以下の桁数
	int          AccuracyR3      = 0;      //小数点以下の桁数
	int          AccuracyR4      = 0;      //小数点以下の桁数
	int          AccuracyR5      = 0;      //小数点以下の桁数
	TValuateType RateTyp1        = tOmit;  //小数点有効桁以下処理タイプ
	TValuateType RateTyp2        = tOmit;  //小数点有効桁以下処理タイプ
	TValuateType RateTyp3        = tOmit;  //小数点有効桁以下処理タイプ
	TValuateType RateTyp4        = tOmit;  //小数点有効桁以下処理タイプ
	TValuateType RateTyp5        = tOmit;  //小数点有効桁以下処理タイプ
public:
	//コンストラクタ
	typSBSetting() = default;
	//コピーコンストラクタ
	typSBSetting(const typSBSetting& h) = default;
};

#endif
