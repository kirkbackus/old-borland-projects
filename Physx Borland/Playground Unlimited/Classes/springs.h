#ifndef __DYNAMIC_SPRINGS_H
#define __DYNAMIC_SPRINGS_H

class Spring {
  private:

  float _r, _g, _b, _a;

  public:

  int id;
  int b1,b2;
  float x1,y1,x2,y2;
  float len;

  Spring(double body1, double body2) {
    b1 = body1; b2 = body2;
    x1 = GetBodyX(b1); y1 = GetBodyY(b1);
    x2 = GetBodyX(b2); y2 = GetBodyY(b2);
    len = PointDistance(x1,y1,x2,y2);
    id = (int)CreateSpring(b1,b2,x1,y1,x2,y2,len,len*2,100,500);
  }

  Spring(double body1, double body2, double length) {
    b1 = body1; b2 = body2;
    x1 = GetBodyX(b1); y1 = GetBodyY(b1);
    x2 = GetBodyX(b2); y2 = GetBodyY(b2);
    len = length;
    id = (int)CreateSpring(b1,b2,x1,y1,x2,y2,len,len*2,100,500);
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
    if (b1==WORLD || b2==WORLD) return;
    float x1,x2,y1,y2,xpos,ypos;
    float width,height;
    x1=GetBodyX(b1); y1=GetBodyY(b1);
    x2=GetBodyX(b2); y2=GetBodyY(b2);
    xpos = (x1+x2)/2;
    ypos = (y1+y2)/2;
    width = x2-x1;
    height = y2-y1;
    glColor4f(_r,_g,_b,_a);
    DrawCircle(x1,y1,4,0);
    DrawCircle(x2,y2,4,0);
    DrawLine(xpos-width/2,ypos-height/2,xpos+width/2,ypos+height/2);
  }
};

#endif
