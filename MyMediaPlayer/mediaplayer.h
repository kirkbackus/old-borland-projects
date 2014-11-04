//---------------------------------------------------------------------------

#ifndef mediaplayerH
#define mediaplayerH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <FileCtrl.hpp>
#include <Forms.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------

String SecToTime(int sec) {
  int _min,_sec;
  String m,s;

  _min=(int)(sec/60);
  _sec=sec-_min*60;

  if (_sec<10)s="0"+(String)_sec;
  else s=(String)_sec;
  if (_min<10)m=(String)_min;
  else m=(String)_min;

  return(m+":"+s);
}

class TKMediaPlayer : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MediaMenu;
        TMenuItem *Open1;
        TMenuItem *Quit1;
        TOpenDialog *MediaOpen;
        TImageList *Image64;
        TImageList *Image16;
        TMenuItem *MenuFile;
        TScrollBox *ControlBox;
        TImage *PlayButton;
        TLabel *Label1;
        TTimer *MediaTimer;
        TShape *TrackLeft;
        TShape *TrackRight;
        TImage *TrackButton;
        TMenuItem *Play1;
        TMenuItem *Repeat1;
        TShape *VolumeLeft;
        TImage *VolumeButton;
        TShape *VolumeRight;
        TMenuItem *PlaySpeed1;
        TMenuItem *VerySlow1;
        TMenuItem *Slow1;
        TMenuItem *Normal1;
        TMenuItem *Fast1;
        TMenuItem *VeryFast1;
        TDirectoryListBox *MusicDirectory;
        TFileListBox *MusicFiles;
        TSplitter *Splitter1;
        TSplitter *Splitter2;
        TMenuItem *Extras1;
        TMenuItem *SoundRecorder1;
        TOpenDialog *VideoOpen;
        TMenuItem *Play2;
        void __fastcall Open1Click(TObject *Sender);
        void __fastcall Quit1Click(TObject *Sender);
        void __fastcall PlayButtonClick(TObject *Sender);
        void __fastcall MediaTimerTimer(TObject *Sender);
        void __fastcall TrackButtonMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall OpenVideo1Click(TObject *Sender);
        void __fastcall Repeat1Click(TObject *Sender);
        void __fastcall VolumeButtonMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall VerySlow1Click(TObject *Sender);
        void __fastcall Slow1Click(TObject *Sender);
        void __fastcall Normal1Click(TObject *Sender);
        void __fastcall Fast1Click(TObject *Sender);
        void __fastcall VeryFast1Click(TObject *Sender);
        void __fastcall MusicDirectoryChange(TObject *Sender);
        void __fastcall MusicFilesDblClick(TObject *Sender);
        void __fastcall SoundRecorder1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TKMediaPlayer(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TKMediaPlayer *KMediaPlayer;
//---------------------------------------------------------------------------
#endif
