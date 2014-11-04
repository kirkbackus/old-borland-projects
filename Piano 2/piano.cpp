//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "piano.h"
#include "options.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
#define clKey 0x00FF9900
TPianoForm *PianoForm;

TShape* keys[25];
byte pkeys[25][2];
Note nkeys[25];

bool __k[255];
bool __kp[255];

bool drag = 0;
int dxoff = 0, dyoff = 0, dwxpos = 0, dwypos = 0;
int qdelay = 0;

POINT mouse;
POINT fmouse;

//---------------------------------------------------------------------------
void InitKeys() {
  for (int i=0;i<255;i++) {
    __k[i]=0;
    __kp[i]=0;
  }
}
//---------------------------------------------------------------------------
void UpdateKeys() {
  for (int i=0;i<255;i++) {
    __kp[i]=__k[i];
    __k[i]=GetAsyncKeyState(i);
  }
}
//---------------------------------------------------------------------------
bool KeyPressed(byte key) {
  if(__k[key]==1 && __kp[key]==0) return 1;
  return 0;
}
//---------------------------------------------------------------------------
bool KeyReleased(byte key) {
  if(__k[key]==0 && __kp[key]==1) return 1;
  return 0;
}
//---------------------------------------------------------------------------
__fastcall TPianoForm::TPianoForm(TComponent* Owner)
        : TForm(Owner)
{
  MidiStart();
  InitKeys();
  ChangeMidiInstrument(0);

  octave = 0;

  ClientWidth = 843;
  ClientHeight = 275;

  SetMidiVolume(0xFFFF);

  HRGN top = CreateRoundRectRgn(0,0,ClientWidth,ClientHeight,32,32);
  HRGN bottom = CreateRectRgn(0,32,ClientWidth,ClientHeight);
  HRGN rgn = CreateRectRgn(0,0,0,0);
  CombineRgn(rgn,top,bottom,RGN_OR);
  SetWindowRgn(Handle,rgn,1);

  DoubleBuffered = 1;
  PianoBox->DoubleBuffered = 1;

  keys[0] = KeyLowC;
  pkeys[0][0]='Z';
  pkeys[0][1]=255;
  nkeys[0] = Note("C4");

  keys[1] = KeyLowCs;
  pkeys[1][0] = 'S';
  pkeys[1][1]=255;
  nkeys[1] = Note("C#4");

  keys[2] = KeyLowD;
  pkeys[2][0]= 'X';
  pkeys[2][1]=255;
  nkeys[2] = Note("D4");

  keys[3] = KeyLowDs;
  pkeys[3][0] = 'D';
  pkeys[3][1]=255;
  nkeys[3] = Note("D#4");

  keys[4] = KeyLowE;
  pkeys[4][0] = 'C';
  pkeys[4][1]=255;
  nkeys[4] = Note("E4");

  keys[5] = KeyLowF;
  pkeys[5][0] = 'V';
  pkeys[5][1]=255;
  nkeys[5] = Note("F4");

  keys[6] = KeyLowFs;
  pkeys[6][0] = 'G';
  pkeys[6][1]=255;
  nkeys[6] = Note("F#4");

  keys[7] = KeyLowG;
  pkeys[7][0] = 'B';
  pkeys[7][1]=255;
  nkeys[7] = Note("G4");

  keys[8] = KeyLowGs;
  pkeys[8][0] = 'H';
  pkeys[8][1]=255;
  nkeys[8] = Note("G#4");

  keys[9] = KeyLowA;
  pkeys[9][0] = 'N';
  pkeys[9][1]= 'Q';
  nkeys[9] = Note("A4");

  keys[10] = KeyLowAs;
  pkeys[10][0] = 'J';
  pkeys[10][1] = '2';
  nkeys[10] = Note("A#4");

  keys[11] = KeyLowB;
  pkeys[11][0] = 'M';
  pkeys[11][1] = 'W';
  nkeys[11] = Note("B4");

  keys[12] = KeyHighC;
  pkeys[12][0] = 188;
  pkeys[12][1] = 'E';
  nkeys[12] = Note("C5");

  keys[13] = KeyHighCs;
  pkeys[13][0] = 'L';
  pkeys[13][1] = '4';
  nkeys[13] = Note("C#5");

  keys[14] = KeyHighD;
  pkeys[14][0] = 190;
  pkeys[14][1] = 'R';
  nkeys[14] = Note("D5");

  keys[15] = KeyHighDs;
  pkeys[15][0] = 186;
  pkeys[15][1] = '5';
  nkeys[15] = Note("D#5");

  keys[16] = KeyHighE;
  pkeys[16][0] = 191;
  pkeys[16][1] = 'T';
  nkeys[16] = Note("E5");

  keys[17] = KeyHighF;
  pkeys[17][0] = 'Y';
  pkeys[17][1] = 255;
  nkeys[17] = Note("F5");

  keys[18] = KeyHighFs;
  pkeys[18][0] = '7';
  pkeys[18][1] = 255;
  nkeys[18] = Note("F#5");

  keys[19] = KeyHighG;
  pkeys[19][0] = 'U';
  pkeys[19][1] = 255;
  nkeys[19] = Note("G5");

  keys[20] = KeyHighGs;
  pkeys[20][0] = '8';
  pkeys[20][1] = 255;
  nkeys[20] = Note("G#5");

  keys[21] = KeyHighA;
  pkeys[21][0] = 'I';
  pkeys[21][1] = 255;
  nkeys[21] = Note("A5");

  keys[22] = KeyHighAs;
  pkeys[22][0] = '9';
  pkeys[22][1] = 255;
  nkeys[22] = Note("A#5");

  keys[23] = KeyHighB;
  pkeys[23][0] = 'O';
  pkeys[23][1] = 255;
  nkeys[23] = Note("B5");

  keys[24] = KeyTopC;
  pkeys[24][0] = 'P';
  pkeys[24][1] = 255;
  nkeys[24] = Note("C6");
}
//---------------------------------------------------------------------------

