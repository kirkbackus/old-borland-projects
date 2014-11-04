object OptionForm: TOptionForm
  Left = 187
  Top = 122
  BorderStyle = bsToolWindow
  Caption = 'Desktop Piano - Options'
  ClientHeight = 327
  ClientWidth = 266
  Color = clSkyBlue
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object LInstrument: TLabel
    Left = 8
    Top = 8
    Width = 249
    Height = 27
    Alignment = taCenter
    AutoSize = False
    Caption = 'Instruments'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Comic Sans MS'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LWindow: TLabel
    Left = 8
    Top = 200
    Width = 249
    Height = 19
    Alignment = taCenter
    AutoSize = False
    Caption = 'Window Properties'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Comic Sans MS'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LTrans: TLabel
    Left = 16
    Top = 232
    Width = 65
    Height = 13
    Caption = 'Transparency'
  end
  object Label1: TLabel
    Left = 8
    Top = 136
    Width = 249
    Height = 19
    Alignment = taCenter
    AutoSize = False
    Caption = 'Note Offset'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Comic Sans MS'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 16
    Top = 168
    Width = 35
    Height = 13
    Caption = 'Octave'
  end
  object InstrumentBox: TListBox
    Left = 8
    Top = 32
    Width = 249
    Height = 95
    BevelEdges = []
    BevelKind = bkFlat
    BevelOuter = bvRaised
    Color = clNavy
    Ctl3D = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWhite
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemHeight = 13
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
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 0
    OnClick = InstrumentBoxClick
  end
  object TransBar: TTrackBar
    Left = 8
    Top = 248
    Width = 249
    Height = 25
    Ctl3D = False
    Max = 254
    Orientation = trHorizontal
    ParentCtl3D = False
    Frequency = 1
    Position = 0
    SelEnd = 0
    SelStart = 0
    TabOrder = 1
    TickMarks = tmBoth
    TickStyle = tsNone
    OnChange = TransBarChange
  end
  object TBtnBox: TCheckBox
    Left = 16
    Top = 280
    Width = 241
    Height = 17
    Caption = 'Taskbar Button Enabled'
    Checked = True
    Ctl3D = False
    ParentCtl3D = False
    State = cbChecked
    TabOrder = 2
    OnClick = TBtnBoxClick
  end
  object Octave: TCSpinEdit
    Left = 56
    Top = 160
    Width = 49
    Height = 33
    AutoSize = False
    EditorEnabled = False
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Comic Sans MS'
    Font.Style = [fsBold]
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 3
    OnChange = OctaveChange
  end
end
