//---------------------------------------------------------------------------
#include <math.h>
#include <vcl.h>
#include <vector>
#include <WinSock2.h>
#include "usock.h"
#pragma hdrstop

#include "mplay.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGameForm *GameForm;

struct Obj {
  float x, y, h, v;
};

void ControlStick(Obj* b, TControl* c);
void UpdateStick(Obj* b, TControl* c);
int ControlBall(Obj* b, TControl* c, Obj* s1, TControl* s1c, Obj* s2, TControl* s2c);
void UpdateBall(Obj* b, TControl* c);
bool Collided(TControl* a, TControl b);

ServerSocket* server = NULL;
ClientSocket* client = NULL;

const int port = 1423;
int gamestart = 0;
int PMAX=0;
int BMAX=0;
int BWMAX=0;

int p1score=0;
int p2score=0;

#define VMAX 6
#define VFRIC .2

Obj hstick;
Obj cstick;
Obj ball;

//---------------------------------------------------------------------------
__fastcall TGameForm::TGameForm(TComponent* Owner)
        : TForm(Owner)
{
  Init39();
  GameForm->DoubleBuffered = 1;
  GameBox->DoubleBuffered = 1;
  PMAX = GameBox->Height-HostPaddle->Height;
  BMAX = GameBox->Height-Ball->Height;
  BWMAX = GameBox->Width-Ball->Width;

  hstick.x = HostPaddle->Left;
  hstick.y = HostPaddle->Top;
  cstick.x = ClientPaddle->Left;
  cstick.y = ClientPaddle->Top;
  ball.x = GameForm->GameBox->Width/2-GameForm->Ball->Width/2;
  ball.y = GameForm->GameBox->Height/2-GameForm->Ball->Height/2;
  UpdateBall(&ball,Ball);

  JoinBox->Visible = 0;

  randomize();
}
//---------------------------------------------------------------------------
void __fastcall TGameForm::Quit1Click(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TGameForm::Host1Click(TObject *Sender)
{
  JoinBox->Visible = 0;
  gamestart = 0;
  if (server!=NULL) {
    delete server;
    server = NULL;
  }

  if (client!=NULL) {
    delete client;
    client = NULL;
  }

  server = new ServerSocket();
  if (server->Listen(port,1)) {
    LStatus->Caption = "Waiting For Player\nLocal IP: "+String(server->GetIPAddress());
    HostTimer->Enabled = 1;
    EndGame1->Enabled = 1;
    Host1->Enabled = 0;
    Join1->Enabled = 0;
  } else {
    delete server;
    server = NULL;
  }
}
//---------------------------------------------------------------------------
void __fastcall TGameForm::HostTimerTimer(TObject *Sender)
{
  if (server->GetNumConnections()==0) { //ACCEPT NEW CONNECTIONS
    server->Accept();
    if (server->GetNumConnections()==1) {
      LStatus->Visible = 0;
      gamestart = 1;
      while(ball.h==0) {
        ball.h = rand()%4-2;
        ball.v = 0.0000000001;
      }
    }
  }

  if (gamestart==1) {
    while(1) {
      int s = server->Receive(0);

      if (s<0) break;

      if (s==0) { //THIS MEANS THE PLAYER LEFT SO WE WILL END THE GAME
        LStatus->Visible = 1;
        LStatus->Caption = "THE PLAYER LEFT THE GAME";
        HostTimer->Enabled = 0;
      }

      if (s>0) { //LOOK THROUGH ALL THE MESSAGES
        int msgid = (int)readbyte(0); //Get's the ID of the message

        switch (msgid) {
          case 0: //UPDATE CLIENT POSITION

          cstick.x = readfloat(0);
          cstick.y = readfloat(0);
          cstick.h = readfloat(0);
          cstick.v = readfloat(0);
          break;
        }
      }
    }
    //UPDATES SERVER PADDLE'S POSITION
    server->ResetBuffer();
    server->WriteByte(0);
    server->WriteFloat(hstick.x);
    server->WriteFloat(hstick.y);
    server->WriteFloat(hstick.h);
    server->WriteFloat(hstick.v);
    server->Send();

    //UPDATES BALL'S POSITION
    server->ResetBuffer();
    server->WriteByte(1);
    server->WriteFloat(ball.x);
    server->WriteFloat(ball.y);
    server->WriteFloat(ball.h);
    server->WriteFloat(ball.v);
    server->Send();

    int bscore = ControlBall(&ball,Ball,&hstick,HostPaddle,&cstick,ClientPaddle);
    if (bscore) {
      if (bscore==1) p1score++;
      if (bscore==2) p2score++;
      LScore->Caption = (String)p1score+" - "+(String)p2score;
      server->ResetBuffer();
      server->WriteByte(2);
      server->WriteInt(p1score);
      server->WriteInt(p2score);
      server->Send();
    }
    
    ControlStick(&hstick,HostPaddle);
    UpdateStick(&cstick,ClientPaddle);
  }
}
//---------------------------------------------------------------------------
void __fastcall TGameForm::ClientTimerTimer(TObject *Sender)
{
  ControlStick(&cstick,ClientPaddle);

  client->ResetBuffer();
  client->WriteByte(0);
  client->WriteFloat(cstick.x);
  client->WriteFloat(cstick.y);
  client->WriteFloat(cstick.h);
  client->WriteFloat(cstick.v);
  client->Send();

  while(1) {
    int s = client->Receive();

    if (s<0) break;

    if (s==0) { //THIS MEANS THE PLAYER LEFT SO WE WILL END THE GAME
      LStatus->Visible = 1;
      LStatus->Caption = "THE HOST ENDED THE GAME";
      ClientTimer->Enabled = 0;
      break;
    }

    int msgid = (int)readbyte(0); //Get's the ID of the message

    switch (msgid) {
      case 0: //UPDATE SERVER PADDLE POSITION

      hstick.x = readfloat(0);
      hstick.y = readfloat(0);
      hstick.h = readfloat(0);
      hstick.v = readfloat(0);

      break;

      case 1: //UPDATE BALL POSITION

      ball.x = readfloat(0);
      ball.y = readfloat(0);
      ball.h = readfloat(0);
      ball.v = readfloat(0);

      break;

      case 2: //UPDATE SCORE

      p1score = readint(0);
      p2score = readint(0);

      LScore->Caption = (String)p1score+" - "+(String)p2score;

      break;
    }
  }

  UpdateStick(&hstick,HostPaddle);
  UpdateBall(&ball,Ball);
}
//---------------------------------------------------------------------------
void __fastcall TGameForm::Join1Click(TObject *Sender)
{
  JoinBox->Visible = 1;
}
//---------------------------------------------------------------------------
bool Collided(TControl* a, TControl* b) {
  if (a->Left+a->Width>b->Left && a->Top+a->Height>b->Top
   && a->Left<b->Left+b->Width && a->Top<b->Top+b->Height) return 1;
  return 0;
}
//---------------------------------------------------------------------------
void UpdateStick(Obj* b, TControl* c) {
  c->Left = b->x;
  c->Top = b->y;
  b->x += b->h;
  b->y += b->v;
}
//---------------------------------------------------------------------------
int ControlBall(Obj* b, TControl* c, Obj* s1, TControl* s1c, Obj* s2, TControl* s2c) {
  if (b->v==0) b->v=.0000001;
  b->x += b->h;
  b->y += b->v;

  b->h += (abs(b->h)/b->h)/100.0;
  b->v += (abs(b->v)/b->v)/100.0;

  if (b->y < 0) {
    b->y=0;
    b->v=-b->v;
  }

  if (b->y > BMAX) {
    b->y = BMAX;
    b->v=-b->v;
  }

  c->Left = b->x;
  c->Top = b->y;

  if (Collided(c,s1c)) {
    b->h = fabs(b->h);
    b->v = (float)-(s1c->Top+s1c->Height/2-(c->Top+c->Height/2))/(float)s1c->Height*fabs(b->h);
  }

  if (Collided(c,s2c)) {
    b->h = -fabs(b->h);
    b->v = (float)-(s2c->Top+s2c->Height/2-(c->Top+c->Height/2))/(float)s2c->Height*fabs(b->h);
  }

  if (b->x<-16) {
    b->x = GameForm->GameBox->Width/2-GameForm->Ball->Width/2;
    b->y = GameForm->GameBox->Height/2-GameForm->Ball->Height/2;
    do { b->h = rand()%4-2; } while(b->h==0);
    b->v = (int)(rand()%4-2);
    if (b->v==0) b->v=.0000001;
    return 2;
  }

  if (b->x>BWMAX+16) {
    b->x = GameForm->GameBox->Width/2-GameForm->Ball->Width/2;
    b->y = GameForm->GameBox->Height/2-GameForm->Ball->Height/2;
    do { b->h = rand()%4-2; } while(b->h==0);
    b->v = (rand()%4)-2;
    if (b->v==0) b->v=.0000001;
    return 1;
  }

  return 0;
}
//---------------------------------------------------------------------------
void UpdateBall(Obj* b, TControl* c) {
  c->Left = b->x;
  c->Top = b->y;

  b->x += b->h;
  b->y += b->v;
}
//---------------------------------------------------------------------------
void ControlStick(Obj* b, TControl* c) {
  if (b->v<VFRIC && b->v>-VFRIC) b->v=0;
  if (b->v>0) b->v-=VFRIC;
  if (b->v<0) b->v+=VFRIC;

  b->y += b->v;

  if (b->y<0) {
    b->v=-b->v/2;
    b->y=0;
  }

  if (b->y>PMAX) {
    b->v=-b->v/2;
    b->y=PMAX;
  }

  if (GetAsyncKeyState(VK_UP)) {
    if (b->v>-VMAX)b->v-=.5;
  }

  if (GetAsyncKeyState(VK_DOWN)) {
    if (b->v<VMAX)b->v+=.5;
  }

  c->Left = b->x;
  c->Top = b->y;
}
//---------------------------------------------------------------------------

void __fastcall TGameForm::FormDestroy(TObject *Sender)
{
  if (server!=NULL) {
    delete server;
    server = NULL;
  }

  if (client!=NULL) {
    delete client;
    client = NULL;
  }

  Close39();
}
//---------------------------------------------------------------------------

void __fastcall TGameForm::EndGame1Click(TObject *Sender)
{
  if (server!=NULL) {
    delete server;
    server = NULL;
  }

  if (client!=NULL) {
    delete client;
    client = NULL;
  }

  p1score = 0;
  p2score = 0;
  ball.x = GameBox->Width/2-Ball->Width/2;
  ball.y = GameBox->Height/2-Ball->Height/2;
  ball.h = 0;
  ball.v = 0;

  UpdateBall(&ball,Ball);

  HostTimer->Enabled=0;
  ClientTimer->Enabled = 0;

  EndGame1->Enabled = 0;
  Host1->Enabled = 1;
  Join1->Enabled = 1;

  LStatus->Caption = "NETWORK PONG";
  LStatus->Visible = 1;
  Refresh(); 
}
//---------------------------------------------------------------------------

void __fastcall TGameForm::JoinButtonClick(TObject *Sender)
{
  if (server!=NULL) {
    delete server;
    server = NULL;
  }

  if (client!=NULL) {
    delete client;
    client = NULL;
  }

  JoinBox->Visible = 0;

  client = new ClientSocket();
  LStatus->Caption = "Looking for Host\nPlease Wait...";
  GameForm->Refresh();
  if (client->Connect(IPEdit->Text.c_str(),port)!=-1) {
    ClientTimer->Enabled = 1;
    LStatus->Visible = 0;
    EndGame1->Enabled = 1;
    Host1->Enabled = 0;
    Join1->Enabled = 0;
  } else {
    delete client;
    client = NULL;
    LStatus->Caption = "Failed to find a game";
  }        
}
//---------------------------------------------------------------------------

