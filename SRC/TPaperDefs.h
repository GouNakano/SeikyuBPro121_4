//---------------------------------------------------------------------------
#ifndef TPaperDefsH
#define TPaperDefsH
//---------------------------------------------------------------------------
#include <QuickRpt.hpp>

//用紙定義
enum psPaperSize
{
	A3P=0, //A3縦
	A3L  , //A3横
	A4P  , //A4縦
	A4L  , //A4横
	A5P  , //A5縦
	A5L  , //A5横
	A6P  , //A6縦
	A6L  , //A6横
	B4P  , //B4縦
	B4L  , //B4横
	B5P  , //B5縦
	B5L    //B5横
};

//用紙定義構造体
class typPaperDef
{
public:
	psPaperSize         Number;      //用紙定義番号
	const wchar_t      *PaperName;   //用紙定義名称
	const wchar_t      *DispName;    //用紙名称(表示用)
	TQRPaperSize        PaperSize;   //用紙サイズ
	TPrinterOrientation Orientation; //印刷方向
	double              PaperWidth;  //用紙幅(カスタムのみ有効)
	double              PaperLength; //用紙高さ(カスタムのみ有効)
public:
	//コンストラクタ
	typPaperDef() = default;
	//コピーコンストラクタ
	typPaperDef(const typPaperDef& h) = default;
public:
	//代入
	typPaperDef& operator = (const typPaperDef& h) = default;
};

//用紙の種類の数
constexpr const int PAPER_SIZE_KIND_NUM = 12;

//用紙種類の定義
constexpr const typPaperDef PaperDef[PAPER_SIZE_KIND_NUM] = {
	{A3P,L"A3P",L"A3縦",A3,poPortrait     ,0    ,    0}, //A3縦
	{A3L,L"A3L",L"A3横",A3,poLandscape    ,0    ,    0}, //A3横
	{A4P,L"A4P",L"A4縦",A4,poPortrait     ,0    ,    0}, //A4縦
	{A4L,L"A4L",L"A4横",A4,poLandscape    ,0    ,    0}, //A4横
	{A5P,L"A5P",L"A5縦",A5,poPortrait     ,0    ,    0}, //A5縦
	{A5L,L"A5L",L"A5横",A5,poLandscape    ,0    ,    0}, //A5横
	{A6P,L"A6P",L"A6縦",Custom,poPortrait ,105.0,148.0}, //A6縦
	{A6L,L"A6L",L"A6横",Custom,poLandscape,148.0,105.0}, //A6横
	{B4P,L"B4P",L"B4縦",B4,poPortrait     ,0    ,    0}, //B4縦
	{B4L,L"B4L",L"B4横",B4,poLandscape    ,0    ,    0}, //B4横
	{B5P,L"B5P",L"B5縦",B5,poPortrait     ,0    ,    0}, //B5縦
	{B5L,L"B5L",L"B5横",B5,poLandscape    ,0    ,    0}  //B5横
};


//用紙種類の取得
class TPaperDefs
{
public:
	//用紙の種類数
	constexpr static int size()
	{
		return PAPER_SIZE_KIND_NUM;
	}
	//用紙サイズ名から用紙情報を得る
	static bool GetPaperDefFromName(const String& SizeName,typPaperDef& paper);
	//用紙情報を得る
	static bool get(int idx,typPaperDef& paper);
	//メインフォームクリックされたメニューの名前から用紙を選択する
	static bool setPaperFromMenyName(const String& menuName);
	//メインフォームクリックされたメニューの名前から用紙種類を得る
	static bool getPaperFromMenyName(const String& menuName,typPaperDef& paperInfo);
	//現在の用紙に対応するテンプレートフォームを得る
	static TForm* getTemplateFormPaper(psPaperSize paper);
};


#endif
