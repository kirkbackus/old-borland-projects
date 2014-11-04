//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "quicksnap.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TQSnap *QSnap;
HDC scr;
bool snapshot = 0;
int shot=0;
String dir;
//---------------------------------------------------------------------------
__fastcall TQSnap::TQSnap(TComponent* Owner)
        : TForm(Owner)
{
  scr = GetDC(0); //Gets the handle of the screen
}
//---------------------------------------------------------------------------
void __fastcall TQSnap::QSnapTimerTimer(TObject *Sender)
{
  if (GetAsyncKeyState(VK_SHIFT)) {
    if (GetAsyncKeyState(VK_RETURN)) {
      if (snapshot==0) {
        BitBlt(QSnapImage->Canvas->Handle, 0, 0, Screen->Width, Screen->Height, scr, 0, 0, SRCCOPY);
        QSnapImage->Refresh();
        QSnapImage->Picture->SaveToFile(dir+"\\"+QSnapName->Text+((String)shot).c_str()+".bmp");
        shot++;
        snapshot=1;
      }
    } else snapshot=0;
  }
}
//---------------------------------------------------------------------------
void __fastcall TQSnap::FormResize(TObject *Sender)
{
  QSnapImage->Refresh();        
}
//---------------------------------------------------------------------------


void __fastcall TQSnap::QSnapButtonClick(TObject *Sender)
{
  QSnapButton->Visible=0;
  QSnapDir->Visible=0;
  QSnapName->Visible=0;
  dir = QSnapDir->Directory;
  QSnapImage->Width = Screen->Width;
  QSnapImage->Height = Screen->Height;
}
//---------------------------------------------------------------------------

