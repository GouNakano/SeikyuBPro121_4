//---------------------------------------------------------------------------
#ifndef SeikyuBDefH
#define SeikyuBDefH
#include <QuickRpt.hpp>
#include <map>
#include "TSCommonLib.h"
#include "nsLong.h"
#include "nsDouble.h"
#include "TSLtabCL.h"
#include "SeikyuBConst.h"
#include "ClsInputDataList.h"
#include "typDocument.h"
#include "typReportData.h"
#include "THistories.h"
#include "SBRegIni.h"
#include "TReopen.h"
#include "TSBSetting.h"
//---------------------------------------------------------------------------

//標準列の数
#define STD_COLUMN_NUM (6)
//標準列情報
struct typStdColumnDef
{
	const wchar_t    *Name;       //列名
	TAlignment        Alignment;  //テキスト揃え

};

//共通変数定義
extern bool         IsFirstUse;            //初回起動
extern typSBSetting ES;
extern String       LicenseStr;            //ライセンス文字列

//----- 共通関数 -----

class sbp
{
public:
	//入力文字列に対して半角にします
	static std::string         StrToHan(std::string Str);
	//ライセンス状態
	static bool                CheckLicenceEnable();
	//メインフォーム設定読み込み
	static void                LoadMainFormSet();
	//ディスクシリアル文字列を得る
	static String              GetDiskSerialString();
	//請求書番頭の設定読み込み
	static void                LoadSBSet(typSBSetting& ES,bool Default);
	//請求書番頭の設定保存
	static void                SaveSBSet();
};

//----- グローバル変数 -----
//書類情報
extern typDocument Document;
//標準列情報
extern typStdColumnDef StdColumn[STD_COLUMN_NUM];
//繰り返し入力用ﾘｽﾄｸﾗｽのｵﾌﾞｼﾞｪｸﾄ
extern ClsInputDataList Inpts;

#endif
