//---------------------------------------------------------------------------

#ifndef levelH
#define levelH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
  TScrollBox *ScrollBox1;
  TMainMenu *MainMenu1;
  TMenuItem *File1;
  TMenuItem *New1;
        TMenuItem *Save1;
        TMenuItem *Open1;
  TMenuItem *Quit1;
  TSpeedButton *SPoint;
  TSpeedButton *SStart;
  TSpeedButton *SEnd;
  TStatusBar *MStatusBar;
  TSaveDialog *TerrainSave;
  TOpenDialog *TerrainOpen;
        TScrollBox *ScrollBox2;
        TMenuItem *Status1;
        TMenuItem *TerrainInfo1;
        TMenuItem *Tools1;
        TMenuItem *AddRemovePoints1;
        TMenuItem *StartingPoint1;
        TMenuItem *EndingPoint1;
        TMenuItem *About1;
        TMenuItem *ResetView1;
        TTimer *ViewTimer;
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TEdit *EditName;
        TLabel *Label2;
        TEdit *EditPassword;
        TComboBox *EditDifficulty;
        TShape *EditColor;
        TColorDialog *EditColorDB;
  void __fastcall Quit1Click(TObject *Sender);
  void __fastcall ScrollBox1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
  void __fastcall SPointClick(TObject *Sender);
  void __fastcall SStartClick(TObject *Sender);
  void __fastcall SEndClick(TObject *Sender);
  void __fastcall New1Click(TObject *Sender);
  void __fastcall ScrollBox1MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall Save1Click(TObject *Sender);
        void __fastcall Open1Click(TObject *Sender);
        void __fastcall TerrainInfo1Click(TObject *Sender);
        void __fastcall StartingPoint1Click(TObject *Sender);
        void __fastcall EndingPoint1Click(TObject *Sender);
        void __fastcall AddRemovePoints1Click(TObject *Sender);
        void __fastcall About1Click(TObject *Sender);
        void __fastcall ResetView1Click(TObject *Sender);
        void __fastcall ViewTimerTimer(TObject *Sender);
        void __fastcall EditColorMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall EditNameChange(TObject *Sender);
        void __fastcall EditPasswordChange(TObject *Sender);
        void __fastcall EditDifficultyChange(TObject *Sender);
private:	// User declarations
  int Tool;
public:		// User declarations
  __fastcall TForm1(TComponent* Owner);
  void __fastcall IdleLoop(TObject*, bool&); 

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
