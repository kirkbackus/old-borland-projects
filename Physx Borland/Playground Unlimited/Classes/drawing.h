inline void DrawRect(float x, float y, float width, float height, float rot) {
  glPushMatrix ();

  glTranslatef(x,y,0);
  glRotatef(-rot,0.0,0.0,1.0);

  glBegin(GL_QUADS);

  glTexCoord2f(0.0f,1.0f); glVertex2f(0.0f,0.0f);
  glTexCoord2f(1.0f,1.0f); glVertex2f(width,0.0f);
  glTexCoord2f(1.0f,0.0f); glVertex2f(width,height);
  glTexCoord2f(0.0f,0.0f); glVertex2f(0.0f,height);

  glEnd();

  glPopMatrix();
}

void DrawRectOut(float x, float y, float width, float height, float rot) {
  glPushMatrix ();

  glTranslatef(x,y,0);
  glRotatef(-rot,0.0,0.0,1.0);

  glBegin(GL_LINES);

  glVertex2f(0.0f,0.0f); glVertex2f(width,0.0f);
  glVertex2f(width,0.0f); glVertex2f(width,height);
  glVertex2f(width,height); glVertex2f(0.0f,height);
  glVertex2f(0.0f,height); glVertex2f(0.0f,0.0f);

  glEnd();

  glPopMatrix();
}

void DrawBox(float x, float y, float width, float height, float rot) {
  glPushMatrix ();

  glTranslatef(x,y,0);
  glRotatef(-rot,0.0,0.0,1.0);

  glBegin(GL_QUADS);

  glTexCoord2f(0,1); glVertex2f(-width/2,-height/2);
  glTexCoord2f(1,1); glVertex2f(+width/2,-height/2);
  glTexCoord2f(1,0); glVertex2f(+width/2,+height/2);
  glTexCoord2f(0,0); glVertex2f(-width/2,+height/2);

  glEnd();

  glPopMatrix();
}

void DrawBoxOut(float x, float y, float width, float height, float rot) {
  glPushMatrix ();

  glTranslatef(x,y,0);
  glRotatef(-rot,0.0,0.0,1.0);

  glBegin(GL_LINES);

  glVertex2f(-width/2,+height/2); glVertex2f(-width/2,-height/2);
  glVertex2f(-width/2,-height/2); glVertex2f(+width/2,-height/2);
  glVertex2f(+width/2,-height/2); glVertex2f(+width/2,+height/2);
  glVertex2f(+width/2,+height/2); glVertex2f(-width/2,+height/2);

  glEnd();

  glPopMatrix();
}

void DrawTriangle(float x, float y, float width, float height, float r) {
  glPushMatrix();

  glTranslatef(x,y,0);
  glRotatef(-r,0.0,0.0,1.0);

  glBegin(GL_TRIANGLE_FAN);

  glVertex2f(-width/2,height/2);
  glVertex2f(0,-height/2);
  glVertex2f(width/2,height/2);

  glEnd();

  glPopMatrix();
}

inline void DrawTriangleOut(float x, float y, float width, float height, float r) {
  glPushMatrix();

  glTranslatef(x,y,0);
  glRotatef(-r,0.0,0.0,1.0);

  glBegin(GL_LINE_LOOP);

  glVertex2f(-width/2,height/2);
  glVertex2f(0,-height/2);
  glVertex2f(width/2,height/2);

  glEnd();

  glPopMatrix();
}


void DrawCircle(float x, float y, float radius, float rot) {
  glPushMatrix();

  int detail = 18;
  if (radius<5) detail = 45;

  glTranslatef(x,y,0);
  glRotatef(-rot,0,0,1);

  glBegin(GL_TRIANGLE_FAN);

  for (int i=0; i<=360; i+=detail)
     glVertex2f(cos(i*(pi/180))*radius,sin(i*(pi/180))*radius);

  glEnd();

  glPopMatrix();
}

void DrawCapsule(float x, float y, float radius, float height, float rot) {
  glPushMatrix();

  radius = fabs(radius);
  height = fabs(height);

  int detail = 18;
  if (radius<5) detail = 45;

  glTranslatef(x,y,0);
  glRotatef(-rot,0,0,1);

  glBegin(GL_TRIANGLE_FAN);

  for (int i=0; i<=180; i+=detail)
     glVertex2f(cos(i*(pi/180))*radius,sin(i*(pi/180))*radius+height/2);
  for (int i=180; i<=360; i+=detail)
     glVertex2f(cos(i*(pi/180))*radius,sin(i*(pi/180))*radius-height/2);

  glEnd();

  glPopMatrix();
}

void DrawCapsuleOut(float x, float y, float radius, float height, float rot) {
  glPushMatrix();

  radius = fabs(radius);
  height = fabs(height);

  int detail = 18;
  if (radius<5) detail = 45;

  glTranslatef(x,y,0);
  glRotatef(-rot,0,0,1);

  glBegin(GL_LINE_LOOP);

  for (int i=0; i<=180; i+=detail)
     glVertex2f(cos(i*(pi/180))*radius,sin(i*(pi/180))*radius+height/2);
  for (int i=180; i<=360; i+=detail)
     glVertex2f(cos(i*(pi/180))*radius,sin(i*(pi/180))*radius-height/2);

  glEnd();

  glPopMatrix();
}

void DrawCircleOut(float x, float y, float radius, float rot) {
  glPushMatrix();

  int detail = 18;
  if (radius<5) detail = 90;

  glTranslatef(x,y,0);
  glRotatef(-rot,0,0,1);

  glBegin(GL_LINE_LOOP);

  for (int i=0; i<=360; i+=detail)
     glVertex2f(cos(i*(pi/180))*radius,sin(i*(pi/180))*radius);

  glEnd();

  glPopMatrix();
}

inline void DrawLine(float x1, float y1, float x2, float y2) {
  glPushMatrix ();
  glBegin(GL_LINES);

  glVertex2f(x1,y1);
  glVertex2f(x2,y2);

  glEnd();
  glPopMatrix();
}