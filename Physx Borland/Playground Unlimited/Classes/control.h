class Race {
  private:

  //Beginning time and Time Controller
  int start_time;
  int time;
  int race_time;

  //Ready Set Go Time Controller
  int rsg_time;
  int rsg;

  char* GetTimeMS(int ms);

  bool started;
  bool ended;
  bool rstart;

  float tx,ty;
  float sx,sy;

  glFont* fRSG;
  glFont* fTime;

  public:

  //Constructor
  Race(HDC dc);
  ~Race();

  //Setting Drawing Values
  void SetTime(float x, float y) {tx=x; ty=y;}
  void SetRSG(float x, float y) {sx=x; sy=y;}
  void EndRace() {ended=1;}

  //Race Started
  bool RaceStarted() {return rstart;}
  bool RaceEnded() {return ended;}

  //Updating Functions
  void Draw();
};

inline Race::Race(HDC dc) {
  fRSG = new glFont(dc,"Arial",128);
  fTime = new glFont(dc,"Arial",32);

  start_time=GetTickCount();
  time=GetTickCount();

  race_time=0;
  rsg_time=0;
  rsg=3;

  started=0;
  ended=0;
  rstart=0;
}

Race::~Race() {
  delete fRSG;
  delete fTime;
}

inline void Race::Draw() {
  time=GetTickCount();
  if (!started) {
    if (!rstart)
      rsg_time=4000-(time-start_time);
    else
      rsg_time=2000-(time-start_time);

    glColor4f(1.0f,1.0f,1.0f,((rsg_time+20)-((rsg_time+20)/1000)*1000)/1000.0);

    if (!rstart)
      fRSG->glPrint(sx,sy,FA_CENTER,"%u",rsg);
    else
      fRSG->glPrint(sx,sy,FA_CENTER,"GO!");

    if ((rsg_time/1000)+1<=rsg)--rsg;

    if (rsg<=0 && !rstart) {
      start_time=GetTickCount();
      rsg=3;
      rstart=1;
    }

    if (rsg<=0 && rstart) {
      started=1;
    }
  } else {
    glColor4f(1.0,1.0,1.0,1.0);
    if (!ended)
    race_time=time-start_time;
    fTime->glPrint(tx,ty,FA_RIGHT,"%s",GetTimeMS(race_time));
  }

  glColor4f(1.0,1.0,1.0,1.0);
}

inline char* Race::GetTimeMS(int ms) {
  int mil=ms;
  int sec=ms/1000;
  int min=sec/60;
  sec-=min*60;
  mil-=sec*1000+min*60*1000;
  mil/=100;

  char buffer[20];

  if (min<10 && sec<10)
  sprintf(buffer,"0%u:0%u:%u",min,sec,mil);
  else if (min<10)
  sprintf(buffer,"0%u:%u:%u",min,sec,mil);
  else if (sec<10)
  sprintf(buffer,"%u:0%u:%u",min,sec,mil);
  else
  sprintf(buffer,"%u:%u:%u",min,sec,mil);

  return(buffer);
}
