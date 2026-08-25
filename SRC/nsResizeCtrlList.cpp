//---------------------------------------------------------------------------
#include<vcl.h>
#pragma hdrstop

#include "nsResizeCtrlList.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


//-------------------------------------------------------------
//インデックスからリサイズコントロールを得る[]演算子
//-------------------------------------------------------------
nsResizeCtrl* nsResizeCtrlList::operator[](int idx)
{
	//リサイズコントロールを返す
	return get(idx);
}
//-------------------------------------------------------------
//リサイズコントロールの数
//-------------------------------------------------------------
int nsResizeCtrlList::size()
{
	return ResizeList.size();
}
//-------------------------------------------------------------
//リサイズコントロールの全消去
//-------------------------------------------------------------
bool nsResizeCtrlList::clear(TWinControl *Parent)
{
	//対象の有無チェック
	if(ResizeList.size() == 0)
	{
		return true;
	}
	//リサイズコンポーネント削除
	try
	{
		//Window描画を中止する
		LockWindowUpdate(Parent->Handle);
		//リサイズ対象コントロールを切り離す
		for(int Cnt = 0;Cnt < ResizeList.size();Cnt++)
		{
			ResizeList[Cnt].get()->Hide();
			ResizeList[Cnt].get()->Control = nullptr;
		}
		//リサイズ対象を消去
		ResizeList.clear();
	}
	__finally
	{
		//Window描画を再開する
		LockWindowUpdate(0);
	}
	return true;
}
//-------------------------------------------------------------
//リサイズコントロール追加
//-------------------------------------------------------------
nsResizeCtrl* nsResizeCtrlList::add(TWinControl *Parent,TControl *Control,TNotifyEvent ResizeHide,TResizeCtrlMoveEvent ResizeCtrlMove,TMouseEvent ResizeCtrlMouseDown,TMouseEvent ResizeCtrlMouseUp)
{
	nsResizeCtrl *pRCtrl = nullptr;

	try
	{
		//Window表示中断
		LockWindowUpdate(Parent->Handle);
		//追加する
		pRCtrl = new nsResizeCtrl(Parent);
		std::unique_ptr<nsResizeCtrl> pResizeCtrl(pRCtrl);

		pResizeCtrl->Parent           = Parent;
		pResizeCtrl->Control          = Control;
		pResizeCtrl->OnHide           = ResizeHide;           //非表示時(確定時)イベント
		pResizeCtrl->OnResizeCtrlMove = ResizeCtrlMove;       //コントロール移動・大きさ変更のイベント
		pResizeCtrl->OnMouseDown      = ResizeCtrlMouseDown;  //コントロール移動・大きさ変更コントロールのマウスダウンイベント
		pResizeCtrl->OnMouseUp        = ResizeCtrlMouseUp;    //コントロール移動・大きさ変更コントロールのマウスアップイベント

		ResizeList.push_back(std::move(pResizeCtrl));
	}
	__finally
	{
		//Window表示再開
		LockWindowUpdate(nullptr);
	}
	return pRCtrl;
}
//-------------------------------------------------------------
//指定されたTControlポインターからnsResizeCtrlを検索してインデックスを返す
//-------------------------------------------------------------
int nsResizeCtrlList::findResizeCtrl(TControl *ctrl)
{
	int idx = -1;
	for(int cnt = 0;cnt < ResizeList.size();cnt++)
	{
		if(ResizeList[cnt].get() == ctrl)
		{
			idx = cnt;
			break;
		}
	}
	return idx;
}
//-------------------------------------------------------------
//インデックスからリサイズコントロールを得る
//-------------------------------------------------------------
nsResizeCtrl* nsResizeCtrlList::get(int idx)
{
	//範囲チェック
	if(idx < 0 || idx >= ResizeList.size())
	{
		return nullptr;
	}
	//リサイズコントロールを返す
	return ResizeList[idx].get();
}
//-------------------------------------------------------------
//インデックス指定のリサイズコントロールを削除
//-------------------------------------------------------------
bool nsResizeCtrlList::erase(int idx)
{
	//範囲チェック
	if(idx < 0 || idx >= ResizeList.size())
	{
		return false;
	}
	//Parentを得る
	TWinControl *Ctrl = ResizeList[idx].get()->Parent;

	//リサイズコントロールの削除
	try
	{
		//Window表示中断
		LockWindowUpdate(Ctrl->Handle);
		//削除する
		ResizeList.erase(ResizeList.begin() + idx);
	}
	__finally
	{
		//Window表示再開
		LockWindowUpdate(0);
	}
	return true;
}
