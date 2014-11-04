#include "glGUIInclude.h"

GUIWindow::GUIWindow(float xpos, float ypos, float w, float h) {
    Font = new GUIFont("Tahoma",30);
    x = xpos; y = ypos; width = w; height = h;
}

void GUIWindow::AddControl(GUIControl* control) {
    controls.push_back(control);
    controls[controls.size()-1]->parent = this;
}

void GUIWindow::Update(int cx, int cy) {
    if (!visible) return;

    if (parent==NULL) {
        nx = x;
        ny = y;
    } else {
        nx = x+parent->x;
        ny = y+parent->y;
    }

    for (int i=0;i<controls.size();i++) {
        controls[i]->Update(cx,cy);
    }

    if (GetAsyncKeyState(VK_LBUTTON)) {
        if (!drag) {
            if (cx > nx && cx < nx+width && cy > ny-26 && cy < ny) drag = 1;
            doffsetx = x-cx;
            doffsety = y-cy;
        } else {
            x = doffsetx+cx;
            y = doffsety+cy;
        }
    } else {
        if (drag) drag = 0;
    }
}

void GUIWindow::Draw() {
    if (!visible) return;

    GUIDrawRectangle(nx,ny-26,nx+width,ny+height,0,0,0,.8,0);
    GUIDrawRectangle(nx-border,ny-26-border,nx+width+border,ny+height+border,0,0,0,.8,0);

    GUIDrawRectangle(nx,ny-26,nx+width,ny,0,0,0,1,0);
    GUIDrawRectangle(nx,ny-26,nx+width,ny-13,1,1,1,.5,0);

    GUIDrawRectangle(nx,ny-26,nx+width,ny+height,1.0,1.0,1.0,1,1);
    GUIDrawRectangle(nx-border,ny-26-border,nx+width+border,ny+height+border,1.0,1.0,1.0,1,1);
    GUIDrawLine(nx,ny,nx+width,ny,1,1,1,1);

    Font->Print(nx+width/2,ny-34,FA_CENTER,caption.c_str());

    for (int i=0;i<controls.size();i++) {
        controls[i]->Draw();
    }
}
