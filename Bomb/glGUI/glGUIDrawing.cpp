#include "glGUIInclude.h"

void GUIDrawRectangle(float x1, float y1, float x2, float y2, float r, float g, float b, float a, bool outline) {
    glBegin (outline==1 ? GL_LINE_LOOP:GL_TRIANGLE_FAN);

    glColor4f(r,g,b,a);

    glVertex2f (x1,y1);
    glVertex2f (x2,y1);
    glVertex2f (x2,y2);
    glVertex2f (x1,y2);

    glEnd();
}

void GUIDrawCircle(float x, float y, float rad, float detail, float r, float g, float b, float a, bool outline) {
    glBegin (outline==1 ? GL_LINE_LOOP:GL_TRIANGLE_FAN);

    glColor4f(r,g,b,a);

    for (float i=0;i<360.0;i+=360.0/detail) {
        glVertex2f (cos(PI/180*i)*rad,sin(PI/180*i)*rad);
    }

    glEnd();
}

void GUIDrawLine(float x1, float y1, float x2, float y2, float r, float g, float b, float a) {
    glBegin (GL_LINES);

    glColor4f(r,g,b,a);

    glVertex2f (x1,y1);
    glVertex2f (x2,y2);

    glEnd();
}


GUIFont::~GUIFont() {
    glDeleteLists(base, 192);
}

GUIFont::GUIFont(const char* font_name, int font_size) {
    BuildFont(font_name,font_size);
}

void GUIFont::BuildFont(const char* name, int size) {
	HFONT font;
    _size = size;

	base = glGenLists(192);	// Storage for 192 characters

	font = CreateFont(-size, 0, 0, 0, FW_BOLD, false, false, true, ANSI_CHARSET, OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE|DEFAULT_PITCH,name);

	HDC tmp = CreateDC(TEXT("DISPLAY"),NULL,NULL,NULL);
	SelectObject(tmp, font);
	wglUseFontOutlines(tmp, 0, 191, base,0.0f, 0.0f, WGL_FONT_POLYGONS, gmf);
	DeleteDC(tmp);
}

void GUIFont::glDrawText(float x, float y, float size, float align, const char *str) {
    float width = 0;

    for (unsigned int i=0;i<strlen(str);i++) {
        width+=gmf[str[i]].gmfCellIncX;
    }

    width*=size;

    glPushMatrix();

    glPushAttrib(GL_LIST_BIT);				// Pushes the display list bits
    glListBase(base);					// Sets the base character to 0

    glTranslatef(x-width*align,y+size,0.0f);
    glScalef(size,-size,size);

    glCallLists(strlen(str), GL_UNSIGNED_BYTE, str);	// Draws the display list text

    glPopMatrix();
}

void GUIFont::Print(float x, float y, float align,  const char *fmt, ...) {
    align/=2;
    float height = 0;
    float yoffset = 0;
    char text[256];		// Holds our string
    va_list ap;			// Pointer to list of arguments

    if (fmt == NULL) return;

    va_start(ap, fmt);		// Parses the string for variables
        vsprintf(text, fmt, ap);    // And converts symbols to actual numbers
    va_end(ap);			// Results are stored in text

    std::string print = text;

    while(1) {
        int npos = print.find_first_of("\n",0);
        if (npos==-1) {
            glDrawText(x,y+yoffset,_size,align,print.c_str());
            break;
        } else {
            glDrawText(x,y+yoffset,_size,align,print.substr(0,npos).c_str());
            yoffset+=24;
            print = print.erase(0,npos+1);
        }
    }

    glPopAttrib();					// Pops the display list bits

    glPopMatrix();
}

void GUIFont::PrintRot(float x, float y, float align, float rot,  const char *fmt, ...) {
    align/=2;
    float length = 0;		// Used to find the length of the text
    char text[256];			// Holds our string
    va_list ap;			// Pointer to list of arguments

    if (fmt == NULL) return;			// Do nothing

    va_start(ap, fmt);		// Parses the string for variables
        vsprintf(text, fmt, ap);    // And converts symbols to actual numbers
    va_end(ap);			// Results are stored in text

    for (unsigned int loop=0;loop<(strlen(text));loop++) {
        length+=gmf[text[loop]].gmfCellIncX;		// Increase length by each characters width
    }

    length*=_size;
    glPushMatrix();

    glTranslatef(x-length*align,y+_size,0.0f);		// Translate &
    glRotatef(rot,0,0,1);
    glScalef(_size,-_size,_size);                           // Scale


    glPushAttrib(GL_LIST_BIT);			// Pushes the display list bits
    glListBase(base);					// Sets the base character to 0
    glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws the display list text
    glPopAttrib();						// Pops the display list bits

    glPopMatrix();
}

float GUIFont::GetPrintWidth(const char *fmt, ...) {
    float length = 0;	// Used to find the length of the text
    char text[256];		// Holds our string
    va_list ap;			// Pointer to list of arguments

    va_start(ap, fmt);		// Parses the string for variables
        vsprintf(text, fmt, ap);    // And converts symbols to actual numbers
    va_end(ap);			// Results are stored in text

    for (unsigned int loop=0;loop<(strlen(text));loop++) {
        length+=gmf[text[loop]].gmfCellIncX;		// Increase length by each characters width
    }

    length*=_size;

    return (length);

    return 1;
}

float GUIFont::GetPrintHeight(const char *fmt, ...) {
    float length = 0;	// Used to find the length of the text
    char text[256];		// Holds our string
    va_list ap;			// Pointer to list of arguments

    va_start(ap, fmt);		// Parses the string for variables
        vsprintf(text, fmt, ap);    // And converts symbols to actual numbers
    va_end(ap);			// Results are stored in text

    for (unsigned int loop=0;loop<(strlen(text));loop++) {
        if (length < gmf[text[loop]].gmfCellIncY) length = gmf[text[loop]].gmfCellIncY;
    }

    length*=_size;

    return (length);

    return 1;
}
