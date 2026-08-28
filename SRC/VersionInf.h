//----------------------------------------------------------------------------
#ifndef VersionInfH
#define VersionInfH
//----------------------------------------------------------------------------
#include <System.hpp>
#include <Windows.hpp>
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Graphics.hpp>
#include <Forms.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Vcl.TitleBarCtrls.hpp>
//----------------------------------------------------------------------------
class TAboutBox : public TForm
{
__published:
	TPanel *Panel1;
	TButton *OKButton;
	TLabel *Label1;
	TLabel *VerLbl;
	TLabel *CopyrightLbl;
	TLabel *Label4;
	TLabel *URLLabel;
	TLabel *LicOkLbl;
	TLabel *LicNGLbl;
	TLabel *Label5;
	TLabel *Label6;
	TPanel *Panel2;
	TImage *ProgramIcon;
	TLabel *Label7;
	TPanel *Panel3;
	TLabel *CPULbl;
	TTimer *Timer;
	TProgressBar *CPUProgressBar;
	TLabel *MemoryLbl;
	TProgressBar *MemoryProgressBar;
	TImage *Image2;
	TLabel *OSLbl;
	TTitleBarPanel *TitleBarPanel;
	void __fastcall URLLabelClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall TimerTimer(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:
	//プロセッサ情報を取得します。
	void GetProcessorInformation(LPTSTR pProcArchitecture,LPTSTR pProcLevel,LPDWORD pProcCount);
	//ファイルバージョン情報の取得
	void GetFileVer();
public:
	virtual __fastcall TAboutBox(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TAboutBox *AboutBox;
//----------------------------------------------------------------------------
#endif    
