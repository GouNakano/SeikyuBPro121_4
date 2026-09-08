//---------------------------------------------------------------------------
#ifndef nsResizeCtrlListH
#define nsResizeCtrlListH
//---------------------------------------------------------------------------
#include <vector>
#include "XnsGrid.h"
#include "nsResizeCtrl.h"

class nsResizeCtrlList
{
private:
	//編集対象のコントロールリスト
	std::vector<std::unique_ptr<nsResizeCtrl>> ResizeList;
	//移動ベクトル
private:
	//インデックスからリサイズコントロールを得る
	nsResizeCtrl* get(int idx);
	//グリッド行高さの調整
	bool AdjustRowHeights(XnsGrid *Grid);
public:
	//コンストラクタ
	nsResizeCtrlList() = default;
	//デストラクタ
	virtual ~nsResizeCtrlList() = default;
public:
	//インデックスからリサイズコントロールを得る[]演算子
	nsResizeCtrl* operator[](int idx);
public:
	//リサイズコントロールの数
	int size();
	//リサイズコントロールの全消去
	bool clear(TWinControl *Parent);
	//追加
	nsResizeCtrl* add(TWinControl *Parent,TControl *Control,TNotifyEvent ResizeHide,TResizeCtrlMoveEvent ResizeCtrlMove,TMouseEvent ResizeCtrlMouseDown,TMouseEvent ResizeCtrlMouseUp);
	//指定されたTControlポインターからnsResizeCtrlを検索してインデックスを返す
	int findResizeCtrl(TControl *ctrl);
	//インデックス指定のリサイズコントロールを削除
	bool erase(int idx);
	//コントロール移動・大きさ変更
	void ResizeCtrlMove(int dx,int dy,int dw,int dh,bool CtrlMove = true);
	//キーボードキーによるコントロール移動・大きさ変更
	bool ResizeKeyMove(WORD Key,const TShiftState& Shift,bool CtrlMove = true);
};

#endif
