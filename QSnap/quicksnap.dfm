object QSnap: TQSnap
  Left = 192
  Top = 114
  Width = 468
  Height = 346
  Caption = 'Quick Snap'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object QSnapDirections: TLabel
    Left = 0
    Top = 0
    Width = 460
    Height = 13
    Align = alTop
    Caption = 
      'Press Shift + Enter to take a snapshot which will be saved to th' +
      'e selected directory'
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 293
    Width = 460
    Height = 19
    Panels = <>
    SimplePanel = False
  end
  object QSnapBox: TScrollBox
    Left = 0
    Top = 13
    Width = 460
    Height = 280
    Align = alClient
    TabOrder = 1
    object QSnapImage: TImage
      Left = 0
      Top = 0
      Width = 456
      Height = 276
    end
    object QSnapDir: TDirectoryListBox
      Left = 0
      Top = 0
      Width = 456
      Height = 276
      Align = alClient
      ItemHeight = 16
      TabOrder = 0
    end
    object QSnapButton: TButton
      Left = 376
      Top = 248
      Width = 75
      Height = 25
      Caption = 'OK'
      TabOrder = 1
      OnClick = QSnapButtonClick
    end
    object QSnapName: TEdit
      Left = 376
      Top = 224
      Width = 73
      Height = 21
      TabOrder = 2
      Text = 'snapshot'
    end
  end
  object QSnapTimer: TTimer
    Interval = 1
    OnTimer = QSnapTimerTimer
    Left = 304
    Top = 32
  end
end
