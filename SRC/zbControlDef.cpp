//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "XnsGrid.h"
#include "BitBtn2.h"
#include "SpeedButton2.h"
#include "TDateEdit.h"
#include "nsLong.h"
#include "SeikyuBConst.h"
#include "zbControlDef.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//-------------------------------------------------------------
//日付入力エディットの設定を行う
//-------------------------------------------------------------
bool zbControlDef::setDateEditPram(TDateEdit *edt)
{
	edt->Font->Name    = STD_DATEEDIT_FONTNAME;       //日付入力エディットのフォント名
	edt->Font->Size    = STD_DATEEDIT_FONTSIZE;       //日付入力エディットのフォントサイズ
	edt->Font->Color   = STD_DATEEDIT_FONT_COLOR;     //日付入力エディットのフォント色
	edt->Height        = STD_DATEEDIT_HEIGHT;         //日付入力エディットの高さ
//	edt->Color         = STD_DATEEDIT_COLOR;          //日付入力エディットの背景色
	edt->EnterColor    = STD_DATEEDIT_ENTER_COLOR;    //日付入力エディットのフォーカス取得時の色
	edt->ExitColor     = STD_DATEEDIT_EXIT_COLOR;     //日付入力エディットのフォーカス無し時の色(正常)
	edt->ErrorColor    = STD_DATEEDIT_ERROR_COLOR;    //日付入力エディットのフォーカス無し時の色(エラー)
	edt->ReadOnlyColor = STD_DATEEDIT_READONLY_COLOR; //日付入力エディットのReadOnly時の色
	edt->BorderColor   = STD_DATEEDIT_BORDER_COLOR;   //日付入力エディットの境界色
	edt->ButtonUse     = true;                        //ボタンを使用する
	edt->ImeMode       = imDisable;                   //IMEは使用しない
	edt->BorderStyle   = bsNone;                      //標準の境界線は使用しない

	return true;
}
//-------------------------------------------------------------
//ベースエディットの設定を行う
//-------------------------------------------------------------
bool zbControlDef::setBaseEditPram(TBaseEdit *edt)
{
	edt->Font->Name    = STD_BASEEDIT_FONTNAME;       //ベースエディットのフォント名
	edt->Font->Size    = STD_BASEEDIT_FONTSIZE;       //ベースエディットのフォントサイズ
	edt->Font->Color   = STD_BASEEDIT_FONT_COLOR;     //ベースエディットのフォント色
	edt->Height        = STD_BASEEDIT_HEIGHT;         //ベースエディットの高さ
	edt->EnterColor    = STD_BASEEDIT_ENTER_COLOR;    //ベースエディットのフォーカス取得時の色
	edt->ExitColor     = STD_BASEEDIT_EXIT_COLOR;     //ベースエディットのフォーカス無し時の色(正常)
	edt->ReadOnlyColor = STD_BASEEDIT_READONLY_COLOR; //ベースエディットのReadOnly時の色
	edt->BorderColor   = STD_BASEEDIT_BORDER_COLOR;   //ベースエディットの境界色
//	edt->ImeMode       = imDisable;                   //IMEは使用しない
//	edt->Alignment     = STD_BASEEDIT_ALIGNMENT;      //テキスト編集コントロール内のテキストの配置方法を決定します。
	edt->Layout        = STD_BASEEDIT_LAYOUT;         //テキストの縦方向の配置を指定します。
//	edt->BorderStyle   = STD_BASEEDIT_BORDERSTYLE;    //編集コントロールがクライアント領域の周囲に単一線の境界を持つかどうかを決定します。

	return true;
}
//-------------------------------------------------------------
//コンボボックス(TComboBox2)の色などの設定を行う
//-------------------------------------------------------------
bool zbControlDef::setComboBox2Pram(TComboBox2 *cbox2)
{
	cbox2->Font->Size               = STD_COMBOBOX2_FONTSIZE;
	cbox2->ItemHeight               = STD_COMBOBOX2_ITEM_HEIGHT;
	cbox2->ExitColor                = STD_COMBOBOX2_COLOR;
	cbox2->Font->Color              = STD_COMBOBOX2_FONT_COLOR;
//	cbox2->EditBoxColor             = STD_COMBOBOX_ENTER_COLOR;
	cbox2->EditBoxColor             = STD_COMBOBOX2_COLOR;
	cbox2->SelectedEditBoxColor     = STD_COMBOBOX2_LIST_SELECT_COLOR;
	cbox2->EditBoxFontColor         = STD_COMBOBOX2_LIST_FONT_COLOR;
	cbox2->SelectedEditBoxFontColor = STD_COMBOBOX2_LIST_SELECT_FONT_COLOR;
	cbox2->ListColor                = STD_COMBOBOX2_LIST_COLOR;
	cbox2->ListFontColor            = STD_COMBOBOX2_LIST_FONT_COLOR;
	cbox2->SelectedListColor        = STD_COMBOBOX2_LIST_SELECT_COLOR;
	cbox2->SelectedListFontColor    = STD_COMBOBOX2_LIST_SELECT_FONT_COLOR;

	return true;
}
//-------------------------------------------------------------
//パネルの設定を行う
//-------------------------------------------------------------
bool zbControlDef::setPanelParam(TPanel *pnl)
{
	//パネルの色
	pnl->Color = STD_PANEL_STD_COLOR;

	return true;
}
//-------------------------------------------------------------
//ウィンドウの設定を行う
//-------------------------------------------------------------
bool zbControlDef::setWindowParam(TForm *win)
{
	//ウィンドウの色
	win->Color = STD_WINDOW_STD_COLOR;

	return true;
}

