class Field {

  private:

  int fieldarr[21][21];
  Textures* txt;
  int img[2];

  public:

  Field(Textures* textures);

  void SetImage(int type, int image_index);
  void SetPosition(int x, int y, int val);
  int GetPosition(int x, int y);
  bool CollisionRect(RECT r);

  void Draw();
};

Field::Field(Textures* textures) {
  for (int x=0;x<21;x++) for (int y=0;y<21;y++) fieldarr[x][y]=0;
  txt = textures;
}

void Field::SetImage(int type, int image_index) {
  img[type]=image_index;
}

inline void Field::SetPosition(int x, int y, int val) {
  fieldarr[x][y]=val;
}

inline int Field::GetPosition(int x, int y) {return(fieldarr[x][y]);}

bool Field::CollisionRect(RECT r) {
  int rx = r.left/16;
  int ry = r.top/16;

  for (int x=rx-1;x<=rx+1;x++) {
    for (int y=ry-1;y<=ry+1;y++) {
      if (x<0 || x>=21 || y<0 || y>=21)continue;
      if (fieldarr[x][y]==0)continue;
      if (r.left + r.right > x*16 &&
          r.top + r.bottom > y*16 &&
          r.left < x*16+16 &&
          r.top < y*16+16) return 1;
    }
  }
  return 0;
}

void Field::Draw() {
  for (int x=0;x<21;x++) for (int y=0;y<21;y++) {
    if (fieldarr[x][y]==1) {
      txt->SetTexture(img[0]);
      glEnable(GL_TEXTURE_2D);
      glPushMatrix ();

      glTranslatef(x*16,y*16,0);

      glBegin(GL_QUADS);

      glTexCoord2f(0.0f,1.0f); glVertex2f(0.0f,0.0f);
      glTexCoord2f(1.0f,1.0f); glVertex2f(16,0.0f);
      glTexCoord2f(1.0f,0.0f); glVertex2f(16,16);
      glTexCoord2f(0.0f,0.0f); glVertex2f(0.0f,16);

      glEnd();

      glPopMatrix();
      glDisable(GL_TEXTURE_2D);
    }
  }
}
