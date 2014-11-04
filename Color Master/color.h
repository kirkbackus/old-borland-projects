//---------------------------------------------------------------------------

#ifndef colorH
#define colorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TMColor : public TForm
{
__published:	// IDE-managed Components
        TShape *Color;
        TBevel *Bevel1;
        TLabel *Label1;
        TEdit *Edit1;
        TLabel *Label2;
        TEdit *Edit2;
        TLabel *Label3;
        TEdit *Edit3;
        TTrackBar *RedBar;
        TTrackBar *GreenBar;
        TTrackBar *BlueBar;
        TTimer *Timer1;
        TEdit *Hex;
        TBevel *Bevel2;
        TLabel *Label4;
        TButton *ScreenCol;
        TBevel *Bevel3;
        TColorDialog *ColorDialog1;
        void __fastcall RedBarChange(TObject *Sender);
        void __fastcall GreenBarChange(TObject *Sender);
        void __fastcall BlueBarChange(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Edit1Change(TObject *Sender);
        void __fastcall Edit2Change(TObject *Sender);
        void __fastcall Edit3Change(TObject *Sender);
        void __fastcall ScreenColClick(TObject *Sender);
        void __fastcall ColorMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
private:	// User declarations
public:		// User declarations
        __fastcall TMColor(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMColor *MColor;
//---------------------------------------------------------------------------
#endif
