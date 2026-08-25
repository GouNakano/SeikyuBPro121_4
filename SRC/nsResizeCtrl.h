//---------------------------------------------------------------------------
#ifndef nsResizeCtrlH
#define nsResizeCtrlH
//---------------------------------------------------------------------------
#include <array>

class nsResizeCtrl;
//グリップハンドル
class TResizeGrip : public TCustomControl
{
protected:
	virtual void __fastcall Paint();
public:
	__fastcall virtual TResizeGrip(TComponent *Owner);
public:
	__property  Canvas;
	__property  OnMouseDown;
	__property  OnMouseMove;
	__property  OnMouseUp;
};

//移動イベント
typedef void __fastcall (__closure *TResizeCtrlMoveEvent)(System::TObject* Sender,bool& IsUserMove,int dx,int dy,int dw,int dh,bool CtrlMove);

class nsResizeCtrl : public TShape
{
private:
	class typMoveVect
	{
	public:
		int iL;
		int iT;
		int iW;
		int iH;
	public:
		typMoveVect() = default;
	};
	std::array<typMoveVect,9> R;
private:
	TControl            *FControl;
	TColor               FBackColor;
	bool                 FDragging;
	bool                 FEditing;
	std::array<TResizeGrip *,8> FResizeGrip;
	int                  FGap;
	int                  FSpace;        // コントロールと FControl との端部のスペース
	int                  FGripSize;     // グリップのサイズ
	int                  FOrgX;         // マウスダウンしたときのマウスの位置
	int                  FOrgY;         // 同上
	TMouseEvent          FOnMouseDown;
	TMouseMoveEvent      FOnMouseMove;
	TMouseEvent          FOnMouseUp;
	TNotifyEvent         FOnHide;
	TNotifyEvent         FOnEndEditing;
	TResizeCtrlMoveEvent FOnResizeCtrlMove;
	int                  FControl_Left;
	int                  FControl_Top;
	int                  FControl_Width;
	int                  FControl_Height;
private:
	void __fastcall HideGrips();
	void __fastcall MoveGrips();
	void __fastcall Move(TObject *Sender,int X,int Y);
	void __fastcall SetBackColor(TColor c);
protected:
	virtual void __fastcall DoMouseDown(TObject *Sender,TMouseButton Button,TShiftState Shift,int X,int Y);
	virtual void __fastcall DoMouseMove(TObject *Sender,TShiftState Shift,int X,int Y);
	virtual void __fastcall DoMouseUp(TObject *Sender,TMouseButton Button,TShiftState Shift,int X,int Y);
	virtual void __fastcall SetControl(TControl *Control);
	virtual void __fastcall SetParent(TWinControl *Control);
	virtual void __fastcall Paint(void);
public:
	__fastcall virtual nsResizeCtrl(TComponent *Owner);
	__fastcall virtual ~nsResizeCtrl();
public:
	void __fastcall Hide();
	void __fastcall Show();
__published:
	__property TControl *Control  = {read = FControl  ,write=SetControl};
	__property TColor    Color    = {read = FBackColor,write=SetBackColor};

	__property TMouseEvent          OnMouseDown       = {read = FOnMouseDown      ,write = FOnMouseDown};
	__property TMouseMoveEvent      OnMouseMove       = {read = FOnMouseMove      ,write = FOnMouseMove};
	__property TMouseEvent          OnMouseUp         = {read = FOnMouseUp        ,write = FOnMouseUp};
	__property TNotifyEvent         OnHide            = {read = FOnHide           ,write = FOnHide};
	__property TNotifyEvent         OnEndEditing      = {read = FOnEndEditing     ,write = FOnEndEditing};
	__property TResizeCtrlMoveEvent OnResizeCtrlMove  = {read = FOnResizeCtrlMove ,write = FOnResizeCtrlMove};
public:
	//移動のみにする(戻せない)
	void SetMoveOnly();
	// ターゲットコントロールおよびコントロールを差分だけ移動する
	void DMove(int dx,int dy,int dw,int dh,bool CtrlMove);
	// グリップハンドルを表示する
	void ShowGrips();
};

#endif
