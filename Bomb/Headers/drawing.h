#ifndef __DRAWING_H
#define __DRAWING_H

#include "fonts.h"

/******************
 * Draw Polygon
 *
 ******************/

bool keydown[255];
bool keydownp[255];

bool KeyPressed(int vKey) {
    return(keydown[vKey]);
}

bool KeyReleased(int vKey) {
    return(!keydown[vKey]);
}

bool KeyJustPressed(int vKey) {
    return(keydown[vKey] && !keydownp[vKey]);
}

bool KeyJustReleased(int vKey) {
    return(!keydown[vKey] && keydownp[vKey]);
}

int Choose(int a, int b) {
    return(rand()%2==1 ? a : b);
}

void UpdateKeys() {
    for (int i=0;i<255;i++) {
        keydownp[i]=keydown[i];
        keydown[i]=GetAsyncKeyState(i);
    }
}

void DrawPolygon(Blackbox::Polygon* p, float r, float g, float b, float a, bool outline) {
    glPushMatrix();

    glBegin (outline==1 ? GL_LINE_LOOP:GL_TRIANGLE_FAN);
    glColor4f(r,g,b,a);
    for (int i=0;i<p->NumPoints();i++) {
        glVertex2f (p->GetAPointX(i), p->GetAPointY(i));
    }
    glEnd();

    glPopMatrix();
}

void DrawRectangle(float x1, float y1, float x2, float y2, float r, float g, float b, float a, bool outline) {
    glBegin (outline==1 ? GL_LINE_LOOP:GL_TRIANGLE_FAN);

    glColor4f(r,g,b,a);

    glVertex2f (x1,y1);
    glVertex2f (x2,y1);
    glVertex2f (x2,y2);
    glVertex2f (x1,y2);

    glEnd();
}

void DrawCircle(float x, float y, float rad, float detail, float r, float g, float b, float a, bool outline) {
    glBegin (outline==1 ? GL_LINE_LOOP:GL_TRIANGLE_FAN);

    glColor4f(r,g,b,a);

    for (float i=0;i<360.0;i+=360.0/detail) {
        glVertex2f (cos(PI/180*i)*rad,sin(PI/180*i)*rad);
    }

    glEnd();
}

void DrawLine(float x1, float y1, float x2, float y2, float r, float g, float b, float a) {
    glBegin (GL_LINES);

    glColor4f(r,g,b,a);

    glVertex2f (x1,y1);
    glVertex2f (x2,y2);

    glEnd();
}

#endif
