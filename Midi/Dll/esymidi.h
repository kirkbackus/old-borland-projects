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
//    Ex: SetMidiVolume(32767); //That is full volume and Default   |
//------------------------------------------------------------------|

#include <mmsystem.h>

int midiport = 0;
HMIDIOUT __device;

union {
   public:
   unsigned long word;
   unsigned char data[4];
} message;

int instrument;
int note;

HMIDIOUT MidiStart() {
  midiOutOpen(&__device, midiport, 0, 0, CALLBACK_NULL);
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

bool PlayMidiNoteT(String Tnote) {

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

  message.data[0] = 0x90;                                      // note on
  message.data[1] = note;                                       // note #
  message.data[2] = 100;                   // once set, no need to repeat
  message.data[3] = 0;                     // once set, no need to repeat
  midiOutShortMsg(__device, message.word);                    // this works

  return 1;
}

void PlayMidiNote(int note) {
  message.data[0] = 0x90;                                      // note on
  message.data[1] = note;                                       // note #
  message.data[2] = 100;                   // once set, no need to repeat
  message.data[3] = 0;                     // once set, no need to repeat
  midiOutShortMsg(__device, message.word);                    // this works
}

void StopMidiNote(int note) {
  message.data[0] = 0x80;
  message.data[1] = note;
  midiOutShortMsg(__device, message.data[0]);
  midiOutShortMsg(__device, message.data[1]);
}

bool StopMidiNoteT(String Tnote) {
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
