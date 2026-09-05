//---------------------------------------------------------------------------
#ifndef TStdComponentsH
#define TStdComponentsH
//---------------------------------------------------------------------------
#include <map>
#include "nsBitmap.h"
#include "SeikyuBConst.h"
#include "TDocKinds.h"
//標準コンポーネントの数
constexpr const int STD_COMPONENT_NUM = 49;

//標準コンポーネントの定義
struct typStdComponentDef
{
public:
	scStdComponent   Number;     //コンポーネント番号
	const wchar_t   *Name;       //名前
	dcDocComponent   CompoKind;  //コンポーネント種別
	dtypCompo        Type;       //書類部品のデータ型
	TAlignment       Alignment;  //整列方法
	bool             Border;     //枠の有無
	const wchar_t   *Value;      //初期内容
	const wchar_t   *NoCaption;  //内容が空の時の代替表示文字列
	const wchar_t   *Explain;    //説明(ヒント)
	bool             Visible;    //初期表示するか
public:
	//コンストラクタ
	typStdComponentDef() = default;
	//コピーコンストラクタ
	typStdComponentDef(const typStdComponentDef& h) = default;
public:
	//代入演算子
	typStdComponentDef& operator = (const typStdComponentDef& h) = default;
};

//標準コンポーネント
constexpr const typStdComponentDef StdComponents[STD_COMPONENT_NUM] = {
	{scBillLabel          ,L"BillLabel"          ,dcLabel     ,dtyString ,taLeftJustify ,false,L"請 求 書"                    ,L"<書類種類名>"  ,L"書類種類名ラベル",true},
	{scYearLabel          ,L"YearLabel"          ,dcLabel     ,dtyString ,taLeftJustify ,false,L"年"                          ,L"<年>"          ,L"年ラベル"        ,true},
	{scMonthLabel         ,L"MonthLabel"         ,dcLabel     ,dtyString ,taLeftJustify ,false,L"月"                          ,L"<月>"          ,L"月ラベル"        ,true},
	{scDayLabel           ,L"DayLabel"           ,dcLabel     ,dtyString ,taLeftJustify ,false,L"日"                          ,L"<日>"          ,L"日ラベル"        ,true},
	{scNumberLabel        ,L"NumberLabel"        ,dcLabel     ,dtyString ,taLeftJustify ,false,L"No."                         ,L"<書類番号>"    ,L"書類番号ラベル"  ,true},
	{scHonorificTitleLabel,L"HonorificTitleLabel",dcLabel     ,dtyString ,taLeftJustify ,false,L"様"                          ,L"<敬称>"        ,L"敬称ラベル"      ,true},
	{scRequestLabel       ,L"RequestLabel"       ,dcLabel     ,dtyString ,taLeftJustify ,false,L"下記の通りご請求申し上げます",L"<用件>"        ,L"用件ラベル"      ,true},
	{scTitleLabel         ,L"TitleLabel"         ,dcLabel     ,dtyString ,taLeftJustify ,false,L"件名"                        ,L"<件名>"        ,L"件名ラベル"      ,true},
	{scChargedAmountLabel ,L"ChargedAmountLabel" ,dcLabel     ,dtyString ,taLeftJustify ,false,L"ご請求金額"                  ,L"<金額>"        ,L"金額ラベル"      ,true},
	{scCompanyNameLabel   ,L"CompanyNameLabel"   ,dcLabel     ,dtyString ,taRightJustify,false,L""                            ,L"<会社名>"      ,L"会社名ラベル"    ,true},
	{scPersonLabel        ,L"PersonLabel"        ,dcLabel     ,dtyString ,taRightJustify,false,L""                            ,L"<代表者>"      ,L"代表者ラベル"    ,true},
	{scZipCodeLabel       ,L"ZipCodeLabel"       ,dcLabel     ,dtyString ,taRightJustify,false,L""                            ,L"<郵便番号>"    ,L"郵便番号ラベル"  ,true},
	{scAddressLabel1      ,L"AddressLabel1"      ,dcLabel     ,dtyString ,taRightJustify,false,L""                            ,L"<住所1>"       ,L"住所１ラベル"    ,true},
	{scAddressLabel2      ,L"AddressLabel2"      ,dcLabel     ,dtyString ,taRightJustify,false,L""                            ,L"<住所2>"       ,L"住所２ラベル"    ,true},
	{scTELLabel           ,L"TELLabel"           ,dcLabel     ,dtyString ,taRightJustify,false,L""                            ,L"<電話番号>"    ,L"電話番号ラベル"  ,true},
	{scFAXLabel           ,L"FAXLabel"           ,dcLabel     ,dtyString ,taRightJustify,false,L""                            ,L"<FAX番号>"     ,L"ＦＡＸ番号ラベル",true},
	{scUnitLabel          ,L"UnitLabel"          ,dcLabel     ,dtyString ,taLeftJustify ,false,L"単位:円"                     ,L"<単位>"        ,L"単位ラベル"      ,true},
	{scSubTotalLabel      ,L"SubTotalLabel"      ,dcLabel     ,dtyString ,taCenter      ,true ,L"小計"                        ,L"<小計>"        ,L"小計ラベル"      ,true},
	{scTaxLabel           ,L"TaxLabel"           ,dcLabel     ,dtyString ,taCenter      ,true ,L"消費税"                      ,L"<消費税>"      ,L"消費税ラベル"    ,true},
	{scTotalLabel         ,L"TotalLabel"         ,dcLabel     ,dtyString ,taCenter      ,true ,L"合計金額"                    ,L"<合計金額>"    ,L"合計金額ラベル"  ,true},
	{scNoteLabel          ,L"NoteLabel"          ,dcLabel     ,dtyString ,taLeftJustify ,false,L"備考"                        ,L"<備考>"        ,L"備考ラベル"      ,true},
	{scTransferLabel1     ,L"TransferLabel1"     ,dcLabel     ,dtyString ,taLeftJustify ,false,L"振込先:"                     ,L"<振込先1>"     ,L"振込先１ラベル"  ,true},
	{scTransferLabel2     ,L"TransferLabel2"     ,dcLabel     ,dtyString ,taLeftJustify ,false,L"振込先:"                     ,L"<振込先2>"     ,L"振込先２ラベル"  ,true},
	{scYearEdit           ,L"YearEdit"           ,dcDayEdit   ,dtyInteger,taLeftJustify ,false,L""                            ,L"[年]"          ,L"年入力"          ,true},
	{scMonthEdit          ,L"MonthEdit"          ,dcDayEdit   ,dtyInteger,taLeftJustify ,false,L""                            ,L"[月]"          ,L"月入力"          ,true},
	{scDayEdit            ,L"DayEdit"            ,dcDayEdit   ,dtyInteger,taLeftJustify ,false,L""                            ,L"[日]"          ,L"日入力"          ,true},
	{scNoEdit             ,L"NoEdit"             ,dcEdit      ,dtyString ,taRightJustify,false,L""                            ,L"[書類番号]"    ,L"書類番号入力"    ,true},
	{scNameEdit           ,L"NameEdit"           ,dcEdit      ,dtyString ,taLeftJustify ,false,L""                            ,L"[名前]"        ,L"名前入力"        ,true},
	{scItemEdit           ,L"ItemEdit"           ,dcEdit      ,dtyString ,taLeftJustify ,false,L""                            ,L"[件名]"        ,L"件名入力"        ,true},
	{scMoneyEdit          ,L"MoneyEdit"          ,dcMoneyEdit ,dtyReal   ,taRightJustify,false,L""                            ,L"[金額]"        ,L"金額入力"        ,true},
	{scSubtotalEdit       ,L"SubtotalEdit"       ,dcMoneyEdit ,dtyReal   ,taRightJustify,true ,L""                            ,L"[小計]"        ,L"小計入力"        ,true},
	{scTaxEdit            ,L"TaxEdit"            ,dcMoneyEdit ,dtyReal   ,taRightJustify,true ,L""                            ,L"[消費税]"      ,L"消費税入力"      ,true},
	{scTotalEdit          ,L"TotalEdit"          ,dcMoneyEdit ,dtyReal   ,taRightJustify,true ,L""                            ,L"[合計金額]"    ,L"合計金額入力"    ,true},
	{scStampImage1        ,L"StampImage1"        ,dcImage     ,dtyImage  ,taCenter	    ,true ,L""                            ,L""              ,L"印影画像１"      ,true},
	{scStampImage2        ,L"StampImage2"        ,dcImage     ,dtyImage  ,taCenter	    ,true ,L""                            ,L""              ,L"印影画像２"      ,true},
	{scLogoImage          ,L"LogoImage"          ,dcImage     ,dtyImage  ,taCenter	    ,false,L""                            ,L""              ,L"ロゴ画像"        ,true},
	{::scGrid             ,L"Grid"               ,dcGrid      ,dtyGrid   ,taLeftJustify ,false,L""                            ,L""              ,L"表入力"          ,true},
	{scDayUnderShape      ,L"DayUnderShape"      ,dcCLine     ,dtyShape  ,taLeftJustify ,false,L""                            ,L""              ,L"書類種類名下線"  ,true},
	{scNumberShape        ,L"NumberShape"        ,dcCLine     ,dtyShape  ,taLeftJustify ,false,L""                            ,L""              ,L"書類番号下線"    ,true},
	{scItemShape          ,L"ItemShape"          ,dcCLine     ,dtyShape  ,taLeftJustify ,false,L""                            ,L""              ,L"件名下線"        ,true},
	{scMoneyShape         ,L"MoneyShape"         ,dcCLine     ,dtyShape  ,taLeftJustify ,false,L""                            ,L""              ,L"金額下線"        ,true},
	{scNoteShape          ,L"NoteShape"          ,dcCLine     ,dtyShape  ,taLeftJustify ,false,L""                            ,L""              ,L"備考下線"        ,true},
	{scNameUnderShape     ,L"NameUnderShape"     ,dcCLine     ,dtyShape  ,taLeftJustify ,false,L""                            ,L""              ,L"名前下線"        ,true},
	{scCustomerZipCodeEdit ,L"CustomerZipCodeEdit" ,dcEdit    ,dtyString ,taLeftJustify ,false,L""                            ,L"[客先郵便番号]",L"客先郵便番号"    ,false},
	{scCustomerAddress1Edit,L"CustomerAddress1Edit",dcEdit    ,dtyString ,taLeftJustify ,false,L""                            ,L"[客先住所1]"   ,L"客先住所１"      ,false},
	{scCustomerAddress2Edit,L"CustomerAddress2Edit",dcEdit    ,dtyString ,taLeftJustify ,false,L""                            ,L"[客先住所2]"   ,L"客先住所２"      ,false},
	{scCustomerTELEdit     ,L"CustomerTELEdit"     ,dcEdit    ,dtyString ,taLeftJustify ,false,L""                            ,L"[客先電話番号]",L"客先電話番号"    ,false},
	{scCustomerFAXEdit     ,L"CustomerFAXEdit"     ,dcEdit    ,dtyString ,taLeftJustify ,false,L""                            ,L"[客先FAX番号]" ,L"客先FAX番号"     ,false},
};

