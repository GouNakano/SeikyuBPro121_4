object SeikyuPrintForm: TSeikyuPrintForm
  Left = 659
  Top = 82
  Caption = #35531#27714#26360#21360#21047#12501#12457#12540#12512
  ClientHeight = 698
  ClientWidth = 743
  Color = clBtnFace
  Font.Charset = SHIFTJIS_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
  Font.Style = []
  Scaled = False
  TextHeight = 12
  object SeikyuRep: TQuickRep
    Left = 14
    Top = 6
    Width = 475
    Height = 675
    ShowingPreview = False
    BeforePrint = SeikyuRepBeforePrint
    Functions.Strings = (
      'PAGENUMBER'
      'COLUMNNUMBER'
      'REPORTTITLE')
    Functions.DATA = (
      '0'
      '0'
      #39#39)
    OnEndPage = SeikyuRepEndPage
    OnNeedData = SeikyuRepNeedData
    OnStartPage = SeikyuRepStartPage
    Options = [FirstPageHeader]
    Page.Columns = 1
    Page.Orientation = poPortrait
    Page.PaperSize = A5
    Page.Continuous = False
    Page.Values = (
      0.000000000000000000
      2100.000000000000000000
      0.000000000000000000
      1480.000000000000000000
      0.000000000000000000
      0.000000000000000000
      0.000000000000000000)
    PrinterSettings.Copies = 1
    PrinterSettings.OutputBin = Auto
    PrinterSettings.Duplex = False
    PrinterSettings.FirstPage = 0
    PrinterSettings.LastPage = 0
    PrinterSettings.UseStandardprinter = False
    PrinterSettings.UseCustomBinCode = False
    PrinterSettings.CustomBinCode = 0
    PrinterSettings.ExtendedDuplex = 0
    PrinterSettings.UseCustomPaperCode = False
    PrinterSettings.CustomPaperCode = 0
    PrinterSettings.PrintMetaFile = False
    PrinterSettings.MemoryLimit = 1000000
    PrinterSettings.PrintQuality = 0
    PrinterSettings.Collate = 0
    PrinterSettings.ColorOption = 0
    PrintIfEmpty = True
    ReportTitle = #35531#27714#26360#30058#38957' '#12503#12525#29256
    SnapToGrid = True
    Units = MM
    Zoom = 85
    PrevFormStyle = fsNormal
    PreviewInitialState = wsNormal
    PreviewWidth = 500
    PreviewHeight = 500
    PrevInitialZoom = qrZoomToFit
    PreviewDefaultSaveType = stPDF
    PreviewLeft = 0
    PreviewTop = 0
    object PrintBand: TQRBand
      Left = 0
      Top = 0
      Width = 475
      Height = 1351
      AlignToBottom = False
      TransparentBand = False
      ForceNewColumn = False
      ForceNewPage = False
      Size.Values = (
        4205.318627450980000000
        1478.553921568627000000)
      PreCaluculateBandHeight = False
      KeepOnOnePage = False
      BandType = rbTitle
    end
  end
end
