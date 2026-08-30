//---------------------------------------------------------------------------
#pragma hdrstop

#include "TPaperDefs.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//用紙サイズ名から用紙情報を得る
bool TPaperDefs::GetPaperDefFromName(const String& SizeName,typPaperDef& paper)
{
	for(int Cnt = 0;Cnt < PAPER_SIZE_KIND_NUM;Cnt++)
	{
		//名前一致チェック
		if(SizeName == PaperDef[Cnt].PaperName)
		{
			paper = PaperDef[Cnt];
			return true;
		}
	}
	//該当しない場合はA4縦を選択
	paper = PaperDef[A4P];

	return true;
}
//用紙情報を得る
bool TPaperDefs::get(int idx,typPaperDef& paper)
{
	if(idx < 0 || idx >= PAPER_SIZE_KIND_NUM)
	{
		return false;
	}

	//該当しない場合はA4縦を選択
	paper = PaperDef[idx];

	return true;
}
