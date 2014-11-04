/**************************
 * Includes
 *
 **************************/

#include <windows.h>
#include <time.h>
#include <vector>
#include <process.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "blackbox.h"
#include "usock.h"

#define DMessage(a) MessageBox(NULL,a,"BomB",MB_OK | MB_ICONERROR)
#define FPS_LIMIT 60

using namespace std;
using namespace Blackbox;

#include "Headers/timer.h"
#include "Headers/drawing.h"
#include "Headers/menu.h"
#include "Headers/particles.h"
#include "Headers/player.h"
#include "Headers/level.h"
#include "Headers/hud.h"
#include "Headers/gamecontrol.h"
#include "glGUI/glGUI.h"
#include "usock.h"

/**************************
 * Definitions
 *
 **************************/
#ifndef PI
#define PI 3.1415926535897932384626433
#endif

#define PointDistance(a,b,c,d) sqrt((c-a)*(c-a)+(d-b)*(d-b))
#define PointDirection(a,b,c,d) 180/PI*atan2(d-b,c-a)

#define ShowMessage(a) MessageBox(NULL,a,"OH SNAP!",MB_OK)

#ifndef sign
#define sign(a) a<0 ? -1:1
#endif

/**************************
 * Function Declarations
 *
 **************************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void SetViewOrtho(int left, int top, int right, int bottom);
void SetViewport(int x, int y, int width, int height);
void DrawPolygon(Blackbox::Polygon* p, float r, float g, float b, float a, bool outline);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);
void ClientResize(HWND hWnd, int nWidth, int nHeight);


/**************************
 * WinMain
 *
 **************************/

