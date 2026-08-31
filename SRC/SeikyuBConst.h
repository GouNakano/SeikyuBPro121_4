//---------------------------------------------------------------------------
#ifndef SeikyuBConstH
#define SeikyuBConstH
//---------------------------------------------------------------------------
#include <QuickRpt.hpp>
#include "nsDouble.h"

//ディスクシリアル文字列フォーマット
constexpr const wchar_t *DISK_SERIAL_STRING = L"GZB%012X";

//ライセンス設定ファイル
constexpr const wchar_t *LIC_SETTING_FILE = L"SEPRO.LIC";

//繰り返し入力ﾃﾞｰﾀﾌｨｰﾙﾄﾞ名
constexpr const wchar_t *FLD_CTRLNAME = L"キー";
constexpr const wchar_t *FLD_STRING   = L"内容";
constexpr const wchar_t *FLD_RANK     = L"順位";

//ファイルバージョン
constexpr const int SB_FILE_VERSION = 2;

//書類種類の数
constexpr const int DOCUMENT_KIND_NUM = 3;

//作業対象の書類の種類
enum typProcMode
{
	pmSeikyu = 0, //請求書
	pmNouhin,     //納品書
	pmMitsumori   //見積書
};

//ズーム定義
enum zoZoomDef
{
	Z200 = 0, //200%
	Z100    , //100%
	Z90     , //90%
	Z80     , //80%
	Z70     , //70%
	Z60     , //60%
	Z50     , //50%
	Z40     , //40%
	Z30     , //30%
	Z20     , //20%
	Z10     , //10%
};

//書類部品定義
enum dcDocComponent
{
	dcUnknown=0  , //未定義
	dcLabel      , //ラベル
	dcEdit       , //Edit
	dcDayEdit    , //日付Edit
	dcMoneyEdit  , //金額Edit
	dcImage      , //画像
	dcVLine      , //縦線
	dcCLine      , //横線
	dcGrid       , //グリッド
	dcCell       , //グリッドのセル
};

//標準コンポーネント番号
enum scStdComponent
{
	scBillLabel=0         ,
	scYearLabel           ,
	scMonthLabel          ,
	scDayLabel            ,
	scNumberLabel         ,
	scHonorificTitleLabel ,
	scRequestLabel        ,
	scTitleLabel          ,
	scChargedAmountLabel  ,
	scCompanyNameLabel    ,
	scPersonLabel         ,
	scZipCodeLabel        ,
	scAddressLabel1       ,
	scAddressLabel2       ,
	scTELLabel            ,
	scFAXLabel            ,
	scUnitLabel           ,
	scSubTotalLabel       ,
	scTaxLabel            ,
	scTotalLabel          ,
	scNoteLabel           ,
	scTransferLabel1      ,
	scTransferLabel2      ,
	scYearEdit            ,
	scMonthEdit           ,
	scDayEdit             ,
	scNoEdit              ,
	scNameEdit            ,
	scItemEdit            ,
	scMoneyEdit           ,
	scSubtotalEdit        ,
	scTaxEdit             ,
	scTotalEdit           ,
	scStampImage1         ,
	scStampImage2         ,
	scLogoImage           ,
	scGrid                ,
	scDayUnderShape       ,
	scNumberShape         ,
	scItemShape           ,
	scMoneyShape          ,
	scNoteShape           ,
	scNameUnderShape      ,
	scCustomerZipCodeEdit ,
	scCustomerAddress1Edit,
	scCustomerAddress2Edit,
	scCustomerTELEdit     ,
	scCustomerFAXEdit
};

//ﾕｰｻﾞが選択した処置の種類
enum mbsel{
	mbselYES,     //YESを選択
	mbselNO,      //NOを選択
	mbselCancel   //ｷｬﾝｾﾙを選択
};
//ダイアログのモード
enum msgMode
{
	mmOk,          //OKボタンのみ
	mmYesNo,       //YesNoﾀﾞｲｱﾛｸﾞ
	mmYesNoCancel  //YesNoｷｬﾝｾﾙﾀﾞｲｱﾛｸﾞ
};

