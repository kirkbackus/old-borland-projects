//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "enum.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
HANDLE desktop;

int __stdcall EnumWindowsProc(HWND hWnd, long lParam) {
  char Buff[255], NameOfClass[255];
  RECT tmp;
  long style;

  if (!hWnd) return true;
  if (!IsWindowVisible(hWnd)) return true;
  if (!SendMessage(hWnd, WM_GETTEXT, sizeof(Buff), (LPARAM)Buff)) return true;

  GetWindowText(hWnd, Buff, 254);
  GetClassName(hWnd, NameOfClass, 254);

  if (Buff=="") return true;

  style = GetWindowLong(hWnd,GWL_STYLE);
  if (style & WS_EX_APPWINDOW != WS_EX_APPWINDOW) return true;

  GetWindowRect(hWnd,&tmp);

  Form1->ListBox1->Items->Add(String(Buff)+"("+String(NameOfClass)+")");

  return true;
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
  EnumWindows((WNDENUMPROC)EnumWindowsProc, 0);
}
//---------------------------------------------------------------------------
