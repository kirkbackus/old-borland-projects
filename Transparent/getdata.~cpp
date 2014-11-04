//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "getdata.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
POINT mouse;
void* hid;
int tval=255;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
  GetCursorPos(&mouse);
  hid = WindowFromPoint(mouse);

  char title[100];
  GetWindowText(hid,title,100);

  if (GetAsyncKeyState(VK_SHIFT)) {
    if (tval!=255) {
      SetWindowLongPtr(hid,GWL_EXSTYLE,WS_EX_TRANSPARENT);
      SetWindowLongPtr(hid,GWL_EXSTYLE,WS_EX_LAYERED);
      SetLayeredWindowAttributes(hid, 0, TrackBar1->Position, LWA_ALPHA);
    } else {
      SetLayeredWindowAttributes(hid, 0, 255, LWA_ALPHA);
    }
  }

  Label1->Caption="ID: "+String((DWORD)hid)+"\n\nTitle: "+String(title);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar1Change(TObject *Sender)
{
  tval=TrackBar1->Position;
}
//---------------------------------------------------------------------------

