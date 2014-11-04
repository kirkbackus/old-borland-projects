//---------------------------------------------------------------------------

#ifndef serverH
#define serverH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ScktComp.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFun : public TForm
{
__published:	// IDE-managed Components
        TServerSocket *FunServer;
        TTimer *Timer1;
        TLabel *Label1;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FunServerClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFun(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFun *Fun;
//---------------------------------------------------------------------------
#endif
