//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>
#include "esymidi.h"
#pragma hdrstop
//---------------------------------------------------------------------------
//   Important note about DLL memory management when your DLL uses the
//   static version of the RunTime Library:
//
//   If your DLL exports any functions that pass String objects (or structs/
//   classes containing nested Strings) as parameter or function results,
//   you will need to add the library MEMMGR.LIB to both the DLL project and
//   any other projects that use the DLL.  You will also need to use MEMMGR.LIB
//   if any other projects which use the DLL will be performing new or delete
//   operations on any non-TObject-derived classes which are exported from the
//   DLL. Adding MEMMGR.LIB to your project will change the DLL and its calling
//   EXE's to use the BORLNDMM.DLL as their memory manager.  In these cases,
//   the file BORLNDMM.DLL should be deployed along with your DLL.
//
//   To avoid using BORLNDMM.DLL, pass string information using "char *" or
//   ShortString parameters.
//
//   If your DLL uses the dynamic version of the RTL, you do not need to
//   explicitly add MEMMGR.LIB as this will be done implicitly for you
//---------------------------------------------------------------------------

#pragma argsused

#define exportd extern "C" __declspec (dllexport)

int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
  return 1;
}
//---------------------------------------------------------------------------

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

exportd double StartMidi() {
  //MidiStart();
  return 0;
}

exportd double DestroyMidi() {
  MidiDestroy();
  return 0;
}

exportd double PlayNote(int note) {
  PlayMidiNote(note);
  return 0;
}

exportd double PlayNoteT(String note) {
  PlayMidiNoteT(note);
  return 0;
}

exportd double StopNote(int note) {
  StopMidiNote(note);
  return 0;
}

exportd double StopNoteT(String note) {
  StopMidiNoteT(note);
  return 0;
}

exportd double SilenceAll() {
  SilenceMidiNotes();
  return 0;
}

exportd double ChangeInstrument(int instrument) {
  ChangeMidiInstrument(instrument);
  return 0;
}

exportd double SetVolume(int volume) {
  SetMidiVolume(volume);
  return 0;
}
