#ifndef __DYNAMIC_SPRINGS_H
#define __DYNAMIC_SPRINGS_H

class Spring {
  private:

  float _r, _g, _b, _a;

  public:

  int id;
  int bodyid;
  int b1,b2;
  float x1,y1,x2,y2;
  float len;
  float minforce, maxforce;

  Spring(int body1, int body2) {
    b1 = body1; b2 = body2;
    x1 = GetBodyX(b1); y1 = GetBodyY(b1);
    x2 = GetBodyX(b2); y2 = GetBodyY(b2);
    len = PointDistance(x1,y1,x2,y2);
    minforce = 100;
    maxforce = 500;
    bodyid = WORLD;
    id = (int)CreateSpring(b1,b2,x1,y1,x2,y2,len*1.2,len*1.5,minforce,maxforce);
  }

  Spring(int body1, int body2, int minf, int maxf) {
    b1 = body1; b2 = body2;
    x1 = GetBodyX(b1); y1 = GetBodyY(b1);
    x2 = GetBodyX(b2); y2 = GetBodyY(b2);
    len = PointDistance(x1,y1,x2,y2);
    minforce = minf;
    maxforce = maxf;
    bodyid = WORLD;
    id = (int)CreateSpring(b1,b2,x1,y1,x2,y2,len*1.2,len*1.5,minforce,maxforce);
  }

  Spring(int body1, int body2, float length) {
    b1 = body1; b2 = body2;
    x1 = GetBodyX(b1); y1 = GetBodyY(b1);
    x2 = GetBodyX(b2); y2 = GetBodyY(b2);
    len = length;
    minforce = 100;
    maxforce = 500;
    id = (int)CreateSpring(b1,b2,x1,y1,x2,y2,len,len*2,2,2);
  }

  Spring(int body1, int body2, float _x1, float _y1, float _x2, float _y2) {
    b1 = body1; b2 = body2;
    x1 = _x1; y1 = _y1; x2 = _x2; y2 = _y2;
    len = PointDistance(x1,y1,x2,y2);
    minforce = 100;
    maxforce = 500;
    bodyid = WORLD;
    id = (int)CreateSpring(b1,b2,x1,y1,x2,y2,len,len*2,minforce,maxforce);
  }

  Spring(int body1, int body2, float length, float _x1, float _y1, float _x2, float _y2) {
    b1 = body1; b2 = body2;
    x1 = _x1; y1 = _y1; x2 = _x2; y2 = _y2;
    len = length;
    minforce = 100;
    maxforce = 500;
    bodyid = WORLD;
    id = (int)CreateSpring(b1,b2,x1,y1,x2,y2,len,len*2,minforce,maxforce);
  }

  Spring(int body1, int body2, float length, float _x1, float _y1, float _x2, float _y2, float minf, float maxf) {
    b1 = body1; b2 = body2;
    x1 = _x1; y1 = _y1; x2 = _x2; y2 = _y2;
    len = length;
    minforce = minf;
    maxforce = maxf;
    bodyid = WORLD;
    id = (int)CreateSpring(b1,b2,x1,y1,x2,y2,len,len*2,minforce,maxforce);
  }

  ~Spring() {
    DestroySpring(id);
  }

  void setColor(float red, float green, float blue, float alpha) {
    _r = red; _g = green; _b = blue; _a = alpha;
  }

  float getColR() { return(_r); }
  float getColG() { return(_g); }
  float getColB() { return(_b); }

  void Draw() {
    float xpos,ypos;
    float width,height;
    if (b1!=-1) { if (GetBodyMass(b1)!=STATIC) { x1=GetSpringX(id,0); y1=GetSpringY(id,0); }}
    if (b2!=-1) { if (GetBodyMass(b2)!=STATIC) { x2=GetSpringX(id,1); y2=GetSpringY(id,1); }}
    xpos = (x1+x2)/2;
    ypos = (y1+y2)/2;
    if (bodyid!=WORLD) {
      SetBodyX(bodyid,xpos);
      SetBodyY(bodyid,ypos);
    }
    width = x2-x1;
    height = y2-y1;
    glColor4f(_r,_g,_b,_a);
    DrawCircle(x1,y1,4,0);
    DrawCircle(x2,y2,4,0);
    DrawLine(xpos-width/2,ypos-height/2,xpos+width/2,ypos+height/2);
  }
};

#endif
