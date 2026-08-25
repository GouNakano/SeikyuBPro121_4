{ TResizeControl クラス

  実行時に指定のコントロールをリサイズおよび移動可能にするクラスです。

  このクラスの元になったコードをどこで手に入れたのかが分かりません。
  作者のハンドル名は「アイクビー」さんであることは確かだと思います。
  オリジナルのコードはコントロールを非表示にできないなど、問題があり
  ましたので、改変しています。また、私の好みに合わせて変数名やコーディ
  ングスタイルなども変えています。

  もし、作者のかたがこれでは不都合だということであれば、ご連絡ください。
  ただちに削除します。

  なお、以上の状況を踏まえた上で、このクラス自体はフリーウエアです。
  私の著作権は主張しません。

【プロパティ】
  Control  : 操作対象のコントロール
  Color    : 背景色（デフォルト clBtnFace）
  ShowHint : ヒントを表示するかどうかを指定するブール型（デフォルト true）

【メソッド】
  Hide     : オブジェクトを非表示にする

【使い方】
  TResizeControl* objResize = NULL;

  objResize = new TResizeControl(this);

  // Edit1 を操作対象とする
  objResize->Control = Edit1;

  // オブジェクトが不要になった時点で開放する
  if (objResize)
    delete objResize
}
//-----------------------------------------------------------------------------
unit TResizeCtrl;

interface

uses
  SysUtils, Graphics, Controls, Classes, ExtCtrls;

