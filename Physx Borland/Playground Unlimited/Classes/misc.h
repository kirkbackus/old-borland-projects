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

#endif