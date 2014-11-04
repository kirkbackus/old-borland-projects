#ifndef __MISCFUNC
#define __MISCFUNC

/**************************
 * Misc. Functions
 *
 **************************/
float PointDirection(float x1, float y1, float x2, float y2) {
  if (fabs(x1-x2) != 0)
  {
    if (x1 < x2)
      return(180+(180/pi)*atan(((y1-y2)/fabs(x1-x2))));
    else {
      if (y1 <= y2)
        return(-(180/pi)*atan(((y1-y2)/fabs(x1-x2))));
      else
        return(360-(180/pi)*atan(((y1-y2)/fabs(x1-x2))));
   }
 } else {
    if (y1 > y2)
      return (270);
    else
      return (90);
  }
}

double CreateLine(int x1, int y1, int x2, int y2) {
  float len=sqrt(pow((x2-x1),2)+pow((y2-y1),2));
  float dir=PointDirection(x1,y1,x2,y2);
  SetLineSize(1);
  return(g.CreateBody((x2+x1)/2.0,(y2+y1)/2.0,STATIC,SHAPE_LINE,len,dir,0));
}

inline float PointDistance(float x1, float y1, float x2, float y2) {
  return(sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1)));
}

inline float LengthDirX(float len, float dir) {
  return(len*cos(dir*pi/180.0));
}

inline float LengthDirY(float len, float dir) {
  return(len*sin(dir*pi/180.0));
}

inline bool PointRectCollide(POINT p, RECT r) {
  if (p.x>=r.left && p.x<=r.right && p.y>=r.top && p.y<=r.bottom) return 1;
  return 0;
}

inline bool PointBoxCollide(POINT p, RECT r, float dir) {
  float tdst = PointDistance(p.x,p.y,r.left,r.top);
  float tdir = PointDirection(r.left,r.top,p.x,p.y);
  tdir-=dir;
  p.x = r.left-LengthDirX(tdst,tdir);
  p.y = r.top+LengthDirY(tdst,tdir);
  r.left -= r.right/2;
  r.top -= r.bottom/2;
  r.right += r.left;
  r.bottom += r.top;
  return(PointRectCollide(p,r));
}

inline bool PointCircleCollide(POINT p, POINT c, float r) {
  if (sqrt((p.x-c.x)*(p.x-c.x)+(p.y-c.y)*(p.y-c.y))<=r) return 1;
  else return 0;
}

inline float TriArea2D(POINT a, POINT b, POINT c) {
  return (fabs(a.x*b.y+b.x*c.y+c.x*a.y-a.x*c.y-c.x*b.y-b.x*a.y)/2);
}

inline bool PointTriangleCollide(POINT p, POINT a, POINT b, POINT c) {
  if (TriArea2D(p,b,c)+TriArea2D(a,p,c)+TriArea2D(a,b,p)==TriArea2D(a,b,c))return 1;
  else return 0;
}


#endif