//---------------------------------------------------------------------------
#pragma hdrstop

#include "SeikyuBConst.h"
#include "sbControlDef.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//-------------------------------------------------------------
//ベースエディットの設定を行う
//-------------------------------------------------------------
bool sbControlDef::setBaseEditPram(TBaseEdit *edt)
{
	edt->Font->Name    = STD_BASEEDIT_FONTNAME;       //ベースエディットのフォント名
	edt->Font->Size    = STD_BASEEDIT_FONTSIZE;       //ベースエディットのフォントサイズ
//	edt->Height        = STD_BASEEDIT_HEIGHT;         //ベースエディットの高さ
	edt->Font->Color   = STD_BASEEDIT_FONT_COLOR;     //ベースエディットのフォント色
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

