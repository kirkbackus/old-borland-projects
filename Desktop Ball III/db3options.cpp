//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "enum.h"
#include "db3options.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormOptions *FormOptions;
//---------------------------------------------------------------------------
__fastcall TFormOptions::TFormOptions(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormOptions::CollideOptionChange(TObject *Sender)
{
  if (CollideOption->ItemIndex==0) BallForm->collide_windows = 1;
  if (CollideOption->ItemIndex==1) BallForm->collide_windows = 0;  
}
//---------------------------------------------------------------------------
void __fastcall TFormOptions::SColorMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  if (BallColor->Execute()) {
    BallForm->SBall->Brush->Color = BallColor->Color;
    SColor->Brush->Color = BallColor->Color;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormOptions::TransBarChange(TObject *Sender)
{
  if (TransBar->Position>0) {
    BallForm->AlphaBlend=1;
    BallForm->AlphaBlendValue=255-TransBar->Position;
  } else {
    BallForm->AlphaBlend=0;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormOptions::FrictionBarChange(TObject *Sender)
{
  BallForm->fric = (float)FrictionBar->Position/10.0;
}
//---------------------------------------------------------------------------
void __fastcall TFormOptions::GravBarChange(TObject *Sender)
{
  BallForm->gravity = (float)GravBar->Position/10.0;
}
//---------------------------------------------------------------------------
void __fastcall TFormOptions::QuitBtnClick(TObject *Sender)
{
  BallForm->Close();        
}
//---------------------------------------------------------------------------
