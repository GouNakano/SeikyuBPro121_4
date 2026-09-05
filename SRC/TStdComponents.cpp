//---------------------------------------------------------------------------
#include<vcl.h>
#pragma hdrstop

#include "MainFrm.h"
#include "TStdComponents.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//書類部品処理オブジェクト
TDocCompo compo;

//---------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------
TDocCompo::TDocCompo()
{
	//Mapに格納
	for(int idx = 0;idx < STD_COMPONENT_NUM;idx++)
	{
		const typStdComponentDef& comp_item = StdComponents[idx];
		//標準コンポーネントオブジェクトのコンポーネント番号のMap追加
		StdCompNumberMap[comp_item.Number] = comp_item;
		//標準コンポーネントオブジェクトの名前のMap追加
		StdNameMap[String(comp_item.Name)] = comp_item;
	}
}
//---------------------------------------------------------------------------
//用紙種別を得る
//---------------------------------------------------------------------------
bool TDocCompo::GetDocKindDefFromName(const String& DocKindName,typDocKindDef& kind)
{
	//コンポーネント番号が一致するのもの検索
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
bool TDocCompo::GetStdComponentDefFromName(const String& StdComponentName,typStdComponentDef& comp,const typProcMode docMode)
{
	//名前が一致するのもの検索
	decltype(StdNameMap)::iterator it = StdNameMap.find(StdComponentName);
	//見つからない場合
	if(it == StdNameMap.end())
	{
		return false;
	}
	//検索に該当したコンポーネント情報をセット
	comp = it->second;

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
	return true;
}
//-------------------------------------------------------------
//MainPanelから指定Nameのコントロールを得る
//-------------------------------------------------------------
TControl *TDocCompo::FindControlFromMainPanel(const String& Name)
{
	for(int Cnt=0;Cnt < MainForm->MainPanel->ControlCount;Cnt++)
	{
		TControl *pCtrl = MainForm->MainPanel->Controls[Cnt];

		if(pCtrl->Name == Name)
		{
			return pCtrl;
		}
	}
	return 0;
}

