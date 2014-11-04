//---------------------------------------------------------------------------

#ifndef weatherH
#define weatherH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "WMPLib_OCX.h"
#include <OleCtrls.hpp>
//---------------------------------------------------------------------------
class TMyWeather : public TForm
{
__published:	// IDE-managed Components
        TWindowsMediaPlayer *WeatherPlus;
        void __fastcall WeatherPlusBuffering(TObject *Sender,
          VARIANT_BOOL Start);
        void __fastcall FormResize(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TMyWeather(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMyWeather *MyWeather;
//---------------------------------------------------------------------------
#endif
