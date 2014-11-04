//---------------------------------------------------------------------------
#include <iostream.h>
#include <vcl.h>
#pragma hdrstop

#include "minirecord.h"
#include "mediaplayer.h"
#include "myplayer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TKMediaRec *KMediaRec;

String status;
//---------------------------------------------------------------------------
__fastcall TKMediaRec::TKMediaRec(TComponent* Owner)
        : TForm(Owner)
{
  DoubleBuffered=1;
  ControlBox->DoubleBuffered=1;

  Visible=0;
  Image64->GetBitmap(0,RecButton->Picture->Bitmap);
}
//---------------------------------------------------------------------------
void __fastcall TKMediaRec::RecButtonMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  if (status=="stopped" || status=="") {
    Media::mciRecord();
    Image64->GetBitmap(1,RecButton->Picture->Bitmap);
    RecButton->Refresh();
  } else if (status=="recording") {
    Media::mciStopRecord();
    Image64->GetBitmap(0,RecButton->Picture->Bitmap);
    RecButton->Refresh();
  }
}
//---------------------------------------------------------------------------
void __fastcall TKMediaRec::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  KMediaPlayer->Enabled=1;        
}
//---------------------------------------------------------------------------
void __fastcall TKMediaRec::Close1Click(TObject *Sender)
{
  Close();        
}
//---------------------------------------------------------------------------
void __fastcall TKMediaRec::New1Click(TObject *Sender)
{
  Media::mciStopRecord();
  Media::mciCloseRecord();
  Media::mciOpenRecord();
}
//---------------------------------------------------------------------------
void __fastcall TKMediaRec::FormCreate(TObject *Sender)
{
  Media::mciOpenRecord();        
}
//---------------------------------------------------------------------------
void __fastcall TKMediaRec::Save1Click(TObject *Sender)
{
  SaveRecord->Execute();
  if (SaveRecord->FileName!="")Media::mciSaveRecord(SaveRecord->FileName.c_str());
}
//---------------------------------------------------------------------------
void __fastcall TKMediaRec::MediaTimerTimer(TObject *Sender)
{
  status=Media::mciGetStatusRec();
  Label1->Caption=status;
  //SoundLevel->Position=Media::mciGetRecordLevel();
}
//---------------------------------------------------------------------------
