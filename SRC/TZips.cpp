//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>
#include "TSCommonLib.h"
#include "SeikyuBConst.h"
#include "TZips.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//郵便番号のデータリスト
TZips Zips;

//---------------------------------------------------------------------------
//消去
//---------------------------------------------------------------------------
bool TZips::clear()
{
	zipList.clear();

	return true;
}
//---------------------------------------------------------------------------
//郵便番号CSVから読み込み
//---------------------------------------------------------------------------
bool TZips::load()
{
	//自分のﾌﾙﾊﾟｽを得る
	String MyPath = ExtractFileDir(ParamStr(0));
	//住所ﾌｧｲﾙのﾌﾙﾊﾟｽ
	String FullPath = MyPath + ZIP_CODE_CSV;
	//ファイルを開く
	std::filesystem::path filepath = FullPath.c_str();
	std::ifstream ifs(filepath);

	//リスト消去
	zipList.clear();
	//リストにセット
	std::string line;
	std::vector<String> pStrs;

	while(std::getline(ifs, line))
	{
		//カンマで分解
		int DivNum = TSCommonLib::CSVDivide(pStrs,String(line.c_str()));
		//分解数(=4)チェック
		if(DivNum != 4)
		{
			continue;
		}
		//データ作成
		typZip Zip;

		Zip.ZipCode     = pStrs[0];  //郵便番号
		Zip.Prefecture  = pStrs[1];  //都道府県
		Zip.City        = pStrs[2];  //市町村
		Zip.Address     = pStrs[3];  //町名
		//リストに追加
		zipList[Zip.ZipCode] = std::move(Zip);
	}
	//閉じる
	ifs.close();

	return true;
}
//---------------------------------------------------------------------------
//郵便番号から住所を得る
//---------------------------------------------------------------------------
bool TZips::getAdress(const String& zipCode,String& prefecture,String& city,String& address)
{
	//検索
	decltype(zipList)::iterator find_iter = zipList.find(zipCode);
	//見つかったか？
	if(find_iter == zipList.end())
	{
		return false;
	}
	//データセット
	typZip& find = find_iter->second;

	prefecture = find.Prefecture;
	city       = find.City;
	address    = find.Address;

	return true;
}

