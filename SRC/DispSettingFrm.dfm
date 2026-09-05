object DispSettingForm: TDispSettingForm
  Left = 352
  Top = 121
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #26360#39006#37096#21697#34920#31034#35373#23450
  ClientHeight = 597
  ClientWidth = 478
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
  Position = poScreenCenter
  StyleElements = [seFont, seClient]
  StyleName = 'Windows'
  OnCreate = FormCreate
  OnShow = FormShow
  TextHeight = 12
  object Panel1: TPanel
    Left = 0
    Top = 555
    Width = 478
    Height = 42
    Align = alBottom
    BevelOuter = bvNone
    Color = clWhite
    ParentBackground = False
    TabOrder = 0
    ExplicitTop = 586
    object Panel2: TPanel
      Left = 215
      Top = 0
      Width = 263
      Height = 42
      Align = alRight
      BevelOuter = bvNone
      TabOrder = 0
      ExplicitLeft = 153
      ExplicitHeight = 37
      object OkBtn: TButton
        Left = 53
        Top = 8
        Width = 100
        Height = 30
        Caption = 'OK'
        Default = True
        TabOrder = 0
        OnClick = OkBtnClick
      end
      object CancelBtn: TButton
        Left = 157
        Top = 8
        Width = 100
        Height = 30
        Cancel = True
        Caption = #12461#12515#12531#12475#12523
        TabOrder = 1
        OnClick = CancelBtnClick
      end
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 30
    Width = 478
    Height = 525
    Align = alClient
    TabOrder = 1
    ExplicitTop = 0
    ExplicitWidth = 416
    ExplicitHeight = 521
    object ObjectListView: TListView2
      Left = 1
      Top = 1
      Width = 476
      Height = 554
      Align = alClient
      BevelInner = bvNone
      BevelOuter = bvNone
      Checkboxes = True
      Columns = <
        item
          Caption = #34920#31034
        end
        item
          Caption = #12479#12452#12503
          Width = 100
        end
        item
          Caption = #21517#31216
          Width = 200
        end>
      ColumnClick = False
      TabOrder = 0
      ViewStyle = vsReport
      OnDeletion = ObjectListViewDeletion
      HeaderColor = clBtnFace
      ExplicitLeft = 33
      ExplicitTop = 25
      ExplicitWidth = 414
      ExplicitHeight = 519
    end
  end
  object TitleBarPanel: TTitleBarPanel
    Left = 0
    Top = 0
    Width = 478
    Height = 30
    Margins.Left = 0
    Margins.Top = 0
    Margins.Right = 50
    Margins.Bottom = 0
    CustomButtons = <>
    ExplicitWidth = 416
    ExplicitHeight = 31
  end
end
