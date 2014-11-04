//---------------------------------------------------------------------------
#include <vector.h>
#include <math.h>

#include <vcl.h>
#pragma hdrstop

#include <iostream.h>

#include "blackbox.cpp"

#include "db3options.h"
#include "enum.h"

using namespace Blackbox;

vector<Blackbox::Polygon*> windows;
Blackbox::Polygon ball;

bool drag;
bool cls = 0;

POINT mousepos;
POINT mouseppos;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
TBallForm *BallForm;

int __stdcall EnumWindowsProc(HWND hWnd, long lParam) {
  RECT tmp;
  long style;

  if (!hWnd) return true;
  if (hWnd==BallForm->Handle) return true;
  if (!IsWindowVisible(hWnd)) return true;

  style = GetWindowLong(hWnd,GWL_STYLE);
  if (style & WS_EX_APPWINDOW != WS_EX_APPWINDOW) return true;

  GetWindowRect(hWnd,&tmp);

  windows.push_back(new Blackbox::Polygon());
  windows[windows.size()-1]->position = Vector((tmp.right-tmp.left)/2,(tmp.bottom-tmp.top)/2);

  windows[windows.size()-1]->AddPoint(tmp.left-windows[windows.size()-1]->position.x,tmp.top-windows[windows.size()-1]->position.y);
  windows[windows.size()-1]->AddPoint(tmp.right-windows[windows.size()-1]->position.x,tmp.top-windows[windows.size()-1]->position.y);
  windows[windows.size()-1]->AddPoint(tmp.right-windows[windows.size()-1]->position.x,tmp.bottom-windows[windows.size()-1]->position.y);
  windows[windows.size()-1]->AddPoint(tmp.left-windows[windows.size()-1]->position.x,tmp.bottom-windows[windows.size()-1]->position.y);

  return true;
}

//---------------------------------------------------------------------------
__fastcall TBallForm::TBallForm(TComponent* Owner)
        : TForm(Owner)
{
  ShowWindow(Application->Handle,0);
  SetWindowLong(Application->Handle,GWL_EXSTYLE,WS_EX_TOOLWINDOW);
  ShowWindow(Application->Handle,1);

  BallForm->Width = 64;
  BallForm->Height = 64;

  collide_windows = 1;
  fric = .3;
  gravity = 1; 

  ball.AddPoint(-32,-32);
  ball.AddPoint(32,-32);
  ball.AddPoint(32,32);
  ball.AddPoint(-32,32);

  ball.position = Vector(BallForm->Left+32, BallForm->Height+32);

  EnumWindows((WNDENUMPROC)EnumWindowsProc, 0);
}
//---------------------------------------------------------------------------
void __fastcall TBallForm::BallTimerTimer(TObject *Sender)
{
  mouseppos = mousepos;
  GetCursorPos(&mousepos);

  FormOptions->LPosition->Caption = "Position: ("+String((int)ball.position.x)+","+String((int)ball.position.y)+")";
  FormOptions->LVelocity->Caption = "Velocity: ("+String((int)ball.velocity.x)+","+String((int)ball.velocity.y)+")";

  if (drag) {
    ball.position.x = mousepos.x;
    ball.position.y = mousepos.y;
    ball.velocity.x = 0;
    ball.velocity.y = 0;

    if (!GetAsyncKeyState(VK_LBUTTON)) {
      ball.velocity.x = mousepos.x-mouseppos.x;
      ball.velocity.y = mousepos.y-mouseppos.y;
      drag = 0;
    } else if (GetAsyncKeyState(VK_RBUTTON)) {
      cls=1;
    } else if (cls==1) {
      Close();
    }
  } else {
    ball.velocity.y+=gravity;
    ball.position+=ball.velocity;

    if (ball.velocity.x > fric) ball.velocity.x -= fric;
    else if (ball.velocity.x < -fric) ball.velocity.x += fric;
    else ball.velocity.x = 0;

    for (unsigned int i=0;i<windows.size();i++) {
      if (ball.Collided(windows[i]) && collide_windows) {
        if (ball.position.y < windows[i]->GetAPointY(0)-30+ball.velocity.y) {
          ball.position.y = windows[i]->GetAPointY(0)-32;
          ball.velocity.y = -fabs(ball.velocity.y);
          ball.velocity.y/=(1+fric);
        }
        if (ball.position.y > windows[i]->GetAPointY(2)+30+ball.velocity.y) {
          ball.position.y = windows[i]->GetAPointY(2)+32;
          ball.velocity.y = fabs(ball.velocity.y);
        }
        if (ball.position.x < windows[i]->GetAPointX(0)-30+ball.velocity.x) {
          ball.position.x = windows[i]->GetAPointX(0)-32;
          ball.velocity.x = -fabs(ball.velocity.x);
        }
        if (ball.position.x > windows[i]->GetAPointX(2)+30+ball.velocity.x) {
          ball.position.x = windows[i]->GetAPointX(2)+32;
          ball.velocity.x = fabs(ball.velocity.x);
        }
        break;
      }
    }

    if (ball.position.y > Screen->Height-32) {
      ball.position.y = Screen->Height-32;
      ball.velocity.y = -fabs(ball.velocity.y);
      ball.velocity.y/=(1+fric);
    }

    if (ball.position.y < 32) {
      ball.position.y = 32;
      ball.velocity.y = fabs(ball.velocity.y);
    }

    if (ball.position.x < 32) {
      ball.position.x = 32;
      ball.velocity.x = fabs(ball.velocity.x);
    }

    if (ball.position.x > Screen->Width-32) {
      ball.position.x = Screen->Width-32;
      ball.velocity.x = -fabs(ball.velocity.x);
    }
  }

  BallForm->Left = ball.position.x-32;
  BallForm->Top = ball.position.y-32;
}
//---------------------------------------------------------------------------

void __fastcall TBallForm::SBallMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  if (GetAsyncKeyState(VK_LBUTTON)) drag = 1;
}
//---------------------------------------------------------------------------


void __fastcall TBallForm::WindowTimerTimer(TObject *Sender)
{
  for (unsigned int i=0;i<windows.size();) {
    delete windows[i];
    windows.erase(windows.begin()+i);
  }
  EnumWindows((WNDENUMPROC)EnumWindowsProc, 0);
}
//---------------------------------------------------------------------------

void __fastcall TBallForm::Quit1Click(TObject *Sender)
{
  Close();        
}
//---------------------------------------------------------------------------

void __fastcall TBallForm::StopBall1Click(TObject *Sender)
{
  ball.velocity = Vector(0,0);        
}
//---------------------------------------------------------------------------

void __fastcall TBallForm::FormClose(TObject *Sender, TCloseAction &Action)
{
  DBallTray->Visible=0;
}
//---------------------------------------------------------------------------

void __fastcall TBallForm::ShowOptions1Click(TObject *Sender)
{
  FormOptions->Visible = 1;
}
//---------------------------------------------------------------------------
