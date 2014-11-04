class Player {
  private:

  int x,y;
  Field* f;

  public:

  Player();
  Player(int xpos,int ypos);

  void SetField(Field* field);

  void Set(int xpos, int ypos);
  void Move(int xpos, int ypos);

  int GetX() {return x;}
  int GetY() {return y;}

  void Draw();
};

inline Player::Player() {
  x = 16; y = 16;
}

inline Player::Player(int xpos, int ypos) {
  x = xpos; y = ypos;
}

inline void Player::Move(int xpos, int ypos) {
  RECT pos;
  pos.left = x+xpos; pos.top = y+ypos; pos.right = 14; pos.bottom = 14;

  if (f->CollisionRect(pos)==0) {
    x += xpos;
    y += ypos;
  }
}

inline void Player::SetField(Field* field) {
  f = field;
}

inline void Player::Set(int xpos, int ypos) {
  x = xpos; y = ypos;
}

inline void Player::Draw() {
  glEnable(GL_TEXTURE_2D);
  glPushMatrix ();

  glTranslatef(x,y,0);

  glBegin(GL_QUADS);

  glTexCoord2f(0.0f,1.0f); glVertex2f(0.0f,0.0f);
  glTexCoord2f(1.0f,1.0f); glVertex2f(14,0.0f);
  glTexCoord2f(1.0f,0.0f); glVertex2f(14,14);
  glTexCoord2f(0.0f,0.0f); glVertex2f(0.0f,14);

  glEnd();

  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}
