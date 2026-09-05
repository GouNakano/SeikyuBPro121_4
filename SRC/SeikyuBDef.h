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

//共通変数定義
extern typSBSetting ES;

//----- 共通関数 -----

class sbp
{
public:
	//入力文字列に対して半角にします
	static String StrToHan(const String& Str);
	//ライセンス状態
	static bool   CheckLicenceEnable();
	//メインフォーム設定読み込み
	static void   LoadMainFormSet();
	//請求書番頭の設定読み込み
	static void   LoadSBSet(typSBSetting& ES,bool Default);
	//請求書番頭の設定保存
	static void   SaveSBSet();
};

//----- グローバル変数 -----
//書類情報
extern typDocument Document;
//繰り返し入力用ﾘｽﾄｸﾗｽのｵﾌﾞｼﾞｪｸﾄ
extern ClsInputDataList Inpts;

#endif
