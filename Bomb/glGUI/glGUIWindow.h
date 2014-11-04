class GUIWindow : public GUIControl {
    private:

    bool drag;
    float doffsetx,doffsety;
    static const int border = 4;

    std::vector<GUIControl*> controls;

    public:

    GUIWindow(float xpos, float ypos, float w, float h);

    void Update(int cx, int cy);
    void AddControl(GUIControl* control);
    void Draw();
};
