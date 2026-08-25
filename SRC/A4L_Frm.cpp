//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "A4L_Frm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "XnsGrid"
#pragma link "TWinLabel"
#pragma link "WinShape"
#pragma link "TBorderEdit"
#pragma resource "*.dfm"
TA4L_Form *A4L_Form;
//---------------------------------------------------------------------------
__fastcall TA4L_Form::TA4L_Form(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
