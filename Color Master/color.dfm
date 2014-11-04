object MColor: TMColor
  Left = 199
  Top = 124
  BorderStyle = bsDialog
  Caption = 'Color Master'
  ClientHeight = 207
  ClientWidth = 320
  Color = clBtnFace
  DefaultMonitor = dmDesktop
  DragMode = dmAutomatic
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poDesktopCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Color: TShape
    Left = 8
    Top = 8
    Width = 121
    Height = 137
    OnMouseDown = ColorMouseDown
  end
  object Bevel1: TBevel
    Left = 132
    Top = 8
    Width = 181
    Height = 137
  end
  object Label1: TLabel
    Left = 136
    Top = 16
    Width = 23
    Height = 13
    Caption = 'Red:'
  end
  object Label2: TLabel
    Left = 136
    Top = 56
    Width = 32
    Height = 13
    Caption = 'Green:'
  end
  object Label3: TLabel
    Left = 136
    Top = 96
    Width = 24
    Height = 13
    Caption = 'Blue:'
  end
  object Bevel2: TBevel
    Left = 8
    Top = 152
    Width = 121
    Height = 49
  end
  object Label4: TLabel
    Left = 16
    Top = 160
    Width = 90
    Height = 13
    Caption = 'Hexidecimal Value:'
  end
  object Bevel3: TBevel
    Left = 136
    Top = 152
    Width = 177
    Height = 49
  end
  object Edit1: TEdit
    Left = 136
    Top = 32
    Width = 25
    Height = 21
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    MaxLength = 3
    ParentFont = False
    TabOrder = 0
    Text = '255'
    OnChange = Edit1Change
  end
  object Edit2: TEdit
    Left = 136
    Top = 72
    Width = 25
    Height = 21
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    MaxLength = 3
    ParentFont = False
    TabOrder = 1
    Text = '255'
    OnChange = Edit2Change
  end
  object Edit3: TEdit
    Left = 136
    Top = 112
    Width = 25
    Height = 21
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    MaxLength = 3
    ParentFont = False
    TabOrder = 2
    Text = '255'
    OnChange = Edit3Change
  end
  object RedBar: TTrackBar
    Left = 160
    Top = 32
    Width = 150
    Height = 25
    Max = 255
    Orientation = trHorizontal
    ParentShowHint = False
    Frequency = 1
    Position = 255
    SelEnd = 0
    SelStart = 0
    ShowHint = False
    TabOrder = 3
    TickMarks = tmBottomRight
    TickStyle = tsNone
    OnChange = RedBarChange
  end
  object GreenBar: TTrackBar
    Left = 160
    Top = 72
    Width = 150
    Height = 25
    Max = 255
    Orientation = trHorizontal
    ParentShowHint = False
    Frequency = 1
    Position = 255
    SelEnd = 0
    SelStart = 0
    ShowHint = False
    TabOrder = 4
    TickMarks = tmBottomRight
    TickStyle = tsNone
    OnChange = GreenBarChange
  end
  object BlueBar: TTrackBar
    Left = 160
    Top = 112
    Width = 150
    Height = 25
    Max = 255
    Orientation = trHorizontal
    ParentShowHint = False
    Frequency = 1
    Position = 255
    SelEnd = 0
    SelStart = 0
    ShowHint = False
    TabOrder = 5
    TickMarks = tmBottomRight
    TickStyle = tsNone
    OnChange = BlueBarChange
  end
  object Hex: TEdit
    Left = 16
    Top = 176
    Width = 105
    Height = 21
    ReadOnly = True
    TabOrder = 6
  end
  object ScreenCol: TButton
    Left = 137
    Top = 153
    Width = 175
    Height = 47
    Caption = 'Get Color off Screen'
    TabOrder = 7
    OnClick = ScreenColClick
  end
  object Timer1: TTimer
    Interval = 10
    OnTimer = Timer1Timer
  end
  object ColorDialog1: TColorDialog
    Ctl3D = True
    Color = clRed
    CustomColors.Strings = (
      'ColorA=FFFFFFFF'
      'ColorB=FFFFFFFF'
      'ColorC=FFFFFFFF'
      'ColorD=FFFFFFFF'
      'ColorE=FFFFFFFF'
      'ColorF=FFFFFFFF'
      'ColorG=FFFFFFFF'
      'ColorH=FFFFFFFF'
      'ColorI=FFFFFFFF'
      'ColorJ=FFFFFFFF'
      'ColorK=FFFFFFFF'
      'ColorL=FFFFFFFF'
      'ColorM=FFFFFFFF'
      'ColorN=FFFFFFFF'
      'ColorO=FFFFFFFF'
      'ColorP=FFFFFFFF')
    Options = [cdFullOpen, cdSolidColor, cdAnyColor]
    Left = 32
  end
end
