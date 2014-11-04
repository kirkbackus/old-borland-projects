//---------------------------------------------------------------------------

#ifndef gbaH
#define gbaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <Grids.hpp>
#include <Outline.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "frameleft.h"
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *File1;
        TMenuItem *New1;
        TMenuItem *Save1;
        TMenuItem *Open1;
        TMenuItem *SaveProjectAs1;
        TMenuItem *Quit1;
        TMenuItem *Program1;
        TMenuItem *Compile1;
        TMenuItem *Run1;
        TStatusBar *StatusBar;
        TScrollBox *CWBox;
        TRichEdit *CompilerWindow;
        TTreeView *TreeView1;
        TSplitter *HSplit;
        TSplitter *VSplit;
        void __fastcall Quit1Click(TObject *Sender);
        void __fastcall Compile1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
