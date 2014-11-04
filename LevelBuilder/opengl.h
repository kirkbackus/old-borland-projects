#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

//ENABLE OPENGL
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC) {
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC (hWnd);

    /* set the pixel format for the DC */
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
      PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );

    glEnable(GL_DITHER);                    // Not sure what this does
    glEnable (GL_BLEND);                    // Enables blending for transparency
    glEnable(GL_DEPTH_TEST);                // Enables depth testing
    glEnable(GL_COLOR_MATERIAL);            // Not sure what this does either

    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);     // For Alphablending
    glDepthFunc(GL_LEQUAL);                                 // The type of depth testing to do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);      // Really nice perspective calculations
}

//DISABLE OPENGL
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC) {
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}

//OPENGL VIEW
void SetViewOrtho(int left, int top, int right, int bottom) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(left,right,bottom,top,-10,10);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

//POINT DISTANCE
float PointDistance(float x1, float y1, float x2, float y2) {
  return(sqrt(pow((x2-x1),2)+pow((y2-y1),2)));
}

//DRAW POINT
void DrawPoint(float x, float y) {
  glPushMatrix();

  glBegin(GL_TRIANGLE_FAN);

  glVertex2f(x,y);

  for (int i=0;i<=8;i++)
    glVertex2f(x+sin(0.0174*i*45)*4,y+cos(0.0174*i*45)*4);

  glEnd();

  glPopMatrix();
}

//DRAW LINE
void DrawLine(float x1, float y1, float x2, float y2) {
  glPushMatrix();

  glBegin(GL_LINES);

  glVertex2f(x1,y1);
  glVertex2f(x2,y2);

  glEnd();

  glPopMatrix();
}
