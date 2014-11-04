#ifndef __POWERBAR_H
#define __POWERBAR_H

class Powerbar
{
        public:

        Powerbar(float max);

        void Draw();
        float GetValue();
        void SetValue(float val);
        void SetPos(float xpos, float ypos, float _width, float _height);
        void AddValue(float val);
        void SetColor(float _r, float _g, float _b) { r=_r;g=_g;b=_b; }
        void Reset();

        private:

        float jump;
        float jump1;
        float max_jump;
        float r,g,b;

        float x,y,width,height;
};

inline Powerbar::Powerbar(float max) {
        jump=0;
        jump1=0;
        max_jump=max;

        r=0.5;
        g=1.0;
        b=0.25;
}

inline void Powerbar::Draw() {
  if (jump1>0)jump1-=1;
  if (jump1<jump)jump1=jump;
  DrawRect(x,y,width,height,0);
  glColor3f(r,g,b);
  DrawRect(x,y,width*(jump1/max_jump),height/2,0);
  glColor3f(r-.1,g-.1,b-.1);
  DrawRect(x,y+height/2,width*(jump1/max_jump),height/2,0);
  glColor3f(0.0,0.0,0.0);
  DrawRectOut(x,y,width,height,0);
  glColor3f(1.0,1.0,1.0);
}

inline void Powerbar::SetPos(float xpos, float ypos, float _width, float _height) {
  x=xpos;
  y=ypos;
  width=_width;
  height=_height;
}

inline float Powerbar::GetValue() {
  return(jump);
}

inline void Powerbar::SetValue(float val) {
  jump=val;
  if (jump>max_jump)
    jump=max_jump;
}

inline void Powerbar::AddValue(float val) {
  jump+=val;
  if (jump>max_jump)
    jump=max_jump;
}

inline void Powerbar::Reset() {
  jump=0;
}

#endif
