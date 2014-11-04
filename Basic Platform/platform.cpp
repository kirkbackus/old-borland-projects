//Written By Kirk Backus ----------------------------------------------------
#include <vector.h>
#include <math.h>
#pragma hdrstop

#include "platform.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

struct Player {
  float x,y,xp,yp,hspeed,vspeed;
  float width,height;
};

//Place to store the world
World collide;

//Gravity constant
float grav=.5;

//Player
Player player;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
  //Double Buffer the form
  DoubleBuffered=1;

  //Add the Shapes to the World
  collide.AddShape(Shape1);
  collide.AddShape(Shape2);
  collide.AddShape(Shape3);
  collide.AddShape(Shape4);
  collide.AddShape(Shape5);
  collide.AddShape(Shape6);
  collide.AddShape(Shape7);
  collide.AddShape(Shape8);
  collide.AddShape(Shape9);
  collide.AddShape(Shape10);

  //Set Player Object Info to player structure
  player.x = MPlayer->Left;
  player.y = MPlayer->Top;
  player.width = MPlayer->Width;
  player.height = MPlayer->Height;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
  //Move Player Right
  if (GetAsyncKeyState(VK_RIGHT)) {
    if (!collide.Collided(MPlayer,5,0)) player.x+=5;
    else if (!collide.Collided(MPlayer,1,0)) player.x+=1;
  }

  //Move Player Left
  if (GetAsyncKeyState(VK_LEFT)) {
    if (!collide.Collided(MPlayer,-5,0))player.x-=5;
    else if (!collide.Collided(MPlayer,-1,0)) player.x-=1;
  }

  //Set Gravity to 0.5
  grav=.5;

  //Check for jumping
  if (collide.Collided(MPlayer,0,1)) {
    grav=0; //If on ground null the gravity
    if (GetAsyncKeyState(VK_UP))player.vspeed=-10; //Jump
  }

  //Move Player
  player.vspeed += grav;
  player.xp = player.x;
  player.yp = player.y;
  player.x += player.hspeed;
  player.y += player.vspeed;

  //Move object to match player
  MPlayer->Left=player.x;
  MPlayer->Top=player.y;

  //"Pull" player out of ground
  while(collide.Collided(MPlayer)) {
    player.vspeed=0;
    grav=0;
    MPlayer->Top-=(player.y-player.yp)/4;
  }

  //Make sure that the fake player matches the player object
  player.x=MPlayer->Left;
  player.y=MPlayer->Top;

  //RESET KEY STATE
  GetAsyncKeyState(0);
}
//---------------------------------------------------------------------------
