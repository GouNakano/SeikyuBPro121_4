//---------------------------------------------------------------------------
#ifndef MainFrmH
#define MainFrmH
//---------------------------------------------------------------------------
#include <System.ImageList.hpp>
#include <System.Classes.hpp>
#include <Vcl.AppEvnts.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ToolWin.hpp>
#include "XnsGrid.h"
#include "nsMsgBox.h"
#include "nsResizeCtrlList.h"
#include "SeikyuBDef.h"
#include "PaintPanel.h"
#include "EditAlignment.h"
#include "ImageControl.h"
#include "TWinLabel.h"
#include "WinShape.h"
#include "ComboBox2.h"
#include "TBaseEdit.h"
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.TitleBarCtrls.hpp>
#include "ActionMainMenuBar2.h"
#include <System.Actions.hpp>
#include <Vcl.ActnColorMaps.hpp>
#include <Vcl.ActnCtrls.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.ActnMenus.hpp>
#include <Vcl.StdStyleActnCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include "TListView2.h"
#include "TSdo.h"
#include "TCompanyInfos.h"
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE 管理のコンポーネント
	TOpenPictureDialog *OpenPictureDialog;
	TImageList *FileMenuImageList;
	TTimer *FirstTimer;
	TPopupMenu *ModifyLabelPopupMenu;
	TMenuItem *ModifyValueMenu;
	TMenuItem *N5;
	TFontDialog *FontDialog;
	TMenuItem *ModifyFontMenu;
	TPopupMenu *ModifyEditPopupMenu;
	TMenuItem *N6;
	TMenuItem *N7;
	TSaveDialog *SaveDialog;
	TOpenDialog *OpenDialog;
	TApplicationEvents *ApplicationEvents;
	TMenuItem *N14;
	TMenuItem *LabelAnotherSamePositionMenu;
	TMenuItem *GridSettingMenu;
	TMenuItem *SetStampImage;
	TMenuItem *CancelStampImage;
	TMenuItem *ColSeparateLineMenu;
	TMenuItem *FigureMenu;
	TMenuItem *N9;
	TMenuItem *N10;
	TMenuItem *N11;
	TMenuItem *BorderMenu;
	TMenuItem *N12;
	TMenuItem *LeftJustifyMenu;
	TMenuItem *CenterMenu;
	TMenuItem *RightJustifyMenu;
	TImageList *PopupImageList;
	TMenuItem *CalendarMenu;
	TMenuItem *N16;
	TImageList *EditMenuImageList;
	TStatusBar *StatusBar;
	TMenuItem *N15;
	TMenuItem *BringToFrontMenu;
	TMenuItem *SendToBackMenu;
	TTimer *LicTimer;
	TMenuItem *N18;
	TMenuItem *PrintObjectMenu;
	TMenuItem *PrintEditMenu;
	TMenuItem *N23;
	TPaintPanel *BasePanel;
	TToolBar *EditToolBar;
	TPanel *Panel7;
	TSpeedButton *LeftJustifyBtn;
	TSpeedButton *CenterBtn;
	TSpeedButton *RightJustifyBtn;
	TPanel *Panel11;
	TSpeedButton *BorderBtn;
	TPanel *Panel13;
	TSpeedButton *ColSeparateBtn;
	TPanel *Panel14;
	TSpeedButton *FontBtn;
	TScrollBox *ScrollBox;
	TPanel *DummyPanel;
	TPaintPanel *MainPanel;
	TPaintPanel *RubberBand1;
	TPaintPanel *RubberBand2;
	TPaintPanel *RubberBand3;
	TPaintPanel *RubberBand4;
	TMenuItem *N24;
	TMenuItem *EditUndoMenu;
	TMenuItem *EditCutMenu;
	TMenuItem *EditCopyMenu;
	TMenuItem *EditPasteMenu;
	TMenuItem *EditDeleteMenu;
	TMenuItem *EditSelectAllMenu;
	TMenuItem *N25;
	TMenuItem *ZipToAddressMenu;
	TMenuItem *N27;
	TMenuItem *NonDispObjectMenu;
	TSaveDialog *PDFSaveDialog;
	XnsGrid *Grid;
	TPanel *Panel6;
	TListView2 *HistListView;
	TPanel *Panel9;
	TImage *SakuraImage;
	TSplitter *Splitter1;
	TPopupMenu *HistPopupMenu;
	TMenuItem *DeleteHistMenu;
	TActionManager *ActionManager;
	TAction *HelpMenu;
	TAction *AskMenu;
	TAction *SakuraDensanMenu;
	TAction *SupportPageMenu;
	TAction *VersionInfMenu;
	TAction *OverWriteMenu;
	TAction *PDFSaveMenu;
	TAction *EndMenu;
	TTitleBarPanel *TitleBarPanel;
	TPanel *ClockPanel;
	TPanel *ClockBorder1;
	TPanel *ClockBorder2;
	TPanel *TitleBarBasePanel;
	TActionMainMenuBar2 *ActionMainMenuBar;
	TAction *NewMenu;
	TAction *OpenMenu;
	TAction *A3P_Menu;
	TAction *A3L_Menu;
	TAction *PrintPreviewMenu;
	TAction *PrintMenu;
	TAction *Z200_Menu;
	TAction *FileFolderMenu;
	TAction *DispComponentsMenu;
	TAction *ResizeModeMenu;
	TAction *A4P_Menu;
	TAction *A4L_Menu;
	TAction *A5P_Menu;
	TAction *A5L_Menu;
	TAction *A6P_Menu;
	TAction *A6L_Menu;
	TAction *B4P_Menu;
	TAction *B4L_Menu;
	TAction *B5P_Menu;
	TAction *B5L_Menu;
	TAction *SaveMenu;
	TAction *DispSettingMenu;
	TAction *AliginRightMenu;
	TAction *AliginLeftMenu;
	TAction *AliginTopMenu;
	TAction *AliginBottomMenu;
	TAction *MinWidthMenu;
	TAction *MaxWidthMenu;
	TAction *MinHeightMenu;
	TAction *MaxHeightMenu;
	TAction *ApplyCompanyInfo1Menu;
	TAction *ApplyCompanyInfo2Menu;
	TAction *ApplyCompanyInfo3Menu;
	TAction *Z100_Menu;
	TAction *Z90_Menu;
	TAction *Z80_Menu;
	TAction *Z70_Menu;
	TAction *Z60_Menu;
	TAction *Z50_Menu;
	TAction *Z40_Menu;
	TAction *Z30_Menu;
	TAction *Z20_Menu;
	TAction *Z10_Menu;
	TAction *CompanyInfoSettingMenu;
	TAction *SaveReportHist_Free_Menu;
	TAction *OptionMenu;
	TImageList *MenuImageList;
	TToolBar *MainToolBar;
	TSpeedButton *BillBtn;
	TPanel *Panel8;
	TSpeedButton *DeliveredBtn;
	TPanel *Panel10;
	TSpeedButton *EstimateBtn;
	TPanel *Panel1;
	TSpeedButton *NewBtn;
	TSpeedButton *OpenFileSettingSpBtn;
	TSpeedButton *SaveBtn;
	TSpeedButton *PDFBtn;
	TSpeedButton *PrintBtn;
	TPanel *Panel2;
	TSpeedButton *CalendarBtn;
	TPanel *Panel5;
	TSpeedButton *ResizeEnableBtn;
	TPanel *Panel4;
	TSpeedButton *EndBtn;
	TSpeedButton *LicenseSettingBtn;
	TStandardColorMap *StandardColorMap;
	TTimer *ClockTimer;
	TTimer *FormActiveTimer;
	TAction *PaperSelectParentMenu;
	TAction *ZoomRootMenu;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall PrintBtnClick(TObject *Sender);
	void __fastcall GridCellAttr(TObject *Sender, int ARow, int ACol,
          TColor &BackColor, int &FontNumber, StrPosX &PosX, StrPosY &PosY,
          VARIANT_BOOL &CellMerge, int &cmLeft, int &cmRight, int &cmTop,
          int &cmBottom, VARIANT_BOOL &ImgView, int &ImgID);
	void __fastcall ModifyLabelClick(TObject *Sender);
	void __fastcall EditEnter(TObject *Sender);
	void __fastcall EditExit(TObject *Sender);
	void __fastcall MoneyEditKeyPress(TObject *Sender, char &Key);
	void __fastcall CompanyInfoBtnClick(TObject *Sender);
	void __fastcall StampImageClick(TObject *Sender);
	void __fastcall EditKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall EditKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall SaveBtnClick(TObject *Sender);
	void __fastcall NewBtnClick(TObject *Sender);
	void __fastcall BillBtnClick(TObject *Sender);
	void __fastcall DeliveredBtnClick(TObject *Sender);
	void __fastcall EndBtnClick(TObject *Sender);
	void __fastcall GridKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall GridEnter(TObject *Sender);
	void __fastcall GridExit(TObject *Sender);
	void __fastcall GridStartEdit(TObject *Sender, int ARow, int ACol,
          String &EditStr, TImeMode &imode);
	void __fastcall GridAfterEdit(TObject *Sender, int ARow, int ACol,
		  String &DispStr);
	void __fastcall GridDispCellStr(TObject *Sender, int ARow, int ACol,
          String &DispStr);
	void __fastcall YearEditDblClick(TObject *Sender);
	void __fastcall VersionInfMenuClick(TObject *Sender);
	void __fastcall SupportPageMenuClick(TObject *Sender);
	void __fastcall HelpMenuClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall CancelStampImageClick(TObject *Sender);
	void __fastcall FirstTimerTimer(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall EstimateBtnClick(TObject *Sender);
	void __fastcall VisialMenuClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall MainPanelClick(TObject *Sender);
	void __fastcall ScrollBoxClick(TObject *Sender);
	void __fastcall ScrollBoxMouseWheelDown(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled);
	void __fastcall ScrollBoxMouseWheelUp(TObject *Sender, TShiftState Shift,
          TPoint &MousePos, bool &Handled);
	void __fastcall MainPanelMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall ScrollBoxResize(TObject *Sender);
	void __fastcall DispComponentsMenuClick(TObject *Sender);
	void __fastcall GridSettingMenuClick(TObject *Sender);
	void __fastcall ModifyFontMenuClick(TObject *Sender);
	void __fastcall EditCopyMenuClick(TObject *Sender);
	void __fastcall EditUndoMenuClick(TObject *Sender);
	void __fastcall EditCutMenuClick(TObject *Sender);
	void __fastcall EditPasteMenuClick(TObject *Sender);
	void __fastcall EditDeleteMenuClick(TObject *Sender);
	void __fastcall EditSelectAllMenuClick(TObject *Sender);
	void __fastcall ModifyEditPopupMenuPopup(TObject *Sender);
	void __fastcall GridColWidthsChanged(TObject *Sender);
	void __fastcall OpenMenuClick(TObject *Sender);
	void __fastcall OverWriteMenuClick(TObject *Sender);
	void __fastcall ApplicationEventsMessage(tagMSG &Msg, bool &Handled);
	void __fastcall ZoomSetMenuClick(TObject *Sender);
	void __fastcall ZoomMenuClick(TObject *Sender);
	void __fastcall PaperSelectMenuClick(TObject *Sender);
	void __fastcall PaperSelectParentMenuClick(TObject *Sender);
	void __fastcall LabelAnotherSamePositionMenuClick(TObject *Sender);
	void __fastcall MainPanelDragOver(TObject *Sender, TObject *Source, int X,
          int Y, TDragState State, bool &Accept);
	void __fastcall MainPanelEndDrag(TObject *Sender, TObject *Target, int X,
          int Y);
	void __fastcall ObjectMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall ResizeEnableBtnClick(TObject *Sender);
	void __fastcall ResizeModeMenuClick(TObject *Sender);
	void __fastcall EditMenuClick(TObject *Sender);
	void __fastcall AliginRightMenuClick(TObject *Sender);
	void __fastcall AliginLeftMenuClick(TObject *Sender);
	void __fastcall AliginTopMenuClick(TObject *Sender);
	void __fastcall AliginBottomMenuClick(TObject *Sender);
	void __fastcall MinWidthMenuClick(TObject *Sender);
	void __fastcall MaxWidthMenuClick(TObject *Sender);
	void __fastcall MinHeightMenuClick(TObject *Sender);
	void __fastcall MaxHeightMenuClick(TObject *Sender);
	void __fastcall ModifyLabelPopupMenuPopup(TObject *Sender);
	void __fastcall RubberBandPaint(TObject *Sender);
	void __fastcall ApplyCompanyInfoMenuClick(TObject *Sender);
	void __fastcall ColSeparateLineMenuClick(TObject *Sender);
	void __fastcall FigureMenuClick(TObject *Sender);
	void __fastcall BorderMenuClick(TObject *Sender);
	void __fastcall LeftJustifyMenuClick(TObject *Sender);
	void __fastcall CenterMenuClick(TObject *Sender);
	void __fastcall RightJustifyMenuClick(TObject *Sender);
	void __fastcall GridUserDrawCell(TObject *Sender, bool &DefaultDraw,
          int ACol, int ARow, const TRect &ARect, TGridDrawState AState);
	void __fastcall BringToFrontMenuClick(TObject *Sender);
	void __fastcall SendToBackMenuClick(TObject *Sender);
	void __fastcall LicenseSettingBtnClick(TObject *Sender);
	void __fastcall LicTimerTimer(TObject *Sender);
	void __fastcall OptionMenuClick(TObject *Sender);
	void __fastcall EditChange(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall ObjectDblClick(TObject *Sender);
	void __fastcall PrintObjectMenuClick(TObject *Sender);
	void __fastcall PrintEditMenuClick(TObject *Sender);
	void __fastcall AskMenuClick(TObject *Sender);
	void __fastcall FileFolderMenuClick(TObject *Sender);
	void __fastcall SaveReportHist_Free_MenuClick(TObject *Sender);
	void __fastcall BasePanelFileDrop(TObject *Sender, TStrings *Files);
	void __fastcall SakuraDensanMenuClick(TObject *Sender);
	void __fastcall EditDblClick(TObject *Sender);
	void __fastcall ZipToAddressMenuClick(TObject *Sender);
	void __fastcall DispSettingMenuClick(TObject *Sender);
	void __fastcall NonDispObjectMenuClick(TObject *Sender);
	void __fastcall EditMenuExecute(TBasicAction *Action, bool &Handled);
	void __fastcall HistListViewDeletion(TObject *Sender, TListItem *Item);
	void __fastcall HistListViewColumnClick(TObject *Sender, TListColumn *Column);
	void __fastcall HistListViewCompare(TObject *Sender, TListItem *Item1, TListItem *Item2,
          int Data, int &Compare);
	void __fastcall HistListViewCustomDrawItem(TCustomListView *Sender, TListItem *Item,
          TCustomDrawState State, bool &DefaultDraw);
	void __fastcall HistListViewMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall DeleteHistMenuClick(TObject *Sender);
	void __fastcall ClockTimerTimer(TObject *Sender);
	void __fastcall FormActiveTimerTimer(TObject *Sender);
	void __fastcall FormDeactivate(TObject *Sender);


private:
	struct LicExcept : public Exception
	{
		LicExcept(int e,String s)
		:Exception(s)
		{
			err = e;
		}

		int     err;
	};
private:
	//ソート対象の列
	int             ColumnToSort;
	//ソートの順位(昇順、降順)
	int             SortVect[3];
	//編集対象のコントロール
	nsResizeCtrlList ResizeList;
	//用紙幅ピクセル数
	int             PaperWidthPixel;
	//用紙高さピクセル数
	int             PaperHeightPixel;
	//用紙幅
	long double     PaperWidth;
	//用紙高さ
	long double     PaperHeight;
	//範囲選択開始X
    int             OriginX;
	//範囲選択開始Y
	int             OriginY;
	//範囲指定中か
	bool            IsDragging;
	//グリッドの選択セルの位置
	int             SelACol;
	int             SelARow;
	//.sdoファイルのためのオブジェクト
	TSdo            Sdo;
	//自社情報
	TCompanyInfos CompanyInfo;
private:
	//フォームがアクティブか記録
	bool isFormActive;
	//フォームがアクティブになった時の色設定
	void setFormActiveColor();
	//フォームが非アクティブになった時の色設定
	void setFormDeactiveColor();
private:
	//フォームがアクティブになった時
	void __fastcall MainFormActivate(TObject *Sender);
	//フォームが非アクティブになった時
	void __fastcall MainFormDeactivate(TObject *Sender);
public:
	__fastcall TMainForm(TComponent* Owner);
private:
	//リサイズコントロールHide時イベント
	void __fastcall ResizeHide(TObject *Sender);
	//コントロール移動・大きさ変更のイベント
	void __fastcall ResizeCtrlMove(TObject *Sender,bool& IsUserMove,int dx,int dy,int dw,int dh,bool CtrlMove=true);
	//コントロール移動・大きさ変更コントロールのマウスダウンイベント
	void __fastcall ResizeCtrlMouseDown(TObject *Sender, TMouseButton Button, Classes::TShiftState Shift,int X,int Y);
	//コントロール移動・大きさ変更コントロールのマウスアップイベント
	void __fastcall ResizeCtrlMouseUp(TObject *Sender, TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	//ﾛｽﾄﾌｫｰｶｽ時金額の位取り修正
	void __fastcall DecimalPointModificationMoneyExit(TObject *Sender);
	//金額関連入力の抑制
	void __fastcall InputRelatedMoneyKeyPress(TObject *Sender,wchar_t &Key);
	//金額関連の表示文字列
	void __fastcall MoneyDispStr(TObject *Sender,String& DispStr);
private:
	//移動・大きさ変更が可能かチェックする
	bool CheckResizeMode();
	//移動・大きさ変更が可能かセット
	void SetResizeMode(bool IsEnable);
	//移動・大きさ変更のコントロール追加
	nsResizeCtrl *AddResizeControl(TControl *pCtrl);
	//移動・大きさ変更のコントロール削除
	bool DeleteResizeControl(nsResizeCtrl *pResizeCtrl,bool IsLock);
	//移動・大きさ変更を取りやめる
	bool CancelResizeMode(bool IsLock);
	//印刷フォントサイズの計算
	int  CalcPrintFontSize(int OrgFontSize);
	//パネルフォントサイズの計算
	int  CalcPanelFontSize(int OrgFontSize);
	//書類の履歴一覧読み込み処理
	bool LoadReportHist();
	//小計、消費税、合計金額の表示
	void DispTotalInfo();
	//書類種類ボタンの表示を設定
	void SetReportKindBtnDisp();
	//MainPanelを中央に移動する
	void SetCenterMainPanel();
	//現在の用紙の縦、横ピクセル数を得る
	bool GetPaperPixel();
	//用紙上の位置からパネル上のX座標ピクセルを計算
	int GetPanelPixelFromPaperPosX(long double PX);
	//用紙上の位置からパネル上のY座標ピクセルを計算
	int GetPanelPixelFromPaperPosY(long double PY);
	//パネル上のX座標ピクセルから用紙上の位置を計算
	long double GetPaperPosXFromPanelPixel(int dx);
	//パネル上のY座標ピクセルから用紙上の位置を計算
	long double GetPaperPosYFromPanelPixel(int dy);
	//書類情報からコンポーネントを配置
	bool SetComponentFromDocumentInfo();
	//メインパネルの表示更新
	void UpdateMainPanelDisp();
	//グリッドの列幅変更イベントをハンドリングするか設定
	void SetGridColWidthsChangedEvent(bool IsEnable);
	//MainPanel上にデータをセット
	void SetDataFromDocData();
	//MainPanel上の値をデータにセット
	void SetDocDataFromMainPanel();
	//指定書類部品を書類間で同じ位置にする
	void SetSamePosionInDocuments(String CompoName);
	//テンプレートフォームからコンポーネントをセット
	bool SetComponentFromTemplateForm(String CtrlName);
	//指定コントロールの配置を行う
	bool SetDocControl(TControl *pCtrl);
	//グリッド行高さの調整
	bool AdjustRowHeights();
	//ステータスバーの表示
	void         DispStatus();
	//コントロールを作成する
	TControl    *CreateControl(String CtrlName,dcDocComponent Type);
	//コントロールのTextまたはCaptionを得る
	String       GetControlStrValue(TControl *pCtrl);
	//BaseControl上のコントロールのTabOrderを動的に決定する
	TWinControl *SetTabOrder(TWinControl *BaseControl);
	//編集ツールバーの状態設定
	void SetEditToolBarCondition();
	//履歴IDからsdoファイルを開く
	bool OpenFile(const String& histID);
	//書類情報のZオーダを決定する
	void SetDocumentCtrlZOrder();
	//書類情報Zオーダーを設定
	void SetZOrderFromDocumentInfo();
	//部品情報のフォントの情報をTFontに反映
	void DocFontInfToTFont(typFontDef& FontDef,TFont *pFont,bool IsCalcSize);
	//TFontのフォント情報を部品情報に反映
	void TFontToDocFontInf(typFontDef& FontDef,TFont *pFont,bool IsCalcSize);
	//前回終了時の状態の復元を行う
	void RemainSetting();
	//書類の変更の有無を設定
	void SetDocumentChange(bool chg);
	//上書き保存メニュー
	bool OverWrite();
	//名前をつけて保存
	bool Save();
	//ラベル内容変更
	void ModifyLabel(TWinLabel *pLbl);
	//変更がある場合は問い合わせて保存処理を行う
	nsLib::mbsel ChangedSave();
	//新規作成処理
	void NewFile();
	//数字だけを残した文字列を作成
	String MakeNumberString(String Str);
	//消費税、合計金額の計算
	void SetTaxAndTotalInfo();
	//合計金額の計算
	void SetTotalInfo();
	//表題の合計金額のセット
	void SetMainTotalInfo();
	//繰り返し入力データの追加
	void AddInputData();
	//空の書類にする(日付は本日)
	bool setVoidDocument();
	//今開いている書類のIDで履歴一覧の行を選択する
	bool selectHistViewFromHistID(const String& histID);
	//標準Editの内容をセット
	bool setStdEdit(scStdComponent comp_typ,const String& val);
	bool setStdEdit(scStdComponent comp_typ,const nsLong& val);
	bool setStdEdit(scStdComponent comp_typ,const nsDouble& val);
	//標準Labelの内容をセット
	bool setStdLabel(scStdComponent comp_typ,const String& val);
	//標準Imageの内容をセット
	bool setStdImage(scStdComponent comp_typ,const nsBitmap& bmp);
	//MainFormパネル上EditコンポーネントからDocDataのメンバの値をセット
	bool setDocValFrom(String& val,scStdComponent comp_typ);
	bool setDocValFrom(nsLong& val,scStdComponent comp_typ);
	bool setDocValFrom(nsDouble& val,scStdComponent comp_typ);
	//MainFormパネル上ImageコンポーネントからDocDataのメンバの値をセット
	bool setDocValFromImage(nsBitmap& val,scStdComponent comp_typ);
	//ラベルのCaptionをDocにセット
	bool setDocValFromLabel(String& val,scStdComponent comp_typ);
	//自社情報の一つをラベルにセットする
	bool setLabelFromCompanyInfo(scStdComponent comp,const String& inf);
public:
	//書類部品情報からコンポーネントを配置
	bool SetComponentFromDocCompo(typDocCompo& doc);
	//書類部品情報からグリッドを配置
	bool SetGridFromDocCompo();
//	//MainPanelから指定Nameのコントロールを得る
//	TControl *FindControlFromMainPanel(String Name);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
