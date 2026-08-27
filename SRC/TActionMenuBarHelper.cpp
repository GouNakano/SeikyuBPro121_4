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
