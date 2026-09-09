//---------------------------------------------------------------------------
#ifndef TSBSettingH
#define TSBSettingH
//---------------------------------------------------------------------------
#include "SeikyuBConst.h"

//請求書番頭設定格納
struct TSBSetting
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
	int          Top             = 4;      //請求書番頭の初期左上Y座標
	int          Left            = 50;     //請求書番頭の初期左上X座標
	int          Width           = 900;    //請求書番頭の初期幅
	int          Height          = 756;    //請求書番頭の初期高さ
	int          HistWidth       = 300;    //履歴エリアの幅
public:
	//コンストラクタ
	TSBSetting() = default;
	//コピーコンストラクタ
	TSBSetting(const TSBSetting& h) = default;
public:
	//請求書番頭の設定読み込み
	static bool LoadSBSet(TSBSetting& es,bool Default);
	//請求書番頭の設定保存
	static bool SaveSBSet(const TSBSetting& es);
};

#endif
