class GUIControl {
    public:

    float x,y,width,height;
    float nx,ny;
    std::string caption;

    bool visible;
    bool enabled;

    void* OnClick();
    void* OnClose();
    void* OnPaint();

    GUIControl();
    ~GUIControl();

    GUIControl* parent;
    GUIFont* Font;

    virtual void Update(int cx, int cy);
    virtual void Draw();
};
