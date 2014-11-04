object MainForm: TMainForm
  Left = 274
  Top = 159
  Width = 812
  Height = 563
  Caption = 'Game Boy Advance IDE'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIForm
  Menu = MainMenu1
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object HSplit: TSplitter
    Left = 121
    Top = 0
    Width = 3
    Height = 381
    Cursor = crHSplit
    Beveled = True
  end
  object VSplit: TSplitter
    Left = 0
    Top = 381
    Width = 804
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    Beveled = True
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 490
    Width = 804
    Height = 19
    Panels = <
      item
        Alignment = taCenter
        Text = 'GBA IDE Created by Kirk Backus'
        Width = 164
      end
      item
        Alignment = taCenter
        Text = 'LLgames.net'
        Width = 128
      end
      item
        Alignment = taCenter
        Text = 'Last Level Games'
        Width = 128
      end>
    SimplePanel = False
  end
  object CWBox: TScrollBox
    Left = 0
    Top = 384
    Width = 804
    Height = 106
    Align = alBottom
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 1
    object CompilerWindow: TRichEdit
      Left = 0
      Top = 0
      Width = 802
      Height = 104
      Align = alClient
      BevelInner = bvNone
      BevelOuter = bvNone
      Ctl3D = True
      ParentCtl3D = False
      ReadOnly = True
      ScrollBars = ssVertical
      TabOrder = 0
    end
  end
  object TreeView1: TTreeView
    Left = 0
    Top = 0
    Width = 121
    Height = 381
    Align = alLeft
    Ctl3D = False
    Indent = 19
    ParentCtl3D = False
    TabOrder = 2
  end
  object MainMenu1: TMainMenu
    object File1: TMenuItem
      Caption = 'File'
      object New1: TMenuItem
        AutoCheck = True
        Caption = 'New'
        ShortCut = 16462
      end
      object Save1: TMenuItem
        Caption = 'Save Project'
        ShortCut = 16467
      end
      object SaveProjectAs1: TMenuItem
        Caption = 'Save Project As...'
        ShortCut = 16449
      end
      object Open1: TMenuItem
        Caption = 'Open'
        ShortCut = 16463
      end
      object Quit1: TMenuItem
        Caption = 'Quit'
        OnClick = Quit1Click
      end
    end
    object Program1: TMenuItem
      Caption = 'Program'
      object Compile1: TMenuItem
        Caption = 'Compile'
        OnClick = Compile1Click
      end
      object Run1: TMenuItem
        Caption = 'Run'
      end
    end
  end
end
