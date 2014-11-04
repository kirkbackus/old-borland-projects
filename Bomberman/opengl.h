#ifndef ____GL_HEADER_BBLOX
#define ____GL_HEADER_BBLOX

#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>

/*******************
 * Enable OpenGL
 *
 *******************/

void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{
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
    pfd.cColorBits = 32;
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
    glCullFace(GL_BACK);                    // Enable Culling to Speed Up Rendering

    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);     // For Alphablending
    glDepthFunc(GL_LEQUAL);                                 // The type of depth testing to do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);      // Really nice perspective calculations
    glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
}

/******************
 * Disable OpenGL
 *
 ******************/

void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}

/******************
 * Resize OpenGL Window
 *
 ******************/

void ResizeGLWindow(int x, int y, int width, int height) {
  if (height==0) height=1;
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,1.0f,250.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

/******************
 * Set View Ortho
 *
 ******************/

void SetViewOrtho(int left, int top, int right, int bottom, float angle) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(left,right,bottom,top,-1,1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

#endif
