//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "paint.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CGRID"
#pragma resource "*.dfm"
TForm1 *Form1;

int mxp,myp;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
  Panel1->Height=ClientHeight-19;
  StatusBar1->Width = ClientWidth;
  StatusBar1->Top = ClientHeight-19;
  ScrollBox1->Height=ClientHeight-19;
  ScrollBox1->Width=ClientWidth-48;
  PaintCanvas->Canvas->Pixels[0][0]=clWhite;
  Shape1->Brush->Color = CColorGrid1->BackgroundColor;
  Shape2->Brush->Color = CColorGrid1->ForegroundColor;
  ScrollBox1->DoubleBuffered=1;
  Panel1->DoubleBuffered=1;

  Form1->DoubleBuffered=1;
  SwapBuffers(Form1);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Quit1Click(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::FormResize(TObject *Sender)
{
  Panel1->Height=ClientHeight-19;
  StatusBar1->Width = ClientWidth;
  StatusBar1->Top = ClientHeight-19;
  ScrollBox1->Height=ClientHeight-19;
  ScrollBox1->Width=ClientWidth-48;
  CColorGrid1->Top = ClientHeight-216;
  Bevel1->Top = ClientHeight-56;
  Shape1->Top = ClientHeight-45;
  Shape2->Top = ClientHeight-53;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CColorGrid1Change(TObject *Sender)
{
  Shape1->Brush->Color = CColorGrid1->BackgroundColor;
  Shape2->Brush->Color = CColorGrid1->ForegroundColor;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Open1Click(TObject *Sender)
{
  OpenPictureDialog1->Execute();
  if (OpenPictureDialog1->FileName!="")
  PaintCanvas->Picture->LoadFromFile(OpenPictureDialog1->FileName);
  PaintCanvas->Width = PaintCanvas->Picture->Width;
  PaintCanvas->Height = PaintCanvas->Picture->Height;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Save1Click(TObject *Sender)
{
  SavePictureDialog1->Execute();
  if (SavePictureDialog1->FileName!="")
  PaintCanvas->Picture->SaveToFile(SavePictureDialog1->FileName);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Shape2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  ColorDialog1->Execute();
  Shape2->Brush->Color=ColorDialog1->Color;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Shape1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  ColorDialog1->Execute();
  Shape1->Brush->Color=ColorDialog1->Color;        
}

//---------------------------------------------------------------------------


void __fastcall TForm1::New1Click(TObject *Sender)
{
  PaintCanvas->Canvas->Rectangle(0,0,PaintCanvas->Width,PaintCanvas->Height);        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
  POINT mouse;
  GetCursorPos(&mouse);
  int X = mouse.x-Form1->Left-6-47;
  int Y = mouse.y-Form1->Top-30-21;

  if (GetAsyncKeyState(VK_LBUTTON)) {
    PaintCanvas->Canvas->Brush->Color = Shape2->Brush->Color;
    PaintCanvas->Canvas->Pen->Color = Shape2->Brush->Color;
  }

  if (GetAsyncKeyState(VK_RBUTTON)) {
    PaintCanvas->Canvas->Brush->Color = Shape1->Brush->Color;
    PaintCanvas->Canvas->Pen->Color = Shape1->Brush->Color;
  }

  if (GetAsyncKeyState(VK_LBUTTON) || GetAsyncKeyState(VK_RBUTTON)) {
    if (Pencil->Down) {
      PaintCanvas->Canvas->MoveTo(mxp,myp);
      PaintCanvas->Canvas->LineTo(X,Y);
    }

    if (Circle->Down) {
    }

  }

  mxp = X;
  myp = Y;
}
//---------------------------------------------------------------------------

