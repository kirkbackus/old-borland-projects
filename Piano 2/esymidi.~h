//Easymidi ----------------------------------------|
//  Written By Kirk Backus                         |
//  Version: 1.00                                  |
//                                                 |
//-------------------------------------------------|

//Functions Include ------------------------------------------------|
//  MidiStart()                                                     |
//  MidiDestroy()                                                   |
//                                                                  |
//  PlayMidiNote(int note)                                          |
//    Ex: PlayMidiNote(56);                                         |
//                                                                  |
//  PlayMidiNoteT(String note)                                      |
//    Ex: PlayMidiNoteT("C5");                                      |
//                                                                  |
//  StopMidiNote(int note)                                          |
//    Ex: StopMidiNote(56);                                         |
//                                                                  |
//  SilenceMidiNotes();                                             |
//                                                                  |
//  ChangeMidiInstrument(int instrument)                            |
//    Ex: ChangeMidiInstrument(115);                                |
//                                                                  |
//  SetMidiVolume(int volume)                                       |
//    Ex: SetMidiVolume(0xFFFF); //That is full volume and Default  |
//------------------------------------------------------------------|
#ifndef _ESY_MIDI_H
#define _ESY_MIDI_H

#include <mmsystem.h>

int midiport = 0;
HMIDIOUT __device;

union {
  public:
  unsigned long word;
  unsigned char data[4];
} message;

class Note {
  private:

  int note;

  int NoteToString(String n);

  public:

  Note() { note = 0; }
  Note(int n) { note = n; }
  Note(String n);

  Note operator=(int n) { note = n; return(*this); }
  Note operator=(const char* n) { note = NoteToString(n); return(*this); }
  Note operator=(char* n) { note = NoteToString(n); return(*this); }
  Note operator=(String n);
  Note operator=(Note n) { note = n.GetMIDINumber(); return(*this); }

  bool operator==(Note n) { return(note==n.GetMIDINumber()); }

  Note operator+(Note n) { return(Note(note+n.GetMIDINumber())); }

  int GetMIDINumber() { return note; }
};

Note::Note(String n) { note = NoteToString(n); }
Note Note::operator=(String n) { note = NoteToString(n); return(*this); }

int Note::NoteToString(String n) {
  int tnote=0;
  String num;

  if (!(n.Length() < 2 || n.Length() > 3)) {
    //Convert note
    if (n.Length()==2)
    num=n.SubString(2,1);
    if (n.Length()==3)
    num=n.SubString(3,1);

    if (n.SubString(1,1)=="C")tnote=0;
    if (n.SubString(1,1)=="D")tnote=2;
    if (n.SubString(1,1)=="E")tnote=4;
    if (n.SubString(1,1)=="F")tnote=5;
    if (n.SubString(1,1)=="G")tnote=7;
    if (n.SubString(1,1)=="A")tnote=9;
    if (n.SubString(1,1)=="B")tnote=11;

    tnote += 12*atoi(num.c_str());

    if (n.Length()==3)
    tnote+=1;
  }

  return (tnote);
}

int instrument;
int note;

HMIDIOUT MidiStart() {
  midiOutOpen(&__device, midiport, 0, 0, CALLBACK_NULL);
  message.data[2] = 127;
  message.data[3] = 0;
  return __device;
}

void MidiDestroy() {
  midiOutClose(&__device);
}

void ChangeMidiInstrument(int instrument) {
  message.data[0] = 0xC0;
  message.data[1] = instrument;
  midiOutShortMsg(__device, message.word);
}

void SetMidiVolume(int vol) {
  midiOutSetVolume(__device, vol);
}

void SilenceMidiNotes() {
  for (int i = 0; i < 127; i++) {
    message.data[0] = 0x80;
    message.data[1] = i;
    midiOutShortMsg(__device, message.data[0]);
    midiOutShortMsg(__device, message.data[1]);
  }
}

void PlayMidiNote(int note) {
  Note tnote = note;
  message.data[0] = 0x90;
  message.data[1] = note;
  midiOutShortMsg(__device, message.word);
}

void PlayMidiNote(String note) {
  Note tnote = note;
  message.data[0] = 0x90;                                      // note on
  message.data[1] = tnote.GetMIDINumber();                     // note #
  midiOutShortMsg(__device, message.word);
  message.data[1] = 0xE0;
  message.data[2] = 64;
  midiOutShortMsg(__device,message.word);
}

void PlayMidiNote(Note note) {
  message.data[0] = 0x90;                                      // note on
  message.data[1] = note.GetMIDINumber();                      // note #
  midiOutShortMsg(__device, message.word);                    // this works
}

void StopMidiNote(int note) {
  message.data[0] = 0x80;
  message.data[1] = note;
  midiOutShortMsg(__device, message.data[0]);
  midiOutShortMsg(__device, message.data[1]);
}

void StopMidiNote(Note note) {
  message.data[0] = 0x80;
  message.data[1] = note.GetMIDINumber();
  midiOutShortMsg(__device, message.data[0]);
  midiOutShortMsg(__device, message.data[1]);
}

bool StopMidiNote(String Tnote) {
  int note=60;
  String num;

  if (Tnote.Length() < 2 || Tnote.Length() > 3) return 0;

  //Convert note
  if (Tnote.Length()==2)
  num=Tnote.SubString(2,1);
  if (Tnote.Length()==3)
  num=Tnote.SubString(3,1);

  if (Tnote.SubString(1,1)=="C")note=0;
  if (Tnote.SubString(1,1)=="D")note=2;
  if (Tnote.SubString(1,1)=="E")note=4;
  if (Tnote.SubString(1,1)=="F")note=5;
  if (Tnote.SubString(1,1)=="G")note=7;
  if (Tnote.SubString(1,1)=="A")note=9;
  if (Tnote.SubString(1,1)=="B")note=11;

  note += 12*atoi(num.c_str());

  if (Tnote.Length()==3)
  note+=1;

  message.data[0] = 0x80;
  message.data[1] = note;
  midiOutShortMsg(__device, message.data[0]);
  midiOutShortMsg(__device, message.data[1]);
  return 1;
}

#endif
