//---------------------------------------------------------------------------
#ifndef TDocKindsH
#define TDocKindsH
//---------------------------------------------------------------------------
#include "SeikyuBConst.h"

//書類種類の定義
class typDocKindDef
{
public:
	typProcMode    Number;    //書類種類
	const wchar_t *KindName;  //書類種類名
public:
	//コンストラクタ
	typDocKindDef() = default;
	//コピーコンストラクタ
	typDocKindDef(const typDocKindDef& h) = default;

public:
	//代入
	typDocKindDef& operator = (const typDocKindDef& h) = default;
};

//書類種類の定義
constexpr const typDocKindDef DocKindDef[DOCUMENT_KIND_NUM] = {
	{pmSeikyu   ,L"BILL"},      //請求書
	{pmNouhin   ,L"DELIVERED"}, //納品書
	{pmMitsumori,L"ESTIMATED"}, //納品書
};

//書類種類のリスト
class TDocKinds
{

};

#endif
