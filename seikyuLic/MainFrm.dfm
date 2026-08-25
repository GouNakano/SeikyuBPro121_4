object MainForm: TMainForm
  Left = 254
  Top = 134
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #35531#27714#26360#30058#38957' '#12503#12525#29256' '#12521#12452#12475#12531#12473#30330#34892
  ClientHeight = 238
  ClientWidth = 490
  Color = clBtnFace
  Font.Charset = SHIFTJIS_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 12
  object Label1: TLabel
    Left = 8
    Top = 104
    Width = 130
    Height = 12
    Caption = #12521#12452#12475#12531#12473#35469#35388#12497#12473#12527#12540#12489
  end
  object Label2: TLabel
    Left = 12
    Top = 12
    Width = 106
    Height = 12
    Caption = #12521#12452#12475#12531#12473#30003#35531#12467#12540#12489
  end
  object Label3: TLabel
    Left = 12
    Top = 60
    Width = 84
    Height = 12
    Caption = #12487#12451#12473#12463#12471#12522#12450#12523
  end
  object ErrLabel: TLabel
    Left = 112
    Top = 60
    Width = 152
    Height = 11
    Caption = #12521#12452#12475#12531#12473#30003#35531#12467#12540#12489#12364#19981#27491#12391#12377
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clRed
    Font.Height = -11
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    ParentFont = False
    Visible = False
  end
  object LicreqEdit: TEdit
    Left = 8
    Top = 28
    Width = 461
    Height = 20
    TabOrder = 0
  end
  object IssueBtn: TButton
    Left = 396
    Top = 188
    Width = 85
    Height = 41
    Caption = #30330#34892#12377#12427
    Default = True
    TabOrder = 1
    OnClick = IssueBtnClick
  end
  object DiskSerialEdit: TEdit
    Left = 8
    Top = 76
    Width = 461
    Height = 20
    Color = clBtnFace
    ReadOnly = True
    TabOrder = 2
  end
  object LicPasswdEdit: TEdit
    Left = 8
    Top = 124
    Width = 461
    Height = 20
    Color = clBtnFace
    ReadOnly = True
    TabOrder = 3
  end
  object CopyBtn: TButton
    Left = 8
    Top = 152
    Width = 75
    Height = 25
    Caption = #12467#12500#12540
    TabOrder = 4
    OnClick = CopyBtnClick
  end
end
