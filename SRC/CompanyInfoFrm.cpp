//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "zbWindowDef.h"
#include "strconv.h"
#include "nsMsgBox.h"
#include "SeikyuBDef.h"
#include "sbControlDef.h"
#include "CompanyInfoFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TBaseEdit"
#pragma link "BitBtn2"
#pragma resource "*.dfm"
TCompanyInfoForm *CompanyInfoForm;
//---------------------------------------------------------------------------
__fastcall TCompanyInfoForm::TCompanyInfoForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
//フォーム作成時
//---------------------------------------------------------------------------
void __fastcall TCompanyInfoForm::FormCreate(TObject *Sender)
{
	//タイトルバーに標準色を設定する
	zbWindowDef::setStdTitlebarColor(this);
	//ベースエディットの設定を行う
	sbControlDef::setBaseEditPram(CompanyNameEdit_1);
	sbControlDef::setBaseEditPram(RepresentEdit_1);
	sbControlDef::setBaseEditPram(ZipNumberEdit_1);
	sbControlDef::setBaseEditPram(AddressEdit1_1);
	sbControlDef::setBaseEditPram(AddressEdit2_1);
	sbControlDef::setBaseEditPram(TELEdit_1);
	sbControlDef::setBaseEditPram(FAXEdit_1);
	sbControlDef::setBaseEditPram(TransferEdit1_1);
	sbControlDef::setBaseEditPram(TransferEdit2_1);
	sbControlDef::setBaseEditPram(TaxEdit_1);

	sbControlDef::setBaseEditPram(CompanyNameEdit_2);
	sbControlDef::setBaseEditPram(RepresentEdit_2);
	sbControlDef::setBaseEditPram(ZipNumberEdit_2);
	sbControlDef::setBaseEditPram(AddressEdit1_1);
	sbControlDef::setBaseEditPram(AddressEdit2_1);
	sbControlDef::setBaseEditPram(TELEdit_2);
	sbControlDef::setBaseEditPram(FAXEdit_2);
	sbControlDef::setBaseEditPram(TransferEdit1_1);
	sbControlDef::setBaseEditPram(TransferEdit2_1);
	sbControlDef::setBaseEditPram(TaxEdit_2);

	sbControlDef::setBaseEditPram(CompanyNameEdit_3);
	sbControlDef::setBaseEditPram(RepresentEdit_3);
	sbControlDef::setBaseEditPram(ZipNumberEdit_3);
	sbControlDef::setBaseEditPram(AddressEdit1_1);
	sbControlDef::setBaseEditPram(AddressEdit2_1);
	sbControlDef::setBaseEditPram(TELEdit_3);
	sbControlDef::setBaseEditPram(FAXEdit_3);
	sbControlDef::setBaseEditPram(TransferEdit1_1);
	sbControlDef::setBaseEditPram(TransferEdit2_1);
	sbControlDef::setBaseEditPram(TaxEdit_3);
}
//-------------------------------------------------------------
//  機能     ：フォーム表示時
//
//  関数定義 ：void __fastcall FormShow(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TCompanyInfoForm::FormShow(TObject *Sender)
{
	//自社情報を得る
	sbp::ReadCompanyInfo();
	//-- データセット --
	//自社情報１
	CompanyNameEdit_1->Text = CompanyInfo[0].CompanyName;
	RepresentEdit_1  ->Text = CompanyInfo[0].Represent;
	ZipNumberEdit_1  ->Text = CompanyInfo[0].ZipNumber;
	AddressEdit1_1   ->Text = CompanyInfo[0].Address1;
	AddressEdit2_1   ->Text = CompanyInfo[0].Address2;
	TELEdit_1        ->Text = CompanyInfo[0].TEL;
	FAXEdit_1        ->Text = CompanyInfo[0].FAX;
	TransferEdit1_1  ->Text = CompanyInfo[0].Transfer1;
	TransferEdit2_1  ->Text = CompanyInfo[0].Transfer2;
	TaxEdit_1        ->Text = CompanyInfo[0].TaxRatio;

	//自社情報２
	CompanyNameEdit_2->Text = CompanyInfo[1].CompanyName;
	RepresentEdit_2  ->Text = CompanyInfo[1].Represent;
	ZipNumberEdit_2  ->Text = CompanyInfo[1].ZipNumber;
	AddressEdit1_2   ->Text = CompanyInfo[1].Address1;
	AddressEdit2_2   ->Text = CompanyInfo[1].Address2;
	TELEdit_2        ->Text = CompanyInfo[1].TEL;
	FAXEdit_2        ->Text = CompanyInfo[1].FAX;
	TransferEdit1_2  ->Text = CompanyInfo[1].Transfer1;
	TransferEdit2_2  ->Text = CompanyInfo[1].Transfer2;
	TaxEdit_2        ->Text = CompanyInfo[1].TaxRatio;

	//自社情報３
	CompanyNameEdit_3->Text = CompanyInfo[2].CompanyName;
	RepresentEdit_3  ->Text = CompanyInfo[2].Represent;
	ZipNumberEdit_3  ->Text = CompanyInfo[2].ZipNumber;
	AddressEdit1_3   ->Text = CompanyInfo[2].Address1;
	AddressEdit2_3   ->Text = CompanyInfo[2].Address2;
	TELEdit_3        ->Text = CompanyInfo[2].TEL;
	FAXEdit_3        ->Text = CompanyInfo[2].FAX;
	TransferEdit1_3  ->Text = CompanyInfo[2].Transfer1;
	TransferEdit2_3  ->Text = CompanyInfo[2].Transfer2;
	TaxEdit_3        ->Text = CompanyInfo[2].TaxRatio;

	//アクティブページ
	CPageCtrl->ActivePage = C1;
	//フォーカス
	CompanyNameEdit_1->SetFocus();
}
//-------------------------------------------------------------
//  機能     ：登録ボタン
//
//  関数定義 ：void __fastcall ResistBtnClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TCompanyInfoForm::ResistBtnClick(TObject *Sender)
{
	//自社情報１
	CompanyInfo[0].CompanyName = CompanyNameEdit_1->Text;
	CompanyInfo[0].Represent   = RepresentEdit_1  ->Text;
	CompanyInfo[0].ZipNumber   = ZipNumberEdit_1  ->Text;
	CompanyInfo[0].Address1    = AddressEdit1_1   ->Text;
	CompanyInfo[0].Address2    = AddressEdit2_1   ->Text;
	CompanyInfo[0].TEL         = TELEdit_1        ->Text;
	CompanyInfo[0].FAX         = FAXEdit_1        ->Text;
	CompanyInfo[0].Transfer1   = TransferEdit1_1  ->Text;
	CompanyInfo[0].Transfer2   = TransferEdit2_1  ->Text;
	CompanyInfo[0].TaxRatio    = TaxEdit_1        ->Text.Trim();

	//自社情報２
	CompanyInfo[1].CompanyName = CompanyNameEdit_2->Text;
	CompanyInfo[1].Represent   = RepresentEdit_2  ->Text;
	CompanyInfo[1].ZipNumber   = ZipNumberEdit_2  ->Text;
	CompanyInfo[1].Address1    = AddressEdit1_2   ->Text;
	CompanyInfo[1].Address2    = AddressEdit2_2   ->Text;
	CompanyInfo[1].TEL         = TELEdit_2        ->Text;
	CompanyInfo[1].FAX         = FAXEdit_2        ->Text;
	CompanyInfo[1].Transfer1   = TransferEdit1_2  ->Text;
	CompanyInfo[1].Transfer2   = TransferEdit2_2  ->Text;
	CompanyInfo[1].TaxRatio    = TaxEdit_2        ->Text.Trim();

	//自社情報３
	CompanyInfo[2].CompanyName = CompanyNameEdit_3->Text;
	CompanyInfo[2].Represent   = RepresentEdit_3  ->Text;
	CompanyInfo[2].ZipNumber   = ZipNumberEdit_3  ->Text;
	CompanyInfo[2].Address1    = AddressEdit1_3   ->Text;
	CompanyInfo[2].Address2    = AddressEdit2_3   ->Text;
	CompanyInfo[2].TEL         = TELEdit_3        ->Text;
	CompanyInfo[2].FAX         = FAXEdit_3        ->Text;
	CompanyInfo[2].Transfer1   = TransferEdit1_3  ->Text;
	CompanyInfo[2].Transfer2   = TransferEdit2_3  ->Text;
	CompanyInfo[2].TaxRatio    = TaxEdit_3        ->Text.Trim();

	//自社情報の保存
	sbp::SaveCompanyInfo();
	//閉じる
	Close();
}
//-------------------------------------------------------------
//  機能     ：郵便番号から住所を検索ボタン
//
//  関数定義 ：void __fastcall ZipToAddressBtnClick(TObject *Sender,...)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：中野  04/02/24
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TCompanyInfoForm::ZipToAddressBtnClick(TObject *Sender)
{
	String Prefecture;
	String City;
	String Address;
	String AllAddrStr;
	String InputZipStr;
	String ZipStr;
	String NumStr;
	int    HyphenPos;
	//対象Editコントロール(郵便番号、住所)
	TBaseEdit *ZipEdit;
	TBaseEdit *AdrEdit;

	if(CPageCtrl->ActivePage == C1)
	{
		ZipEdit = ZipNumberEdit_1;
		AdrEdit = AddressEdit1_1;
	}
	else if(CPageCtrl->ActivePage == C2)
	{
		ZipEdit = ZipNumberEdit_2;
		AdrEdit = AddressEdit1_2;
	}
	else
	{
		ZipEdit = ZipNumberEdit_3;
		AdrEdit = AddressEdit1_3;
	}
	//入力された郵便番号を得る
	InputZipStr = ZipEdit->Text.Trim();
	//半角にする
	InputZipStr = sbp::StrToHan(wide_to_ansi(InputZipStr.c_str())).c_str();
	//数字文字だけを抽出(全角も)
	for(int Cnt = 0;Cnt < (int)InputZipStr.Length();Cnt++)
	{
		//指定位置の文字を得る
		NumStr = InputZipStr.SubString(Cnt+1,1);
		//数字なら追加
		if(NumStr.ToIntDef(-1) >= 0)
		{
			ZipStr += NumStr;
		}
	}
	//長さチェック
	if(ZipStr.Length() != 7)
	{
		nsLib::ErrMsgBox(Handle,"郵便番号の桁数が７桁ではありません。\n処理を中止します。");
		return;
	}
	//数字だけで構成されているか？
	if(ZipStr.ToIntDef(-1) == -1)
	{
		nsLib::ErrMsgBox(Handle,"郵便番号に不要な文字が入力されています。\n処理を中止します。");
		return;
	}
	//郵便番号検索
	sbp::GetAdressFromZipCode(ZipStr,Prefecture,City,Address);
	//住所を作成
	AllAddrStr = Prefecture + City + Address;
	//住所をセット
	AdrEdit->Text = AllAddrStr;
	//郵便番号の補正
	ModifyInputZipStr(ZipEdit);
}
//-------------------------------------------------------------
//  機能     ：郵便番号文字列の補正
//
//  関数定義 ：void ModifyInputZipStr(TBaseEdit *ZipNumberEdit)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：
//
//  引数     ：
//
//  戻り値   ：
//
//  作成者　 ：
//
//  改定者   ：
//-------------------------------------------------------------
void TCompanyInfoForm::ModifyInputZipStr(TBaseEdit *ZipNumberEdit)
{
	//入力された郵便番号を得る
	String InputZipStr = ZipNumberEdit->Text.Trim();
	//数字だけで構成されているか？
	int Val = InputZipStr.ToIntDef(-1);
	//数字だけでないなら補正なし
	if(Val == -1)
	{
		return;
	}
	//長さ(7以外は補正なし)
	if(wcslen(InputZipStr.c_str()) != 7)
	{
		return;
	}
	//４桁目に - を追加
	ZipNumberEdit->Text = InputZipStr.Insert(L"-",4);
}
//---------------------------------------------------------------------------
//  機能     ：アクティブタブを白、その他をclBtnFaceにする
//
//  関数定義 ：void __fastcall ColorChangeBtnClick(TObject *Sender)
//
//  ｱｸｾｽﾚﾍﾞﾙ ：__published
//
//  引数     ：
//
//  戻り値   ：
//
//  改定者   ：
//-------------------------------------------------------------
void __fastcall TCompanyInfoForm::CPageCtrlDrawTab(TCustomTabControl *Control, int TabIndex,const TRect &Rect, bool Active)
{
	TCanvas *C = Control->Canvas;
	TColor fCol = clBlack;

	// 背景色
	if(Active == true)
	{
		// アクティブタブを白
		C->Brush->Color = clWhite;
		//タブ文字列Navy
		fCol = clBlue;
	}
	else
	{
		// 非アクティブは標準
		C->Brush->Color = clBtnFace;
		//タブ文字列黒
		fCol = clBlack;
	}
	//塗りつぶし
	C->FillRect(Rect);
	//表示文字列
	String cap = CPageCtrl->Pages[TabIndex]->Caption;
	//sx,syの設定
	int sx = (Rect.Width()  - C->TextWidth(cap))  / 2;
	int sy = (Rect.Height() - C->TextHeight(cap)) / 2;

	// タブ文字列
	C->Font->Color = fCol;
	C->TextOut(Rect.Left + sx, Rect.Top + sy,cap);
}
//---------------------------------------------------------------------------

