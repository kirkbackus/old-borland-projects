//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "server.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFun *Fun;
int draw;
int sdraw;
HDC scr;
String msg;
//---------------------------------------------------------------------------
__fastcall TFun::TFun(TComponent* Owner)
        : TForm(Owner)
{
  FunServer->Port=12000;
  FunServer->Active=1;
  SetWindowLong(Application->Handle,GWL_EXSTYLE,WS_EX_TOOLWINDOW);
  Fun->Visible=1;
  scr=GetDC(0);

  sdraw=GetTickCount();
}
//---------------------------------------------------------------------------

void __fastcall TFun::FormClose(TObject *Sender, TCloseAction &Action)
{
  FunServer->Active=0;
}
//---------------------------------------------------------------------------
void __fastcall TFun::FunServerClientRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
  String tmptxt;
  tmptxt = Socket->ReceiveText();

  //Message
  if (AnsiPos("_msg:",tmptxt)) {
    //MessageBoxA(tmptxt.SubString(6,tmptxt.Length()-5).c_str(),"HAHA!",MB_OK);
    msg=tmptxt.SubString(6,tmptxt.Length()-5).c_str();
    sdraw=GetTickCount()+3000;
  }

  if (AnsiPos("_ScrUP",tmptxt)){
    // press DOWN "Ctrl-Alt-Up"
    keybd_event(VK_CONTROL, 0, 0, 0);
    keybd_event(VK_MENU, 0, 0, 0);
    keybd_event(VK_UP, 0, 0, 0);

    Sleep(100);

    // stop pressing "Ctrl-Alt-UP"
    keybd_event(VK_UP, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
  }

  if (AnsiPos("_ScrRIGHT",tmptxt)){
    // press DOWN "Ctrl-Alt-Up"
    keybd_event(VK_CONTROL, 0, 0, 0);
    keybd_event(VK_MENU, 0, 0, 0);
    keybd_event(VK_RIGHT, 0, 0, 0);

    Sleep(100);

    // stop pressing "Ctrl-Alt-UP"
    keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
  }

  if (AnsiPos("_ScrLEFT",tmptxt)){
    // press DOWN "Ctrl-Alt-Up"
    keybd_event(VK_CONTROL, 0, 0, 0);
    keybd_event(VK_MENU, 0, 0, 0);
    keybd_event(VK_LEFT, 0, 0, 0);

    Sleep(100);

    // stop pressing "Ctrl-Alt-UP"
    keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
  }

  if (AnsiPos("_ScrDOWN",tmptxt)){
    // press DOWN "Ctrl-Alt-Up"
    keybd_event(VK_CONTROL, 0, 0, 0);
    keybd_event(VK_MENU, 0, 0, 0);
    keybd_event(VK_DOWN, 0, 0, 0);

    Sleep(100);

    // stop pressing "Ctrl-Alt-UP"
    keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
  }

}
//---------------------------------------------------------------------------


void __fastcall TFun::Timer1Timer(TObject *Sender)
{
  Label1->Caption = "Status: "+String(FunServer->Active ? "Active":"Off");
  if (!FunServer->Active) {
    FunServer->Active=1;
  }
  draw=GetTickCount();

  if (draw<sdraw) {
    Rectangle(scr,0,0,Screen->Width,32);
    SetTextColor(scr,clBlack);
    TextOut(scr,5,5,msg.c_str(),msg.Length());
  }
}
//---------------------------------------------------------------------------

