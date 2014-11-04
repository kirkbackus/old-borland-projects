object Form1: TForm1
  Left = 192
  Top = 113
  BorderStyle = bsToolWindow
  Caption = 'Music Player Test'
  ClientHeight = 120
  ClientWidth = 457
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
  object MusicPlay: TGroupBox
    Left = 8
    Top = 0
    Width = 137
    Height = 113
    Caption = 'Music Player'
    TabOrder = 0
    object Button1: TButton
      Left = 8
      Top = 16
      Width = 121
      Height = 57
      Caption = 'Play Song'
      TabOrder = 0
      OnClick = Button1Click
    end
    object Instruments: TComboBox
      Left = 8
      Top = 84
      Width = 121
      Height = 21
      ItemHeight = 13
      TabOrder = 1
      Text = 'Instruments'
      OnChange = InstrumentsChange
      Items.Strings = (
        'Acoustic Grand Piano'
        'Bright Acoustic Piano'
        'Electric Grand Piano'
        'Honky-tonk Piano'
        'Electric Piano 1'
        'Electric Piano 2'
        'Harpsichord'
        'Clavi'
        'Celesta'
        'Glockenspiel'
        'Music Box'
        'Vibraphone'
        'Marimba'
        'Xylophone'
        'Tubular Bells'
        'Dulcimer'
        'Drawbar Organ'
        'Percussive Organ'
        'Rock Organ'
        'Church Organ'
        'Reed Organ'
        'Accordion'
        'Harmonica                      '
        'Tango Accordion'
        'Acoustic Guitar (nylon)'
        'Acoustic Guitar (steel)'
        'Electric Guitar (jazz)'
        'Electric Guitar (clean)'
        'Electric Guitar (muted)'
        'Overdriven Guitar'
        'Distortion Guitar'
        'Guitar harmonics'
        'Acoustic Bass'
        'Electric Bass (finger)'
        'Electric Bass (pick)'
        'Fretless Bass'
        'Slap Bass 1'
        'Slap Bass 2'
        'Synth Bass 1'
        'Synth Bass 2'
        'Violin'
        'Viola'
        'Cello'
        'Contrabass'
        'Tremolo Strings'
        'Pizzicato Strings'
        'Orchestral Harp'
        'Timpani'
        'String Ensemble 1'
        'String Ensemble 2'
        'SynthStrings 1'
        'SynthStrings 2'
        'Choir Aahs'
        'Voice Oohs'
        'Synth Voice'
        'Orchestra Hit'
        'Trumpet'
        'Trombone'
        'Tuba'
        'Muted Trumpet'
        'French Horn'
        'Brass Section'
        'SynthBrass 1'
        'SynthBrass 2'
        'Soprano Sax'
        'Alto Sax'
        'Tenor Sax'
        'Baritone Sax'
        'Oboe'
        'English Horn'
        'Bassoon'
        'Clarinet'
        'Piccolo'
        'Flute'
        'Recorder'
        'Pan Flute'
        'Blown Bottle'
        'Shakuhachi'
        'Whistle'
        'Ocarina'
        'Lead 1 (square)'
        'Lead 2 (sawtooth)'
        'Lead 3 (calliope)'
        'Lead 4 (chiff)'
        'Lead 5 (charang)'
        'Lead 6 (voice)'
        'Lead 7 (fifths)'
        'Lead 8 (bass + lead)'
        'Pad 1 (new age)'
        'Pad 2 (warm)'
        'Pad 3 (polysynth)'
        'Pad 4 (choir)'
        'Pad 5 (bowed)'
        'Pad 6 (metallic)'
        'Pad 7 (halo)'
        'Pad 8 (sweep)'
        'FX 1 (rain)'
        'FX 2 (soundtrack)'
        'FX 3 (crystal)'
        'FX 4 (atmosphere)'
        'FX 5 (brightness)'
        'FX 6 (goblins)'
        'FX 7 (echoes)'
        'FX 8 (sci-fi)'
        'Sitar'
        'Banjo'
        'Shamisen'
        'Koto'
        'Kalimba'
        'Bag pipe'
        'Fiddle'
        'Shanai'
        'Tinkle Bell'
        'Agogo'
        'Steel Drums'
        'Woodblock'
        'Taiko Drum'
        'Melodic Tom'
        'Synth Drum'
        'Reverse Cymbal'
        'Guitar Fret Noise'
        'Breath Noise'
        'Seashore'
        'Bird Tweet'
        'Telephone Ring'
        'Helicopter'
        'Applause'
        'Gunshot')
    end
  end
  object Debug: TGroupBox
    Left = 152
    Top = 0
    Width = 105
    Height = 113
    Caption = 'Debug'
    TabOrder = 1
    object Note: TLabel
      Left = 9
      Top = 32
      Width = 23
      Height = 13
      Caption = 'Note'
    end
    object NotesCap: TLabel
      Left = 8
      Top = 16
      Width = 63
      Height = 13
      Caption = 'Note Playing:'
    end
    object Button2: TButton
      Left = 8
      Top = 56
      Width = 89
      Height = 49
      Caption = 'Silence Notes'
      TabOrder = 0
      OnClick = Button2Click
    end
  end
  object Control: TGroupBox
    Left = 264
    Top = 0
    Width = 185
    Height = 113
    Caption = 'Music Control'
    TabOrder = 2
    object VolCap: TLabel
      Left = 8
      Top = 16
      Width = 82
      Height = 13
      Caption = 'Volume Controller'
    end
    object Volume: TTrackBar
      Left = 8
      Top = 32
      Width = 169
      Height = 33
      Max = 65025
      Orientation = trHorizontal
      Frequency = 1
      Position = 65025
      SelEnd = 0
      SelStart = 0
      TabOrder = 0
      TickMarks = tmBottomRight
      TickStyle = tsNone
      OnChange = VolumeChange
    end
    object Stop: TButton
      Left = 8
      Top = 64
      Width = 169
      Height = 41
      Caption = 'Stop Song'
      TabOrder = 1
      OnClick = StopClick
    end
  end
  object SongTimer: TTimer
    Enabled = False
    Interval = 5
    OnTimer = SongTimerTimer
  end
end
