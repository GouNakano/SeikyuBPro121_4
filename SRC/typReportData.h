//---------------------------------------------------------------------------
#ifndef typReportDataH
#define typReportDataH
//---------------------------------------------------------------------------
#include <array>

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
#endif
