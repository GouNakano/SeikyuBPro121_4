//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "nsResizeCtrl.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
//   グリップハンドル
//---------------------------------------------------------------------------
__fastcall TResizeGrip::TResizeGrip(TComponent *Owner) :TCustomControl(Owner)
{
}
//---------------------------------------------------------------------------
// グリップハンドルを描画する
//---------------------------------------------------------------------------
void __fastcall TResizeGrip::Paint()
{
	Canvas->Rectangle(TRect(0,0,Width,Height));
}
//---------------------------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------------------------
__fastcall nsResizeCtrl::nsResizeCtrl(TComponent *Owner)
:TShape(Owner)
{
	TCursor fNC[8] = {
	   crSizeNWSE, crSizeNS, crSizeNESW, crSizeWE,
	   crSizeNWSE, crSizeNS, crSizeNESW, crSizeWE
	};

	typMoveVect RMove[9] =
	{
		{  1,   1,  -1,  -1},
		{  0,   1,   0,  -1},
		{  0,   1,   1,  -1},
		{  0,   0,   1,   0},
		{  0,   0,   1,   1},
		{  0,   0,   0,   1},
		{  1,   0,  -1,   1},
		{  1,   0,  -1,   0},
		{  1,   1,   0,   0}
	};

	//移動ベクトル初期化
	for(int Cnt = 0;Cnt < 9;Cnt++)
	{
		R[Cnt] = RMove[Cnt];
	}

	FControl   = NULL;
	FBackColor = clBtnFace;
	FDragging  = False;
	FEditing   = true;
	FGap       = 7;
	FGripSize  = 7;
	FSpace     = 7;

	FOnMouseDown      = 0;
	FOnMouseMove      = 0;
	FOnMouseUp        = 0;
	FOnEndEditing     = 0;
	FOnResizeCtrlMove = 0;

	Visible      = false;
	Shape        = stRectangle;
	Brush->Color = FBackColor;
	Brush->Style = bsClear;
	Canvas->Brush->Style = bsBDiagonal;
	Canvas->Pen  ->Color = clGray;
	Cursor       = crSizeAll;
	Tag          = 8;

	SetBounds(0,0,0,0);


	TShape::OnMouseDown = DoMouseDown;
	TShape::OnMouseMove = DoMouseMove;
	TShape::OnMouseUp   = DoMouseUp;

	for(int i = 0;i < 8;i++)
	{
		FResizeGrip[i] = new TResizeGrip(Owner);

		FResizeGrip[i]->Visible               = false;
		FResizeGrip[i]->Canvas->Brush->Color  = clBlack;
		FResizeGrip[i]->Canvas->Brush->Style  = bsSolid;
		FResizeGrip[i]->Canvas->Pen->Color    = clWhite;
		FResizeGrip[i]->Canvas->Pen->Mode     = pmCopy;
		FResizeGrip[i]->Canvas->Pen->Style    = psSolid;
		FResizeGrip[i]->Canvas->Pen->Width    = 1;
		FResizeGrip[i]->Cursor    = fNC[i];
		FResizeGrip[i]->Tag       = i;


		FResizeGrip[i]->SetBounds(0,0,FGripSize,FGripSize);

		FResizeGrip[i]->OnMouseDown = DoMouseDown;
		FResizeGrip[i]->OnMouseMove = DoMouseMove;
		FResizeGrip[i]->OnMouseUp   = DoMouseUp;
	}

	FEditing = false;
}
//---------------------------------------------------------------------------
// デストラクタ
//---------------------------------------------------------------------------
__fastcall nsResizeCtrl::~nsResizeCtrl()
{
	//Hide時イベント
	if(FOnHide)
	{
		FOnHide(this);
	}
	//終了時処理
	//非表示
	Visible = false;
	//グリップ削除
	for(int i = 0;i < 8;i++)
	{
		delete FResizeGrip[i];
	}
	//対象コントロール使用可
	if(FControl)
	{
		FControl->Enabled = true;
	}
}
//---------------------------------------------------------------------------
// マウスダウンした
//---------------------------------------------------------------------------
void __fastcall nsResizeCtrl::DoMouseDown(TObject *Sender,TMouseButton Button,TShiftState Shift,int X,int Y)
{

	if(FOnMouseDown != 0)
	{
		FOnMouseDown(this,Button,Shift,X,Y);
	}

	if(FEditing == true)
	{
		return;
	}
	else
	{
		FEditing = true;
	}


	try
	{
		if(Button == mbLeft)
		{
			FDragging = true;
			FOrgX     = X;
			FOrgY     = Y;

			TComponent *pCompo = static_cast<TComponent *>(Sender);

			if (pCompo->Tag == 8)
			{
				HideGrips();
			}
			Move(Sender, X, Y);
		}
	}
	__finally
	{
		FEditing = false;
	}
}

