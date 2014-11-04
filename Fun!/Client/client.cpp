//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "client.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
  FunClient->Port = 12000;
  FunClient->Host = "192.168.2.102";
  FunClient->Active=1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
  FunClient->Active = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
  if( FunClient->Active ) FunClient->Socket->SendText("_ScrUP");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SendClick(TObject *Sender)
{
  if( FunClient->Active ) FunClient->Socket->SendText("_msg:"+Message->Text);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
  if( FunClient->Active ) FunClient->Socket->SendText("_ScrDOWN");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
  if( FunClient->Active ) FunClient->Socket->SendText("_ScrRIGHT");        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
  if( FunClient->Active ) FunClient->Socket->SendText("_ScrLEFT");        
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ConnectClick(TObject *Sender)
{
  if ( FunClient->Active ) {

  }
}
//---------------------------------------------------------------------------

