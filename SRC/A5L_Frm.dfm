object A5L_Form: TA5L_Form
  Tag = 90
  Left = 470
  Top = 122
  Caption = 'A5-L'
  ClientHeight = 496
  ClientWidth = 752
  Color = clWhite
  Font.Charset = SHIFTJIS_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
  Font.Style = []
  TextHeight = 12
  object StampImage1: TImage
    Left = 566
    Top = 13
    Width = 31
    Height = 31
  end
  object StampImage2: TImage
    Left = 596
    Top = 13
    Width = 31
    Height = 31
  end
  object LogoImage: TImage
    Left = 381
    Top = 412
    Width = 70
    Height = 35
    Center = True
  end
  object DayUnderShape: TWinShape
    Left = 32
    Top = 46
    Width = 606
    Height = 2
    Shape = wsHorLine
  end
  object NameUnderShape: TWinShape
    Left = 32
    Top = 76
    Width = 229
    Height = 2
    Shape = wsHorLine
  end
  object ItemShape: TWinShape
    Left = 32
    Top = 125
    Width = 327
    Height = 2
    Shape = wsHorLine
  end
  object NumberShape: TWinShape
    Left = 469
    Top = 68
    Width = 170
    Height = 2
    Shape = wsHorLine
  end
  object MoneyShape: TWinShape
    Left = 32
    Top = 165
    Width = 301
    Height = 2
    Shape = wsHorLine
  end
  object NoteShape: TWinShape
    Left = 32
    Top = 408
    Width = 422
    Height = 2
    Shape = wsHorLine
  end
  object HonorificTitleLabel: TWinLabel
    Left = 234
    Top = 61
    Width = 30
    Height = 15
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -15
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = #27096
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    Color = 15984895
    ParentColor = False
    ParentFont = False
  end
  object SubTotalLabel: TWinLabel
    Left = 464
    Top = 384
    Width = 109
    Height = 20
    BorderDraw = True
    Layout = tlCenter
    Pen.Color = clGray
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -12
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = #23567#35336
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    ParentFont = False
  end
  object TaxLabel: TWinLabel
    Left = 464
    Top = 403
    Width = 109
    Height = 20
    BorderDraw = True
    Layout = tlCenter
    Pen.Color = clGray
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -12
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = #28040#36027#31246'(5%)'
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    ParentFont = False
  end
  object TotalLabel: TWinLabel
    Left = 464
    Top = 422
    Width = 109
    Height = 20
    BorderDraw = True
    Layout = tlCenter
    Pen.Color = clGray
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -12
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = #21512#35336#37329#38989
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    ParentFont = False
  end
  object CompanyNameLabel: TWinLabel
    Left = 450
    Top = 73
    Width = 185
    Height = 12
    Alignment = taRightJustify
    Layout = tlCenter
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -9
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = 'CompanyNameLabel'
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    ParentFont = False
  end
  object PersonLabel: TWinLabel
    Left = 450
    Top = 84
    Width = 185
    Height = 12
    Alignment = taRightJustify
    Layout = tlCenter
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -9
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = 'PersonLabel'
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    ParentFont = False
  end
  object ZipCodeLabel: TWinLabel
    Left = 450
    Top = 95
    Width = 185
    Height = 12
    Alignment = taRightJustify
    Layout = tlCenter
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -9
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = 'ZipCodeLabel'
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    ParentFont = False
  end
  object AddressLabel1: TWinLabel
    Left = 450
    Top = 106
    Width = 185
    Height = 12
    Alignment = taRightJustify
    Layout = tlCenter
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -9
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = 'AddressLabel1'
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    ParentFont = False
  end
  object AddressLabel2: TWinLabel
    Left = 450
    Top = 117
    Width = 185
    Height = 12
    Alignment = taRightJustify
    Layout = tlCenter
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -9
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = 'AddressLabel2'
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    ParentFont = False
  end
  object TELLabel: TWinLabel
    Left = 450
    Top = 128
    Width = 185
    Height = 12
    Alignment = taRightJustify
    Layout = tlCenter
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -9
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = 'TELLabel'
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    ParentFont = False
  end
  object FAXLabel: TWinLabel
    Left = 450
    Top = 139
    Width = 185
    Height = 12
    Alignment = taRightJustify
    Layout = tlCenter
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -9
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = 'FAXLabel'
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    ParentFont = False
  end
  object NumberLabel: TWinLabel
    Left = 469
    Top = 55
    Width = 17
    Height = 12
    Layout = tlCenter
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -9
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = 'No.'
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    ParentFont = False
  end
  object UnitLabel: TWinLabel
    Left = 604
    Top = 157
    Width = 35
    Height = 12
    Layout = tlCenter
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -9
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = #21336#20301':'#20870
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    ParentFont = False
  end
  object YearLabel: TWinLabel
    Left = 456
    Top = 33
    Width = 16
    Height = 12
    Layout = tlCenter
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -9
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = #24180
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    ParentFont = False
  end
  object MonthLabel: TWinLabel
    Left = 493
    Top = 33
    Width = 16
    Height = 12
    Layout = tlCenter
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -9
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = #26376
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    ParentFont = False
  end
  object DayLabel: TWinLabel
    Left = 529
    Top = 33
    Width = 16
    Height = 12
    Layout = tlCenter
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -9
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = #26085
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    ParentFont = False
  end
  object BillLabel: TWinLabel
    Left = 34
    Top = 14
    Width = 223
    Height = 29
    Layout = tlCenter
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -29
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = #35531' '#27714' '#26360
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    ParentFont = False
  end
  object RequestLabel: TWinLabel
    Left = 30
    Top = 79
    Width = 185
    Height = 12
    Layout = tlCenter
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -9
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = #19979#35352#12398#36890#12426#12372#35531#27714#30003#12375#19978#12370#12414#12377
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    ParentFont = False
  end
  object TitleLabel: TWinLabel
    Left = 32
    Top = 106
    Width = 47
    Height = 19
    Layout = tlCenter
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -13
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = #24481#20214#21517
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    ParentFont = False
  end
  object ChargedAmountLabel: TWinLabel
    Left = 32
    Top = 143
    Width = 81
    Height = 20
    Layout = tlCenter
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -15
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = #12372#35531#27714#37329#38989
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    ParentFont = False
  end
  object NoteLabel: TWinLabel
    Left = 32
    Top = 398
    Width = 369
    Height = 9
    Layout = tlCenter
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -9
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = #20633#32771':'
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    ParentFont = False
  end
  object TransferLabel1: TWinLabel
    Left = 32
    Top = 418
    Width = 320
    Height = 11
    Layout = tlCenter
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -11
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = 'TransferLabel1'
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    ParentFont = False
  end
  object TransferLabel2: TWinLabel
    Left = 32
    Top = 431
    Width = 320
    Height = 11
    Layout = tlCenter
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -11
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = 'TransferLabel2'
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    ParentFont = False
  end
  object Grid: XnsGrid
    Left = 32
    Top = 169
    Width = 608
    Height = 216
    BorderStyle = bsNone
    Color = clWhite
    ColCount = 6
    DefaultRowHeight = 18
    FixedCols = 0
    RowCount = 12
    Options = [goRowSizing, goColSizing, goEditing]
    ScrollBars = ssNone
    TabOrder = 29
    CanEdit = True
    CustomFont1.Charset = SHIFTJIS_CHARSET
    CustomFont1.Color = clWindowText
    CustomFont1.Height = -12
    CustomFont1.Name = #65325#65331' '#65328#12468#12471#12483#12463
    CustomFont1.Style = []
    CustomFont2.Charset = SHIFTJIS_CHARSET
    CustomFont2.Color = clWindowText
    CustomFont2.Height = -12
    CustomFont2.Name = #65325#65331' '#65328#12468#12471#12483#12463
    CustomFont2.Style = []
    CustomFont3.Charset = SHIFTJIS_CHARSET
    CustomFont3.Color = clWindowText
    CustomFont3.Height = -12
    CustomFont3.Name = #65325#65331' '#65328#12468#12471#12483#12463
    CustomFont3.Style = []
    CustomFont4.Charset = SHIFTJIS_CHARSET
    CustomFont4.Color = clWindowText
    CustomFont4.Height = -12
    CustomFont4.Name = #65325#65331' '#65328#12468#12471#12483#12463
    CustomFont4.Style = []
    ActiveCellColor = clWhite
    SelectCellColor = clBlue
    EditBackColor = clWhite
    CellBorderColor = clGray
    ColWidths = (
      40
      352
      40
      43
      65
      68)
  end
  object SubtotalEdit: TBorderEdit
    Left = 572
    Top = 384
    Width = 68
    Height = 20
    ImeMode = imDontCare
    BorderDraw = True
    Alignment = taRightJustify
    ColSeparateNum = 7
    ColPen.Color = clGray
    ColPen.Style = psDot
    Pen.Color = clGray
    NoCaptionPen.Color = clMoneyGreen
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = DEFAULT_CHARSET
    NoCaptionFont.Color = clMoneyGreen
    NoCaptionFont.Height = -11
    NoCaptionFont.Name = 'Tahoma'
    NoCaptionFont.Style = []
    TabOrder = 30
    TabStop = True
  end
  object TaxEdit: TBorderEdit
    Left = 572
    Top = 403
    Width = 68
    Height = 20
    ImeMode = imDontCare
    BorderDraw = True
    Alignment = taRightJustify
    ColSeparateNum = 7
    ColPen.Color = clGray
    ColPen.Style = psDot
    Pen.Color = clGray
    NoCaptionPen.Color = clMoneyGreen
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = DEFAULT_CHARSET
    NoCaptionFont.Color = clMoneyGreen
    NoCaptionFont.Height = -11
    NoCaptionFont.Name = 'Tahoma'
    NoCaptionFont.Style = []
    TabOrder = 31
    TabStop = True
  end
  object TotalEdit: TBorderEdit
    Left = 572
    Top = 422
    Width = 68
    Height = 20
    ImeMode = imDontCare
    BorderDraw = True
    Alignment = taRightJustify
    ColSeparateNum = 7
    ColPen.Color = clGray
    ColPen.Style = psDot
    Pen.Color = clGray
    NoCaptionPen.Color = clMoneyGreen
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = DEFAULT_CHARSET
    NoCaptionFont.Color = clMoneyGreen
    NoCaptionFont.Height = -11
    NoCaptionFont.Name = 'Tahoma'
    NoCaptionFont.Style = []
    TabOrder = 32
    TabStop = True
  end
  object NoEdit: TBorderEdit
    Left = 487
    Top = 52
    Width = 141
    Height = 13
    ImeMode = imDontCare
    Alignment = taRightJustify
    ColSeparateNum = 7
    NoCaptionPen.Color = clMoneyGreen
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = DEFAULT_CHARSET
    NoCaptionFont.Color = clMoneyGreen
    NoCaptionFont.Height = -11
    NoCaptionFont.Name = 'Tahoma'
    NoCaptionFont.Style = []
    TabOrder = 33
    TabStop = True
  end
  object ItemEdit: TBorderEdit
    Left = 84
    Top = 108
    Width = 265
    Height = 15
    ImeMode = imDontCare
    Alignment = taRightJustify
    ColSeparateNum = 7
    NoCaptionPen.Color = clMoneyGreen
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = DEFAULT_CHARSET
    NoCaptionFont.Color = clMoneyGreen
    NoCaptionFont.Height = -11
    NoCaptionFont.Name = 'Tahoma'
    NoCaptionFont.Style = []
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    TabOrder = 34
    TabStop = True
    ParentFont = False
  end
  object MoneyEdit: TBorderEdit
    Left = 124
    Top = 136
    Width = 205
    Height = 27
    ImeMode = imDontCare
    Alignment = taRightJustify
    ColSeparateNum = 7
    NoCaptionPen.Color = clMoneyGreen
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = DEFAULT_CHARSET
    NoCaptionFont.Color = clMoneyGreen
    NoCaptionFont.Height = -11
    NoCaptionFont.Name = 'Tahoma'
    NoCaptionFont.Style = []
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = [fsBold]
    TabOrder = 35
    TabStop = True
    ParentFont = False
  end
  object NameEdit: TBorderEdit
    Left = 32
    Top = 59
    Width = 197
    Height = 14
    ImeMode = imDontCare
    Alignment = taRightJustify
    ColSeparateNum = 7
    NoCaptionPen.Color = clMoneyGreen
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = DEFAULT_CHARSET
    NoCaptionFont.Color = clMoneyGreen
    NoCaptionFont.Height = -11
    NoCaptionFont.Name = 'Tahoma'
    NoCaptionFont.Style = []
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    TabOrder = 36
    TabStop = True
    ParentFont = False
  end
  object YearEdit: TBorderEdit
    Left = 424
    Top = 34
    Width = 29
    Height = 11
    Text = '2008'
    ImeMode = imDontCare
    Alignment = taRightJustify
    ColSeparateNum = 7
    NoCaptionPen.Color = clMoneyGreen
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = DEFAULT_CHARSET
    NoCaptionFont.Color = clMoneyGreen
    NoCaptionFont.Height = -11
    NoCaptionFont.Name = 'Tahoma'
    NoCaptionFont.Style = []
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    TabOrder = 37
    TabStop = True
    ParentFont = False
  end
  object MonthEdit: TBorderEdit
    Left = 476
    Top = 34
    Width = 17
    Height = 11
    Text = '12'
    ImeMode = imDontCare
    Alignment = taRightJustify
    ColSeparateNum = 7
    NoCaptionPen.Color = clMoneyGreen
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = DEFAULT_CHARSET
    NoCaptionFont.Color = clMoneyGreen
    NoCaptionFont.Height = -11
    NoCaptionFont.Name = 'Tahoma'
    NoCaptionFont.Style = []
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    TabOrder = 38
    TabStop = True
    ParentFont = False
  end
  object DayEdit: TBorderEdit
    Left = 508
    Top = 34
    Width = 18
    Height = 11
    Text = '12'
    ImeMode = imDontCare
    Alignment = taRightJustify
    ColSeparateNum = 7
    NoCaptionPen.Color = clMoneyGreen
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = DEFAULT_CHARSET
    NoCaptionFont.Color = clMoneyGreen
    NoCaptionFont.Height = -11
    NoCaptionFont.Name = 'Tahoma'
    NoCaptionFont.Style = []
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    TabOrder = 39
    TabStop = True
    ParentFont = False
  end
end
