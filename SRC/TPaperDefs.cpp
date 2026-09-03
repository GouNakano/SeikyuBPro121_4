//---------------------------------------------------------------------------
#pragma hdrstop

#include "A3P_Frm.h"
#include "A3L_Frm.h"
#include "A4P_Frm.h"
#include "A4L_Frm.h"
#include "A5P_Frm.h"
#include "A5L_Frm.h"
#include "A6P_Frm.h"
#include "A6L_Frm.h"
#include "B4P_Frm.h"
#include "B4L_Frm.h"
#include "B5P_Frm.h"
#include "B5L_Frm.h"
#include "TPaperDefs.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
//用紙サイズ名から用紙情報を得る
//---------------------------------------------------------------------------
bool TPaperDefs::GetPaperDefFromName(const String& SizeName,typPaperDef& paper)
{
	for(int Cnt = 0;Cnt < PAPER_SIZE_KIND_NUM;Cnt++)
	{
		//名前一致チェック
		if(SizeName == PaperDef[Cnt].PaperName)
		{
			paper = PaperDef[Cnt];
			return true;
		}
	}
	//該当しない場合はA4縦を選択
	paper = PaperDef[A4P];

	return true;
}
//---------------------------------------------------------------------------
//用紙情報を得る
//---------------------------------------------------------------------------
bool TPaperDefs::get(int idx,typPaperDef& paper)
{
	if(idx < 0 || idx >= PAPER_SIZE_KIND_NUM)
	{
		return false;
	}

	//該当しない場合はA4縦を選択
	paper = PaperDef[idx];

	return true;
}
//---------------------------------------------------------------------------
//メインフォームクリックされたメニューの名前から用紙種類情報を得る
//---------------------------------------------------------------------------
bool TPaperDefs::getPaperFromMenyName(const String& menuName,typPaperDef& paperInfo)
{
	//メニュー名の加工アンダーバー以前の文字列
	int    UBPos    = menuName.Pos(L"_");
	String PaperStr = menuName.SubString(1,UBPos-1);
	//メニューから用紙情報を得る
	if(TPaperDefs::GetPaperDefFromName(PaperStr,paperInfo) == false)
	{
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
//現在の用紙に対応するテンプレートフォームを得る
//---------------------------------------------------------------------------
TForm* TPaperDefs::getTemplateFormPaper(psPaperSize paper)
{
	TForm *pTemplateForm;
	//対応するフォームを取得
	switch(paper)
	{
		case A3P:
		{
			pTemplateForm      = A3P_Form;
			pTemplateForm->Tag = 43;
			break;
		}
		case A3L:
		{
			pTemplateForm      = A3L_Form;
			pTemplateForm->Tag = 43;
			break;
		}
		case A4P:
		{
			pTemplateForm      = A4P_Form;
			pTemplateForm->Tag = 60;
			break;
		}
		case A4L:
		{
			pTemplateForm      = A4L_Form;
			pTemplateForm->Tag = 60;
			break;
		}
		case A5P:
		{
			pTemplateForm      = A5P_Form;
			pTemplateForm->Tag = 85;
			break;
		}
		case A5L:
		{
			pTemplateForm      = A5L_Form;
			pTemplateForm->Tag = 90;
			break;
		}
		case A6P:
		{
			pTemplateForm      = A6P_Form;
			pTemplateForm->Tag = 120;
			break;
		}
		case A6L:
		{
			pTemplateForm      = A6L_Form;
			pTemplateForm->Tag = 120;
			break;
		}
		case B4P:
		{
			pTemplateForm      = B4P_Form;
			pTemplateForm->Tag = 50;
			break;
		}
		case B4L:
		{
			pTemplateForm      = B4L_Form;
			pTemplateForm->Tag = 50;
			break;
		}
		case B5P:
		{
			pTemplateForm      = A5P_Form;
			pTemplateForm->Tag = 69;
			break;
		}
		case B5L:
		{
			pTemplateForm      = A5L_Form;
			pTemplateForm->Tag = 69;
			break;
		}
		default :
		{
			pTemplateForm      = A4P_Form;
			pTemplateForm->Tag = 60;
			break;
		}
	}
	return pTemplateForm;
}

