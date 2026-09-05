//---------------------------------------------------------------------------
#pragma hdrstop

#include "SeikyuBConst.h"
#include "SBRegIni.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall SBRegIni::SBRegIni()
	: TRegistryIniFile(INI_REG_ROOT)
{
}

__fastcall SBRegIni::SBRegIni(const String& FileName)
: TRegistryIniFile(FileName)
{
}

__fastcall SBRegIni::~SBRegIni()
{
}

//書類履歴
__fastcall SBHistRegIni::SBHistRegIni()
: TRegistryIniFile(INI_REG_HIST_ROOT)
{
}

__fastcall SBHistRegIni::~SBHistRegIni()
{
}

//レジストリ関連名前空間
namespace regsp
{

//初回起動か？
bool getIsFirstUse()
{
	std::unique_ptr<SBRegIni> pReg(new SBRegIni);

	return pReg->ReadBool(C_SYSTEM_SETTING,V_IS_FIRST,true);
}
//初回起動フラグセット
bool setIsFirstUse(bool first)
{
	std::unique_ptr<SBRegIni> pReg(new SBRegIni);

	pReg->WriteBool(C_SYSTEM_SETTING,V_IS_FIRST,first);

	return true;
}

}
