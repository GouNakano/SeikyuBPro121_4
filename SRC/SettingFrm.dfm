object SettingForm: TSettingForm
  Left = 573
  Top = 190
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #12458#12503#12471#12519#12531
  ClientHeight = 413
  ClientWidth = 360
  Color = clBtnFace
  Font.Charset = SHIFTJIS_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
  Font.Style = []
  Position = poMainFormCenter
  OnShow = FormShow
  TextHeight = 12
  object OkBtn: TButton
    Left = 196
    Top = 384
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    TabOrder = 0
    OnClick = OkBtnClick
  end
  object CancelBtn: TButton
    Left = 280
    Top = 384
    Width = 75
    Height = 25
    Cancel = True
    Caption = #12461#12515#12531#12475#12523
    TabOrder = 1
    OnClick = CancelBtnClick
  end
  object PageControl: TPageControl
    Left = 4
    Top = 4
    Width = 353
    Height = 377
    ActivePage = TabSheet2
    TabOrder = 2
    object GeneralTabSheet: TTabSheet
      Caption = #19968#33324
      object BackupFileCBox: TCheckBox
        Left = 4
        Top = 28
        Width = 233
        Height = 17
        Caption = #12496#12483#12463#12450#12483#12503#12501#12449#12452#12523#12398#20316#25104
        TabOrder = 0
      end
      object RemainCBox: TCheckBox
        Left = 4
        Top = 8
        Width = 233
        Height = 17
        Caption = #21069#22238#32066#20102#26178#12398#29366#24907#12434#20877#29694#12377#12427
        TabOrder = 1
      end
      object GroupBox1: TGroupBox
        Left = 4
        Top = 60
        Width = 310
        Height = 93
        Caption = ' '#26032#35215#20316#25104#12398#35373#23450' '
        TabOrder = 2
        object UseTemplateCBox: TCheckBox
          Left = 4
          Top = 20
          Width = 201
          Height = 17
          Caption = #12486#12531#12503#12524#12540#12488#12501#12449#12452#12523#12434#20351#29992#12377#12427
          TabOrder = 0
          OnClick = UseTemplateCBoxClick
        end
        object TemplateFileEdit: TEdit
          Left = 4
          Top = 40
          Width = 273
          Height = 20
          MaxLength = 255
          TabOrder = 1
        end
        object FIB_01: TBitBtn
          Left = 276
          Top = 39
          Width = 25
          Height = 22
          Hint = #65420#65383#65394#65433#21442#29031
          Glyph.Data = {
            36030000424D3603000000000000360000002800000010000000100000000100
            1800000000000003000000000000000000000000000000000000C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C00000000000000000000000000000000000000000000000000000000000
            00000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000FFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            FF000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000FFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0000000FFFFFF808080808080808080808080808080808080808080FFFF
            FF000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000FFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0000000FFFFFF808080808080808080808080808080FFFFFFFFFFFFFFFF
            FF000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000FFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0000000FFFFFF808080808080808080808080808080FFFFFFFFFFFFFFFF
            FF000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000FFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0000000FFFFFF808080808080808080808080808080808080808080FFFF
            FF000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0000000FFFFFFFFFFFFFFFFFFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C00000000000000000000000000000000000000000000000000000000000
            00000000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
            C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0}
          ParentShowHint = False
          ShowHint = True
          TabOrder = 2
          TabStop = False
          OnClick = FIB_01Click
        end
        object TodayCBox: TCheckBox
          Left = 4
          Top = 68
          Width = 185
          Height = 17
          Caption = #26412#26085#12398#26085#20184#12434#12475#12483#12488#12377#12427
          TabOrder = 3
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = #23567#25968#28857#38306#36899#35373#23450
      ImageIndex = 1
      object StockingTaxGBox: TGroupBox
        Left = 0
        Top = 8
        Width = 341
        Height = 61
        Caption = ' '#12300#25968#37327#12301#12398#23567#25968#28857#12398#35373#23450' '
        Font.Charset = SHIFTJIS_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        object Label2: TLabel
          Left = 8
          Top = 40
          Width = 96
          Height = 12
          Caption = #26377#21177#26689#20197#19979#12398#20966#29702
          Font.Charset = SHIFTJIS_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
          Font.Style = []
          ParentFont = False
        end
        object Label10: TLabel
          Left = 8
          Top = 20
          Width = 96
          Height = 12
          Caption = #23567#25968#28857#20197#19979#12398#26689#25968
        end
        object Label11: TLabel
          Left = 144
          Top = 20
          Width = 32
          Height = 12
          Caption = '(0'#65374'2)'
        end
        object RB00: TRadioButton
          Left = 112
          Top = 38
          Width = 69
          Height = 17
          Caption = #20999#25448#12390
          Font.Charset = SHIFTJIS_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
          Font.Style = []
          ParentFont = False
          TabOrder = 1
        end
        object RB01: TRadioButton
          Left = 172
          Top = 38
          Width = 73
          Height = 17
          Caption = #20999#12426#19978#12370
          Font.Charset = SHIFTJIS_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
          Font.Style = []
          ParentFont = False
          TabOrder = 2
        end
        object RB02: TRadioButton
          Left = 244
          Top = 38
          Width = 73
          Height = 17
          Caption = #22235#25448#20116#20837
          Font.Charset = SHIFTJIS_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
          Font.Style = []
          ParentFont = False
          TabOrder = 3
        end
        object Ratio00Edit: TEdit
          Left = 112
          Top = 16
          Width = 25
          Height = 20
          ImeMode = imDisable
          MaxLength = 1
          TabOrder = 0
        end
      end
      object GroupBox2: TGroupBox
        Left = 0
        Top = 144
        Width = 341
        Height = 61
        Caption = ' '#12300#37329#38989#12301#12392#12300#23567#35336#12301#12398#23567#25968#28857#12398#35373#23450' '
        Font.Charset = SHIFTJIS_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        object Label1: TLabel
          Left = 8
          Top = 40
          Width = 96
          Height = 12
          Caption = #26377#21177#26689#20197#19979#12398#20966#29702
          Font.Charset = SHIFTJIS_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
          Font.Style = []
          ParentFont = False
        end
        object Label3: TLabel
          Left = 8
          Top = 20
          Width = 96
          Height = 12
          Caption = #23567#25968#28857#20197#19979#12398#26689#25968
        end
        object Label4: TLabel
          Left = 144
          Top = 20
          Width = 32
          Height = 12
          Caption = '(0'#65374'2)'
        end
        object RB20: TRadioButton
          Left = 112
          Top = 38
          Width = 69
          Height = 17
          Caption = #20999#25448#12390
          Font.Charset = SHIFTJIS_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
          Font.Style = []
          ParentFont = False
          TabOrder = 1
          TabStop = True
        end
        object RB21: TRadioButton
          Left = 172
          Top = 38
          Width = 73
          Height = 17
          Caption = #20999#12426#19978#12370
          Font.Charset = SHIFTJIS_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
          Font.Style = []
          ParentFont = False
          TabOrder = 2
          TabStop = True
        end
        object RB22: TRadioButton
          Left = 244
          Top = 38
          Width = 73
          Height = 17
          Caption = #22235#25448#20116#20837
          Font.Charset = SHIFTJIS_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
          Font.Style = []
          ParentFont = False
          TabOrder = 3
          TabStop = True
        end
        object Ratio02Edit: TEdit
          Left = 112
          Top = 16
          Width = 25
          Height = 20
          ImeMode = imDisable
          MaxLength = 1
          TabOrder = 0
        end
      end
      object GroupBox3: TGroupBox
        Left = 0
        Top = 76
        Width = 341
        Height = 61
        Caption = ' '#12300#21336#20385#12301#12398#23567#25968#28857#12398#35373#23450' '
        Font.Charset = SHIFTJIS_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        object Label5: TLabel
          Left = 8
          Top = 40
          Width = 96
          Height = 12
          Caption = #26377#21177#26689#20197#19979#12398#20966#29702
          Font.Charset = SHIFTJIS_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
          Font.Style = []
          ParentFont = False
        end
        object Label6: TLabel
          Left = 8
          Top = 20
          Width = 96
          Height = 12
          Caption = #23567#25968#28857#20197#19979#12398#26689#25968
        end
        object Label7: TLabel
          Left = 144
          Top = 20
          Width = 32
          Height = 12
          Caption = '(0'#65374'2)'
        end
        object RB10: TRadioButton
          Left = 112
          Top = 38
          Width = 69
          Height = 17
          Caption = #20999#25448#12390
          Font.Charset = SHIFTJIS_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
          Font.Style = []
          ParentFont = False
          TabOrder = 1
          TabStop = True
        end
        object RB11: TRadioButton
          Left = 172
          Top = 38
          Width = 73
          Height = 17
          Caption = #20999#12426#19978#12370
          Font.Charset = SHIFTJIS_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
          Font.Style = []
          ParentFont = False
          TabOrder = 2
          TabStop = True
        end
        object RB12: TRadioButton
          Left = 244
          Top = 38
          Width = 73
          Height = 17
          Caption = #22235#25448#20116#20837
          Font.Charset = SHIFTJIS_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
          Font.Style = []
          ParentFont = False
          TabOrder = 3
          TabStop = True
        end
        object Ratio01Edit: TEdit
          Left = 112
          Top = 16
          Width = 25
          Height = 20
          ImeMode = imDisable
          MaxLength = 1
          TabOrder = 0
        end
      end
      object GroupBox4: TGroupBox
        Left = 0
        Top = 212
        Width = 341
        Height = 61
        Caption = ' '#12300#28040#36027#31246#12301#12398#23567#25968#28857#12398#35373#23450' '
        Font.Charset = SHIFTJIS_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
        Font.Style = []
        ParentFont = False
        TabOrder = 3
        object Label8: TLabel
          Left = 8
          Top = 40
          Width = 96
          Height = 12
          Caption = #26377#21177#26689#20197#19979#12398#20966#29702
          Font.Charset = SHIFTJIS_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
          Font.Style = []
          ParentFont = False
        end
        object Label9: TLabel
          Left = 8
          Top = 20
          Width = 96
          Height = 12
          Caption = #23567#25968#28857#20197#19979#12398#26689#25968
        end
        object Label12: TLabel
          Left = 144
          Top = 20
          Width = 32
          Height = 12
          Caption = '(0'#65374'2)'
        end
        object RB30: TRadioButton
          Left = 112
          Top = 38
          Width = 69
          Height = 17
          Caption = #20999#25448#12390
          Font.Charset = SHIFTJIS_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
          Font.Style = []
          ParentFont = False
          TabOrder = 1
          TabStop = True
        end
        object RB31: TRadioButton
          Left = 172
          Top = 38
          Width = 73
          Height = 17
          Caption = #20999#12426#19978#12370
          Font.Charset = SHIFTJIS_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
          Font.Style = []
          ParentFont = False
          TabOrder = 2
          TabStop = True
        end
        object RB32: TRadioButton
          Left = 244
          Top = 38
          Width = 73
          Height = 17
          Caption = #22235#25448#20116#20837
          Font.Charset = SHIFTJIS_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
          Font.Style = []
          ParentFont = False
          TabOrder = 3
          TabStop = True
        end
        object Ratio03Edit: TEdit
          Left = 112
          Top = 16
          Width = 25
          Height = 20
          ImeMode = imDisable
          MaxLength = 1
          TabOrder = 0
        end
      end
      object GroupBox5: TGroupBox
        Left = 0
        Top = 280
        Width = 341
        Height = 61
        Caption = ' '#12300#21512#35336#37329#38989#12301#12398#23567#25968#28857#12398#35373#23450' '
        Font.Charset = SHIFTJIS_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
        Font.Style = []
        ParentFont = False
        TabOrder = 4
        object Label13: TLabel
          Left = 8
          Top = 40
          Width = 96
          Height = 12
          Caption = #26377#21177#26689#20197#19979#12398#20966#29702
          Font.Charset = SHIFTJIS_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
          Font.Style = []
          ParentFont = False
        end
        object Label14: TLabel
          Left = 8
          Top = 20
          Width = 96
          Height = 12
          Caption = #23567#25968#28857#20197#19979#12398#26689#25968
        end
        object Label15: TLabel
          Left = 144
          Top = 20
          Width = 32
          Height = 12
          Caption = '(0'#65374'2)'
        end
        object RB40: TRadioButton
          Left = 112
          Top = 38
          Width = 69
          Height = 17
          Caption = #20999#25448#12390
          Font.Charset = SHIFTJIS_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
          Font.Style = []
          ParentFont = False
          TabOrder = 1
          TabStop = True
        end
        object RB41: TRadioButton
          Left = 172
          Top = 38
          Width = 73
          Height = 17
          Caption = #20999#12426#19978#12370
          Font.Charset = SHIFTJIS_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
          Font.Style = []
          ParentFont = False
          TabOrder = 2
          TabStop = True
        end
        object RB42: TRadioButton
          Left = 244
          Top = 38
          Width = 73
          Height = 17
          Caption = #22235#25448#20116#20837
          Font.Charset = SHIFTJIS_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
          Font.Style = []
          ParentFont = False
          TabOrder = 3
          TabStop = True
        end
        object Ratio04Edit: TEdit
          Left = 112
          Top = 16
          Width = 25
          Height = 20
          ImeMode = imDisable
          MaxLength = 1
          TabOrder = 0
        end
      end
    end
  end
  object OpenDialog: TOpenDialog
    Filter = #35531#27714#26360#30058#38957' '#25991#26360#12501#12449#12452#12523'(*.sdo)|*.sdo'
    Left = 252
    Top = 20
  end
end
