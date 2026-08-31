//---------------------------------------------------------------------------
#include<vcl.h>
#pragma hdrstop

#include "SeikyuBConst.h"
#include "SBRegIni.h"
#include "TReopen.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
//再開処理情報を得る
//---------------------------------------------------------------------------
bool TReopen::LoadReopenSet(TReopen& ReopenInf)
{
	String  KeySdo;
	String  KeyHist;

	//Regｵｰﾌﾟﾝ
	std::unique_ptr<SBRegIni> Ini(new SBRegIni);
	//再開処理の有無をセット
	bool IsReopen = Ini->ReadBool(INI_DEF_REOPEN,INI_ROP_ISREOPEN,false);
	//再開ファイルの情報セット
	ReopenInf.sdoPath = Ini->ReadString(INI_DEF_REOPEN,INI_ROP_SDOPATH,L"");
	ReopenInf.histID  = Ini->ReadString(INI_DEF_REOPEN,INI_ROP_HISTID,L"");

	return IsReopen;
}
//-------------------------------------------------------------
//再開処理情報をセット
//-------------------------------------------------------------
bool TReopen::SaveReopenSet(bool IsReopen,const TReopen& reopenInf)
{
	String KeySdo;
	String KeyHist;
	//Regｵｰﾌﾟﾝ
	std::unique_ptr<SBRegIni> Ini(new SBRegIni);
	//再開処理の有無をセット
	Ini->WriteBool   (INI_DEF_REOPEN,INI_ROP_ISREOPEN,IsReopen);
	//再開ファイルの情報セット
	Ini->WriteString(INI_DEF_REOPEN,INI_ROP_SDOPATH,reopenInf.sdoPath);
	Ini->WriteString(INI_DEF_REOPEN,INI_ROP_HISTID ,reopenInf.histID);

	return true;
}

