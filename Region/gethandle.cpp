//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#pragma hdrstop

#include "gethandle.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

HWND mwin;
HRGN m_reg;
POINT VertexPoint[5];
RGNDATAHEADER rgndh;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
  //mwin = FindWindow(NULL,"Untitled - Notepad");
  mwin = Form1->Handle;
  //m_reg = CreateRoundRectRgn(0,0,Form1->Width,Form1->Height,50,50);

  rgndh.dwSize = Form1->Width*Form1->Height;
  rgndh.iType = RDH_RECTANGLES;
  rgndh.nCount = 128;
  rgndh.nRgnSize

  VertexPoint[0].x = 0; VertexPoint[0].y = 64;
  VertexPoint[1].x = 64;   VertexPoint[1].y = 0;
  VertexPoint[2].x = Form1->Width; VertexPoint[2].y = 0;
  VertexPoint[3].x = Form1->Width; VertexPoint[3].y = 26;
  VertexPoint[4].x = Form1->Width/2; VertexPoint[4].y = Form1->Height;

  m_reg = CreatePolygonRgn(VertexPoint,5,WINDING);

  SetWindowRgn(mwin,m_reg,1);
}
//---------------------------------------------------------------------------




