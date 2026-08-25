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

//èëóﬁóöó
__fastcall SBHistRegIni::SBHistRegIni()
: TRegistryIniFile(INI_REG_HIST_ROOT)
{
}

__fastcall SBHistRegIni::~SBHistRegIni()
{
}


