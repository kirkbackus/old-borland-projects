//---------------------------------------------------------------------------

#ifndef basicH
#define basicH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

#include <math.h>
#include <stdlib.h>
#include "collision.h"
#include <Graphics.hpp>
#include <jpeg.hpp>

#define pi 3.14159

float point_distance(float x1, float y1, float x2, float y2) {
  return (sqrt(pow(x2-x1,2)+pow(y2-y1,2)));
}

float point_direction(float x1, float y1, float x2, float y2) {
  if (abs(x1-x2) != 0)
  {
    if (x1 < x2)
      return(180+(180/pi)*atan(((y1-y2)/abs(x1-x2))));
    else {
      if (y1 <= y2)
        return(-(180/pi)*atan(((y1-y2)/abs(x1-x2))));
      else
        return(360-(180/pi)*atan(((y1-y2)/abs(x1-x2))));
   }
 } else {
    if (y1 > y2)
      return (270);
    else
      return (90);
  }
}

float lengthdir_x(float len,float dir) {
  return (len*cos(dir*(pi/180)));
}

float lengthdir_y(float len,float dir) {
  return (-len*sin(dir*(pi/180)));
}

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TTimer *Timer1;
        TImage *Image1;
        TImage *Image2;
        void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
