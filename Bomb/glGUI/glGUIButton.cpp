#include "glGUIInclude.h"

GUIButton::GUIButton(float xpos, float ypos, float w, float h) {
    Font = new GUIFont("Tahoma",30);
    x = xpos; y = ypos; width = w; height = h;
    visible = 1;
    clicked = 0;
}

bool GUIButton::Clicked() {
    if (clicked) {
        clicked = 0;
        return (1);
    }
}

void GUIButton::Update(int cx, int cy) {
    if (parent==NULL) {
        nx = x;
        ny = y;
    } else {
        nx = x+parent->x;
        ny = y+parent->y;
    }

    if (cx >= nx && cy >= ny && cx <= nx+width && cy <= ny+height) {
        if (GetAsyncKeyState(VK_LBUTTON)) state = 2;
        else if (state == 2) {
            clicked = 1;
            state = 1;
        } else state = 1;
    } else state = 0;
}

void GUIButton::Draw() {
    if (!visible) return;

    if (state==0) GUIDrawRectangle(nx,ny,nx+width,ny+height,0,0,0,.8,0);
    if (state==1) GUIDrawRectangle(nx,ny,nx+width,ny+height,.25,.25,.3,.8,0);
    if (state==2) GUIDrawRectangle(nx,ny,nx+width,ny+height,0,0,0,1,0);

    GUIDrawRectangle(nx,ny,nx+width,ny+height/2,1,1,1,.5,0);
    if (state==2) GUIDrawRectangle(nx,ny,nx+width,ny+height/2,0,0,0,.5,0);
    GUIDrawRectangle(nx,ny,nx+width,ny+height,1,1,1,1,1);

    Font->Print(nx+width/2,ny-height/5,FA_CENTER,caption.c_str());
}