int WINAPI
WinMain (HINSTANCE hInstance,
         HINSTANCE hPrevInstance,
         LPSTR lpCmdLine,
         int iCmdShow)
{
    WNDCLASS wc;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;

    /* register window class */
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "BomB";
    RegisterClass (&wc);

    srand (time(NULL));

    Timer timer;

    /* create main window */
    hWnd = CreateWindow (
      "BomB", "BomB",
      WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE | WS_MAXIMIZEBOX | WS_SIZEBOX | WS_MINIMIZEBOX,
      0, 0, 640, 480, NULL, NULL, hInstance, NULL);

    ClientResize(hWnd,640,480);

    /* enable OpenGL for the window */
    EnableOpenGL (hWnd, &hDC, &hRC);

    Blackbox::Polygon* _playerpoly = new Blackbox::Polygon();
    _playerpoly->BuildCircle(0,0,16,16);

    Blackbox::Polygon* _upgradepoly = new Blackbox::Polygon();
    _upgradepoly->BuildCircle(0,0,16,16);

    Blackbox::Polygon* _bulletsmallpoly = new Blackbox::Polygon();
    _bulletsmallpoly->BuildCircle(0,0,2,4);

    Blackbox::Polygon* _bulletrocket = new Blackbox::Polygon();
    _bulletrocket->BuildCircle(0,0,16,16);

    Textures textures(hInstance);
    if (!textures.AddTexture64("particle.bmp",1))MessageBoxA(hWnd,"FAILED TO LOAD \"particle.bmp\"","ERROR",MB_OK);

    Player* p1 = new Player(64,64,1);

    p1->SetCollisionPoly(_playerpoly);
    p1->SetCollisionBullets(_bulletsmallpoly,_bulletrocket);
    p1->SetColor(1,.8,.8);

    Player* p2 = new Player(64,880,1);

    p2->SetCollisionPoly(_playerpoly);
    p2->SetCollisionBullets(_bulletsmallpoly,_bulletrocket);
    p2->SetColor(.8,1,.8);

    Player* p3 = new Player(1216,880,1);

    p3->SetCollisionPoly(_playerpoly);
    p3->SetCollisionBullets(_bulletsmallpoly,_bulletrocket);
    p3->SetColor(.8,.8,1);

    Player* p4 = new Player(1216,64,1);

    p4->SetCollisionPoly(_playerpoly);
    p4->SetCollisionBullets(_bulletsmallpoly,_bulletrocket);
    p4->SetColor(1,.8,1);

    Player* control = NULL;

    GameControl* gc = new GameControl(hDC,p1,p2,p3,p4);

    Menu* joinmenu = new Menu(hDC);
    joinmenu->SetTitle("Join");
    joinmenu->AddItem("IP: ",1);
    joinmenu->AddItem("Join");
    joinmenu->AddItem("Back");
    joinmenu->visible = 0;

    Menu* optionmenu = new Menu(hDC);
    optionmenu->SetTitle("Options");
    optionmenu->AddItem("Name: ",2);
    optionmenu->AddItem("Back");
    optionmenu->visible = 0;

    int view_x, view_y, view_width, view_height;

    view_x = 320;
    view_y = 240;
    view_width = 640;
    view_height = 480;

    Level* level = new Level();
    level->SetLimits(1280,960);

    level->AddRectangle(256,128,320,320);
    level->AddRectangle(128,256,320,320);
    level->AddRectangle(1024,128,960,320);
    level->AddRectangle(1152,256,960,320);
    level->AddRectangle(256,832,320,640);
    level->AddRectangle(128,704,320,640);
    level->AddRectangle(1024,832,960,640);
    level->AddRectangle(1152,704,960,640);

    level->AddCircle(640,480,128,32);

    level->AddRectangle(608,192,672,320);
    level->AddRectangle(608,640,672,768);
    level->AddRectangle(352,448,480,512);
    level->AddRectangle(800,448,928,512);

    level->AddUpgrade(640,128,0,_upgradepoly);
    level->AddUpgrade(640,832,0,_upgradepoly);
    level->AddUpgrade(288,480,1,_upgradepoly);
    level->AddUpgrade(992,480,1,_upgradepoly);
    level->AddUpgrade(352,352,2,_upgradepoly);
    level->AddUpgrade(928,608,2,_upgradepoly);
    level->AddUpgrade(928,352,5,_upgradepoly);
    level->AddUpgrade(352,608,5,_upgradepoly);
    level->AddUpgrade(496,480,3,_upgradepoly);
    level->AddUpgrade(784,480,3,_upgradepoly);
    level->AddUpgrade(640,336,4,_upgradepoly);
    level->AddUpgrade(640,624,4,_upgradepoly);

    HUD* hud = new HUD(hDC);
    glFont* font = new glFont(hDC,"Arial",32);

    POINT cursor;

    GUIWindow* wndMain = new GUIWindow(192,80,256,320);
    GUIButton* btnHostGame = new GUIButton(32,32,192,32);
    GUIButton* btnJoinGame = new GUIButton(32,80,192,32);
    GUIButton* btnOptions = new GUIButton(32,128,192,32);
    GUIButton* btnQuit = new GUIButton(32,256,192,32);
    GUILabel* capTest = new GUILabel(32,156,192,32);

    wndMain->caption = "BomB";
    btnHostGame->caption = "Host Game";
    btnJoinGame->caption = "Join Game";
    btnOptions->caption = "Options";
    btnQuit->caption = "Quit";

    capTest->SetCaption("This is the caption to test and see if word wrap is working!");
    capTest->align = FA_CENTER;

    wndMain->AddControl(btnHostGame);
    wndMain->AddControl(btnJoinGame);
    wndMain->AddControl(btnOptions);
    wndMain->AddControl(btnQuit);
    wndMain->AddControl(capTest);

    ///PROGRAM MAIN LOOP
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }
        else
        {
            RECT tmp;

            GetClientRect(hWnd,&tmp);
            GetCursorPos(&cursor);
            ScreenToClient(hWnd,&cursor);

            UpdateKeys();

            float tmpx = cursor.x,tmpy = cursor.y;

            tmpx/=((float)tmp.right/view_width>0)?(float)tmp.right/view_width:1;
            tmpy/=((float)tmp.bottom/view_height>0)?(float)tmp.bottom/view_height:1;

            cursor.x = (long)tmpx;
            cursor.y = (long)tmpy;

            if (control!=NULL) {
                if (control->alive) {
                    if (KeyPressed('D')) control->x += 3;
                    if (KeyPressed('A')) control->x -= 3;
                    if (KeyPressed('W')) control->y -= 3;
                    if (KeyPressed('S')) control->y += 3;
                }

                control->aimdir = 180/PI*atan2((cursor.y+view_y)-control->y, (cursor.x+view_x)-control->x);

                view_x = (int)(control->x+((cursor.x<640 && cursor.x > 0 ? cursor.x : cursor.x > 0 ? 640 : 0)-320)/2)-320;
                view_y = (int)(control->y+((cursor.y<480 && cursor.y > 0 ? cursor.y : cursor.y > 0 ? 480 : 0)-240)/2)-240;

                if (KeyPressed(VK_LBUTTON)) {
                    if (control->alive) if (control->Shoot()) gc->Shoot();
                }

                hud->health = control->health;
                hud->weaponid = control->weapon->type;
                hud->ammo = control->weapon->ammo;
                hud->maxammo = control->weapon->maxammo;

                level->Collided(p1);
                level->Collided(p2);
                level->Collided(p3);
                level->Collided(p4);

                level->CollidedBullets(p1,p2,p3,p4);
                level->CollidedBullets(p2,p1,p3,p4);
                level->CollidedBullets(p3,p1,p2,p4);
                level->CollidedBullets(p4,p1,p2,p3);

                p1->Update();
                p2->Update();
                p3->Update();
                p4->Update();

                if (control->killedby!=NULL) {
                    int kd,kk;

                    if (control->killedby==p1) kk = 0;
                    if (control->killedby==p2) kk = 1;
                    if (control->killedby==p3) kk = 2;
                    if (control->killedby==p4) kk = 3;

                    if (control==p1) kd = 0;
                    if (control==p2) kd = 1;
                    if (control==p3) kd = 2;
                    if (control==p4) kd = 3;

                    gc->AddDeath(kd);
                    gc->AddKill(kk);

                    control->killedby = NULL;
                }
            } else {
                control = gc->SetControl();
                if (control!=NULL) control->Activate(1);
            }

            gc->Update();

            if(timer.get_ticks() < 1000 / FPS_LIMIT ) Sleep( ( 1000 / FPS_LIMIT ) - timer.get_ticks()-1 );
            timer.start();

            ///---------------------------------------------------------------
            ///DRAW EVERYTHING BELOW
            ///---------------------------------------------------------------
            SetViewport(0,0,tmp.right,tmp.bottom);
            SetViewOrtho(view_x,view_y,view_x+view_width,view_y+view_height);
            wndMain->Update(cursor.x,cursor.y);

            glClearColor (0.0f, 0.0f, 0.0f, 1.0f);
            glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glLoadIdentity();

            level->Draw();

            if (control!=NULL) control->Draw();
            if (control!=p1) p1->Draw();
            if (control!=p2) p2->Draw();
            if (control!=p3) p3->Draw();
            if (control!=p4) p4->Draw();

            textures.SetTexture(1);
            pe.Update();
            pe.Draw();

            SetViewOrtho(0,0,640,480);

            //Close Game
            if (btnQuit->Clicked()) {
                PostQuitMessage(0); return 0;
            }

            if (btnHostGame->Clicked()) {
                DrawRectangle(0,0,640,480,0,0,0,.75,0); glColor4f(1,1,1,1); font->glPrint(320,220,FA_CENTER,"ATTEMPING TO HOST"); SwapBuffers(hDC);
                if (!gc->started) if(gc->HostGame()) wndMain->visible = 0;
            }

            if (btnJoinGame->Clicked()) {
                DrawRectangle(0,0,640,480,0,0,0,.75,0); glColor4f(1,1,1,1); font->glPrint(320,220,FA_CENTER,"ATTEMPING TO FIND A GAME"); SwapBuffers(hDC);
                if (!gc->started) if (gc->JoinGame((char*)"127.0.0.1")) wndMain->visible = 0;
            }

            if (btnOptions->Clicked()) {
                //SHOW OPTIONS
            }

            if (control!=NULL) hud->Draw();

            gc->Draw();

            wndMain->Draw();

            SwapBuffers (hDC);
        }
    }

    delete _playerpoly;

    /* shutdown OpenGL */
    DisableOpenGL (hWnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow (hWnd);

    return msg.wParam;
}


