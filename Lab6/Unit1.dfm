object Form1: TForm1
  Left = 930
  Top = 174
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Trees'
  ClientHeight = 506
  ClientWidth = 836
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
    Left = 16
    Top = 304
    Width = 35
    Height = 13
    Caption = 'Output:'
  end
  object treeLabel: TLabel
    Left = 416
    Top = 8
    Width = 98
    Height = 13
    Caption = 'Tree representation :'
  end
  object PrintArea: TMemo
    Left = 416
    Top = 24
    Width = 409
    Height = 473
    Lines.Strings = (
      'PrintArea')
    TabOrder = 0
  end
  object appendGroupBox: TGroupBox
    Left = 16
    Top = 8
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
    Top = 8
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
    Left = 16
    Top = 320
    Width = 385
    Height = 177
    TabOrder = 3
  end
  object printGroupBox: TGroupBox
    Left = 16
    Top = 168
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
    Top = 168
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
    end
    object deleteButton: TButton
      Left = 32
      Top = 88
      Width = 121
      Height = 25
      Caption = 'Delete tree'
      TabOrder = 1
    end
    object leavesButton: TButton
      Left = 32
      Top = 56
      Width = 121
      Height = 25
      Caption = 'Print number of leaves'
      TabOrder = 2
    end
  end
end
