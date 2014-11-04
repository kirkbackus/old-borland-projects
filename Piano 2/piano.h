//---------------------------------------------------------------------------

#ifndef pianoH
#define pianoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>

#include "esymidi.h"
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TPianoForm : public TForm
{
__published:	// IDE-managed Components
        TShape *KeyLowF;
        TShape *KeyLowG;
        TShape *KeyLowA;
        TShape *KeyLowFs;
        TShape *KeyLowGs;
        TShape *KeyLowB;
        TShape *KeyLowC;
        TShape *KeyLowAs;
        TShape *KeyLowD;
        TShape *KeyLowCs;
        TShape *KeyLowE;
        TShape *KeyLowDs;
        TShape *KeyHighC;
        TShape *KeyHighD;
        TShape *KeyHighCs;
        TShape *KeyHighE;
        TShape *KeyHighDs;
        TShape *KeyHighF;
        TShape *KeyHighG;
        TShape *KeyHighA;
        TShape *KeyHighFs;
        TShape *KeyHighGs;
        TShape *KeyHighB;
        TShape *KeyHighAs;
        TScrollBox *PianoBox;
        TTimer *PianoTimer;
        TShape *KeyTopC;
        TShape *BtnQuit;
        TLabel *LTitle;
        TShape *BtnOptions;
        void __fastcall PianoTimerTimer(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall Quit1Click(TObject *Sender);
        void __fastcall LTitleMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall BtnQuitMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall BtnQuitMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall BtnQuitMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall BtnOptionsMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
private:	// User declarations
public:		// User declarations
        int octave;
        __fastcall TPianoForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPianoForm *PianoForm;
//---------------------------------------------------------------------------
#endif
