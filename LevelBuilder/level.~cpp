//---------------------------------------------------------------------------
#include <fstream.h>
#include <vector.h>
#include <vcl.h>
#pragma hdrstop

#include "opengl.h"
#include "level.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
HDC hdc;
HGLRC hrc;

int mx,my;
int ofx,ofy=-1;
int view_x=0;
int view_y=0;
int cvx,cvy=0;

struct TerPoints {
  float x,y;
};

struct TerCData {
  char name[20];
  char pass[20];
  int difficulty;
  float r;
  float g;
  float b;
};

int selected;

vector<TerPoints> terrain;
TerPoints start,end;
TerCData leveldata;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
  : TForm(Owner)
{
  Application->OnIdle = IdleLoop;
  SetWindowLong(Application->Handle,GWL_EXSTYLE,WS_EX_ACCEPTFILES);
  SetWindowLong(Form1->Handle,GWL_EXSTYLE,WS_EX_ACCEPTFILES);

  Tool=0;

  EnableOpenGL(ScrollBox1->Handle,&hdc,&hrc);
  SetViewOrtho(0,0,ScrollBox1->Width,ScrollBox1->Height);

  view_x=-ScrollBox1->Width/2;
  view_y=-ScrollBox1->Height/2;

  start.x=-10000;
  start.y=-10000;
  end.x=-10000;
  end.y=-10000;

  leveldata.r=GetRValue(EditColor->Brush->Color)/255;
  leveldata.g=GetGValue(EditColor->Brush->Color)/255;
  leveldata.b=GetBValue(EditColor->Brush->Color)/255;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::IdleLoop(TObject*, bool& done)
{
  done = false;

  SetViewOrtho(view_x,view_y,view_x+ScrollBox1->Width,view_y+ScrollBox1->Height);

  //Draw EVERY THING HERE!!!
  glClearColor (0.0f, 0.1f, 0.1f, 1.0f);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  for (int i=((int)(view_x/64))*64;i<ScrollBox1->Width+64+view_x;i+=32) {
    glColor3f(0.25,0.25,0.25);
    if (i%128==0)glColor3f(0.5,0.5,0.5);
    if (i%256==0)glColor3f(0.75,0.75,0.75);
    if (i==0)glColor3f(0.0,1.0,0.0);
    DrawLine(i,view_y,i,view_y+ScrollBox1->Height);
    glColor3f(1.0,1.0,1.0);
  }

  for (int i=((int)(view_y/64))*64;i<ScrollBox1->Height+64+view_y;i+=32) {
    glColor3f(0.25,0.25,0.25);
    if (i%128==0)glColor3f(0.5,0.5,0.5);
    if (i%256==0)glColor3f(0.75,0.75,0.75);
    if (i==0)glColor3f(0.0,1.0,0.0);
    DrawLine(view_x,i,view_x+ScrollBox1->Width,i);
    glColor3f(1.0,1.0,1.0);
  }

  for (int i=0;i<(signed)terrain.size();i++) {
    if (PointDistance(terrain[i].x,terrain[i].y,mx+view_x,my+view_y)<16) glColor3f(1.0,0.0,0.0);
    DrawPoint(terrain[i].x,terrain[i].y);
    glColor3f(1.0,1.0,1.0);
    if (i>0)DrawLine(terrain[i].x,terrain[i].y,terrain[i-1].x,terrain[i-1].y);
  }

  glColor3f(1.0,0.5,0.2);
  DrawPoint(start.x,start.y);
  glColor3f(0.2,0.5,1.0);
  DrawPoint(end.x,end.y);
  glColor3f(1.0,1.0,1.0);

  SwapBuffers(hdc);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Quit1Click(TObject *Sender)
{
  Form1->Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ScrollBox1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
  mx = X;
  my = Y;
  MStatusBar->Panels->Items[0]->Text="Mouse: "+(String)(X+view_x)+","+(String)(Y+view_y);

  //Moving the view
  if (GetAsyncKeyState(VK_RBUTTON)) {
    if (ofx==-1) {
      ofx=mx+view_x;
      ofy=my+view_y;
    }
    view_x=ofx-mx;
    view_y=ofy-my;
  } else {
    ofx=-1;
    ofy=-1;
  }

  if (GetAsyncKeyState(VK_LBUTTON)) {
    if (selected==-1) {
      for (int i=0;i<(signed)terrain.size();i++)
        if (PointDistance(mx+view_x,my+view_y,terrain[i].x,terrain[i].y)<16)
          selected=i;

    } else {
      if (terrain.size()>0) {
        terrain[selected].x=mx+view_x;
        terrain[selected].y=my+view_y;
      }
    }
  } else selected=-1;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SPointClick(TObject *Sender)
{
  AddRemovePoints1->Checked=1;
  Tool=0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SStartClick(TObject *Sender)
{
  StartingPoint1->Checked=1;
  Tool=1;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SEndClick(TObject *Sender)
{
  EndingPoint1->Checked=1;
  Tool=2;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::New1Click(TObject *Sender)
{
  view_x=-ScrollBox1->Width/2;
  view_y=-ScrollBox1->Height/2;
  terrain.clear();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ScrollBox1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  if (Tool==0) {
    if (GetAsyncKeyState(VK_LBUTTON)) {
      bool onpt=false;
      for (int i=0;i<(signed)terrain.size();i++) {
        if (PointDistance(mx+view_x,my+view_y,terrain[i].x,terrain[i].y)<16)
        onpt=true;
      }
      if (!onpt) {
        TerPoints tmp;
        tmp.x=mx+view_x;
        tmp.y=my+view_y;
        terrain.push_back(tmp);
      }
    }

    if (GetAsyncKeyState(VK_RBUTTON)) {
      float index=-1;
      for (int i=0;i<(signed)terrain.size();i++) {
        if (PointDistance(mx+view_x,my+view_y,terrain[i].x,terrain[i].y)<16) {
          index=i;
          break;
        }
      }
      if (index!=-1) terrain.erase(&terrain[index]);
    }
  }

  if (Tool==1 && GetAsyncKeyState(VK_LBUTTON)) {
    start.x=mx+view_x;
    start.y=my+view_y;
  }

  if (Tool==2 && GetAsyncKeyState(VK_LBUTTON)) {
    end.x=mx+view_x;
    end.y=my+view_y;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Save1Click(TObject *Sender)
{
  if (start.x==-10000) {
    MessageBox(Form1->Handle,"Please Add The Starting Point!","WAIT!!!",MB_OK);
    return;
  }

  if (end.x==-10000) {
    MessageBox(Form1->Handle,"Please Add The Ending Point!","WAIT!!!",MB_OK);
    return;
  }

  const char* fname;

  if (TerrainSave->Execute()) {
    fname=TerrainSave->FileName.c_str();

    ofstream tsave(fname, ios_base::out | ios_base::binary);

    if (!tsave.is_open()) {
      MessageBox(NULL,"Failed to save Terrain Data File","ERROR",MB_OK);
      return;
    }

    tsave.write((const char*)&leveldata,sizeof(TerCData));
    tsave.write((const char*)&start,sizeof(TerPoints));
    tsave.write((const char*)&end,sizeof(TerPoints));

    for (int i=0;i<(signed)terrain.size();i++) {
      tsave.write((const char*)&terrain[i], sizeof(TerPoints));
    }

    tsave.close();
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Open1Click(TObject *Sender)
{
  const char* fname;

  if (TerrainOpen->Execute()) {

    fname=TerrainOpen->FileName.c_str();

    ifstream topen(fname, ios_base::out | ios_base::binary);

    if (topen.is_open()) {
      view_x=-ScrollBox1->Width/2;
      view_y=-ScrollBox1->Height/2;
      terrain.clear();

      TerPoints tmp;

      topen.read((char*)&leveldata,sizeof(TerCData));
      topen.read((char*)&tmp,sizeof(TerPoints));
      start.x=tmp.x; start.y=tmp.y;
      topen.read((char*)&tmp,sizeof(TerPoints));
      end.x=tmp.x; end.y=tmp.y;

      while(!topen.eof()) {
        topen.read((char*)&tmp,sizeof(TerPoints));
        terrain.push_back(tmp);
      }

      EditName->Text = leveldata.name;
      EditDifficulty->ItemIndex = leveldata.difficulty-1;
      EditPassword->Text = leveldata.pass;
      EditColor->Brush->Color = RGB(leveldata.r*255,leveldata.g*255,leveldata.b*255);
      
    } else {
      MessageBox(NULL,"Failed to open Terrain Data File","ERROR",MB_OK);
      return;
    }

    topen.close();
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TerrainInfo1Click(TObject *Sender)
{
  char buffer[1024];
  if (start.x==-10000 && end.x==-10000)
  sprintf(buffer,"Number of Vertecies: %u\nStarting Point: UNDEFINED\nEnding Point: UNDEFINED",terrain.size());
  else if (start.x==-10000)
  sprintf(buffer,"Number of Vertecies: %u\nStarting Point: UNDEFINED\nEnding Point: (%.0f,%.0f)",terrain.size(),end.x,end.y);
  else if (end.x==-10000)
  sprintf(buffer,"Number of Vertecies: %u\nStarting Point: (%.0f,%.0f)\nEnding Point: UNDEFINED",terrain.size(),start.x,start.y);
  else
  sprintf(buffer,"Number of Vertecies: %u\nStarting Point: (%.0f,%.0f)\nEnding Point: (%.0f,%.0f)",terrain.size(),start.x,start.y,end.x,end.y);

  MessageBox(Form1->Handle,buffer,"Terrain Info",MB_OK);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StartingPoint1Click(TObject *Sender)
{
  StartingPoint1->Checked=1;
  SStart->Click();
  SStart->Down=1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EndingPoint1Click(TObject *Sender)
{
  EndingPoint1->Checked=1;
  SEnd->Click();
  SEnd->Down=1;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::AddRemovePoints1Click(TObject *Sender)
{
  AddRemovePoints1->Checked=1;
  SPoint->Click();
  SPoint->Down=1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::About1Click(TObject *Sender)
{
  char buffer[1024];
  sprintf(buffer,"2d Terrain Editor v1.0\n------------------------------------\n(c) 2008 Kirk Backus\n\nFor use in the game 'Planet Riders'");
  MessageBox(Form1->Handle,buffer,"About",MB_OK);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ResetView1Click(TObject *Sender)
{
  view_x=-ScrollBox1->Width/2;
  view_y=-ScrollBox1->Height/2;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ViewTimerTimer(TObject *Sender)
{
  HDROP hd;
  PostMessage(Form1->Handle,WM_DROPFILES,(WPARAM)hd,0);
  char buffer[128];
  if (DragQueryFile(hd,0xFFFFFFFF,buffer,128)<5) {
    MessageBox(NULL,buffer,"YAY",MB_OK);
  }

  for (int i=0;i<255;i++)GetAsyncKeyState(i);

  if (GetAsyncKeyState(VK_RIGHT)) {
    view_x+=32;
  }

  if (GetAsyncKeyState(VK_LEFT)) {
    view_x-=32;
  }

  if (GetAsyncKeyState(VK_UP)) {
    view_y-=32;
  }

  if (GetAsyncKeyState(VK_DOWN)) {
    view_y+=32;
  }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::EditColorMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  EditColorDB->Color=EditColor->Brush->Color;
  EditColorDB->Execute();
  EditColor->Brush->Color=EditColorDB->Color;

  leveldata.r=GetRValue(EditColor->Brush->Color)/255;
  leveldata.g=GetGValue(EditColor->Brush->Color)/255;
  leveldata.b=GetBValue(EditColor->Brush->Color)/255;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EditNameChange(TObject *Sender)
{
  sprintf(leveldata.name,"%s",EditName->Text.c_str());
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EditPasswordChange(TObject *Sender)
{
  sprintf(leveldata.pass,"%s",EditPassword->Text.c_str());
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EditDifficultyChange(TObject *Sender)
{
  leveldata.difficulty = EditDifficulty->ItemIndex+1;
}
//---------------------------------------------------------------------------

