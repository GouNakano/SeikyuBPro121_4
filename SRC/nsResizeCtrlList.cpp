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
//Parent               リサイズコントロールを配置する親コンポーネント
//Control              リサイズコントロールで制御するコントロール
//ResizeHide           リサイズコントロールが消えるとき(確定時)のイベント
//ResizeCtrlMove       リサイズコントロール移動・大きさ変更のイベント
//ResizeCtrlMouseDown  リサイズコントロール移動・大きさ変更コントロールのマウスダウンイベント
//ResizeCtrlMouseUp    リサイズコントロール移動・大きさ変更コントロールのマウスアップイベント
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
//-------------------------------------------------------------
//コントロール移動・大きさ変更
//-------------------------------------------------------------
void nsResizeCtrlList::ResizeCtrlMove(int dx,int dy,int dw,int dh,bool CtrlMove)
{
	//リストに登録されているコントロールの移動
	for(int Cnt = 0;Cnt < ResizeList.size();Cnt++)
	{
		//移動・サイズ変更実行
		ResizeList[Cnt]->DMove(dx,dy,dw,dh,CtrlMove);
		//グリッド場合
		XnsGrid *pGrid = dynamic_cast<XnsGrid *>(ResizeList[Cnt]->Control);
		if(pGrid != nullptr)
		{
			//グリッド行高さの調整
			AdjustRowHeights(pGrid);
		}
	}
}
//-------------------------------------------------------------
//キーボードキーによるコントロール移動・大きさ変更
//-------------------------------------------------------------
bool nsResizeCtrlList::ResizeKeyMove(WORD Key,const TShiftState& Shift,bool CtrlMove)
{
	//移動ベクトル(dx,dy,dw,dh)
	std::tuple<int,int,int,int> mv;
	//Shift状態
	bool IsShift = ((GetKeyState(VK_SHIFT) & 0x80) != 0);

	//キーによる操作
	if(IsShift == true)
	{
		//Shiftキー押下時
		switch(Key)
		{
			case VK_RIGHT:
			{
				mv = {0,0,1,0};
				break;
			}
			case VK_LEFT:
			{
				mv = {0,0,-1,0};
				break;
			}
			case VK_DOWN:
			{
				mv = {0,0,0,1};
				break;
			}
			case VK_UP:
			{
				mv = {0,0,0,-1};
				break;
			}
			default:
			{
				return false;
			}
		}
	}
	else
	{
		switch(Key)
		{
			case VK_RIGHT:
			{
				mv = {1,0,0,0};
				break;
			}
			case VK_LEFT:
			{
				mv = {-1,0,0,0};
				break;
			}
			case VK_DOWN:
			{
				mv = {0,1,0,0};
				break;
			}
			case VK_UP:
			{
				mv = {0,-1,0,0};
				break;
			}
			default:
			{
				return false;
			}
		}
	}
	//移動ベクトル(dx,dy,dw,dh)取得
	auto [dx,dy,dw,dh] = mv;
	//コントロール移動・大きさ変更
	ResizeCtrlMove(dx,dy,dw,dh);

    return true;
}
//-------------------------------------------------------------
//グリッド行高さの調整
//-------------------------------------------------------------
bool nsResizeCtrlList::AdjustRowHeights(XnsGrid *Grid)
{
	//デフォルト行高さ
	Grid->DefaultRowHeight = (Grid->Height / Grid->RowCount);
	//調整値を得る
	int DiffY = Grid->Height - Grid->RowCount * Grid->DefaultRowHeight;
	//調整
	if(DiffY > 0)
	{
		for(int Cnt = 0;Cnt < DiffY;Cnt++)
		{
			Grid->RowHeights[Cnt] = Grid->RowHeights[Cnt] + 1;
		}
	}
	else if(DiffY < 0)
	{
		DiffY = -DiffY;

		for(int Cnt = 0;Cnt < DiffY;Cnt++)
		{
			Grid->RowHeights[Cnt] = Grid->RowHeights[Cnt] - 1;
		}
	}
	return true;
}

