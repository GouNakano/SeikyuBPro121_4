object DispSettingForm: TDispSettingForm
  Left = 352
  Top = 121
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #26360#39006#37096#21697#34920#31034#35373#23450
  ClientHeight = 558
  ClientWidth = 416
  Color = clBtnFace
  Font.Charset = SHIFTJIS_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
  Font.Style = []
  Position = poScreenCenter
  StyleName = 'Windows'
  OnShow = FormShow
  TextHeight = 12
  object Panel1: TPanel
    Left = 0
    Top = 521
    Width = 416
    Height = 37
    Align = alBottom
    BevelOuter = bvNone
    Color = clWhite
    ParentBackground = False
    TabOrder = 0
    object Panel2: TPanel
      Left = 153
      Top = 0
      Width = 263
      Height = 37
      Align = alRight
      BevelOuter = bvNone
      TabOrder = 0
      object OkBtn: TButton
        Left = 56
        Top = 5
        Width = 100
        Height = 30
        Caption = 'OK'
        Default = True
        TabOrder = 0
        OnClick = OkBtnClick
      end
      object CancelBtn: TButton
        Left = 160
        Top = 5
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
    Top = 0
    Width = 416
    Height = 521
    Align = alClient
    TabOrder = 1
    object ObjectListView: TListView2
      Left = 1
      Top = 1
      Width = 414
      Height = 519
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
    end
  end
end
