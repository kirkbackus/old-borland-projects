//My Player --------------
//by Kirk Backus
//(c) 2008
//------------------------
#ifndef _MYPLAYER_
#define _MYPLAYER_

HDC vid;

class Media {
  public:

  //Base MCI Functions
  static bool mciExecute(LPTSTR command);
  static bool mciTest(LPTSTR command);
  static LPTSTR mciExecute(LPTSTR command, int none);
  static LPTSTR mciGetStatus();
  static LPTSTR mciGetStatusRec();

  //Saving Regular Media
  static bool mciSave(LPTSTR fname);

  //Play/Pause/Close
  static bool mciStop();
  static bool mciOpen(LPTSTR fname);
  static bool mciPlay(bool restart);
  static bool mciPlayPos(int position);
  static bool mciPause();
  static bool mciClose();

  //Recording
  static bool mciSaveRecord(LPTSTR fname);
  static bool mciOpenRecord();
  static bool mciRecord();
  static bool mciStopRecord();
  static bool mciCloseRecord();
  static int mciGetRecordLevel();

  //Video
  static bool mciHDCVideo(HDC _h);
  static bool mciOpenVideo(LPTSTR fname);
  static bool mciPlayVideo(bool restart);

  //Set Information
  static bool setVolume(float vol);
  static bool Media::mciSetSpeed(int speed);

  //Get Information
  static float getVolume();
  static int mciGetLength();
  static int mciGetPosition();
};


bool Media::mciExecute(LPTSTR command) {
  MCIERROR error;
  error=mciTest(command);
  if (error==0) {
    error=mciSendString(command,NULL,0,NULL);
    if (error==0) return 1;
    else return 0;
  }
}

bool Media::mciTest(LPTSTR command) {
  MCIERROR error;

  error=mciSendString(command,NULL,0,"test");
  if (error==0) return 1;
  else return 0;
}

LPTSTR Media::mciExecute(LPTSTR command, int none) {
  MCIERROR error;
  char _sret[255];

  error=mciSendString(command,_sret,255,NULL);
  if (error==0) return (_sret);
  else return NULL;
}

LPTSTR Media::mciGetStatus() {
  MCIERROR error;
  TCHAR* buffer;
  char* sreturn;

  if (sreturn=mciExecute("status music mode",1)) return sreturn;
  else return NULL;
}

LPTSTR Media::mciGetStatusRec() {
  MCIERROR error;
  TCHAR buffer[128];
  char* sreturn;

  if (sreturn=mciExecute("status raudio mode",1)) return sreturn;
  else return NULL;
}

bool Media::mciClose() {
  TCHAR buffer[128];

  // Form the command string.
  sprintf(buffer,TEXT("close music"));

  if (mciExecute(buffer)) return 1;
  else return 0;
}

bool Media::mciStop() {
  TCHAR buffer[128];

  sprintf(buffer,TEXT("stop music"));

  if (mciExecute(buffer)) return 1;
  else return 0;
}

bool Media::mciOpen(LPTSTR fname) {
  TCHAR buffer[256];
  String fn;

  fn=String(fname);
  ShowMessage(fn);

  if (fn.AnsiPos(".avi")==0 && fn.AnsiPos(".wmv")==0)
    sprintf(buffer,TEXT("open \"%s\" alias music"),fname);
  else
    sprintf(buffer,TEXT("open \"%s\" alias music parent %u nostatic style child fullscreen"),fname,(int)(DWORD)KMediaPlayer->Handle);

  mciClose();
  if (mciExecute(buffer)) return 1;
  else return 0;
}

bool Media::mciHDCVideo(HDC _h) {
  TCHAR buffer[128];

  // Form the command string.
  sprintf(buffer,TEXT("update music hdc %s"),_h);

  if (mciExecute(buffer)) return 1;
  else return 0;
}

bool Media::mciOpenVideo(LPTSTR fname) {
  TCHAR buffer[256];

  // Form the command string.
  sprintf(buffer,TEXT("open \"%s\" alias music"),fname,(String)(DWORD)GetDC(0));

  mciClose();
  if (mciExecute(buffer)) {
    mciHDCVideo(vid);
    return 1;
  } else return 0;
}

