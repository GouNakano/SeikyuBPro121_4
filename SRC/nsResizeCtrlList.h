//---------------------------------------------------------------------------
#ifndef nsResizeCtrlListH
#define nsResizeCtrlListH
//---------------------------------------------------------------------------
#include <vector>
#include "nsResizeCtrl.h"

class nsResizeCtrlList
{
private:
	//編集対象のコントロールリスト
	std::vector<std::unique_ptr<nsResizeCtrl>> ResizeList;
private:
	//インデックスからリサイズコントロールを得る
	nsResizeCtrl* get(int idx);
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
	//Parent               リサイズコントロールを配置する親コンポーネント
	//Control              リサイズコントロールで制御するコントロール
	//ResizeHide           リサイズコントロールが消えるとき(確定時)のイベント
	//ResizeCtrlMove       リサイズコントロール移動・大きさ変更のイベント
	//ResizeCtrlMouseDown  リサイズコントロール移動・大きさ変更コントロールのマウスダウンイベント
	//ResizeCtrlMouseUp    リサイズコントロール移動・大きさ変更コントロールのマウスアップイベント
	nsResizeCtrl* add(TWinControl *Parent,TControl *Control,TNotifyEvent ResizeHide,TResizeCtrlMoveEvent ResizeCtrlMove,TMouseEvent ResizeCtrlMouseDown,TMouseEvent ResizeCtrlMouseUp);
	//指定されたTControlポインターからnsResizeCtrlを検索してインデックスを返す
	int findResizeCtrl(TControl *ctrl);
	//インデックス指定のリサイズコントロールを削除
	bool erase(int idx);
};

#endif
