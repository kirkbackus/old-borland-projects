//---------------------------------------------------------------------------

#ifndef mapperH
#define mapperH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFormMapper : public TForm
{
__published:	// IDE-managed Components
        TScrollBox *ViewBox;
        TGroupBox *ViewerBox;
        TMainMenu *MainMenu;
        TMenuItem *F1;
        TMenuItem *Restart1;
        TMenuItem *Quit1;
        TMenuItem *Texture1;
        TMenuItem *Load1;
        TOpenPictureDialog *TextureDialog;
        TTimer *KeyTimer;
        TScrollBox *ShapePDisk;
        TSpeedButton *ShapeSphere;
        TSpeedButton *ShapeCylinder;
        TSpeedButton *ShapeDisk;
        TSpeedButton *SpeedButton3;
        TMenuItem *View1;
        TMenuItem *SetBackgroundColor1;
        TColorDialog *BgColorDialog;
        TGroupBox *ShapeBox;
        TMenuItem *N1;
        TMenuItem *Nearest1;
        TMenuItem *Linear1;
        TMenuItem *EnableLighting1;
        TMenuItem *N2;
        TMenuItem *N01;
        TMenuItem *SmoothShading1;
        TMenuItem *FlatShading1;
        TScrollBox *ScrollBox1;
        TStatusBar *StatusBar1;
        void __fastcall Quit1Click(TObject *Sender);
        void __fastcall Load1Click(TObject *Sender);
        void __fastcall KeyTimerTimer(TObject *Sender);
        void __fastcall ShapeSphereClick(TObject *Sender);
        void __fastcall ShapeCylinderClick(TObject *Sender);
        void __fastcall ShapeDiskClick(TObject *Sender);
        void __fastcall SpeedButton3Click(TObject *Sender);
        void __fastcall Restart1Click(TObject *Sender);
        void __fastcall SetBackgroundColor1Click(TObject *Sender);
        void __fastcall Nearest1Click(TObject *Sender);
        void __fastcall Linear1Click(TObject *Sender);
        void __fastcall EnableLighting1Click(TObject *Sender);
        void __fastcall SmoothShading1Click(TObject *Sender);
        void __fastcall FlatShading1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormMapper(TComponent* Owner);
        void __fastcall IdleLoop(TObject*, bool&);
        void __fastcall Render();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMapper *FormMapper;
//---------------------------------------------------------------------------
#endif
