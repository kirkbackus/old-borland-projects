class GUITextBox : public GUIControl {
    private:

    char text[255];

    int state;
    bool active;

    int maxlength;
    int type;

    public:

    GUITextBox(float xpos, float ypos, float w, float h);

    char* GetText();
    void SetType(int newtype);
    void Update(int cx, int cy);
    void Draw();
};