//---------------------------------------------------------------------------
// マウスを移動した
//---------------------------------------------------------------------------
void __fastcall nsResizeCtrl::DoMouseMove(TObject *Sender,TShiftState Shift,int X,int Y)
{
	if(FOnMouseMove != 0)
	{
		FOnMouseMove(Sender,Shift,X,Y);
	}

	if(FEditing == true || FDragging == false)
	{
		return;
	}
	else
	{
		FEditing = true;
	}

	try
	{
		Move(Sender, X, Y);
	}
	__finally
	{
		FEditing = false;
	}
}

//---------------------------------------------------------------------------
// マウスアップした
//---------------------------------------------------------------------------
void __fastcall nsResizeCtrl::DoMouseUp(TObject *Sender,TMouseButton Button,TShiftState Shift,int X, int Y)
{
	if(FEditing == true || FDragging == false)
	{
		 return;
	}
	else
	{
		FEditing = true;
	}

	try
	{
		Move(Sender,X,Y);

		TComponent *pCompo = static_cast<TComponent *>(Sender);

		ShowGrips();

		FDragging = false;
	}
	__finally
	{
		FEditing = false;
		//編集終了イベント
		if(FOnEndEditing != 0)
		{
			FOnEndEditing(Sender);
		}
	}
	if(FOnMouseUp != 0)
	{
		FOnMouseUp(this,Button,Shift,X,Y);
	}
}
//---------------------------------------------------------------------------
// グリップハンドルを非表示にする（非公開メソッド）
//---------------------------------------------------------------------------
void __fastcall nsResizeCtrl::HideGrips()
{
	int i;

	for(i = 0;i< 8;i++)
	{
		FResizeGrip[i]->Hide();
	}
}
//---------------------------------------------------------------------------
// グリップハンドルを非表示にする
//---------------------------------------------------------------------------
void __fastcall nsResizeCtrl::Hide()
{
	if(Visible == true)
	{

		//対象コントロール使用可
		if(FControl)
		{
			FControl->Enabled = true;
		}
		//Hide時イベント
		if(FOnHide)
		{
			FOnHide(this);
		}
		//非表示
		HideGrips();
		Visible = false;
	}
}
//---------------------------------------------------------------------------
// グリップハンドルを表示する
//---------------------------------------------------------------------------
void __fastcall nsResizeCtrl::Show()
{
	if(Visible == false)
	{
		//対象コントロールは使用不可
		FControl->Enabled = false;
		//グリップの表示
		ShowGrips();
		Visible = true;
	}
}
//---------------------------------------------------------------------------
// ターゲットコントロールおよびコントロールを移動する
//---------------------------------------------------------------------------
void __fastcall nsResizeCtrl::Move(TObject *Sender,int X, int Y)
{
	String      S;
	TComponent *pCompo     = static_cast<TComponent *>(Sender);
	TControl   *pCtrl      = static_cast<TControl   *>(Sender);
	bool        IsUserMove = false;

	int         Idx    = pCompo->Tag;

	//移動量の取得
	int dx = ((X - FOrgX) * R[Idx].iL);
	int dy = ((Y - FOrgY) * R[Idx].iT);
	int dw = ((X - FOrgX) * R[Idx].iW);
	int dh = ((Y - FOrgY) * R[Idx].iH);

	//移動イベント
	if(FOnResizeCtrlMove)
	{
		FOnResizeCtrlMove(this,IsUserMove,dx,dy,dw,dh,true);
	}
	// ターゲットコントロールおよびコントロールを差分だけ移動する
	if(IsUserMove == false)
	{
		DMove(dx,dy,dw,dh,true);
	}
	return;
}
//---------------------------------------------------------------------------
// ターゲットコントロールおよびコントロールを差分だけ移動する
//---------------------------------------------------------------------------
void nsResizeCtrl::DMove(int dx,int dy,int dw,int dh,bool CtrlMove)
{
	String      S;

	//親のコンポーネントを得る
	TControl *pParent = FControl->Parent;
	//親の大きさを得る
	int PWidth  = pParent->ClientWidth;
	int PHeight = pParent->ClientHeight;
	//移動限界をチェック
	if(dx > 0)
	{
		//X増加
		if(FControl->Left + dx > PWidth - 4)
		{
			dx = PWidth - FControl->Left - 4;
			dx = (dx < 0)?dx=0:dx;
		}
	}
	else if(dx < 0)
	{
		//X減少
		if(FControl->Left + dx < -FControl->Width + 4)
		{
			dx =  -FControl->Left - FControl->Width + 4;
			dx = (dx > 0)?dx=0:dx;
		}
	}
	if(dy > 0)
	{
		//Y増加
		if(FControl->Top + dy > PHeight - 4)
		{
			dy = PHeight - FControl->Top - 4;
			dy = (dy < 0)?dy=0:dy;
		}
	}
	else if(dy < 0)
	{
		//Y減少
		if(FControl->Top + dy < -FControl->Height + 4)
		{
			dy = -FControl->Height - FControl->Top + 40;
			dy = (dy > 0)?dy=0:dy;
		}
	}
	//移動及びサイズ変更の値更新
	FControl_Left   += dx;
	FControl_Top    += dy;
	FControl_Width  += dw;
	FControl_Height += dh;
	// 自身の位置
	SetBounds(FControl_Left-FSpace,FControl_Top-FSpace,FControl_Width+(FSpace*2),FControl_Height+(FSpace*2));
	//グリップの移動
	MoveGrips();
	//移動及びサイズ変更を行う
	if(CtrlMove == true)
	{
		FControl->SetBounds(FControl_Left,FControl_Top,FControl_Width,FControl_Height);
	}
}
//---------------------------------------------------------------------------
// グリップハンドルを移動する
//---------------------------------------------------------------------------
void __fastcall nsResizeCtrl::MoveGrips()
{
	struct
	{
		int iX;
		int iY;
	}C[8] =
	{
		{ 0,  0}, { 1,  0},
		{ 2,  0}, { 2,  1},
		{ 2,  2}, { 1,  2},
		{ 0,  2}, { 0,  1}
	};

	for (int i = 0;i< 8;i++)
	{
		int NewLeft   = Left - FGripSize + FGap + int((Width  - (FGap * 2) + FGripSize - 1) * C[i].iX / 2);
		int NewTop    = Top  - FGripSize + FGap + int((Height - (FGap * 2) + FGripSize - 1) * C[i].iY / 2);

		FResizeGrip[i]->Left = NewLeft;
		FResizeGrip[i]->Top  = NewTop;
		FResizeGrip[i]->Refresh();
	}
}
//---------------------------------------------------------------------------
// リサイズ対象のコントロールを設定する
//---------------------------------------------------------------------------
void __fastcall nsResizeCtrl::SetControl(TControl *Control)
{

	if(Control == nullptr)
	{
		if(FControl)
		{
			FControl->Enabled = true;
		}

		FControl = Control;
		Visible = False;
		HideGrips();
	}
	else
	{
		//一旦消す
		Hide();
		//座標変更
		try
		{
			FControl = Control;
			TShape::SetParent(FControl->Parent);
			//座標設定
			SetBounds(FControl->Left-FSpace,FControl->Top-FSpace,FControl->Width+(FSpace * 2),FControl->Height+(FSpace * 2));
			//座標記録
			FControl_Left   = FControl->Left;
			FControl_Top    = FControl->Top;
			FControl_Width  = FControl->Width;
			FControl_Height = FControl->Height;
		}
		__finally
		{
			//最後は必ず表示
			Show();
		}
	}
}
//---------------------------------------------------------------------------
// コントロールの背景色を設定する
//---------------------------------------------------------------------------
void __fastcall nsResizeCtrl::SetBackColor(TColor c)
{
	FBackColor   = c;
	Brush->Color = FBackColor;
}
//---------------------------------------------------------------------------
// 親コントロールを設定する
//---------------------------------------------------------------------------
void __fastcall nsResizeCtrl::SetParent(TWinControl *Control)
{
	TShape::SetParent(Control);

	if (Control != 0)
	{
		SetControl(NULL);
	}
}
//---------------------------------------------------------------------------
// 親コントロールを設定する
//---------------------------------------------------------------------------
void __fastcall nsResizeCtrl::Paint(void)
{
//	Canvas->Pen->Color = 0x00D2D2D2;
//	Canvas->Brush->Style = bsClear;
//	Canvas->Rectangle(FSpace-1,FSpace-1,Width-FSpace+1,Height-FSpace+1);
}
//---------------------------------------------------------------------------
// グリップハンドルを表示する
//---------------------------------------------------------------------------
void nsResizeCtrl::ShowGrips()
{
	MoveGrips();

	for(int i = 0 ;i< 8;i++)
	{
		FResizeGrip[i]->Parent = Parent;
		FResizeGrip[i]->Show();
	}
}
//---------------------------------------------------------------------------
// 移動のみにする(戻せない)
//---------------------------------------------------------------------------
void nsResizeCtrl::SetMoveOnly()
{
	//移動ベクトルを移動のみにする
	for(int Cnt = 0;Cnt < 9;Cnt++)
	{
		R[Cnt].iL  = 1;
		R[Cnt].iT  = 1;
		R[Cnt].iW  = 0;
		R[Cnt].iH  = 0;
	}
	//マウスカーソルを移動だけにする
	for(int Cnt = 0;Cnt < 8;Cnt++)
	{
		FResizeGrip[Cnt]->Cursor = crSizeAll;
	}
}

