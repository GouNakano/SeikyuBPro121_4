//---------------------------------------------------------------------------
#ifndef TCompanyInfosH
#define TCompanyInfosH
//---------------------------------------------------------------------------

//自社情報の数
constexpr const int COMPANY_INFO_NUM = 3;

//自社情報の定義
struct typCompanyInfoDef
{
	std::wstring CompanyName;  //会社名
	std::wstring Represent;    //代表者
	std::wstring ZipNumber;    //郵便番号
	std::wstring Address1;     //住所１
	std::wstring Address2;     //住所２
	std::wstring TEL;          //電話番号
	std::wstring FAX;          //FAX番号
	std::wstring Transfer1;    //振込先１
	std::wstring Transfer2;    //振込先２
	std::wstring TaxRatio;     //消費税率
public:
	//コンストラクタ
	typCompanyInfoDef() = default;
	//コピーコンストラクタ
	typCompanyInfoDef(const typCompanyInfoDef& h) = default;
};

//自社情報のリスト定義
class TCompanyInfos
{
private:
	//自社情報の配列
	typCompanyInfoDef CompanyInfo[COMPANY_INFO_NUM];
public:
	//自社情報の取得
	typCompanyInfoDef& operator[] (int idx);
public:
	//自社情報の読み込み
	bool ReadCompanyInfo();
	//自社情報の保存
	bool SaveCompanyInfo();
};

#endif
