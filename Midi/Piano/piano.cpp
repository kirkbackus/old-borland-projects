//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "piano.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
  MidiStart();
  SetMidiVolume(32767);
  DoubleBuffered=1;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::white1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  PlayMidiNoteT("C4");
  white1->Brush->Color=RGB(64,128,255);        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::white2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  PlayMidiNoteT("D4");
  white2->Brush->Color=RGB(64,128,255);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::white3MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  PlayMidiNoteT("E4");
  white3->Brush->Color=RGB(64,128,255);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::white4MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  PlayMidiNoteT("F4");
  white4->Brush->Color=RGB(64,128,255);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::white5MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  PlayMidiNoteT("G4");
  white5->Brush->Color=RGB(64,128,255);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::white6MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  PlayMidiNoteT("A4");
  white6->Brush->Color=RGB(64,128,255);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::white7MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  PlayMidiNoteT("B4");
  white7->Brush->Color=RGB(64,128,255);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::white8MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  PlayMidiNoteT("C5");
  white8->Brush->Color=RGB(64,128,255);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::white9MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  PlayMidiNoteT("D5");
  white9->Brush->Color=RGB(64,128,255);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::white10MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  PlayMidiNoteT("E5");
  white10->Brush->Color=RGB(64,128,255);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::white11MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  PlayMidiNoteT("F5");
  white11->Brush->Color=RGB(64,128,255);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::white12MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  PlayMidiNoteT("G5");
  white12->Brush->Color=RGB(64,128,255);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::white13MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  PlayMidiNoteT("A5");
  white13->Brush->Color=RGB(64,128,255);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::white14MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  PlayMidiNoteT("B5");
  white14->Brush->Color=RGB(64,128,255);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::white15MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  PlayMidiNoteT("C6");
  white15->Brush->Color=RGB(64,128,255);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::black1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  PlayMidiNoteT("C#4");
  black1->Brush->Color=RGB(64,128,255);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::black2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  PlayMidiNoteT("D#4");
  black2->Brush->Color=RGB(64,128,255);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::black3MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  PlayMidiNoteT("F#4");
  black3->Brush->Color=RGB(64,128,255);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::black4MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  PlayMidiNoteT("G#4");
  black4->Brush->Color=RGB(64,128,255);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::black5MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  PlayMidiNoteT("A#4");
  black5->Brush->Color=RGB(64,128,255);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::black6MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  PlayMidiNoteT("C#5");
  black6->Brush->Color=RGB(64,128,255);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::black7MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  PlayMidiNoteT("D#5");
  black7->Brush->Color=RGB(64,128,255);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::black8MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  PlayMidiNoteT("F#5");
  black8->Brush->Color=RGB(64,128,255);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::black9MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  PlayMidiNoteT("G#5");
  black9->Brush->Color=RGB(64,128,255);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::black10MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  PlayMidiNoteT("A#5");
  black10->Brush->Color=RGB(64,128,255);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::white15MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  StopMidiNoteT("C6");
  white15->Brush->Color=clWhite;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::white14MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  StopMidiNoteT("B5");
  white14->Brush->Color=clWhite;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::white13MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  StopMidiNoteT("A5");
  white13->Brush->Color=clWhite;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::white12MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  StopMidiNoteT("G5");
  white12->Brush->Color=clWhite;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::white11MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  StopMidiNoteT("F5");
  white11->Brush->Color=clWhite;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::white10MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  StopMidiNoteT("E5");
  white10->Brush->Color=clWhite;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::white9MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
  StopMidiNoteT("D5");
  white9->Brush->Color=clWhite;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::white8MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
  StopMidiNoteT("C5");
  white8->Brush->Color=clWhite;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::white7MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
  StopMidiNoteT("B4");
  white7->Brush->Color=clWhite;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::white6MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
  StopMidiNoteT("A4");
  white6->Brush->Color=clWhite;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::white5MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
  StopMidiNoteT("G4");
  white5->Brush->Color=clWhite;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::white4MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
  StopMidiNoteT("F4");
  white4->Brush->Color=clWhite;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::white3MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
  StopMidiNoteT("E4");
  white3->Brush->Color=clWhite;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::white2MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
  StopMidiNoteT("D4");
  white2->Brush->Color=clWhite;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::white1MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
  StopMidiNoteT("C4");
  white1->Brush->Color=clWhite;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::black1MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
  StopMidiNoteT("C#4");
  black1->Brush->Color=clBlack;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::black2MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
  StopMidiNoteT("D#4");
  black2->Brush->Color=clBlack;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::black3MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
  StopMidiNoteT("F#4");
  black3->Brush->Color=clBlack;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::black4MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
  StopMidiNoteT("G#4");
  black4->Brush->Color=clBlack;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::black5MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
  StopMidiNoteT("A#4");
  black5->Brush->Color=clBlack;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::black6MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
  StopMidiNoteT("C#5");
  black6->Brush->Color=clBlack;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::black7MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
  StopMidiNoteT("D#5");
  black7->Brush->Color=clBlack;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::black8MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
  StopMidiNoteT("F#5");
  black8->Brush->Color=clBlack;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::black9MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
  StopMidiNoteT("G#5");
  black9->Brush->Color=clBlack;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::black10MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  StopMidiNoteT("A#5");
  black10->Brush->Color=clBlack;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::About1Click(TObject *Sender)
{
  ShowMessage("Simple Piano by Kirk Backus\n\nUses the power of midi\nto play the notes\nHave fun ^_^\n(c) 2007 All Rights Reserved");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Quit1Click(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
  //Check keys for piano
  if (!GetAsyncKeyState(VK_LBUTTON)) {

  if (GetAsyncKeyState(65) && white1->Brush->Color==clWhite) {
    PlayMidiNoteT("C4");
    white1->Brush->Color=RGB(64,128,255);
  } else if (!GetAsyncKeyState(65) && white1->Brush->Color==RGB(64,128,255)) {
    StopMidiNoteT("C4");
    white1->Brush->Color=clWhite;
  }

  if ((GetAsyncKeyState(83)||GetAsyncKeyState(192)) && white2->Brush->Color==clWhite) {
    PlayMidiNoteT("D4");
    white2->Brush->Color=RGB(64,128,255);
  } else if (!(GetAsyncKeyState(83)||GetAsyncKeyState(192)) && white2->Brush->Color==RGB(64,128,255)) {
    StopMidiNoteT("D4");
    white2->Brush->Color=clWhite;
  }

  if ((GetAsyncKeyState(68)||GetAsyncKeyState(49)) && white3->Brush->Color==clWhite) {
    PlayMidiNoteT("E4");
    white3->Brush->Color=RGB(64,128,255);
  } else if (!(GetAsyncKeyState(68)||GetAsyncKeyState(49)) && white3->Brush->Color==RGB(64,128,255)) {
    StopMidiNoteT("E4");
    white3->Brush->Color=clWhite;
  }

  if ((GetAsyncKeyState(70)||GetAsyncKeyState(50)) && white4->Brush->Color==clWhite) {
    PlayMidiNoteT("F4");
    white4->Brush->Color=RGB(64,128,255);
  } else if (!(GetAsyncKeyState(70)||GetAsyncKeyState(50)) && white4->Brush->Color==RGB(64,128,255)) {
    StopMidiNoteT("F4");
    white4->Brush->Color=clWhite;
  }

  if ((GetAsyncKeyState(71)||GetAsyncKeyState(51)) && white5->Brush->Color==clWhite) {
    PlayMidiNoteT("G4");
    white5->Brush->Color=RGB(64,128,255);
  } else if (!(GetAsyncKeyState(71)||GetAsyncKeyState(51)) && white5->Brush->Color==RGB(64,128,255)) {
    StopMidiNoteT("G4");
    white5->Brush->Color=clWhite;
  }

  if ((GetAsyncKeyState(72)||GetAsyncKeyState(52)) && white6->Brush->Color==clWhite) {
    PlayMidiNoteT("A4");
    white6->Brush->Color=RGB(64,128,255);
  } else if (!(GetAsyncKeyState(72)||GetAsyncKeyState(52)) && white6->Brush->Color==RGB(64,128,255)) {
    StopMidiNoteT("A4");
    white6->Brush->Color=clWhite;
  }

  if ((GetAsyncKeyState(74)||GetAsyncKeyState(53)) && white7->Brush->Color==clWhite) {
    PlayMidiNoteT("B4");
    white7->Brush->Color=RGB(64,128,255);
  } else if (!(GetAsyncKeyState(74)||GetAsyncKeyState(53)) && white7->Brush->Color==RGB(64,128,255)) {
    StopMidiNoteT("B4");
    white7->Brush->Color=clWhite;
  }

  if ((GetAsyncKeyState(75)||GetAsyncKeyState(54)) && white8->Brush->Color==clWhite) {
    PlayMidiNoteT("C5");
    white8->Brush->Color=RGB(64,128,255);
  } else if (!(GetAsyncKeyState(75)||GetAsyncKeyState(54)) && white8->Brush->Color==RGB(64,128,255)) {
    StopMidiNoteT("C5");
    white8->Brush->Color=clWhite;
  }

  if ((GetAsyncKeyState(76)||GetAsyncKeyState(55)) && white9->Brush->Color==clWhite) {
    PlayMidiNoteT("D5");
    white9->Brush->Color=RGB(64,128,255);
  } else if (!(GetAsyncKeyState(76)||GetAsyncKeyState(55)) && white9->Brush->Color==RGB(64,128,255)) {
    StopMidiNoteT("D5");
    white9->Brush->Color=clWhite;
  }

  if ((GetAsyncKeyState(186)||GetAsyncKeyState(56)) && white10->Brush->Color==clWhite) {
    PlayMidiNoteT("E5");
    white10->Brush->Color=RGB(64,128,255);
  } else if (!(GetAsyncKeyState(186)||GetAsyncKeyState(56)) && white10->Brush->Color==RGB(64,128,255)) {
    StopMidiNoteT("E5");
    white10->Brush->Color=clWhite;
  }

  if ((GetAsyncKeyState(222)||GetAsyncKeyState(57)) && white11->Brush->Color==clWhite) {
    PlayMidiNoteT("F5");
    white11->Brush->Color=RGB(64,128,255);
  } else if (!(GetAsyncKeyState(222)||GetAsyncKeyState(57)) && white11->Brush->Color==RGB(64,128,255)) {
    StopMidiNoteT("F5");
    white11->Brush->Color=clWhite;
  }

  if (GetAsyncKeyState(48) && white12->Brush->Color==clWhite) {
    PlayMidiNoteT("G5");
    white12->Brush->Color=RGB(64,128,255);
  } else if (!GetAsyncKeyState(48) && white12->Brush->Color==RGB(64,128,255)) {
    StopMidiNoteT("G5");
    white12->Brush->Color=clWhite;
  }

  if (GetAsyncKeyState(189) && white13->Brush->Color==clWhite) {
    PlayMidiNoteT("A5");
    white13->Brush->Color=RGB(64,128,255);
  } else if (!GetAsyncKeyState(189) && white13->Brush->Color==RGB(64,128,255)) {
    StopMidiNoteT("A5");
    white13->Brush->Color=clWhite;
  }

  if (GetAsyncKeyState(187) && white14->Brush->Color==clWhite) {
    PlayMidiNoteT("B5");
    white14->Brush->Color=RGB(64,128,255);
  } else if (!GetAsyncKeyState(187) && white14->Brush->Color==RGB(64,128,255)) {
    StopMidiNoteT("B5");
    white14->Brush->Color=clWhite;
  }

  if (GetAsyncKeyState(8) && white15->Brush->Color==clWhite) {
    PlayMidiNoteT("C6");
    white15->Brush->Color=RGB(64,128,255);
  } else if (!GetAsyncKeyState(8) && white15->Brush->Color==RGB(64,128,255)) {
    StopMidiNoteT("C6");
    white15->Brush->Color=clWhite;
  }

  if (GetAsyncKeyState(87) && black1->Brush->Color==clBlack) {
    PlayMidiNoteT("C#4");
    black1->Brush->Color=RGB(64,128,255);
  } else if (!GetAsyncKeyState(87) && black1->Brush->Color==RGB(64,128,255)) {
    StopMidiNoteT("C#4");
    black1->Brush->Color=clBlack;
  }

  if ((GetAsyncKeyState(69)||GetAsyncKeyState(112)) && black2->Brush->Color==clBlack) {
    PlayMidiNoteT("D#4");
    black2->Brush->Color=RGB(64,128,255);
  } else if (!(GetAsyncKeyState(69)||GetAsyncKeyState(112)) && black2->Brush->Color==RGB(64,128,255)) {
    StopMidiNoteT("D#4");
    black2->Brush->Color=clBlack;
  }

  if ((GetAsyncKeyState(84)||GetAsyncKeyState(114)) && black3->Brush->Color==clBlack) {
    PlayMidiNoteT("F#4");
    black3->Brush->Color=RGB(64,128,255);
  } else if (!(GetAsyncKeyState(84)||GetAsyncKeyState(114)) && black3->Brush->Color==RGB(64,128,255)) {
    StopMidiNoteT("F#4");
    black3->Brush->Color=clBlack;
  }

  if ((GetAsyncKeyState(89)||GetAsyncKeyState(115)) && black4->Brush->Color==clBlack) {
    PlayMidiNoteT("G#4");
    black4->Brush->Color=RGB(64,128,255);
  } else if (!(GetAsyncKeyState(89)||GetAsyncKeyState(115)) && black4->Brush->Color==RGB(64,128,255)) {
    StopMidiNoteT("G#4");
    black4->Brush->Color=clBlack;
  }

  if ((GetAsyncKeyState(85)||GetAsyncKeyState(116)) && black5->Brush->Color==clBlack) {
    PlayMidiNoteT("A#4");
    black5->Brush->Color=RGB(64,128,255);
  } else if (!(GetAsyncKeyState(85)||GetAsyncKeyState(116)) && black5->Brush->Color==RGB(64,128,255)) {
    StopMidiNoteT("A#4");
    black5->Brush->Color=clBlack;
  }

  if ((GetAsyncKeyState(79)||GetAsyncKeyState(118)) && black6->Brush->Color==clBlack) {
    PlayMidiNoteT("C#5");
    black6->Brush->Color=RGB(64,128,255);
  } else if (!(GetAsyncKeyState(79)||GetAsyncKeyState(118)) && black6->Brush->Color==RGB(64,128,255)) {
    StopMidiNoteT("C#5");
    black6->Brush->Color=clBlack;
  }

  if ((GetAsyncKeyState(80)||GetAsyncKeyState(119)) && black7->Brush->Color==clBlack) {
    PlayMidiNoteT("D#5");
    black7->Brush->Color=RGB(64,128,255);
  } else if (!(GetAsyncKeyState(80)||GetAsyncKeyState(119)) && black7->Brush->Color==RGB(64,128,255)) {
    StopMidiNoteT("D#5");
    black7->Brush->Color=clBlack;
  }

  if ((GetAsyncKeyState(221)||GetAsyncKeyState(121)) && black8->Brush->Color==clBlack) {
    PlayMidiNoteT("F#5");
    black8->Brush->Color=RGB(64,128,255);
  } else if (!(GetAsyncKeyState(221)||GetAsyncKeyState(121)) && black8->Brush->Color==RGB(64,128,255)) {
    StopMidiNoteT("F#5");
    black8->Brush->Color=clBlack;
  }

  if (GetAsyncKeyState(122) && black9->Brush->Color==clBlack) {
    PlayMidiNoteT("G#5");
    black9->Brush->Color=RGB(64,128,255);
  } else if (!GetAsyncKeyState(122) && black9->Brush->Color==RGB(64,128,255)) {
    StopMidiNoteT("G#5");
    black9->Brush->Color=clBlack;
  }

  if (GetAsyncKeyState(123) && black10->Brush->Color==clBlack) {
    PlayMidiNoteT("A#5");
    black10->Brush->Color=RGB(64,128,255);
  } else if (!GetAsyncKeyState(123) && black10->Brush->Color==RGB(64,128,255)) {
    StopMidiNoteT("A#5");
    black10->Brush->Color=clBlack;
  }

  }
  /*
  for (int i=1;i<255;i++) {
    if (GetAsyncKeyState(i))
    ShowMessage(IntToStr(i));
  }
  */
  //33: !"#$%&'()*+,-./01234567890:;<=>?@
}
//---------------------------------------------------------------------------




void __fastcall TForm1::Button1Click(TObject *Sender)
{
  ChangeMidiInstrument(Instrument->ItemIndex);        
}
//---------------------------------------------------------------------------

