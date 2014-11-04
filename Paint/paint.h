//---------------------------------------------------------------------------

#ifndef paintH
#define paintH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <FileCtrl.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include "CGRID.h"
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <OleCtnrs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TImage *PaintCanvas;
        TStatusBar *StatusBar1;
        TMainMenu *MainMenu1;
        TMenuItem *File1;
        TMenuItem *New1;
        TMenuItem *Open1;
        TMenuItem *Save1;
        TMenuItem *Quit1;
        TMenuItem *SaveAs1;
        TSpeedButton *Pencil;
        TSpeedButton *Line;
        TSpeedButton *Rectangle;
        TSpeedButton *RoundRect;
        TSpeedButton *Circle;
        TScrollBox *ScrollBox1;
        TPanel *Panel1;
        TCColorGrid *CColorGrid1;
        TBevel *Bevel1;
        TShape *Shape1;
        TShape *Shape2;
        TOpenPictureDialog *OpenPictureDialog1;
        TSavePictureDialog *SavePictureDialog1;
        TColorDialog *ColorDialog1;
        TMenuItem *Edit1;
        TMenuItem *Copy1;
        TMenuItem *Paste1;
        TTimer *Timer1;
        void __fastcall Quit1Click(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall CColorGrid1Change(TObject *Sender);
        void __fastcall Open1Click(TObject *Sender);
        void __fastcall Save1Click(TObject *Sender);
        void __fastcall Shape2MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Shape1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall New1Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
