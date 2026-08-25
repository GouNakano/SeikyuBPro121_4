object LabelModifyForm: TLabelModifyForm
  Left = 246
  Top = 329
  BorderStyle = bsDialog
  Caption = #12521#12505#12523#12398#22793#26356
  ClientHeight = 78
  ClientWidth = 292
  Color = clBtnFace
  Font.Charset = SHIFTJIS_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
  Font.Style = []
  Position = poMainFormCenter
  StyleName = 'Windows'
  OnClose = FormClose
  OnShow = FormShow
  TextHeight = 12
  object LabelValEdit: TBaseEdit
    Left = 8
    Top = 12
    Width = 277
    Height = 20
    TabOrder = 0
    dx = 0
    dy = 0
  end
  object ModifyBtn: TBitBtn2
    Left = 124
    Top = 48
    Width = 75
    Height = 25
    Caption = #22793#26356
    Default = True
    DoubleBuffered = True
    DoubleBufferedMode = dbmRequested
    ParentDoubleBuffered = False
    TabOrder = 1
    OnClick = ModifyBtnClick
    DownColor = clBtnFace
  end
  object CancelBtn: TBitBtn2
    Left = 208
    Top = 48
    Width = 75
    Height = 25
    Cancel = True
    Caption = #65399#65388#65437#65406#65433
    DoubleBuffered = True
    DoubleBufferedMode = dbmRequested
    ParentDoubleBuffered = False
    TabOrder = 2
    OnClick = CancelBtnClick
    DownColor = clBtnFace
  end
end
