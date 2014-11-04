void GUIDrawRectangle(float x1, float y1, float x2, float y2, float r, float g, float b, float a, bool outline);
void GUIDrawCircle(float x, float y, float rad, float detail, float r, float g, float b, float a, bool outline);
void GUIDrawLine(float x1, float y1, float x2, float y2, float r, float g, float b, float a);

#define FA_LEFT 0
#define FA_CENTER 1
#define FA_RIGHT 2

class GUIFont {
    private:

    GLuint base;
    GLYPHMETRICSFLOAT gmf[192];
    int _size;

    void glDrawText(float x, float y, float size, float align, const char *str);

    void BuildFont(const char* name, int size);

    public:

    GUIFont(const char* font_name, int font_size);
    ~GUIFont();

    float GetPrintWidth(const char* fmt, ...);
    float GetPrintHeight(const char* fmt, ...);

    void Print(float x, float y, float align,  const char *fmt, ...);
    void PrintRot(float x, float y, float align, float rot,  const char *fmt, ...);
};
