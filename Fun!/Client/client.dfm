object Form1: TForm1
  Left = 194
  Top = 115
  Width = 457
  Height = 187
  Caption = 'Fun! Client'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 264
    Top = 8
    Width = 177
    Height = 137
    Caption = 'Screen Direction'
    TabOrder = 0
    object Button4: TButton
      Left = 16
      Top = 48
      Width = 49
      Height = 49
      Caption = 'Left'
      TabOrder = 3
      OnClick = Button4Click
    end
    object Button1: TButton
      Left = 64
      Top = 24
      Width = 49
      Height = 49
      Caption = 'Up'
      TabOrder = 0
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 64
      Top = 72
      Width = 49
      Height = 49
      Caption = 'Down'
      TabOrder = 1
      OnClick = Button2Click
    end
    object Button3: TButton
      Left = 112
      Top = 48
      Width = 49
      Height = 49
      Caption = 'Right'
      TabOrder = 2
      OnClick = Button3Click
    end
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 8
    Width = 249
    Height = 137
    Caption = 'Send Message'
    TabOrder = 1
    object Message: TEdit
      Left = 8
      Top = 16
      Width = 233
      Height = 21
      TabOrder = 0
      Text = 'Type Your Message Here!'
    end
    object Send: TButton
      Left = 8
      Top = 48
      Width = 235
      Height = 81
      Caption = 'Send'
      TabOrder = 1
      OnClick = SendClick
    end
  end
  object FunClient: TClientSocket
    Active = False
    ClientType = ctNonBlocking
    Host = '192.168.2.102'
    Port = 12000
  end
end
