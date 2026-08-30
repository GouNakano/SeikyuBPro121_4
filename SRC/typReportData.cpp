//---------------------------------------------------------------------------
#include <vcl.h>
#include <System.Win.Registry.hpp>
#pragma hdrstop

#include "TSCommonLib.h"
#include "typReportData.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
//要素数
//---------------------------------------------------------------------------
int TSBFreeDataList::size()
{
	return SBFreeDataList.size();
}
//---------------------------------------------------------------------------
//消去
//---------------------------------------------------------------------------
bool TSBFreeDataList::clear()
{
	SBFreeDataList.clear();

	return true;
}
//---------------------------------------------------------------------------
//要素取得[]演算子
//---------------------------------------------------------------------------
typReportData& TSBFreeDataList::operator [](int idx)
{
	return SBFreeDataList[idx];
}
//-------------------------------------------------------------
//数字だけを残した文字列を作成
//-------------------------------------------------------------
String TSBFreeDataList::MakeNumberString(const String& Str)
{
	String Chr;
	String NumStr;

	for(int Cnt = 1;Cnt <= Str.Length();Cnt++)
	{
		//一文字取り出し
		Chr = Str[Cnt];
		//数字なら追加
		if(Chr >= "0" && Chr <= "9")
		{
			NumStr += Chr;
		}
	}
	return NumStr;
}
//---------------------------------------------------------------------------
//請求書番頭フリー版の読み込み
//---------------------------------------------------------------------------
bool TSBFreeDataList::load()
{
	int     DivNum;
	String  ValueName;
	String  GridStr;
	std::vector<String> pStrs;
	//リスト初期化
	SBFreeDataList.clear();
	//文字列リスト
	std::unique_ptr<TStringList> pSections(new TStringList);
	//請求書番頭フリー版レジストリ
	std::unique_ptr<TRegistryIniFile> pReg(new TRegistryIniFile("Software\\SakuraDensan\\SeikyuBFree\\history"));
	//セクション一覧を得る
	pReg->ReadSections(pSections.get());
	//リストをセット
	for(int Cnt = 0;Cnt < pSections->Count;Cnt++)
	{
		//セクション名
		String SectionStr = pSections->Strings[Cnt];
		//データを得る
		int    Year    = pReg->ReadString(SectionStr,"YearEdit" ,"").ToIntDef(2008); //年
		int    Month   = pReg->ReadString(SectionStr,"MonthEdit","").ToIntDef(1);    //月
		int    Day     = pReg->ReadString(SectionStr,"DayEdit"  ,"").ToIntDef(1);    //日
		String NameStr = pReg->ReadString(SectionStr,"NameEdit" ,"");                //名前
		String ItemStr = pReg->ReadString(SectionStr,"ItemEdit" ,"");                //件名

		//請求書番頭フリー版からの書類データ
		typReportData pData;

		pData.Key      = SectionStr;
		pData.Year     = Year;
		pData.Month    = Month;
		pData.Day      = Day;
		pData.NameStr  = NameStr; //名前
		pData.ItemStr  = ItemStr; //件名
		pData.No       = pReg->ReadString(SectionStr,"NoEdit","");       //番号
		pData.Money    = pReg->ReadString(SectionStr,"MoneyEdit","");    //請求金額
		pData.Subtotal = pReg->ReadString(SectionStr,"SubtotalEdit",""); //小計
		pData.Tax      = pReg->ReadString(SectionStr,"TaxEdit","");      //消費税
		pData.Total    = pReg->ReadString(SectionStr,"TotalEdit","");    //合計

		//グリッド内容の保存
		for(int Row = 1;Row < 15;Row++)
		{
			//Value名
			ValueName.sprintf(L"D%02d",Row);
			//一行分のデータを得る
			GridStr = pReg->ReadString(SectionStr,ValueName,L"");
			//カンマで分解
			DivNum = TSCommonLib::CSVDivide(pStrs,GridStr);
			//グリッド一行分のデータを文字列化
			for(int Col = 0;Col < 5;Col++)
			{
				//分解数と列番号の関係をチェック
				if(DivNum == 0 || DivNum-1 < Col)
				{
					//内容が無いのでセルは空白
					pData.GridData[Row][Col] = L"";
				}
				else
				{
					//内容をセット
					pData.GridData[Row][Col] = pStrs[Col];
				}
			}
		}
		//リストに追加
		SBFreeDataList.push_back(pData);
	}
	return true;
}
//---------------------------------------------------------------------------
//インデックスを指定して書類情報に反映
//---------------------------------------------------------------------------
bool TSBFreeDataList::reflectToDoc(int idx,typDocument& pDoc)
{
	//インデックスチェック
	if(idx < 0 || idx >= size())
	{
		return false;
	}
	//請求書番頭フリー版の対象データ
	typReportData& pData = SBFreeDataList[idx];

	//書類別にデータセット
	for(int Kind = 0;Kind < DOCUMENT_KIND_NUM;Kind++)
	{
		//データのセット
		pDoc.Data[Kind].Year     = pData.Year;                               //年
		pDoc.Data[Kind].Month    = pData.Month;                              //月
		pDoc.Data[Kind].Day      = pData.Day;                                //日
		pDoc.Data[Kind].No       = pData.No;                                 //番号
		pDoc.Data[Kind].Name     = pData.NameStr;                            //名前
		pDoc.Data[Kind].Item     = pData.ItemStr;                            //件名
		pDoc.Data[Kind].Money    = MakeNumberString(pData.Money).c_str();    //金額
		pDoc.Data[Kind].Subtotal = MakeNumberString(pData.Subtotal).c_str(); //小計
		pDoc.Data[Kind].Tax      = MakeNumberString(pData.Tax).c_str();      //消費税
		pDoc.Data[Kind].Total    = pData.Total.c_str();                      //合計
		pDoc.Data[Kind].RowNum   = 15;                                        //行数
		pDoc.Data[Kind].ColNum   = 6;                                         //列数
		//グリッドデータ消去
		pDoc.Data[Kind].GridData.clear();
		//グリッドデータセット
		for(int Row = 1;Row < 15;Row++)
		{
			//一行分のデータ作成
			typDocOneRowData GridRow;
			//データセット
			GridRow.Item       = pData.GridData[Row][0];
			GridRow.Name       = pData.GridData[Row][1];
			GridRow.Num        = pData.GridData[Row][2].c_str();
			GridRow.Unit       = L"";
			GridRow.PriceUnit  = pData.GridData[Row][3].c_str();
			GridRow.Money      = pData.GridData[Row][4].c_str();
			//リストに追加
			pDoc.Data[Kind].GridData.push_back(std::move(GridRow));
		}
	}
	return true;
}

