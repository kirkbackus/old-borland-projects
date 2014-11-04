//---------------------------------------------------------------------------

#ifndef midiH
#define midiH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>

#include "esymidi.h"

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TTimer *SongTimer;
        TLabel *Note;
        TComboBox *Instruments;
        TGroupBox *MusicPlay;
        TGroupBox *Debug;
        TLabel *NotesCap;
        TGroupBox *Control;
        TLabel *VolCap;
        TTrackBar *Volume;
        TButton *Stop;
        TButton *Button2;
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall SongTimerTimer(TObject *Sender);
        void __fastcall InstrumentsChange(TObject *Sender);
        void __fastcall StopClick(TObject *Sender);
        void __fastcall VolumeChange(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