type
  // グリップハンドル
  TResizeGrip = class(TCustomControl)
    protected
      procedure Paint; override;

    public
      property  Canvas;
      property  OnMouseDown;
      property  OnMouseMove;
      property  OnMouseUp;
  end;
  //------------------------------------------------------------
  TResizeControl = class(TShape)
    private
      FControl:     TControl;
      FBackColor:   TColor;
      FDragging:    Boolean;
      FEditing:     Boolean;
      FShowHint:    Boolean;
      FHintWindow:  THintWindow;
      FResizeGrip:  array[0..7] of TResizeGrip;
      FGap:         Integer; //
      FSpace:       Integer; // コントロールと FControl との端部のスペース
      FGripSize:    Integer; // グリップのサイズ
      FOrgX:        Integer; // マウスダウンしたときのマウスの位置
      FOrgY:        Integer; // 同上
      FOnMouseDown: TMouseEvent;
      FOnMouseMove: TMouseMoveEvent;
      FOnMouseUp:   TMouseEvent;

      procedure HideGrips;
      procedure MoveGrips;
      procedure ShowGrips;
      procedure Move(Sender: TObject; X, Y: Integer);
      procedure SetBackColor(c: TColor);
      procedure SetShowHint(flag: Boolean);

    protected
      procedure DoMouseDown(Sender: TObject;
           Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
      procedure DoMouseMove(Sender: TObject;
           Shift: TShiftState; X, Y: Integer);
      procedure DoMouseUp(Sender: TObject;
           Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
      procedure SetControl(Control:TControl); virtual;
      procedure SetParent(Control:TWinControl); override;

    public
      constructor Create(Owner:TComponent); override;
      destructor  Destroy; override;
      procedure   Hide;

    published
      property Control: TControl read FControl write SetControl;
      property Color: TColor read FBackColor write SetBackColor;
      property ShowHint: Boolean read FShowHint write SetShowHint;

      property OnMouseDown: TMouseEvent read FOnMouseDown write FOnMouseDown;
      property OnMouseMove: TMouseMoveEvent read FOnMouseMove write FOnMouseMove;
      property OnMouseUp:   TMouseEvent read FOnMouseUp write FOnMouseUp;
  end;
//*******************************************************************************

implementation

//******************************************************************************
// コンストラクタ
constructor TResizeControl.Create(Owner:TComponent);
const
  // 各グリップのカーソル
  fNC: array[0..7] of TCursor = (
       crSizeNWSE, crSizeNS, crSizeNESW, crSizeWE,
       crSizeNWSE, crSizeNS, crSizeNESW, crSizeWE);
var
  i: Integer;

begin
  inherited Create(Owner);

  FControl   := nil;
  FBackColor := clBtnFace;
  FDragging  := False;
  FEditing   := True;
  FShowHint  := True;
  FGap       := 7;
  FSpace     := 7;
  FGripSize  := 7;

  FOnMouseDown  := nil;
  FOnMouseMove  := nil;
  FOnMouseUp    := nil;

  Brush.Color := FBackColor;
  Brush.Style := bsSolid;
  Cursor      := crSizeAll;
  Height      := 0;
  Left        := 0;
  Pen.Style   := psClear;
  Shape       := stRectangle;
  Tag         := 8;
  Top         := 0;
  Visible     := False;
  Width       := 0;

  inherited OnMouseDown := DoMouseDown;
  inherited OnMouseMove := DoMouseMove;
  inherited OnMouseUp   := DoMouseUp;

  FHintWindow := THintWindow.Create(Self);

  with FHintWindow do begin
    Brush.Color := clInfoBk;
    ActivateHint(Rect(0, 0, 0, 0), '');
  end;

  for i := 0 to 7 do begin
    FResizeGrip[i] := TResizeGrip.Create(Self);

    with FResizeGrip[i] do begin
      Canvas.Brush.Color  := clPurple;
      Canvas.Brush.Style  := bsSolid;
      Canvas.Pen.Color    := clWhite;
      Canvas.Pen.Mode     := pmCopy;
      Canvas.Pen.Style    := psSolid;
      Canvas.Pen.Width    := 1;
      Cursor    := fNC[i];
      Height    := FGripSize;
      Left      := 0;
      Tag       := i;
      Top       := 0;
      Visible   := False;
      Width     := FGripSize;

      OnMouseDown := DoMouseDown;
      OnMouseMove := DoMouseMove;
      OnMouseUp   := DoMouseUp;
    end;
  end;

  FEditing := False;
end;
//*****************************************************************************
// デストラクタ
destructor TResizeControl.Destroy;
begin
  FHintWindow.ReleaseHandle();
  FHintWindow.Free();

  inherited Destroy();
end;

//*****************************************************************************
// マウスダウンした
procedure TResizeControl.DoMouseDown(Sender: TObject;
     Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
begin
  if Assigned(FOnMouseDown) then
  begin
    FOnMouseDown(Sender, Button, Shift, X, Y);
  end;

  if FEditing then Exit else FEditing := True;

  try
    case Button of
      mbLeft:
      begin
        FDragging := True;
        FOrgX     := X;
        FOrgY     := Y;

        if (TComponent(Sender).Tag = 8) then HideGrips();

        Move(Sender, X, Y);
      end;
    end;

  finally
    FEditing := False;
  end;
end;

//*****************************************************************************
// マウスを移動した
procedure TResizeControl.DoMouseMove(Sender: TObject;
     Shift: TShiftState; X, Y: Integer);
begin
  if Assigned(FOnMouseMove) then
  begin
    FOnMouseMove(Sender, Shift, X, Y);
  end;

  if FEditing or not FDragging then Exit else FEditing := True;

  try
    Move(Sender, X, Y);
  finally
    FEditing := False;
  end;
end;

//*****************************************************************************
// マウスアップした
procedure TResizeControl.DoMouseUp(Sender: TObject;
     Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
begin
  if Assigned(FOnMouseUp) then
  begin
    FOnMouseUp(Sender, Button, Shift, X, Y);
  end;

  if FEditing or not FDragging then Exit else FEditing := True;

  try
    Move(Sender, X, Y);
    if (TComponent(Sender).Tag = 8) then ShowGrips();

    with FHintWindow do
    begin
      Height := 0;
      Left   := 0;
      Top    := 0;
      Width  := 0;
    end;

    FDragging := False;

  finally
    FEditing := False;
  end;
end;

//******************************************************************************
// グリップハンドルを非表示にする（非公開メソッド）
procedure TResizeControl.HideGrips;
var
  i: Integer;

begin
  for i := 0 to 7 do
  begin
    FResizeGrip[i].Hide();
  end;
end;

//*****************************************************************************
// グリップハンドルを非表示にする
procedure TResizeControl.Hide;
begin
  HideGrips;
  Visible := False;
end;

//*****************************************************************************
// ターゲットコントロールおよびコントロールを移動する
procedure TResizeControl.Move(Sender:TObject; X, Y: Integer);
const
  R: array[0..8] of record
          iL: Integer;
          iT: Integer;
          iW: Integer;
          iH: Integer;
  end = (
        (iL:  1; iT:  1; iW: -1; iH: -1;),
        (iL:  0; iT:  1; iW:  0; iH: -1;),
        (iL:  0; iT:  1; iW:  1; iH: -1;),
        (iL:  0; iT:  0; iW:  1; iH:  0;),
        (iL:  0; iT:  0; iW:  1; iH:  1;),
        (iL:  0; iT:  0; iW:  0; iH:  1;),
        (iL:  1; iT:  0; iW: -1; iH:  1;),
        (iL:  1; iT:  0; iW: -1; iH:  0;),
        (iL:  1; iT:  1; iW:  0; iH:  0;) );

var
  S: string;

begin
  // ターゲットコントロールの位置
  with FControl, R[TComponent(Sender).Tag] do
  begin
    Left   := Left   + ((X - FOrgX) * iL);
    Top    := Top    + ((Y - FOrgY) * iT);
    Width  := Width  + ((X - FOrgX) * iW);
    Height := Height + ((Y - FOrgY) * iH);
  end;

  // 自身の位置
  Left   := FControl.Left   - FSpace;
  Top    := FControl.Top    - FSpace;
  Width  := FControl.Width  + (FSpace * 2);
  Height := FControl.Height + (FSpace * 2);

  if (TComponent(Sender).Tag = 8) then
  begin
    S := Format('X: %d, Y: %d', [FControl.Left, FControl.Top]);
  end
  else
  begin
    MoveGrips();
    S := Format('W: %d, H: %d', [FControl.Width, FControl.Height]);
  end;

  if (FShowHint) then
  begin
    with TControl(Sender).ClientToScreen(Point(X, Y)) do
    begin
      with FHintWindow.CalcHintRect(100, S, nil) do
      begin
        FHintWindow.Left    := X + 9;
        FHintWindow.Top     := Y - 9;
        FHintWindow.Width   := Right;
        FHintWindow.Height  := Bottom;
        FHintWindow.Caption := S;
      end;
    end;
  end;
end;

//******************************************************************************
// グリップハンドルを移動する
procedure TResizeControl.MoveGrips;
const
  C: array[0..7] of record
          iX: Integer;
          iY: Integer;
  end = ((iX: 0; iY: 0;), (iX: 1; iY: 0;),
         (iX: 2; iY: 0;), (iX: 2; iY: 1;),
         (iX: 2; iY: 2;), (iX: 1; iY: 2;),
         (iX: 0; iY: 2;), (iX: 0; iY: 1;));

var
  i: Integer;

begin
  for i := 0 to 7 do
  begin
    FResizeGrip[i].Left := Left - FGripSize + FGap
          + Trunc((Width - (FGap * 2) + FGripSize - 1) * C[i].iX / 2);

    FResizeGrip[i].Top := Top - FGripSize + FGap
          + Trunc((Height - (FGap * 2) + FGripSize - 1) * C[i].iY / 2);
  end;
end;

//*****************************************************************************
// リサイズ対象のコントロールを設定する
procedure TResizeControl.SetControl(Control: TControl);
begin
  FControl := Control;

  if not Assigned(FControl) or not Assigned(FControl.Parent) then
  begin
    Visible := False;
    HideGrips();
  end
  else
  begin
    inherited SetParent(FControl.Parent);

    Left    := FControl.Left   - FSpace;
    Top     := FControl.Top    - FSpace;
    Width   := FControl.Width  + (FSpace * 2);
    Height  := FControl.Height + (FSpace * 2);
    Visible := True;

    ShowGrips();

    FControl.BringToFront();
  end;
end;

//*****************************************************************************
// コントロールの背景色を設定する
procedure TResizeControl.SetBackColor(c: TColor);
begin
  FBackColor := c;
  Brush.Color := FBackColor;//clSilver;
end;

//*****************************************************************************
// ヒントウインドウを表示するかどうかを設定する
procedure TResizeControl.SetShowHint(flag: Boolean);
begin
  FShowHint := flag;
end;

//*****************************************************************************
// 親コントロールを設定する
procedure TResizeControl.SetParent(Control: TWinControl);
begin
  inherited SetParent(Control);

  if Assigned(Control) then
  begin
    SetControl(nil);
  end;
end;

//*****************************************************************************
// グリップハンドルを表示する
procedure TResizeControl.ShowGrips;
var
  i: Integer;

begin
  MoveGrips();

  for i := 0 to 7 do
  begin
    FResizeGrip[i].Parent := Parent;
    FResizeGrip[i].Show();
  end;
end;

//*****************************************************************************
//   グリップハンドル
//*****************************************************************************

// グリップハンドルを描画する
// Pen と Brush は TResizeControl の Create メソッドで設定している
procedure TResizeGrip.Paint;
begin
  Canvas.Rectangle(Rect(0, 0, Width, Height));
end;

end.
