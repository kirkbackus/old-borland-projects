//---------------------------------------------------------------------------

#ifndef bombermanH
#define bombermanH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
#include <math.h>
#include "opengl.h"
#include "textures.h"
#include "field.h"
#include "player.h"
#include "bomb.h"
#include "explosion.h"

#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TBombForm : public TForm
{
__published:	// IDE-managed Components
        TTimer *Timer1;
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormPaint(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
  HDC hdc;
  HGLRC hrc;
  int PixelFormat;
  GLfloat w, h;
public:		// User declarations
        __fastcall TBombForm(TComponent* Owner);
        void __fastcall IdleLoop(TObject*, bool& done);
        void __fastcall RenderGLScene();
        void __fastcall DrawObjects();
};
//---------------------------------------------------------------------------
extern PACKAGE TBombForm *BombForm;
//---------------------------------------------------------------------------
#endif
