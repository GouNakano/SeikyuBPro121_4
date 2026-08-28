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
//---------------------------------------------------------------------------

//標準列の数
#define STD_COLUMN_NUM (6)
//標準列情報
struct typStdColumnDef
{
	const wchar_t    *Name;       //列名
	TAlignment        Alignment;  //テキスト揃え

};

//---- 共通定義 ----
struct typZip
{
	String ZipCode;    //郵便番号
	String Prefecture; //都道府県
	String City;       //市町村
	String Address;    //住所
public:
	//コンストラクタ
	typZip() = default;
	//コピーコンストラクタ
	typZip(const typZip& him) = default;
	//移譲コンストラクタ
	typZip(typZip&& him) = default;
	//キーコンストラクタ
	typZip(const String& key)
	:typZip()
	{
		ZipCode = key;
	}

public:
	//代入
	typZip& operator = (const typZip& Him) = default;
	//移譲代入
	typZip& operator = (typZip&& Him) = default;
public:
	//比較
	bool operator == (const typZip& Him)const{return ZipCode == Him.ZipCode;}
	bool operator  > (const typZip& Him)const{return ZipCode  > Him.ZipCode;}
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
	//郵便番号から住所を得る
	static bool                GetAdressFromZipCode(String ZipCode,String& Prefecture,String& City,String& Address);
	//郵便番号情報を読み込む
	static bool                ReadZipList();
	//ライセンス状態
	static bool                CheckLicenceEnable();
	//自社情報の読み込み
	static bool                ReadCompanyInfo();
	//自社情報の保存
	static bool                SaveCompanyInfo();
	//メインフォーム設定読み込み
	static void                LoadMainFormSet();
	//ディスクシリアル文字列を得る
	static String              GetDiskSerialString();
	//請求書番頭の設定読み込み
	static void                LoadSBSet(typSBSetting& ES,bool Default);
	//請求書番頭の設定保存
	static void                SaveSBSet();
	//再開処理情報を得る
	static void                LoadReopenSet(bool& IsReopen,typReopen& ReopenInf);
	//再開処理情報をセット
	static void                SaveReopenSet(bool IsReopen,typReopen& ReopenInf);
};

//----- グローバル変数 -----
//書類情報
extern typDocument Document;
//標準列情報
extern typStdColumnDef StdColumn[STD_COLUMN_NUM];
//住所リスト
extern std::map<String,typZip> ZipList;
//繰り返し入力用ﾘｽﾄｸﾗｽのｵﾌﾞｼﾞｪｸﾄ
extern ClsInputDataList Inpts;

#endif
