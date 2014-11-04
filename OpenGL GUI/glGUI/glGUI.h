#ifndef _OGL_GUI_H_
#define _OGL_GUI_H_

class GUIControl {
    public:

    GUIControl();

    int x,y,width,height;
    std::string caption;
};

class GUIWindow : public GUIControl {
};

#endif
