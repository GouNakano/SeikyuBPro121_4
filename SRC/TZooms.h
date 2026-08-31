//---------------------------------------------------------------------------
#ifndef TZoomsH
#define TZoomsH
//---------------------------------------------------------------------------
#include "SeikyuBConst.h"

//ズームの種類の数
constexpr const int ZOOM_KIND_NUM = 11;

//ズーム定義構造体
class typZoomDef
{
public:
	zoZoomDef           Number;      //ズーム定義番号
	const wchar_t      *ZoomName;    //ズーム定義名称
	int                 Zoom;        //倍率(%)
public:
	//コンストラクタ
	typZoomDef() = default;
	//コピーコンストラクタ
	typZoomDef(const typZoomDef& h) = default;
public:
	//代入
	typZoomDef& operator = (const typZoomDef& h) = default;
};

//ズーム定義
constexpr const typZoomDef ZoomDef[ZOOM_KIND_NUM] = {
	{Z200,L"Z200",200}, //200%
	{Z100,L"Z100",100}, //100%
	{Z90 ,L"Z90" , 90}, //90%
	{Z80 ,L"Z80" , 80}, //80%
	{Z70 ,L"Z70" , 70}, //70%
	{Z60 ,L"Z60" , 60}, //60%
	{Z50 ,L"Z50" , 50}, //50%
	{Z40 ,L"Z40" , 40}, //40%
	{Z30 ,L"Z30" , 30}, //30%
	{Z20 ,L"Z20" , 20}, //20%
	{Z10 ,L"Z10" , 10}  //10%
};

//ズーム種類の取得
class TZooms
{
public:
	//ズーム名からズーム情報を得る
	static bool GetZoomDefFromName(String ZoomName,typZoomDef& zoom);
	//ズーム情報を得る
	static bool get(int idx,typZoomDef& zoom);
	//ズームの種類数
	constexpr static int size()
	{
		return ZOOM_KIND_NUM;
	}
};

#endif
