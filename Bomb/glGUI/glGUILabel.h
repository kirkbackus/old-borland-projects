class GUILabel : public GUIControl {
    private:

    public:

    int align;

    GUILabel(float xpos, float ypos, float w, float h);

    void SetCaption(std::string newcaption);
    void Update(int cx, int cy);
    void Draw();
};
