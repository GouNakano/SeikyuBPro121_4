object CalendarForm: TCalendarForm
  Left = 427
  Top = 327
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #26085#20184#12398#35373#23450
  ClientHeight = 236
  ClientWidth = 244
  Color = clWhite
  Font.Charset = SHIFTJIS_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
  Font.Style = []
  Position = poMainFormCenter
  StyleName = 'Windows'
  OnCreate = FormCreate
  TextHeight = 12
  object MonthCalendar: TMonthCalendar
    Left = 0
    Top = 0
    Width = 244
    Height = 197
    Align = alClient
    Date = 38043.000000000000000000
    TabOrder = 0
  end
  object Panel1: TPanel
    Left = 0
    Top = 197
    Width = 244
    Height = 39
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    object Panel2: TPanel
      Left = 78
      Top = 0
      Width = 166
      Height = 39
      Align = alRight
      BevelOuter = bvNone
      TabOrder = 0
      object OKBtn: TBitBtn2
        Left = 8
        Top = 8
        Width = 75
        Height = 25
        Caption = 'OK'
        DoubleBuffered = True
        DoubleBufferedMode = dbmRequested
        ParentDoubleBuffered = False
        TabOrder = 0
        OnClick = OKBtnClick
        DownColor = clBtnFace
      end
      object CancelBtn: TBitBtn2
        Left = 88
        Top = 8
        Width = 75
        Height = 25
        Caption = #65399#65388#65437#65406#65433
        DoubleBuffered = True
        DoubleBufferedMode = dbmRequested
        ModalResult = 2
        ParentDoubleBuffered = False
        TabOrder = 1
        DownColor = clBtnFace
      end
    end
  end
end
