//---------------------------------------------------------------------------

#ifndef mplayH
#define mplayH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TGameForm : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *Menu;
        TMenuItem *Game1;
        TMenuItem *Host1;
        TMenuItem *Join1;
        TMenuItem *N1;
        TMenuItem *Quit1;
        TTimer *HostTimer;
        TTimer *ClientTimer;
        TLabel *LStatus;
        TStatusBar *GameSBar;
        TShape *HostPaddle;
        TShape *ClientPaddle;
        TShape *Ball;
        TScrollBox *GameBox;
        TLabel *LScore;
        TShape *BackDivider;
        TMenuItem *EndGame1;
        TScrollBox *JoinBox;
        TLabel *Label1;
        TEdit *IPEdit;
        TButton *JoinButton;
        void __fastcall Quit1Click(TObject *Sender);
        void __fastcall Host1Click(TObject *Sender);
        void __fastcall HostTimerTimer(TObject *Sender);
        void __fastcall Join1Click(TObject *Sender);
        void __fastcall ClientTimerTimer(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall EndGame1Click(TObject *Sender);
        void __fastcall JoinButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TGameForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGameForm *GameForm;
//---------------------------------------------------------------------------
#endif
