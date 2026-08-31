//---------------------------------------------------------------------------
#ifndef TCompanyInfosH
#define TCompanyInfosH
//---------------------------------------------------------------------------

//自社情報の数
constexpr const int COMPANY_INFO_NUM = 3;

//自社情報の定義
struct typCompanyInfoDef
{
	String CompanyName;  //会社名
	String Represent;    //代表者
	String ZipNumber;    //郵便番号
	String Address1;     //住所１
	String Address2;     //住所２
	String TEL;          //電話番号
	String FAX;          //FAX番号
	String Transfer1;    //振込先１
	String Transfer2;    //振込先２
	String TaxRatio;     //消費税率
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
