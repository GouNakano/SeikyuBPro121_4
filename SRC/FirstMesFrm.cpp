//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SeikyuBDef.h"
#include "FirstMesFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFirstMesForm *FirstMesForm;
//---------------------------------------------------------------------------
__fastcall TFirstMesForm::TFirstMesForm(TComponent* Owner)
	: TForm(Owner)
{
}

//-------------------------------------------------------------
//  機能     ：フォームを閉じる時
//
//  関数定義 ：void __fastcall FormClose(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TFirstMesForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
	//初回起動フラグ
	bool   IsFirst   = (NextCheckBox->Checked == false);
	//レジストリ
	SBRegIni *pReg = new SBRegIni;
	//初回起動か？
	pReg->WriteBool(C_SYSTEM_SETTING,V_IS_FIRST,(IsFirst == true));
	//レジストリ開放
	delete pReg;
}
//---------------------------------------------------------------------------
