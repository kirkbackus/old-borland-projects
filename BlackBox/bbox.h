//---------------------------------------------------------------------------

#ifndef bboxH
#define bboxH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TBBForm : public TForm
{
__published:	// IDE-managed Components
        TTimer *Timer1;
        void __fastcall FormPaint(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TBBForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TBBForm *BBForm;
//---------------------------------------------------------------------------
#endif
