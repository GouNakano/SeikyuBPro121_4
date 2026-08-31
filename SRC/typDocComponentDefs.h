//---------------------------------------------------------------------------
#ifndef typDocComponentDefsH
#define typDocComponentDefsH
//---------------------------------------------------------------------------
#include "SeikyuBConst.h"


//書類部品種類の数
constexpr const int DOC_COMPONENT_KIND_NUM = 10;

//書類部品定義構造体
struct typDocComponentDef
{
	dcDocComponent      Number;         //書類部品定義番号
	const wchar_t      *ComponentName;  //書類部品定義名称
};

//書類部品定義構造体
constexpr const typDocComponentDef DocComponentDef[DOC_COMPONENT_KIND_NUM] = {
	{dcUnknown    ,L"UNKNOWN"  }, //未定義
	{dcLabel      ,L"LABEL"    }, //ラベル
	{dcEdit       ,L"EDIT"     }, //Edit
	{dcDayEdit    ,L"NUMEDIT"  }, //数値Edit
	{dcMoneyEdit  ,L"MONEYEDIT"}, //金額エディット
	{dcImage      ,L"IMAGE"    }, //画像
	{dcVLine      ,L"VLINE"    }, //縦線
	{dcCLine      ,L"CLINE"    }, //横線
	{dcGrid       ,L"GRID"     }, //グリッド
	{dcCell       ,L"CELL"     }  //グリッドのセル
};

class typDocComponentDefs
{
public:
	//用紙サイズ名から用紙情報を得る
	static bool GetDocComponentDefFromName(String DocComponentName,typDocComponentDef& comp);
};

#endif
