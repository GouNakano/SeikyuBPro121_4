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
	//コントロールを検索
	TControl *pCtrl = MainForm->MainPanel->FindChildControl(Name);

	return pCtrl;
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
//標準コンポーネント番号のコンポーネントにデータセット
//-------------------------------------------------------------
bool TDocCompo::setCompoData(scStdComponent sc,const String& data)
{
	TWinLabel   *pLabel = nullptr;
	TBorderEdit *pEdit  = nullptr;

	//標準コンポーネント名からコンポーネントを得る
	TControl *pCtrl = FindControlFromMainPanel(StdComponents[sc].Name);
	//チェック
	if(pCtrl == nullptr)
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
			//ラベルの内容セット
			pLabel->Caption = data;
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
			pEdit->Text = data;
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
			//金額内容
			pEdit->Text = data;
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
			pEdit->Text = data;
			break;
		}
		default:
		{
			//文字列
			pEdit->Text = L"";
		}
	}
	return true;
}

bool TDocCompo::setCompoData(scStdComponent sc,nsLong in)
{
	//セットするデータ文字列
	String data = in.ToStr();
	//コンポーネントにセット
	bool success = setCompoData(sc,data);

	return success;
}
bool TDocCompo::setCompoData(scStdComponent sc,nsDouble in,int Accuracy,TValuateType offType,bool IsDelete0)
{
	//セットするデータ文字列
	String data = in.ToStrEX(Accuracy,offType,IsDelete0);
	//コンポーネントにセット
	bool success = setCompoData(sc,data);

	return success;
}
//-------------------------------------------------------------
//標準コンポーネント番号のコンポーネント名取得
//-------------------------------------------------------------
String TDocCompo::getCompoName(scStdComponent sc)
{
	//標準コンポーネント名からコンポーネントを得る
	TControl *pCtrl = FindControlFromMainPanel(StdComponents[sc].Name);
	//チェック
	if(pCtrl == nullptr)
	{
		return L"";
	}
	return pCtrl->Name;
}
//-------------------------------------------------------------
//標準コンポーネント番号のコンポーネントのデータ取得
//-------------------------------------------------------------
String TDocCompo::getCompoData(scStdComponent sc)
{
	String str;
	//標準コンポーネント名からコンポーネントを得る
	TControl *pCtrl = FindControlFromMainPanel(StdComponents[sc].Name);
	//チェック
	if(pCtrl == nullptr)
	{
		return L"";
	}
	//標準番号から型を得る
	dcDocComponent typ = StdComponents[sc].CompoKind;
	switch(typ)
	{
		case dcLabel:
		{
			//ラベルにキャスト
			TWinLabel *pLabel = dynamic_cast<TWinLabel *>(pCtrl);
			//チェック
			if(pLabel == nullptr)
			{
				return false;
			}
			//ラベルの内容セット
			str = pLabel->Caption;
			break;
		}
		case dcDayEdit:
		{
			//ラベルにキャスト
			TBorderEdit *pEdit = dynamic_cast<TBorderEdit *>(pCtrl);
			//チェック
			if(pEdit == nullptr)
			{
				return false;
			}
			//日付(年、月、日)内容
			str = pEdit->Text;
			break;
		}
		case dcMoneyEdit:
		{
			//ラベルにキャスト
			TBorderEdit *pEdit = dynamic_cast<TBorderEdit *>(pCtrl);
			//チェック
			if(pEdit == nullptr)
			{
				return false;
			}
			//金額内容
			str = pEdit->Text;
			break;
		}
		case dcEdit:
		{
			//ラベルにキャスト
			TBorderEdit *pEdit = dynamic_cast<TBorderEdit *>(pCtrl);
			//チェック
			if(pEdit == nullptr)
			{
				return false;
			}
			//文字列
			str = pEdit->Text;
			break;
		}
		default:
		{
			//サポートされない文字列
			str = L"";
		}
	}
	return str;
}
//-------------------------------------------------------------
//コントロールのTextまたはCaptionを得る
//-------------------------------------------------------------
String TDocCompo::GetControlStrValue(TControl *pCtrl)
{
	TWinLabel    *pWinLabel;
	TBorderEdit *pBorderEdit;
	String       Val;
	//型別処理
	if((pWinLabel = dynamic_cast<TWinLabel *>(pCtrl))!=nullptr)
	{
		Val = pWinLabel->Caption;
	}
	else if((pBorderEdit = dynamic_cast<TBorderEdit *>(pCtrl))!=nullptr)
	{
		Val = pBorderEdit->Text;
	}
	return Val;
}

