class Bomb {
  private:
  int x,y,ind;
  int img;
  int time;
  int stime;
  int ctime;
  int index;
  bool solid;
  bool destroy;
  bool explode;

  public:

  Bomb();

  void Draw();

  void SetImage(int image_index);

  int GetX() {return x;}
  int GetY() {return y;}

  bool Destroyed() {return (destroy);}
  bool Ignite(int xpos, int ypos, int ms);
  bool Explode() { int tmp=explode; explode = 0; return tmp;}

  void BlowUp() { explode=1; destroy=1;}
};

inline Bomb::Bomb() {
  destroy = 1;
  explode = 0;
  img = -1;
  x=16;
  y=16;
  time=3000;
  stime = GetTickCount();
}

inline bool Bomb::Ignite(int xpos, int ypos, int ms) {
  if (destroy==1) {
    destroy=0;
    time=ms;
    x = ceil((float)xpos/16.0-.5)*16;
    y = ceil((float)ypos/16.0-.5)*16;
    time = ms;
    stime = GetTickCount();
    ctime = stime;
    return (true);
  }
  return (false);
}

void Bomb::SetImage(int image_index) {
  index = image_index;
}

inline void Bomb::Draw() {
  glEnable(GL_TEXTURE_2D);
  glColor3f(0.5,0.5,1.0);
  glPushMatrix ();

  glTranslatef(x,y,0);

  glBegin(GL_QUADS);

  glTexCoord2f(0.0f,1.0f); glVertex2f(0.0f,0.0f);
  glTexCoord2f(1.0f,1.0f); glVertex2f(16,0.0f);
  glTexCoord2f(1.0f,0.0f); glVertex2f(16,16);
  glTexCoord2f(0.0f,0.0f); glVertex2f(0.0f,16);

  glEnd();

  glPopMatrix();
  glColor3f(1.0,1.0,1.0);
  glDisable(GL_TEXTURE_2D);

  ctime = GetTickCount();
  if (ctime-stime>time) {
    explode=1;
    destroy=1;
  }
}