//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "memory.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
  MEMORYSTATUS pt1;
  double ramavail;
  double pagetotal;
  double ramused;

  pt1.dwLength = sizeof(MEMORYSTATUS);
  GlobalMemoryStatus(&pt1);

  ramavail = pt1.dwAvailPhys;
  pagetotal = pt1.dwTotalPageFile;
  //ramused = pagetotal-ramavail;

  Label1->Caption="RAM LEFT: "+FloatToStr((double)ramavail/(double)(1024.0*1024.0));
  Label2->Caption="RAM USED: "+FloatToStr((double)pagetotal/(double)(1024.0*1024.0));
}
//---------------------------------------------------------------------------

