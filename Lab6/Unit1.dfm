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
  object Label1: TLabel
    Left = 16
    Top = 16
    Width = 79
    Height = 13
    Caption = 'Input new value:'
  end
  object PrintArea: TMemo
    Left = 16
    Top = 136
    Width = 737
    Height = 361
    Lines.Strings = (
      'PrintArea')
    TabOrder = 0
  end
  object NewElementEdit: TEdit
    Left = 104
    Top = 8
    Width = 121
    Height = 21
    TabOrder = 1
    Text = '0'
  end
  object AppendButton: TButton
    Left = 240
    Top = 8
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Append'
    TabOrder = 2
    OnClick = AppendButtonClick
  end
end
