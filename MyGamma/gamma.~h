//---------------------------------------------------------------------------

#ifndef gammaH
#define gammaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include "trayicon.h"
#include <ExtCtrls.hpp>

#ifndef GAMMARAMP_H_
#define GAMMARAMP_H_


/*
CGammaRamp class

Encapsulates the Gamma Ramp API and changes the brightness of
the entire screen.

Written by Nir Sofer.
http://www.nirsoft.net


*/

class CGammaRamp
{
protected:
	HMODULE hGDI32;
	HDC hScreenDC;
	typedef BOOL (WINAPI *Type_SetDeviceGammaRamp)(HDC hDC, LPVOID lpRamp);

	Type_SetDeviceGammaRamp pGetDeviceGammaRamp;
	Type_SetDeviceGammaRamp pSetDeviceGammaRamp;

public:

	CGammaRamp();
	~CGammaRamp();
	BOOL LoadLibrary();
	void FreeLibrary();
	BOOL LoadLibraryIfNeeded();
	BOOL SetDeviceGammaRamp(HDC hDC, LPVOID lpRamp);
	BOOL GetDeviceGammaRamp(HDC hDC, LPVOID lpRamp);
	BOOL SetBrightness(HDC hDC, WORD wBrightness);

};
#endif

//---------------------------------------------------------------------------
class TMyGammaForm : public TForm
{
__published:	// IDE-managed Components
        TTrackBar *GammaBar;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TTrayIcon *TrayIcon1;
        TTimer *VisibleTimer;
        TShape *Shape1;
        void __fastcall GammaBarChange(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall VisibleTimerTimer(TObject *Sender);
        void __fastcall TrayIcon1Click(TObject *Sender);
        void __fastcall Shape1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
private:	// User declarations
public:		// User declarations
        __fastcall TMyGammaForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMyGammaForm *MyGammaForm;
//---------------------------------------------------------------------------
#endif
