//---------------------------------------------------------------------------

#ifndef dballH
#define dballH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <math.h>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include "trayicon.h"
#include <ImgList.hpp>
#include <Menus.hpp>
#include <Graphics.hpp>

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
        TButton *Button1;
        TTimer *Timer1;
        TGroupBox *Control;
        TButton *Button2;
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TLabel *Label2;
        TTrackBar *TrackBar1;
        TButton *Button3;
        TGroupBox *GroupBox2;
        TComboBox *ComboBox1;
        TButton *Button4;
        TLabel *Label3;
        TBevel *Bevel1;
        TColorDialog *ColorDialog1;
        TLabel *Label4;
        TShape *Shape1;
        TButton *Button5;
        TButton *Button6;
        TTrayIcon *TrayIcon1;
        TImageList *ImageList1;
        TPopupMenu *PopupMenu1;
        TMenuItem *ShowOptions1;
        TMenuItem *AddBall1;
        TMenuItem *FreezeBalls1;
        TMenuItem *Quit1;
        TMenuItem *EraseBall1;
        TLabel *Label5;
        TTrackBar *TrackBar2;
        TStatusBar *StatusBar1;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall TrackBar1Change(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall ComboBox1Change(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall TrayIcon1Click(TObject *Sender);
        void __fastcall ShowOptions1Click(TObject *Sender);
        void __fastcall AddBall1Click(TObject *Sender);
        void __fastcall EraseBall1Click(TObject *Sender);
        void __fastcall FreezeBalls1Click(TObject *Sender);
        void __fastcall Quit1Click(TObject *Sender);
        void __fastcall TrackBar2Change(TObject *Sender);
private:	// User declarations
        TForm *Ball[30];
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
