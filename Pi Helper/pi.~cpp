//---------------------------------------------------------------------------
#include <iostream>
#include <vcl.h>
#pragma hdrstop

#include "pi.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

String pi;
bool key;
int digit=1;
FILE *str;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
  PiGrid->Cells[15][0]=".";
  PiGrid->Cells[14][0]="3";
  RichEdit1->Lines->LoadFromFile("pidata.txt");
  pi = RichEdit1->Text;
  str = fopen("pidata.txt", "r+");
  fscanf(str,"%s",pi);
  pi.Trim();
}

//---------------------------------------------------------------------------

void AddNumber(String num) {
  if (digit<pi.Length())
  if (num.SubString(0,1)==pi.SubString(digit,1) && Form1->PiGrid->Font->Color==clBlack) {
    for (int i=0;i<15;i++) {
      Form1->PiGrid->Cells[i][0]=Form1->PiGrid->Cells[i+1][0];
    }
    Form1->PiGrid->Cells[15][0]=num;
    digit++;
    Form1->Label1->Caption = "Digits Correct: "+IntToStr(digit-1);
  } else {
    Form1->PiGrid->Font->Color = clRed;
  }
}

//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
  AddNumber("1");        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
  AddNumber("2");        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
  AddNumber("3");        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
  AddNumber("4");        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button5Click(TObject *Sender)
{
  AddNumber("5");        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button6Click(TObject *Sender)
{
  AddNumber("6");        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button7Click(TObject *Sender)
{
  AddNumber("7");        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button8Click(TObject *Sender)
{
  AddNumber("8");        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button9Click(TObject *Sender)
{
  AddNumber("9");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button10Click(TObject *Sender)
{
  AddNumber("0");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{

  if (GetAsyncKeyState(48)) {if(!key) {AddNumber("0");key=1;}} else
  if (GetAsyncKeyState(49)) {if(!key) {AddNumber("1");key=1;}} else
  if (GetAsyncKeyState(50)) {if(!key) {AddNumber("2");key=1;}} else
  if (GetAsyncKeyState(51)) {if(!key) {AddNumber("3");key=1;}} else
  if (GetAsyncKeyState(52)) {if(!key) {AddNumber("4");key=1;}} else
  if (GetAsyncKeyState(53)) {if(!key) {AddNumber("5");key=1;}} else
  if (GetAsyncKeyState(54)) {if(!key) {AddNumber("6");key=1;}} else
  if (GetAsyncKeyState(55)) {if(!key) {AddNumber("7");key=1;}} else
  if (GetAsyncKeyState(56)) {if(!key) {AddNumber("8");key=1;}} else
  if (GetAsyncKeyState(57)) {if(!key) {AddNumber("9");key=1;}} else
  if (key)key=0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button11Click(TObject *Sender)
{
  AddNumber(pi.SubString(digit,1));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button12Click(TObject *Sender)
{
  digit = 1;
  PiGrid->Cells[15][0]=".";
  PiGrid->Cells[14][0]="3";

  for (int i=0;i<14;i++) PiGrid->Cells[i][0]="";

  Form1->Label1->Caption = "Digits Correct: "+IntToStr(digit-1);
  Form1->PiGrid->Font->Color = clBlack;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button13Click(TObject *Sender)
{
  for (int i=0;i<10;i++)
  AddNumber(pi.SubString(digit,1));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button14Click(TObject *Sender)
{
  for (int i=0;i<100;i++)
  AddNumber(pi.SubString(digit,1));
}
//---------------------------------------------------------------------------
