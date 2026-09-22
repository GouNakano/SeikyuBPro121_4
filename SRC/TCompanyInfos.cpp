//---------------------------------------------------------------------------
#include<vcl.h>
#pragma hdrstop

#include "strconv.h"
#include "SeikyuBConst.h"
#include "SBRegIni.h"
#include "TCompanyInfos.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
//自社情報の取得
//---------------------------------------------------------------------------
typCompanyInfoDef& TCompanyInfos::operator[] (int idx)
{
	return CompanyInfo[idx];
}
//-------------------------------------------------------------
//自社情報の読み込み
//-------------------------------------------------------------
bool TCompanyInfos::ReadCompanyInfo()
{
	std::wstring Section;
	//レジストリを開く
	std::unique_ptr<SBRegIni> pIni(new SBRegIni);
	//自社情報の数だけ読み込む
	for(int Cnt = 1;Cnt <= COMPANY_INFO_NUM;Cnt++)
	{
		//レジストリキー(セクション)作成
		Section = std_format(C_KEY_COMPANY_INFO,Cnt);
		//対象データ
		typCompanyInfoDef *pInfo = &CompanyInfo[Cnt-1];
		//データ読み込み
		pInfo->CompanyName = pIni->ReadString (Section,COMPANY_INFO_COMPANYNAME,L"");
		pInfo->Represent   = pIni->ReadString (Section,COMPANY_INFO_REPRESENT  ,L"");
		pInfo->ZipNumber   = pIni->ReadString (Section,COMPANY_INFO_ZIPNUMBER  ,L"");
		pInfo->Address1    = pIni->ReadString (Section,COMPANY_INFO_ADDRESS1   ,L"");
		pInfo->Address2    = pIni->ReadString (Section,COMPANY_INFO_ADDRESS2   ,L"");
		pInfo->TEL         = pIni->ReadString (Section,COMPANY_INFO_TEL        ,L"");
		pInfo->FAX         = pIni->ReadString (Section,COMPANY_INFO_FAX        ,L"");
		pInfo->Transfer1   = pIni->ReadString (Section,COMPANY_INFO_TRANSFER1  ,L"");
		pInfo->Transfer2   = pIni->ReadString (Section,COMPANY_INFO_TRANSFER2  ,L"");
		pInfo->TaxRatio    = pIni->ReadString (Section,COMPANY_INFO_TAXRATIO   ,std::to_wstring(STD_TAXRATIO));
	}

	return true;
}
//-------------------------------------------------------------
//自社情報の保存
//-------------------------------------------------------------
bool TCompanyInfos::SaveCompanyInfo()
{
	std::wstring Section;
	//レジストリを開く
	std::unique_ptr<SBRegIni> pIni(new SBRegIni);
	//自社情報の数だけ読み込む
	for(int Cnt = 1;Cnt <= COMPANY_INFO_NUM;Cnt++)
	{
		//レジストリキー(セクション)作成
		Section = std_format(C_KEY_COMPANY_INFO,Cnt);
		//対象データ
		typCompanyInfoDef& pInfo = CompanyInfo[Cnt-1];
		//データ読み込み
		pIni->WriteString (Section,COMPANY_INFO_COMPANYNAME,pInfo.CompanyName);
		pIni->WriteString (Section,COMPANY_INFO_REPRESENT  ,pInfo.Represent  );
		pIni->WriteString (Section,COMPANY_INFO_ZIPNUMBER  ,pInfo.ZipNumber  );
		pIni->WriteString (Section,COMPANY_INFO_ADDRESS1   ,pInfo.Address1   );
		pIni->WriteString (Section,COMPANY_INFO_ADDRESS2   ,pInfo.Address2   );
		pIni->WriteString (Section,COMPANY_INFO_TEL        ,pInfo.TEL        );
		pIni->WriteString (Section,COMPANY_INFO_FAX        ,pInfo.FAX        );
		pIni->WriteString (Section,COMPANY_INFO_TRANSFER1  ,pInfo.Transfer1  );
		pIni->WriteString (Section,COMPANY_INFO_TRANSFER2  ,pInfo.Transfer2  );
		pIni->WriteString (Section,COMPANY_INFO_TAXRATIO   ,pInfo.TaxRatio   );
	}
	return true;
}
