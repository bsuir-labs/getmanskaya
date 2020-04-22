object Form1: TForm1
  Left = 1162
  Top = 120
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Trees'
  ClientHeight = 506
  ClientWidth = 724
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object searchResultsLabel: TLabel
    Left = 416
    Top = 8
    Width = 35
    Height = 13
    Caption = 'Output:'
  end
  object treeLabel: TLabel
    Left = 416
    Top = 192
    Width = 98
    Height = 13
    Caption = 'Tree representation :'
  end
  object PrintArea: TMemo
    Left = 416
    Top = 208
    Width = 297
    Height = 289
    Lines.Strings = (
      'PrintArea')
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object appendGroupBox: TGroupBox
    Left = 16
    Top = 208
    Width = 185
    Height = 153
    Caption = 'Add new value'
    TabOrder = 1
    object newKeyEdit: TLabeledEdit
      Left = 16
      Top = 40
      Width = 153
      Height = 21
      EditLabel.Width = 76
      EditLabel.Height = 13
      EditLabel.BiDiMode = bdLeftToRight
      EditLabel.Caption = 'Key (digits only):'
      EditLabel.ParentBiDiMode = False
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 0
      Text = '0'
    end
    object newValueEdit: TLabeledEdit
      Left = 16
      Top = 80
      Width = 153
      Height = 21
      EditLabel.Width = 30
      EditLabel.Height = 13
      EditLabel.Caption = 'Value:'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 1
    end
    object AppendButton: TButton
      Left = 54
      Top = 112
      Width = 75
      Height = 25
      Cancel = True
      Caption = 'Append'
      TabOrder = 2
      OnClick = AppendButtonClick
    end
  end
  object findGroupBox: TGroupBox
    Left = 216
    Top = 208
    Width = 185
    Height = 153
    Caption = 'Search'
    TabOrder = 2
    object findAndPrintButton: TButton
      Left = 56
      Top = 80
      Width = 75
      Height = 25
      Caption = 'Print info'
      TabOrder = 0
      OnClick = findAndPrintButtonClick
    end
    object findKeyEdit: TLabeledEdit
      Left = 16
      Top = 40
      Width = 153
      Height = 21
      EditLabel.Width = 53
      EditLabel.Height = 13
      EditLabel.Caption = 'Key to find:'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 1
    end
    object findAndEraseButton: TButton
      Left = 56
      Top = 112
      Width = 75
      Height = 25
      Caption = 'REMOVE'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = findAndEraseButtonClick
    end
  end
  object searchResultsArea: TMemo
    Left = 416
    Top = 24
    Width = 297
    Height = 161
    ScrollBars = ssVertical
    TabOrder = 3
  end
  object printGroupBox: TGroupBox
    Left = 16
    Top = 368
    Width = 185
    Height = 129
    Caption = 'Print'
    TabOrder = 4
    object preorderButton: TButton
      Left = 16
      Top = 24
      Width = 153
      Height = 25
      Caption = 'Pre-order traversal'
      TabOrder = 0
      OnClick = preorderButtonClick
    end
    object postorderButton: TButton
      Left = 16
      Top = 56
      Width = 153
      Height = 25
      Caption = 'Post-order traversal'
      TabOrder = 1
      OnClick = postorderButtonClick
    end
    object inorderButton: TButton
      Left = 16
      Top = 88
      Width = 153
      Height = 25
      Caption = 'In-order traversal'
      TabOrder = 2
      OnClick = inorderButtonClick
    end
  end
  object controlsGroupBox: TGroupBox
    Left = 216
    Top = 368
    Width = 185
    Height = 129
    Caption = 'Controls'
    TabOrder = 5
    object rebalanceButton: TButton
      Left = 32
      Top = 24
      Width = 121
      Height = 25
      Caption = 'Rebalance tree'
      TabOrder = 0
      OnClick = rebalanceButtonClick
    end
    object deleteButton: TButton
      Left = 32
      Top = 88
      Width = 121
      Height = 25
      Caption = 'Delete tree'
      TabOrder = 1
      OnClick = deleteButtonClick
    end
    object leavesButton: TButton
      Left = 32
      Top = 56
      Width = 121
      Height = 25
      Caption = 'Print number of leaves'
      TabOrder = 2
      OnClick = leavesButtonClick
    end
  end
  object treeInitGroupBox: TGroupBox
    Left = 16
    Top = 8
    Width = 385
    Height = 193
    Caption = 'Tree initialization'
    TabOrder = 6
    object sourceStringGrid: TStringGrid
      Left = 8
      Top = 16
      Width = 369
      Height = 120
      ColCount = 2
      Ctl3D = True
      FixedCols = 0
      RowCount = 100
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goAlwaysShowEditor]
      ParentCtl3D = False
      ScrollBars = ssVertical
      TabOrder = 0
      ColWidths = (
        74
        270)
    end
    object initTreeButton: TButton
      Left = 280
      Top = 152
      Width = 91
      Height = 25
      Caption = 'Create the tree'
      TabOrder = 1
      OnClick = initTreeButtonClick
    end
    object clearTableButton: TButton
      Left = 176
      Top = 152
      Width = 91
      Height = 25
      Caption = 'Clear table'
      TabOrder = 2
      OnClick = clearTableButtonClick
    end
  end
end
