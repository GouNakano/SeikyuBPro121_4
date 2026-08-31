//---------------------------------------------------------------------------
#ifndef TStdComponentsH
#define TStdComponentsH
//---------------------------------------------------------------------------
#include "SeikyuBConst.h"
#include "TDocKinds.h"

//標準コンポーネントの数
constexpr const int STD_COMPONENT_NUM = 49;

//標準コンポーネントの定義
struct typStdComponentDef
{
	scStdComponent   Number;     //コンポーネント番号
	const wchar_t   *Name;       //名前
	dcDocComponent   Type;       //型
	TAlignment       Alignment;  //整列方法
	bool             Border;     //枠の有無
	const wchar_t   *Value;      //初期内容
	const wchar_t   *NoCaption;  //内容が空の時の代替表示文字列
	const wchar_t   *Explain;    //説明(ヒント)
	bool             Visible;    //初期表示するか
};

//標準コンポーネント
constexpr const typStdComponentDef StdComponents[STD_COMPONENT_NUM] = {
	{scBillLabel          ,L"BillLabel"          ,dcLabel     ,taLeftJustify ,false,L"請 求 書"                    ,L"<書類種類名>"  ,L"書類種類名ラベル",true},
	{scYearLabel          ,L"YearLabel"          ,dcLabel     ,taLeftJustify ,false,L"年"                          ,L"<年>"          ,L"年ラベル"        ,true},
	{scMonthLabel         ,L"MonthLabel"         ,dcLabel     ,taLeftJustify ,false,L"月"                          ,L"<月>"          ,L"月ラベル"        ,true},
	{scDayLabel           ,L"DayLabel"           ,dcLabel     ,taLeftJustify ,false,L"日"                          ,L"<日>"          ,L"日ラベル"        ,true},
	{scNumberLabel        ,L"NumberLabel"        ,dcLabel     ,taLeftJustify ,false,L"No."                         ,L"<書類番号>"    ,L"書類番号ラベル"  ,true},
	{scHonorificTitleLabel,L"HonorificTitleLabel",dcLabel     ,taLeftJustify ,false,L"様"                          ,L"<敬称>"        ,L"敬称ラベル"      ,true},
	{scRequestLabel       ,L"RequestLabel"       ,dcLabel     ,taLeftJustify ,false,L"下記の通りご請求申し上げます",L"<用件>"        ,L"用件ラベル"      ,true},
	{scTitleLabel         ,L"TitleLabel"         ,dcLabel     ,taLeftJustify ,false,L"件名"                        ,L"<件名>"        ,L"件名ラベル"      ,true},
	{scChargedAmountLabel ,L"ChargedAmountLabel" ,dcLabel     ,taLeftJustify ,false,L"ご請求金額"                  ,L"<金額>"        ,L"金額ラベル"      ,true},
	{scCompanyNameLabel   ,L"CompanyNameLabel"   ,dcLabel     ,taRightJustify,false,L""                            ,L"<会社名>"      ,L"会社名ラベル"    ,true},
	{scPersonLabel        ,L"PersonLabel"        ,dcLabel     ,taRightJustify,false,L""                            ,L"<代表者>"      ,L"代表者ラベル"    ,true},
	{scZipCodeLabel       ,L"ZipCodeLabel"       ,dcLabel     ,taRightJustify,false,L""                            ,L"<郵便番号>"    ,L"郵便番号ラベル"  ,true},
	{scAddressLabel1      ,L"AddressLabel1"      ,dcLabel     ,taRightJustify,false,L""                            ,L"<住所1>"       ,L"住所１ラベル"    ,true},
	{scAddressLabel2      ,L"AddressLabel2"      ,dcLabel     ,taRightJustify,false,L""                            ,L"<住所2>"       ,L"住所２ラベル"    ,true},
	{scTELLabel           ,L"TELLabel"           ,dcLabel     ,taRightJustify,false,L""                            ,L"<電話番号>"    ,L"電話番号ラベル"  ,true},
	{scFAXLabel           ,L"FAXLabel"           ,dcLabel     ,taRightJustify,false,L""                            ,L"<FAX番号>"     ,L"ＦＡＸ番号ラベル",true},
	{scUnitLabel          ,L"UnitLabel"          ,dcLabel     ,taLeftJustify ,false,L"単位:円"                     ,L"<単位>"        ,L"単位ラベル"      ,true},
	{scSubTotalLabel      ,L"SubTotalLabel"      ,dcLabel     ,taCenter      ,true ,L"小計"                        ,L"<小計>"        ,L"小計ラベル"      ,true},
	{scTaxLabel           ,L"TaxLabel"           ,dcLabel     ,taCenter      ,true ,L"消費税"                      ,L"<消費税>"      ,L"消費税ラベル"    ,true},
	{scTotalLabel         ,L"TotalLabel"         ,dcLabel     ,taCenter      ,true ,L"合計金額"                    ,L"<合計金額>"    ,L"合計金額ラベル"  ,true},
	{scNoteLabel          ,L"NoteLabel"          ,dcLabel     ,taLeftJustify ,false,L"備考"                        ,L"<備考>"        ,L"備考ラベル"      ,true},
	{scTransferLabel1     ,L"TransferLabel1"     ,dcLabel     ,taLeftJustify ,false,L"振込先:"                     ,L"<振込先1>"     ,L"振込先１ラベル"  ,true},
	{scTransferLabel2     ,L"TransferLabel2"     ,dcLabel     ,taLeftJustify ,false,L"振込先:"                     ,L"<振込先2>"     ,L"振込先２ラベル"  ,true},
	{scYearEdit           ,L"YearEdit"           ,dcDayEdit   ,taLeftJustify ,false,L""                            ,L"[年]"          ,L"年入力"          ,true},
	{scMonthEdit          ,L"MonthEdit"          ,dcDayEdit   ,taLeftJustify ,false,L""                            ,L"[月]"          ,L"月入力"          ,true},
	{scDayEdit            ,L"DayEdit"            ,dcDayEdit   ,taLeftJustify ,false,L""                            ,L"[日]"          ,L"日入力"          ,true},
	{scNoEdit             ,L"NoEdit"             ,dcEdit      ,taRightJustify,false,L""                            ,L"[書類番号]"    ,L"書類番号入力"    ,true},
	{scNameEdit           ,L"NameEdit"           ,dcEdit      ,taLeftJustify ,false,L""                            ,L"[名前]"        ,L"名前入力"        ,true},
	{scItemEdit           ,L"ItemEdit"           ,dcEdit      ,taLeftJustify ,false,L""                            ,L"[件名]"        ,L"件名入力"        ,true},
	{scMoneyEdit          ,L"MoneyEdit"          ,dcMoneyEdit ,taRightJustify,false,L""                            ,L"[金額]"        ,L"金額入力"        ,true},
	{scSubtotalEdit       ,L"SubtotalEdit"       ,dcMoneyEdit ,taRightJustify,true ,L""                            ,L"[小計]"        ,L"小計入力"        ,true},
	{scTaxEdit            ,L"TaxEdit"            ,dcMoneyEdit ,taRightJustify,true ,L""                            ,L"[消費税]"      ,L"消費税入力"      ,true},
	{scTotalEdit          ,L"TotalEdit"          ,dcMoneyEdit ,taRightJustify,true ,L""                            ,L"[合計金額]"    ,L"合計金額入力"    ,true},
	{scStampImage1        ,L"StampImage1"        ,dcImage     ,taCenter	    ,true ,L""                            ,L""              ,L"印影画像１"      ,true},
	{scStampImage2        ,L"StampImage2"        ,dcImage     ,taCenter	    ,true ,L""                            ,L""              ,L"印影画像２"      ,true},
	{scLogoImage          ,L"LogoImage"          ,dcImage     ,taCenter	    ,false,L""                            ,L""              ,L"ロゴ画像"        ,true},
	{scStdComponent::scGrid,L"Grid"               ,dcGrid      ,taLeftJustify ,false,L""                            ,L""              ,L"表入力"          ,true},
	{scDayUnderShape      ,L"DayUnderShape"      ,dcCLine     ,taLeftJustify ,false,L""                            ,L""              ,L"書類種類名下線"  ,true},
	{scNumberShape        ,L"NumberShape"        ,dcCLine     ,taLeftJustify ,false,L""                            ,L""              ,L"書類番号下線"    ,true},
	{scItemShape          ,L"ItemShape"          ,dcCLine     ,taLeftJustify ,false,L""                            ,L""              ,L"件名下線"        ,true},
	{scMoneyShape         ,L"MoneyShape"         ,dcCLine     ,taLeftJustify ,false,L""                            ,L""              ,L"金額下線"        ,true},
	{scNoteShape          ,L"NoteShape"          ,dcCLine     ,taLeftJustify ,false,L""                            ,L""              ,L"備考下線"        ,true},
	{scNameUnderShape     ,L"NameUnderShape"     ,dcCLine     ,taLeftJustify ,false,L""                            ,L""              ,L"名前下線"        ,true},
	{scCustomerZipCodeEdit ,L"CustomerZipCodeEdit" ,dcEdit    ,taLeftJustify ,false,L""                            ,L"[客先郵便番号]",L"客先郵便番号"    ,false},
	{scCustomerAddress1Edit,L"CustomerAddress1Edit",dcEdit    ,taLeftJustify ,false,L""                            ,L"[客先住所1]"   ,L"客先住所１"      ,false},
	{scCustomerAddress2Edit,L"CustomerAddress2Edit",dcEdit    ,taLeftJustify ,false,L""                            ,L"[客先住所2]"   ,L"客先住所２"      ,false},
	{scCustomerTELEdit     ,L"CustomerTELEdit"     ,dcEdit    ,taLeftJustify ,false,L""                            ,L"[客先電話番号]",L"客先電話番号"    ,false},
	{scCustomerFAXEdit     ,L"CustomerFAXEdit"     ,dcEdit    ,taLeftJustify ,false,L""                            ,L"[客先FAX番号]" ,L"客先FAX番号"     ,false},
};

//---------------------------------------------------------------------------
//書類種類名から書類種類情報を得る
//---------------------------------------------------------------------------
class typDocKindDefs
{
public:
	//用紙種別を得る
	static bool GetDocKindDefFromName(const String& DocKindName,typDocKindDef& kind);
	//コンポーネント名から標準コンポーネント情報を得る
	static bool GetStdComponentDefFromName(const String& StdComponentName,typStdComponentDef& comp,const typProcMode docMode);
};

#endif
