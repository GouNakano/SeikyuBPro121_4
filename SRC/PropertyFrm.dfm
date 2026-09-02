object PropertyForm: TPropertyForm
  Left = 366
  Top = 114
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #37096#21697#24773#22577#35373#23450
  ClientHeight = 209
  ClientWidth = 217
  Color = clWhite
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
  Position = poOwnerFormCenter
  StyleElements = [seFont, seClient]
  StyleName = 'Windows'
  OnCreate = FormCreate
  OnShow = FormShow
  TextHeight = 12
  object Panel1: TPanel
    Left = 0
    Top = 173
    Width = 217
    Height = 36
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    object Panel2: TPanel
      Left = -29
      Top = 0
      Width = 246
      Height = 36
      Align = alRight
      BevelOuter = bvNone
      TabOrder = 0
      object CloseBtn: TBitBtn2
        Left = 168
        Top = 6
        Width = 75
        Height = 25
        Cancel = True
        Caption = #38281#12376#12427
        DoubleBuffered = True
        DoubleBufferedMode = dbmRequested
        ModalResult = 2
        ParentDoubleBuffered = False
        TabOrder = 0
        DownColor = clBtnFace
      end
      object FormatBtn: TBitBtn2
        Left = 72
        Top = 6
        Width = 90
        Height = 25
        Caption = #35373#23450
        DoubleBuffered = True
        DoubleBufferedMode = dbmRequested
        ParentDoubleBuffered = False
        TabOrder = 1
        OnClick = FormatBtnClick
        DownColor = clBtnFace
      end
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 30
    Width = 217
    Height = 143
    Align = alClient
    TabOrder = 1
    object Label1: TLabel
      Left = 12
      Top = 13
      Width = 24
      Height = 12
      Caption = #21517#31216
    end
    object NameLabel: TLabel
      Left = 68
      Top = 13
      Width = 56
      Height = 12
      Caption = 'NameLabel'
    end
    object Label2: TLabel
      Left = 12
      Top = 38
      Width = 48
      Height = 12
      Caption = #27700#24179#20301#32622
    end
    object Label3: TLabel
      Left = 12
      Top = 62
      Width = 48
      Height = 12
      Caption = #22402#30452#20301#32622
    end
    object Label4: TLabel
      Left = 160
      Top = 38
      Width = 12
      Height = 12
      Caption = #13212
    end
    object Label5: TLabel
      Left = 160
      Top = 62
      Width = 12
      Height = 12
      Caption = #13212
    end
    object Label6: TLabel
      Left = 12
      Top = 86
      Width = 12
      Height = 12
      Caption = #24133
    end
    object Label7: TLabel
      Left = 160
      Top = 86
      Width = 12
      Height = 12
      Caption = #13212
    end
    object Label8: TLabel
      Left = 12
      Top = 110
      Width = 21
      Height = 12
      Caption = #39640#12373
    end
    object Label9: TLabel
      Left = 160
      Top = 110
      Width = 12
      Height = 12
      Caption = #13212
    end
    object XEdit: TBaseEdit
      Left = 68
      Top = 34
      Width = 85
      Height = 20
      TabOrder = 0
      dx = 0
      dy = 0
    end
    object YEdit: TBaseEdit
      Left = 68
      Top = 58
      Width = 85
      Height = 20
      TabOrder = 1
      dx = 0
      dy = 0
    end
    object WidthEdit: TBaseEdit
      Left = 68
      Top = 82
      Width = 85
      Height = 20
      TabOrder = 2
      dx = 0
      dy = 0
    end
    object HeightEdit: TBaseEdit
      Left = 68
      Top = 106
      Width = 85
      Height = 20
      TabOrder = 3
      dx = 0
      dy = 0
    end
  end
  object TitleBarPanel: TTitleBarPanel
    Left = 0
    Top = 0
    Width = 217
    Height = 30
    Margins.Left = 0
    Margins.Top = 0
    Margins.Right = 50
    Margins.Bottom = 0
    CustomButtons = <>
  end
end
