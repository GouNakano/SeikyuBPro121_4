object ComponentsForm: TComponentsForm
  Left = 402
  Top = 171
  Caption = #37096#21697#19968#35239#34920
  ClientHeight = 471
  ClientWidth = 739
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
  Position = poMainFormCenter
  StyleElements = [seFont, seClient]
  StyleName = 'Windows'
  OnCreate = FormCreate
  OnShow = FormShow
  TextHeight = 12
  object Panel1: TPanel
    Left = 0
    Top = 435
    Width = 739
    Height = 36
    Align = alBottom
    Color = clWhite
    ParentBackground = False
    TabOrder = 0
    object Panel2: TPanel
      Left = 492
      Top = 1
      Width = 246
      Height = 34
      Align = alRight
      TabOrder = 0
      object CloseBtn: TBitBtn2
        Left = 163
        Top = 4
        Width = 75
        Height = 25
        Caption = #38281#12376#12427
        DoubleBuffered = True
        DoubleBufferedMode = dbmRequested
        ParentDoubleBuffered = False
        TabOrder = 0
        OnClick = CloseBtnClick
        DownColor = clBtnFace
      end
      object FormatBtn: TBitBtn2
        Left = 39
        Top = 4
        Width = 118
        Height = 25
        Caption = #26360#24335#35373#23450
        Default = True
        DoubleBuffered = True
        DoubleBufferedMode = dbmRequested
        ParentDoubleBuffered = False
        TabOrder = 1
        OnClick = FormatBtnClick
        DownColor = clBtnFace
      end
    end
  end
  object ListView: TListView2
    Left = 0
    Top = 30
    Width = 739
    Height = 405
    Align = alClient
    Columns = <
      item
        Caption = #21517#31216
        Width = 200
      end
      item
        Caption = #34920#31034
      end
      item
        Caption = #21360#21047
      end
      item
        Caption = #27700#24179#20301#32622
        Width = 65
      end
      item
        Caption = #22402#30452#20301#32622
        Width = 60
      end
      item
        Caption = #24133
      end
      item
        Caption = #39640#12373
      end
      item
        Caption = #20869#23481
        Width = 200
      end>
    ColumnClick = False
    RowSelect = True
    TabOrder = 1
    ViewStyle = vsReport
    OnDeletion = ListViewDeletion
    HeaderColor = clBtnFace
  end
  object TitleBarPanel: TTitleBarPanel
    Left = 0
    Top = 0
    Width = 739
    Height = 30
    Margins.Left = 0
    Margins.Top = 0
    Margins.Right = 50
    Margins.Bottom = 0
    CustomButtons = <>
  end
end
