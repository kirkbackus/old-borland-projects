//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "basic.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

POINT mouse;
CollisionEngine engine;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
  DoubleBuffered=1;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
  //Getting the mouse position
  GetCursorPos(&mouse);
  mouse.x=mouse.x-Form1->Left-4;
  mouse.y=mouse.y-Form1->Top-30;

  //Move the shapes to the mouse position
  Shape1->Left = mouse.x-Shape1->Width/2;
  Shape1->Top = mouse.y-Shape1->Height/2;

  //Move the shapes to the mouse position
  Shape4->Left = mouse.x-Shape4->Width/2;
  Shape4->Top = mouse.y-Shape4->Height/2;

  //HERE IS THE ACTUAL CODE!!!
  if (engine.RectCollide(Shape1,Shape2)) //If there is a Rectangle collision
    Shape2->Brush->Color = clRed;   //Turns outer rectangle red
  else
    Shape2->Brush->Color = clWhite; //Turns outer rectangle white

  if (engine.CircleCollide(Shape3,Shape4)) //If there is a Rectangle collision
    Shape3->Brush->Color = clBlue; //Turns inner circle blue
  else
    Shape3->Brush->Color = clWhite; //Turns inner circle white

  //If pressing escape, quit game
  if (GetAsyncKeyState(VK_ESCAPE)) {
    Close();
  }
}
//---------------------------------------------------------------------------


