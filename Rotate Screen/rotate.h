//---------------------------------------------------------------------------

#ifndef rotateH
#define rotateH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TButton *BUp;
        TButton *BDown;
        TButton *BRight;
        TButton *BLeft;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BUpClick(TObject *Sender);
        void __fastcall BLeftClick(TObject *Sender);
        void __fastcall BRightClick(TObject *Sender);
        void __fastcall BDownClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
