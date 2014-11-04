//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "bbox.h"
#include "blackbox.cpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TBBForm *BBForm;

using namespace Blackbox;

Blackbox::Polygon* square;
Blackbox::Polygon* level;
float rot=0;

//---------------------------------------------------------------------------
__fastcall TBBForm::TBBForm(TComponent* Owner)
        : TForm(Owner)
{
  DoubleBuffered=1;
  
  square = new Blackbox::Polygon();
  level = new Blackbox::Polygon();

  square->AddPoint(-25,-25);
  square->AddPoint(25,-25);
  square->AddPoint(25,25);
  square->AddPoint(-25,25);

  level->AddPoint(-255,0);
  level->AddPoint(255,0);
  level->AddPoint(255,75);
  level->AddPoint(0,150);
  level->AddPoint(-255,25);

  level->position = Vector(255,230);
}
//---------------------------------------------------------------------------
void __fastcall TBBForm::FormPaint(TObject *Sender)
{
  for (int i=1;i<=square->NumPoints();i++) {
    Canvas->MoveTo(square->GetAPointX(i-1),square->GetAPointY(i-1));
    if (i!=square->NumPoints()) Canvas->LineTo(square->GetAPointX(i),square->GetAPointY(i));
    else Canvas->LineTo(square->GetAPointX(0),square->GetAPointY(0));
  }

  for (int i=1;i<=level->NumPoints();i++) {
    Canvas->MoveTo(level->GetAPointX(i-1),level->GetAPointY(i-1));
    if (i!=level->NumPoints()) Canvas->LineTo(level->GetAPointX(i),level->GetAPointY(i));
    else Canvas->LineTo(level->GetAPointX(0),level->GetAPointY(0));
  }
}
//---------------------------------------------------------------------------
void __fastcall TBBForm::Timer1Timer(TObject *Sender)
{
  if (fabs(square->velocity.x)<=1) square->velocity.x = 0;
  else square->velocity.x-=sign(square->velocity.x);

  if (GetAsyncKeyState(VK_RIGHT)) square->velocity.x+=2;
  if (GetAsyncKeyState(VK_LEFT)) square->velocity.x-=2;
  if (GetAsyncKeyState(VK_DOWN)) square->velocity.y++;
  if (GetAsyncKeyState(VK_UP)) {
    if (square->Collided(level,0,1)) square->velocity.y-=10;
  }

  level->SetRotation(rot);
  if (GetAsyncKeyState(VK_SHIFT))rot += .01;

  if (square->velocity.x>5) square->velocity.x=5;
  if (square->velocity.x<-5) square->velocity.x=-5;

  square->velocity.y+=.5;
  square->position += square->velocity;

  Vector vtmp;
  if (square->Collided(level,&vtmp)) {
    square->velocity.y = 0;
    square->position -= vtmp*1.1;
  }

  if (square->position.x<25) { square->position.x = 25; square->velocity.x = 0; }
  if (square->position.y<25) { square->position.y = 25; square->velocity.y = 0; }
  if (square->position.x>BBForm->ClientWidth-25) { square->position.x = BBForm->ClientWidth-25; square->velocity.x = 0; }
  if (square->position.y>BBForm->ClientHeight-25) { square->position.y = BBForm->ClientHeight-25; square->velocity.y = 0; }

  Refresh();
}
//---------------------------------------------------------------------------
