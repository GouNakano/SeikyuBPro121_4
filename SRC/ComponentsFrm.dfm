object ComponentsForm: TComponentsForm
  Left = 402
  Top = 171
  Caption = #37096#21697#19968#35239#34920
  ClientHeight = 440
  ClientWidth = 739
  Color = clWhite
  Font.Charset = SHIFTJIS_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
  Font.Style = []
  Position = poMainFormCenter
  StyleName = 'Windows'
  OnShow = FormShow
  TextHeight = 12
  object Panel1: TPanel
    Left = 0
    Top = 404
    Width = 739
    Height = 36
    Align = alBottom
    Color = clWhite
    ParentBackground = False
    TabOrder = 0
    object Panel2: TPanel
      Left = 492
      Top = 1
      Width = 246
      Height = 34
      Align = alRight
      TabOrder = 0
      object CloseBtn: TBitBtn2
        Left = 168
        Top = 4
        Width = 75
        Height = 25
        Caption = #38281#12376#12427
        DoubleBuffered = True
        DoubleBufferedMode = dbmRequested
        ParentDoubleBuffered = False
        TabOrder = 0
        OnClick = CloseBtnClick
        DownColor = clBtnFace
      end
      object FormatBtn: TBitBtn2
        Left = 44
        Top = 4
        Width = 118
        Height = 25
        Caption = #26360#24335#35373#23450
        Default = True
        DoubleBuffered = True
        DoubleBufferedMode = dbmRequested
        ParentDoubleBuffered = False
        TabOrder = 1
        OnClick = FormatBtnClick
        DownColor = clBtnFace
      end
    end
  end
  object ListView: TListView
    Left = 0
    Top = 0
    Width = 739
    Height = 404
    Align = alClient
    Columns = <
      item
        Caption = #21517#31216
        Width = 200
      end
      item
        Caption = #34920#31034
      end
      item
        Caption = #21360#21047
      end
      item
        Caption = #27700#24179#20301#32622
        Width = 65
      end
      item
        Caption = #22402#30452#20301#32622
        Width = 60
      end
      item
        Caption = #24133
      end
      item
        Caption = #39640#12373
      end
      item
        Caption = #20869#23481
        Width = 200
      end>
    ColumnClick = False
    RowSelect = True
    TabOrder = 1
    ViewStyle = vsReport
    OnDeletion = ListViewDeletion
  end
end
