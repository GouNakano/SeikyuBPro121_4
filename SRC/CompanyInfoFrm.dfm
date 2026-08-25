object CompanyInfoForm: TCompanyInfoForm
  Left = 165
  Top = 132
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #33258#31038#24773#22577
  ClientHeight = 321
  ClientWidth = 483
  Color = clWhite
  Font.Charset = SHIFTJIS_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
  Font.Style = []
  Position = poMainFormCenter
  StyleName = 'Windows'
  OnCreate = FormCreate
  OnShow = FormShow
  TextHeight = 12
  object CancelBtn: TBitBtn2
    Left = 400
    Top = 292
    Width = 75
    Height = 25
    Cancel = True
    Caption = #65399#65388#65437#65406#65433
    DoubleBuffered = True
    DoubleBufferedMode = dbmRequested
    ModalResult = 2
    ParentDoubleBuffered = False
    TabOrder = 1
    DownColor = clBtnFace
  end
  object ResistBtn: TBitBtn2
    Left = 320
    Top = 292
    Width = 75
    Height = 25
    Cancel = True
    Caption = #30331#37682
    Default = True
    DoubleBuffered = True
    DoubleBufferedMode = dbmRequested
    ModalResult = 1
    ParentDoubleBuffered = False
    TabOrder = 0
    OnClick = ResistBtnClick
    DownColor = clBtnFace
  end
  object CPageCtrl: TPageControl
    Left = 6
    Top = 5
    Width = 469
    Height = 281
    ActivePage = C2
    OwnerDraw = True
    TabOrder = 2
    OnDrawTab = CPageCtrlDrawTab
    object C1: TTabSheet
      Caption = ' '#33258#31038#24773#22577#65297' '
      object Label1: TLabel
        Left = 4
        Top = 8
        Width = 68
        Height = 12
        Caption = #33258#31038#21517'('#23627#21495')'
      end
      object Label2: TLabel
        Left = 4
        Top = 32
        Width = 48
        Height = 12
        Caption = #20195#34920#32773#21517
      end
      object Label3: TLabel
        Left = 4
        Top = 56
        Width = 48
        Height = 12
        Caption = #37109#20415#30058#21495
      end
      object Label4: TLabel
        Left = 4
        Top = 80
        Width = 32
        Height = 12
        Caption = #20303#25152#65297
      end
      object Label5: TLabel
        Left = 4
        Top = 104
        Width = 32
        Height = 12
        Caption = #20303#25152#65298
      end
      object Label6: TLabel
        Left = 4
        Top = 128
        Width = 48
        Height = 12
        Caption = #38651#35441#30058#21495
      end
      object Label8: TLabel
        Left = 4
        Top = 176
        Width = 44
        Height = 12
        Caption = #25391#36796#20808#65297
      end
      object Label9: TLabel
        Left = 4
        Top = 200
        Width = 44
        Height = 12
        Caption = #25391#36796#20808#65298
      end
      object Label10: TLabel
        Left = 4
        Top = 224
        Width = 48
        Height = 12
        Caption = #28040#36027#31246#29575
      end
      object Label7: TLabel
        Left = 4
        Top = 152
        Width = 22
        Height = 12
        Caption = 'FAX'
      end
      object Label11: TLabel
        Left = 130
        Top = 220
        Width = 151
        Height = 12
        Caption = '('#8251#38750#35506#31246#12398#22580#21512#12399' 0 '#12392#20837#21147')'
      end
      object Label38: TLabel
        Left = 130
        Top = 236
        Width = 207
        Height = 12
        Caption = '('#8251#31246#38989#35336#31639#19981#35201#12398#22580#21512#12399#31354#27396#12395#12375#12414#12377')'
      end
      object Label39: TLabel
        Left = 117
        Top = 230
        Width = 6
        Height = 12
        Caption = '%'
      end
      object CompanyNameEdit_1: TBaseEdit
        Left = 79
        Top = 4
        Width = 327
        Height = 20
        TabOrder = 0
        MaxLength = 256
        dx = 0
        dy = 0
      end
      object RepresentEdit_1: TBaseEdit
        Left = 79
        Top = 28
        Width = 327
        Height = 20
        TabOrder = 1
        MaxLength = 128
        dx = 0
        dy = 0
      end
      object ZipNumberEdit_1: TBaseEdit
        Left = 79
        Top = 52
        Width = 122
        Height = 20
        TabOrder = 2
        MaxLength = 32
        ImeMode = imDisable
        dx = 0
        dy = 0
        KeyFilter = PostCode
      end
      object AddressEdit1_1: TBaseEdit
        Left = 79
        Top = 76
        Width = 327
        Height = 20
        TabOrder = 3
        MaxLength = 256
        dx = 0
        dy = 0
      end
      object AddressEdit2_1: TBaseEdit
        Left = 79
        Top = 100
        Width = 327
        Height = 20
        TabOrder = 4
        MaxLength = 256
        dx = 0
        dy = 0
      end
      object TELEdit_1: TBaseEdit
        Left = 79
        Top = 124
        Width = 150
        Height = 20
        TabOrder = 5
        MaxLength = 64
        ImeMode = imDisable
        dx = 0
        dy = 0
        KeyFilter = Telephone
      end
      object FAXEdit_1: TBaseEdit
        Left = 79
        Top = 148
        Width = 150
        Height = 20
        TabOrder = 6
        MaxLength = 64
        ImeMode = imDisable
        dx = 0
        dy = 0
        KeyFilter = Telephone
      end
      object TransferEdit1_1: TBaseEdit
        Left = 79
        Top = 172
        Width = 327
        Height = 20
        TabOrder = 7
        MaxLength = 256
        dx = 0
        dy = 0
      end
      object TransferEdit2_1: TBaseEdit
        Left = 79
        Top = 196
        Width = 327
        Height = 20
        TabOrder = 8
        MaxLength = 256
        dx = 0
        dy = 0
      end
      object TaxEdit_1: TBaseEdit
        Left = 79
        Top = 220
        Width = 35
        Height = 20
        TabOrder = 9
        MaxLength = 2
        ImeMode = imDisable
        dx = 0
        dy = 0
        KeyFilter = Number
        DataType = Integer
      end
      object ZipToAddressBtn: TBitBtn2
        Left = 208
        Top = 52
        Width = 121
        Height = 19
        Caption = #37109#20415#30058#21495#8594#20303#25152#22793#25563
        DoubleBuffered = True
        DoubleBufferedMode = dbmRequested
        ParentDoubleBuffered = False
        TabOrder = 10
        TabStop = False
        OnClick = ZipToAddressBtnClick
        DownColor = clBtnFace
      end
    end
    object C2: TTabSheet
      Caption = ' '#33258#31038#24773#22577#65298' '
      ImageIndex = 1
      object Label12: TLabel
        Left = 4
        Top = 8
        Width = 68
        Height = 12
        Caption = #33258#31038#21517'('#23627#21495')'
      end
      object Label13: TLabel
        Left = 4
        Top = 32
        Width = 48
        Height = 12
        Caption = #20195#34920#32773#21517
      end
      object Label14: TLabel
        Left = 4
        Top = 56
        Width = 48
        Height = 12
        Caption = #37109#20415#30058#21495
      end
      object Label15: TLabel
        Left = 4
        Top = 80
        Width = 32
        Height = 12
        Caption = #20303#25152#65297
      end
      object Label16: TLabel
        Left = 4
        Top = 104
        Width = 32
        Height = 12
        Caption = #20303#25152#65298
      end
      object Label17: TLabel
        Left = 4
        Top = 128
        Width = 48
        Height = 12
        Caption = #38651#35441#30058#21495
      end
      object Label18: TLabel
        Left = 4
        Top = 176
        Width = 44
        Height = 12
        Caption = #25391#36796#20808#65297
      end
      object Label19: TLabel
        Left = 4
        Top = 200
        Width = 44
        Height = 12
        Caption = #25391#36796#20808#65298
      end
      object Label20: TLabel
        Left = 4
        Top = 224
        Width = 48
        Height = 12
        Caption = #28040#36027#31246#29575
      end
      object Label22: TLabel
        Left = 4
        Top = 152
        Width = 22
        Height = 12
        Caption = 'FAX'
      end
      object Label21: TLabel
        Left = 130
        Top = 220
        Width = 151
        Height = 12
        Caption = '('#8251#38750#35506#31246#12398#22580#21512#12399' 0 '#12392#20837#21147')'
      end
      object Label36: TLabel
        Left = 130
        Top = 236
        Width = 207
        Height = 12
        Caption = '('#8251#31246#38989#35336#31639#19981#35201#12398#22580#21512#12399#31354#27396#12395#12375#12414#12377')'
      end
      object Label37: TLabel
        Left = 117
        Top = 230
        Width = 6
        Height = 12
        Caption = '%'
      end
      object CompanyNameEdit_2: TBaseEdit
        Left = 79
        Top = 4
        Width = 327
        Height = 20
        TabOrder = 0
        MaxLength = 256
        dx = 0
        dy = 0
      end
      object RepresentEdit_2: TBaseEdit
        Left = 79
        Top = 28
        Width = 327
        Height = 20
        TabOrder = 1
        MaxLength = 128
        dx = 0
        dy = 0
      end
      object ZipNumberEdit_2: TBaseEdit
        Left = 79
        Top = 52
        Width = 122
        Height = 20
        TabOrder = 2
        MaxLength = 32
        ImeMode = imDisable
        dx = 0
        dy = 0
        KeyFilter = PostCode
      end
      object AddressEdit1_2: TBaseEdit
        Left = 79
        Top = 76
        Width = 327
        Height = 20
        TabOrder = 3
        MaxLength = 256
        dx = 0
        dy = 0
      end
      object AddressEdit2_2: TBaseEdit
        Left = 79
        Top = 100
        Width = 327
        Height = 20
        TabOrder = 4
        MaxLength = 256
        dx = 0
        dy = 0
      end
      object TELEdit_2: TBaseEdit
        Left = 79
        Top = 124
        Width = 150
        Height = 20
        TabOrder = 5
        MaxLength = 64
        ImeMode = imDisable
        dx = 0
        dy = 0
        KeyFilter = Telephone
      end
      object FAXEdit_2: TBaseEdit
        Left = 79
        Top = 148
        Width = 150
        Height = 20
        TabOrder = 6
        MaxLength = 64
        ImeMode = imDisable
        dx = 0
        dy = 0
        KeyFilter = Telephone
      end
      object TransferEdit1_2: TBaseEdit
        Left = 79
        Top = 172
        Width = 327
        Height = 20
        TabOrder = 7
        MaxLength = 256
        dx = 0
        dy = 0
      end
      object TransferEdit2_2: TBaseEdit
        Left = 79
        Top = 196
        Width = 327
        Height = 20
        TabOrder = 8
        MaxLength = 256
        dx = 0
        dy = 0
      end
      object TaxEdit_2: TBaseEdit
        Left = 79
        Top = 220
        Width = 35
        Height = 20
        TabOrder = 9
        MaxLength = 2
        ImeMode = imDisable
        dx = 0
        dy = 0
        KeyFilter = Number
      end
      object ZipBtn2: TBitBtn2
        Left = 208
        Top = 52
        Width = 121
        Height = 19
        Caption = #37109#20415#30058#21495#8594#20303#25152#22793#25563
        DoubleBuffered = True
        DoubleBufferedMode = dbmRequested
        ParentDoubleBuffered = False
        TabOrder = 10
        TabStop = False
        OnClick = ZipToAddressBtnClick
        DownColor = clBtnFace
      end
    end
    object C3: TTabSheet
      Caption = ' '#33258#31038#24773#22577#65299' '
      ImageIndex = 2
      object Label23: TLabel
        Left = 4
        Top = 8
        Width = 68
        Height = 12
        Caption = #33258#31038#21517'('#23627#21495')'
      end
      object Label24: TLabel
        Left = 4
        Top = 32
        Width = 48
        Height = 12
        Caption = #20195#34920#32773#21517
      end
      object Label25: TLabel
        Left = 4
        Top = 56
        Width = 48
        Height = 12
        Caption = #37109#20415#30058#21495
      end
      object Label26: TLabel
        Left = 4
        Top = 80
        Width = 32
        Height = 12
        Caption = #20303#25152#65297
      end
      object Label27: TLabel
        Left = 4
        Top = 104
        Width = 32
        Height = 12
        Caption = #20303#25152#65298
      end
      object Label28: TLabel
        Left = 4
        Top = 128
        Width = 48
        Height = 12
        Caption = #38651#35441#30058#21495
      end
      object Label29: TLabel
        Left = 4
        Top = 176
        Width = 44
        Height = 12
        Caption = #25391#36796#20808#65297
      end
      object Label30: TLabel
        Left = 4
        Top = 200
        Width = 44
        Height = 12
        Caption = #25391#36796#20808#65298
      end
      object Label31: TLabel
        Left = 4
        Top = 224
        Width = 48
        Height = 12
        Caption = #28040#36027#31246#29575
      end
      object Label32: TLabel
        Left = 130
        Top = 220
        Width = 151
        Height = 12
        Caption = '('#8251#38750#35506#31246#12398#22580#21512#12399' 0 '#12392#20837#21147')'
      end
      object Label33: TLabel
        Left = 4
        Top = 152
        Width = 22
        Height = 12
        Caption = 'FAX'
      end
      object Label34: TLabel
        Left = 130
        Top = 236
        Width = 207
        Height = 12
        Caption = '('#8251#31246#38989#35336#31639#19981#35201#12398#22580#21512#12399#31354#27396#12395#12375#12414#12377')'
      end
      object Label35: TLabel
        Left = 117
        Top = 230
        Width = 6
        Height = 12
        Caption = '%'
      end
      object CompanyNameEdit_3: TBaseEdit
        Left = 79
        Top = 4
        Width = 327
        Height = 20
        TabOrder = 0
        MaxLength = 256
        dx = 0
        dy = 0
      end
      object RepresentEdit_3: TBaseEdit
        Left = 79
        Top = 28
        Width = 327
        Height = 20
        TabOrder = 1
        MaxLength = 128
        dx = 0
        dy = 0
      end
      object ZipNumberEdit_3: TBaseEdit
        Left = 79
        Top = 52
        Width = 122
        Height = 20
        TabOrder = 2
        MaxLength = 32
        ImeMode = imDisable
        dx = 0
        dy = 0
        KeyFilter = PostCode
      end
      object AddressEdit1_3: TBaseEdit
        Left = 79
        Top = 76
        Width = 327
        Height = 20
        TabOrder = 3
        MaxLength = 256
        dx = 0
        dy = 0
      end
      object AddressEdit2_3: TBaseEdit
        Left = 79
        Top = 100
        Width = 327
        Height = 20
        TabOrder = 4
        MaxLength = 256
        dx = 0
        dy = 0
      end
      object TELEdit_3: TBaseEdit
        Left = 79
        Top = 124
        Width = 150
        Height = 20
        TabOrder = 5
        MaxLength = 64
        ImeMode = imDisable
        dx = 0
        dy = 0
        KeyFilter = Telephone
      end
      object FAXEdit_3: TBaseEdit
        Left = 79
        Top = 148
        Width = 150
        Height = 20
        TabOrder = 6
        MaxLength = 64
        ImeMode = imDisable
        dx = 0
        dy = 0
        KeyFilter = Telephone
      end
      object TransferEdit1_3: TBaseEdit
        Left = 79
        Top = 172
        Width = 327
        Height = 20
        TabOrder = 7
        MaxLength = 256
        dx = 0
        dy = 0
      end
      object TransferEdit2_3: TBaseEdit
        Left = 79
        Top = 196
        Width = 327
        Height = 20
        TabOrder = 8
        MaxLength = 256
        dx = 0
        dy = 0
      end
      object TaxEdit_3: TBaseEdit
        Left = 79
        Top = 220
        Width = 35
        Height = 20
        TabOrder = 9
        MaxLength = 2
        ImeMode = imDisable
        dx = 0
        dy = 0
        KeyFilter = Number
        DataType = Integer
      end
      object ZipBtn3: TBitBtn2
        Left = 208
        Top = 52
        Width = 121
        Height = 19
        Caption = #37109#20415#30058#21495#8594#20303#25152#22793#25563
        DoubleBuffered = True
        DoubleBufferedMode = dbmRequested
        ParentDoubleBuffered = False
        TabOrder = 10
        TabStop = False
        OnClick = ZipToAddressBtnClick
        DownColor = clBtnFace
      end
    end
  end
end
