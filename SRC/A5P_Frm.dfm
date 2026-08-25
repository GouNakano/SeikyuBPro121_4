object A5P_Form: TA5P_Form
  Tag = 85
  Left = 580
  Top = 13
  Caption = 'A5P'
  ClientHeight = 710
  ClientWidth = 476
  Color = clWhite
  Font.Charset = SHIFTJIS_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
  Font.Style = []
  TextHeight = 12
  object StampImage1: TImage
    Left = 373
    Top = 169
    Width = 41
    Height = 46
  end
  object StampImage2: TImage
    Left = 412
    Top = 169
    Width = 41
    Height = 46
  end
  object LogoImage: TImage
    Left = 385
    Top = 617
    Width = 70
    Height = 35
    Center = True
  end
  object DayUnderShape: TWinShape
    Left = 24
    Top = 42
    Width = 427
    Height = 1
    Shape = wsHorLine
  end
  object NameUnderShape: TWinShape
    Left = 24
    Top = 82
    Width = 229
    Height = 2
    Shape = wsHorLine
  end
  object ItemShape: TWinShape
    Left = 24
    Top = 166
    Width = 327
    Height = 2
    Shape = wsHorLine
  end
  object NumberShape: TWinShape
    Left = 281
    Top = 65
    Width = 170
    Height = 4
    Shape = wsHorLine
  end
  object MoneyShape: TWinShape
    Left = 23
    Top = 215
    Width = 301
    Height = 2
    Shape = wsHorLine
  end
  object NoteShape: TWinShape
    Left = 24
    Top = 613
    Width = 431
    Height = 2
    Shape = wsHorLine
  end
  object SubTotalLabel: TBorderEdit
    Left = 250
    Top = 529
    Width = 133
    Height = 20
    ImeMode = imDontCare
    BorderDraw = True
    Alignment = taLeftJustify
    ColSeparateNum = 7
    NoCaptionPen.Color = clMoneyGreen
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = DEFAULT_CHARSET
    NoCaptionFont.Color = clMoneyGreen
    NoCaptionFont.Height = -11
    NoCaptionFont.Name = 'Tahoma'
    NoCaptionFont.Style = []
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -12
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    TabOrder = 6
    TabStop = True
    ParentFont = False
  end
  object TaxLabel: TBorderEdit
    Left = 250
    Top = 548
    Width = 133
    Height = 20
    ImeMode = imDontCare
    BorderDraw = True
    Alignment = taLeftJustify
    ColSeparateNum = 7
    NoCaptionPen.Color = clMoneyGreen
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = DEFAULT_CHARSET
    NoCaptionFont.Color = clMoneyGreen
    NoCaptionFont.Height = -11
    NoCaptionFont.Name = 'Tahoma'
    NoCaptionFont.Style = []
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -12
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    TabOrder = 7
    TabStop = True
    ParentFont = False
  end
  object TotalLabel: TBorderEdit
    Left = 250
    Top = 567
    Width = 133
    Height = 20
    ImeMode = imDontCare
    BorderDraw = True
    Alignment = taLeftJustify
    ColSeparateNum = 7
    NoCaptionPen.Color = clMoneyGreen
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = DEFAULT_CHARSET
    NoCaptionFont.Color = clMoneyGreen
    NoCaptionFont.Height = -11
    NoCaptionFont.Name = 'Tahoma'
    NoCaptionFont.Style = []
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -12
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    TabOrder = 8
    TabStop = True
    ParentFont = False
  end
  object BillLabel: TWinLabel
    Left = 25
    Top = 15
    Width = 289
    Height = 24
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -24
    Font.Name = #65325#65331' '#12468#12471#12483#12463
    Font.Style = []
    Caption = #35531' '#27714' '#26360
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    Color = 16121836
    ParentColor = False
    ParentFont = False
  end
  object YearLabel: TWinLabel
    Left = 365
    Top = 28
    Width = 15
    Height = 11
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
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
    Color = 16121836
    ParentColor = False
    ParentFont = False
  end
  object MonthLabel: TWinLabel
    Left = 398
    Top = 28
    Width = 15
    Height = 11
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
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
    Color = 16121836
    ParentColor = False
    ParentFont = False
  end
  object DayLabel: TWinLabel
    Left = 434
    Top = 28
    Width = 15
    Height = 11
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
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
    Color = 16121836
    ParentColor = False
    ParentFont = False
  end
  object HonorificTitleLabel: TWinLabel
    Left = 226
    Top = 66
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
  object TitleLabel: TWinLabel
    Left = 24
    Top = 152
    Width = 39
    Height = 13
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
    Color = 16121836
    ParentColor = False
    ParentFont = False
  end
  object RequestLabel: TWinLabel
    Left = 26
    Top = 86
    Width = 145
    Height = 9
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
    Color = 16121836
    ParentColor = False
    ParentFont = False
  end
  object NumberLabel: TWinLabel
    Left = 281
    Top = 53
    Width = 17
    Height = 11
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -11
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
  object CompanyNameLabel: TWinLabel
    Left = 270
    Top = 76
    Width = 185
    Height = 13
    Alignment = taRightJustify
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -11
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = #12373#12367#12425#38651#31639
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    Color = 16121836
    ParentColor = False
    ParentFont = False
  end
  object PersonLabel: TWinLabel
    Left = 270
    Top = 91
    Width = 185
    Height = 11
    Alignment = taRightJustify
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -11
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = #20195#34920#32773#12288#20013#37326#12288#21083
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    Color = 16121836
    ParentColor = False
    ParentFont = False
  end
  object ZipCodeLabel: TWinLabel
    Left = 270
    Top = 103
    Width = 185
    Height = 11
    Alignment = taRightJustify
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -11
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = #12306' 350-0023'
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    Color = 16121836
    ParentColor = False
    ParentFont = False
  end
  object AddressLabel1: TWinLabel
    Left = 270
    Top = 115
    Width = 185
    Height = 11
    Alignment = taRightJustify
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -11
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = #22524#29577#30476#24029#36234#24066#20006#26408' 855-1'
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    Color = 16121836
    ParentColor = False
    ParentFont = False
  end
  object AddressLabel2: TWinLabel
    Left = 270
    Top = 127
    Width = 185
    Height = 11
    Alignment = taRightJustify
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -11
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = #12467#12540#12509#21335' 103'
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    Color = 16121836
    ParentColor = False
    ParentFont = False
  end
  object TELLabel: TWinLabel
    Left = 354
    Top = 139
    Width = 101
    Height = 11
    Alignment = taRightJustify
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -11
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = 'TEL 049-236-1638'
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    Color = 16121836
    ParentColor = False
    ParentFont = False
  end
  object FAXLabel: TWinLabel
    Left = 354
    Top = 151
    Width = 101
    Height = 11
    Alignment = taRightJustify
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -11
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = 'FAX 049-236-1638'
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    Color = 16121836
    ParentColor = False
    ParentFont = False
  end
  object ChargedAmountLabel: TWinLabel
    Left = 24
    Top = 198
    Width = 84
    Height = 15
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
    Color = 16121836
    ParentColor = False
    ParentFont = False
  end
  object UnitLabel: TWinLabel
    Left = 421
    Top = 219
    Width = 32
    Height = 9
    Alignment = taRightJustify
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
    Color = 16121836
    ParentColor = False
    ParentFont = False
  end
  object TransferLabel1: TWinLabel
    Left = 24
    Top = 623
    Width = 320
    Height = 11
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -11
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = #25391#36796#20808#65306' '#12415#12378#12411#37504#34892' '#28171#35895#25903#24215' '#26222#36890#12288'8189386  '#12490#12459#12494#12288#12468#12454' '
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    Color = 16121836
    ParentColor = False
    ParentFont = False
  end
  object TransferLabel2: TWinLabel
    Left = 24
    Top = 637
    Width = 320
    Height = 10
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -11
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = #25391#36796#20808#65306' '#37109#20415#25391#36796' 10330-9493581'#12288#21517#32681#20154#65306#20013#37326#12288#21083
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    Color = 16121836
    ParentColor = False
    ParentFont = False
  end
  object NoteLabel: TWinLabel
    Left = 24
    Top = 600
    Width = 430
    Height = 9
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clGray
    Font.Height = -9
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    Caption = #20633#32771#65306
    NoCaptionPen.Color = clSilver
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = SHIFTJIS_CHARSET
    NoCaptionFont.Color = clSilver
    NoCaptionFont.Height = -12
    NoCaptionFont.Name = #65325#65331' '#65328#12468#12471#12483#12463
    NoCaptionFont.Style = []
    Color = 16121836
    ParentColor = False
    ParentFont = False
  end
  object Grid: XnsGrid
    Left = 24
    Top = 230
    Width = 431
    Height = 300
    BorderStyle = bsNone
    Color = clWhite
    ColCount = 6
    DefaultRowHeight = 20
    FixedCols = 0
    RowCount = 15
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
    ColWidths = (
      34
      192
      40
      32
      60
      73)
  end
  object YearEdit: TBorderEdit
    Left = 337
    Top = 28
    Width = 29
    Height = 11
    Text = '2008'
    ImeMode = imDontCare
    Alignment = taLeftJustify
    ColSeparateNum = 7
    NoCaptionPen.Color = clMoneyGreen
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = DEFAULT_CHARSET
    NoCaptionFont.Color = clMoneyGreen
    NoCaptionFont.Height = -11
    NoCaptionFont.Name = 'Tahoma'
    NoCaptionFont.Style = []
    Color = 14540253
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    TabOrder = 30
    TabStop = True
    ParentColor = False
    ParentFont = False
  end
  object MonthEdit: TBorderEdit
    Left = 381
    Top = 28
    Width = 18
    Height = 11
    Text = '10'
    ImeMode = imDontCare
    Alignment = taLeftJustify
    ColSeparateNum = 7
    NoCaptionPen.Color = clMoneyGreen
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = DEFAULT_CHARSET
    NoCaptionFont.Color = clMoneyGreen
    NoCaptionFont.Height = -11
    NoCaptionFont.Name = 'Tahoma'
    NoCaptionFont.Style = []
    Color = 14540253
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    TabOrder = 31
    TabStop = True
    ParentColor = False
    ParentFont = False
  end
  object DayEdit: TBorderEdit
    Left = 416
    Top = 28
    Width = 18
    Height = 11
    Text = '12'
    ImeMode = imDontCare
    Alignment = taLeftJustify
    ColSeparateNum = 7
    NoCaptionPen.Color = clMoneyGreen
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = DEFAULT_CHARSET
    NoCaptionFont.Color = clMoneyGreen
    NoCaptionFont.Height = -11
    NoCaptionFont.Name = 'Tahoma'
    NoCaptionFont.Style = []
    Color = 14540253
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    TabOrder = 32
    TabStop = True
    ParentColor = False
    ParentFont = False
  end
  object NameEdit: TBorderEdit
    Left = 25
    Top = 66
    Width = 197
    Height = 14
    ImeMode = imDontCare
    Alignment = taLeftJustify
    ColSeparateNum = 7
    NoCaptionPen.Color = clMoneyGreen
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = DEFAULT_CHARSET
    NoCaptionFont.Color = clMoneyGreen
    NoCaptionFont.Height = -11
    NoCaptionFont.Name = 'Tahoma'
    NoCaptionFont.Style = []
    Color = 14540253
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = [fsBold]
    TabOrder = 33
    TabStop = True
    ParentColor = False
    ParentFont = False
  end
  object ItemEdit: TBorderEdit
    Left = 66
    Top = 149
    Width = 285
    Height = 15
    ImeMode = imDontCare
    Alignment = taLeftJustify
    ColSeparateNum = 7
    NoCaptionPen.Color = clMoneyGreen
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = DEFAULT_CHARSET
    NoCaptionFont.Color = clMoneyGreen
    NoCaptionFont.Height = -11
    NoCaptionFont.Name = 'Tahoma'
    NoCaptionFont.Style = []
    Color = 14540253
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = []
    TabOrder = 34
    TabStop = True
    ParentColor = False
    ParentFont = False
  end
  object NoEdit: TBorderEdit
    Left = 303
    Top = 51
    Width = 147
    Height = 12
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
    Color = 14540253
    TabOrder = 35
    TabStop = True
    ParentColor = False
  end
  object MoneyEdit: TBorderEdit
    Left = 113
    Top = 189
    Width = 204
    Height = 24
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
    Color = 14540253
    Font.Charset = SHIFTJIS_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
    Font.Style = [fsBold]
    TabOrder = 36
    TabStop = True
    ParentColor = False
    ParentFont = False
  end
  object SubtotalEdit: TBorderEdit
    Left = 382
    Top = 529
    Width = 73
    Height = 20
    ImeMode = imDontCare
    BorderDraw = True
    Alignment = taRightJustify
    ColSeparateNum = 7
    ColPen.Color = clGray
    ColPen.Style = psDot
    NoCaptionPen.Color = clMoneyGreen
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = DEFAULT_CHARSET
    NoCaptionFont.Color = clMoneyGreen
    NoCaptionFont.Height = -11
    NoCaptionFont.Name = 'Tahoma'
    NoCaptionFont.Style = []
    TabOrder = 37
    TabStop = True
  end
  object TaxEdit: TBorderEdit
    Left = 382
    Top = 548
    Width = 73
    Height = 20
    ImeMode = imDontCare
    BorderDraw = True
    Alignment = taRightJustify
    ColSeparateNum = 7
    ColPen.Color = clGray
    ColPen.Style = psDot
    NoCaptionPen.Color = clMoneyGreen
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = DEFAULT_CHARSET
    NoCaptionFont.Color = clMoneyGreen
    NoCaptionFont.Height = -11
    NoCaptionFont.Name = 'Tahoma'
    NoCaptionFont.Style = []
    TabOrder = 38
    TabStop = True
  end
  object TotalEdit: TBorderEdit
    Left = 382
    Top = 567
    Width = 73
    Height = 20
    ImeMode = imDontCare
    BorderDraw = True
    Alignment = taRightJustify
    ColSeparateNum = 7
    ColPen.Color = clGray
    ColPen.Style = psDot
    NoCaptionPen.Color = clMoneyGreen
    NoCaptionPen.Style = psDot
    NoCaptionFont.Charset = DEFAULT_CHARSET
    NoCaptionFont.Color = clMoneyGreen
    NoCaptionFont.Height = -11
    NoCaptionFont.Name = 'Tahoma'
    NoCaptionFont.Style = []
    TabOrder = 39
    TabStop = True
  end
end
