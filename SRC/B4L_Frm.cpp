//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "B4L_Frm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "XnsGrid"
#pragma link "TWinLabel"
#pragma link "WinShape"
#pragma link "TBorderEdit"
#pragma resource "*.dfm"
TB4L_Form *B4L_Form;
//---------------------------------------------------------------------------
__fastcall TB4L_Form::TB4L_Form(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
