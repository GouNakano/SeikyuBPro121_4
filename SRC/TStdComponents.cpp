//---------------------------------------------------------------------------
#include<vcl.h>
#pragma hdrstop

#include "TBorderEdit.h"
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
//-------------------------------------------------------------
//コンポーネントの型を得る
//-------------------------------------------------------------
dcDocComponent TDocCompo::GetComponentType(TComponent *pCompo)
{
	TWinLabel       *pWinLabel   = nullptr;
	TBorderEdit     *pBorderEdit = nullptr;
	TImageControl   *pImage      = nullptr;
	TWinShape       *pShape      = nullptr;
	XnsGrid         *pGrid       = nullptr;
	dcDocComponent   Type;
	//コンポーネントの型を得る
	if(pCompo == nullptr)
	{
		//不明
		Type = dcUnknown;
	}
	else if((pWinLabel = dynamic_cast<TWinLabel *>(pCompo)) != nullptr)
	{
		//ラベル
		Type = dcLabel;
	}
	else if((pBorderEdit = dynamic_cast<TBorderEdit *>(pCompo)) != nullptr)
	{
		//枠つきEdit
		Type = dcMoneyEdit;
	}
	else if((pImage = dynamic_cast<TImageControl *>(pCompo)) != nullptr)
	{
		//画像
		Type = dcImage;
	}
	else if((pShape = dynamic_cast<TWinShape *>(pCompo)) != nullptr)
	{
		//Shape
		if(pShape->Height <= 2)
		{
			//横線
			Type = dcCLine;
		}
		else
		{
			//縦線
			Type = dcVLine;
		}
	}
	else if((pGrid = dynamic_cast<XnsGrid *>(pCompo)) != nullptr)
	{
		//画像
		Type = dcGrid;
	}
	else
	{
		//不明
		Type = dcUnknown;
	}
	return Type;
}
//-------------------------------------------------------------
//コンポーネント名と標準コンポーネント番号からデータを得る
//-------------------------------------------------------------
bool TDocCompo::getCompoData(scStdComponent sc,TCompoData& data)
{
	TWinLabel   *pLabel = nullptr;
	TBorderEdit *pEdit  = nullptr;

	//データ初期化
	data.clear();
	//標準コンポーネント名からコンポーネントを得る
	TControl *pCtrl = FindControlFromMainPanel(StdComponents[sc].Name);
	//チェック
	if(pLabel == nullptr)
	{
		return false;
	}
	//標準番号から型を得る
	dcDocComponent typ = StdComponents[sc].CompoKind;
	//コンポーネントの型に沿ってキャスト
	switch(typ)
	{
		case dcLabel:
		{
			//ラベルにキャスト
			pLabel = dynamic_cast<TWinLabel *>(pCtrl);
			//チェック
			if(pLabel == nullptr)
			{
				return false;
			}
			//ラベルの内容
			data.str_val = pLabel->Caption;
			break;
		}
		case dcDayEdit:
		{
			//ラベルにキャスト
			pEdit = dynamic_cast<TBorderEdit *>(pCtrl);
			//チェック
			if(pEdit == nullptr)
			{
				return false;
			}
			//日付(年、月、日)内容
			data.int_val = pEdit->Text.ToIntDef(0);
			break;
		}
		case dcMoneyEdit:
		{
			//ラベルにキャスト
			pEdit = dynamic_cast<TBorderEdit *>(pCtrl);
			//チェック
			if(pEdit == nullptr)
			{
				return false;
			}
			//日付(年、月、日)内容
			data.dbl_val = std::_wtof(pEdit->Text.c_str());
			break;
		}
		case dcEdit:
		{
			//ラベルにキャスト
			pEdit = dynamic_cast<TBorderEdit *>(pCtrl);
			//チェック
			if(pEdit == nullptr)
			{
				return false;
			}
			//文字列
			data.str_val = pEdit->Text;
			break;
		}
	}
    return true;
}

