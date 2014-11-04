//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "options.h"
#include "piano.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TOptionForm *OptionForm;
//---------------------------------------------------------------------------
__fastcall TOptionForm::TOptionForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TOptionForm::InstrumentBoxClick(TObject *Sender)
{
  ChangeMidiInstrument(InstrumentBox->ItemIndex);        
}
//---------------------------------------------------------------------------

void __fastcall TOptionForm::TransBarChange(TObject *Sender)
{
  if (TransBar->Position != 0) {
    PianoForm->AlphaBlend = 1;
    PianoForm->AlphaBlendValue = 255-TransBar->Position;
  } else {
    PianoForm->AlphaBlend = 0;
    PianoForm->AlphaBlendValue = 255;
  }
}
//---------------------------------------------------------------------------

void __fastcall TOptionForm::TBtnBoxClick(TObject *Sender)
{
  if (!TBtnBox->Checked) {
    ShowWindow(Application->Handle,0);
    SetWindowLong(Application->Handle,GWL_EXSTYLE,WS_EX_TOOLWINDOW);
    ShowWindow(Application->Handle,1);
  } else {
    ShowWindow(Application->Handle,0);
    SetWindowLong(Application->Handle,GWL_EXSTYLE,WS_EX_APPWINDOW);
    ShowWindow(Application->Handle,1);
  }
}
//---------------------------------------------------------------------------


void __fastcall TOptionForm::OctaveChange(TObject *Sender)
{
  int c = atoi(Octave->Text.c_str());
  if (c<-4) c = -4;
  if (c>4) c = 4;
  Octave->Text = String(c);
  PianoForm->octave = c;
}
//---------------------------------------------------------------------------

