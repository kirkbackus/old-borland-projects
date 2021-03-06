//---------------------------------------------------------------------------
#define MAX(a, b) (a > b) ? a : b
#define QuickMessage(a) MessageBoxA(NULL,a,"Bomb Blox",MB_OK)
#include <vcl.h>
#pragma hdrstop

#include "bomberman.h"
#define MAXBOMBS 8
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TBombForm *BombForm;
HINSTANCE hInstance;
Player* p1;
Field* field;
TImage* bmp;
Bomb* bomb[MAXBOMBS];
Explosion* explosion[MAXBOMBS];
Textures* textures;
int cbomb;
int cexpl;
int ctrl_press = 0;

//---------------------------------------------------------------------------
__fastcall TBombForm::TBombForm(TComponent* Owner)
        : TForm(Owner)
{
  Application->OnIdle = IdleLoop;

  hInstance = (HINSTANCE)GetWindowLong(BombForm->Handle, GWL_HINSTANCE);
  textures = new Textures(hInstance);

  if (!textures->AddTexture16("guy.bmp",1,0)) QuickMessage("Failed to load guy.bmp");
  if (!textures->AddTexture16("solid.bmp",2,0)) QuickMessage("Failed to load solid.bmp");

  p1 = new Player();
  field = new Field(textures);

  field->SetImage(0,2);
  p1->SetField(field);

  for (int i=0;i<21;i++) {
    field->SetPosition(i,0,1);
    field->SetPosition(i,20,1);
    field->SetPosition(0,i,1);
    field->SetPosition(20,i,1);
  }

  for (int i=0;i<8;i++) {
    bomb[i] = new Bomb();
    bomb[i]->SetImage(1);
  }

  for (int i=0;i<8;i++) {
    explosion[i] = new Explosion();
    explosion[i]->SetField(field);

    explosion[i]->SetImage(1);
  }

  cexpl = 0;

  for (int x=0;x<21;x+=2) for (int y=0;y<21;y+=2) field->SetPosition(x,y,1);
}
//---------------------------------------------------------------------------
void __fastcall TBombForm::FormPaint(TObject *Sender)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  DrawObjects();
  glFlush();
}

//---------------------------------------------------------------------------
void __fastcall TBombForm::IdleLoop(TObject*, bool& done)
{
  done = false;

  for (int i=0;i<MAXBOMBS;i++) {
    if (bomb[i]->Explode()) explosion[cexpl]->Explode(bomb[i]->GetX(),bomb[i]->GetY(),8);
    if (++cexpl>=MAXBOMBS)cexpl = 0;
    for (int n=0;n<MAXBOMBS;n++) {
      if (bomb[n]->Destroyed())continue;
      RECT tmp; tmp.left = bomb[n]->GetX(); tmp.top = bomb[n]->GetY();
      tmp.right = 16; tmp.bottom = 16;
      if (explosion[i]->CollisionRect(tmp)) {
        bomb[n]->BlowUp();
      }
    }
  }

  for (int i=0;i<MAXBOMBS;i++) explosion[i]->Draw();

  RenderGLScene();
  SwapBuffers(hdc);
}
//---------------------------------------------------------------------------
void __fastcall TBombForm::RenderGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    DrawObjects();
    glFlush();
}
//---------------------------------------------------------------------------
void __fastcall TBombForm::DrawObjects()
{
   glLoadIdentity();
   textures->SetTexture(1);
   field->Draw();   
   for (int i=0;i<8;i++) {
     if (!bomb[i]->Destroyed()) bomb[i]->Draw();
     explosion[i]->Draw();
   }
   p1->Draw();
}
//---------------------------------------------------------------------------

void __fastcall TBombForm::Timer1Timer(TObject *Sender)
{
  if (GetAsyncKeyState(VK_RIGHT)) p1->Move(1,0);
  if (GetAsyncKeyState(VK_LEFT)) p1->Move(-1,0);
  if (GetAsyncKeyState(VK_UP)) p1->Move(0,-1);
  if (GetAsyncKeyState(VK_DOWN)) p1->Move(0,1);
  if (GetAsyncKeyState(VK_CONTROL)) {
    if (ctrl_press==0) {
      ctrl_press = 1;
      int cst;
      cst = cbomb;
      while(!bomb[cbomb]->Ignite(p1->GetX(),p1->GetY(),3000)) {
        cbomb++;
        if (cbomb>=MAXBOMBS)cbomb=0;
        if (cbomb==cst)break;
      }
    }
  } else {
    ctrl_press = 0;
  }
}
//---------------------------------------------------------------------------

void __fastcall TBombForm::FormResize(TObject *Sender)
{
  ResizeGLWindow(0,0,ClientWidth,ClientHeight);
  SetViewOrtho(0,0,336,336,0);
}
//---------------------------------------------------------------------------

void __fastcall TBombForm::FormDestroy(TObject *Sender)
{
  DisableOpenGL(Handle,hdc,hrc);
}
//---------------------------------------------------------------------------

void __fastcall TBombForm::FormCreate(TObject *Sender)
{
  ClientWidth = 336;
  ClientHeight = 336;

  EnableOpenGL(Handle,&hdc,&hrc);
}
//---------------------------------------------------------------------------
