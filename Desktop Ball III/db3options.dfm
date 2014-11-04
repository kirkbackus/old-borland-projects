object FormOptions: TFormOptions
  Left = 346
  Top = 170
  Width = 390
  Height = 366
  Caption = 'FormOptions'
  Color = clCream
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label3: TLabel
    Left = 16
    Top = 208
    Width = 34
    Height = 13
    Caption = 'Friction'
  end
  object ScrollBox1: TScrollBox
    Left = 0
    Top = 0
    Width = 382
    Height = 41
    HorzScrollBar.Visible = False
    VertScrollBar.Visible = False
    Align = alTop
    Color = 16750899
    Ctl3D = False
    ParentColor = False
    ParentCtl3D = False
    TabOrder = 0
    object LTitle: TLabel
      Left = 0
      Top = 0
      Width = 380
      Height = 39
      Align = alClient
      Alignment = taCenter
      Caption = 'Options'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -32
      Font.Name = 'Charlemagne Std'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object DBallStatus: TStatusBar
    Left = 0
    Top = 313
    Width = 382
    Height = 19
    Panels = <
      item
        Text = 'Created by Kirk Backus'
        Width = 50
      end>
    SimplePanel = False
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 48
    Width = 169
    Height = 257
    Caption = 'Ball'#39's Properties'
    TabOrder = 2
    object LCollide: TLabel
      Left = 6
      Top = 24
      Width = 61
      Height = 13
      Caption = 'Collides With'
    end
    object LColor: TLabel
      Left = 8
      Top = 68
      Width = 24
      Height = 13
      Caption = 'Color'
    end
    object SColor: TShape
      Left = 8
      Top = 88
      Width = 145
      Height = 25
      Shape = stRoundRect
      OnMouseDown = SColorMouseDown
    end
    object Label1: TLabel
      Left = 8
      Top = 120
      Width = 34
      Height = 13
      Caption = 'Friction'
    end
    object Label2: TLabel
      Left = 8
      Top = 208
      Width = 65
      Height = 13
      Caption = 'Transparency'
    end
    object Label4: TLabel
      Left = 8
      Top = 160
      Width = 33
      Height = 13
      Caption = 'Gravity'
    end
    object CollideOption: TComboBox
      Left = 8
      Top = 40
      Width = 145
      Height = 21
      ItemHeight = 13
      TabOrder = 0
      Text = 'Windows'
      OnChange = CollideOptionChange
      Items.Strings = (
        'Windows'
        'Nothing')
    end
    object TransBar: TTrackBar
      Left = 8
      Top = 224
      Width = 150
      Height = 25
      LineSize = 0
      Max = 254
      Orientation = trHorizontal
      Frequency = 1
      Position = 1
      SelEnd = 0
      SelStart = 0
      TabOrder = 1
      TickMarks = tmBoth
      TickStyle = tsNone
      OnChange = TransBarChange
    end
    object FrictionBar: TTrackBar
      Left = 8
      Top = 136
      Width = 150
      Height = 25
      LineSize = 0
      Orientation = trHorizontal
      Frequency = 1
      Position = 3
      SelEnd = 0
      SelStart = 0
      TabOrder = 2
      TickMarks = tmBoth
      TickStyle = tsNone
      OnChange = FrictionBarChange
    end
  end
  object GroupBox2: TGroupBox
    Left = 184
    Top = 48
    Width = 193
    Height = 73
    Caption = 'Ball Data'
    TabOrder = 3
    object LPosition: TLabel
      Left = 8
      Top = 24
      Width = 43
      Height = 13
      Caption = 'LPosition'
    end
    object LVelocity: TLabel
      Left = 8
      Top = 40
      Width = 43
      Height = 13
      Caption = 'LVelocity'
    end
  end
  object GravBar: TTrackBar
    Left = 16
    Top = 224
    Width = 150
    Height = 25
    LineSize = 0
    Max = 20
    Orientation = trHorizontal
    Frequency = 1
    Position = 10
    SelEnd = 0
    SelStart = 0
    TabOrder = 4
    TickMarks = tmBoth
    TickStyle = tsNone
    OnChange = GravBarChange
  end
  object GroupBox3: TGroupBox
    Left = 184
    Top = 128
    Width = 193
    Height = 177
    Caption = 'Extra Options'
    TabOrder = 5
    object QuitBtn: TButton
      Left = 8
      Top = 144
      Width = 177
      Height = 25
      Caption = 'Quit Desktop Ball III'
      TabOrder = 0
      OnClick = QuitBtnClick
    end
  end
  object BallColor: TColorDialog
    Ctl3D = True
  end
end
