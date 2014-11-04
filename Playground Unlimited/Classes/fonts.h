#ifndef __CLASSES
#define __CLASSES

#define FA_LEFT 0
#define FA_CENTER 1
#define FA_RIGHT 2

class glFont {
  private:

  GLuint base;
  GLYPHMETRICSFLOAT gmf[192];
  int _size;

  void BuildFont(HDC dc, const char* name, int size)	// Build Our Bitmap Font
  {
	HFONT font;		// Windows font ID
        _size = size;           // For scaling

	base = glGenLists(192);	// Storage for 256 characters

	font = CreateFont(-size,	                // Height of font
			  0,				// Width of font
			  0,				// Angle of escapement
			  0,				// Orientation angle
			  FW_HEAVY,			// Font weight
			  false,			// Italic
			  false,			// Underline
			  true,				// Strikeout
			  ANSI_CHARSET,			// Character set identifier
			  OUT_RASTER_PRECIS,		// Output precision
			  CLIP_DEFAULT_PRECIS,		// Clipping precision
			  ANTIALIASED_QUALITY,		// Output quality
			  FF_MODERN|DEFAULT_PITCH,	// Family and pitch
			  name);          		// Font name

	SelectObject(dc, font);			        // Selects the font we created

	wglUseFontOutlines(dc,				// Select the current DC
			   0,	                        // Starting character
			   191,				// Number of display lists to build
			   base,			// Starting display lists
			   0.0f,			// Deviation from the true outlines
			   0.0f,			// Font thickness in the Z direction
			   WGL_FONT_POLYGONS,		// Use polygons, not lines
			   gmf);			// Address of buffer to recieve data
        }

  public:

  glFont(HDC dc, const char* font_name, int font_size) {
    BuildFont(dc,font_name,font_size);
  }

  ~glFont() {
    glDeleteLists(base, 192);  // Delete all 192 characters
  }

  void glPrint(float x, float y, float align,  const char *fmt, ...);
  void glPrintRot(float x, float y, float align, float rot,  const char *fmt, ...);
};

void glFont::glPrint(float x, float y, float align,  const char *fmt, ...) {
  align/=2;
  float length = 0;		// Used to find the length of the text
  char text[256];		// Holds our string
  va_list ap;			// Pointer to list of arguments

  if (fmt == NULL)		// If there's no text
    return;			// Do nothing

  va_start(ap, fmt);		// Parses the string for variables
    vsprintf(text, fmt, ap);    // And converts symbols to actual numbers
  va_end(ap);			// Results are stored in text

  for (unsigned int loop=0;loop<(strlen(text));loop++)	{
    length+=gmf[text[loop]].gmfCellIncX;		// Increase length by each characters width
  }

  length*=_size;
  glPushMatrix();

  glTranslatef(x-length*align,y+_size,0.0f);		// Draw
  glScalef(_size,-_size,_size);

  glPushAttrib(GL_LIST_BIT);				// Pushes the display list bits
  glListBase(base);					// Sets the base character to 0
  glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws the display list text
  glPopAttrib();					// Pops the display list bits

  glPopMatrix();
}

void glFont::glPrintRot(float x, float y, float align, float rot,  const char *fmt, ...) {
  align/=2;
  float length = 0;		// Used to find the length of the text
  char text[256];			// Holds our string
  va_list ap;			// Pointer to list of arguments

  if (fmt == NULL)		// If there's no text
    return;			// Do nothing

  va_start(ap, fmt);		// Parses the string for variables
    vsprintf(text, fmt, ap);    // And converts symbols to actual numbers
  va_end(ap);			// Results are stored in text

  for (unsigned int loop=0;loop<(strlen(text));loop++) {
    length+=gmf[text[loop]].gmfCellIncX;		// Increase length by each characters width
  }

  length*=_size;
  glPushMatrix();

  glTranslatef(x-length*align,y+_size,0.0f);		// Translate &
  glScalef(_size,-_size,_size);                           // Scale

  glPushAttrib(GL_LIST_BIT);				// Pushes the display list bits
  glListBase(base+32);					// Sets the base character to 0
  glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws the display list text
  glPopAttrib();						// Pops the display list bits

  glPopMatrix();
}

#endif
