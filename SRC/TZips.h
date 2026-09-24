//---------------------------------------------------------------------------
#ifndef TZipsH
#define TZipsH
//---------------------------------------------------------------------------
#include<map>

//郵便番号のデータ
struct typZip
{
	std::wstring ZipCode;    //郵便番号
	std::wstring Prefecture; //都道府県
	std::wstring City;       //市町村
	std::wstring Address;    //住所
public:
	//コンストラクタ
	typZip() = default;
	//コピーコンストラクタ
	typZip(const typZip& him) = default;
	//移譲コンストラクタ
	typZip(typZip&& him) = default;
	//キーコンストラクタ
	typZip(const String& key)
	:typZip()
	{
		ZipCode = key;
	}

public:
	//代入
	typZip& operator = (const typZip& Him) = default;
	//移譲代入
	typZip& operator = (typZip&& Him) = default;
public:
	//比較
	bool operator == (const typZip& Him)const{return ZipCode == Him.ZipCode;}
	bool operator  > (const typZip& Him)const{return ZipCode  > Him.ZipCode;}
};

//郵便番号のデータリスト
class TZips
{
private:
	//郵便番号をキーにした郵便番号データMAP
	std::map<std::wstring,typZip> zipList;
public:
	//コンストラクタ
	TZips() = default;
public:
	//数字だけの郵便番号を整形
	static bool modifyZipStr(const std::wstring& in_digi_zip,std::wstring& out_digi_zip);
public:
	//消去
	bool clear();
	//郵便番号CSVから読み込み
	bool load();
	//郵便番号から住所を得る
	bool getAdress(const std::wstring& zipCode,std::wstring& prefecture,std::wstring& city,std::wstring& address);
};

//郵便番号のデータリスト
extern TZips Zips;


#endif
