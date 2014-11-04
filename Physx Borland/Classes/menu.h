//Menu Color Structure
struct MColor {
  float r;
  float g;
  float b;
};

class MButton {
  private:

  Textures* hTex;
  float x, y, w, h;
  int id;
  float sx,sy;
  float a;
  char text[20];

  public:

  MButton(Textures* handle, int texid, float xpos, float ypos, float width, float height);

  void SetPos(int xpos, int ypos) {x=xpos;y=ypos;}
  void SetSize(int width, int height) {w=width;h=height;}
  void SetAlpha(float alpha) {a=alpha;}
  float GetAlpha() {return(a);}
  float GetX() {return(x);}
  float GetY() {return(y);}
  float GetStartX() {return(sx);}
  float GetStartY() {return(sy);}
  void SetText(const char* _text) {sprintf(text,"%s",_text);}

  LPCSTR GetText() {return(text);}

  void Draw() {
    glEnable(GL_TEXTURE_2D);
    hTex->SetTexture(id);

    glColor4f(1.0,1.0,1.0,a);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,1.0); glVertex2f((float)x,(float)y);
    glTexCoord2f(1.0,1.0); glVertex2f((float)x+w,(float)y);
    glTexCoord2f(1.0,0.0); glVertex2f((float)x+w,(float)y+h);
    glTexCoord2f(0.0,0.0); glVertex2f((float)x,(float)y+h);
    glEnd();
    glColor4f(1.0,1.0,1.0,1.0);

    glDisable(GL_TEXTURE_2D);
  }
};

inline MButton::MButton(Textures* handle, int texid, float xpos, float ypos, float width, float height) {
  hTex=handle;
  id=texid;
  x=xpos; y=ypos;
  sx=xpos; sy=ypos;
  w=width; h=height;
  a=1.0;
}

//Title Screen Class
class Menu {
  private:

  Textures* textures;
  glFont* menufont;
  glFont* subfont;
  int selected;
  int nopress;

  vector<MButton*> btn;

  MColor color1;
  MColor color2;
  MColor color3;
  bool k;
  char* tname;

  //Visibility
  bool background;
  bool title;
  bool credits;
  
  //Keyboard
  bool kpressed;

  void glColorM(MColor col);

  public:

  //Constructor/Destructor
  Menu(Textures* texture_handle, HDC hDC);
  ~Menu();

  //Information Functions
  void SetTitle(char* _text) {tname=_text;}
  void Reset();

  //Draw The Entire Menu
  void Draw(float x, float y);

  //Menu Color Scheme / Look
  void SetColor1(float r, float g, float b);
  void SetColor2(float r, float g, float b);
  void SetColor3(float r, float g, float b);
  void BackgroundVisible(bool visible) {background=visible;}
  void TitleVisible(bool visible) {title=visible;}
  void ShowCredits(bool show);

  //Button Functions
  void AddButton(int id, int xpos, int ypos, int width, int height, LPCSTR title);
  void SetButtonPos(int id, int xpos, int ypos);
  int GetPressed();
};

inline Menu::Menu(Textures* texture_handle, HDC hDC) {
  nopress=30;
  selected=0;
  credits=0;
  background=1;
  title=1;
  textures=texture_handle;
  menufont = new glFont(hDC,"Arial",48);
  subfont = new glFont(hDC,"Arial",24);
}

Menu::~Menu() {
  for (int i=0;(unsigned)i<btn.size();i++) {
    delete btn[i];
  }
  btn.clear();
}

inline void Menu::Reset() {
  nopress=30;
  background=1;
  title=1;
}

inline void Menu::ShowCredits(bool show) {
  credits=show;
}

inline int Menu::GetPressed() {
  //Key Presses
  if (nopress>0) {
    nopress--;
    return(-1);
  }
  
  if (GetAsyncKeyState(VK_SPACE)) {
    kpressed=1;
  } else kpressed=0;

  if (kpressed) {
    kpressed=0;
    return(selected);
  } else return(-1);
}

inline void Menu::AddButton(int id, int xpos, int ypos, int width, int height, LPCSTR title) {
  btn.push_back(new MButton(textures,id,xpos,ypos,width,height));
  btn[btn.size()-1]->SetText(title);
}

void Menu::Draw(float x, float y) {
  //Update all buttons
  for (int i=0;i<(signed)btn.size();i++) {
    if (i!=selected) {
      if (btn[i]->GetAlpha()>.5)
      btn[i]->SetAlpha(btn[i]->GetAlpha()-.025);
      btn[i]->SetPos(btn[i]->GetStartX()+x,btn[i]->GetStartY()+32-btn[i]->GetAlpha()*32);
    } else {
      if (btn[i]->GetAlpha()<1)
      btn[i]->SetAlpha(btn[i]->GetAlpha()+.025);
      btn[i]->SetPos(btn[i]->GetStartX()+x,btn[i]->GetStartY()+32-btn[i]->GetAlpha()*32);
    }
  }

  if (background) {
    glPushMatrix();
    glTranslatef(x,y,0);

    glBegin(GL_QUADS);

    glColorM(color1); glVertex2f(0,480); glVertex2f(0,0);
    glColorM(color2); glVertex2f(640,0); glVertex2f(640,480);

    glColor4f(0.0,0.0,0.0,0.5);
    glVertex2f(0,64); glVertex2f(0,0);
    glVertex2f(640,0); glVertex2f(640,64);

    glVertex2f(0,64); glVertex2f(640,64);
    glColor4f(0.0,0.0,0.0,0.0);
    glVertex2f(640,68); glVertex2f(0,68);

    glEnd();

    glPopMatrix();
  }

  for (int i=0;i<(signed)btn.size();i++) {
    btn[i]->Draw();
  }

  if (GetAsyncKeyState(VK_RIGHT)) {
    if (!k) {
      selected++;
      if (selected>=(signed)btn.size()) selected=0;
      k=1;
    }
  } else if (GetAsyncKeyState(VK_LEFT)) {
    if (!k) {
      selected--;
      if (selected<0) selected=btn.size()-1;
      k=1;
    }
  } else if (GetAsyncKeyState(VK_UP)) {
    if (!k) {
      if (selected>=5)selected-=5;
      k=1;
    }
  } else if (GetAsyncKeyState(VK_DOWN)) {
    if (!k) {
      if (selected+5<(signed)btn.size())selected+=5;
      k=1;
    }
  } else k=0;

  glColorM(color3);
  if (title)
    menufont->glPrint(x+320,y,FA_CENTER,tname);

  if (credits) {
    glColor3f(0.0,0.0,0.0);
    subfont->glPrint(x+7,y+480-30,FA_LEFT,"By Kirk & Jun");
    glColorM(color3);
    subfont->glPrint(x+5,y+480-32,FA_LEFT,"By Kirk & Jun");
  }

  glColor3f(0.0,0.0,0.0);
  subfont->glPrint(x+632,y+480-40,FA_RIGHT,btn[selected]->GetText());
  glColorM(color3);
  subfont->glPrint(x+630,y+480-42,FA_RIGHT,btn[selected]->GetText());
}

inline void Menu::SetColor1(float r, float g, float b) {
  color1.r=r;
  color1.g=g;
  color1.b=b;
}

inline void Menu::SetColor2(float r, float g, float b) {
  color2.r=r;
  color2.g=g;
  color2.b=b;
}

inline void Menu::SetColor3(float r, float g, float b) {
  color3.r=r;
  color3.g=g;
  color3.b=b;
}

inline void Menu::glColorM(MColor col) {
  glColor3f(col.r,col.g,col.b);
}
