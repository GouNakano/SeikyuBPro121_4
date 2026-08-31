//---------------------------------------------------------------------------
#ifndef TZipsH
#define TZipsH
//---------------------------------------------------------------------------
#include<map>

//郵便番号のデータ
struct typZip
{
	String ZipCode;    //郵便番号
	String Prefecture; //都道府県
	String City;       //市町村
	String Address;    //住所
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
	std::map<String,typZip> zipList;
public:
	//コンストラクタ
	TZips() = default;
public:
	//消去
	bool clear();
	//郵便番号CSVから読み込み
	bool load();
	//郵便番号から住所を得る
	bool getAdress(const String& zipCode,String& prefecture,String& city,String& address);
};

//郵便番号のデータリスト
extern TZips Zips;


#endif
