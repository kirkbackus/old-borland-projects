//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "rotate.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

void Rotate(int direction) {
   DEVMODE dm;
   // initialize the DEVMODE structure
   ZeroMemory(&dm, sizeof(dm));
   dm.dmSize = sizeof(dm);

   if (EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm)) {
      if (dm.dmDisplayOrientation == 0 || dm.dmDisplayOrientation == 2) {
        if (direction==1 || direction == 3) {
          long tmp = dm.dmPelsWidth;
          dm.dmPelsWidth = dm.dmPelsHeight;
          dm.dmPelsHeight = tmp;
          dm.dmDisplayOrientation = direction;
        }
        if (direction==0 || direction == 2) dm.dmDisplayOrientation = direction;
      }

      if (dm.dmDisplayOrientation == 1 || dm.dmDisplayOrientation == 3) {
        if (direction==0 || direction == 2) {
          long tmp = dm.dmPelsWidth;
          dm.dmPelsWidth = dm.dmPelsHeight;
          dm.dmPelsHeight = tmp;
          dm.dmDisplayOrientation = direction;
        }
        if (direction==1 || direction == 3) dm.dmDisplayOrientation = direction;
      }

      long lRet = ChangeDisplaySettings(&dm, 0);
      if (DISP_CHANGE_SUCCESSFUL != lRet) ShowMessage("ERROR CHANGING DISPLAY SETTINGS");
   }
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
  Rotate(0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BUpClick(TObject *Sender)
{
  Rotate(0);        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BLeftClick(TObject *Sender)
{
  Rotate(1);        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BRightClick(TObject *Sender)
{
  Rotate(3);        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BDownClick(TObject *Sender)
{
  Rotate(2);        
}
//---------------------------------------------------------------------------
