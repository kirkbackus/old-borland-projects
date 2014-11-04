object CodeForm: TCodeForm
  Left = 300
  Top = 210
  Width = 574
  Height = 439
  Caption = 'Code Window'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  PixelsPerInch = 96
  TextHeight = 13
  object CodeBox: TSynEdit
    Left = 0
    Top = 0
    Width = 566
    Height = 405
    Align = alClient
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    TabOrder = 0
    Gutter.Font.Charset = DEFAULT_CHARSET
    Gutter.Font.Color = clWindowText
    Gutter.Font.Height = -11
    Gutter.Font.Name = 'Courier New'
    Gutter.Font.Style = []
  end
  object CppLexer: TSynCppSyn
    CommentAttri.Foreground = clGreen
    DirecAttri.Foreground = clGreen
    StringAttri.Foreground = clNavy
    CharAttri.Foreground = clNavy
    Left = 8
    Top = 8
  end
end