/********************
 * Window Procedure
 *
 ********************/
LRESULT CALLBACK
WndProc (HWND hWnd, UINT message,
         WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE:
        return 0;
    case WM_CLOSE:
        PostQuitMessage (0);
        return 0;

    case WM_DESTROY:
        return 0;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            return 0;
        }
        return 0;

    default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}


/*******************
 * Enable OpenGL
 *
 *******************/
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

    glShadeModel(GL_SMOOTH);		        // Enables smooth shading
	glClearColor(0.0f,0.0f,0.0f,0.0f);      	// Black background
	glClearDepth(1.0f);			        // Depth buffer setup
	glDisable(GL_DEPTH_TEST);	        	// Disables depth testing
	glEnable(GL_BLEND);	        		// Enable blending
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);	        // Type of blending to perform
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really nice perspective calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);	        // Really nice point smoothing
	glEnable(GL_TEXTURE_2D);	        	// Enable texture mapping


    //Enable OpenGL Settings
    //glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LEQUAL);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


/******************
 * Disable OpenGL
 *
 ******************/
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC) {
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}

/******************
 * Orthographics
 *
 ******************/
void SetViewOrtho(int left, int top, int right, int bottom) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(left,right,bottom,top,-1,1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void SetViewport(int x, int y, int width, int height) {
  if (y<=0) y=1;
  glViewport(x,y,width,height);
}

void ClientResize(HWND hWnd, int nWidth, int nHeight)
{
    RECT rcClient, rcWindow;
    POINT ptDiff;
    GetClientRect(hWnd, &rcClient);
    GetWindowRect(hWnd, &rcWindow);
    ptDiff.x = (rcWindow.right - rcWindow.left) - rcClient.right;
    ptDiff.y = (rcWindow.bottom - rcWindow.top) - rcClient.bottom;
    MoveWindow(hWnd,rcWindow.left, rcWindow.top, nWidth + ptDiff.x, nHeight + ptDiff.y, TRUE);
}
