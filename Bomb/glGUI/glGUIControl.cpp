#include "glGUIInclude.h"

GUIControl::GUIControl() {
    visible = 1;
}

GUIControl::~GUIControl() {
    delete Font;
}

void GUIControl::Update(int cx, int cy) {
    //THIS METHOD SHOULD BE OVERRIDEN
}

void GUIControl::Draw() {
    //THIS METHOD SHOULD BE OVERRIDEN
}
