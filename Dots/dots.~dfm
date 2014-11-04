object DotForm: TDotForm
  Left = 192
  Top = 114
  Width = 177
  Height = 299
  Caption = 'Dot'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnPaint = FormPaint
  PixelsPerInch = 96
  TextHeight = 13
  object Interface: TGroupBox
    Left = 8
    Top = 8
    Width = 153
    Height = 217
    Caption = 'Dot Controller Interface'
    TabOrder = 0
    object LSpeed: TLabel
      Left = 16
      Top = 24
      Width = 115
      Height = 13
      Caption = 'Speed (Pixels / Second)'
    end
    object LSize: TLabel
      Left = 16
      Top = 72
      Width = 40
      Height = 13
      Caption = 'Dot Size'
    end
    object LAngle: TLabel
      Left = 16
      Top = 120
      Width = 27
      Height = 13
      Caption = 'Angle'
    end
    object LSpacing: TLabel
      Left = 16
      Top = 168
      Width = 39
      Height = 13
      Caption = 'Spacing'
    end
    object Speed: TEdit
      Left = 16
      Top = 40
      Width = 121
      Height = 21
      TabOrder = 0
      Text = '50'
      OnChange = SpeedChange
    end
    object Size: TEdit
      Left = 16
      Top = 88
      Width = 121
      Height = 21
      TabOrder = 1
      Text = '1'
      OnChange = SizeChange
    end
    object Angle: TEdit
      Left = 16
      Top = 136
      Width = 121
      Height = 21
      TabOrder = 2
      Text = '30'
      OnChange = AngleChange
    end
    object Space: TEdit
      Left = 16
      Top = 184
      Width = 121
      Height = 21
      TabOrder = 3
      Text = '64'
      OnChange = SpaceChange
    end
  end
  object Generate: TButton
    Left = 8
    Top = 232
    Width = 153
    Height = 25
    Caption = 'Generate'
    TabOrder = 1
    OnClick = GenerateClick
  end
  object Controller: TTimer
    Enabled = False
    Interval = 1
    OnTimer = ControllerTimer
  end
end
