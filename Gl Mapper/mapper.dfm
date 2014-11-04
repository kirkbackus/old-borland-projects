object FormMapper: TFormMapper
  Left = 195
  Top = 113
  Width = 640
  Height = 450
  HorzScrollBar.Smooth = True
  HorzScrollBar.Visible = False
  VertScrollBar.Smooth = True
  VertScrollBar.Visible = False
  Caption = 'Simple Mapper'
  Color = clBtnFace
  Constraints.MinHeight = 450
  Constraints.MinWidth = 361
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object ViewerBox: TGroupBox
    Left = 8
    Top = 8
    Width = 337
    Height = 265
    Caption = 'Viewer Box'
    TabOrder = 0
    object ViewBox: TScrollBox
      Left = 8
      Top = 16
      Width = 321
      Height = 239
      Color = clWhite
      Ctl3D = False
      ParentColor = False
      ParentCtl3D = False
      TabOrder = 0
    end
  end
  object ShapePDisk: TScrollBox
    Left = 0
    Top = 281
    Width = 632
    Height = 96
    Align = alBottom
    BorderStyle = bsNone
    Color = clActiveCaption
    Ctl3D = True
    ParentColor = False
    ParentCtl3D = False
    TabOrder = 1
    object ShapeBox: TGroupBox
      Left = 8
      Top = 0
      Width = 297
      Height = 89
      Align = alCustom
      Caption = 'Shapes'
      TabOrder = 0
      object ShapeCylinder: TSpeedButton
        Left = 80
        Top = 16
        Width = 65
        Height = 65
        GroupIndex = 1
        Caption = 'Cylinder'
        Flat = True
        OnClick = ShapeCylinderClick
      end
      object ShapeDisk: TSpeedButton
        Left = 152
        Top = 16
        Width = 65
        Height = 65
        GroupIndex = 1
        Caption = 'Disk'
        Flat = True
        OnClick = ShapeDiskClick
      end
      object ShapeSphere: TSpeedButton
        Left = 8
        Top = 16
        Width = 65
        Height = 65
        GroupIndex = 1
        Down = True
        Caption = 'Sphere'
        Flat = True
        OnClick = ShapeSphereClick
      end
      object SpeedButton3: TSpeedButton
        Left = 224
        Top = 16
        Width = 65
        Height = 65
        GroupIndex = 1
        Caption = 'Partial Disk'
        Flat = True
        OnClick = SpeedButton3Click
      end
    end
  end
  object ScrollBox1: TScrollBox
    Left = 353
    Top = 0
    Width = 279
    Height = 281
    Align = alRight
    BorderStyle = bsNone
    Color = clActiveCaption
    Ctl3D = False
    ParentColor = False
    ParentCtl3D = False
    TabOrder = 2
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 377
    Width = 632
    Height = 19
    Panels = <>
    SimplePanel = False
  end
  object MainMenu: TMainMenu
    Left = 352
    Top = 8
    object F1: TMenuItem
      Caption = 'File'
      object Restart1: TMenuItem
        Caption = 'Restart'
        ShortCut = 16466
        OnClick = Restart1Click
      end
      object Quit1: TMenuItem
        Caption = 'Quit'
        ShortCut = 16465
        OnClick = Quit1Click
      end
    end
    object View1: TMenuItem
      Caption = 'View'
      object SetBackgroundColor1: TMenuItem
        Caption = 'Set Background Color'
        ShortCut = 16450
        OnClick = SetBackgroundColor1Click
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object EnableLighting1: TMenuItem
        Caption = 'Lighting Enabled'
        Checked = True
        ShortCut = 16460
        OnClick = EnableLighting1Click
      end
      object N01: TMenuItem
        Caption = '-'
      end
      object SmoothShading1: TMenuItem
        Caption = 'Smooth Shading'
        Checked = True
        GroupIndex = 1
        RadioItem = True
        OnClick = SmoothShading1Click
      end
      object FlatShading1: TMenuItem
        Caption = 'Flat Shading'
        GroupIndex = 1
        RadioItem = True
        OnClick = FlatShading1Click
      end
    end
    object Texture1: TMenuItem
      Caption = 'Texture'
      object Load1: TMenuItem
        Caption = 'Load'
        ShortCut = 16460
        OnClick = Load1Click
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Nearest1: TMenuItem
        Caption = 'Nearest'
        GroupIndex = 1
        RadioItem = True
        OnClick = Nearest1Click
      end
      object Linear1: TMenuItem
        Caption = 'Linear'
        Checked = True
        GroupIndex = 1
        RadioItem = True
        OnClick = Linear1Click
      end
    end
  end
  object TextureDialog: TOpenPictureDialog
    Filter = 'Bitmaps (*.bmp)|*.bmp'
    Left = 352
    Top = 40
  end
  object KeyTimer: TTimer
    Interval = 10
    OnTimer = KeyTimerTimer
    Left = 352
    Top = 72
  end
  object BgColorDialog: TColorDialog
    Ctl3D = True
    Left = 352
    Top = 104
  end
end
