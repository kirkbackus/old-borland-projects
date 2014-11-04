#ifndef __DYNAMIC_OBJ_H
#define __DYNAMIC_OBJ_H

class Dynamic {
  private:

  float x,y,width,height,radius,type,rot;
  bool txt;

  public:

  int id;

  Dynamic(double xpos, double ypos, double density, double shape, double arg1) {
    id = (int)g.CreateBody(xpos,ypos,density,shape,arg1,0,0);
    type=shape;
    if (shape==SHAPE_SPHERE) {
      width=arg1;
    }
  }

  Dynamic(double xpos, double ypos, double density, double shape, double arg1, double arg2) {
    if (shape!=SHAPE_LINE)
    id = (int)g.CreateBody(xpos,ypos,density,shape,arg1,arg2,0);
    type=shape;
    if (shape==SHAPE_BOX) {
      width=arg1;
      height=arg2;
    }
    if (shape==SHAPE_LINE) {
      width = arg1-xpos;
      height = arg2-ypos;
      id = CreateLine(xpos,ypos,arg1,arg2);
    }
  }

  Dynamic(double xpos, double ypos, double density, double shape, double arg1, double arg2, double arg3) {
    id = (int)g.CreateBody(xpos,ypos,density,shape,arg1,arg2,arg3);
    type=shape;
  }

  ~Dynamic() {
    DestroyBody(id);
  }

  void UseTexture(bool _use_texture) {
    txt = _use_texture;
  }

  double getWidth() {
    return(width);
  }

  double getHeight() {
    return(height);
  }

  double getX() {
    return(GetBodyX(id));
  }

  double getY() {
    return(GetBodyY(id));
  }

  double getRot() {
    return(GetBodyRotation(id));
  }

  void Draw() {
    x=GetBodyX(id);
    y=GetBodyY(id);
    rot=GetBodyRotation(id);
    if(type==SHAPE_BOX) {
      DrawBox(x,y,width,height,rot);
    } else if (type==SHAPE_TRIMESH || type==SHAPE_CONVEX) {
      DrawBox(x,y,128,64,rot);
    } else if (type==SHAPE_SPHERE) {
      if (txt) DrawBox(x,y,2*width,2*width,rot);
      else DrawCircle(x,y,width,rot);
    } else if (type==SHAPE_LINE) {
      DrawLine(x-width/2,y-height/2,x+width/2,y+height/2);
    }
  }

  void DrawQuad(float size, float r, float g, float b) {
    Draw();
    glPushMatrix ();

    glTranslatef(x,y,0);

    glBegin(GL_TRIANGLES);

    float val=(float)(rand()%4)/20.0;

    glColor4f(r+val,g+val,b+val,1.0f);
    glVertex2f(-width/2,-height/2-8);
    glVertex2f(+width/2,+height/2-8);
    glColor4f(1.0f,1.0f,1.0f,0.0f);
    glVertex2f(+width/2,+height/2-8+size);

    glColor4f(r+val,g+val,b+val,1.0f);
    glVertex2f(-width/2,-height/2-8);
    glColor4f(1.0f,1.0f,1.0f,0.0f);
    glVertex2f(-width/2,-height/2-8+size);
    glVertex2f(+width/2,+height/2-8+size);
    glColor4f(1.0f,1.0f,1.0f,1.0f);

    glEnd();
    
    glPopMatrix();
    Draw();
  }
};

#endif