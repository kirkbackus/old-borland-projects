//---------------------------------------------------------------------------

#ifndef connect4H
#define connect4H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TC4Form : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *Game1;
        TMenuItem *NewGame1;
        TMenuItem *N1;
        TMenuItem *Exit1;
        TScrollBox *TitleBox;
        TLabel *Title;
        TScrollBox *GameBox;
        TTimer *GameTimer;
        TImage *GameImg;
        TStatusBar *C4StatusBar;
        TShape *TmpCircle;
        TMenuItem *Help1;
        TMenuItem *About1;
        TMenuItem *Transparency1;
        TMenuItem *N201;
        TMenuItem *N401;
        TMenuItem *N601;
        TMenuItem *N801;
        TMenuItem *N01;
        TMenuItem *Opaque1;
        TMenuItem *N901;
        TMenuItem *N2;
        TMenuItem *RemoveFromTaskbar1;
        void __fastcall NewGame1Click(TObject *Sender);
        void __fastcall Exit1Click(TObject *Sender);
        void __fastcall GameTimerTimer(TObject *Sender);
        void __fastcall GameImgMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall GameImgMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall About1Click(TObject *Sender);
        void __fastcall N201Click(TObject *Sender);
        void __fastcall N401Click(TObject *Sender);
        void __fastcall N601Click(TObject *Sender);
        void __fastcall N801Click(TObject *Sender);
        void __fastcall Opaque1Click(TObject *Sender);
        void __fastcall N901Click(TObject *Sender);
        void __fastcall RemoveFromTaskbar1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TC4Form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TC4Form *C4Form;
//---------------------------------------------------------------------------
#endif
