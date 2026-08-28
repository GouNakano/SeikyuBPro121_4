//---------------------------------------------------------------------------
#ifndef zbControlDefH
#define zbControlDefH
#include "ComboBox2.h"
#include "TDateEdit.h"
#include "TBaseEdit.h"
//---------------------------------------------------------------------------
class zbControlDef
{
public:
	//日付入力エディットの設定を行う
	static bool setDateEditPram(TDateEdit *edt);
	//ベースエディットの設定を行う
	static bool setBaseEditPram(TBaseEdit *edt);
	//コンボボックス(TComboBox2,XnsSrchItemEdit)の色などの設定を行う
	static bool setComboBox2Pram(TComboBox2 *cbox2);
	//パネルの設定を行う
	static bool setPanelParam(TPanel *pnl);
	//ウィンドウの設定を行う
	static bool setWindowParam(TForm *win);
};

//コントロール操作オブジェクト
extern zbControlDef zbControl;

#endif
