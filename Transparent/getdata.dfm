object Form1: TForm1
  Left = 300
  Top = 164
  Width = 610
  Height = 113
  Caption = 'SUPER CONTROLLER'
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
    Left = 8
    Top = 8
    Width = 32
    Height = 13
    Caption = 'Label1'
  end
  object TrackBar1: TTrackBar
    Left = 208
    Top = 16
    Width = 377
    Height = 45
    Max = 255
    Orientation = trHorizontal
    Frequency = 1
    Position = 255
    SelEnd = 0
    SelStart = 0
    TabOrder = 0
    TickMarks = tmBottomRight
    TickStyle = tsNone
    OnChange = TrackBar1Change
  end
  object Timer1: TTimer
    Interval = 1
    OnTimer = Timer1Timer
  end
end
