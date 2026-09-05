object FirstMesForm: TFirstMesForm
  Left = 410
  Top = 357
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #35531#27714#26360#30058#38957' '#12503#12525#29256#12408#12424#12358#12371#12381
  ClientHeight = 187
  ClientWidth = 493
  Color = clBtnFace
  CustomTitleBar.Control = TitleBarPanel
  CustomTitleBar.Enabled = True
  CustomTitleBar.Height = 31
  CustomTitleBar.BackgroundColor = clWhite
  CustomTitleBar.ForegroundColor = 65793
  CustomTitleBar.InactiveBackgroundColor = clWhite
  CustomTitleBar.InactiveForegroundColor = 10066329
  CustomTitleBar.ButtonForegroundColor = 65793
  CustomTitleBar.ButtonBackgroundColor = clWhite
  CustomTitleBar.ButtonHoverForegroundColor = 65793
  CustomTitleBar.ButtonHoverBackgroundColor = 16053492
  CustomTitleBar.ButtonPressedForegroundColor = 65793
  CustomTitleBar.ButtonPressedBackgroundColor = 15395562
  CustomTitleBar.ButtonInactiveForegroundColor = 10066329
  CustomTitleBar.ButtonInactiveBackgroundColor = clWhite
  Font.Charset = SHIFTJIS_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
  Font.Style = []
  GlassFrame.Enabled = True
  GlassFrame.Top = 31
  Position = poMainFormCenter
  StyleElements = []
  StyleName = 'Windows'
  OnClose = FormClose
  OnCreate = FormCreate
  TextHeight = 12
  object Label1: TLabel
    Left = 8
    Top = 12
    Width = 257
    Height = 12
    Caption = #35531#27714#26360#30058#38957' '#12503#12525#29256#12398#12372#20351#29992#12354#12426#12364#12392#12358#12372#12374#12356#12414#12377#12290
  end
  object Label2: TLabel
    Left = 8
    Top = 41
    Width = 329
    Height = 12
    Caption = #26412#35069#21697#12398#20351#29992#12395#12399#12289#21021#12417#12395#33258#31038#24773#22577#12434#35373#23450#12377#12427#24517#35201#12364#12354#12426#12414#12377#12290
  end
  object Label3: TLabel
    Left = 8
    Top = 57
    Width = 357
    Height = 12
    Caption = #33258#31038#24773#22577#12398#35373#23450#12399#12513#12491#12517#12540#12398#35373#23450'(S)-'#33258#31038#24773#22577#12398#35373#23450'(C)'#12434#36984#25246#12375#12390#12289
  end
  object Label4: TLabel
    Left = 8
    Top = 73
    Width = 230
    Height = 12
    Caption = #20250#31038#12420#20107#26989#25152#12394#12393#12398#24773#22577#12434#20837#21147#12375#12390#12367#12384#12373#12356#12290
  end
  object Label5: TLabel
    Left = 8
    Top = 105
    Width = 300
    Height = 12
    Caption = '('#8251#33258#31038#24773#22577#12399#35531#27714#26360#12289#32013#21697#26360#12381#12428#12382#12428#12395#35373#23450#12375#12390#12367#12384#12373#12356')'
  end
  object Label6: TLabel
    Left = 8
    Top = 89
    Width = 408
    Height = 12
    Caption = #33258#31038#24773#22577#12398#26360#39006#12408#12398#21453#26144#12399#12513#12491#12517#12540#12398#32232#38598'(E)-'#33258#31038#24773#22577#12398#21453#26144'(C)'#12391#34892#12356#12414#12377#12290
  end
  object Label7: TLabel
    Left = 8
    Top = 125
    Width = 479
    Height = 12
    Caption = #27491#35215#12521#12452#12475#12531#12473#12364#35373#23450#12373#12428#12390#12356#12394#12356'PC'#12391#12399#12289#26360#39006#12398#21360#21047#12395#21046#38480#12364#12354#12426#12414#12377#12398#12391#12289#12372#20102#25215#19979#12373#12356#12290
  end
  object NextCheckBox: TCheckBox
    Left = 8
    Top = 153
    Width = 161
    Height = 17
    Caption = #27425#22238#36215#21205#26178#12399#34920#31034#12375#12394#12356
    TabOrder = 0
  end
  object CloseBtn: TBitBtn2
    Left = 412
    Top = 152
    Width = 75
    Height = 25
    Cancel = True
    Caption = #38281#12376#12427
    DoubleBuffered = True
    DoubleBufferedMode = dbmRequested
    ModalResult = 2
    ParentDoubleBuffered = False
    TabOrder = 1
    DownColor = clBtnFace
  end
  object TitleBarPanel: TTitleBarPanel
    Left = 0
    Top = 0
    Width = 493
    Height = 30
    Margins.Left = 0
    Margins.Top = 0
    Margins.Right = 50
    Margins.Bottom = 0
    CustomButtons = <>
  end
end
