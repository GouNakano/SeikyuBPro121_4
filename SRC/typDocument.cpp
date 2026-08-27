//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "typDocument.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//書類情報
typDocument Document;

//=============================================================
//
//  ｼｽﾃﾑ名称 ：請求書番頭 プロ版
//
//  名前空間 ：
//
//  クラス名 ：typDocument
//
//  機能     ：書類情報クラス
//
//  継承元   ：
//
//  作成者   ：
//
//  改定者   ：
//
//=============================================================

//---------------------------------------------------------------------------
//履歴IDのリセット
//---------------------------------------------------------------------------
bool typDocument::resetHistID()
{

}
//-------------------------------------------------------------
//  機能     ：書類部品リストの要素数
//
//  関数定義 ：int GetCompoSize()
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
int typDocument::GetCompoSize()
{
	return DocCompo.size();
}
//-------------------------------------------------------------
//  機能     ：インデックスから書類部品リスト要素を得る
//
//  関数定義 ：typDocCompo& GetCompoFromIndex(int idx)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
typDocCompo& typDocument::GetCompoFromIndex(int idx)
{
	return DocCompo[idx];
}
//-------------------------------------------------------------
//  機能     ：書類部品リストを消去
//
//  関数定義 ：void ClearDocCompo()
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void typDocument::ClearDocCompo()
{
	DocCompo.clear();
}
//-------------------------------------------------------------
//  機能     ：データ消去
//
//  関数定義 ：void ClearData()
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void typDocument::ClearData()
{
	for(int Cnt = 0;Cnt < DOCUMENT_KIND_NUM;Cnt++)
	{
		Data[Cnt].Clear();
	}
}
//-------------------------------------------------------------
//  機能     ：書類部品情報名から書類部品情報を得る
//
//  関数定義 ：typDocCompo *GetDocCompoFromName(String Name)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：public
//
//  引数     ：String Name 書類部品情報名
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
bool typDocument::GetDocCompoFromName(const String& Name,typDocCompo& doc_compo)
{
	typDocCompo  Key;
	int          Idx;
	typDocCompo *pRes = nullptr;
	//最初のセルの情報
	Key.Paper    = Document.Paper;
	Key.DocKind  = Document.DocKind;
	Key.Name     = Name;
	//最初のセル情報のイテレータ
	decltype(DocCompo)::iterator it = std::find(DocCompo.begin(),DocCompo.end(),Key);
	//チェック
	if(it == DocCompo.end())
	{
		//見つからない
		return false;
	}
	//返却オブジェクトとしてセット
	doc_compo = (*it);

	return true;
}
//-------------------------------------------------------------
//  機能     ：書類部品情報名から書類部品情報をセット
//
//  関数定義 ：bool SetDocCompoFromName(String Name,const typDocCompo& doc_compo)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：public
//
//  引数     ：String Name 書類部品情報名
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
bool typDocument::SetDocCompoFromName(String Name,const typDocCompo& doc_compo)
{
	typDocCompo  Key;
	int          Idx;
	typDocCompo *pRes = nullptr;
	//最初のセルの情報
	Key.Paper    = Paper;
	Key.DocKind  = DocKind;
	Key.Name     = Name;
	//最初のセル情報のインデックス
	decltype(DocCompo)::iterator it = std::find(DocCompo.begin(),DocCompo.end(),Key);
	//存在の有無でチェック
	if(it != DocCompo.end())
	{
		//情報を上書き
		(*it) = doc_compo;
	}
	else
	{
		//新規追加
		DocCompo.push_back(doc_compo);
	}
	return true;
}

