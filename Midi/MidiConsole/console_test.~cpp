//---------------------------------------------------------------------------

#include <vcl.h>
#include "esymidi.h"
#pragma hdrstop

//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[])
{
  int delay=0;

  MidiStart();

  while (1) {
    if (GetAsyncKeyState(VK_SPACE) && delay==0) {
      delay = 1000000;
      PlayMidiNoteT("C4");
      PlayMidiNoteT("E4");
      PlayMidiNoteT("G4");
    }

    if (delay>0)delay--;

    if (GetAsyncKeyState(VK_ESCAPE))
    break;
  }

  SilenceMidiNotes();
  MidiDestroy();

  return 0;
}
//---------------------------------------------------------------------------
 