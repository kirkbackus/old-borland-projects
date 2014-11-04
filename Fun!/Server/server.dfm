object Fun: TFun
  Left = 237
  Top = 124
  Width = 320
  Height = 102
  Caption = 'Fun Server'
  Color = clBtnFace
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
  object Label1: TLabel
    Left = 16
    Top = 8
    Width = 32
    Height = 13
    Caption = 'Label1'
  end
  object FunServer: TServerSocket
    Active = False
    Port = 12000
    ServerType = stNonBlocking
    OnClientRead = FunServerClientRead
  end
  object Timer1: TTimer
    Interval = 1
    OnTimer = Timer1Timer
    Left = 32
  end
end
