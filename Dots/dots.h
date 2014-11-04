//---------------------------------------------------------------------------

#ifndef dotsH
#define dotsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TDotForm : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *Interface;
        TButton *Generate;
        TLabel *LSpeed;
        TLabel *LSize;
        TLabel *LAngle;
        TLabel *LSpacing;
        TEdit *Speed;
        TEdit *Size;
        TEdit *Angle;
        TEdit *Space;
        TTimer *Controller;
        void __fastcall GenerateClick(TObject *Sender);
        void __fastcall ControllerTimer(TObject *Sender);
        void __fastcall FormPaint(TObject *Sender);
        void __fastcall SpeedChange(TObject *Sender);
        void __fastcall SpaceChange(TObject *Sender);
        void __fastcall SizeChange(TObject *Sender);
        void __fastcall AngleChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TDotForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDotForm *DotForm;
//---------------------------------------------------------------------------
#endif
