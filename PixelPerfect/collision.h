#ifndef COLLISION_H
#define COLLISION_H

int MIN (int x, int y) {
  if (x <= y) return x;
  else return y;
}

int MAX (int x, int y) {
  if (x >= y) return x;
  else return y;
}


const float pi = 3.141592653;

class CollisionEngine {
  public:
    bool RectCollide(TControl *Object1,TControl *Object2);
    bool CircleCollide(TControl *Object1,TControl *Object2);
    bool PixelCollide(TImage *Object1,TImage *Object2);
};

bool CollisionEngine::RectCollide(TControl *Object1, TControl *Object2) {
  if (Object1->Left+Object1->Width>Object2->Left &&
      Object1->Top+Object1->Height>Object2->Top &&
      Object1->Left<Object2->Left+Object2->Width &&
      Object1->Top<Object2->Top+Object2->Height)
    return true;
    else
    return false;
}

bool CollisionEngine::CircleCollide(TControl *Object1,TControl *Object2) {
  float xx1,yy1,xx2,yy2,dist1,dist2;

  xx1 = Object1->Left+Object1->Width/2;
  yy1 = Object1->Top+Object1->Height/2;
  xx2 = Object2->Left+Object2->Width/2;
  yy2 = Object2->Top+Object2->Height/2;

  dist1 = sqrt((xx2-xx1)*(xx2-xx1)+(yy2-yy1)*(yy2-yy1));
  dist2 = Object1->Width/2+Object2->Width/2;

  if (dist1<=dist2) return 1;
  else return 0;
}

bool CollisionEngine::PixelCollide(TImage *Object1,TImage *Object2) {
  //If Collided with bounding box
  if (Object1->Left+Object1->Width>Object2->Left &&
  Object1->Top+Object1->Height>Object2->Top &&
  Object1->Left<Object2->Left+Object2->Width &&
  Object1->Top<Object2->Top+Object2->Height) {
    COLORREF trans1,trans2;
    trans1 = Object1->Canvas->Pixels[0][Object1->Picture->Height-1]; //Get Transparent Color
    trans2 = Object2->Canvas->Pixels[0][Object2->Picture->Height-1]; //Get Transparent Color
    if (!Object1->Transparent)trans1=-1; //Cancel Transparent Color if Not
    if (!Object2->Transparent)trans2=-1; //Cancel Transparent Color if Not

    int xx,yy,mx,my,w,h,width,height,mw,mh,ww,hh;
    mx = MIN(Object1->Left,Object2->Left);     //Min X-value
    my = MIN(Object1->Top,Object2->Top);       //Min Y-value
    xx = MAX(Object1->Left,Object2->Left);     //Max X-value
    yy = MAX(Object1->Top,Object2->Top);       //Max Y-value

    int x1,y1,lw,lh;

    //Set X and Y value
    x1 = xx-mx;
    y1 = yy-my;

    //Get Width and height
    if (mx == Object1->Left) width = Object1->Width-x1;
    if (mx == Object2->Left) width = Object2->Width-x1;
    if (my == Object1->Top) height = Object1->Height-y1;
    if (my == Object2->Top) height = Object2->Height-y1;

    //Limit width if not as large
    if (xx==Object1->Left)if (Object1->Left+Object1->Width<Object2->Left+Object2->Width)
    width=Object1->Width;
    if (xx==Object2->Left)if (Object2->Left+Object2->Width<Object1->Left+Object1->Width)
    width=Object2->Width;
    if (yy==Object1->Left)if (Object1->Top+Object1->Height<Object2->Top+Object2->Height)
    height=Object1->Height;
    if (yy==Object2->Left)if (Object2->Top+Object2->Height<Object1->Top+Object1->Height)
    height=Object2->Height;

    int xoff1,xoff2,yoff1,yoff2;
    if (Object1->Left==mx)xoff1=xx-mx;
    else xoff1=0;
    if (Object2->Left==mx)xoff2=xx-mx;
    else xoff2=0;
    if (Object1->Top==my)yoff1=yy-my;
    else yoff1=0;
    if (Object2->Top==my)yoff2=yy-my;
    else yoff2=0;

    COLORREF check1,check2;

    //Actually Check for the collision
    for(int i=0;i<width;i++) for(int ii=0;ii<height;ii++) {
      check1 = Object1->Canvas->Pixels[i+xoff1][ii+yoff1];
      check2 = Object2->Canvas->Pixels[i+xoff2][ii+yoff2];
      if (check1!=trans1 && check1!=-1 && check2!=trans2 && check2!=-1)
      return 1;
    }
    
    return 0;
  } else return 0;

}

#endif
