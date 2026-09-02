//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "typDocument.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//書類情報
typDocument Document;

//-------------------------------------------------------------
//書類部品リストの要素数
//-------------------------------------------------------------
int typDocument::GetCompoSize()
{
	return DocCompo.size();
}
//-------------------------------------------------------------
//インデックスから書類部品リスト要素を得る
//-------------------------------------------------------------
typDocCompo& typDocument::GetCompoFromIndex(int idx)
{
	return DocCompo[idx];
}
//-------------------------------------------------------------
//書類部品リストを消去
//-------------------------------------------------------------
void typDocument::ClearDocCompo()
{
	DocCompo.clear();
}
//-------------------------------------------------------------
//データ消去
//-------------------------------------------------------------
void typDocument::ClearData()
{
	for(int Cnt = 0;Cnt < DOCUMENT_KIND_NUM;Cnt++)
	{
		Data[Cnt].Clear();
	}
}
//-------------------------------------------------------------
//書類部品情報名から書類部品情報を得る
//-------------------------------------------------------------
bool typDocument::GetDocCompoFromName(const String& Name,typDocCompo& doc_compo)
{
	typDocCompo  Key;
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
//書類部品情報名から書類部品情報をセット
//-------------------------------------------------------------
bool typDocument::SetDocCompoFromName(const String& name,const typDocCompo& doc_compo)
{
	typDocCompo  Key;
	//最初のセルの情報
	Key.Paper    = Paper;
	Key.DocKind  = DocKind;
	Key.Name     = name;
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

