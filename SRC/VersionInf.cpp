//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "nsCPURatio.h"
#include "SeikyuBDef.h"
#include "VersionInf.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TAboutBox *AboutBox;
//--------------------------------------------------------------------- 
__fastcall TAboutBox::TAboutBox(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------------
//  機能     ：URLのラベルをクリック
//
//  関数定義 ：void __fastcall URLLabelClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TAboutBox::URLLabelClick(TObject *Sender)
{
	String URL;
	//ラベル
	TLabel *pLbl = static_cast<TLabel *>(Sender);
	//URLを得る
	URL = pLbl->Caption;
	URL.Unique();
	//起動
	ShellExecute(Handle,L"open",URL.c_str(),L"",L"",SW_SHOW);
}
//---------------------------------------------------------------------------
//  機能     ：フォーム表示時
//
//  関数定義 ：void __fastcall FormShow(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TAboutBox::FormShow(TObject *Sender)
{
	OSVERSIONINFO OSInf;
	String        VerText;
	String        OSName;
	String        OSDispStr;
	long          Build;
	TCHAR         proc_arch[32];
	TCHAR         proc_level[32];
	DWORD         proc_count;
	//ライセンスチェック
	bool IsLicOk = sbp::CheckLicenceEnable();
	//ライセンス表示の設定
	if(IsLicOk == true)
	{
		LicNGLbl->Visible = false;
		LicOkLbl->Visible = true;
	}
	else
	{
		LicNGLbl->Visible = true;
		LicOkLbl->Visible = false;
	}
	//OS情報の取得
	OSInf.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&OSInf);
	//バージョンテキスト
	VerText = OSInf.szCSDVersion;
	//OS名の取得
	if(OSInf.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
	{
		if(OSInf.dwMajorVersion == 4)
		{
			if(OSInf.dwMinorVersion == 0)
			{
				if(VerText == "B" || VerText == "C")
				{
					OSName = "Windows 95 OSR2";
				}
				else
				{
					OSName = "Windows 95";
				}
			}
			else if(OSInf.dwMinorVersion == 10)
			{
				if(VerText == "A")
				{
					OSName = "Windows 98 SE";
				}
				else
				{
					OSName = "Windows 98";
				}
			}
			else if(OSInf.dwMinorVersion == 90)
			{
				OSName = "Windows ME";
			}
		}
	}
	else if(OSInf.dwPlatformId == VER_PLATFORM_WIN32_NT)
	{
		if(OSInf.dwMajorVersion == 3)
		{
			OSName = "Windows NT 3.x";
		}
		else if(OSInf.dwMajorVersion == 4)
		{
			if(OSInf.dwMinorVersion == 0)
			{
				OSName = "Windows NT 4.0";
			}
		}
		else if(OSInf.dwMajorVersion == 5)
		{
			if(OSInf.dwMinorVersion == 0)
			{
				OSName = "Windows 2000";
			}
			else if(OSInf.dwMinorVersion == 1)
			{
				OSName = "Windows XP";
			}
			else if(OSInf.dwMinorVersion == 2)
			{
				OSName = "Windows .NET Server";
			}
		}
		else if(OSInf.dwMajorVersion == 6)
		{
			OSName = "Windows Vista";
		}
	}
	//ビルド番号
	Build = (OSInf.dwBuildNumber & 0xffff);
	//表示文字列組み立て
	if(OSName == "")
	{
		OSDispStr = "";
	}
	else if(OSInf.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
	{
		OSDispStr = OSName + " (Build:" + Build + ")";
	}
	else if(OSInf.dwPlatformId == VER_PLATFORM_WIN32_NT)
	{
		OSDispStr = OSName + " " + VerText  + " (Build:" + Build + ")";
	}
	//表示
	OSLbl->Caption = OSDispStr;
	//ファイルバージョン情報の取得
	GetFileVer();
	//CPU使用率表示初期化
	if(nsCPURatio::Init() == true)
	{
		CPULbl        ->Caption = "CPU使用率";
		CPULbl        ->Visible = true;
		CPUProgressBar->Visible = true;
	}
	//Copyright表示
	unsigned short year;
	unsigned short month;
	unsigned short day;
	String Copyright;
	TDateTime today = TDateTime::CurrentDate();
	today.DecodeDate(&year,&month,&day);
	Copyright.sprintf(L"Copyright(C) 2007-%d さくら電算",year);
	CopyrightLbl->Caption = Copyright;


	//監視タイマー起動
	Timer->Enabled = true;
}
//---------------------------------------------------------------------------
//  機能     ：フォームを閉じる時
//
//  関数定義 ：void __fastcall FormClose(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TAboutBox::FormClose(TObject *Sender, TCloseAction &Action)
{
	//監視タイマー終了
	Timer->Enabled = false;
	//CPU表示終了
	CPULbl        ->Visible = false;
	CPUProgressBar->Visible = false;
}
//---------------------------------------------------------------------------
//  機能     ：監視タイマー処理時
//
//  関数定義 ：void __fastcall TimerTimer(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：TObject *Sender
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TAboutBox::TimerTimer(TObject *Sender)
{
	MEMORYSTATUS stat;
	//初期化
	stat.dwLength = sizeof(MEMORYSTATUS);
	//メモリー使用情報を得る
	GlobalMemoryStatus(&stat);
	//メモリー使用率
	MemoryLbl        ->Caption  = String("メモリ使用率 ") + stat.dwMemoryLoad + "%";
	MemoryProgressBar->Position = stat.dwMemoryLoad;

	//CPU使用率
	if(CPULbl->Visible == true)
	{
		int Ratio;

		Ratio = nsCPURatio::GetRatio();

		if(Ratio >= 0)
		{
			CPULbl        ->Caption  = String("CPU使用率 ") + Ratio + "%";
			CPUProgressBar->Position = Ratio;
		}
	}
}

/*
 * GetProcessorInformation
 *
 * Description:
 *   プロセッサ情報を取得します。
 */
void TAboutBox::GetProcessorInformation(LPTSTR pProcArchitecture,
                             LPTSTR pProcLevel,
                             LPDWORD pProcCount)
{
    SYSTEM_INFO sys_info;

    /*
     * GetSystemInfo API を呼び出してプロセッサ情報を取得します。
     */
    GetSystemInfo(&sys_info);

    /*
     * Windows では Intel 以外のアーキテクチャはすべて無効ですので、
     * 混乱を避けるために場合を分けてプロセッサ情報を文字列に変換します。
     */
    if (!(GetVersion() & 0x80000000))
	{
        switch (sys_info.wProcessorArchitecture) {
        case PROCESSOR_ARCHITECTURE_INTEL:
            lstrcpy(pProcArchitecture, TEXT("Intel"));
            wsprintf(pProcLevel, TEXT("%ld86"),
                     (DWORD)sys_info.wProcessorLevel);
            break;
        case PROCESSOR_ARCHITECTURE_MIPS:
            lstrcpy(pProcArchitecture, TEXT("MIPS"));
            wsprintf(pProcLevel, TEXT("R%ld000"),
                     (DWORD)(sys_info.wProcessorLevel >> 8));
            break;
        case PROCESSOR_ARCHITECTURE_ALPHA:
            lstrcpy(pProcArchitecture, TEXT("Alpha"));
            wsprintf(pProcLevel, TEXT("%ld"),
                     (DWORD)sys_info.wProcessorLevel);
            break;
        case PROCESSOR_ARCHITECTURE_PPC:
            lstrcpy(pProcArchitecture, TEXT("Power PC"));
            if (sys_info.wProcessorLevel == 6) {
                wsprintf(pProcLevel, TEXT("603+"));
            } else if (sys_info.wProcessorLevel == 9) {
                wsprintf(pProcLevel, TEXT("604+"));
            } else {
                wsprintf(pProcLevel, TEXT("6%02d"),
                         (DWORD)sys_info.wProcessorLevel);
            }
            break;
        default:
            lstrcpy(pProcArchitecture, TEXT("(Unknown Processor)"));
            lstrcpy(pProcLevel, TEXT(""));
        }
    } else {
        switch (sys_info.dwOemId) {
        case PROCESSOR_ARCHITECTURE_INTEL:
            lstrcpy(pProcArchitecture, TEXT("Intel"));
            wsprintf(pProcLevel, TEXT("%ld86"),
                     (DWORD)sys_info.wProcessorLevel);
            break;
        default:
            lstrcpy(pProcArchitecture, TEXT("(Unknown Processor)"));
            lstrcpy(pProcLevel, TEXT(""));
        }
    }

    /*
     * プロセッサの個数を格納します。
     */
    *pProcCount = sys_info.dwNumberOfProcessors;
}

//---------------------------------------------------------------------------
//  機能     ：ファイルバージョン情報の取得
//
//  関数定義 ：void GetFileVer()
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
void TAboutBox::GetFileVer()
{
	typedef struct
	{
		WORD wLanguage;
		WORD wCodePage;
	} LANGANDCODEPAGE, *LPLANGANDCODEPAGE;



	VS_FIXEDFILEINFO vffi;           // バージョン情報を受け取る構造体
	wchar_t          ExeName[512];
	wchar_t          VerOrgStr[512];
	String           VerStr;
	String           BuildStr;

	wcscpy(ExeName,Application->ExeName.c_str());
	unsigned int size = GetFileVersionInfoSize(ExeName, 0);
	byte *vbuf = new byte[size];



	if (GetFileVersionInfo(ExeName, 0, size, vbuf))
	{
		String strwork;

		void    *buf;
		wchar_t *pbuf;

		VerQueryValue(vbuf,TEXT("\\"),&buf,&size);         // バージョンを取得
		CopyMemory( &vffi, buf, sizeof(VS_FIXEDFILEINFO)); //コピー

		LPLANGANDCODEPAGE lplgcode;
		UINT unLen;
		BOOL bret = VerQueryValue(vbuf,L"\\VarFileInfo\\Translation",(LPVOID *)&lplgcode, &unLen);

		if( bret == FALSE)
		{
			return;
		}
		for( UINT i = 0;i < unLen / sizeof( LANGANDCODEPAGE); i++)
		{
			strwork.sprintf(L"\\StringFileInfo\\%04x%04x\\FileVersion",lplgcode[i].wLanguage, lplgcode[i].wCodePage);
			VerQueryValue( vbuf,strwork.c_str(),(LPVOID *)&pbuf, &unLen);
			if( unLen > 0)
			{
				wcscpy(VerOrgStr,pbuf);
				break;
			}
		}
		//開放
		delete []vbuf;
		//右から.を検索
		wchar_t *p = wcsrchr(VerOrgStr,L'.');
		//バージョンの分離
		if(p)
		{
			*p       = '\0';
			VerStr   = VerOrgStr;
			BuildStr = (p+1);
		}


	}
	//表示
	if(VerStr != "" && BuildStr != "")
	{
		VerLbl->Caption = String("Version ") + VerStr + " Build(" + BuildStr +")";
	}
	else
	{
		VerLbl->Caption = String("Version 1.0");
	}
}


//---------------------------------------------------------------------------

