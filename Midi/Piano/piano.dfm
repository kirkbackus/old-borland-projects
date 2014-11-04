object Form1: TForm1
  Left = 195
  Top = 113
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Simple Piano'
  ClientHeight = 165
  ClientWidth = 721
  Color = clBtnFace
  DefaultMonitor = dmDesktop
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object white1: TShape
    Left = 0
    Top = 0
    Width = 49
    Height = 145
    OnMouseDown = white1MouseDown
    OnMouseUp = white1MouseUp
  end
  object white2: TShape
    Left = 48
    Top = 0
    Width = 49
    Height = 145
    OnMouseDown = white2MouseDown
    OnMouseUp = white2MouseUp
  end
  object black1: TShape
    Left = 32
    Top = 0
    Width = 33
    Height = 81
    Brush.Color = clBlack
    OnMouseDown = black1MouseDown
    OnMouseUp = black1MouseUp
  end
  object white3: TShape
    Left = 96
    Top = 0
    Width = 49
    Height = 145
    OnMouseDown = white3MouseDown
    OnMouseUp = white3MouseUp
  end
  object white4: TShape
    Left = 144
    Top = 0
    Width = 49
    Height = 145
    OnMouseDown = white4MouseDown
    OnMouseUp = white4MouseUp
  end
  object black2: TShape
    Left = 80
    Top = 0
    Width = 33
    Height = 81
    Brush.Color = clBlack
    OnMouseDown = black2MouseDown
    OnMouseUp = black2MouseUp
  end
  object white5: TShape
    Left = 192
    Top = 0
    Width = 49
    Height = 145
    OnMouseDown = white5MouseDown
    OnMouseUp = white5MouseUp
  end
  object black3: TShape
    Left = 176
    Top = 0
    Width = 33
    Height = 81
    Brush.Color = clBlack
    OnMouseDown = black3MouseDown
    OnMouseUp = black3MouseUp
  end
  object white6: TShape
    Left = 240
    Top = 0
    Width = 49
    Height = 145
    OnMouseDown = white6MouseDown
    OnMouseUp = white6MouseUp
  end
  object white7: TShape
    Left = 288
    Top = 0
    Width = 49
    Height = 145
    OnMouseDown = white7MouseDown
    OnMouseUp = white7MouseUp
  end
  object white8: TShape
    Left = 336
    Top = 0
    Width = 49
    Height = 145
    OnMouseDown = white8MouseDown
    OnMouseUp = white8MouseUp
  end
  object white9: TShape
    Left = 384
    Top = 0
    Width = 49
    Height = 145
    OnMouseDown = white9MouseDown
    OnMouseUp = white9MouseUp
  end
  object white10: TShape
    Left = 432
    Top = 0
    Width = 49
    Height = 145
    OnMouseDown = white10MouseDown
    OnMouseUp = white10MouseUp
  end
  object white11: TShape
    Left = 480
    Top = 0
    Width = 49
    Height = 145
    OnMouseDown = white11MouseDown
    OnMouseUp = white11MouseUp
  end
  object white12: TShape
    Left = 528
    Top = 0
    Width = 49
    Height = 145
    OnMouseDown = white12MouseDown
    OnMouseUp = white12MouseUp
  end
  object white13: TShape
    Left = 576
    Top = 0
    Width = 49
    Height = 145
    OnMouseDown = white13MouseDown
    OnMouseUp = white13MouseUp
  end
  object white14: TShape
    Left = 624
    Top = 0
    Width = 49
    Height = 145
    OnMouseDown = white14MouseDown
    OnMouseUp = white14MouseUp
  end
  object black4: TShape
    Left = 224
    Top = 0
    Width = 33
    Height = 81
    Brush.Color = clBlack
    OnMouseDown = black4MouseDown
    OnMouseUp = black4MouseUp
  end
  object black5: TShape
    Left = 272
    Top = 0
    Width = 33
    Height = 81
    Brush.Color = clBlack
    OnMouseDown = black5MouseDown
    OnMouseUp = black5MouseUp
  end
  object black6: TShape
    Left = 368
    Top = 0
    Width = 33
    Height = 81
    Brush.Color = clBlack
    OnMouseDown = black6MouseDown
    OnMouseUp = black6MouseUp
  end
  object black7: TShape
    Left = 416
    Top = 0
    Width = 33
    Height = 81
    Brush.Color = clBlack
    OnMouseDown = black7MouseDown
    OnMouseUp = black7MouseUp
  end
  object black8: TShape
    Left = 512
    Top = 0
    Width = 33
    Height = 81
    Brush.Color = clBlack
    OnMouseDown = black8MouseDown
    OnMouseUp = black8MouseUp
  end
  object black9: TShape
    Left = 560
    Top = 0
    Width = 33
    Height = 81
    Brush.Color = clBlack
    OnMouseDown = black9MouseDown
    OnMouseUp = black9MouseUp
  end
  object black10: TShape
    Left = 608
    Top = 0
    Width = 33
    Height = 81
    Brush.Color = clBlack
    OnMouseDown = black10MouseDown
    OnMouseUp = black10MouseUp
  end
  object white15: TShape
    Left = 672
    Top = 0
    Width = 49
    Height = 145
    OnMouseDown = white15MouseDown
    OnMouseUp = white15MouseUp
  end
  object PianoStatus: TStatusBar
    Left = 0
    Top = 145
    Width = 429
    Height = 20
    Align = alCustom
    Panels = <
      item
        BiDiMode = bdLeftToRight
        ParentBiDiMode = False
        Text = 'Simple MIDI Piano Created by Kirk Backus'
        Width = 50
      end>
    SimplePanel = False
  end
  object Instrument: TComboBox
    Left = 430
    Top = 146
    Width = 193
    Height = 19
    BevelInner = bvNone
    Style = csOwnerDrawFixed
    DropDownCount = 32
    ImeMode = imDisable
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 2
    Text = 'acoustic grand piano'
    Items.Strings = (
      'acoustic grand piano'
      'bright acoustic piano'
      'electric grand piano'
      'honky-tonk piano'
      'electric piano 1'
      'electric piano 2'
      'harpsichord'
      'clavi'
      'celesta'
      'glockenspiel'
      'music box'
      'vibraphone'
      'marimba'
      'xylophone'
      'tubular bells'
      'dulcimer'
      'drawbar organ'
      'percussive organ'
      'rock organ'
      'church organ'
      'reed organ'
      'accordion'
      'harmonica                      '
      'tango accordion'
      'acoustic guitar (nylon)'
      'acoustic guitar (steel)'
      'electric guitar (jazz)'
      'electric guitar (clean)'
      'electric guitar (muted)'
      'overdriven guitar'
      'distortion guitar'
      'guitar harmonics'
      'acoustic bass'
      'electric bass (finger)'
      'electric bass (pick)'
      'fretless bass'
      'slap bass 1'
      'slap bass 2'
      'synth bass 1'
      'synth bass 2'
      'violin'
      'viola'
      'cello'
      'contrabass'
      'tremolo strings'
      'pizzicato strings'
      'orchestral harp'
      'timpani'
      'string ensemble 1'
      'string ensemble 2'
      'synthstrings 1'
      'synthstrings 2'
      'choir aahs'
      'voice oohs'
      'synth voice'
      'orchestra hit'
      'trumpet'
      'trombone'
      'tuba'
      'muted trumpet'
      'french horn'
      'brass section'
      'synthbrass 1'
      'synthbrass 2'
      'soprano sax'
      'alto sax'
      'tenor sax'
      'baritone sax'
      'oboe'
      'english horn'
      'bassoon'
      'clarinet'
      'piccolo'
      'flute'
      'recorder'
      'pan flute'
      'blown bottle'
      'shakuhachi'
      'whistle'
      'ocarina'
      'lead 1 (square)'
      'lead 2 (sawtooth)'
      'lead 3 (calliope)'
      'lead 4 (chiff)'
      'lead 5 (charang)'
      'lead 6 (voice)'
      'lead 7 (fifths)'
      'lead 8 (bass + lead)'
      'pad 1 (new age)'
      'pad 2 (warm)'
      'pad 3 (polysynth)'
      'pad 4 (choir)'
      'pad 5 (bowed)'
      'pad 6 (metallic)'
      'pad 7 (halo)'
      'pad 8 (sweep)'
      'fx 1 (rain)'
      'fx 2 (soundtrack)'
      'fx 3 (crystal)'
      'fx 4 (atmosphere)'
      'fx 5 (brightness)'
      'fx 6 (goblins)'
      'fx 7 (echoes)'
      'fx 8 (sci-fi)'
      'sitar'
      'banjo'
      'shamisen'
      'koto'
      'kalimba'
      'bag pipe'
      'fiddle'
      'shanai'
      'tinkle bell'
      'agogo'
      'steel drums'
      'woodblock'
      'taiko drum'
      'melodic tom'
      'synth drum'
      'reverse cymbal'
      'guitar fret noise'
      'breath noise'
      'seashore'
      'bird tweet'
      'telephone ring'
      'helicopter'
      'applause'
      'gunshot')
  end
  object Button1: TButton
    Left = 624
    Top = 144
    Width = 99
    Height = 22
    Caption = 'Set Instrument'
    TabOrder = 1
    OnClick = Button1Click
  end
  object MainMenu1: TMainMenu
    object P1: TMenuItem
      Caption = 'Piano'
      object Quit1: TMenuItem
        Caption = 'Quit'
        OnClick = Quit1Click
      end
    end
    object Help1: TMenuItem
      Caption = 'Help'
      object About1: TMenuItem
        Caption = 'About'
        OnClick = About1Click
      end
    end
  end
  object Timer1: TTimer
    Interval = 1
    OnTimer = Timer1Timer
    Left = 32
  end
end
