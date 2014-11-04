object MiniTVForm: TMiniTVForm
  Left = 192
  Top = 114
  Width = 361
  Height = 383
  Caption = 'Mini TV'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object MiniTV: TWindowsMediaPlayer
    Left = 0
    Top = 0
    Width = 353
    Height = 329
    Align = alClient
    TabOrder = 0
    ControlData = {
      000300000800000000000500000000000000F03F030000000000050000000000
      0000000008000200000000000300010000000B00FFFF0300000000000B00FFFF
      08000200000000000300320000000B00000008000A000000660075006C006C00
      00000B0000000B0000000B00FFFF0B00FFFF0B00000008000200000000000800
      020000000000080002000000000008000200000000000B0000007C2400000122
      0000}
  end
  object MainMenu1: TMainMenu
    Left = 8
    Top = 8
    object Sports1: TMenuItem
      Caption = 'Sports'
      object ESPN1: TMenuItem
        Caption = 'ESPN'
      end
    end
    object Weather1: TMenuItem
      Caption = 'Weather'
    end
  end
end