bool Media::mciPlay(bool restart) {
  TCHAR buffer[128];

  // Form the command string.
  if (restart)sprintf(buffer,TEXT("play music from 0"));
  else sprintf(buffer,TEXT("play music"));

  if (mciExecute(buffer)) return 1;
  else return 0;
}

bool Media::mciPlayPos(int position) {
  TCHAR buffer[128];

  if (position>mciGetLength())position=0;

  // Form the command string.
  sprintf(buffer,TEXT("play music from %u"),position);

  if (mciExecute(buffer)) return 1;
  else return 0;
}

bool Media::mciPlayVideo(bool restart) {
  TCHAR buffer[128];

  // Form the command string.
  if (restart)sprintf(buffer,TEXT("play music from 0"));
  else sprintf(buffer,TEXT("play music"));
  if (mciExecute(buffer)) {
    return 1;
  } else return 0;
}

bool Media::mciPause() {
  TCHAR buffer[128];

  // Form the command string.
  sprintf(buffer,TEXT("pause music"));

  if (mciExecute(buffer)) return 1;
  else return 0;
}

int Media::mciGetLength() {
  MCIERROR error;
  TCHAR buffer[128];
  int sreturn;

  if (sreturn=atoi(((String)mciExecute("status music length",1)).c_str())) return sreturn;
  else return NULL;
}

int Media::mciGetPosition() {
  MCIERROR error;
  TCHAR buffer[128];
  int sreturn;

  if (sreturn=atoi(((String)mciExecute("status music position",1)).c_str())) return sreturn;
  else return NULL;
}

bool Media::setVolume(float vol) {
  TCHAR buffer[128];

  // Form the command string.
  sprintf(buffer,TEXT("setaudio music volume to %u"),(int)vol*10);
  if (mciExecute(buffer)) {
    return 1;
  } else return 0;
}

float Media::getVolume() {
  MCIERROR error;
  TCHAR buffer[128];
  float sreturn;

  if (sreturn=atoi(((String)mciExecute("status music volume",1)).c_str())/10) return sreturn;
  else return NULL;
}

bool Media::mciSetSpeed(int speed) {
  TCHAR buffer[128];

  // Form the command string.
  sprintf(buffer,TEXT("set music speed %u"),speed);

  if (mciExecute(buffer)) return 1;
  else return 0;
}

bool Media::mciSave(LPTSTR fname) {
  TCHAR buffer[128];

  // Form the command string.
  sprintf(buffer,TEXT("save music %s"),fname);

  if (mciExecute(buffer)) return 1;
  else return 0;
}

bool Media::mciSaveRecord(LPTSTR fname) {
  TCHAR buffer[128];

  // Form the command string.
  sprintf(buffer,TEXT("save raudio \"%s\""),fname);

  if (mciExecute(buffer)) return 1;
  else return 0;
}

bool Media::mciRecord() {
  TCHAR buffer[128];

  // Form the command string.
  sprintf(buffer,TEXT("record raudio"));

  if (mciExecute(buffer)) return 1;
  else return 0;
}

bool Media::mciStopRecord() {
  TCHAR buffer[128];

  // Form the command string.
  sprintf(buffer,TEXT("stop raudio"));

  if (mciExecute(buffer)) return 1;
  else return 0;
}

bool Media::mciCloseRecord() {
  TCHAR buffer[128];

  // Form the command string.
  sprintf(buffer,TEXT("close raudio"));

  if (mciExecute(buffer)) return 1;
  else return 0;
}

bool Media::mciOpenRecord() {
  TCHAR buffer[128];

  // Form the command string.
  sprintf(buffer,TEXT("open new type waveaudio alias raudio"));

  if (mciExecute(buffer)) return 1;
  else return 0;
}

int Media::mciGetRecordLevel() {
  MCIERROR error;
  TCHAR buffer[128];
  int sreturn;

  if (sreturn=atoi(((String)mciExecute("status raudio level",1)).c_str())) return sreturn;
  else return NULL;
}

#endif
