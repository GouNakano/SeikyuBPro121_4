//---------------------------------------------------------------------------
#include<vcl.h>
#pragma hdrstop

#include "TStdComponents.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
//用紙種別を得る
//---------------------------------------------------------------------------
bool typDocKindDefs::GetDocKindDefFromName(const String& DocKindName,typDocKindDef& kind)
{
	for(int Cnt = 0;Cnt < DOCUMENT_KIND_NUM;Cnt++)
	{
		//名前一致チェック
		if(DocKindName == DocKindDef[Cnt].KindName)
		{
			kind = DocKindDef[Cnt];
			return true;
		}
	}
	//該当しない場合はA4縦を選択
	kind = DocKindDef[pmSeikyu];

	return true;
}
//---------------------------------------------------------------------------
//コンポーネント名から標準コンポーネント情報を得る
//---------------------------------------------------------------------------
bool typDocKindDefs::GetStdComponentDefFromName(const String& StdComponentName,typStdComponentDef& comp,const typProcMode docMode)
{
	bool res = false;

	for(int Cnt = 0;Cnt < STD_COMPONENT_NUM;Cnt++)
	{
		//名前一致チェック
		if(StdComponentName == StdComponents[Cnt].Name)
		{
			//見つかった
			comp = StdComponents[Cnt];
			res  = true;
			break;
		}
	}
	//見つかったか
	if(res == false)
	{
		return res;
	}
	//現在の対象書類
	const typDocKindDef& docKind = DocKindDef[docMode];
	//書類種別ラベルへの特別処理
	if(comp.Number == scBillLabel)
	{
		switch(docKind.Number)
		{
			case pmSeikyu   :comp.Value = L"請 求 書";break;
			case pmNouhin   :comp.Value = L"納 品 書";break;
			case pmMitsumori:comp.Value = L"見 積 書";break;
			default         :comp.Value = L"請 求 書";
		}
	}
	return res;
}
