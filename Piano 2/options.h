//---------------------------------------------------------------------------

#ifndef optionsH
#define optionsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include "CSPIN.h"
//---------------------------------------------------------------------------
class TOptionForm : public TForm
{
__published:	// IDE-managed Components
        TListBox *InstrumentBox;
        TLabel *LInstrument;
        TLabel *LWindow;
        TTrackBar *TransBar;
        TCheckBox *TBtnBox;
        TLabel *LTrans;
        TLabel *Label1;
        TCSpinEdit *Octave;
        TLabel *Label2;
        void __fastcall InstrumentBoxClick(TObject *Sender);
        void __fastcall TransBarChange(TObject *Sender);
        void __fastcall TBtnBoxClick(TObject *Sender);
        void __fastcall OctaveChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TOptionForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TOptionForm *OptionForm;
//---------------------------------------------------------------------------
#endif
