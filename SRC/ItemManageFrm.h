//---------------------------------------------------------------------------

#ifndef ItemManageFrmH
#define ItemManageFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TItemManageForm : public TForm
{
__published:	// IDE 管理のコンポーネント
	TPanel *TopPanel;
	TPanel *BottomPanel;
	TPanel *ClientPanel;
	TPanel *FolderPanel;
	TSplitter *Splitter1;
	TPanel *ItemPanel;
	TListView *HistListView;
	TPopupMenu *HistPopupMenu;
	TMenuItem *DeleteHistMenu;
	void __fastcall HistListViewColumnClick(TObject *Sender,
          TListColumn *Column);
	void __fastcall HistListViewCompare(TObject *Sender, TListItem *Item1,
          TListItem *Item2, int Data, int &Compare);
	void __fastcall HistListViewDeletion(TObject *Sender, TListItem *Item);
	void __fastcall DeleteHistMenuClick(TObject *Sender);
	void __fastcall HistListViewMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall HistListViewClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:
	//ソート対象の列
	int    ColumnToSort;
	//ソートの順位(昇順、降順)
	int    SortVect[3];
private:
	//年、月、日からレジストリキー用日付文字列を作成
	String MakeRegDateString(int Year,int Month,int Day);
public:
	__fastcall TItemManageForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TItemManageForm *ItemManageForm;
//---------------------------------------------------------------------------
#endif
