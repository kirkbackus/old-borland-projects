object MyGammaForm: TMyGammaForm
  Left = 192
  Top = 115
  BorderIcons = [biSystemMenu, biMinimize, biHelp]
  BorderStyle = bsNone
  Caption = 'My Gamma Control'
  ClientHeight = 80
  ClientWidth = 338
  Color = clBlack
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 56
    Width = 32
    Height = 13
    Caption = 'Darker'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 16
    Top = 8
    Width = 58
    Height = 13
    Caption = 'Set Gamma:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWhite
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 288
    Top = 56
    Width = 36
    Height = 13
    Caption = 'Brighter'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clYellow
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label4: TLabel
    Left = 152
    Top = 56
    Width = 33
    Height = 13
    Caption = 'Normal'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWhite
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Shape1: TShape
    Left = 313
    Top = 0
    Width = 25
    Height = 25
    Brush.Color = clRed
    Pen.Color = clRed
    OnMouseDown = Shape1MouseDown
  end
  object GammaBar: TTrackBar
    Left = 8
    Top = 24
    Width = 321
    Height = 25
    BorderWidth = 1
    Ctl3D = False
    Max = 255
    Orientation = trHorizontal
    ParentCtl3D = False
    PageSize = 1
    Frequency = 1
    Position = 128
    SelEnd = 0
    SelStart = 0
    TabOrder = 0
    TickMarks = tmBottomRight
    TickStyle = tsNone
    OnChange = GammaBarChange
  end
  object TrayIcon1: TTrayIcon
    Visible = True
    Hide = True
    RestoreOn = imDoubleClick
    PopupMenuOn = imNone
    OnClick = TrayIcon1Click
  end
  object VisibleTimer: TTimer
    OnTimer = VisibleTimerTimer
    Left = 32
  end
end
