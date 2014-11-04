//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "gamma.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
TMyGammaForm *MyGammaForm;

#include <windows.h>

int visible=5;

/*
CGammaRamp class

Encapsulates the Gamma Ramp API and changes the brightness of 
the entire screen.

Written by Nir Sofer.
http://www.nirsoft.net


*/

CGammaRamp::CGammaRamp()
{
	//Initialize all variables.
	hGDI32 = NULL;
	hScreenDC = NULL;
	pGetDeviceGammaRamp = NULL;
	pSetDeviceGammaRamp = NULL;
}

CGammaRamp::~CGammaRamp()
{
	FreeLibrary();
}


BOOL CGammaRamp::LoadLibrary()
{
	BOOL bReturn = FALSE;

	FreeLibrary();
	//Load the GDI library.
	hGDI32 = ::LoadLibrary("gdi32.dll");
	if (hGDI32 != NULL)
	{
		//Get the addresses of GetDeviceGammaRamp and SetDeviceGammaRamp API functions.
		pGetDeviceGammaRamp = 
			(Type_SetDeviceGammaRamp)GetProcAddress(hGDI32, "GetDeviceGammaRamp");
		
		pSetDeviceGammaRamp = 
			(Type_SetDeviceGammaRamp)GetProcAddress(hGDI32, "SetDeviceGammaRamp");
		
		//Return TRUE only if these functions exist.
		if (pGetDeviceGammaRamp == NULL || pSetDeviceGammaRamp == NULL)
			FreeLibrary();
		else
			bReturn = TRUE;
	}

	return bReturn;
}


void CGammaRamp::FreeLibrary()
{
	//Free the GDI library.
	if (hGDI32 != NULL) 
	{
		::FreeLibrary(hGDI32);
		hGDI32 = NULL;
	}
}


BOOL CGammaRamp::LoadLibraryIfNeeded()
{
	BOOL bReturn = FALSE;

	if (hGDI32 == NULL)
		LoadLibrary();

	if (pGetDeviceGammaRamp != NULL && pSetDeviceGammaRamp != NULL)
		bReturn = TRUE;

	return bReturn;
}


BOOL CGammaRamp::SetDeviceGammaRamp(HDC hDC, LPVOID lpRamp)
{
	//Call to SetDeviceGammaRamp only if this function is successfully loaded.
	if (LoadLibraryIfNeeded())
	{
		return pSetDeviceGammaRamp(hDC, lpRamp);
	}
	else
		return FALSE;
}


BOOL CGammaRamp::GetDeviceGammaRamp(HDC hDC, LPVOID lpRamp)
{
	//Call to GetDeviceGammaRamp only if this function is successfully loaded.
	if (LoadLibraryIfNeeded())
	{
		return pGetDeviceGammaRamp(hDC, lpRamp);
	}
	else
		return FALSE;

}


BOOL CGammaRamp::SetBrightness(HDC hDC, WORD wBrightness)
{
	/*
	Changes the brightness of the entire screen.
	This function may not work properly in some video cards.

	The wBrightness value should be a number between 0 and 255.
	128 = Regular brightness
	above 128 = brighter
	below 128 = darker

    If hDC is NULL, SetBrightness automatically load and release 
	the display device context for you.

	*/
	BOOL bReturn = FALSE;
	HDC hGammaDC = hDC;

	//Load the display device context of the entire screen if hDC is NULL.
	if (hDC == NULL)
		hGammaDC = GetDC(NULL);

	if (hGammaDC != NULL)
	{
		//Generate the 256-colors array for the specified wBrightness value.
		WORD GammaArray[3][256];

		for (int iIndex = 0; iIndex < 256; iIndex++)
		{
			int iArrayValue = iIndex * (wBrightness + 128);

			if (iArrayValue > 65535)
				iArrayValue = 65535;

			GammaArray[0][iIndex] = 
			GammaArray[1][iIndex] = (WORD)iArrayValue;
			GammaArray[2][iIndex] = (WORD)iArrayValue;
			
		}

		//Set the GammaArray values into the display device context.
		bReturn = SetDeviceGammaRamp(hGammaDC, GammaArray);
	}

	if (hDC == NULL)
		ReleaseDC(NULL, hGammaDC);

	return bReturn;
}

CGammaRamp gamma;

//---------------------------------------------------------------------------
__fastcall TMyGammaForm::TMyGammaForm(TComponent* Owner)
        : TForm(Owner)
{
  HRGN rgn;
  rgn=CreateRoundRectRgn(0,0,MyGammaForm->Width,MyGammaForm->Height,16,16);
  SetWindowRgn(MyGammaForm->Handle,rgn,1);

  SetWindowLong(Application->Handle,GWL_EXSTYLE,WS_EX_TOOLWINDOW);
  MyGammaForm->Left = Screen->DesktopWidth-MyGammaForm->Width-4;
  MyGammaForm->Top = Screen->DesktopHeight-MyGammaForm->Height-32;
}
//---------------------------------------------------------------------------

void __fastcall TMyGammaForm::GammaBarChange(TObject *Sender)
{
  gamma.SetBrightness(NULL, GammaBar->Position);
}
//---------------------------------------------------------------------------
void __fastcall TMyGammaForm::FormDestroy(TObject *Sender)
{
  gamma.SetBrightness(NULL, 128);        
}
//---------------------------------------------------------------------------
void __fastcall TMyGammaForm::VisibleTimerTimer(TObject *Sender)
{
  POINT m;
  GetCursorPos(&m);
  if (m.x>MyGammaForm->Left && m.x<MyGammaForm->Left+MyGammaForm->Width &&
      m.y>MyGammaForm->Top  && m.y<MyGammaForm->Top+MyGammaForm->Height)
      visible=5;
      
  if (visible>0)visible-=1;
  if (visible==0) {
    MyGammaForm->Visible=0;
    VisibleTimer->Enabled=0;
  }
}
//---------------------------------------------------------------------------
void __fastcall TMyGammaForm::TrayIcon1Click(TObject *Sender)
{
  MyGammaForm->Visible=1;
  visible=5;
  VisibleTimer->Enabled=1;
}
//---------------------------------------------------------------------------
void __fastcall TMyGammaForm::Shape1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  MyGammaForm->Close();        
}
//---------------------------------------------------------------------------
