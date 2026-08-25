//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <fstream>
#include <filesystem>

#include <openssl/rsa.h>
#include <openssl/engine.h>
#include <openssl/err.h>
#include <openssl/rc4.h>

#include "nsDouble.h"
#include "strconv.h"
#include "wstr.h"
#include "MainFrm.h"
#include "nsShellApi.h"
#include "TSFileCL.h"
#include "SeikyuBDef.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


//標準列情報
typStdColumnDef StdColumn[STD_COLUMN_NUM] = {
	{L"項目"   ,taCenter      },
	{L"品目名" ,taLeftJustify },
	{L"数量"   ,taRightJustify},
	{L"単位"   ,taCenter      },
	{L"単価"   ,taRightJustify},
	{L"金額"   ,taRightJustify}
};



//----- 共通変数定義 -----
//住所リスト
std::map<String,typZip> ZipList;
//初回使用フラグ
bool IsFirstUse;
//ライセンス文字列
String LicenseStr;

//前回の書類ファイルパス
String RecentReportFile;
//請求書番頭の設定
typSBSetting ES;
//繰り返し入力用ﾘｽﾄｸﾗｽのｵﾌﾞｼﾞｪｸﾄ
ClsInputDataList Inpts;

//=============================================================
//
//  ｼｽﾃﾑ名称 ：
//
//  名前空間 ：
//
//  クラス名 ：
//
//  機能     ：共通関数
//
//  継承元   ：
//
//  作成者   ：
//
//  改定者   ：
//
//=============================================================


//-------------------------------------------------------------
//  機能     ：入力文字列に対して半角にします
//
//  関数定義 ：std::string StrToHan(std::string Str)
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
std::string sbp::StrToHan(std::string Str)
{
	nsArray<wchar_t> wStrBuf;
	wchar_t          hs[3];
	String           RStr;
	wchar_t          Nterm = 0;
	//WideStringにする
	String WStr(Str.c_str());
	//一文字ずつ変換
	wchar_t *pWS = WStr.c_str();

	while(*pWS != 0)
	{
		//半角に変換
		wsstr::wsZenToHan(*pWS,hs);

		wStrBuf.Add(hs[0]);

		if(hs[1] != 0)
		{
			wStrBuf.Add(hs[1]);
		}
		pWS++;
	}
	wStrBuf.Add(Nterm);

	//通常文字列に復帰
	return wide_to_ansi(&(wStrBuf[0]));
}

