//---------------------------------------------------------------------------
#ifndef SBRegIniH
#define SBRegIniH
//---------------------------------------------------------------------------
#include <string>
#include <Registry.hpp>

class SBRegIni : public TRegistryIniFile
{
public:
	__fastcall SBRegIni();
	__fastcall SBRegIni(const String& FileName);
	__fastcall ~SBRegIni();
public:
	virtual void __fastcall WriteString(const std::wstring& Section, const std::wstring& Ident, const std::wstring& Value)
	{
		TRegistryIniFile::WriteString(Section.c_str(),Ident.c_str(),Value.c_str());
	}
	virtual std::wstring __fastcall ReadString(const std::wstring& Section, const std::wstring& Ident, const std::wstring& Default)
	{
		String res = TRegistryIniFile::ReadString(Section.c_str(),Ident.c_str(),Default.c_str());

		return std::wstring(res.c_str());
	}
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