void __fastcall TPianoForm::PianoTimerTimer(TObject *Sender)
{
  UpdateKeys();
  GetCursorPos(&mouse);
  fmouse.x = mouse.x-Left;
  fmouse.y = mouse.y-Top;

  if (drag) {
    Left = dwxpos+mouse.x-dxoff;
    Top = dwypos+mouse.y-dyoff;
    if (!GetAsyncKeyState(VK_LBUTTON)) drag = 0;
  }

  if (!(fmouse.x > BtnQuit->Left && fmouse.y > BtnQuit->Top && fmouse.x < BtnQuit->Left+BtnQuit->Width && fmouse.y < BtnQuit->Top+BtnQuit->Height)) {
    BtnQuit->Brush->Color = clRed;
    BtnQuit->Pen->Color = clRed;
  }
  
  for (int i=0;i<25;i++) {
    bool kp = 1;
    if (KeyPressed(pkeys[i][0])) {
      PlayMidiNote(nkeys[i]+Note(octave*12));
      keys[i]->Brush->Color = (TColor)clKey;
    } else if (KeyPressed(pkeys[i][1]) && pkeys[i][1]!=255) {
      PlayMidiNote(nkeys[i]+Note(octave*12));
      keys[i]->Brush->Color = (TColor)clKey;
    } else if (KeyReleased(pkeys[i][1]) && !KeyReleased(pkeys[i][0])) kp = 0;
    else if (KeyReleased(pkeys[i][0]) && !KeyReleased(pkeys[i][1])) kp = 0;

    int ti=i;
    while(ti>11)ti-=12;

    if (!kp) {
      StopMidiNote(nkeys[i]+Note(octave*12));
      if (ti==1 || ti==3 || ti==6 || ti==8 || ti==10) keys[i]->Brush->Color = clBlack;
      else keys[i]->Brush->Color = clWhite;
    }                                                                                                   
  }
}
//---------------------------------------------------------------------------

void __fastcall TPianoForm::FormDestroy(TObject *Sender)
{
  MidiDestroy();
}
//---------------------------------------------------------------------------


void __fastcall TPianoForm::Quit1Click(TObject *Sender)
{
  Close();        
}
//---------------------------------------------------------------------------
void __fastcall TPianoForm::LTitleMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  dxoff = mouse.x;
  dyoff = mouse.y;
  dwxpos = Left;
  dwypos = Top;
  drag = 1;
}
//---------------------------------------------------------------------------

void __fastcall TPianoForm::BtnQuitMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  BtnQuit->Brush->Color = (TColor)0x000000CC;
  BtnQuit->Pen->Color = (TColor)0x000000CC;
}
//---------------------------------------------------------------------------

void __fastcall TPianoForm::BtnQuitMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
  if (fmouse.x > BtnQuit->Left && fmouse.y > BtnQuit->Top && fmouse.x < BtnQuit->Left+BtnQuit->Width && fmouse.y < BtnQuit->Top+BtnQuit->Height) {
    if (!GetAsyncKeyState(VK_LBUTTON)) {
      BtnQuit->Brush->Color = (TColor)0x009999FF;
      BtnQuit->Pen->Color = (TColor)0x009999FF;
    } else {
      BtnQuit->Brush->Color = (TColor)0x000000CC;
      BtnQuit->Pen->Color = (TColor)0x000000CC;
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TPianoForm::BtnQuitMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  if (fmouse.x > BtnQuit->Left && fmouse.y > BtnQuit->Top && fmouse.x < BtnQuit->Left+BtnQuit->Width && fmouse.y < BtnQuit->Top+BtnQuit->Height) Close();
}
//---------------------------------------------------------------------------

void __fastcall TPianoForm::BtnOptionsMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  OptionForm->Visible = 1;
}
//---------------------------------------------------------------------------

