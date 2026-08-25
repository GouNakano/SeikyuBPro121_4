object ItemManageForm: TItemManageForm
  Left = 918
  Top = 317
  BorderIcons = [biSystemMenu, biMaximize]
  Caption = #26696#20214#31649#29702
  ClientHeight = 492
  ClientWidth = 436
  Color = clBtnFace
  Font.Charset = SHIFTJIS_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 12
  object TopPanel: TPanel
    Left = 0
    Top = 0
    Width = 436
    Height = 21
    Align = alTop
    TabOrder = 0
    ExplicitWidth = 444
  end
  object BottomPanel: TPanel
    Left = 0
    Top = 472
    Width = 436
    Height = 20
    Align = alBottom
    TabOrder = 1
    ExplicitTop = 477
    ExplicitWidth = 444
  end
  object ClientPanel: TPanel
    Left = 0
    Top = 21
    Width = 436
    Height = 451
    Align = alClient
    TabOrder = 2
    ExplicitWidth = 444
    ExplicitHeight = 456
    object Splitter1: TSplitter
      Left = 1
      Top = 146
      Width = 442
      Height = 3
      Cursor = crVSplit
      Align = alTop
    end
    object FolderPanel: TPanel
      Left = 1
      Top = 1
      Width = 442
      Height = 145
      Align = alTop
      TabOrder = 0
    end
    object ItemPanel: TPanel
      Left = 1
      Top = 149
      Width = 442
      Height = 306
      Align = alClient
      TabOrder = 1
      object HistListView: TListView
        Left = 1
        Top = 1
        Width = 440
        Height = 304
        Align = alClient
        Columns = <
          item
            Caption = #26085#20184
            Width = 75
          end
          item
            Caption = #23458#20808#21517
            Width = 100
          end
          item
            Caption = #20214#21517
            Width = 210
          end>
        ReadOnly = True
        RowSelect = True
        TabOrder = 0
        TabStop = False
        ViewStyle = vsReport
        OnClick = HistListViewClick
        OnColumnClick = HistListViewColumnClick
        OnCompare = HistListViewCompare
        OnDeletion = HistListViewDeletion
        OnMouseDown = HistListViewMouseDown
      end
    end
  end
  object HistPopupMenu: TPopupMenu
    Left = 8
    Top = 32
    object DeleteHistMenu: TMenuItem
      Caption = #21066#38500'(&D)'
      OnClick = DeleteHistMenuClick
    end
  end
end
