//---------------------------------------------------------------------------

#ifndef quicksnapH
#define quicksnapH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <FileCtrl.hpp>
//---------------------------------------------------------------------------
class TQSnap : public TForm
{
__published:	// IDE-managed Components
        TImage *QSnapImage;
        TLabel *QSnapDirections;
        TTimer *QSnapTimer;
        TStatusBar *StatusBar1;
        TScrollBox *QSnapBox;
        TDirectoryListBox *QSnapDir;
        TButton *QSnapButton;
        TEdit *QSnapName;
        void __fastcall QSnapTimerTimer(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall QSnapButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TQSnap(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TQSnap *QSnap;
//---------------------------------------------------------------------------
#endif
