//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "color.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMColor *MColor;
bool getcol=0;
POINT cursor;
HDC scol = GetDC(0);

//---------------------------------------------------------------------------
__fastcall TMColor::TMColor(TComponent* Owner)
        : TForm(Owner)
{
  MColor->DoubleBuffered=1;
}
//---------------------------------------------------------------------------
void __fastcall TMColor::RedBarChange(TObject *Sender)
{
  Edit1->Text = IntToStr(RedBar->Position);
}
//---------------------------------------------------------------------------
void __fastcall TMColor::GreenBarChange(TObject *Sender)
{
  Edit2->Text = IntToStr(GreenBar->Position);        
}
//---------------------------------------------------------------------------
void __fastcall TMColor::BlueBarChange(TObject *Sender)
{
  Edit3->Text = IntToStr(BlueBar->Position);         
}
//---------------------------------------------------------------------------
void __fastcall TMColor::Timer1Timer(TObject *Sender)
{
  String hex;
  Color->Brush->Color = RGB(RedBar->Position,GreenBar->Position,BlueBar->Position);
  hex = Hex->Text.IntToHex(RedBar->Position,2);
  hex = hex+Hex->Text.IntToHex(GreenBar->Position,2);
  hex = hex+Hex->Text.IntToHex(BlueBar->Position,2);
  if (Hex->Text!=hex)Hex->Text = hex;

  if (getcol) {
    GetCursorPos(&cursor);
    Color->Brush->Color=GetPixel(scol,cursor.x,cursor.y);
    RedBar->Position = GetRValue(Color->Brush->Color);
    GreenBar->Position = GetGValue(Color->Brush->Color);
    BlueBar->Position = GetBValue(Color->Brush->Color);
  }

  for (int i=0;i<255;i+=1)
  if (GetAsyncKeyState(i))
  getcol=0;
}
//---------------------------------------------------------------------------
void __fastcall TMColor::Edit1Change(TObject *Sender)
{
  RedBar->Position=atoi(Edit1->Text.c_str());
}
//---------------------------------------------------------------------------
void __fastcall TMColor::Edit2Change(TObject *Sender)
{
  GreenBar->Position=atoi(Edit2->Text.c_str());
}
//---------------------------------------------------------------------------
void __fastcall TMColor::Edit3Change(TObject *Sender)
{
  BlueBar->Position=atoi(Edit3->Text.c_str());
}
//---------------------------------------------------------------------------
void __fastcall TMColor::ScreenColClick(TObject *Sender)
{
  getcol=1;
}
//---------------------------------------------------------------------------

void __fastcall TMColor::ColorMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  ColorDialog1->Color=Color->Brush->Color;
  ColorDialog1->Execute();
  Color->Brush->Color=ColorDialog1->Color;
  RedBar->Position = GetRValue(Color->Brush->Color);
  GreenBar->Position = GetGValue(Color->Brush->Color);
  BlueBar->Position = GetBValue(Color->Brush->Color);
}
//---------------------------------------------------------------------------

