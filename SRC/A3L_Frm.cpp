//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "A3L_Frm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "XnsGrid"
#pragma link "TWinLabel"
#pragma link "WinShape"
#pragma link "TWinLabel"
#pragma link "TBorderEdit"
#pragma resource "*.dfm"
TA3L_Form *A3L_Form;
//---------------------------------------------------------------------------
__fastcall TA3L_Form::TA3L_Form(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
