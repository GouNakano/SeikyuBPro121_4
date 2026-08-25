//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("MainFrm.cpp", MainForm);
USEFORM("LicSetting.cpp", LicSettingForm);
USEFORM("PropertyFrm.cpp", PropertyForm);
USEFORM("LicenseFrm.cpp", LicenseForm);
USEFORM("GridPropertyFrm.cpp", GridPropertyForm);
USEFORM("FirstMesFrm.cpp", FirstMesForm);
USEFORM("LabelModifyFrm.cpp", LabelModifyForm);
USEFORM("SubSelectFrm.cpp", SubSelectForm);
USEFORM("VersionInf.cpp", AboutBox);
USEFORM("SettingFrm.cpp", SettingForm);
USEFORM("SeikyuPrintFrm.cpp", SeikyuPrintForm);
USEFORM("A4L_Frm.cpp", A4L_Form);
USEFORM("A3P_Frm.cpp", A3P_Form);
USEFORM("A3L_Frm.cpp", A3L_Form);
USEFORM("CalendarFrm.cpp", CalendarForm);
USEFORM("B5P_Frm.cpp", B5P_Form);
USEFORM("CompanyInfoFrm.cpp", CompanyInfoForm);
USEFORM("FigureSettingFrm.cpp", FigureSettingForm);
USEFORM("DispSettingFrm.cpp", DispSettingForm);
USEFORM("ComponentsFrm.cpp", ComponentsForm);
USEFORM("B5L_Frm.cpp", B5L_Form);
USEFORM("A5P_Frm.cpp", A5P_Form);
USEFORM("A5L_Frm.cpp", A5L_Form);
USEFORM("A4P_Frm.cpp", A4P_Form);
USEFORM("A6L_Frm.cpp", A6L_Form);
USEFORM("B4P_Frm.cpp", B4P_Form);
USEFORM("B4L_Frm.cpp", B4L_Form);
USEFORM("A6P_Frm.cpp", A6P_Form);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->CreateForm(__classid(TA3P_Form), &A3P_Form);
		Application->CreateForm(__classid(TA4L_Form), &A4L_Form);
		Application->CreateForm(__classid(TA4P_Form), &A4P_Form);
		Application->CreateForm(__classid(TA5L_Form), &A5L_Form);
		Application->CreateForm(__classid(TA5P_Form), &A5P_Form);
		Application->CreateForm(__classid(TA6L_Form), &A6L_Form);
		Application->CreateForm(__classid(TA6P_Form), &A6P_Form);
		Application->CreateForm(__classid(TB4L_Form), &B4L_Form);
		Application->CreateForm(__classid(TB4P_Form), &B4P_Form);
		Application->CreateForm(__classid(TB5L_Form), &B5L_Form);
		Application->CreateForm(__classid(TB5P_Form), &B5P_Form);
		Application->CreateForm(__classid(TCalendarForm), &CalendarForm);
		Application->CreateForm(__classid(TCompanyInfoForm), &CompanyInfoForm);
		Application->CreateForm(__classid(TComponentsForm), &ComponentsForm);
		Application->CreateForm(__classid(TDispSettingForm), &DispSettingForm);
		Application->CreateForm(__classid(TFigureSettingForm), &FigureSettingForm);
		Application->CreateForm(__classid(TFirstMesForm), &FirstMesForm);
		Application->CreateForm(__classid(TGridPropertyForm), &GridPropertyForm);
		Application->CreateForm(__classid(TLabelModifyForm), &LabelModifyForm);
		Application->CreateForm(__classid(TLicenseForm), &LicenseForm);
		Application->CreateForm(__classid(TLicSettingForm), &LicSettingForm);
		Application->CreateForm(__classid(TPropertyForm), &PropertyForm);
		Application->CreateForm(__classid(TA3L_Form), &A3L_Form);
		Application->CreateForm(__classid(TSeikyuPrintForm), &SeikyuPrintForm);
		Application->CreateForm(__classid(TAboutBox), &AboutBox);
		Application->CreateForm(__classid(TSettingForm), &SettingForm);
		Application->CreateForm(__classid(TSubSelectForm), &SubSelectForm);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
