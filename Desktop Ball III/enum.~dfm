object BallForm: TBallForm
  Left = 196
  Top = 117
  BorderStyle = bsNone
  Caption = 'Desktop Ball III'
  ClientHeight = 285
  ClientWidth = 419
  Color = clFuchsia
  TransparentColor = True
  TransparentColorValue = clFuchsia
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object SBall: TShape
    Left = 0
    Top = 0
    Width = 64
    Height = 64
    Shape = stCircle
    OnMouseDown = SBallMouseDown
  end
  object BallTimer: TTimer
    Interval = 1
    OnTimer = BallTimerTimer
  end
  object WindowTimer: TTimer
    Interval = 50
    OnTimer = WindowTimerTimer
    Left = 32
  end
  object DBallTray: TTrayIcon
    Visible = True
    PopupMenu = TrayOptions
    Hide = True
    RestoreOn = imDoubleClick
    PopupMenuOn = imRightClickUp
    Left = 64
  end
  object ImageList1: TImageList
    Height = 32
    Top = 32
  end
  object TrayOptions: TPopupMenu
    Left = 96
    object ShowOptions1: TMenuItem
      Caption = 'Show Options'
      OnClick = ShowOptions1Click
    end
    object StopBall1: TMenuItem
      Caption = 'Stop Ball'
      OnClick = StopBall1Click
    end
    object N1: TMenuItem
      Caption = '-'
    end
    object Quit1: TMenuItem
      Caption = 'Quit'
      OnClick = Quit1Click
    end
  end
end
