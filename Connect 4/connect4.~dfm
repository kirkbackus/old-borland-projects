object C4Form: TC4Form
  Left = 197
  Top = 111
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Connect 4 Game'
  ClientHeight = 347
  ClientWidth = 296
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
  object TitleBox: TScrollBox
    Left = 0
    Top = 0
    Width = 296
    Height = 65
    Align = alTop
    BevelInner = bvNone
    Color = clNavy
    Ctl3D = False
    ParentColor = False
    ParentCtl3D = False
    TabOrder = 0
    object Title: TLabel
      Left = 8
      Top = 8
      Width = 179
      Height = 44
      Caption = 'Connect 4'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWhite
      Font.Height = -35
      Font.Name = 'Showcard Gothic'
      Font.Style = []
      ParentFont = False
    end
  end
  object GameBox: TScrollBox
    Left = 0
    Top = 65
    Width = 296
    Height = 282
    HorzScrollBar.Visible = False
    VertScrollBar.Visible = False
    Align = alClient
    BorderStyle = bsNone
    Color = clBlack
    ParentColor = False
    TabOrder = 1
    object GameImg: TImage
      Left = 0
      Top = 0
      Width = 296
      Height = 263
      Align = alClient
      OnMouseDown = GameImgMouseDown
      OnMouseMove = GameImgMouseMove
    end
    object TmpCircle: TShape
      Left = 0
      Top = 0
      Width = 48
      Height = 48
      Brush.Color = clRed
      Pen.Color = clWhite
      Shape = stCircle
    end
    object C4StatusBar: TStatusBar
      Left = 0
      Top = 263
      Width = 296
      Height = 19
      Color = clWhite
      Panels = <
        item
          Text = ' Player 1'#39's Turn'
          Width = 512
        end>
      SimplePanel = False
    end
  end
  object MainMenu1: TMainMenu
    object Game1: TMenuItem
      Caption = 'Game'
      object NewGame1: TMenuItem
        Caption = 'New Game'
        ShortCut = 16462
        OnClick = NewGame1Click
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Exit1: TMenuItem
        Caption = 'Exit'
        ShortCut = 16465
        OnClick = Exit1Click
      end
    end
    object Transparency1: TMenuItem
      Caption = 'Transparency'
      object N201: TMenuItem
        Caption = '20%'
        ShortCut = 16433
        OnClick = N201Click
      end
      object N401: TMenuItem
        Caption = '40%'
        ShortCut = 16434
        OnClick = N401Click
      end
      object N601: TMenuItem
        Caption = '60%'
        ShortCut = 16435
        OnClick = N601Click
      end
      object N801: TMenuItem
        Caption = '80%'
        ShortCut = 16436
        OnClick = N801Click
      end
      object N901: TMenuItem
        Caption = '90%'
        ShortCut = 16437
        OnClick = N901Click
      end
      object N01: TMenuItem
        Caption = '-'
      end
      object Opaque1: TMenuItem
        Caption = 'Opaque'
        ShortCut = 16432
        OnClick = Opaque1Click
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object RemoveFromTaskbar1: TMenuItem
        Caption = 'Taskbar Button'
        Checked = True
        OnClick = RemoveFromTaskbar1Click
      end
    end
    object Help1: TMenuItem
      Caption = 'Help'
      object About1: TMenuItem
        Caption = 'About'
        ShortCut = 16456
        OnClick = About1Click
      end
    end
  end
  object GameTimer: TTimer
    Interval = 1
    OnTimer = GameTimerTimer
    Left = 32
  end
end
