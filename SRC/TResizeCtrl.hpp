// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'TResizeCtrl.pas' rev: 6.00

#ifndef TResizeCtrlHPP
#define TResizeCtrlHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <ExtCtrls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Tresizectrl
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TResizeGrip;
class PASCALIMPLEMENTATION TResizeGrip : public Controls::TCustomControl 
{
	typedef Controls::TCustomControl inherited;
	
protected:
	virtual void __fastcall Paint(void);
	
public:
	__property Canvas ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
public:
	#pragma option push -w-inl
	/* TCustomControl.Create */ inline __fastcall virtual TResizeGrip(Classes::TComponent* AOwner) : Controls::TCustomControl(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomControl.Destroy */ inline __fastcall virtual ~TResizeGrip(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TResizeGrip(HWND ParentWindow) : Controls::TCustomControl(ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TResizeControl;
class PASCALIMPLEMENTATION TResizeControl : public Extctrls::TShape 
{
	typedef Extctrls::TShape inherited;
	
private:
	Controls::TControl* FControl;
	Graphics::TColor FBackColor;
	bool FDragging;
	bool FEditing;
	bool FShowHint;
	Controls::THintWindow* FHintWindow;
	TResizeGrip* FResizeGrip[8];
	int FGap;
	int FSpace;
	int FGripSize;
	int FOrgX;
	int FOrgY;
	Controls::TMouseEvent FOnMouseDown;
	Controls::TMouseMoveEvent FOnMouseMove;
	Controls::TMouseEvent FOnMouseUp;
	void __fastcall HideGrips(void);
	void __fastcall MoveGrips(void);
	void __fastcall ShowGrips(void);
	void __fastcall Move(System::TObject* Sender, int X, int Y);
	void __fastcall SetBackColor(Graphics::TColor c);
	HIDESBASE void __fastcall SetShowHint(bool flag);
	
protected:
	HIDESBASE void __fastcall DoMouseDown(System::TObject* Sender, Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	void __fastcall DoMouseMove(System::TObject* Sender, Classes::TShiftState Shift, int X, int Y);
	HIDESBASE void __fastcall DoMouseUp(System::TObject* Sender, Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall SetControl(Controls::TControl* Control);
	virtual void __fastcall SetParent(Controls::TWinControl* Control);
	
public:
	__fastcall virtual TResizeControl(Classes::TComponent* Owner);
	__fastcall virtual ~TResizeControl(void);
	HIDESBASE void __fastcall Hide(void);
	
__published:
	__property Controls::TControl* Control = {read=FControl, write=SetControl};
	__property Graphics::TColor Color = {read=FBackColor, write=SetBackColor, nodefault};
	__property bool ShowHint = {read=FShowHint, write=SetShowHint, nodefault};
	__property Controls::TMouseEvent OnMouseDown = {read=FOnMouseDown, write=FOnMouseDown};
	__property Controls::TMouseMoveEvent OnMouseMove = {read=FOnMouseMove, write=FOnMouseMove};
	__property Controls::TMouseEvent OnMouseUp = {read=FOnMouseUp, write=FOnMouseUp};
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Tresizectrl */
using namespace Tresizectrl;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// TResizeCtrl
