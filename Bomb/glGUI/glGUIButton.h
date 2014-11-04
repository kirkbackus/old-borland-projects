class GUIButton : public GUIControl {
    private:

    int state;
    bool clicked;

    public:

    GUIButton(float xpos, float ypos, float w, float h);

    bool Clicked();
    void Update(int cx, int cy);
    void Draw();
};