//---------------------------------------------------------------------------
//書類部品用汎用データクラス
//---------------------------------------------------------------------------
class TCompoData
{
public:
	dtypCompo type = dtyInteger;
public:
	int      int_val = 0;
	double   dbl_val = 0.0;
	String   str_val;
	nsBitmap bmp_val;
public:
	//コンストラクタ
	TCompoData() = default;
	//コピーコンストラクタ
	TCompoData(const TCompoData& h) = default;
public:
	//代入
	TCompoData& operator = (const TCompoData& h) = default;
public:
	//初期化
	bool clear()
	{
		*this = TCompoData();

		return true;
	}
};
//---------------------------------------------------------------------------
//書類部品処理クラス
//---------------------------------------------------------------------------
class TDocCompo
{
private:
	//標準コンポーネントオブジェクトのコンポーネント番号のMap
	std::map<scStdComponent,typStdComponentDef> StdCompNumberMap;
	//標準コンポーネントオブジェクトの名前のMap
	std::map<String,typStdComponentDef> StdNameMap;
public:
	//コンストラクタ
	TDocCompo();
public:
	//用紙種別を得る
	bool GetDocKindDefFromName(const String& DocKindName,typDocKindDef& kind);
	//コンポーネント名から標準コンポーネント情報を得る
	bool GetStdComponentDefFromName(const String& StdComponentName,typStdComponentDef& comp,const typProcMode docMode);
public:
	//コンポーネント名と標準コンポーネント番号からデータを得る
	bool getCompoData(scStdComponent sc,TCompoData& data);
	//MainPanelから指定Nameのコントロールを得る
	TControl *FindControlFromMainPanel(const String& Name);
	//コンポーネントの型を得る
	dcDocComponent GetComponentType(TComponent *pCompo);
};

//書類部品処理オブジェクト
extern TDocCompo compo;

#endif
