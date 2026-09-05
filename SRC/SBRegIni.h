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

//書類履歴
class SBHistRegIni : public TRegistryIniFile
{
public:
	__fastcall SBHistRegIni();
	__fastcall ~SBHistRegIni();
};

//レジストリ関連名前空間
namespace regsp
{
	//初回起動か？
	bool getIsFirstUse();
	//初回起動フラグセット
	bool setIsFirstUse(bool first);
}
#endif
