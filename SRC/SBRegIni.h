//---------------------------------------------------------------------------
#ifndef SBRegIniH
#define SBRegIniH
//---------------------------------------------------------------------------
#include <Registry.hpp>

class SBRegIni : public TRegistryIniFile
{
public:
	__fastcall SBRegIni();
	__fastcall SBRegIni(const String& FileName);
	__fastcall ~SBRegIni();
};

//èëóﬁóöó
class SBHistRegIni : public TRegistryIniFile
{
public:
	__fastcall SBHistRegIni();
	__fastcall ~SBHistRegIni();
};

#endif
