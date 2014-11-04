object GameForm: TGameForm
  Left = 219
  Top = 132
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Network Pong'
  ClientHeight = 422
  ClientWidth = 616
  Color = clGreen
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = Menu
  OldCreateOrder = False
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object GameSBar: TStatusBar
    Left = 0
    Top = 403
    Width = 616
    Height = 19
    Color = clWhite
    Panels = <>
    SimplePanel = False
  end
  object GameBox: TScrollBox
    Left = 0
    Top = 0
    Width = 616
    Height = 403
    HorzScrollBar.Visible = False
    VertScrollBar.Visible = False
    Align = alClient
    BorderStyle = bsNone
    Color = clGreen
    ParentColor = False
    TabOrder = 1
    object BackDivider: TShape
      Left = 302
      Top = 0
      Width = 12
      Height = 409
      Brush.Color = clGray
    end
    object LStatus: TLabel
      Left = 0
      Top = 40
      Width = 616
      Height = 97
      Alignment = taCenter
      AutoSize = False
      Caption = 'NETWORK PONG'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWhite
      Font.Height = -32
      Font.Name = 'Showcard Gothic'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object LScore: TLabel
      Left = 0
      Top = 0
      Width = 616
      Height = 41
      Alignment = taCenter
      AutoSize = False
      Caption = '0 - 0'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWhite
      Font.Height = -32
      Font.Name = 'Showcard Gothic'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object Ball: TShape
      Left = 296
      Top = 296
      Width = 25
      Height = 25
      Shape = stCircle
    end
    object ClientPaddle: TShape
      Left = 568
      Top = 144
      Width = 33
      Height = 121
      Brush.Color = clBlue
    end
    object HostPaddle: TShape
      Left = 16
      Top = 144
      Width = 33
      Height = 121
      Brush.Color = clRed
    end
    object JoinBox: TScrollBox
      Left = 0
      Top = 0
      Width = 137
      Height = 89
      Color = clBlack
      Ctl3D = False
      ParentColor = False
      ParentCtl3D = False
      TabOrder = 0
      object Label1: TLabel
        Left = 8
        Top = 8
        Width = 72
        Height = 17
        Caption = 'IPADDRESS'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWhite
        Font.Height = -13
        Font.Name = 'Showcard Gothic'
        Font.Style = []
        ParentFont = False
      end
      object IPEdit: TEdit
        Left = 8
        Top = 32
        Width = 121
        Height = 19
        AutoSelect = False
        AutoSize = False
        BevelInner = bvNone
        TabOrder = 0
        Text = '127.0.0.1'
      end
      object JoinButton: TButton
        Left = 8
        Top = 56
        Width = 121
        Height = 25
        Caption = 'Join'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Showcard Gothic'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        OnClick = JoinButtonClick
      end
    end
  end
  object Menu: TMainMenu
    object Game1: TMenuItem
      Caption = 'Game'
      object Host1: TMenuItem
        Caption = 'Host'
        ShortCut = 16456
        OnClick = Host1Click
      end
      object Join1: TMenuItem
        Caption = 'Join'
        ShortCut = 16458
        OnClick = Join1Click
      end
      object EndGame1: TMenuItem
        Caption = 'End Game'
        Enabled = False
        ShortCut = 16472
        OnClick = EndGame1Click
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Quit1: TMenuItem
        Caption = 'Quit'
        ShortCut = 32883
        OnClick = Quit1Click
      end
    end
  end
  object HostTimer: TTimer
    Enabled = False
    Interval = 1
    OnTimer = HostTimerTimer
    Left = 32
  end
  object ClientTimer: TTimer
    Enabled = False
    Interval = 1
    OnTimer = ClientTimerTimer
    Left = 64
  end
end
