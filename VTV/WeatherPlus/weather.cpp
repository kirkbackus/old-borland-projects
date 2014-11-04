//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "weather.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "WMPLib_OCX"
#pragma resource "*.dfm"
TMyWeather *MyWeather;
bool skip=0;
//---------------------------------------------------------------------------
__fastcall TMyWeather::TMyWeather(TComponent* Owner)
        : TForm(Owner)
{
  WeatherPlus->Realign();
  WeatherPlus->settings->volume=0;
  WeatherPlus->SetBounds(0,0,ClientWidth,ClientHeight);
}
//---------------------------------------------------------------------------
void __fastcall TMyWeather::WeatherPlusBuffering(TObject *Sender,
      VARIANT_BOOL Start)
{
  if (skip==0) {
    WeatherPlus->controls->next();
    skip=1;
    WeatherPlus->settings->volume=50;
  }
}
//---------------------------------------------------------------------------
void __fastcall TMyWeather::FormResize(TObject *Sender)
{
  WeatherPlus->SetBounds(0,0,ClientWidth,ClientHeight);
  WeatherPlus->PaintTo(GetDC(MyWeather->Handle),0,0);
}
//---------------------------------------------------------------------------
