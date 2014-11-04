#ifndef __STATIC_WATER_H
#define __STATIC_WATER_H

class Water {
  public:

  int id;
  int bodyid;
  int bclassid;
  float x,y,width,height;
  float _r, _g, _b, _a;

  Water(int x1, int y1, int x2, int y2) {
    x = x1;
    y = y1;
    width = x2-x1;
    height = y2-y1;

    id=CreateWater(x1,y1,x2,y2,1.25,0.05,false,8);
    SetWaterWaves(id,true,.25);
    SetWaterWavesUpdateFactor(id,.05);
  }

  ~Water() {
    DestroyWater(id);
  }

  void setColor(float red, float green, float blue, float alpha) {
    _r = red; _g = green; _b = blue; _a = alpha;
  }

  void Draw();
};

void Water::Draw() {
  glColor4f(_r, _g, _b, _a);
  int waves = GetWaterWavesNumPoints(id);
  float xc,yc,xp,yp;
  xp = x;
  yp = y;

  glPushMatrix();

  //glTranslatef(x,y,0);

  glBegin(GL_TRIANGLES);

  int i;
  for (i=0;i<waves-1;i++) {
    xc = GetWaterWavesPointX(id,i);
    yc = GetWaterWavesPointY(id,i);

    glVertex2f(xp,yp);
    glVertex2f(xc,yc);
    glVertex2f(xp,y+height);

    glVertex2f(xp,y+height);
    glVertex2f(xc,yc);
    glVertex2f(xc,y+height);

    xp = xc;
    yp = yc;
  }

  xc = x+width;
  yc = y;

  glVertex2f(xp,yp);
  glVertex2f(xc,yc);
  glVertex2f(xp,y+height);

  glVertex2f(xp,y+height);
  glVertex2f(xc,yc);
  glVertex2f(xc,y+height);

  glEnd();

  glPopMatrix();
}

#endif