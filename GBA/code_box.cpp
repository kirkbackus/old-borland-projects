//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "code_box.h"
#include "gba.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SynEdit"
#pragma link "SynEditHighlighter"
#pragma link "SynHighlighterCpp"
#pragma link "SynEdit"
#pragma link "SynEditHighlighter"
#pragma link "SynHighlighterCpp"
#pragma resource "*.dfm"
TCodeForm *CodeForm;
//---------------------------------------------------------------------------
__fastcall TCodeForm::TCodeForm(TComponent* Owner)
        : TForm(Owner)
{
  //Code Box Attributes
  CodeBox->Gutter->FormatLineNumber(1);
  CodeBox->Highlighter=CppLexer;
  CodeBox->WantTabs=1;
  CodeBox->Gutter->ShowLineNumbers=1;
}
//---------------------------------------------------------------------------



