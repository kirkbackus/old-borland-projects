//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "background.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
TForm1 *Form1;
int current=0;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
  ImgInd->Caption = "Image Index: 0";
  SetWindowLong(Application->Handle,GWL_EXSTYLE,WS_EX_TOOLWINDOW);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AddImgClick(TObject *Sender)
{
  OpenPic->Execute();
  ImageList->Items->Add(OpenPic->FileName);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ImageListClick(TObject *Sender)
{
  if (ImageList->Items->Strings[ImageList->ItemIndex].c_str()) {
    Image1->Picture->LoadFromFile(ImageList->Items->Strings[ImageList->ItemIndex].c_str());
    Image1->Width = Image1->Picture->Width;
    Image1->Height = Image1->Picture->Height;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DelImgClick(TObject *Sender)
{
  ImageList->DeleteSelected();
  if (ImageList->Items->Count<=0)Delay->Enabled=0;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::SetDelayClick(TObject *Sender)
{
  Delay->Interval = 1000*atoi(DelayEdit->Text.c_str());
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StartClick(TObject *Sender)
{
  Delay->Enabled=1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StopClick(TObject *Sender)
{
  Delay->Enabled=0;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::DelayTimer(TObject *Sender)
{
  current++;
  if (current>=ImageList->Items->Count)current=0;
  if (ImageList->Items->Count!=0)
  SetWallpaper(ImageList->Items->Strings[current].c_str());
  ImgInd->Caption = "Image Index: "+(String)current;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrayIcon1Click(TObject *Sender)
{
  Form1->Visible=1;        
}
//---------------------------------------------------------------------------


