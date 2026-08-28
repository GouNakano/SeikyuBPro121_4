//---------------------------------------------------------------------------
#include <vcl.h>
#include <CommCtrl.hpp>
#pragma hdrstop

#include "nsDebug.h"
#include "TListView2.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck は、作成したコンポーネントに純粋仮想関数が
// ないことを確認するために使用します。
//

static inline void ValidCtrCheck(TListView2 *)
{
	new TListView2(NULL);
}
//---------------------------------------------------------------------------
__fastcall TListView2::TListView2(TComponent* Owner)
	: TListView(Owner)
{
	FDisableFontColor = clGray;
	FHeaderColor      = clBtnFace;
}
//---------------------------------------------------------------------------
namespace Tlistview2
{
	void __fastcall PACKAGE Register()
	{
		TComponentClass classes[1] = {__classid(TListView2)};
		RegisterComponents(L"SSGO", classes, 0);
	}
}
//---------------------------------------------------------------------------
//ヘッダーのテーマを無効化する
//---------------------------------------------------------------------------
void __fastcall TListView2::CreateWnd()
{
	TListView::CreateWnd();

	HWND hHeader = ListView_GetHeader(Handle);

	// テーマ無効化
	SetWindowTheme(hHeader, L"", L"");
}
//---------------------------------------------------------------------------
//通知のウィンドウメッセージ
//---------------------------------------------------------------------------
void __fastcall TListView2::WMNotify(TMessage& Message)
{
	LPNMHDR lpnmh = (LPNMHDR)Message.LParam;

	// ヘッダーのハンドルを取得
	HWND hHeader = ListView_GetHeader(Handle);
	if(lpnmh->hwndFrom == hHeader && lpnmh->code == NM_CUSTOMDRAW)
	{
		LPNMCUSTOMDRAW lpnmcd = (LPNMCUSTOMDRAW)Message.LParam;

		switch (lpnmcd->dwDrawStage)
		{
			case CDDS_PREPAINT:
			{
               // ★ヘッダー全体を先に塗る（余白も含む）
                HDC hdc = lpnmcd->hdc;
                RECT rc;
				::GetClientRect(hHeader, &rc);

                HBRUSH brush = CreateSolidBrush(ColorToRGB(FHeaderColor));
                FillRect(hdc, &rc, brush);
				DeleteObject(brush);

				Message.Result = CDRF_NOTIFYITEMDRAW;
				return;
			}
			case CDDS_ITEMPREPAINT:
			{
				HDC hdc = lpnmcd->hdc;
				// 背景色を塗る
//				RECT rc = lpnmcd->rc;
//				HBRUSH brush = CreateSolidBrush(ColorToRGB(clRed));
//				FillRect(hdc, &rc, brush);
//				DeleteObject(brush);
				//ヘッダーの文字色を設定
				if(Enabled == false)
				{
					//使用不可時のフォントの色
					::SetTextColor(hdc,(DWORD)FDisableFontColor);
				}
				else
				{
					//使用可時のフォントの色
					::SetTextColor(hdc,(DWORD)clBlack);
				}
				SetBkMode(hdc, TRANSPARENT);

				Message.Result = CDRF_NEWFONT;
				return;
			}
		}
	}
}
//---------------------------------------------------------------------------
//使用不可時のフォントの色
//---------------------------------------------------------------------------
void __fastcall TListView2::SetDisableFontColor(TColor col)
{
	FDisableFontColor = col;
	Invalidate();
}
//---------------------------------------------------------------------------
//ヘッダーの背景色
//---------------------------------------------------------------------------
void __fastcall TListView2::SetHeaderColor(TColor Value)
{
	if(FHeaderColor != Value)
	{
		FHeaderColor = Value;
		HWND hHeader = ListView_GetHeader(Handle);
		InvalidateRect(hHeader, NULL, TRUE);
	}
}
//---------------------------------------------------------------------------
//左ボタンクリック時
//---------------------------------------------------------------------------
void __fastcall TListView2::WMLButtonDown(TWMLButtonDown &Message)
{
	// クリック位置にアイテムがあるか？
	if (GetItemAt(Message.XPos, Message.YPos) != nullptr)
	{
		// アイテム上なら通常処理
		TListView::Dispatch(&Message);
	}
	// 何もない所なら何もしない → 選択が消えない
}
//---------------------------------------------------------------------------
//ダブルクリック時
//---------------------------------------------------------------------------
void __fastcall TListView2::WMLButtonDblClk(TWMLButtonDblClk &Message)
{
	if (GetItemAt(Message.XPos, Message.YPos) != nullptr)
	{
		TListView::Dispatch(&Message);
	}
	// 空白なら何もしない → 選択が消えない
}
//---------------------------------------------------------------------------
