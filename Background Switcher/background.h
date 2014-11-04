//---------------------------------------------------------------------------

#ifndef backgroundH
#define backgroundH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <ExtCtrls.hpp>
#include "trayicon.h"
#include <ImgList.hpp>

//SPI_GETDESKWALLPAPER
//SPI_SETDESKWALLPAPER

char GetWallpaper() {
  char buffer[255];
  SystemParametersInfo(SPI_GETDESKWALLPAPER,sizeof(buffer)-1, buffer, 0);
  return *buffer;
}


bool SetWallpaper(char* buffer) {
  return(SystemParametersInfo(SPI_SETDESKWALLPAPER,0, buffer, 0));
}
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TListBox *ImageList;
        TGroupBox *GroupBox2;
        TButton *AddImg;
        TButton *DelImg;
        TOpenPictureDialog *OpenPic;
        TGroupBox *ImgPrev;
        TScrollBox *ScrollBox1;
        TImage *Image1;
        TEdit *DelayEdit;
        TButton *SetDelay;
        TTimer *Delay;
        TButton *Start;
        TButton *Stop;
        TLabel *ImgInd;
        TTrayIcon *TrayIcon1;
        TImageList *ImageList1;
        void __fastcall AddImgClick(TObject *Sender);
        void __fastcall ImageListClick(TObject *Sender);
        void __fastcall DelImgClick(TObject *Sender);
        void __fastcall SetDelayClick(TObject *Sender);
        void __fastcall StartClick(TObject *Sender);
        void __fastcall StopClick(TObject *Sender);
        void __fastcall DelayTimer(TObject *Sender);
        void __fastcall TrayIcon1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
