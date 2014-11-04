//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#pragma hdrstop

#define pi 3.1415926535897932384626433

#include "dots.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDotForm *DotForm;

float dspeed;
float dsize;
float dangle;
float dspacing;

int twidth;
int theight;
int tleft;
int ttop;

float offset = 0;
float speed;

int centerx;
int centery;
float tval;
float dtime = 0;

//---------------------------------------------------------------------------
__fastcall TDotForm::TDotForm(TComponent* Owner)
        : TForm(Owner)
{
    DoubleBuffered = 1;
}
//---------------------------------------------------------------------------
void __fastcall TDotForm::GenerateClick(TObject *Sender)
{
    dspeed = atoi(Speed->Text.c_str());
    dsize = atoi(Size->Text.c_str());
    dangle = atoi(Angle->Text.c_str());
    dspacing = atoi(Space->Text.c_str());

    twidth = Width;
    theight = Height;
    tleft = Left;
    ttop = Top;

    Interface->Visible = 0;
    Generate->Visible = 0;
    Color = clBlack;
    BorderStyle = bsNone;
    Left = 0;
    Top = 0;
    Width = Screen->Width;
    Height = Screen->Height;

    centerx = ClientWidth/2;
    centery = ClientHeight/2;

    if (dspeed <= 0) dspeed = 1;
    Cursor = crNone;

    Controller->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TDotForm::ControllerTimer(TObject *Sender)
{
    if (GetAsyncKeyState(VK_ESCAPE)) {
        Interface->Visible = 1;
        Generate->Visible = 1;
        Color = clBtnFace;
        BorderStyle = bsSingle;
        Left = tleft;
        Top = ttop;
        Width = twidth;
        Height = theight;
        Cursor = crDefault;
        Controller->Enabled = false;
    }

    float add;
    if (dtime) add = (float)dtime*(dspeed/1000.0);
    else add = 0;

    offset += add;
    while (offset>dspacing) {
        if(GetAsyncKeyState(VK_ESCAPE))break;
        offset-=(float)dspacing;
    }
    Repaint();

    float tmtime = GetTickCount();
    dtime = tmtime-tval;
    tval = tmtime;
}
//---------------------------------------------------------------------------
void __fastcall TDotForm::FormPaint(TObject *Sender)
{
    if (Controller->Enabled) {
        Canvas->Pen->Color = clBlack;
        Canvas->Brush->Color = clBlack;
        Canvas->Rectangle(0,0,ClientWidth,ClientHeight);

        int bounds;
        bounds = (Width+Height)/dspacing;

        for (int i=-bounds;i<bounds;i++) {
            int doff = dspacing*i;
            float tangle = pi/180.0*dangle;
            int xoffset = centerx;
            int yoffset = centery;
            xoffset -= cos(tangle)*doff;
            yoffset -= sin(tangle)*doff;
            xoffset -= cos(tangle)*offset;
            yoffset -= sin(tangle)*offset;
            if (dsize==1) Canvas->Pixels[xoffset][yoffset] = clWhite;
            else {
                Canvas->Pen->Color = clWhite;
                Canvas->Brush->Color = clWhite;
                Canvas->Rectangle(xoffset-dsize/2,yoffset-dsize/2,xoffset+dsize/2,yoffset+dsize/2);
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TDotForm::SpeedChange(TObject *Sender)
{
    int tmp = atoi(Speed->Text.c_str());
    if (tmp<1)tmp=1;
    if (tmp>1000)tmp=1000;
    Speed->Text = (String)tmp;
}
//---------------------------------------------------------------------------
void __fastcall TDotForm::SpaceChange(TObject *Sender)
{
    int tmp = atoi(Space->Text.c_str());
    if (tmp<1)tmp=1;
    Space->Text = (String)tmp;
}
//---------------------------------------------------------------------------
void __fastcall TDotForm::SizeChange(TObject *Sender)
{
    int tmp = atoi(Size->Text.c_str());
    if (tmp<1)tmp=1;
    Size->Text = (String)tmp;
}
//---------------------------------------------------------------------------
void __fastcall TDotForm::AngleChange(TObject *Sender)
{
    int tmp = atoi(Angle->Text.c_str());
    if (tmp<0)tmp=0;
    if (tmp>360)tmp=360;
    Angle->Text = (String)tmp;
}
//---------------------------------------------------------------------------
