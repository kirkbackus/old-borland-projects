//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "connect4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TC4Form *C4Form;
int board[7][6];
bool bwin[7][6];
bool turn=0;
bool gameover=0;
int px=0,py=0,pv=0;
int mx=0,my=0;
bool fall=0;
int fallheight=0;

const int xsep=48;
const int ysep=48;

int CheckForWin();
bool CheckForTie();

//---------------------------------------------------------------------------
__fastcall TC4Form::TC4Form(TComponent* Owner)
        : TForm(Owner)
{
  DoubleBuffered=1;
  GameBox->DoubleBuffered=1;
  for (int x=0;x<7;x++) {
    for (int y=0;y<6;y++) {
      board[x][y]=0;
      bwin[x][y]=0;
    }
  }

  ClientWidth = 336;
  ClientHeight = 421;

  Constraints->MaxWidth = Width;
  Constraints->MaxHeight = Height;
  Constraints->MinWidth = Width;
  Constraints->MinHeight = Height;
}
//---------------------------------------------------------------------------

void __fastcall TC4Form::NewGame1Click(TObject *Sender)
{
  gameover = 0;
  fall = 0;
  for (int x=0;x<7;x++) {
    for (int y=0;y<6;y++) {
      board[x][y]=0;
      bwin[x][y]=0;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TC4Form::Exit1Click(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TC4Form::GameTimerTimer(TObject *Sender)
{
  if (!gameover) {
    if (!fall) {
      if ((int)mx/48>TmpCircle->Left/xsep) {
        TmpCircle->Left+=(((int)mx/xsep)*xsep-TmpCircle->Left)/2;
      }

      if ((int)mx/48<(TmpCircle->Left/48+1)) {
        TmpCircle->Left-=(TmpCircle->Left-((int)mx/xsep)*xsep)/2;
      }
    } else {
      pv+=1;
      TmpCircle->Left=px*48;
      TmpCircle->Top+=pv;
      if (TmpCircle->Top>fallheight) {
        TmpCircle->Top=fallheight;
        pv=-pv/2;
        if (abs(pv)<1) {
          fall = 0;
          pv = 0;
          board[px][py]=turn+1;
          TmpCircle->Top = 0;
          turn=!turn;
          if (turn==0) {
            C4StatusBar->Panels->Items[0]->Text = " Player 1's Turn";
            TmpCircle->Brush->Color = clRed;
          } else {
            C4StatusBar->Panels->Items[0]->Text = " Player 2's Turn";
            TmpCircle->Brush->Color = clBlue;
          }
          int twin = CheckForWin();
          if (twin) {
            if (twin==1) C4StatusBar->Panels->Items[0]->Text = " Player 1 Wins! - Press Ctrl-N To Restart";
            else C4StatusBar->Panels->Items[0]->Text = " Player 2 Wins! - Press Ctrl-N To Restart";
            gameover = 1;
          }
          if (CheckForTie()) {
            gameover = 1;
            C4StatusBar->Panels->Items[0]->Text = " Cats Game! - Press Ctrl-N To Restart";
          }
        }
      }
    }
  }

  GameImg->Canvas->Pen->Color = clWhite;
  GameImg->Canvas->Brush->Color = clBlack;

  GameImg->Canvas->Rectangle(0,0,GameImg->Width,GameImg->Height);

  for (int x=0;x<8;x++) {
    GameImg->Canvas->MoveTo(x*xsep,ysep);
    GameImg->Canvas->LineTo(x*xsep,7*ysep);
  }
  for (int y=1;y<8;y++) {
    GameImg->Canvas->MoveTo(0,y*ysep);
    GameImg->Canvas->LineTo(7*xsep,y*ysep);
  }

  for (int x=0;x<7;x++) {
    for (int y=1;y<7;y++) {
      if (board[x][y-1]>0) {
        if (board[x][y-1]==1) GameImg->Canvas->Brush->Color = clRed;
        else if (board[x][y-1]==2) GameImg->Canvas->Brush->Color = clBlue;
        else GameImg->Canvas->Brush->Color = clGreen;
        GameImg->Canvas->Ellipse(x*xsep,y*ysep,(x+1)*xsep,(y+1)*ysep);
      }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TC4Form::GameImgMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
  mx = X;
  my = Y;
}
//---------------------------------------------------------------------------
void __fastcall TC4Form::GameImgMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  if (fall) return;
  
  int tx,th;
  tx = (int)(mx/xsep);

  int i;
  for (i=0;i<6;i++) {
    if (board[tx][i]!=0) break;
  }

  th = i;

  px = tx;
  py = th-1;

  if (th>0) {
    fall = 1;
    fallheight = th*ysep;
  }
}
//---------------------------------------------------------------------------
void __fastcall TC4Form::About1Click(TObject *Sender)
{
  ShowMessage("----| Connect 4 |----\n by Kirk Backus\n\nPlayers take turns to try to\nget four of thier peices\nnext to eachother horizontally,\nvertically, or diagonally");
}
//---------------------------------------------------------------------------

void __fastcall TC4Form::N201Click(TObject *Sender)
{
  C4Form->AlphaBlend = 1;
  C4Form->AlphaBlendValue = 204;
}
//---------------------------------------------------------------------------

void __fastcall TC4Form::N401Click(TObject *Sender)
{
  C4Form->AlphaBlend = 1;
  C4Form->AlphaBlendValue = 153;
}
//---------------------------------------------------------------------------

void __fastcall TC4Form::N601Click(TObject *Sender)
{
  C4Form->AlphaBlend = 1;
  C4Form->AlphaBlendValue = 102;
}
//---------------------------------------------------------------------------

void __fastcall TC4Form::N801Click(TObject *Sender)
{
  C4Form->AlphaBlend = 1;
  C4Form->AlphaBlendValue = 51;
}
//---------------------------------------------------------------------------
void __fastcall TC4Form::N901Click(TObject *Sender)
{
  C4Form->AlphaBlend = 1;
  C4Form->AlphaBlendValue = 25;
}
//---------------------------------------------------------------------------
void __fastcall TC4Form::Opaque1Click(TObject *Sender)
{
  C4Form->AlphaBlend = 0;
  C4Form->AlphaBlendValue = 255;
}
//---------------------------------------------------------------------------
bool CheckForTie() {
  for (int x=0;x<7;x++) for(int y=0;y<6;y++) {
    if (board[x][y]==0) return 0;
  }
  return 1;
}
//---------------------------------------------------------------------------
int CheckForWin() {
  int ret=0;
  for (int i=1;i<=2;i++) {
    for (int x=0;x<4;x++) {
      for (int y=0;y<3;y++) {
        if (board[x][y]==i && board[x+1][y]==i && board[x+2][y]==i && board[x+3][y]==i) {
          bwin[x][y]=1; bwin[x+1][y]=1; bwin[x+2][y]=1; bwin[x+3][y]=1;
          ret = i;
        }

        if (board[x][y]==i && board[x][y+1]==i && board[x][y+2]==i && board[x][y+3]==i) {
          bwin[x][y]=1; bwin[x][y+1]=1; bwin[x][y+2]=1; bwin[x][y+3]=1;
          ret = i;
        }

        if (board[x][y]==i && board[x+1][y+1]==i && board[x+2][y+2]==i && board[x+3][y+3]==i) {
          bwin[x][y]=1; bwin[x+1][y+1]=1; bwin[x+2][y+2]=1; bwin[x+3][y+3]=1;
          ret = i;
        }
      }
    }

    for (int x=0;x<4;x++) {
      for (int y=3;y<6;y++) {
        if (board[x][y]==i && board[x+1][y]==i && board[x+2][y]==i && board[x+3][y]==i) {
          bwin[x][y]=1; bwin[x+1][y]=1; bwin[x+2][y]=1; bwin[x+3][y]=1;
          ret = i;
        }

        if (board[x][y]==i && board[x+1][y-1]==i && board[x+2][y-2]==i && board[x+3][y-3]==i) {
          bwin[x][y]=1; bwin[x+1][y-1]=1; bwin[x+2][y-2]=1; bwin[x+3][y-3]=1;
          ret = i;
        }
      }
    }

    for (int x=4;x<7;x++) {
      for (int y=0;y<3;y++) {
        if (board[x][y]==i && board[x][y+1]==i && board[x][y+2]==i && board[x][y+3]==i) {
          bwin[x][y]=1; bwin[x][y+1]=1; bwin[x][y+2]=1; bwin[x][y+3]=1;
          ret = i;
        }

        if (board[x][y]==i && board[x-1][y+1]==i && board[x-2][y+2]==i && board[x-3][y+3]==i) {
          bwin[x][y]=1; bwin[x-1][y+1]=1; bwin[x-2][y+2]=1; bwin[x-3][y+3]=1;
          ret = i;
        }
      }
    }
  }

  for (int x=0;x<7;x++) for (int y=0;y<6;y++) if (bwin[x][y]) board[x][y]=3;

  return ret;
}

void __fastcall TC4Form::RemoveFromTaskbar1Click(TObject *Sender)
{
  RemoveFromTaskbar1->Checked=!RemoveFromTaskbar1->Checked;
  if (!RemoveFromTaskbar1->Checked) {
    ShowWindow(Application->Handle,0);
    SetWindowLong(Application->Handle,GWL_EXSTYLE,WS_EX_TOOLWINDOW);
    ShowWindow(Application->Handle,1);
  } else {
    ShowWindow(Application->Handle,0);
    SetWindowLong(Application->Handle,GWL_EXSTYLE,WS_EX_APPWINDOW);
    ShowWindow(Application->Handle,1);
  }
}
//---------------------------------------------------------------------------

