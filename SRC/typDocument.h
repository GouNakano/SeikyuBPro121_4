//---------------------------------------------------------------------------
#ifndef typDocumentH
#define typDocumentH
//---------------------------------------------------------------------------
#include <vector>
#include <array>
#include <QuickRpt.hpp>
#include "nsLong.h"
#include "nsDouble.h"
#include "SeikyuBConst.h"
#include "nsBitmap.h"
#include "TPaperDefs.h"

//書類の表１行分データ定義
struct typDocOneRowData
{
	String   Item;       //項目
	String   Name;       //品目名
	nsDouble Num;        //数量
	String   Unit;       //単位
	nsDouble PriceUnit;  //単価
	nsDouble Money;      //金額
public:
	//コンストラクタ
	typDocOneRowData() = default;
	//コピーコンストラクタ
	typDocOneRowData(const typDocOneRowData& h) = default;
public:
	//代入
	typDocOneRowData& operator = (const typDocOneRowData& h) = default;
};

//書類のデータ定義
struct typDocData
{
	//書類データ
	nsLong                   Year;                //年
	nsLong                   Month;               //月
	nsLong                   Day;                 //日
	String                   No;                  //番号
	String                   Name;                //名前
	String                   Item;                //件名
	nsDouble                 Money;               //金額
	nsDouble                 Subtotal;            //小計
	nsDouble                 Tax;                 //消費税
	nsDouble                 Total;               //合計
	String                   CustomerZipCode;     //客先郵便番号
	String                   CustomerAddress1;    //客先住所1
	String                   CustomerAddress2;    //客先住所2
	String                   CustomerTEL;         //客先電話番号
	String                   CustomerFAX;         //客先ＦＡＸ番号
	nsLong                   RowNum;              //行数
	nsLong                   ColNum;              //列数
	//ラベル内容
	String                   BillLabel;           //書類種類名ラベル"
	String                   YearLabel;           //年ラベル
	String                   MonthLabel;          //月ラベル
	String                   DayLabel;            //日ラベル
	String                   NumberLabel;         //書類番号ラベル
	String                   HonorificTitleLabel; //敬称ラベル
	String                   RequestLabel;        //用件ラベル
	String                   TitleLabel;          //件名ラベル
	String                   ChargedAmountLabel;  //金額ラベル
	String                   CompanyNameLabel;    //会社名ラベル
	String                   PersonLabel;         //代表者ラベル
	String                   ZipCodeLabel;        //郵便番号ラベル
	String                   AddressLabel1;       //住所１ラベル
	String                   AddressLabel2;       //住所２ラベル
	String                   TELLabel;            //電話番号ラベル
	String                   FAXLabel;            //ＦＡＸ番号ラベル
	String                   UnitLabel;           //単位ラベル
	String                   SubTotalLabel;       //小計ラベル
	String                   TaxLabel;            //消費税ラベル
	String                   TotalLabel;          //合計金額ラベル
	String                   NoteLabel;           //備考ラベル
	String                   TransferLabel1;      //振込先１ラベル
	String                   TransferLabel2;      //振込先２ラベル
	//画像関連
	nsBitmap                 StampImage1;         //印影１
	nsBitmap                 StampImage2;         //印影２
	nsBitmap                 LogoImage;           //ロゴ
	//消費税率
	String  ConsumptionTaxRatio;
	//表のデータ
	std::vector<typDocOneRowData> GridData;
public:
	//コンストラクタ
	typDocData() = default;
	//コピーコンストラクタ
	typDocData(const typDocData& h) = default;
	//デストラクタ
	~typDocData() = default;
public:
	//代入
	typDocData& operator = (const typDocData& h) = default;
	//移譲代入
	typDocData& operator = (typDocData&& h) = default;

public:
	//データコピー
	void DataCopy(typDocData &Him)
	{
		Year             = Him.Year;                //年
		Month            = Him.Month;               //月
		Day              = Him.Day;                 //日
		No               = Him.No;                  //番号
		Name             = Him.Name;                //名前
		Item             = Him.Item;                //件名
		Money            = Him.Money;               //金額
		Subtotal         = Him.Subtotal;            //小計
		Tax              = Him.Tax;                 //消費税
		Total            = Him.Total;               //合計
		RowNum           = Him.RowNum;              //行数
		ColNum           = Him.ColNum;              //列数
		CustomerZipCode  = Him.CustomerZipCode ;    //客先郵便番号
		CustomerAddress1 = Him.CustomerAddress1;    //客先住所1
		CustomerAddress2 = Him.CustomerAddress2;    //客先住所2
		CustomerTEL      = Him.CustomerTEL     ;    //客先電話番号
		CustomerFAX      = Him.CustomerFAX     ;    //客先ＦＡＸ番号

		//表のデータ
		GridData.clear();
		for(int Cnt = 0;Cnt < Him.GridData.size();Cnt++)
		{
			//表のデータオブジェクト作成
			typDocOneRowData pItem;
			//データコピー
			pItem = Him.GridData[Cnt];
//			pItem.Copy(Him.GridData[Cnt]);
			//リストに追加
			GridData.push_back(pItem);
		}
	}
	//全消去
	void Clear()
	{
		*this = std::move(typDocData());
	}
};