//-------------------------------------------------------------
//  機能     ：郵便番号から住所を得る
//
//  関数定義 ：bool GetAdressFromZipCode(String ZipCode,String& Prefecture,String& City,String& Address)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
bool sbp::GetAdressFromZipCode(String ZipCode,String& Prefecture,String& City,String& Address)
{
	//検索
	decltype(ZipList)::iterator find_iter = ZipList.find(ZipCode);
	//見つかったか？
	if(find_iter == ZipList.end())
	{
		return false;
	}
	//データセット
	typZip& find = find_iter->second;

	Prefecture = find.Prefecture;
	City       = find.City;
	Address    = find.Address;

	return true;
}
//-------------------------------------------------------------
//  機能     ：郵便番号情報を読み込む
//
//  関数定義 ：bool ReadZipList()
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
bool sbp::ReadZipList()
{
	//自分のﾌﾙﾊﾟｽを得る
	String MyPath = ExtractFileDir(ParamStr(0));
	//住所ﾌｧｲﾙのﾌﾙﾊﾟｽ
	String FullPath = MyPath + ZIP_CODE_CSV;
	//ファイルを開く
	std::filesystem::path filepath = FullPath.c_str();
	std::ifstream ifs(filepath);

	//リスト消去
	ZipList.clear();
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
		ZipList[Zip.ZipCode] = std::move(Zip);
	}
	//閉じる
	ifs.close();

	return true;
}
//-------------------------------------------------------------
//  機能     ：ライセンス状態
//
//  関数定義 ：bool CheckLicenceEnable()
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
bool sbp::CheckLicenceEnable()
{
	bool IsLicOk = (MainForm->LicenseSettingBtn->Visible == false);

	return IsLicOk;
}
//-------------------------------------------------------------
//  機能     ：自社情報の読み込み
//
//  関数定義 ：bool ReadCompanyInfo()
//
//  ｱｸｾｽﾚﾍﾞﾙ ：public
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
bool sbp::ReadCompanyInfo()
{
	String Section;
	//レジストリを開く
	std::unique_ptr<SBRegIni> pIni(new SBRegIni);
	//自社情報の数だけ読み込む
	for(int Cnt = 1;Cnt <= COMPANY_INFO_NUM;Cnt++)
	{
		//レジストリキー(セクション)作成
		Section.sprintf(C_KEY_COMPANY_INFO,Cnt);
		//対象データ
		typCompanyInfoDef *pInfo = &CompanyInfo[Cnt-1];
		//データ読み込み
		pInfo->CompanyName = pIni->ReadString (Section,COMPANY_INFO_COMPANYNAME,"");
		pInfo->Represent   = pIni->ReadString (Section,COMPANY_INFO_REPRESENT  ,"");
		pInfo->ZipNumber   = pIni->ReadString (Section,COMPANY_INFO_ZIPNUMBER  ,"");
		pInfo->Address1    = pIni->ReadString (Section,COMPANY_INFO_ADDRESS1   ,"");
		pInfo->Address2    = pIni->ReadString (Section,COMPANY_INFO_ADDRESS2   ,"");
		pInfo->TEL         = pIni->ReadString (Section,COMPANY_INFO_TEL        ,"");
		pInfo->FAX         = pIni->ReadString (Section,COMPANY_INFO_FAX        ,"");
		pInfo->Transfer1   = pIni->ReadString (Section,COMPANY_INFO_TRANSFER1  ,"");
		pInfo->Transfer2   = pIni->ReadString (Section,COMPANY_INFO_TRANSFER2  ,"");
		pInfo->TaxRatio    = pIni->ReadString (Section,COMPANY_INFO_TAXRATIO   ,STD_TAXRATIO);
	}

	return true;
}
//-------------------------------------------------------------
//  機能     ：自社情報の保存
//
//  関数定義 ：bool SaveCompanyInfo()
//
//  ｱｸｾｽﾚﾍﾞﾙ ：public
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
bool sbp::SaveCompanyInfo()
{
	String Section;
	//レジストリを開く
	std::unique_ptr<SBRegIni> pIni(new SBRegIni);
	//自社情報の数だけ読み込む
	for(int Cnt = 1;Cnt <= COMPANY_INFO_NUM;Cnt++)
	{
		//レジストリキー(セクション)作成
		Section.sprintf(C_KEY_COMPANY_INFO,Cnt);
		//対象データ
		typCompanyInfoDef *pInfo = &CompanyInfo[Cnt-1];
		//データ読み込み
		pIni->WriteString (Section,COMPANY_INFO_COMPANYNAME,pInfo->CompanyName);
		pIni->WriteString (Section,COMPANY_INFO_REPRESENT  ,pInfo->Represent  );
		pIni->WriteString (Section,COMPANY_INFO_ZIPNUMBER  ,pInfo->ZipNumber  );
		pIni->WriteString (Section,COMPANY_INFO_ADDRESS1   ,pInfo->Address1   );
		pIni->WriteString (Section,COMPANY_INFO_ADDRESS2   ,pInfo->Address2   );
		pIni->WriteString (Section,COMPANY_INFO_TEL        ,pInfo->TEL        );
		pIni->WriteString (Section,COMPANY_INFO_FAX        ,pInfo->FAX        );
		pIni->WriteString (Section,COMPANY_INFO_TRANSFER1  ,pInfo->Transfer1  );
		pIni->WriteString (Section,COMPANY_INFO_TRANSFER2  ,pInfo->Transfer2  );
		pIni->WriteString (Section,COMPANY_INFO_TAXRATIO   ,pInfo->TaxRatio   );
	}
	return true;
}
//-------------------------------------------------------------
//  機能     ：メインフォーム設定読み込み
//
//  関数定義 ：void LoadMainFormSet()
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
void sbp::LoadMainFormSet()
{
	String Section;

	//メインフォームを得る
	TMainForm *M = MainForm;
	//自分のﾌﾙﾊﾟｽを得る
	String MyPath = ParamStr(0);
	//自分の存在するﾃﾞｨﾚｸﾄﾘ
	String MyDir  = ExtractFileDir(MyPath);
	//EXEの場所をカレントディレクトリにする
	SetCurrentDir(MyDir);

	//Iniﾌｧｲﾙｵｰﾌﾟﾝ
	std::unique_ptr<SBRegIni> pReg(new SBRegIni());
	//EXEの位置とバージョンをレジストリに書く
	pReg->WriteString(C_SYSTEM_SETTING,V_INSTALL_EXE,MyPath);
	//初回起動か？
	IsFirstUse       = pReg->ReadBool(C_SYSTEM_SETTING,V_IS_FIRST,true);
	//ライセンス文字列
	LicenseStr       = pReg->ReadString(C_SYSTEM_SETTING,LICENSE_STRING,L"");
	//前回の書類パス
	RecentReportFile = pReg->ReadString(C_SYSTEM_SETTING,V_RECENT_REPORT,L"");
	//レジストリから各部のデータセット
	M->Top           = pReg->ReadInteger(C_SYSTEM_SETTING,V_WINDOW_TOP ,4);
	M->Left          = pReg->ReadInteger(C_SYSTEM_SETTING,V_WINDOW_LEFT,50);
	M->Width         = pReg->ReadInteger(C_SYSTEM_SETTING,V_WINDOW_WIDTH ,900);
	M->Height        = pReg->ReadInteger(C_SYSTEM_SETTING,V_WINDOW_HEIGHT,756);
}
//-------------------------------------------------------------
//  機能     ：Iniにフォント設定の情報をセット
//
//  関数定義 ：void SetColInfToIni(TMemIniFile *Ini,String Sec,String Val,typFontDef& ECol)
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
//void sbp::SetColInfToIni(TMemIniFile *Ini,String Sec,String Val,typFontDef& ECol)
//{
//	String Str;
//	//セットする文字列作成
//	Str.sprintf(L"%s,%d,%d,%d,%d,%d",
//		ECol.Name.c_str(),
//		ECol.Size,
//		(int)ECol.Color,
//		(ECol.Bold == true),
//		(ECol.Italic == true),
//		(ECol.Under == true)
//	);
//	//文字列をセットする
//	Ini->WriteString(Sec,Val,Str);
//}
//-------------------------------------------------------------
//  機能     ：ディスクシリアル文字列を得る
//
//  関数定義 ：String GetDiskSerialString()
//
//  ｱｸｾｽﾚﾍﾞﾙ ：public
//
//  引数     ：
//
//  戻り値   ：true Ok
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
String sbp::GetDiskSerialString()
{
	wchar_t VolumeName[1000];
	wchar_t SystemName[1000];
	DWORD   SerialNumber;
	DWORD   FileNameLength;
	DWORD   Flags;
	String  Str;

	//Cドライブの情報を得る
	GetVolumeInformationW(
		L"C:\\",
		VolumeName,
		1000,
		&SerialNumber,
		&FileNameLength,
		&Flags,
		SystemName,
		1000);
	//ディスクシリアル文字列を作成
	Str.sprintf(DISK_SERIAL_STRING,SerialNumber);

	return Str;
}
//-------------------------------------------------------------
//  機能     ：請求書番頭の設定読み込み
//
//  関数定義 ：void LoadSBSet(typSBSetting& ES,bool Default)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：typEditSetting& ES      取得したエディット設定
//             bool            Default ==true インストール時設定 ==false 現在の設定
//  戻り値   ：
//
//  作成者　 ：中野
//
//  改定者   ：
//-------------------------------------------------------------
void sbp::LoadSBSet(typSBSetting& ES,bool Default)
{
	std::unique_ptr<SBRegIni> Ini;

	if(Default == false)
	{
		Ini.reset(new SBRegIni);
	}
	else
	{
		Ini.reset(new SBRegIni(L""));
	}

	//構造体にデータをセット
	//共通定義
	ES.IsRemain        = Ini->ReadBool   (INI_SETTING_SECTION,INI_ISREMAIN          ,true);    //前回の状態を再現
	ES.BackupFile      = Ini->ReadBool   (INI_SETTING_SECTION,INI_BACKUPFILE        ,true);    //バックアップファイルの作成
	ES.UseTemplateFile = Ini->ReadBool   (INI_SETTING_SECTION,INI_USE_TEMPLATE      ,false);   //新規作成時のテンプレートファイルの使用
	ES.TemplateFile    = Ini->ReadString (INI_SETTING_SECTION,INI_TEMPLATE_FILE     ,"");      //新規作成時のテンプレートファイル
	ES.IsToday         = Ini->ReadBool   (INI_SETTING_SECTION,INI_SET_TODAY         ,true);    //新規作成時、本日の日付をセットするか
	ES.RateTyp1        = (TValuateType)Ini->ReadInteger(INI_SETTING_SECTION,INIKEY_RATE_TYP01     ,tOmit);   //丸めタイプ１
	ES.AccuracyR1      = Ini->ReadInteger(INI_SETTING_SECTION,INIKEY_RATE_ACCURACY01,0);       //小数点以下精度
	ES.RateTyp2        = (TValuateType)Ini->ReadInteger(INI_SETTING_SECTION,INIKEY_RATE_TYP02     ,tOmit);   //丸めタイプ
	ES.AccuracyR2      = Ini->ReadInteger(INI_SETTING_SECTION,INIKEY_RATE_ACCURACY02,0);       //小数点以下精度
	ES.RateTyp3        = (TValuateType)Ini->ReadInteger(INI_SETTING_SECTION,INIKEY_RATE_TYP03     ,tOmit);   //丸めタイプ
	ES.AccuracyR3      = Ini->ReadInteger(INI_SETTING_SECTION,INIKEY_RATE_ACCURACY03,0);       //小数点以下精度
	ES.RateTyp4        = (TValuateType)Ini->ReadInteger(INI_SETTING_SECTION,INIKEY_RATE_TYP04     ,tOmit);   //丸めタイプ
	ES.AccuracyR4      = Ini->ReadInteger(INI_SETTING_SECTION,INIKEY_RATE_ACCURACY04,0);       //小数点以下精度
	ES.RateTyp5        = (TValuateType)Ini->ReadInteger(INI_SETTING_SECTION,INIKEY_RATE_TYP05     ,tOmit);   //丸めタイプ
	ES.AccuracyR5      = Ini->ReadInteger(INI_SETTING_SECTION,INIKEY_RATE_ACCURACY05,0);       //小数点以下精度
}
//-------------------------------------------------------------
//  機能     ：請求書番頭の設定保存
//
//  関数定義 ：void SaveSBSet()
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
void sbp::SaveSBSet()
{
	std::unique_ptr<SBRegIni> Ini(new SBRegIni);

	//構造体にデータをセット
	//共通定義
	Ini->WriteBool   (INI_SETTING_SECTION,INI_ISREMAIN          ,(ES.IsRemain == true));        //前回の状態を再現
	Ini->WriteBool   (INI_SETTING_SECTION,INI_BACKUPFILE        ,(ES.BackupFile == true));      //バックアップファイルの作成
	Ini->WriteBool   (INI_SETTING_SECTION,INI_USE_TEMPLATE      ,(ES.UseTemplateFile == true)); //新規作成時のテンプレートファイルの使用
	Ini->WriteString (INI_SETTING_SECTION,INI_TEMPLATE_FILE     ,ES.TemplateFile);    //新規作成時のテンプレートファイル
	Ini->WriteBool   (INI_SETTING_SECTION,INI_SET_TODAY         ,(ES.IsToday == true));         //新規作成時、本日の日付をセットするか
	Ini->WriteInteger(INI_SETTING_SECTION,INIKEY_RATE_TYP01     ,ES.RateTyp1);        //丸めタイプ１
	Ini->WriteInteger(INI_SETTING_SECTION,INIKEY_RATE_ACCURACY01,ES.AccuracyR1);      //小数点以下精度
	Ini->WriteInteger(INI_SETTING_SECTION,INIKEY_RATE_TYP02     ,ES.RateTyp2);        //丸めタイプ
	Ini->WriteInteger(INI_SETTING_SECTION,INIKEY_RATE_ACCURACY02,ES.AccuracyR2);      //小数点以下精度
	Ini->WriteInteger(INI_SETTING_SECTION,INIKEY_RATE_TYP03     ,ES.RateTyp3);        //丸めタイプ
	Ini->WriteInteger(INI_SETTING_SECTION,INIKEY_RATE_ACCURACY03,ES.AccuracyR3);      //小数点以下精度
	Ini->WriteInteger(INI_SETTING_SECTION,INIKEY_RATE_TYP04     ,ES.RateTyp4);        //丸めタイプ
	Ini->WriteInteger(INI_SETTING_SECTION,INIKEY_RATE_ACCURACY04,ES.AccuracyR4);      //小数点以下精度
	Ini->WriteInteger(INI_SETTING_SECTION,INIKEY_RATE_TYP05     ,ES.RateTyp5);        //丸めタイプ
	Ini->WriteInteger(INI_SETTING_SECTION,INIKEY_RATE_ACCURACY05,ES.AccuracyR5);      //小数点以下精度
}
//-------------------------------------------------------------
//  機能     ：再開処理情報を得る
//
//  関数定義 ：void LoadReopenSet(bool& IsReopen,std::vector<typReopen>& ReopenInf)
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
void sbp::LoadReopenSet(bool& IsReopen,std::vector<typReopen>& ReopenInf)
{
	String  Key;

	//Regｵｰﾌﾟﾝ
	std::unique_ptr<SBRegIni> Ini(new SBRegIni);
	//再開処理の有無をセット
	IsReopen = Ini->ReadBool(INI_DEF_REOPEN,INI_ROP_ISREOPEN,false);
	//再開処理数
	long ReopNum = Ini->ReadInteger(INI_DEF_REOPEN,INI_ROP_OPENNUM,0);

	//再開ファイルの情報セット
	for(int Cnt = 0;Cnt < ReopNum;Cnt++)
	{
		//キーの作成
		Key.sprintf(INI_ROP_PATHURL,Cnt + 1);
		//ファイルまたはパスを得る
		String PhURL = Ini->ReadString(INI_DEF_REOPEN,Key,"");
		//チェック
		if(PhURL == L"")
		{
			continue;
		}
		//情報構造体作成
		typReopen Inf;
		//データセット
		Inf.IsURL    = false;
		Inf.PathURL  = PhURL.c_str();
		//リストに追加
		ReopenInf.push_back(std::move(Inf));
	}
}
//-------------------------------------------------------------
//  機能     ：再開処理情報をセット
//
//  関数定義 ：void SaveReopenSet(bool IsReopen,std::vector<typReopen>& ReopenInf)
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
void sbp::SaveReopenSet(bool IsReopen,std::vector<typReopen>& ReopenInf)
{
	String Key;
	String Val;
	//Regｵｰﾌﾟﾝ
	std::unique_ptr<SBRegIni> Ini(new SBRegIni);
	//再開処理の有無をセット
	Ini->WriteBool   (INI_DEF_REOPEN,INI_ROP_ISREOPEN ,(IsReopen == true));
	//再開処理数
	Ini->WriteInteger(INI_DEF_REOPEN,INI_ROP_OPENNUM ,ReopenInf.size());

	//再開ファイルの情報セット
	for(int Cnt = 0;Cnt < ReopenInf.size();Cnt++)
	{
		//パスの作成
		Val.sprintf(L"%s",ReopenInf[Cnt].PathURL.c_str());
		//キーの作成
		Key.sprintf(INI_ROP_PATHURL,Cnt + 1);
		//書き込み
		Ini->WriteString(INI_DEF_REOPEN,Key,Val);
	}
}

