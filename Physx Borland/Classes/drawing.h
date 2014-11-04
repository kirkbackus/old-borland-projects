void DrawRect(float x, float y, float width, float height, float rot) {
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

void DrawCircle(float x, float y, float radius, float rot) {
  glPushMatrix();

  glTranslatef(x,y,0);

  glBegin(GL_TRIANGLE_FAN);

  for (int i=0; i<=360; i++)
     glVertex2f(cos(i*(pi/180))*radius,sin(i*(pi/180))*radius);

  glEnd();

  glPopMatrix();
}

void DrawCircleOut(float x, float y, float radius, float rot) {
  glPushMatrix();

  glTranslatef(x,y,0);

  glBegin(GL_LINE_LOOP);

  for (int i=0; i<=360; i++)
     glVertex2f(cos(i*(pi/180))*radius,sin(i*(pi/180))*radius);

  glEnd();

  glPopMatrix();
}

void DrawLine(float x1, float y1, float x2, float y2) {
  glPushMatrix ();
  glBegin(GL_LINES);

  glVertex2f(x1,y1-8);
  glVertex2f(x2,y2-8);

  glEnd();
  glPopMatrix();
}