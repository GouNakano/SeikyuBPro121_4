//---------------------------------------------------------------------------
#include<Vcl.h>
#pragma hdrstop

#include "TZooms.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
//ズーム名からズーム情報を得る
//---------------------------------------------------------------------------
bool TZooms::GetZoomDefFromName(String ZoomName,typZoomDef& zoom)
{
	for(int Cnt = 0;Cnt < ZOOM_KIND_NUM;Cnt++)
	{
		//名前一致チェック
		if(ZoomName == ZoomDef[Cnt].ZoomName)
		{
			zoom = ZoomDef[Cnt];
			return true;
		}
	}
	//該当しない場合は100%を選択
	zoom = ZoomDef[Z100];

	return false;
}

//---------------------------------------------------------------------------
//ズーム情報を得る
//---------------------------------------------------------------------------
bool TZooms::get(int idx,typZoomDef& zoom)
{
	if(idx < 0 || idx >= ZOOM_KIND_NUM)
	{
		return false;
	}

	//インデックスに対応した用紙情報
	zoom = ZoomDef[idx];

	return true;
}
