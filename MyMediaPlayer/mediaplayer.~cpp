//---------------------------------------------------------------------------
#include <iostream.h>
#pragma hdrstop

#include "mediaplayer.h"
#include "myplayer.h"
#include "minirecord.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TKMediaPlayer *KMediaPlayer;
String status;
POINT mouse;

HDC mvideo;

int index=0;

int pos=0;
int tx=8;
int ty=8;
int tw=256;
int th=8;

int vpos=256;
int vx=0;
int vy=24;
int vw=256;
int vh=8;

int sel=0;
int repeat=0;
int button=0;

RECT trect;

bool tbutton=0;
int cmx=0;
int cmy=0;
int lst=0;

//---------------------------------------------------------------------------
__fastcall TKMediaPlayer::TKMediaPlayer(TComponent* Owner)
        : TForm(Owner)
{
  mvideo=GetDC(KMediaPlayer->Handle);

  DoubleBuffered=1;
  ControlBox->DoubleBuffered=1;
  MusicDirectory->DoubleBuffered=1;
  MusicFiles->DoubleBuffered=1;

  Splitter2->Enabled=0;

  PlayButton->Transparent=1;
  TrackButton->Transparent=1;
  VolumeButton->Transparent=1;
  Image64->GetBitmap(0,PlayButton->Picture->Bitmap);
  Image16->GetBitmap(0,TrackButton->Picture->Bitmap);
  Image16->GetBitmap(0,VolumeButton->Picture->Bitmap);
}
//---------------------------------------------------------------------------


