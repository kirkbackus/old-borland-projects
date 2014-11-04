//---------------------------------------------------------------------------

#ifndef enumH
#define enumH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "trayicon.h"
#include <ImgList.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TBallForm : public TForm
{
__published:	// IDE-managed Components
        TShape *SBall;
        TTimer *BallTimer;
        TTimer *WindowTimer;
        TTrayIcon *DBallTray;
        TImageList *ImageList1;
        TPopupMenu *TrayOptions;
        TMenuItem *ShowOptions1;
        TMenuItem *Quit1;
        TMenuItem *StopBall1;
        TMenuItem *N1;
        void __fastcall BallTimerTimer(TObject *Sender);
        void __fastcall SBallMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall WindowTimerTimer(TObject *Sender);
        void __fastcall Quit1Click(TObject *Sender);
        void __fastcall StopBall1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall ShowOptions1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TBallForm(TComponent* Owner);
        bool collide_windows;
        float fric;
        float gravity;
};
//---------------------------------------------------------------------------
extern PACKAGE TBallForm *BallForm;
//---------------------------------------------------------------------------
#endif
