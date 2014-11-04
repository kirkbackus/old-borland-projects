//---------------------------------------------------------------------------

#ifndef db3optionsH
#define db3optionsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFormOptions : public TForm
{
__published:	// IDE-managed Components
        TScrollBox *ScrollBox1;
        TLabel *LTitle;
        TLabel *LCollide;
        TComboBox *CollideOption;
        TLabel *LColor;
        TShape *SColor;
        TColorDialog *BallColor;
        TStatusBar *DBallStatus;
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TLabel *Label2;
        TTrackBar *TransBar;
        TTrackBar *FrictionBar;
        TGroupBox *GroupBox2;
        TLabel *LPosition;
        TLabel *LVelocity;
        TLabel *Label3;
        TTrackBar *GravBar;
        TLabel *Label4;
        TGroupBox *GroupBox3;
        TButton *QuitBtn;
        void __fastcall CollideOptionChange(TObject *Sender);
        void __fastcall SColorMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall TransBarChange(TObject *Sender);
        void __fastcall FrictionBarChange(TObject *Sender);
        void __fastcall GravBarChange(TObject *Sender);
        void __fastcall QuitBtnClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormOptions(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormOptions *FormOptions;
//---------------------------------------------------------------------------
#endif