////請求書番頭設定格納
//struct typSBSetting
//{
//public:
//	//共通定義
//	bool         IsRemain        = true;   //前回のを再現
//	bool         BackupFile      = true;   //バックアップファイルの作成
//	bool         UseTemplateFile = false;  //新規作成時のテンプレートファイルの使用
//	String       TemplateFile;             //新規作成時のテンプレートファイル
//	bool         IsToday         = true;   //新規作成時、本日の日付をセットするか
//	int          AccuracyR1      = 0;      //小数点以下の桁数
//	int          AccuracyR2      = 0;      //小数点以下の桁数
//	int          AccuracyR3      = 0;      //小数点以下の桁数
//	int          AccuracyR4      = 0;      //小数点以下の桁数
//	int          AccuracyR5      = 0;      //小数点以下の桁数
//	TValuateType RateTyp1        = tOmit;  //小数点有効桁以下処理タイプ
//	TValuateType RateTyp2        = tOmit;  //小数点有効桁以下処理タイプ
//	TValuateType RateTyp3        = tOmit;  //小数点有効桁以下処理タイプ
//	TValuateType RateTyp4        = tOmit;  //小数点有効桁以下処理タイプ
//	TValuateType RateTyp5        = tOmit;  //小数点有効桁以下処理タイプ
//};

//レジストリ関連定数
constexpr const wchar_t *INI_REG_ROOT        = L"Software\\SakuraDensan\\SeikyuBPro";            //共通定義
constexpr const wchar_t *INI_REG_HIST_ROOT   = L"Software\\SakuraDensan\\SeikyuBPro\\HISTORIES"; // 作成履歴

constexpr const wchar_t  *INI_REG_INPUT      = L"INPUT";         //入力履歴
constexpr const wchar_t  *INI_REG_FILE_PATH  = L"FILE_PATH";     //ファイルのパス
constexpr const wchar_t  *INI_REG_FILE_ID    = L"FILE_ID";       //ファイルのID
constexpr const wchar_t  *INI_REG_NAME       = L"NAME";          //名前
constexpr const wchar_t  *INI_REG_ITEM_NAME  = L"ITEM_NAME";     //件名
constexpr const wchar_t  *INI_REG_YEAR       = L"YEAR";          //年
constexpr const wchar_t  *INI_REG_MONTH      = L"MONTH";         //月
constexpr const wchar_t  *INI_REG_DAY        = L"DAY";           //日

//定数定義
constexpr const wchar_t  *SYSTEM_NAME        = L"請求書番頭 プロ版";
constexpr const wchar_t  *HELPFILE           = L"\\SeikyuBPro.chm";                     //ヘルプファイル
constexpr const wchar_t  *DATABESE_FILE_NAME = L"%s\\sbpro.mdb";                        //データベースファイル名
constexpr const wchar_t  *ZIP_CODE_CSV       = L"\\zip.csv";                            //郵便番号定義ファイル
constexpr const wchar_t  *VERSION_STRING     = L"1.00";                                 //バージョンを表す文字列

