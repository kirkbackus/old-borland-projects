//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <wchar.h>
#include <string.h>

#include "texttospeech.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ACTIVEVOICEPROJECTLib_OCX"
#pragma resource "*.dfm"
TForm1 *Form1;
wchar_t* text;

int speed,pitch,speaker;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
  text = L"hello, welcome";

  int i=1;
  while (DirectSS1->ModeName(i)) {
    ListBox1->Items->Add(DirectSS1->ModeName(i));
    i++;
  }

  speaker = 1;
  speed = DirectSS1->Speed;
  pitch = DirectSS1->Pitch;
  DirectSS1->Select(speaker);
  Label4->Caption = DirectSS1->ModeName(speaker);

  TrackBar1->Max = DirectSS1->MaxSpeed;
  TrackBar1->Min = DirectSS1->MinSpeed;
  TrackBar2->Max = DirectSS1->MaxPitch;
  TrackBar2->Min = DirectSS1->MinPitch;
  TrackBar1->Position = speed;
  TrackBar2->Position = pitch;

  DirectSS1->Speak(text);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
  if (!DirectSS1->Speaking) {
    int length;
    length = Edit1->Text.Length();
    delete text;
    Edit1->Text.WideChar(text,Edit1->Text.WideCharBufSize());

    DirectSS1->Select(speaker);
    DirectSS1->Speed = speed;
    DirectSS1->Pitch = pitch;

    DirectSS1->Speak(text);
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ListBox1Click(TObject *Sender)
{
  if (!DirectSS1->Speaking) {
    speaker = ListBox1->ItemIndex+1;
    DirectSS1->Select(speaker);
    TrackBar1->Max = DirectSS1->MaxSpeed;
    TrackBar1->Min = DirectSS1->MinSpeed;
    TrackBar2->Max = DirectSS1->MaxPitch;
    TrackBar2->Min = DirectSS1->MinPitch;
    Label4->Caption = DirectSS1->ModeName(speaker);
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar1Change(TObject *Sender)
{
  speed = TrackBar1->Position;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar2Change(TObject *Sender)
{
  pitch = TrackBar2->Position;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormDestroy(TObject *Sender)
{
  delete text;        
}
//---------------------------------------------------------------------------

