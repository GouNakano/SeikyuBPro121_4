//---------------------------------------------------------------------------
#ifndef TStdColumnH
#define TStdColumnH
//---------------------------------------------------------------------------
#include "SeikyuBConst.h"

//標準列の数
constexpr const int STD_COLUMN_NUM = 8;
//標準列情報
struct typStdColumnDef
{
	const wchar_t    *Name;       //列名
	TAlignment        Alignment;  //テキスト揃え

};

//標準列情報
constexpr const typStdColumnDef StdColumn[STD_COLUMN_NUM] = {
	{L"項目"   ,taCenter      },
	{L"品目名" ,taLeftJustify },
	{L"数量"   ,taRightJustify},
	{L"単位"   ,taCenter      },
	{L"単価"   ,taRightJustify},
	{L"金額"   ,taRightJustify}
};
#endif
