//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "dball.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
TForm1 *Form1;
int ballnum=0;

float grav=.2;
float hfric=.075;
float vfric=.00;
float xx[30],yy[30],hsp[30],vsp[30];

POINT cursor,pcursor;
bool drag[30];
bool gdrag;

TShape *balls[30];

int ballindex;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
  randomize();

  SetWindowLong(Application->Handle,GWL_EXSTYLE,WS_EX_TOOLWINDOW);

  Ball[ballnum] = new TForm(this);
  SetWindowLong(Ball[ballnum]->Handle,GWL_EXSTYLE,WS_EX_TOOLWINDOW);
  Ball[ballnum]->TransparentColor = true;
  Ball[ballnum]->TransparentColorValue = (TColor)RGB(255,255,254);
  Ball[ballnum]->BorderStyle = bsToolWindow;
  Ball[ballnum]->AlphaBlend = 1;
  Ball[ballnum]->AlphaBlendValue = TrackBar2->Position;
  Ball[ballnum]->Color = (TColor)RGB(255,255,254);
  Ball[ballnum]->BorderStyle = bsNone;
  Ball[ballnum]->Left = rand()%(Screen->Width-64);
  Ball[ballnum]->Top = rand()%(Screen->Height/2-64);
  Ball[ballnum]->Visible = 1;

  xx[ballnum]=(float)Ball[ballnum]->Left;
  yy[ballnum]=(float)Ball[ballnum]->Top;
  hsp[ballnum]=rand()%50-25;
  vsp[ballnum]=0;

  TShape *ball = new TShape(Ball[ballnum]);
  Ball[ballnum]->InsertControl(ball);
  ball->Brush->Color = (TColor)RGB(rand()%128+127,rand()%128+127,rand()%128+127);
  ball->Shape = stCircle;
  ball->Left = 0;
  ball->Top = 0;
  ball->Width = 64;
  ball->Height = 64;

  balls[ballnum]=ball;

  ComboBox1->ItemIndex = ballnum;

  ballnum++;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
  if (ballnum < 30) {
    Ball[ballnum] = new TForm(this);
    SetWindowLong(Ball[ballnum]->Handle,GWL_EXSTYLE,WS_EX_TOOLWINDOW);
    Ball[ballnum]->TransparentColor = true;
    Ball[ballnum]->TransparentColorValue = (TColor)RGB(255,255,254);
    Ball[ballnum]->AlphaBlend = 1;
    Ball[ballnum]->AlphaBlendValue = TrackBar2->Position;
    Ball[ballnum]->BorderStyle = bsToolWindow;
    Ball[ballnum]->Color = (TColor)RGB(255,255,254);
    Ball[ballnum]->BorderStyle = bsNone;
    Ball[ballnum]->Left = rand()%(Screen->Width-64);
    Ball[ballnum]->Top = rand()%(Screen->Height/2-64);
    Ball[ballnum]->Visible = 1;

    hsp[ballnum]=rand()%50-25;
    vsp[ballnum]=0;

    xx[ballnum]=(float)Ball[ballnum]->Left;
    yy[ballnum]=(float)Ball[ballnum]->Top;

    TShape *ball = new TShape(Ball[ballnum]);
    Ball[ballnum]->InsertControl(ball);
    ball->Brush->Color = (TColor)RGB(rand()%128,rand()%128,rand()%128);
    ball->Pen->Color = clWindowText;
    ball->Shape = stCircle;
    ball->Left = 0;
    ball->Top = 0;
    ball->Width = 64;
    ball->Height = 64;
    Ball[ballnum]->FormStyle = fsStayOnTop;

    balls[ballnum]=ball;

    ComboBox1->Items->Add("Ball "+IntToStr(ballnum+1));

    ballnum++;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
  //Get Mouse Position / Previous position
  pcursor.x = cursor.x;
  pcursor.y = cursor.y;
  GetCursorPos(&cursor);

  for (int i=0;i<ballnum;i++) {
    //Gravity
    vsp[i]+=grav;

    //Move ball
    xx[i]+= hsp[i];
    yy[i]+= vsp[i];

    if (hsp[i]>100)hsp[i]=100;
    if (vsp[i]>100)vsp[i]=100;
    if (hsp[i]<-100)hsp[i]=-100;
    if (vsp[i]<-100)vsp[i]=-100;

    //Limit Left
    if (xx[i]<=0) {
      xx[i]=0;
      hsp[i]=-hsp[i];
    }

    //Limit Right
    if (xx[i]>=Screen->Width-64) {
      xx[i]=Screen->Width-64;
      hsp[i]=-hsp[i];
    }

    //Limit top
    if (yy[i]<=0) {
      yy[i]=0;
      vsp[i]=-vsp[i];
    }

    //Limit ground
    if (yy[i]>=Screen->Height-64) {
      yy[i]=Screen->Height-64;
      vsp[i]=-vsp[i];
      vsp[i]/=1.4;
    }

    //Friction Horizontal
    if (hsp[i]<0)hsp[i]+=hfric;
    if (hsp[i]>0)hsp[i]-=hfric;
    if (hsp[i]<hfric && hsp[i]>-hfric)hsp[i]=0;
    //Vertical Friction
    if (vsp[i]<0)vsp[i]+=vfric;
    if (vsp[i]>0)vsp[i]-=vfric;
    if (vsp[i]<vfric && vsp[i]>-vfric)vsp[i]=0;

    if (!Ball[i]->Visible)Ball[i]->Visible=1;

    //Collision
    for (int c=0;c<ballnum;c++) {
      if (c > i) {
        float dir,force,dir2,force2;
        //Check distances for collisions
        if (point_distance(xx[i],yy[i],xx[c],yy[c])<64) {
          dir=point_direction(xx[i],yy[i],xx[c],yy[c]);
          force=lengthdir_x(1,dir)*hsp[i]+lengthdir_y(1,dir)*vsp[i];
          dir2=point_direction(xx[c],yy[c],xx[i],yy[i]);
          force2=lengthdir_x(1,dir2)*hsp[c]+lengthdir_y(1,dir2)*vsp[c];

          //Move them away from eachother
          int itr=0;
          if (!(xx[i]==xx[c] && yy[i]==yy[c]))
          while (point_distance(xx[i],yy[i],xx[c],yy[c])<64) {
            xx[i]-=lengthdir_x(1,dir+180);
            yy[i]-=lengthdir_y(1,dir+180);
            xx[c]-=lengthdir_x(1,dir2+180);
            yy[c]-=lengthdir_y(1,dir2+180);
            if (itr > 1000) break;
            itr++;
          }

          //Simulate motion add
          hsp[c]+=lengthdir_x(-(force2+force),dir+180);
          vsp[c]+=lengthdir_y(-(force2+force),dir+180);
          hsp[i]+=lengthdir_x(-(force+force2),dir2+180);
          vsp[i]+=lengthdir_y(-(force+force2),dir2+180);
        }
      }
    }

    //Drag ball with mouse
    if (!drag[i]) {
      if (GetAsyncKeyState(VK_LBUTTON) && !gdrag) {
        if (point_distance(cursor.x,cursor.y,xx[i]+32,yy[i]+32)<64) {
          drag[i]=1;
          gdrag = 1;
        }
      }
    } else {
      if (!GetAsyncKeyState(VK_LBUTTON)) {
        drag[i]=false;
        hsp[i]=cursor.x-pcursor.x;
        vsp[i]=cursor.y-pcursor.y;
        gdrag = 0;
      } else {
        hsp[i]=(cursor.x-32)-xx[i];
        vsp[i]=(cursor.y-32)-yy[i];
      }
    }

    //Limit top
    if (Ball[i]->Top >= Screen->Height-64)
    hsp[i] /= 1.1;

    //Move form on the screen
    Ball[i]->Left = xx[i];
    Ball[i]->Top = yy[i];
  }

  Label1->Caption = "Number of Balls: "+IntToStr(ballnum);
  Label2->Caption = "Gravity: "+IntToStr((int)(20*grav));

  if (ballindex >= 0) {
    Label3->Caption = "X: "+IntToStr(Ball[ballindex]->Left)+
    "\nY: "+IntToStr(Ball[ballindex]->Top)+
    "\nHor Speed: "+IntToStr((int)(hsp[ballindex]*100.0))+
    "\nVrt Speed: "+IntToStr((int)(vsp[ballindex]*100.0));
    Shape1->Brush->Color = balls[ballindex]->Brush->Color;
  }
  else
  Label3->Caption = "No ball selected";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
  if (ballnum > 0) {
    Ball[ballnum-1]->Close();
    delete Ball[ballnum-1];
    ComboBox1->Items->Delete(ballnum-1);
    if (ballnum-1==ballindex)ballindex -= 1;
    ComboBox1->ItemIndex = ballindex;
    Shape1->Brush->Color = clWhite;
    ballnum-=1;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TrackBar1Change(TObject *Sender)
{
  grav = (float)TrackBar1->Position/20.0;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
  for (int i=0;i<ballnum;i++) {
    hsp[i]=0;
    vsp[i]=0;
  }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
  ballindex = ComboBox1->ItemIndex;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
  if (ballindex >= 0) {
    hsp[ballindex]=0;
    vsp[ballindex]=0;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
  if (ColorDialog1->Execute() && ballindex >= 0)
  balls[ballindex]->Brush->Color=ColorDialog1->Color;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
  Visible=0;        
}
//---------------------------------------------------------------------------


void __fastcall TForm1::TrayIcon1Click(TObject *Sender)
{
  Visible = 1;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ShowOptions1Click(TObject *Sender)
{
  Visible = 1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AddBall1Click(TObject *Sender)
{
    if (ballnum < 10) {
    Ball[ballnum] = new TForm(this);
    SetWindowLong(Ball[ballnum]->Handle,GWL_EXSTYLE,WS_EX_TOOLWINDOW);
    Ball[ballnum]->TransparentColor = true;
    Ball[ballnum]->TransparentColorValue = (TColor)RGB(255,255,254);
    Ball[ballnum]->Color = (TColor)RGB(255,255,254);
    Ball[ballnum]->BorderStyle = bsNone;
    Ball[ballnum]->Left = rand()%(Screen->Width-64);
    Ball[ballnum]->Top = rand()%(Screen->Height/2-64);
    Ball[ballnum]->Visible = 1;

    hsp[ballnum]=rand()%50-25;
    vsp[ballnum]=0;

    xx[ballnum]=(float)Ball[ballnum]->Left;
    yy[ballnum]=(float)Ball[ballnum]->Top;

    TShape *ball = new TShape(Ball[ballnum]);
    Ball[ballnum]->InsertControl(ball);
    ball->Brush->Color = (TColor)RGB(rand()%128,rand()%128,rand()%128);
    ball->Pen->Color = clWindowText;
    ball->Shape = stCircle;
    ball->Left = 0;
    ball->Top = 0;
    ball->Width = 64;
    ball->Height = 64;
    Ball[ballnum]->FormStyle = fsStayOnTop;

    balls[ballnum]=ball;

    ComboBox1->Items->Add("Ball "+IntToStr(ballnum+1));

    ballnum++;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EraseBall1Click(TObject *Sender)
{
  if (ballnum > 0) {
    Ball[ballnum-1]->Close();
    delete Ball[ballnum-1];
    ComboBox1->Items->Delete(ballnum-1);
    if (ballnum-1==ballindex)ballindex -= 1;
    ComboBox1->ItemIndex = ballindex;
    Shape1->Brush->Color = clWhite;
    ballnum-=1;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FreezeBalls1Click(TObject *Sender)
{
  for (int i=0;i<ballnum;i++) {
    hsp[i]=0;
    vsp[i]=0;
  }        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Quit1Click(TObject *Sender)
{
  Close();        
}
//---------------------------------------------------------------------------


void __fastcall TForm1::TrackBar2Change(TObject *Sender)
{
  for (int i=0;i<ballnum;i++) {
    if (TrackBar2->Position==255) Ball[i]->AlphaBlend = 0;
    else Ball[i]->AlphaBlend=1;
    Ball[i]->AlphaBlendValue = TrackBar2->Position;
  }
}
//---------------------------------------------------------------------------