constexpr const wchar_t  *C_SYSTEM_SETTING              = L"SYSTEM_SETTING";            //ソフトの設定
constexpr const wchar_t  *C_LABEL_NO_SETTING            = L"@@_SBFREE_SETTING_NONE_@@"; //値が未設定のラベル
constexpr const wchar_t  *C_KEY_BILL_LABELS             = L"BILL_LABELS";               //請求書ラベルのキー
constexpr const wchar_t  *C_KEY_DELIVERED_LABELS        = L"DELIVERED_LABELS";          //納品書ラベルのキー
constexpr const wchar_t  *C_KEY_ESTIMATE_LABELS         = L"ESTIMATE_LABELS";           //見積書ラベルのキー
constexpr const wchar_t  *C_KEY_COMPANY_INFO            = L"COMPANY_INFO_%02d";         //自社情報のキー
constexpr const int   C_PRINT_ZOOM_RATIO                = 60;                           //印刷レポートのズーム率
constexpr const wchar_t  *C_CONSUMPTION_TAX_RATIO       = L"CONSUMPTION_TAX_RATIO";     //消費税率
constexpr const wchar_t  *C_PAPER_SIZE_KIND             = L"PAPER_SIZE_KIND";           //用紙サイズの種類
constexpr const wchar_t  *C_PAPER_DISPLAY_ZOOM          = L"PAPER_DISPLAY_ZOOM";        //ズーム定義
constexpr const int   DEFAULT_CONSUMPTION_TAX_RATIO     = 5;                            //デフォルトの消費税率
constexpr const wchar_t  *V_REPORT_TYPE                 = L"REPORT_TYPE";               //現在の書類の種類(請求書、納品書)
constexpr const wchar_t  *V_WINDOW_TOP                  = L"WINDOW_TOP";                //ウィンドウ座標(X)
constexpr const wchar_t  *V_WINDOW_LEFT                 = L"WINDOW_LEFT";               //ウィンドウ座標(Y)
constexpr const wchar_t  *V_WINDOW_WIDTH                = L"WINDOW_WIDTH";              //ウィンドウ幅
constexpr const wchar_t  *V_WINDOW_HEIGHT               = L"WINDOW_HEIGHT";             //ウィンドウ高さ
constexpr const wchar_t  *V_IS_FIRST                    = L"IS_FIRST";                  //初回起動？
constexpr const wchar_t  *V_INSTALL_EXE                 = L"INSTALL_EXE";               //EXEの位置
constexpr const wchar_t  *V_VERSION                     = L"VERSION";                   //バージョン
constexpr const wchar_t  *S_SECTION_SETTING             = L"SETTING";                   //設定セクション名
constexpr const wchar_t  *V_PAPER_SIZE                  = L"PAPER_SIZE";                //用紙の種類
constexpr const wchar_t  *V_ZOOM                        = L"ZOOM";                      //ズーム
constexpr const wchar_t  *V_DOCKIND                     = L"DOCKIND";                   //書類種別
constexpr const wchar_t  *V_LEFT                        = L"LEFT";                      //X座標(1/100 mm単位)
constexpr const wchar_t  *V_TOP                         = L"TOP";                       //Y座標(1/100 mm単位)
constexpr const wchar_t  *V_WIDTH                       = L"WIDTH";                     //幅(1/100 mm単位)
constexpr const wchar_t  *V_HEIGHT                      = L"HEIGHT";                    //高さ(1/100 mm単位)
constexpr const wchar_t  *V_FONT_INFO                   = L"FONT_INFO";                 //フォント情報
constexpr const wchar_t  *V_CAPTION                     = L"CAPTION";                   //キャプション(内容)
constexpr const wchar_t  *V_ROWNUM                      = L"ROWNUM";                    //行数
constexpr const wchar_t  *V_COLNUM                      = L"COLNUM";                    //列数
constexpr const wchar_t  *V_VISIBLE                     = L"VISIBLE";                   //表示するか
constexpr const wchar_t  *V_ZORDER                      = L"ZORDER";                    //Zオーダー
constexpr const wchar_t  *V_PRINT                       = L"PRINT";                     //印刷するか
constexpr const wchar_t  *V_TYPE                        = L"TYPE";                      //部品の型
constexpr const wchar_t  *V_ALIGNMENT                   = L"ALIGNMENT";                 //整列方法
constexpr const wchar_t  *V_BORDER                      = L"BORDER";                    //枠の有無
constexpr const wchar_t  *V_FIGURES                     = L"FIGURES";                   //桁数
constexpr const wchar_t  *V_FIGURE_LINE                 = L"FIGURE_LINE";               //桁区切り線の有無
constexpr const wchar_t  *LICENSE_STRING                = L"SBPRO.LIC";                 //設定セクション名

constexpr const int       DEFAULT_FIGURES               = 7;                            //デフォルト桁数
constexpr const long double PRINT_ADJUST_DIFF           = 0.2;                          //印刷用調整値
constexpr const char     *INI_DOK_STOCKMANAGER          = "FIGURE_LINE";                //在庫マネージャー
constexpr const char     *INI_DOK_BTOMHEIGHT            = "FONT_INFO";                  //下パネルの高さ


