object Form1: TForm1
  Left = 801
  Top = 252
  Width = 924
  Height = 547
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
  object Image1: TImage
    Left = 8
    Top = 176
    Width = 425
    Height = 329
  end
  object Chart1: TChart
    Left = 448
    Top = 168
    Width = 465
    Height = 337
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.Text.Strings = (
      'TChart')
    TabOrder = 0
  end
  object chartControlsGroupBox: TGroupBox
    Left = 448
    Top = 0
    Width = 465
    Height = 169
    Caption = 'Char controls'
    TabOrder = 1
    object RadioGroup1: TRadioGroup
      Left = 264
      Top = 40
      Width = 185
      Height = 105
      Caption = 'RadioGroup1'
      TabOrder = 0
    end
  end
  object imageControlsGroupBox: TGroupBox
    Left = 8
    Top = 0
    Width = 425
    Height = 169
    Caption = 'Image controls'
    TabOrder = 2
    object loadImageButton: TButton
      Left = 8
      Top = 24
      Width = 185
      Height = 25
      Caption = 'Load image'
      TabOrder = 0
      OnClick = loadImageButtonClick
    end
    object playAnimationButton: TButton
      Left = 8
      Top = 56
      Width = 185
      Height = 25
      Caption = 'Play animation (Rammstein logo)'
      TabOrder = 1
      OnClick = playAnimationButtonClick
    end
  end
  object openPictureDialog: TOpenDialog
    Filter = 'Pictures|*.jpg;*.jpeg'
    Left = 32
    Top = 200
  end
end
