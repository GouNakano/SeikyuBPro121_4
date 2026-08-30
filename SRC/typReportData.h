//---------------------------------------------------------------------------
#ifndef typReportDataH
#define typReportDataH
//---------------------------------------------------------------------------
#include <array>
#include <vector>
#include "typDocument.h"

//請求書番頭フリー版データ
class typReportData
{
public:
	using TGridArr = std::array<std::array<String,5>,15>;
public:
	String   Key;             //レジストリキー
	int      Year  = 0;       //年
	int      Month = 0;       //月
	int      Day   = 0;       //日
	String   NameStr;         //名前
	String   ItemStr;         //件名
	String   No;              //番号
	String   Money;           //請求金額
	String   Subtotal;        //小計
	String   Tax;             //消費税
	String   Total;           //合計
	//グリッドの内容
	TGridArr GridData;
public:
	//コンストラクタ
	typReportData() = default;
	//コピーコンストラクタ
	typReportData(const typReportData& h) = default;
public:
	//代入
	typReportData& operator = (const typReportData& h) = default;
};

//請求書番頭フリー版データリスト
class TSBFreeDataList
{
private:
	std::vector<typReportData> SBFreeDataList;
private:
	//数字だけを残した文字列を作成
	String MakeNumberString(const String& Str);
public:
	//コンストラクタ
	TSBFreeDataList() = default;
	//コピーコンストラクタ
	TSBFreeDataList(const TSBFreeDataList& h) = default;
public:
	//要素取得[]演算子
	typReportData& operator [](int idx);
public:
	//要素数
	int size();
	//消去
	bool clear();
	//請求書番頭フリー版の読み込み
	bool load();
	//インデックスを指定して書類情報に反映
	bool reflectToDoc(int idx,typDocument& doc);
};

#endif
