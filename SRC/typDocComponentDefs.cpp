//---------------------------------------------------------------------------
#include <Vcl.h>
#pragma hdrstop

#include "typDocComponentDefs.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
//用紙サイズ名から用紙情報を得る
//---------------------------------------------------------------------------
bool typDocComponentDefs::GetDocComponentDefFromName(String DocComponentName,typDocComponentDef& comp)
{
	for(int Cnt = 0;Cnt < DOC_COMPONENT_KIND_NUM;Cnt++)
	{
		//名前一致チェック
		if(DocComponentName == DocComponentDef[Cnt].ComponentName)
		{
			comp = DocComponentDef[Cnt];
			return true;
		}
	}
	//該当しない場合は不明を選択
	comp = DocComponentDef[dcUnknown];

	return false;
}

