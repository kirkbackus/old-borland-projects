//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "object.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
TShape *shapes[100];
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
  for (int i=0;i<100;i++) {
    shapes[i] = TControl::TShape();
    //shapes[i]->Visible = 1;
    //shapes[i]->Left = rand()%ClientWidth;
    //shapes[i]->Top = rand()%ClientHeight;
    //shapes[i]->Shape = stRectangle;
    //shapes[i]->Brush->Color = clWhite;
    //shapes[i]->Pen->Color = clBlack;
  }
}
//---------------------------------------------------------------------------
