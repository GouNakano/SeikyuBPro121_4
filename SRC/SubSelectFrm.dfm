object SubSelectForm: TSubSelectForm
  Left = 530
  Top = 183
  Width = 280
  Height = 301
  BorderIcons = [biSystemMenu]
  Caption = 'SubSelectForm'
  Color = clBtnFace
  Font.Charset = SHIFTJIS_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 12
  object Panel1: TPanel
    Left = 0
    Top = 232
    Width = 272
    Height = 35
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    object Panel2: TPanel
      Left = 110
      Top = 0
      Width = 162
      Height = 35
      Align = alRight
      BevelOuter = bvNone
      TabOrder = 0
      object CancelBtn: TButton
        Left = 84
        Top = 4
        Width = 75
        Height = 25
        Cancel = True
        Caption = #38281#12376#12427
        TabOrder = 0
        OnClick = CancelBtnClick
      end
      object OkBtn: TButton
        Left = 3
        Top = 4
        Width = 75
        Height = 25
        Caption = #36984#25246
        Default = True
        TabOrder = 1
        OnClick = OkBtnClick
      end
    end
  end
  object ItemListBox: TListBox
    Left = 0
    Top = 13
    Width = 272
    Height = 219
    Align = alClient
    ItemHeight = 12
    PopupMenu = PopupMenu
    TabOrder = 1
    OnDblClick = OkBtnClick
  end
  object Panel3: TPanel
    Left = 0
    Top = 0
    Width = 272
    Height = 13
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 2
  end
  object PopupMenu: TPopupMenu
    Left = 36
    Top = 160
    object DeleteMenu: TMenuItem
      Caption = #21066#38500'(&D)'
      OnClick = DeleteMenuClick
    end
  end
end
