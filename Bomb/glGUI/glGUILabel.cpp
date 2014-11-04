#include "glGUIInclude.h"

GUILabel::GUILabel(float xpos, float ypos, float w, float h) {
    Font = new GUIFont("Tahoma",24);
    x = xpos; y = ypos; width = w; height = h;
    visible = 1;
    align = FA_LEFT;
}

void GUILabel::SetCaption(std::string newcaption) {
    int len = newcaption.size();

    int spaceprev = 0;
    int space = 0;
    int newline = 0;

    //WORD WRAP
    for (int i=0;i<len;i++) {
        if (iswspace(newcaption[i])) {
            space = i;
            spaceprev = space;
            if (Font->GetPrintWidth(newcaption.substr(newline,space-newline).c_str()) > width) {
                newcaption.erase(spaceprev,1);
                newcaption.insert(spaceprev,"\n");
                newline = spaceprev+1;
                i++;
            }
        }
    }

    caption = newcaption;
}

void GUILabel::Update(int cx, int cy) {
    if (parent==NULL) {
        nx = x;
        ny = y;
    } else {
        nx = x+parent->x;
        ny = y+parent->y;
    }
}

void GUILabel::Draw() {
    if (!visible) return;

    if (align==FA_LEFT) Font->Print(nx,ny,align,caption.c_str());
    if (align==FA_CENTER) Font->Print(nx+width/2,ny,align,caption.c_str());
    if (align==FA_RIGHT) Font->Print(nx+width,ny,align,caption.c_str());
}
