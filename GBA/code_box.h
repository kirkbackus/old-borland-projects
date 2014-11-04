//---------------------------------------------------------------------------

#ifndef code_boxH
#define code_boxH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "SynEdit.hpp"
#include "SynEditHighlighter.hpp"
#include "SynHighlighterCpp.hpp"

//---------------------------------------------------------------------------
class TCodeForm : public TForm
{
__published:	// IDE-managed Components
        TSynEdit *CodeBox;
        TSynCppSyn *CppLexer;
private:	// User declarations
public:		// User declarations
        __fastcall TCodeForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TCodeForm *CodeForm;
//---------------------------------------------------------------------------
#endif
