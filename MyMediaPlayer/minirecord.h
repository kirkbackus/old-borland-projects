//---------------------------------------------------------------------------

#ifndef minirecordH
#define minirecordH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Forms.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
class TKMediaRec : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *RecordMenu;
        TMenuItem *File1;
        TMenuItem *New1;
        TMenuItem *Save1;
        TMenuItem *Close1;
        TScrollBox *ControlBox;
        TSplitter *Splitter1;
        TImageList *Image64;
        TImage *RecButton;
        TTimer *MediaTimer;
        TSaveDialog *SaveRecord;
        TLabel *Label1;
        void __fastcall RecButtonMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Close1Click(TObject *Sender);
        void __fastcall New1Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Save1Click(TObject *Sender);
        void __fastcall MediaTimerTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TKMediaRec(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TKMediaRec *KMediaRec;
//---------------------------------------------------------------------------
#endif
