object Form1: TForm1
  Left = 192
  Top = 114
  Width = 783
  Height = 540
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object PrintArea: TMemo
    Left = 16
    Top = 216
    Width = 737
    Height = 281
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
    Left = 224
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
    end
  end
end
