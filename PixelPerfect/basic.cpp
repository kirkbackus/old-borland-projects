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

int hspeed1 = 2;
int hspeed2 = -10;
int vspeed1 = -6;
int vspeed2 = 4; 
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
  DoubleBuffered=1;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
  GetCursorPos(&mouse);
  mouse.x=mouse.x-Form1->Left-4;
  mouse.y=mouse.y-Form1->Top-30;

  Image1->Left += hspeed1;
  Image1->Top += vspeed1;

  Image2->Left += hspeed2;
  Image2->Top += vspeed2;

  //Window Borders
  if (Image1->Left+Image1->Width >= ClientWidth) hspeed1=-abs(hspeed1); //Rev-H
  if (Image2->Left+Image2->Width >= ClientWidth) hspeed2=-abs(hspeed2); //Rev-H
  if (Image1->Left <= 0) hspeed1=abs(hspeed1); //Rev-H
  if (Image2->Left <= 0) hspeed2=abs(hspeed2); //Rev-H
  if (Image1->Top+Image1->Height >= ClientHeight) vspeed1=-abs(vspeed1); //Rev-H
  if (Image2->Top+Image2->Height >= ClientHeight) vspeed2=-abs(vspeed2); //Rev-H
  if (Image1->Top <= 0) vspeed1=abs(vspeed1);
  if (Image2->Top <= 0) vspeed2=abs(vspeed2);

  //HERE IS THE ACTUAL CODE!!!
  if (engine.PixelCollide(Image1,Image2)) { //If there is a collision
    float dir,force,dir2,force2,xx1,xx2,yy1,yy2;

    xx1 = Image1->Left+64;
    xx2 = Image2->Left+64;
    yy1 = Image1->Top+64;
    yy2 = Image2->Top+64;

    dir=point_direction(xx1,yy1,xx2,yy2);
    force=lengthdir_x(1,dir)*hspeed1+lengthdir_y(1,dir)*vspeed1;
    dir2=point_direction(xx2,yy2,xx1,yy1);
    force2=lengthdir_x(1,dir2)*hspeed2+lengthdir_y(1,dir2)*vspeed2;

    //Move them away from eachother
    int itr=0;
    if (!(xx1==xx2 && yy1==yy2))
    while (point_distance(xx1,yy1,xx2,yy2)<=64) {
      xx2-=lengthdir_x(.1,dir+180);
      yy2-=lengthdir_y(.1,dir+180);
      xx1-=lengthdir_x(.1,dir2+180);
      yy1-=lengthdir_y(.1,dir2+180);
      if (itr > 1000) break; //Stop if it crashed
      itr++;
    }

    //Simulate motion add
    hspeed2+=lengthdir_x(-(force2+force),dir+180);
    vspeed2+=lengthdir_y(-(force2+force),dir+180);
    hspeed1+=lengthdir_x(-(force+force2),dir2+180);
    vspeed1+=lengthdir_y(-(force+force2),dir2+180);

    Image1->Left = xx1-64;
    Image2->Left = xx2-64;
    Image1->Top = yy1-64;
    Image2->Top = yy2-64;
  }

  //If pressing escape, quit game
  if (GetAsyncKeyState(VK_ESCAPE)) {
    Close();
  }
}
//---------------------------------------------------------------------------
