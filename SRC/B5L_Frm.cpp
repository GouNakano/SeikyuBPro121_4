//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "B5L_Frm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "XnsGrid"
#pragma link "TWinLabel"
#pragma link "WinShape"
#pragma link "TBorderEdit"
#pragma resource "*.dfm"
TB5L_Form *B5L_Form;
//---------------------------------------------------------------------------
__fastcall TB5L_Form::TB5L_Form(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
