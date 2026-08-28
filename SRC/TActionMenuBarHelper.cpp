//---------------------------------------------------------------------------
#pragma hdrstop

#include "TActionMenuBarHelper.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//	//子のメニューのチェックの有無を設定
//	int bars_num = ActionManager->ActionBars->Count;
//
//	TActionBarItem *main_menu = ActionManager->ActionBars->ActionBars[bars_num-1];
//
//	int cnt = main_menu->Items->Count;
//
//	TActionClientItem *pcl = main_menu->Items->ActionClients[0];
//
//	String pcl_mn = pcl->Caption;
//
//	int pcl_num = pcl->Items->Count;
//
//	TActionClientItem *yousi = pcl->Items->ActionClients[3];
//
//	String yousi_nm = yousi->Caption;
//
//	int yousi_cnt = yousi->Items->Count;
//
//	TActionClientItem *p = yousi->Items->ActionClients[0];
//
//	String p_nm = p->Caption;
//
//	TContainedAction* action = p->Action;
//
//	String action_mn = action->Name;
//
//
//	for(int Cnt = 0;Cnt < yousi_cnt;Cnt++)
//	{
//		//子メニューを得る
//		TActionClientItem *child_menu = yousi->Items->ActionClients[Cnt];
//		//アクションを得る
//		TContainedAction *action = child_menu->Action;
//
//		//名前の一致をチェック
//		if(action->Name == MenuName)
//		{
//			//チェック表示
//			action->Checked = true;
//		}
//		else
//		{
//			//チェック表示しない
//			action->Checked = false;
//		}
//	}


//-------------------------------------------------------------
//履歴一覧ListView変化時
//-------------------------------------------------------------
//void __fastcall TMainForm::HistListViewChanging(TObject *Sender, TListItem *Item,TItemChange Change, bool &AllowChange)
//{
//TListItem *pxx;
//	// 状態（選択など）が変更されようとしているときのみ処理
//	if(Change == ctState)
//	{
//		// 現在のマウスカーソルの位置を ListView のクライアント座標に変換
//		TPoint clientPos = HistListView->ScreenToClient(Mouse->CursorPos);
//
//		// クリックされた位置（マウス座標）にアイテムが存在するかチェック
//		TListItem* hitItem = HistListView->GetItemAt(clientPos.X, clientPos.Y);
//
//		// アイテムが存在しない（空白をクリックした）かつ、選択が解除されようとしている場合
//		if(hitItem == nullptr && Item->Selected == true)
//		{
//			// 変更を拒否して現在の選択を維持する
//			AllowChange = false;
//		}
//pxx = HistListView->Selected;
//	}
//}

