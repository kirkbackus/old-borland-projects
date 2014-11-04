//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "midi.h"
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int cnote = 0;
int cmax = 19;
String Notes[]={"A5","A5","A#5","G5","G5","A5","A#5","A#5","A5","G5","F5","D5",
"A5","A5","A#5","G5","G5","A5","F5"};
int interval[]={4,2,2,4,2,2,4,2,2,2,2,4,
4,2,2,4,2,4,12};
int delay = 200;

//--------------------------------------------------------------------------------|
//Midi Help                                                                       |
//--------------------------------------------------------------------------------|
//Note  0   |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |  9   |  10  |
//----------|------|------|------|------|------|------|------|------|------|------|
//C  -  0   |  12  |  24  |  36  |  48  |  60  |  72  |  84  |  96  | 108  | 120  |
//C# -  1   |  13  |  25  |  37  |  49  |  61  |  73  |  85  |  97  | 109  | 121  |
//D  -  2   |  14  |  26  |  38  |  50  |  62  |  74  |  86  |  98  | 110  | 122  |
//D# -  3   |  15  |  27  |  39  |  51  |  63  |  75  |  87  |  99  | 111  | 123  |
//E  -  4   |  16  |  28  |  40  |  52  |  64  |  76  |  88  | 100  | 112  | 124  |
//F  -  5   |  17  |  29  |  41  |  53  |  65  |  77  |  89  | 101  | 113  | 125  |
//F# -  6   |  18  |  30  |  42  |  54  |  66  |  78  |  90  | 102  | 114  | 126  |
//G  -  7   |  19  |  31  |  43  |  55  |  67  |  79  |  91  | 103  | 115  | 127  |
//G# -  8   |  20  |  32  |  44  |  56  |  68  |  80  |  92  | 104  | 116  |------|
//A  -  9   |  21  |  33  |  45  |  57  |  69  |  81  |  93  | 105  | 117  |
//A# -  10  |  22  |  34  |  46  |  58  |  70  |  82  |  94  | 106  | 118  |
//B  -  11  |  23  |  35  |  47  |  59  |  71  |  83  |  95  | 107  | 119  |
//-------------------------------------------------------------------------|
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
  //Initialize the midi controller
  MidiStart();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormDestroy(TObject *Sender)
{
  //Erase the midi controller from memory so it doesn't waste space
  MidiDestroy();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
  //Play Song
  SongTimer->Enabled = 1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SongTimerTimer(TObject *Sender)
{
  //Disable timer so we can change the interval
  SongTimer->Enabled=false;

  //If on last note, restart
  if (cmax == cnote)
  cnote = 0;

  //Stop all currently playing notes
  SilenceMidiNotes();
  //Plays the midi note
  PlayMidiNoteT(Notes[cnote]);

  //Set the Caption so you know what note you are playing
  Note->Caption=Notes[cnote];

  //Set the interval of the timer to wait till next note
  SongTimer->Interval = interval[cnote]*delay;

  //Set it to play the next note next time
  cnote++;

  //Turn it on again
  SongTimer->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::InstrumentsChange(TObject *Sender)
{
  //Change the midi instrument
  //A list of all instruments can be found online
  //Their numer is the instrument
  ChangeMidiInstrument(Instruments->ItemIndex);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StopClick(TObject *Sender)
{
  //Silence all currently playing notes
  SilenceMidiNotes();
  //Stop timer from playing song
  SongTimer->Enabled = false;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::VolumeChange(TObject *Sender)
{
  //Set volume (0 - 32767) (0x0000 - 0xFFFF)
  SetMidiVolume(Volume->Position);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
  //Silence all currently playing notes
  SilenceMidiNotes();
}
//---------------------------------------------------------------------------

