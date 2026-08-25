//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "A3P_Frm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "XnsGrid"
#pragma link "TWinLabel"
#pragma link "WinShape"
#pragma link "TWinLabel"
#pragma link "TBorderEdit"
#pragma resource "*.dfm"
TA3P_Form *A3P_Form;
//---------------------------------------------------------------------------
__fastcall TA3P_Form::TA3P_Form(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
