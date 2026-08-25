//---------------------------------------------------------------------------
#include <vcl.h>
#include <System.Win.ComObj.hpp>
#pragma hdrstop

#include <algorithm>
#include "TSCommonLib.h"
#include "SeikyuBConst.h"
#include "SBRegIni.h"
#include "ClsInputDataList.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//=============================================================
//
//  ｼｽﾃﾑ名称 ：請求書番頭 プロ版
//
//  ｻﾌﾞｼｽﾃﾑ名：
//
//  名前空間 ：なし
//
//  クラス名 ：ClsInputDataList
//
//  機能     ：繰り返し入力用ﾘｽﾄｸﾗｽ
//
//  継承元   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//  改定者   ：
//
//=============================================================

//-------------------------------------------------------------
//  機能     ：ﾌｧｲﾙから読み出す
//
//  関数定義 ：bool Load()
//
//  ｱｸｾｽﾚﾍﾞﾙ ：public
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
bool ClsInputDataList::Load()
{
	//入力履歴レジストリを開く
	SBRegIni *pIni = new SBRegIni;
	//Value一覧を得る
	TStringList *pValues = new TStringList;
	pIni->ReadSectionValues(INI_REG_INPUT,pValues);
	//データ取り込み
	for(int Cnt = 0;Cnt < pValues->Count;Cnt++)
	{
//		wchar_t   Buf[1024];
		std::vector<String> sptr;
//		wchar_t *sptr[256];

		//名前を得る
		String Name = pValues->Names[Cnt];
		//内容取り込み
		String Val  = pValues->Values[Name];
//		//バッファにコピー
//		wcscpy(Buf,Val.c_str());
		//分解
		int DivNum = TSCommonLib::CSVDivide(sptr,Val);
		//データ追加
		if(DivNum >= 3)
		{
			//ﾘｽﾄのｱｲﾃﾑを生成
			InputData Item;
//			InputData *Item = new InputData();
			//ｺﾝﾄﾛｰﾙ名
			Item.CtrlName  = sptr[0];
			//内容
			Item.Str       = sptr[1];
			//順位
			Item.Rank      = sptr[2];
			//ﾘｽﾄに追加
			StrList.push_back(Item);
//			StrList.SortingAdd(Item);
		}
	}
	//開放
	delete pIni;
	delete pValues;

	return true;
}
//-------------------------------------------------------------
//  機能     ：ﾌｧｲﾙへﾃﾞｰﾀを保存
//
//  関数定義 ：bool Save()
//
//  ｱｸｾｽﾚﾍﾞﾙ ：public
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
bool ClsInputDataList::Save()
{
	//入力履歴レジストリを開く
	std::unique_ptr<SBRegIni> pIni(new SBRegIni);
	//セクション削除
	pIni->EraseSection(INI_REG_INPUT);
	//データ追加
	for(int Cnt = 0;Cnt <  StrList.size();Cnt++)
	{
		String Buf;
		//名前を生成
		String Name = CreateClassID();
		//ﾃﾞｰﾀを取得
		InputData& Item = StrList[Cnt];
		//内容作成
		Buf.sprintf(L"\"%s\",\"%s\",\"%s\"",Item.CtrlName.c_str(),Item.Str.c_str(),Item.Rank.c_str());
		//レジストリに書き込み
		pIni->WriteString(INI_REG_INPUT,Name,Buf);
	}
	return true;
}
//-------------------------------------------------------------
//  機能     ：追加
//
//  関数定義 ：void AddInputData(String ctrlname,String str)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：public
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
void ClsInputDataList::AddInputData(String ctrlname,String str)
{
//	InputData *SrchItem;
	//内容が空文字列なら登録しない
	if(str == L"")
	{
		return;
	}
	//日付＆時刻を得る
	TDateTime DT   = TDateTime::CurrentDateTime();
	//日付＆時刻を示す文字列を得る
	String DTStr = DT.FormatString("yyyymmddhhnnss");
	//ｱｲﾃﾑ作成
	InputData Item;
	Item.CtrlName  = ctrlname;
	Item.Str       = str;
	Item.Rank      = DTStr;
	//同じ物があるかﾁｪｯｸ
	decltype(StrList)::iterator it = std::find(StrList.begin(),StrList.end(),Item);

//	if((SrchItem = StrList.Search(*Item)) != 0)
	if(it != StrList.end())
	{
		//同じのがある場合は時刻だけ変更
		InputData& SrchItem = (*it);
		SrchItem.Rank = DTStr;
//		delete Item;
		return;
	}
	//登録
	std::sort(StrList.begin(),StrList.end());
//	StrList.SortingAdd(Item);
}
//-------------------------------------------------------------
//  機能     ：削除
//
//  関数定義 ：void DeleteInputData(String ctrlname,String str)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：public
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
void ClsInputDataList::DeleteInputData(String ctrlname,String str)
{
	//ｱｲﾃﾑ作成
	InputData Item;
	Item.CtrlName  = ctrlname;
	Item.Str       = str;
	//内容が空文字列なら登録しない
	if(str == L"")
	{
		return;
	}
	//目的の物があるかﾁｪｯｸ
	decltype(StrList)::iterator it =std::find(StrList.begin(),StrList.end(),Item);
//	InputData *Find = StrList.Search(Item);
	//あるなら削除
//	if(Find)
	if(it != StrList.end())
	{
		StrList.erase(it);
//		StrList.Delete(Find);
	}
}
//-------------------------------------------------------------
//  機能     ：取得
//
//  関数定義 ：void GetInputDataList(String ctrlname,TStrings *List)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：public
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
void ClsInputDataList::GetInputDataList(String ctrlname,TStrings *List)
{
	std::vector<InputDataRank> Ranks;
	//ﾘｽﾄｸﾘｱ
	List->Clear();
	//ｺﾝﾄﾛｰﾙ名が一致するものを追加
	for(int Cnt = 0;Cnt < StrList.size();Cnt++)
	{
		//ｱｲﾃﾑ取得
		InputData& Item = StrList[Cnt];
		//ﾁｪｯｸ
		if(Item.CtrlName == ctrlname)
		{
			Ranks.push_back((InputDataRank&)Item);
		}
	}
	//ソート
	std::sort(Ranks.begin(),Ranks.end());

	for(int Cnt = 0;Cnt < Ranks.size();Cnt++)
	{
		//ｱｲﾃﾑ取得
		InputData& Item = Ranks[Cnt];
		//追加
		List->Add(Item.Str);
	}
}
