//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "A4P_Frm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "XnsGrid"
#pragma link "TWinLabel"
#pragma link "WinShape"
#pragma link "TBorderEdit"
#pragma resource "*.dfm"
TA4P_Form *A4P_Form;
//---------------------------------------------------------------------------
__fastcall TA4P_Form::TA4P_Form(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
