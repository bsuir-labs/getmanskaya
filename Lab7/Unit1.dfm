object Form1: TForm1
  Left = 943
  Top = 271
  Width = 924
  Height = 547
  Caption = 'Images & Charts'
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
    object Series1: TLineSeries
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = clRed
      Pointer.Dark3D = False
      Pointer.Draw3D = False
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = False
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
  end
  object chartControlsGroupBox: TGroupBox
    Left = 448
    Top = 0
    Width = 465
    Height = 169
    Caption = 'Char controls'
    TabOrder = 1
    object functionsToPlotGroup: TRadioGroup
      Left = 264
      Top = 16
      Width = 193
      Height = 145
      Caption = 'Functions to plot'
      TabOrder = 0
    end
    object sinRadioButton: TRadioButton
      Left = 280
      Top = 40
      Width = 113
      Height = 17
      Caption = 'sin(x)'
      Checked = True
      TabOrder = 1
      TabStop = True
    end
    object expRadioButton: TRadioButton
      Left = 280
      Top = 64
      Width = 113
      Height = 17
      Caption = 'exp(x)'
      TabOrder = 2
    end
    object xxRadioButton: TRadioButton
      Left = 280
      Top = 88
      Width = 113
      Height = 17
      Caption = 'x^2'
      TabOrder = 3
    end
    object startEdit: TLabeledEdit
      Left = 8
      Top = 40
      Width = 73
      Height = 21
      EditLabel.Width = 61
      EditLabel.Height = 13
      EditLabel.Caption = 'First X value:'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 4
      Text = '0'
    end
    object finishEdit: TLabeledEdit
      Left = 96
      Top = 40
      Width = 73
      Height = 21
      EditLabel.Width = 60
      EditLabel.Height = 13
      EditLabel.Caption = 'Last X vaue:'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 5
      Text = '50'
    end
    object plotCharButton: TButton
      Left = 184
      Top = 88
      Width = 75
      Height = 25
      Caption = 'Plot chart'
      TabOrder = 6
      OnClick = plotCharButtonClick
    end
    object stepEdit: TLabeledEdit
      Left = 184
      Top = 40
      Width = 73
      Height = 21
      EditLabel.Width = 47
      EditLabel.Height = 13
      EditLabel.Caption = 'Increment'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 7
      Text = '1'
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
