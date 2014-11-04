#ifndef _PROGRESS_H
#define _PROGRESS_H

class Progress
{
  public:

  Progress(float _length);
  void SetPos(float _x, float _y,float _min, float _max,float _pos_x);
  void SetPos(float _x, float _y,float _min, float _max,float _pos_x, float _pos2_x);
  void Draw();
  void NumCars(bool second_car) { second = second_car; }

  private:

  float car_pos;
  float car_pos2;
  float length;
  float min;
  float max;
  float pos_x;
  float pos2_x;
  float x;
  float y;

  bool second;
};

inline Progress::Progress (float _length)
{
  length=_length;
}

inline void Progress::SetPos(float _x, float _y, float _min, float _max, float _pos_x)
{
  x=_x;
  y=_y;
  min=_min;
  max=_max;
  pos_x=_pos_x;
  car_pos=x+length*(pos_x-min)/(max-min);
  second=0;
}

inline void Progress::SetPos(float _x, float _y, float _min, float _max, float _pos_x, float _pos2_x)
{
  x=_x;
  y=_y;
  min=_min;
  max=_max;
  pos_x=_pos_x;
  car_pos=x+length*(pos_x-min)/(max-min);
  pos2_x=_pos2_x;
  car_pos2=x+length*(pos2_x-min)/(max-min);
}

inline void Progress::Draw()
{
  DrawRect(x,y,length,2,0);
  glColor3f(0.5,1.0,0.25);
  DrawRectOut(x,y,630,2,0);
  glColor3f(1.0,1.0,1.0);
  if (pos_x<max) {
    if (second) glColor3f(0.5,1.0,0.5);
    else glColor3f(1.0,1.0,1.0);
    DrawCircle(car_pos,y+1,5,0);

    if (second) {
      glColor3f(1.0,0.5,0.5);
      DrawCircle(car_pos2,y+1,5,0);
    }

    glColor3f(1.0,0,0);
  } else  {
    DrawCircle(x+630,y+1,5,0);
    glColor3f(1.0,0,0);
  }
}

#endif
