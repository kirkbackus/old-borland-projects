//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "hacker.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

HDC hDC;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
  hDC = GetDC(0);
  randomize();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
  SetBkMode(hDC,1);

  for (int x=0;x<100;x++) {
    SetTextColor(hDC,RGB(rand()%255,rand()%255,rand()%255));
    TextOutA(hDC,rand()%Screen->Width,rand()%Screen->Height,"HACKER ALERT!!!",10);
  }

  //SetBkColor(hDC,clRed);

  //BitBlt(Form1->Canvas->Handle,0,0,Screen->Width,Screen->Height,hDC,0,0,SRCCOPY);

  if (GetAsyncKeyState(VK_ESCAPE))Close();
}
//---------------------------------------------------------------------------