struct typFontDef
{
public:
	String Name   = "ＭＳ Ｐゴシック";    //フォント名
	int    Size   = 9;                    //フォントサイズ
	TColor Color  = clBlack;              //フォント色
	bool   Bold   = false;                //太字
	bool   Italic = false;                //斜体
	bool   Under  = false;                //下線
public:
	//コンストラクタ
	typFontDef() = default;
	//コピーコンストラクタ
	typFontDef(const typFontDef& h) = default;
public:
	typFontDef& operator = (const typFontDef& h) = default;
};

//書類部品情報
struct typDocCompo
{
	psPaperSize    Paper;            //用紙の種類
	typProcMode    DocKind;          //書類種別
	dcDocComponent Type = dcUnknown; //部品の種類
	String         Name;             //部品名
	TAlignment     Alignment;        //整列方法
	bool           Border;           //枠の有無
	bool           Visible;          //表示するか
	bool           IsPrint;          //印刷するか
	long double    X;                //X座標(1/100 mm単位)
	long double    Y;                //Y座標(1/100 mm単位)
	long double    Width;            //幅(1/100 mm単位)
	long double    Height;           //高さ(1/100 mm単位)
	typFontDef     Font;             //フォント情報
	String         Caption;          //表示内容
	int            RowNum = 0;       //行数(グリッド)
	int            ColNum = 0;       //列数(グリッド)
	int            Figures;          //桁数
	bool           FigureLine;       //桁区切り線の有無
	int            ZOrder;           //Zオーダー
public:
	//コンストラクタ
	typDocCompo() = default;
	//キー用コンストラクタ
	typDocCompo(psPaperSize p,String n)
	:typDocCompo()
	{
		Paper = p;
		Name  = n;
	}
	//コピーコンストラクタ
	typDocCompo(const typDocCompo& h) = default;
	//デストラクタ
	virtual~typDocCompo() = default;
public:
	//代入
	typDocCompo& operator = (const typDocCompo& Him) = default;
	//比較
	bool operator == (const typDocCompo& Him)const{return (Paper == Him.Paper && DocKind == Him.DocKind && Name == Him.Name);}
};

//Zオーダソート用書類部品情報
class typZOrderDocCompo : public typDocCompo
{
//	typDocCompo *pDoc;
public:
	//コンストラクタ
	typZOrderDocCompo()  = default;
	//typDocCompoを用いたコンストラクタ
	typZOrderDocCompo(const typDocCompo& h)
	:typDocCompo(h)
	{
	}
	//デストラクタ
	~typZOrderDocCompo() = default;

public:
	bool operator == (const typZOrderDocCompo& Him)const{return (ZOrder == Him.ZOrder);}
	bool operator  > (const typZOrderDocCompo& Him)const{return (ZOrder  > Him.ZOrder);}
	bool operator  < (const typZOrderDocCompo& Him)const{return (ZOrder  < Him.ZOrder);}
};

//書類情報
class typDocument
{
private:
	std::vector<typDocCompo> DocCompo;              //書類部品リスト
public:
    String                 HistID;                  //現在の履歴ID
	String                 File;                    //現在の書類ファイルパス
	psPaperSize            Paper;                   //現在の用紙
	zoZoomDef              Zoom;                    //現在のズーム
	typProcMode            DocKind;                 //現在の書類種別
	bool                   Edited;                  //変更があるか
	int                    Version;                 //ファイルのバージョン
	std::array<typDocData,DOCUMENT_KIND_NUM> Data;  //書類のデータ
public:
	//コンストラクタ
	typDocument() = default;
	//コピーコンストラクタ
	typDocument(const typDocument& h) = default;
public:
	typDocument& operator = (const typDocument& h) = default;
public:
	//書類部品リストの要素数
	int GetCompoSize();
	//インデックスから書類部品リスト要素を得る
	typDocCompo& GetCompoFromIndex(int idx);
	//書類部品リストを消去
	void ClearDocCompo();
	//データ消去
	void ClearData();
	//書類部品情報名から書類部品情報を得る
	bool GetDocCompoFromName(const String& Name,typDocCompo& doc_compo);
	//書類部品情報名から書類部品情報をセット
	bool SetDocCompoFromName(String Name,const typDocCompo& doc_compo);
};

#endif