//自社情報関連キー
constexpr const wchar_t  *COMPANY_INFO_COMPANYNAME  = L"COMPANYNAME";
constexpr const wchar_t  *COMPANY_INFO_REPRESENT    = L"REPRESENT";
constexpr const wchar_t  *COMPANY_INFO_ZIPNUMBER    = L"ZIPNUMBER";
constexpr const wchar_t  *COMPANY_INFO_ADDRESS1     = L"ADDRESS1";
constexpr const wchar_t  *COMPANY_INFO_ADDRESS2     = L"ADDRESS2";
constexpr const wchar_t  *COMPANY_INFO_TEL          = L"TEL";
constexpr const wchar_t  *COMPANY_INFO_FAX          = L"FAX";
constexpr const wchar_t  *COMPANY_INFO_TRANSFER1    = L"TRANSFER1";
constexpr const wchar_t  *COMPANY_INFO_TRANSFER2    = L"TRANSFER2";
constexpr const wchar_t  *COMPANY_INFO_TAXRATIO     = L"TAXRATIO";
constexpr const int   STD_TAXRATIO                  = 10;
constexpr const int   STD_GRID_COLNUM               = 6;
constexpr const long double PRINT_BORDER_MARGIN     = 1.0;

//編集履歴
constexpr const int       INI_MAX_HISTORY               = 5;                            //編集履歴の最大数
constexpr const wchar_t  *INI_HISTORY                   = L"HISTRY_%02d";               //編集履歴(1～INI_MAX_HISTORY)
constexpr const wchar_t  *INI_HISTORY_SECTION           = L"HISTRY";                    //編集履歴(1～INI_MAX_HISTORY)

//ファイル再開処理
constexpr const wchar_t  *INI_DEF_REOPEN   = L"REOPEN";      //再開処理
constexpr const wchar_t  *INI_ROP_ISREOPEN = L"REOPEN";      //再開処理を有効にするか
constexpr const wchar_t  *INI_ROP_SDOPATH  = L"SDO_FILE";    //再開処理対象ファイルパス
constexpr const wchar_t  *INI_ROP_HISTID   = L"HISTID";      //再開処理対象ファイルパス

//共通設定
constexpr const wchar_t  *INI_SETTING_SECTION           = L"SETTING";                  //設定のセクション
constexpr const wchar_t  *INI_ISREMAIN                  = L"IS_REMAIN";                //前回のを再現
constexpr const wchar_t  *INI_BACKUPFILE                = L"BACKUPFILE";               //バックアップファイルの作成
constexpr const wchar_t  *INI_USE_TEMPLATE              = L"USE_TEMPLATE";             //新規作成時のテンプレートファイルの使用
constexpr const wchar_t  *INI_TEMPLATE_FILE             = L"TEMPLATE_FILE";            //新規作成時のテンプレートファイル
constexpr const wchar_t  *INI_SET_TODAY                 = L"SET_TODAY";                //新規作成時、本日の日付をセットするか
constexpr const wchar_t  *INIKEY_RATE_TYP01             = L"RATETYP01";                //丸めタイプ１
constexpr const wchar_t  *INIKEY_RATE_ACCURACY01        = L"RATEACCURACY01";           //小数点以下精度
constexpr const wchar_t  *INIKEY_RATE_TYP02             = L"RATETYP02";                //丸めタイプ
constexpr const wchar_t  *INIKEY_RATE_ACCURACY02        = L"RATEACCURACY02";           //小数点以下精度
constexpr const wchar_t  *INIKEY_RATE_TYP03             = L"RATETYP03";                //丸めタイプ
constexpr const wchar_t  *INIKEY_RATE_ACCURACY03        = L"RATEACCURACY03";           //小数点以下精度
constexpr const wchar_t  *INIKEY_RATE_TYP04             = L"RATETYP04";                //丸めタイプ
constexpr const wchar_t  *INIKEY_RATE_ACCURACY04        = L"RATEACCURACY04";           //小数点以下精度
constexpr const wchar_t  *INIKEY_RATE_TYP05             = L"RATETYP05";                //丸めタイプ
constexpr const wchar_t  *INIKEY_RATE_ACCURACY05        = L"RATEACCURACY05";           //小数点以下精度
constexpr const wchar_t  *STD_FILEXT                    = L".sdo";                     //標準の請求書番頭ファイル拡張子
constexpr const wchar_t  *INI_FILEXT                    = L".ini";                     //テキストの請求書番頭拡張子
constexpr const wchar_t  *INI_TEMP_SDO_INI              = L"TEMP_SDO.ini";             //一時作成のデータiniファイル
constexpr const wchar_t  *INI_STAMP1_FILE               = L"%sSTAMP1_FILE_%02d.bmp";   //印影１のファイル名(数字は書類の種別)
constexpr const wchar_t  *INI_STAMP2_FILE               = L"%sSTAMP2_FILE_%02d.bmp";   //印影２のファイル名
constexpr const wchar_t  *INI_LOGO_FILE                 = L"%sLOGO_FILE_%02d.bmp";     //ロゴのファイル名
constexpr const wchar_t  *INI_TEMP_FILE_LIST            = L"%sTEMP_FILE_LIST.tmp";     //一時作成のファイルのリストファイル

