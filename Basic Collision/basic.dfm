object Form1: TForm1
  Left = 192
  Top = 114
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Collision Engine'
  ClientHeight = 409
  ClientWidth = 560
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Shape2: TShape
    Left = 200
    Top = 120
    Width = 145
    Height = 145
  end
  object Shape3: TShape
    Left = 200
    Top = 120
    Width = 145
    Height = 145
    Shape = stCircle
  end
  object Shape1: TShape
    Left = 56
    Top = 24
    Width = 81
    Height = 105
    Brush.Style = bsClear
  end
  object Shape4: TShape
    Left = 56
    Top = 36
    Width = 81
    Height = 81
    Brush.Style = bsClear
    Shape = stCircle
  end
  object Timer1: TTimer
    Interval = 1
    OnTimer = Timer1Timer
    Left = 600
    Top = 8
  end
end