void __fastcall TKMediaPlayer::Open1Click(TObject *Sender)
{
  char* file;
  if (MediaOpen->Execute()) {
    file = MediaOpen->FileName.c_str();
    if (file!="") {
      MusicDirectory->Directory=MediaOpen->FileName;
      if (!Media::mciOpen(file))
      Application->MessageBoxA("ERROR",
      "There was a problem when trying to open the file",MB_OK);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TKMediaPlayer::Quit1Click(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TKMediaPlayer::PlayButtonClick(TObject *Sender)
{
  if (status=="stopped") {
    Media::mciPlay(1);
    Media::setVolume(vpos*100/256);
    Image64->GetBitmap(1,PlayButton->Picture->Bitmap);
    PlayButton->Refresh();
    index=1;
  } else if (status=="paused") {
    Media::mciPlay(0);
    Media::setVolume(vpos*100/256);
    Image64->GetBitmap(1,PlayButton->Picture->Bitmap);
    PlayButton->Refresh();
    index=1;
  } else if (status=="playing") {
    Media::mciPause();
    Media::setVolume(vpos*100/256);
    Image64->GetBitmap(0,PlayButton->Picture->Bitmap);
    PlayButton->Refresh();
    index=0;
  }
}
//---------------------------------------------------------------------------
void __fastcall TKMediaPlayer::MediaTimerTimer(TObject *Sender)
{
  GetCursorPos(&mouse);

  trect.left = 0;
  trect.top = 0;
  trect.right = MusicFiles->Width+MusicDirectory->Left+MusicDirectory->Width;
  trect.bottom = MusicFiles->Height;

  status=Media::mciGetStatus();
  if (status!="")Label1->Caption=status+"\n"
  +SecToTime(Media::mciGetPosition()/1000);
  else Label1->Caption="no media loaded";

  if (status=="stopped" && index!=0) {
    if (repeat) Media::mciPlay(1);
    else {
      Image64->GetBitmap(0,PlayButton->Picture->Bitmap);
      PlayButton->Refresh();
      index=0;
    }
  }

  VolumeLeft->Left=vx;
  VolumeLeft->Width=vpos;
  VolumeLeft->Top=vy;
  VolumeLeft->Height=vh;
  VolumeRight->Left=vx+vpos;
  VolumeRight->Width=vw-vpos;
  VolumeRight->Top=vy;
  VolumeRight->Height=vh;
  VolumeButton->Left=vx+vpos-8;
  VolumeButton->Top=vy-4;

  TrackLeft->Left=tx;
  TrackLeft->Width=pos;
  TrackLeft->Top=ty;
  TrackLeft->Height=th;
  TrackRight->Left=tx+pos;
  TrackRight->Width=tw-pos;
  TrackRight->Top=ty;
  TrackRight->Height=th;
  TrackButton->Left=tx+pos-8;
  TrackButton->Top=ty-4;

  tw=ControlBox->Width-96;
  vx=ControlBox->Width-96-vw;

  if (Media::mciGetLength()!=0)pos=((float)Media::mciGetPosition()/(float)Media::mciGetLength())*tw;
  else pos=0;

  if (!GetAsyncKeyState(VK_LBUTTON) && tbutton) {
    tbutton=0;
    if (button==0 && status=="playing")
    Media::mciPlayPos(((float)(lst+(mouse.x-cmx))/tw)*Media::mciGetLength());
  } else if (tbutton) {
    if (button==0) {
      pos=lst+(mouse.x-cmx);
      if (pos>tw)pos=tw;
      if (pos<0)pos=0;
    }
    if (button==1) {
      vpos=lst+(mouse.x-cmx);
      if (vpos>vw)vpos=vw;
      if (vpos<0)vpos=0;
      Media::setVolume(vpos*100/256);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TKMediaPlayer::TrackButtonMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  button=0;
  tbutton=1;
  cmx=mouse.x;
  lst=TrackButton->Left;
}
//---------------------------------------------------------------------------

void __fastcall TKMediaPlayer::OpenVideo1Click(TObject *Sender)
{
  /*char* command;
  char* file;
  VideoOpen->Execute();
  file = VideoOpen->FileName.c_str();
  if (file!="") {
    if (!Media::mciOpenVideo(file,KMediaPlayer->Handle))
    Application->MessageBoxA("ERROR",
    "There was a problem when trying to open the file",MB_OK);
  }*/
}
//---------------------------------------------------------------------------

void __fastcall TKMediaPlayer::Repeat1Click(TObject *Sender)
{
  Repeat1->Checked=!Repeat1->Checked;
  repeat=Repeat1->Checked;        
}
//---------------------------------------------------------------------------

void __fastcall TKMediaPlayer::VolumeButtonMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  button=1;
  tbutton=1;
  cmx=mouse.x;
  lst=VolumeButton->Left-vx+8;
}
//---------------------------------------------------------------------------

void __fastcall TKMediaPlayer::VerySlow1Click(TObject *Sender)
{
  Media::mciSetSpeed(500);
}
//---------------------------------------------------------------------------

void __fastcall TKMediaPlayer::Slow1Click(TObject *Sender)
{
  Media::mciSetSpeed(750);        
}
//---------------------------------------------------------------------------

void __fastcall TKMediaPlayer::Normal1Click(TObject *Sender)
{
  Media::mciSetSpeed(1000);        
}
//---------------------------------------------------------------------------

void __fastcall TKMediaPlayer::Fast1Click(TObject *Sender)
{
  Media::mciSetSpeed(1500);        
}
//---------------------------------------------------------------------------

void __fastcall TKMediaPlayer::VeryFast1Click(TObject *Sender)
{
  Media::mciSetSpeed(2000);        
}
//---------------------------------------------------------------------------


void __fastcall TKMediaPlayer::MusicDirectoryChange(TObject *Sender)
{
  MusicFiles->Directory=MusicDirectory->Directory;        
}
//---------------------------------------------------------------------------


void __fastcall TKMediaPlayer::MusicFilesDblClick(TObject *Sender)
{
  if (Media::mciOpen(MusicFiles->FileName.c_str())) {
    Media::mciPlay(1);
    Media::setVolume(vpos*100/256);
    Image64->GetBitmap(1,PlayButton->Picture->Bitmap);
    PlayButton->Refresh();
  }
}
//---------------------------------------------------------------------------


void __fastcall TKMediaPlayer::SoundRecorder1Click(TObject *Sender)
{
  Media::mciPause();
  Media::setVolume(vpos*100/256);
  Image64->GetBitmap(0,PlayButton->Picture->Bitmap);
  PlayButton->Refresh();
  index=0;

  Enabled=0;
  KMediaRec->Visible=1;        
}
//---------------------------------------------------------------------------



