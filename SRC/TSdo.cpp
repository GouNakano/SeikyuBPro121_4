//---------------------------------------------------------------------------
#include <vcl.h>
#include <System.IOUtils.hpp>
#include <System.IniFiles.hpp>
#include <System.SysUtils.hpp>
#pragma hdrstop

#include <io.h>
#include "strconv.h"
#include "nsShellApi.h"
#include "TSFileCL.h"
#include "TSCommonLib.h"
#include "SeikyuBDef.h"
#include "THistories.h"
#include "TStdComponents.h"
#include "typDocComponentDefs.h"
#include "TZooms.h"
#include "TCompanyInfos.h"
#include "TSdo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
//Iniにフォント設定の情報をセット
//---------------------------------------------------------------------------
void TSdo::SetColInfToIni(TMemIniFile *Ini,String Sec,String Val,typFontDef& ECol)
{
	String Str;
	//セットする文字列作成
	Str.sprintf(L"%s,%d,%d,%d,%d,%d",
		ECol.Name.c_str(),
		ECol.Size,
		(int)ECol.Color,
		(ECol.Bold == true),
		(ECol.Italic == true),
		(ECol.Under == true)
	);
	//文字列をセットする
	Ini->WriteString(Sec,Val,Str);
}
//---------------------------------------------------------------------------
//フォルダーを削除する
//---------------------------------------------------------------------------
bool TSdo::deleteDir(const String folder_path)
{
	//\で終わっていると削除できない
	String dir = ExcludeTrailingPathDelimiter(folder_path);

	//終端文字は\0\0
	std::vector<wchar_t> from(dir.Length() + 2,L'\0');
	wcscpy(from.data(), dir.c_str());

	SHFILEOPSTRUCT fs;
	ZeroMemory(&fs, sizeof(SHFILEOPSTRUCT));
	fs.hwnd = Application->Handle;
	fs.wFunc = FO_DELETE;
	fs.pFrom = (decltype(fs.pFrom))from.data();
	fs.pTo = NULL;
	//進捗ダイアログ表示をやめる(FOF_SILENT)
	fs.fFlags=FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOERRORUI;

	//処理結果
	bool result = (SHFileOperation(&fs) == 0);

	return result;
}
//---------------------------------------------------------------------------
//Iniからフォント設定の情報を読む
//---------------------------------------------------------------------------
typFontDef TSdo::GetColInfFromIni(TMemIniFile *Ini,String Sec,String Val)
{
	String               Buf;
	std::vector<String>  sptr;
	typFontDef           Res;
	//Iniから読む
	String Str = Ini->ReadString(Sec,Val,"").Trim();

	//内容が無い場合の処理
	if(Str == L"")
	{
		return Res;
	}
	//カンマで分解
	int DivNum = TSCommonLib::CSVDivide(sptr,Str);

	if(DivNum > 0)
	{
		Res.Name = sptr[0];
	}
	if(DivNum > 1)
	{
		Res.Size = _wtoi(sptr[1].c_str());
	}
	if(DivNum > 2)
	{
		Res.Color = (TColor)_wtoi(sptr[2].c_str());
	}
	if(DivNum > 3)
	{
		Res.Bold = (_wtoi(sptr[3].c_str()) > 0);
	}
	if(DivNum > 4)
	{
		Res.Italic = (_wtoi(sptr[4].c_str()) > 0);
	}
	if(DivNum > 5)
	{
		Res.Under = (_wtoi(sptr[5].c_str()) > 0);
	}
	return Res;
}
//---------------------------------------------------------------------------
//sdoファイルを展開する
//---------------------------------------------------------------------------
bool TSdo::expandSDO(const String sdo_file,std::unique_ptr<TMemIniFile>& pIni,String& TmpIniPath)
{
	//ファイルの存在を確認する
	if(sdo_file != L"" && _waccess(sdo_file.c_str(),00) != 0)
	{
		//データIniファイルはなし
		TmpIniPath = L"";

		return false;
	}
	//テンポラリディレクトリ
	String tempdir = TPath::GetTempPath();
	//一時ディレクトリのパス
	String TmpDir = String(tempdir) + L"__sbdir";
	//一時ディレクトリを削除する
	deleteDir(TmpDir);
	//一時ディレクトリを作成する
	TSDirectoryCL Dirs;
	Dirs.MakeDirectory(TmpDir.c_str());
	//カレントディレクトリを設定
	SetCurrentDir(TmpDir);
	//コピーする
	String CabFile = TmpDir + "\\_sb.cab";
	CopyFile(sdo_file.c_str(),CabFile.c_str(),FALSE);
	//解凍する
	String Cmd = String(L"_sb.cab . -F:*");
	nsShellApi::ShellAndWait(L"expand",Cmd.c_str(),SW_HIDE);
	//データIniファイル
	TmpIniPath = TmpDir + L"\\" + INI_TEMP_SDO_INI;
	//Iniファイルを開く
	if(sdo_file != L"")
	{
		//Iniファイルを開く
		pIni.reset(new TMemIniFile(TmpIniPath));
	}
	else
	{
		//Iniファイルを開く
		pIni.reset(new TMemIniFile(""));
	}
	return true;
}
//---------------------------------------------------------------------------
//基礎情報のセット
//---------------------------------------------------------------------------
bool TSdo::setBasicInfo(std::unique_ptr<TMemIniFile>& pIni,const String& sdo_file,const String& fileID,typDocument& DocInfo)
{
	try
	{
		String        Val;
		typPaperDef   pPaperDef;
		typDocKindDef pDocKindDef;
		typZoomDef    pZoomDef;

		//初期化
		DocInfo.ClearDocCompo();
		//--- 基礎情報 ---
		//ファイルパスセット
		DocInfo.File    = sdo_file;
		//履歴ID
		DocInfo.HistID  = fileID;
		//用紙名
		Val             = pIni->ReadString (S_SECTION_SETTING,V_PAPER_SIZE,PaperDef[A4P].PaperName);
		TPaperDefs::GetPaperDefFromName(Val,pPaperDef);
		DocInfo.Paper   = pPaperDef.Number;

		//用紙種別
		Val             = pIni->ReadString (S_SECTION_SETTING,V_DOCKIND,DocKindDef[pmSeikyu].KindName);
		compo.GetDocKindDefFromName(Val,pDocKindDef);
		DocInfo.DocKind = pDocKindDef.Number;

		//ズーム
		Val             = pIni->ReadString (S_SECTION_SETTING,V_ZOOM,ZoomDef[Z60].ZoomName);
		TZooms::GetZoomDefFromName(Val,pZoomDef);
		DocInfo.Zoom    = pZoomDef.Number;

		//バージョン
		DocInfo.Version = pIni->ReadInteger(S_SECTION_SETTING,V_VERSION,0);
	}
	catch(Exception& e)
	{
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
//部品情報の読み出し
//---------------------------------------------------------------------------
bool TSdo::readComponents(std::unique_ptr<TMemIniFile>& pIni,typDocument& DocInfo)
{
	String        Val;
	typDocCompo   pDoc;
	typPaperDef   pPaperDef;
	typDocKindDef pDocKindDef;
	typDocComponentDef pDocComponentDef;

	try
	{
		//セクション一覧を得る
		std::unique_ptr<TStringList> pSections(new TStringList);
		pIni->ReadSections(pSections.get());
		//部品情報の読み出し
		for(int Cnt = 0;Cnt < pSections->Count;Cnt++)
		{
			String      PaperName;
			String      CompoName;
			String      DocKindName;
			String      DocComponentName;
			int         DivPos;
			//セクション名
			String SecName = pSections->Strings[Cnt];
			//-の位置を確認
			DivPos = SecName.Pos("-");
			if(DivPos < 2)
			{
				continue;
			}
			//-の前後で分解(用紙名とその後)
			PaperName = SecName.SubString(1         ,DivPos - 1).Trim();
			Val       = SecName.SubString(DivPos + 1,SecName.Length()).Trim();
			//-の位置を確認
			DivPos = Val.Pos("-");
			//-の前後で分解(書類種類と部品名)
			if(DivPos < 2)
			{
				DocKindName = DocKindDef[pmSeikyu].KindName;
				CompoName   = Val;
			}
			else
			{
				DocKindName = Val.SubString(1       ,DivPos-1);
				CompoName   = Val.SubString(DivPos+1,Val.Length());
			}
			//データセクションは除外
			if(CompoName == L"DOCDATA")
			{
				continue;
			}
			//名前
			pDoc.Name           = CompoName;
			//整列方法
			pDoc.Alignment      = (System::Classes::TAlignment)pIni->ReadInteger(SecName,V_ALIGNMENT,taLeftJustify);
			//枠の有無
			pDoc.Border         = pIni->ReadBool(SecName,V_BORDER,false);
			//用紙情報
			pDoc.Paper          = DocInfo.Paper;
			//書類種類
			pDoc.DocKind        = DocInfo.DocKind;
			//部品の種類
			DocComponentName    = pIni->ReadString (SecName,V_TYPE,"");
			typDocComponentDefs::GetDocComponentDefFromName(DocComponentName,pDocComponentDef);

			if(pDocComponentDef.Number != dcUnknown)
			{
				//型を設定
				pDoc.Type  = pDocComponentDef.Number;
			}
			else
			{
				//名前から標準コンポーネント情報を得る
				typStdComponentDef pStd;
				bool std_valid = compo.GetStdComponentDefFromName(pDoc.Name,pStd,DocInfo.DocKind);
				//型を設定
				if(std_valid == true)
				{
					pDoc.Type  = pStd.CompoKind;
				}
				else
				{
					pDoc.Type  = dcUnknown;
				}
			}
			//表示するか
			pDoc.Visible        = pIni->ReadBool(SecName,V_VISIBLE,true);
			//印刷するか
			pDoc.IsPrint        = pIni->ReadBool(SecName,V_PRINT,true);
			//X座標(1/100 mm単位)
			Val                 = pIni->ReadString (SecName,V_LEFT,L"0.0");
			pDoc.X              = _wtold(Val.c_str());
			//Y座標(1/100 mm単位)
			Val                 = pIni->ReadString (SecName,V_TOP,L"0.0");
			pDoc.Y              = _wtold(Val.c_str());
			//幅(1/100 mm単位)
			Val                 = pIni->ReadString (SecName,V_WIDTH,L"0.0");
			pDoc.Width          = _wtold(Val.c_str());
			//高さ(1/100 mm単位)
			Val                 = pIni->ReadString (SecName,V_HEIGHT,L"0.0");
			pDoc.Height         = _wtold(Val.c_str());
			//フォント情報
			pDoc.Font           = GetColInfFromIni(pIni.get(),SecName,V_FONT_INFO);
			//キャプション(内容)
			pDoc.Caption        = pIni->ReadString (SecName,V_CAPTION,L"");
			//行数
			pDoc.RowNum         = pIni->ReadInteger(SecName,V_ROWNUM,0);
			//列数
			pDoc.ColNum         = pIni->ReadInteger(SecName,V_COLNUM,0);
			//桁数
			pDoc.Figures        = pIni->ReadInteger(SecName,V_FIGURES,7);
			//桁区切り線の有無
			pDoc.FigureLine     = pIni->ReadBool(SecName,V_FIGURE_LINE,false);
			//リストに追加
			//書類部品情報名から書類部品情報をセット
			DocInfo.SetDocCompoFromName(CompoName,pDoc);
		}
	}
	__finally
	{
	}

	return true;
}
//---------------------------------------------------------------------------
//書類ファイルのデータ読み込み
//---------------------------------------------------------------------------
bool TSdo::loadDocumentData(std::unique_ptr<TMemIniFile>& pIni,typDocument& DocInfo)
{
	String Val;
	String ImgFile;

	//読み込み処理
	try
	{
		//iniファイルのパス
		String FilePath = pIni->FileName;
		//Iniファイルの格納ディレクトリを得る
		String FileDir = ExtractFileDir(FilePath) + L"\\";
		//今日の日付
		TDateTime Today = TDateTime::CurrentDate();
		//データの読み出し
		for(int KindCnt = 0;KindCnt < DOCUMENT_KIND_NUM;KindCnt++)
		{
			//対象書類
			const typDocKindDef& DocKind = DocKindDef[KindCnt];
			//セクション名
			String SecName = String(DocKind.KindName) + L"-DOCDATA";
			//対象データ構造体
			typDocData& DocData = DocInfo.Data[KindCnt];
			//書類データ設定
			if(ES.IsToday == true)
			{
				//本日の日付を入れる
				DocData.Year      = pIni->ReadString(SecName,StdComponents[scYearEdit    ].Name,Today.FormatString("yyyy")).c_str(); //年
				DocData.Month     = pIni->ReadString(SecName,StdComponents[scMonthEdit   ].Name,Today.FormatString("m")).c_str();    //月
				DocData.Day       = pIni->ReadString(SecName,StdComponents[scDayEdit     ].Name,Today.FormatString("d")).c_str();    //日
			}
			else
			{
				//本日の日付を入ない
				DocData.Year      = pIni->ReadString(SecName,StdComponents[scYearEdit    ].Name,"").c_str(); //年
				DocData.Month     = pIni->ReadString(SecName,StdComponents[scMonthEdit   ].Name,"").c_str(); //月
				DocData.Day       = pIni->ReadString(SecName,StdComponents[scDayEdit     ].Name,"").c_str(); //日
			}
			DocData.No                 = pIni->ReadString(SecName,StdComponents[scNoEdit              ].Name,"");         //番号
			DocData.Name               = pIni->ReadString(SecName,StdComponents[scNameEdit            ].Name,"");         //名前
			DocData.Item               = pIni->ReadString(SecName,StdComponents[scItemEdit            ].Name,"");         //件名
			DocData.Money              = pIni->ReadString(SecName,StdComponents[scMoneyEdit           ].Name,"").c_str(); //請求金額
			DocData.Subtotal           = pIni->ReadString(SecName,StdComponents[scSubtotalEdit        ].Name,"").c_str(); //小計
			DocData.Tax                = pIni->ReadString(SecName,StdComponents[scTaxEdit             ].Name,"").c_str(); //消費税
			DocData.Total              = pIni->ReadString(SecName,StdComponents[scTotalEdit           ].Name,"").c_str(); //合計
			DocData.CustomerZipCode    = pIni->ReadString(SecName,StdComponents[scCustomerZipCodeEdit ].Name,"");         //客先郵便番号
			DocData.CustomerAddress1   = pIni->ReadString(SecName,StdComponents[scCustomerAddress1Edit].Name,"");         //客先住所1
			DocData.CustomerAddress2   = pIni->ReadString(SecName,StdComponents[scCustomerAddress2Edit].Name,"");         //客先住所2
			DocData.CustomerTEL        = pIni->ReadString(SecName,StdComponents[scCustomerTELEdit     ].Name,"");         //客先電話番号
			DocData.CustomerFAX        = pIni->ReadString(SecName,StdComponents[scCustomerFAXEdit     ].Name,"");         //客先FAX番号
			//ラベル内容設定
			DocData.YearLabel          = pIni->ReadString(SecName,StdComponents[scYearLabel          ].Name,"年");       //年ラベル
			DocData.MonthLabel         = pIni->ReadString(SecName,StdComponents[scMonthLabel         ].Name,"月");       //月ラベル
			DocData.DayLabel           = pIni->ReadString(SecName,StdComponents[scDayLabel           ].Name,"日");       //日ラベル
			DocData.NumberLabel        = pIni->ReadString(SecName,StdComponents[scNumberLabel        ].Name,"No.");      //書類番号ラベル
			DocData.TitleLabel         = pIni->ReadString(SecName,StdComponents[scTitleLabel         ].Name,"件名");     //件名ラベル
			DocData.HonorificTitleLabel= pIni->ReadString(SecName,StdComponents[scHonorificTitleLabel].Name,"様");       //敬称ラベル
			DocData.CompanyNameLabel   = pIni->ReadString(SecName,StdComponents[scCompanyNameLabel   ].Name,"");         //会社名ラベル
			DocData.PersonLabel        = pIni->ReadString(SecName,StdComponents[scPersonLabel        ].Name,"");         //代表者ラベル
			DocData.ZipCodeLabel       = pIni->ReadString(SecName,StdComponents[scZipCodeLabel       ].Name,"");         //郵便番号ラベル
			DocData.AddressLabel1      = pIni->ReadString(SecName,StdComponents[scAddressLabel1      ].Name,"");         //住所１ラベル
			DocData.AddressLabel2      = pIni->ReadString(SecName,StdComponents[scAddressLabel2      ].Name,"");         //住所２ラベル
			DocData.TELLabel           = pIni->ReadString(SecName,StdComponents[scTELLabel           ].Name,"");         //電話番号ラベル
			DocData.FAXLabel           = pIni->ReadString(SecName,StdComponents[scFAXLabel           ].Name,"");         //ＦＡＸ番号ラベル
			DocData.UnitLabel          = pIni->ReadString(SecName,StdComponents[scUnitLabel          ].Name,"単位:円");  //単位ラベル
			DocData.SubTotalLabel      = pIni->ReadString(SecName,StdComponents[scSubTotalLabel      ].Name,"小計");     //小計ラベル
			DocData.TaxLabel           = pIni->ReadString(SecName,StdComponents[scTaxLabel           ].Name,"消費税");   //消費税ラベル
			DocData.TotalLabel         = pIni->ReadString(SecName,StdComponents[scTotalLabel         ].Name,"合計金額"); //合計金額ラベル
			DocData.NoteLabel          = pIni->ReadString(SecName,StdComponents[scNoteLabel          ].Name,"備考");     //備考ラベル
			//書類種類ごとのラベルの設定
			switch(KindCnt)
			{
				case pmSeikyu:
				{
					DocData.BillLabel          = pIni->ReadString(SecName,StdComponents[scBillLabel          ].Name,"請 求 書");                     //書類種類名ラベル
					DocData.RequestLabel       = pIni->ReadString(SecName,StdComponents[scRequestLabel       ].Name,"下記の通りご請求申し上げます"); //用件ラベル
					DocData.ChargedAmountLabel = pIni->ReadString(SecName,StdComponents[scChargedAmountLabel ].Name,"御請求金額");                   //金額ラベル
					DocData.TransferLabel1     = pIni->ReadString(SecName,StdComponents[scTransferLabel1     ].Name,"振込先:");                      //振込先１ラベル
					DocData.TransferLabel2     = pIni->ReadString(SecName,StdComponents[scTransferLabel2     ].Name,"振込先:");                      //振込先２ラベル
					break;
				}
				case pmNouhin:
				{
					DocData.BillLabel          = pIni->ReadString(SecName,StdComponents[scBillLabel          ].Name,"納 品 書");                 //書類種類名ラベル
					DocData.RequestLabel       = pIni->ReadString(SecName,StdComponents[scRequestLabel       ].Name,"下記の通り納品致しました"); //用件ラベル
					DocData.ChargedAmountLabel = pIni->ReadString(SecName,StdComponents[scChargedAmountLabel ].Name,"合計金額");                 //金額ラベル
					DocData.TransferLabel1     = pIni->ReadString(SecName,StdComponents[scTransferLabel1     ].Name,"");                         //振込先１ラベル
					DocData.TransferLabel2     = pIni->ReadString(SecName,StdComponents[scTransferLabel2     ].Name,"");                         //振込先２ラベル
					break;
				}
				case pmMitsumori:
				{
					DocData.BillLabel          = pIni->ReadString(SecName,StdComponents[scBillLabel          ].Name,"見 積 書");                       //書類種類名ラベル
					DocData.RequestLabel       = pIni->ReadString(SecName,StdComponents[scRequestLabel       ].Name,"下記の通りお見積り申し上げます"); //用件ラベル
					DocData.ChargedAmountLabel = pIni->ReadString(SecName,StdComponents[scChargedAmountLabel ].Name,"合計金額");                       //金額ラベル
					DocData.TransferLabel1     = pIni->ReadString(SecName,StdComponents[scTransferLabel1     ].Name,"");                               //振込先１ラベル
					DocData.TransferLabel2     = pIni->ReadString(SecName,StdComponents[scTransferLabel2     ].Name,"");                               //振込先２ラベル
					break;
				}
			}
			//画像の設定
			if(FilePath != L"")
			{
				//印影１
				try
				{
					ImgFile.sprintf(INI_STAMP1_FILE,FileDir.c_str(),KindCnt);
					DocData.StampImage1->LoadFromFile(ImgFile);
				}
				catch(...)
				{
				}
				//印影２
				try
				{
					ImgFile.sprintf(INI_STAMP2_FILE,FileDir.c_str(),KindCnt);
					DocData.StampImage2->LoadFromFile(ImgFile);
				}
				catch(...)
				{
				}
				//ロゴ
				try
				{
					ImgFile.sprintf(INI_LOGO_FILE,FileDir.c_str(),KindCnt);
					DocData.LogoImage->LoadFromFile(ImgFile);
				}
				catch(...)
				{
				}
			}
            //自社情報を得る
			TCompanyInfos CompanyInfo;
			CompanyInfo.ReadCompanyInfo();
			//消費税率を得る
			try
			{
				DocData.ConsumptionTaxRatio = pIni->ReadString(SecName,COMPANY_INFO_TAXRATIO,CompanyInfo[0].TaxRatio).Trim();
			}
			catch(...)
			{
				long TaxVal;
				TaxVal                       = pIni->ReadInteger(SecName,COMPANY_INFO_TAXRATIO,CompanyInfo[0].TaxRatio.ToIntDef(STD_TAXRATIO));
				DocData.ConsumptionTaxRatio  = String(TaxVal);
			}
		}
		//変更はなし
		DocInfo.Edited = false;
	}
	__finally
	{
	}
	return true;
}
//---------------------------------------------------------------------------
//グリッドのデータ読み込み
//---------------------------------------------------------------------------
bool TSdo::loadGridData(std::unique_ptr<TMemIniFile>& pIni,typDocument& DocInfo)
{
	String              Val;
	String              SecName;

	//読み込み処理
	try
	{
		//データの読み出し
		for(int KindCnt = 0;KindCnt < DOCUMENT_KIND_NUM;KindCnt++)
		{
			//対象書類
			const typDocKindDef& DocKind = DocKindDef[KindCnt];
			//セクション名
			String SecName = String(DocKind.KindName) + L"-DOCDATA";
			//対象データ構造体
			typDocData& DocData = DocInfo.Data[KindCnt];
			//グリッドデータ初期化
			DocData.GridData.clear();
			//グリッド内容の読み出し
			for(int Row = 1;;Row++)
			{
				//一行分のデータ作成
				typDocOneRowData RowData;
				//Value名
				String ValueName;
				ValueName.sprintf(L"D%02d",Row);
				//一行分のデータを得る
				String GridStr = pIni->ReadString(SecName,ValueName,L"").Trim();
				//内容が空の場合は処理終了
				if(GridStr == L"")
				{
					break;
				}
				//カンマで分解
				std::vector<String> pStrs;
				int DivNum = TSCommonLib::CSVDivide(pStrs,GridStr);
				//分解数チェック
				if(DivNum == STD_GRID_COLNUM)
				{
					String ItemBuf = StringReplace(pStrs[0],L"\\r\\n",L"\r\n", TReplaceFlags() << rfReplaceAll);
					String NameBuf = StringReplace(pStrs[1],L"\\r\\n",L"\r\n", TReplaceFlags() << rfReplaceAll);

					RowData.Item       = ItemBuf;
					RowData.Name       = NameBuf;
					RowData.Num        = pStrs[2].c_str();
					RowData.PriceUnit  = pStrs[3].c_str();
					RowData.Money      = pStrs[4].c_str();
					RowData.Unit       = pStrs[5].c_str();
				}
				else if(DivNum == 5)
				{
					String ItemBuf = StringReplace(pStrs[0],L"\\r\\n",L"\r\n", TReplaceFlags() << rfReplaceAll);
					String NameBuf = StringReplace(pStrs[1],L"\\r\\n",L"\r\n", TReplaceFlags() << rfReplaceAll);

					RowData.Item       = ItemBuf;
					RowData.Name       = NameBuf;
					RowData.Num        = pStrs[2].c_str();
					RowData.PriceUnit  = pStrs[3].c_str();
					RowData.Money      = pStrs[4].c_str();
					RowData.Unit       = L"";
				}
				else
				{
					RowData.Item       = L"";
					RowData.Name       = L"";
					RowData.Num        = L"";
					RowData.PriceUnit  = L"";
					RowData.Money      = L"";
					RowData.Unit       = L"";
				}
				//リストに追加
				DocData.GridData.push_back(std::move(RowData));
			}
		}
		//変更はなし
		DocInfo.Edited = false;
	}
	__finally
	{
	}
	return true;
}
//---------------------------------------------------------------------------
//書類情報のバージョン更新
//---------------------------------------------------------------------------
bool TSdo::updateDocumentVersion(typDocument& DocInfo)
{
	//バージョン毎の処理
	if(DocInfo.Version < 1)
	{
		typDocCompo  pDoc;
		//バージョン番号更新
		DocInfo.Version = 1;
		//グリッドの情報
		typDocCompo  pGridDoc;
		DocInfo.GetDocCompoFromName(StdComponents[scStdComponent::scGrid].Name,pGridDoc);
		//列数を６にする
		pGridDoc.ColNum = 6;
		//数量の列のデータ取得
		typDocCompo pNum;
		DocInfo.GetDocCompoFromName("D_00_02",pNum);
		//最終列のデータを作成
		typDocCompo pFromDoc;
		typDocCompo pToDoc;

		DocInfo.GetDocCompoFromName("D_00_04",pFromDoc);
		pDoc                = pFromDoc;
		pDoc.X              = pFromDoc.X + pNum.Width;
		pDoc.Name           = L"D_00_05";
		DocInfo.SetDocCompoFromName(L"D_00_05",pDoc);
		//５列目(単価)の設定
		DocInfo.GetDocCompoFromName("D_00_03",pFromDoc);
		DocInfo.GetDocCompoFromName("D_00_04",pToDoc);
		pToDoc              = pFromDoc;
		pToDoc.X            = pFromDoc.X + pNum.Width;
		pToDoc.Name         = L"D_00_04";
		DocInfo.SetDocCompoFromName(L"D_00_04",pToDoc);
		//４列目(単位)の設定
		DocInfo.GetDocCompoFromName("D_00_02",pFromDoc);
		DocInfo.GetDocCompoFromName("D_00_03",pToDoc);
		pToDoc              = pFromDoc;
		pToDoc.Name         = L"D_00_03";
		pToDoc.X            = pFromDoc.X + pNum.Width;
		pToDoc.FigureLine   = false;
		pToDoc.Caption      = L"単位";

		DocInfo.SetDocCompoFromName(L"D_00_03",pToDoc);
	}
	if(DocInfo.Version < 2)
	{
		typDocCompo  pDoc;
		//バージョン番号更新
		DocInfo.Version = 2;
		//項目の列のテキスト揃え
		DocInfo.GetDocCompoFromName("D_00_00",pDoc);
		pDoc.Alignment = taCenter;
		DocInfo.SetDocCompoFromName("D_00_03",pDoc);
		//品目名の列のテキスト揃え
		DocInfo.GetDocCompoFromName("D_00_01",pDoc);
		pDoc.Alignment = taLeftJustify;
		DocInfo.SetDocCompoFromName("D_00_01",pDoc);
		//数量の列のテキスト揃え
		DocInfo.GetDocCompoFromName("D_00_02",pDoc);
		pDoc.Alignment = taRightJustify;
		DocInfo.SetDocCompoFromName("D_00_02",pDoc);
		//単位の列のテキスト揃え
		DocInfo.GetDocCompoFromName("D_00_03",pDoc);
		pDoc.Alignment = taCenter;
		DocInfo.SetDocCompoFromName("D_00_03",pDoc);
		//単価の列のテキスト揃え
		DocInfo.GetDocCompoFromName("D_00_04",pDoc);
		pDoc.Alignment = taRightJustify;
		DocInfo.SetDocCompoFromName("D_00_04",pDoc);
		//金額の列のテキスト揃え
		DocInfo.GetDocCompoFromName("D_00_05",pDoc);
		pDoc.Alignment = taRightJustify;
		DocInfo.SetDocCompoFromName("D_00_05",pDoc);
	}
	return true;
}
//---------------------------------------------------------------------------
//.sdoファイルの読み込み
//---------------------------------------------------------------------------
bool TSdo::readSDO(const String& fileID,typDocument& document)
{
	//該当履歴を取得
	THistory hist;

	if(Histories.get(fileID,hist) == false)
	{
		return false;
	}
	//sdoファイルを取得
	String sdo_file = hist.getFilePath();
	//sdoファイルを展開する
	std::unique_ptr<TMemIniFile> pIni;
	String TmpIniPath;

	try
	{
		//typDocumentの現在の状態を保持
		typDocument DocInfo(document);
		//ファイルの存在を確認する
		if(sdo_file != L"" && _waccess(sdo_file.c_str(),00) != 0)
		{
			return false;
		}
		//sdoファイルを展開する
		if(expandSDO(sdo_file,pIni,TmpIniPath) == false)
		{
			return false;
		}
		//基礎情報のセット
		if(setBasicInfo(pIni,sdo_file,fileID,DocInfo) == false)
		{
			return false;
		}
		//部品情報の読み出し
		if(readComponents(pIni,DocInfo) == false)
		{
			return false;
		}
		//書類ファイルのデータ読み込み
		if(loadDocumentData(pIni,DocInfo) == false)
		{
			return false;
		}
		//グリッドのデータ読み込み
		if(loadGridData(pIni,DocInfo) == false)
		{
			return false;
		}
		//書類情報のバージョン更新
		if(updateDocumentVersion(DocInfo) == false)
		{
			return false;
		}
		//変更はなし
		DocInfo.Edited = false;
		//処理を完走したので読み込んだ情報を反映
		document = DocInfo;
	}
	__finally
	{
		//一時ファイルの存在を確認する
		if(_waccess(TmpIniPath.c_str(),00) != 0)
		{
			_wunlink(TmpIniPath.c_str());
		}
	}

	return true;
}
//---------------------------------------------------------------------------
//テンプレート.sdoファイルの読み込み
//---------------------------------------------------------------------------
bool TSdo::readTemplateSDO(const String& filePath,typDocument& DocInfo)
{
	//sdoファイルを取得
	String sdo_file = filePath;
	//sdoファイルを展開する
	std::unique_ptr<TMemIniFile> pIni;
	String TmpIniPath;

	try
	{
		//ファイルの存在を確認する
		if(sdo_file != L"" && _waccess(sdo_file.c_str(),00) != 0)
		{
			return false;
		}
		//部品情報の読み出し
		if(readComponents(pIni,DocInfo) == false)
		{
			return false;
		}
		//書類ファイルのデータ読み込み
		if(loadDocumentData(pIni,DocInfo) == false)
		{
			return false;
		}
		//グリッドのデータ読み込み
		if(loadGridData(pIni,DocInfo) == false)
		{
			return false;
		}
		//書類情報のバージョン更新
		if(updateDocumentVersion(DocInfo) == false)
		{
			return false;
		}
	}
	__finally
	{
		//一時ファイルの存在を確認する
		if(_waccess(TmpIniPath.c_str(),00) != 0)
		{
			_wunlink(TmpIniPath.c_str());
		}
	}
	//変更はなし
	DocInfo.Edited = false;

	return true;
}
//---------------------------------------------------------------------------
//空読み込み
//---------------------------------------------------------------------------
bool TSdo::readVoid(typDocument& DocInfo)
{
	//Iniファイルを開く
	std::unique_ptr<TMemIniFile> pIni(new TMemIniFile(""));

	try
	{
		//部品情報の読み出し
		if(readComponents(pIni,DocInfo) == false)
		{
			return false;
		}
		//書類ファイルのデータ読み込み
		if(loadDocumentData(pIni,DocInfo) == false)
		{
			return false;
		}
		//グリッドのデータ読み込み
		if(loadGridData(pIni,DocInfo) == false)
		{
			return false;
		}
		//書類情報のバージョン更新
		if(updateDocumentVersion(DocInfo) == false)
		{
			return false;
		}
	}
	__finally
	{
	}
	return true;
}
//---------------------------------------------------------------------------
//基礎情報の保存
//---------------------------------------------------------------------------
bool TSdo::writeBasicInfo(typDocument& DocInfo,std::unique_ptr<TMemIniFile>& pIni)
{
	try
	{
		pIni->WriteString (S_SECTION_SETTING,V_PAPER_SIZE,PaperDef  [Document.Paper  ].PaperName); //用紙名
		pIni->WriteString (S_SECTION_SETTING,V_ZOOM      ,ZoomDef   [Document.Zoom   ].ZoomName ); //ズーム
		pIni->WriteString (S_SECTION_SETTING,V_DOCKIND   ,DocKindDef[Document.DocKind].KindName ); //書類種別
		pIni->WriteInteger(S_SECTION_SETTING,V_VERSION   ,SB_FILE_VERSION                       ); //バージョン
	}
	catch(Exception& e)
	{
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
//書類データの保存
//---------------------------------------------------------------------------
bool TSdo::writeDocInfo(const String& SecName,typDocData& DocData,std::unique_ptr<TMemIniFile>& pIni)
{
	try
	{
		pIni->WriteString(SecName,StdComponents[scYearEdit           ].Name,DocData.Year    .ToStr()   ); //年
		pIni->WriteString(SecName,StdComponents[scMonthEdit          ].Name,DocData.Month   .ToStr()   ); //月
		pIni->WriteString(SecName,StdComponents[scDayEdit            ].Name,DocData.Day     .ToStr()   ); //日
		pIni->WriteString(SecName,StdComponents[scNoEdit             ].Name,DocData.No                 ); //番号
		pIni->WriteString(SecName,StdComponents[scNameEdit           ].Name,DocData.Name               ); //名前
		pIni->WriteString(SecName,StdComponents[scItemEdit           ].Name,DocData.Item               ); //件名
		pIni->WriteString(SecName,StdComponents[scMoneyEdit          ].Name,DocData.Money   .ToStr()   ); //請求金額
		pIni->WriteString(SecName,StdComponents[scSubtotalEdit       ].Name,DocData.Subtotal.ToStr()   ); //小計
		pIni->WriteString(SecName,StdComponents[scTaxEdit            ].Name,DocData.Tax     .ToStr()   ); //消費税
		pIni->WriteString(SecName,StdComponents[scTotalEdit          ].Name,DocData.Total   .ToStr()   ); //合計
		pIni->WriteString(SecName,StdComponents[scCustomerZipCodeEdit ].Name,DocData.CustomerZipCode    ); //客先郵便番号
		pIni->WriteString(SecName,StdComponents[scCustomerAddress1Edit].Name,DocData.CustomerAddress1   ); //客先住所1
		pIni->WriteString(SecName,StdComponents[scCustomerAddress2Edit].Name,DocData.CustomerAddress2   ); //客先住所2
		pIni->WriteString(SecName,StdComponents[scCustomerTELEdit     ].Name,DocData.CustomerTEL        ); //客先電話番号
		pIni->WriteString(SecName,StdComponents[scCustomerFAXEdit     ].Name,DocData.CustomerFAX        ); //客先FAX番号
	}
	catch(Exception& e)
	{
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
//ラベル内容保存
//---------------------------------------------------------------------------
bool TSdo::writeLableInfo(const String& SecName,typDocData& DocData,std::unique_ptr<TMemIniFile>& pIni)
{
	try
	{
		pIni->WriteString(SecName,StdComponents[scYearLabel          ].Name,DocData.YearLabel          ); //年ラベル
		pIni->WriteString(SecName,StdComponents[scMonthLabel         ].Name,DocData.MonthLabel         ); //月ラベル
		pIni->WriteString(SecName,StdComponents[scDayLabel           ].Name,DocData.DayLabel           ); //日ラベル
		pIni->WriteString(SecName,StdComponents[scNumberLabel        ].Name,DocData.NumberLabel        ); //書類番号ラベル
		pIni->WriteString(SecName,StdComponents[scTitleLabel         ].Name,DocData.TitleLabel         ); //件名ラベル
		pIni->WriteString(SecName,StdComponents[scHonorificTitleLabel].Name,DocData.HonorificTitleLabel); //敬称ラベル
		pIni->WriteString(SecName,StdComponents[scCompanyNameLabel   ].Name,DocData.CompanyNameLabel   ); //会社名ラベル
		pIni->WriteString(SecName,StdComponents[scPersonLabel        ].Name,DocData.PersonLabel        ); //代表者ラベル
		pIni->WriteString(SecName,StdComponents[scZipCodeLabel       ].Name,DocData.ZipCodeLabel       ); //郵便番号ラベル
		pIni->WriteString(SecName,StdComponents[scAddressLabel1      ].Name,DocData.AddressLabel1      ); //住所１ラベル
		pIni->WriteString(SecName,StdComponents[scAddressLabel2      ].Name,DocData.AddressLabel2      ); //住所２ラベル
		pIni->WriteString(SecName,StdComponents[scTELLabel           ].Name,DocData.TELLabel           ); //電話番号ラベル
		pIni->WriteString(SecName,StdComponents[scFAXLabel           ].Name,DocData.FAXLabel           ); //ＦＡＸ番号ラベル
		pIni->WriteString(SecName,StdComponents[scUnitLabel          ].Name,DocData.UnitLabel          ); //単位ラベル
		pIni->WriteString(SecName,StdComponents[scSubTotalLabel      ].Name,DocData.SubTotalLabel      ); //小計ラベル
		pIni->WriteString(SecName,StdComponents[scTaxLabel           ].Name,DocData.TaxLabel           ); //消費税ラベル
		pIni->WriteString(SecName,StdComponents[scTotalLabel         ].Name,DocData.TotalLabel         ); //合計金額ラベル
		pIni->WriteString(SecName,StdComponents[scNoteLabel          ].Name,DocData.NoteLabel          ); //備考ラベル
		pIni->WriteString(SecName,StdComponents[scBillLabel          ].Name,DocData.BillLabel          ); //書類種類名ラベル
		pIni->WriteString(SecName,StdComponents[scRequestLabel       ].Name,DocData.RequestLabel       ); //用件ラベル
		pIni->WriteString(SecName,StdComponents[scChargedAmountLabel ].Name,DocData.ChargedAmountLabel ); //金額ラベル
		pIni->WriteString(SecName,StdComponents[scTransferLabel1     ].Name,DocData.TransferLabel1     ); //振込先１ラベル
		pIni->WriteString(SecName,StdComponents[scTransferLabel2     ].Name,DocData.TransferLabel2     ); //振込先２ラベル
	}
	catch(Exception& e)
	{
		return  false;
	}
	return true;
}
//---------------------------------------------------------------------------
//イメージ(印影、ロゴ)の保存
//---------------------------------------------------------------------------
bool TSdo::writeImageInfo(const String& SecName,const String& TmpDirStr,int KindCnt,typDocData& DocData,std::unique_ptr<TStringList>& pFiles,std::unique_ptr<TMemIniFile>& pIni)
{
	try
	{
		String ImgFilePath;

		//印影１ファイルの保存
		ImgFilePath.sprintf(INI_STAMP1_FILE,TmpDirStr.c_str(),KindCnt);
		_wunlink(ImgFilePath.c_str());
		DocData.StampImage1->SaveToFile(ImgFilePath);
		pFiles->Add(ImgFilePath);
		//印影２ファイルの保存
		ImgFilePath.sprintf(INI_STAMP2_FILE,TmpDirStr.c_str(),KindCnt);
		_wunlink(ImgFilePath.c_str());
		DocData.StampImage2->SaveToFile(ImgFilePath);
		pFiles->Add(ImgFilePath);
		//ロゴファイルの保存
		ImgFilePath.sprintf(INI_LOGO_FILE,TmpDirStr.c_str(),KindCnt);
		_wunlink(ImgFilePath.c_str());
		DocData.LogoImage->SaveToFile(ImgFilePath);
		pFiles->Add(ImgFilePath);
	}
	catch(Exception& e)
	{
		return  false;
	}
	return true;
}
//---------------------------------------------------------------------------
//グリッド情報を保存
//---------------------------------------------------------------------------
bool TSdo::writeGridInfo(const String& SecName,typDocData& DocData,std::unique_ptr<TMemIniFile>& pIni)
{
	try
	{
		//グリッド内容の保存
		for(int Row = 1;Row <= DocData.GridData.size();Row++)
		{
			String            ValueName;
			String            GridStr;
			//リストのインデックス
			int Idx = Row - 1;
			//Value名
			ValueName.sprintf(L"D%02d",Row);
			//一行分のデータ取得
			if(Idx < DocData.GridData.size())
			{
				//一行分のデータ取得
				typDocOneRowData& RowData = DocData.GridData[Idx];
				//数値関係データの文字列
				String Num        = RowData.Num      .ToStr();
				String PriceUnit  = RowData.PriceUnit.ToStr();
				String Money      = RowData.Money    .ToStr();

				//改行を\r\nに変換する
				String ItemBuf = StringReplace(RowData.Item,L"\r\n",L"\\r\\n", TReplaceFlags() << rfReplaceAll);
				String NameBuf = StringReplace(RowData.Name,L"\r\n",L"\\r\\n", TReplaceFlags() << rfReplaceAll);

				//一行分のデータ文字列作成
				GridStr.sprintf(L"\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"",
					ItemBuf.c_str(),
					NameBuf.c_str(),
					Num.c_str(),
					PriceUnit.c_str(),
					Money.c_str(),
					RowData.Unit.c_str()
				);
			}
			else
			{
				//一行分のデータ文字列作成
				GridStr.sprintf(L"\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"",
					"",
					"",
					"",
					"",
					"",
					""
				);
			}
			//書き込み
			pIni->WriteString(SecName,ValueName,GridStr);
		}
	}
	catch(Exception& e)
	{
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
//部品情報の保存
//---------------------------------------------------------------------------
bool TSdo::writeCompoInfo(const String& SecName,typDocument& DocInfo,std::unique_ptr<TMemIniFile>& pIni)
{
	for(int Cnt = 0;Cnt < DocInfo.GetCompoSize();Cnt++)
	{
		try
		{
			String Str;
			//部品情報を得る
			typDocCompo& pDoc = DocInfo.GetCompoFromIndex(Cnt);
			//名前チェック
			if(pDoc.Name == L"")
			{
				continue;
			}
			//--- 書き込み ---
			//型
			pIni->WriteString(SecName,V_TYPE,DocComponentDef[pDoc.Type].ComponentName);
			//整列方法
			pIni->WriteInteger(SecName,V_ALIGNMENT,pDoc.Alignment);
			//枠の有無
			pIni->WriteBool(SecName,V_BORDER,(pDoc.Border == true));
			//X座標(1/100 mm単位)
			Str.sprintf(L"%Lf",pDoc.X);
			pIni->WriteString(SecName,V_LEFT,Str);
			//Y座標(1/100 mm単位)
			Str.sprintf(L"%Lf",pDoc.Y);
			pIni->WriteString(SecName,V_TOP,Str);
			//幅(1/100 mm単位)
			Str.sprintf(L"%Lf",pDoc.Width);
			pIni->WriteString(SecName,V_WIDTH,Str);
			//高さ(1/100 mm単位)
			Str.sprintf(L"%Lf",pDoc.Height);
			pIni->WriteString(SecName,V_HEIGHT,Str);
			//フォント名
			SetColInfToIni(pIni.get(),SecName,V_FONT_INFO,pDoc.Font);
			//キャプション(内容)
			pIni->WriteString(SecName,V_CAPTION,pDoc.Caption);
			//表示するか
			pIni->WriteBool(SecName,V_VISIBLE,(pDoc.Visible == true));
			//印刷するか
			pIni->WriteBool(SecName,V_PRINT  ,(pDoc.IsPrint == true));
			//Zオーダー
			pIni->WriteInteger(SecName,V_ZORDER,pDoc.ZOrder);
			//桁数(数値入力のみ有効)
			pIni->WriteInteger(SecName,V_FIGURES,pDoc.Figures);
			//桁区切り線の有無(数値入力のみ有効)
			pIni->WriteBool(SecName,V_FIGURE_LINE,(pDoc.FigureLine == true));
			//行数(グリッドのみ有効)
			pIni->WriteInteger(SecName,V_ROWNUM,pDoc.RowNum);
			//列数(グリッドのみ有効)
			pIni->WriteInteger(SecName,V_COLNUM,pDoc.ColNum);
		}
		catch(...)
		{
		}
	}
	return true;
}
//---------------------------------------------------------------------------
//現在のファイルのバックアップを取る
//---------------------------------------------------------------------------
bool TSdo::makeBackup(typDocument& DocInfo)
{
	//現在のファイルのバックアップを取る
	if(ES.BackupFile == true)
	{
		//現在のファイルは存在するか？
		if(_waccess(Document.File.c_str(),00) == 0)
		{
			//現在のファイルパスに .bak を追加
			String BackupFile = Document.File + L".bak";
			//コピーする
			CopyFileW(Document.File.c_str(),BackupFile.c_str(),FALSE);
		}
	}
	return true;
}
//---------------------------------------------------------------------------
//作成されるファイルのリスト(圧縮対象)原本作成とINIファイル用のTMemIniFile作成
//---------------------------------------------------------------------------
bool TSdo::makeCompression(std::unique_ptr<TStringList>& pFiles,std::unique_ptr<TMemIniFile>& pIni,String& TmpDirStr)
{
	//作成されるファイルのリスト(圧縮対象)
	pFiles.reset(new TStringList);
	//一時ファイルのディレクトリを得る
	TmpDirStr = TPath::GetTempPath();
	//一時作成Iniファイルのパス
	String TmpIniPath = TmpDirStr + INI_TEMP_SDO_INI;
	//一時作成Iniファイルが既にあれば消す
	_wunlink(TmpIniPath.c_str());
	//Iniファイルを開く
	pIni.reset(new TMemIniFile(TmpIniPath));
	pFiles->Add(TmpIniPath);

	return true;
}
//---------------------------------------------------------------------------
//sdoファイルを作成する
//---------------------------------------------------------------------------
bool TSdo::makeSDO(const String& TmpDirStr,	std::unique_ptr<TStringList>& pFiles,const String& FilePath)
{
	String FileListPath;
	//ファイル一覧のファイル作成
	FileListPath.sprintf(INI_TEMP_FILE_LIST,TmpDirStr.c_str());
	_wunlink(FileListPath.c_str());
	pFiles->SaveToFile(FileListPath);

	//カレントディレクトリを一時ファイルのディレクトリにする
	SetCurrentDir(TmpDirStr);
	//コマンドラインの作成
	String Cmd = String(L"/F ") + FileListPath;
	//makecab起動
	nsShellApi::ShellAndWait(L"makecab",Cmd.c_str(),SW_HIDE);
	//作成された .cab ファイルを .sdo にコピー
	String CabFile = TmpDirStr + L"disk1\\1.cab";
	CopyFileW(CabFile.c_str(),FilePath.c_str(),FALSE);
	//作成された .cab ファイルを削除
	_wunlink(CabFile.c_str());

	return true;
}
//---------------------------------------------------------------------------
//.sdoファイルの保存
//---------------------------------------------------------------------------
bool TSdo::writeSDO(typDocument& DocInfo,const String& FilePath)
{
	String SecName;
	String Str;
	String ImgFilePath;
	String Cmd;
	String TmpDirStr;
	//現在のファイルのバックアップを取る
	makeBackup(DocInfo);

	//作成されるファイルのリスト(圧縮対象)
	std::unique_ptr<TStringList> pFiles;
	std::unique_ptr<TMemIniFile> pIni;

	makeCompression(pFiles,pIni,TmpDirStr);

	//ファイルパスセット
	DocInfo.File = FilePath;
	//基礎情報の保存
	writeBasicInfo(DocInfo,pIni);

	//---- 履歴用のデータ ----
	//対象データ構造体
	typDocData& HistDocData = DocInfo.Data[DocInfo.DocKind];
	//年
	nsLong Year  = HistDocData.Year;
	//月
	nsLong Month = HistDocData.Month;
	//日
	nsLong Day   = HistDocData.Day;
	//名前
	String name  = HistDocData.Name;
	//件名
	String item  = HistDocData.Item;
	//ファイル名
	String file  = FilePath;

	//部品用のデータ
	String paper_mn = PaperDef[DocInfo.Paper].PaperName;
	String kind_mn  = DocKindDef[DocInfo.DocKind].KindName;

	//データの書き出し
	for(int KindCnt = 0;KindCnt < DOCUMENT_KIND_NUM;KindCnt++)
	{
		//対象書類
		const typDocKindDef& DocKind = DocKindDef[KindCnt];
		//セクション名
		String SecName = String(DocKind.KindName) + L"-DOCDATA";
		//対象データ構造体
		typDocData& DocData = DocInfo.Data[KindCnt];

		//書類データの保存
		writeDocInfo(SecName,DocData,pIni);

		//ラベル内容保存
		writeLableInfo(SecName,DocData,pIni);

		//イメージ(印影、ロゴ)の保存
		writeImageInfo(SecName,TmpDirStr,KindCnt,DocData,pFiles,pIni);

		//消費税率
		pIni->WriteString(SecName,COMPANY_INFO_TAXRATIO,DocData.ConsumptionTaxRatio);

		//グリッド情報を保存
		writeGridInfo(SecName,DocData,pIni);
	}
	//部品情報の保存
	writeCompoInfo(SecName,DocInfo,pIni);

	//保存
	pIni->UpdateFile();
	//変更はなし
	DocInfo.Edited = false;
	//sdoファイル作成
	makeSDO(TmpDirStr,pFiles,FilePath);

	//---- 履歴をレジストリに記載 ----
	//履歴情報セット
	NowHistory.setAll(NowHistory.getID(),Year,Month,Day,name,item,file);

	//リストを更新
	Histories.update(NowHistory);
	//レジストリに書き込み
	Histories.save(NowHistory);

	return true;
}

