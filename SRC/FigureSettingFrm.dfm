object FigureSettingForm: TFigureSettingForm
  Left = 238
  Top = 129
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #26689#25968#35373#23450
  ClientHeight = 99
  ClientWidth = 210
  Color = clBtnFace
  Font.Charset = SHIFTJIS_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 12
  object Label1: TLabel
    Left = 12
    Top = 20
    Width = 24
    Height = 12
    Caption = #26689#25968
  end
  object Label2: TLabel
    Left = 96
    Top = 20
    Width = 97
    Height = 12
    Caption = '(4'#65374'12'#12398#38291#12391#35373#23450')'
  end
  object FigureEdit: TEdit
    Left = 44
    Top = 16
    Width = 37
    Height = 20
    MaxLength = 2
    TabOrder = 0
  end
  object OkBtn: TButton
    Left = 48
    Top = 68
    Width = 75
    Height = 25
    Caption = #35373#23450
    Default = True
    TabOrder = 1
    OnClick = OkBtnClick
  end
  object CancelBtn: TButton
    Left = 128
    Top = 68
    Width = 75
    Height = 25
    Cancel = True
    Caption = #12461#12515#12531#12475#12523
    TabOrder = 2
    OnClick = CancelBtnClick
  end
end
