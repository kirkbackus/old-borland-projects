object Form1: TForm1
  Left = 198
  Top = 124
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Happy Face'
  ClientHeight = 321
  ClientWidth = 397
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 8
    Top = 0
    Width = 209
    Height = 225
    Caption = 'Smiley Face Guy'
    TabOrder = 0
    object Shape8: TShape
      Left = 8
      Top = 16
      Width = 193
      Height = 169
      Brush.Color = clNavy
      Pen.Style = psClear
      Shape = stEllipse
    end
    object Shape1: TShape
      Left = 8
      Top = 32
      Width = 193
      Height = 185
      Brush.Color = clYellow
      Shape = stCircle
    end
    object Shape2: TShape
      Left = 48
      Top = 64
      Width = 57
      Height = 57
      Shape = stCircle
    end
    object Shape3: TShape
      Left = 104
      Top = 64
      Width = 57
      Height = 57
      Shape = stCircle
    end
    object Shape4: TShape
      Left = 64
      Top = 80
      Width = 25
      Height = 25
      Brush.Color = clBlack
      Shape = stCircle
    end
    object Shape5: TShape
      Left = 120
      Top = 80
      Width = 25
      Height = 25
      Brush.Color = clBlack
      Shape = stCircle
    end
    object Shape6: TShape
      Left = 90
      Top = 119
      Width = 33
      Height = 33
      Brush.Color = clBlack
      Shape = stCircle
    end
    object Shape7: TShape
      Left = 93
      Top = 118
      Width = 33
      Height = 33
      Brush.Color = clYellow
      Pen.Style = psClear
      Shape = stCircle
    end
    object Shape9: TShape
      Left = 40
      Top = 24
      Width = 129
      Height = 41
      Brush.Color = clNavy
      Pen.Style = psClear
      Shape = stEllipse
    end
    object DirectSS1: TDirectSS
      Left = 48
      Top = 158
      Width = 113
      Height = 59
      TabOrder = 0
      ControlData = {
        02020000AE0B0000190600000200000002000000020000000200640002000000
        0200F4000200E600020096000200010002000100020001000200010002000000}
    end
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 232
    Width = 209
    Height = 81
    Caption = 'Type your Sentence Here!'
    TabOrder = 1
    object Edit1: TEdit
      Left = 8
      Top = 20
      Width = 193
      Height = 21
      TabOrder = 0
      Text = 'My name is happy face!'
    end
    object Button1: TButton
      Left = 8
      Top = 48
      Width = 193
      Height = 25
      Caption = 'Say It!'
      TabOrder = 1
      OnClick = Button1Click
    end
  end
  object GroupBox3: TGroupBox
    Left = 224
    Top = 0
    Width = 169
    Height = 273
    Caption = 'Options'
    TabOrder = 2
    object Label2: TLabel
      Left = 12
      Top = 16
      Width = 69
      Height = 13
      Caption = 'Voice Selector'
    end
    object Label1: TLabel
      Left = 16
      Top = 136
      Width = 61
      Height = 13
      Caption = 'Voice Speed'
    end
    object Label3: TLabel
      Left = 12
      Top = 184
      Width = 54
      Height = 13
      Caption = 'Voice Pitch'
    end
    object Label4: TLabel
      Left = 8
      Top = 256
      Width = 77
      Height = 13
      Caption = 'Current Speaker'
    end
    object Bevel1: TBevel
      Left = 8
      Top = 232
      Width = 153
      Height = 9
      Shape = bsTopLine
    end
    object Label5: TLabel
      Left = 8
      Top = 240
      Width = 93
      Height = 13
      Caption = 'Current Speaker'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object ListBox1: TListBox
      Left = 8
      Top = 32
      Width = 145
      Height = 97
      ItemHeight = 13
      TabOrder = 0
      OnClick = ListBox1Click
    end
    object TrackBar1: TTrackBar
      Left = 8
      Top = 152
      Width = 153
      Height = 25
      Max = 510
      Min = 30
      Orientation = trHorizontal
      Frequency = 0
      Position = 170
      SelEnd = 0
      SelStart = 0
      TabOrder = 1
      TickMarks = tmBottomRight
      TickStyle = tsNone
      OnChange = TrackBar1Change
    end
    object TrackBar2: TTrackBar
      Left = 8
      Top = 200
      Width = 153
      Height = 25
      Max = 337
      Min = 84
      Orientation = trHorizontal
      Frequency = 0
      Position = 169
      SelEnd = 0
      SelStart = 0
      TabOrder = 2
      TickMarks = tmBottomRight
      TickStyle = tsNone
      OnChange = TrackBar2Change
    end
  end
  object GroupBox4: TGroupBox
    Left = 224
    Top = 280
    Width = 169
    Height = 33
    Caption = 'For more games/programs go to'
    TabOrder = 3
    object Label6: TLabel
      Left = 7
      Top = 14
      Width = 119
      Height = 13
      Caption = 'http://www.LLgames.net'
    end
  end
  object Timer1: TTimer
    Interval = 1
  end
end