//標準タイトルバー関連
constexpr const wchar_t *ZB_TITLEBAR_FONTNAME                   = L"メイリオ";           //フォント名
constexpr const wchar_t *STD_TITLEBAR_NAME                      = L"TitleBarPanel";      //タイトルバーの名前
constexpr const int      STD_TITLEBAR_HEIGHT                    = 35;                    //タイトルバーの高さ
constexpr const TColor   STD_TITLEBAR_BACKGROUNDCOLOR           = (TColor)0x00A56110;    //タイトルバー背景色
constexpr const TColor   STD_TITLEBAR_FOREGROUNDCOLOR           = clWhite;               //タイトルバー前景色
constexpr const TColor   STD_TITLEBAR_INACTIVE_BACKGROUNDCOLOR  = (TColor)0x00B58242;    //タイトルバー非アクティブ背景色
constexpr const TColor   STD_TITLEBAR_INACTIVE_FOREGROUNDCOLOR  = (TColor)0x00D6BA94;    //タイトルバー非アクティブ前景色
constexpr const TColor   STD_TITLEBAR_BLUE_FONTCOLOR            = (TColor)0x0072460C;    //タイトルバーに合わせたボタンのフォントの色
//青系ボタン関連
constexpr const wchar_t *STD_BLUE_BUTTON_FONTNAME               = L"メイリオ";           //青系ボタンのフォント名
constexpr const TColor   STD_BLUE_BUTTON_FONT_COLOR             = (TColor)0x00331A00;    //青系ボタンのフォント色
constexpr const TColor   STD_BLUE_BUTTON_COLOR                  = clWhite;               //青系ボタンの色
constexpr const TColor   STD_BLUE_BUTTON_MOUSE_ENTER_COLOR      = (TColor)0x00F9DFBF;    //青系ボタンマウスポインタがボタンの上にある時の色
constexpr const TColor   STD_BLUE_BUTTON_MOUSE_DOWN_COLOR       = (TColor)0x00F1B872;    //青系ボタンマウスダウン時の色
constexpr const TColor   STD_BLUE_BUTTON_BORDER_COLOR           = clGray;                //青系ボタン境界色
constexpr const TColor   STD_BLUE_BUTTON_DISABLE_FONT_COLOR     = clGray;                //青系ボタン使用不可時のフォントの色
//赤系ボタン関連
constexpr const wchar_t *STD_RED_BUTTON_FONTNAME               = L"メイリオ";            //赤系ボタンのフォント名
constexpr const TColor   STD_RED_BUTTON_FONT_COLOR             = (TColor)0x00000033;     //赤系ボタンのフォント色
constexpr const TColor   STD_RED_BUTTON_COLOR                  = clWhite;                //赤系ボタンの色
constexpr const TColor   STD_RED_BUTTON_MOUSE_ENTER_COLOR      = (TColor)0x00E3E3FF;     //赤系ボタンマウスポインタがボタンの上にある時の色
constexpr const TColor   STD_RED_BUTTON_MOUSE_DOWN_COLOR       = (TColor)0x00B5B5FF;     //赤系ボタンマウスダウン時の色
constexpr const TColor   STD_RED_BUTTON_BORDER_COLOR           = clGray;                 //赤系ボタン境界色
constexpr const TColor   STD_RED_BUTTON_DISABLE_FONT_COLOR     = clGray;                 //赤系ボタン使用不可時のフォントの色
//緑系ボタン関連
constexpr const wchar_t *STD_GREEN_BUTTON_FONTNAME             = L"メイリオ";            //緑系ボタンのフォント名
constexpr const TColor   STD_GREEN_BUTTON_FONT_COLOR           = (TColor)0x00003300;     //緑系ボタンのフォント色
constexpr const TColor   STD_GREEN_BUTTON_COLOR                = clWhite;                //緑系ボタンの色
constexpr const TColor   STD_GREEN_BUTTON_MOUSE_ENTER_COLOR    = (TColor)0x00CFFFBF;     //緑系ボタンマウスポインタがボタンの上にある時の色
constexpr const TColor   STD_GREEN_BUTTON_MOUSE_DOWN_COLOR     = (TColor)0x0082FF57;     //緑系ボタンマウスダウン時の色
constexpr const TColor   STD_GREEN_BUTTON_BORDER_COLOR         = clGray;                 //緑系ボタン境界色
constexpr const TColor   STD_GREEN_BUTTON_DISABLE_FONT_COLOR   = clGray;                 //緑系ボタン使用不可時のフォントの色
//スピードボタン関連
constexpr const wchar_t *STD_BLUE_SPEEDBUTTON_FONTNAME          = L"メイリオ";           //青系スピードボタンのフォント名
constexpr const TColor   STD_BLUE_SPEEDBUTTON_FONT_COLOR        = (TColor)0x00301E05;    //青系スピードボタンのフォント色
constexpr const TColor   STD_BLUE_SPEEDBUTTON_COLOR             = clWhite;               //青系スピードボタンの色
constexpr const TColor   STD_BLUE_SPEEDBUTTON_DOWN_COLOR        = (TColor)0x00F7E7C6;    //青系スピードボタンマウスポインタがボタンの上にある時の色
constexpr const TColor   STD_BLUE_SPEEDBUTTON_MOUSE_ENTER_COLOR = (TColor)0x00F7E7C6;    //青系スピードボタンマウスポインタがボタンの上にある時の色
constexpr const TColor   STD_BLUE_SPEEDBUTTON_MOUSE_DOWN_COLOR  = (TColor)0x00F1B872;    //青系スピードボタンマウスダウン時の色
constexpr const TColor   STD_BLUE_SPEEDBUTTON_DISABLE_FONT_COLOR= clGray;                //青系スピードボタン使用不可時のフォントの色
constexpr const TColor   STD_BLUE_SPEEDBUTTON_BORDER_COLOR      = clSilver;              //青系スピードボタン境界色
constexpr const TColor   STD_BLUE_SPEEDBUTTON_DOWN_BORDER_COLOR = (TColor)0x008C6129;    //青系スピードボタンダウン時境界色
constexpr const TColor   STD_BLUE_SPEEDBUTTON_DOWN_FONT_COLOR   = clBlue;                //青系ボタンダウン時のフォントの色
//日付入力エディット関連
constexpr const wchar_t *STD_DATEEDIT_FONTNAME                  = L"ＭＳ Ｐゴシック";    //日付入力エディットのフォント名
constexpr const int      STD_DATEEDIT_FONTSIZE                  = 10;                    //日付入力エディットのフォントサイズ
constexpr const int      STD_DATEEDIT_HEIGHT                    = 22;                    //日付入力エディットの高さ
constexpr const TColor   STD_DATEEDIT_COLOR                     = clWhite;               //日付入力エディットの背景色
constexpr const TColor   STD_DATEEDIT_FONT_COLOR                = clBlack;               //日付入力エディットのフォント色
constexpr const TColor   STD_DATEEDIT_ENTER_COLOR               = (TColor)0x00AAFFFF;    //日付入力エディットのフォーカス取得時の色
constexpr const TColor   STD_DATEEDIT_EXIT_COLOR                = clWhite;               //日付入力エディットのフォーカス無し時の色(正常)
constexpr const TColor   STD_DATEEDIT_ERROR_COLOR               = (TColor)0x00D5D5FF;    //日付入力エディットのフォーカス無し時の色(エラー)
constexpr const TColor   STD_DATEEDIT_READONLY_COLOR            = (TColor)0x00EBEBEB;    //日付入力エディットのReadOnly時の色
constexpr const TColor   STD_DATEEDIT_BORDER_COLOR              = clGray;                //日付入力エディットの境界色
//ベースエディット関連
constexpr const wchar_t     *STD_BASEEDIT_FONTNAME              = L"ＭＳ Ｐゴシック";    //ベースエディットのフォント名
constexpr const int          STD_BASEEDIT_FONTSIZE              = 10;                    //ベースエディットのフォントサイズ
constexpr const int          STD_BASEEDIT_HEIGHT                = 21;                    //ベースエディットの高さ
constexpr const TColor       STD_BASEEDIT_FONT_COLOR            = clBlack;               //ベースエディットのフォント色
constexpr const TColor       STD_BASEEDIT_ENTER_COLOR           = (TColor)0x00AAFFFF;    //ベースエディットのフォーカス取得時の色
constexpr const TColor       STD_BASEEDIT_EXIT_COLOR            = clWhite;               //ベースエディットのフォーカス無し時の色(正常)
constexpr const TColor       STD_BASEEDIT_READONLY_COLOR        = (TColor)0x00EBEBEB;    //ベースエディットのReadOnly時の色
constexpr const TColor       STD_BASEEDIT_BORDER_COLOR          = clGray;                //ベースエディットの境界色
constexpr const TAlignment   STD_BASEEDIT_ALIGNMENT             = taLeftJustify;         //テキスト編集コントロール内のテキストの配置方法を決定します。
constexpr const TTextLayout  STD_BASEEDIT_LAYOUT                = tlCenter;              //テキストの縦方向の配置を指定します。
constexpr const TBorderStyle STD_BASEEDIT_BORDERSTYLE           = bsNone;                //編集コントロールがクライアント領域の周囲に単一線の境界を持つかどうかを決定します。
//コンボボックス２関連
constexpr const wchar_t *STD_COMBOBOX2_FONTNAME                  = L"Meiryo UI";          //コンボボックス２のフォント名
constexpr const int      STD_COMBOBOX2_FONTSIZE                  = 9;                     //コンボボックス２のフォントサイズ
constexpr const int      STD_COMBOBOX2_ITEM_HEIGHT               = 17;                    //コンボボックス２のアイテムの高さ
constexpr const TColor   STD_COMBOBOX2_COLOR                     = clWhite;               //コンボボックス２の背景色
constexpr const TColor   STD_COMBOBOX2_FONT_COLOR                = clBlack;               //コンボボックス２のフォント色
constexpr const TColor   STD_COMBOBOX2_LIST_COLOR                = clWhite;               //コンボボックス２の背景色
constexpr const TColor   STD_COMBOBOX2_LIST_FONT_COLOR           = clBlack;               //コンボボックス２のリストフォント色
constexpr const TColor   STD_COMBOBOX2_LIST_SELECT_COLOR         = (TColor)0x00A56110;    //コンボボックス２の選択行の背景色
constexpr const TColor   STD_COMBOBOX2_LIST_SELECT_FONT_COLOR    = clWhite;               //コンボボックス２の選択行のフォント色
//パネル関連
constexpr const TColor       STD_PANEL_STD_COLOR                = (TColor)0x00FEFEFE;    //標準のパネルの色
//ウィンドウ関連
constexpr const TColor       STD_WINDOW_STD_COLOR               = (TColor)0x00FEFEFE;    //標準のウィンドウの色

#endif
