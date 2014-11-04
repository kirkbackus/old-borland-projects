/********************************************
 * TerRacers by KIRK BACKUS & JUN LIANG     *
 *------------------------------------------*
 * "gmphysics.dll" created by Chris Giles   *
 ********************************************/

/**************************
 * Includes
 *
 **************************/
#include <fstream.h>
#include <iostream.h>
#include <stdarg.h>
#include <windows.h>
#include <math.h>
#include <vector>
#include <gl/gl.h>
#include <gl/glu.h>

//Custom Includes
#include "classes.h"

bool trigger=0;
bool play_2=0;
void TRFUNC(int num) {
  if (!trigger) return;
  char buffer[10];
  sprintf(buffer,"TRIGGER %u",num);
  MessageBox(NULL,buffer,"TRIGGER",MB_OK);
}

/**************************
 * Function Declarations
 *
 **************************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
WPARAM wParam, LPARAM lParam);

/**************************
 * Deletable Objects
 *
 **************************/

Race* vRace=NULL;
Terrain* vTerrain;
Vehicle* vVehicle=NULL;
Vehicle* vVehicle2=NULL;
vector<Powerbar*> vPowerbar;
vector<Progress*> vProgress;
vector<Menu*> vMenu;

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
    DWORD dwExStyle;
    DWORD dwStyle;

    /* register window class */
    wc.style = CS_OWNDC | CS_VREDRAW | CS_BYTEALIGNWINDOW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "TerRacers";
    RegisterClass (&wc);

    dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;    // Window extended style
    dwStyle=WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_MAXIMIZEBOX |
    WS_MINIMIZEBOX | WS_CAPTION | WS_SIZEBOX;

    /* create main window */
    hWnd = CreateWindowEx (dwExStyle,
      "TerRacers", "TeRRacers",
      dwStyle,
      CW_USEDEFAULT , CW_USEDEFAULT, 800, 600,
      NULL, NULL, hInstance, NULL);

    //Activate Random Number Generator
    randomize();

    //Window Dimensions
    RECT window;

    vProgress.push_back(new Progress(630));

    vPowerbar.push_back(new Powerbar(64)); //Player1 Powerbar
    vPowerbar.push_back(new Powerbar(64)); //Player2 Powerbar
    vPowerbar[1]->SetColor(1.0,0.25,0.5);

    /* enable OpenGL for the window */
    EnableOpenGL (hWnd, &hDC, &hRC);

    /** INITIALIZE PHYSICS */
    SetSolverAccuracy(1/60,8); //Run @ 60 fps / quite accurate
    SetFriction(1,1);

    /** Create Body Polygon */
    double poly = g.CreatePolygon();

    AddVertex( poly, -54, 5 );
    AddVertex( poly, -52, 8 );
    AddVertex( poly, -48, 12 );
    AddVertex( poly, -34, 19 );
    AddVertex( poly, -32, 19 );
    AddVertex( poly, -30, 20 );
    AddVertex( poly, -28, 20 );
    AddVertex( poly, -26, 21 );
    AddVertex( poly, -16, 21 );
    AddVertex( poly, -14, 20 );
    AddVertex( poly, -12, 20 );
    AddVertex( poly, -10, 19 );
    AddVertex( poly, -2, 19 );
    AddVertex( poly, 0, 20 );
    AddVertex( poly, 2, 20 );
    AddVertex( poly, 6, 22 );
    AddVertex( poly, 20, 22 );
    AddVertex( poly, 22, 21 );
    AddVertex( poly, 24, 21 );
    AddVertex( poly, 26, 20 );
    AddVertex( poly, 28, 20 );
    AddVertex( poly, 34, 17 );
    AddVertex( poly, 36, 17 );
    AddVertex( poly, 38, 16 );
    AddVertex( poly, 40, 16 );
    AddVertex( poly, 42, 15 );
    AddVertex( poly, 44, 15 );
    AddVertex( poly, 50, 12 );
    AddVertex( poly, 54, 8 );
    AddVertex( poly, 56, 5 );
    AddVertex( poly, 56, 0 );
    AddVertex( poly, 57, -2 );
    AddVertex( poly, 56, -4 );
    AddVertex( poly, 56, -10 );
    AddVertex( poly, 54, -14 );
    AddVertex( poly, 54, -16 );
    AddVertex( poly, 52, -18 );
    AddVertex( poly, 51, -20 );
    AddVertex( poly, 49, -22 );
    AddVertex( poly, 43, -26 );
    AddVertex( poly, 31, -30 );
    AddVertex( poly, 27, -30 );
    AddVertex( poly, 25, -31 );
    AddVertex( poly, -29, -31 );
    AddVertex( poly, -31, -30 );
    AddVertex( poly, -47, -30 );
    AddVertex( poly, -51, -28 );
    AddVertex( poly, -53, -26 );
    AddVertex( poly, -55, -23 );
    AddVertex( poly, -55, -21 );
    AddVertex( poly, -54, -19 );
    AddVertex( poly, -54, -17 );
    AddVertex( poly, -53, -15 );
    AddVertex( poly, -53, -7 );
    AddVertex( poly, -54, -5 );
    AddVertex( poly, -54, -3 );
    AddVertex( poly, -55, -1 );
    AddVertex( poly, -55, 1 );
    AddVertex( poly, -54, 3 );

    //View
    View view(0,0,640,480,240,180);
    view.SetViewPort(0,0,150,400,300);   //Used For Split Screen
    view.SetViewPort(1,400,150,400,300); //Used For Split Screen
    view.SetSplitScreen(0);

    vTerrain = new Terrain("GameData/terrain0.ter");
    view.SetMaxMin(vTerrain->GetMin(),vTerrain->GetMax());

    /** Create Texture Controller */
    Textures textures(hInstance);

    if (!textures.AddTexture128("GameData/car.bmp",8))MessageBoxA(hWnd,"FAILED TO LOAD \"car.bmp\"","ERROR",MB_OK);
    if (!textures.AddTexture64("GameData/wheel.bmp",1))MessageBoxA(hWnd,"FAILED TO LOAD \"wheel.bmp\"","ERROR",MB_OK);

    if (!textures.AddTexture128("GameData/button_play.bmp",2))MessageBoxA(hWnd,"FAILED TO LOAD \"button_play.bmp\"","ERROR",MB_OK);
    if (!textures.AddTexture128("GameData/button_2play.bmp",3))MessageBoxA(hWnd,"FAILED TO LOAD \"button_2play.bmp\"","ERROR",MB_OK);
    if (!textures.AddTexture128("GameData/button_quit.bmp",4))MessageBoxA(hWnd,"FAILED TO LOAD \"button_quit.bmp\"","ERROR",MB_OK);

    if (!textures.AddTexture128("GameData/button_restart.bmp",5))MessageBoxA(hWnd,"FAILED TO LOAD \"button_restart.bmp\"","ERROR",MB_OK);
    if (!textures.AddTexture128("GameData/button_menu.bmp",6))MessageBoxA(hWnd,"FAILED TO LOAD \"button_menu.bmp\"","ERROR",MB_OK);
    if (!textures.AddTexture128("GameData/button_level.bmp",7))MessageBoxA(hWnd,"FAILED TO LOAD \"button_level.bmp\"","ERROR",MB_OK);

    ///Create Title Menu
    Menu TitleScreen(&textures,hDC);
    TitleScreen.SetColor1(0.0,0.3,0.7);
    TitleScreen.SetColor2(0.0,0.5,0.7);
    TitleScreen.SetColor3(1.0,1.0,1.0);
    TitleScreen.AddButton(2,256-140,176,128,128,"Play");
    TitleScreen.AddButton(3,256,176,128,128,"2 Player");
    TitleScreen.AddButton(4,256+140,176,128,128,"Quit");
    TitleScreen.SetTitle("TeRRacers");
    TitleScreen.ShowCredits(1);

    Menu EndRaceScreen(&textures,hDC);
    EndRaceScreen.BackgroundVisible(0);
    EndRaceScreen.TitleVisible(0);
    EndRaceScreen.SetColor3(1.0,1.0,1.0);
    EndRaceScreen.AddButton(5,256-70,176,128,128,"Restart Level");
    EndRaceScreen.AddButton(6,256+70,176,128,128,"Go Back Menu");

    Menu LevelSelect(&textures,hDC);
    LevelSelect.SetTitle("Level Select");
    LevelSelect.SetColor1(0.0,0.7,0.5);
    LevelSelect.SetColor2(0.0,0.7,0.3);
    LevelSelect.SetColor3(1.0,1.0,1.0);

    for (int y=0;y<4;y++) {
      for (int x=0;x<5;x++) {
        char buffer[20];
        sprintf(buffer,"GameData/terrain%u.ter",(y*5)+x);

        TerCData tmp;
        vTerrain->GetData(buffer, &tmp);

        LevelSelect.AddButton(7,100+x*86,69+y*86,84,84,tmp.name);
      }
    }

    vMenu.push_back(&TitleScreen);

    //Room Speed (fps)
    int roomsp=60;
    int spint=1000/roomsp+1;
    int nctick=GetTickCount()+spint;
    int ctick=GetTickCount();

    //Direction
    double dir=270;

    //Play Music
    //Media::mciPlay(1);

    //************************************************************************
    //
    // MAIN LOOP OF THE PROGRAM STARTS HERE
    //
    //************************************************************************
    while (!bQuit) {
      /* check for messages */
      if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        /* handle or dispatch messages */
        if (msg.message==WM_QUIT) {
          bQuit = 1;
        } else {
          TranslateMessage (&msg);
          DispatchMessage (&msg);
        }
      } else {
        if (ctick<nctick) {
          //Ctick
          ctick=GetTickCount();
        } else {
          //-----------------------------------------------------------------
          //UPDATE THE PHYSICS ENGINE
          //-----------------------------------------------------------------
          g.UpdateBodies(0);

          //-----------------------------------------------------------------
          //CONTROL THE NEXT ITERATION TIME
          //-----------------------------------------------------------------
          nctick+=(spint);

          //-----------------------------------------------------------------
          //GET THE WINDOW INFORMATION
          //-----------------------------------------------------------------
          GetClientRect(hWnd,&window);

          //-----------------------------------------------------------------
          //CONTROL ALL VEHICLES
          //-----------------------------------------------------------------
          if (vRace!=NULL) {
            if (vVehicle!=NULL && vRace->RaceStarted()) {
              if (vVehicle->getX()>vTerrain->GetMax()) {
                if (!vMenu.size()) {
                  vMenu.push_back(&EndRaceScreen);
                  vRace->EndRace();
                  view.Lock(1);
                }
              }
              if (GetAsyncKeyState(VK_RIGHT)) vVehicle->Drive(50);
              if (GetAsyncKeyState(VK_LEFT)) vVehicle->Drive(-50);
              if (GetAsyncKeyState(VK_UP)) {
                vPowerbar[0]->AddValue(.5);
              } else {
                if (vPowerbar[0]->GetValue()>0) {
                  vVehicle->Jump(dir,vPowerbar[0]->GetValue());
                  vPowerbar[0]->Reset();
                }
              }
            }

            if (vVehicle2!=NULL && vRace->RaceStarted()) {
              if (vVehicle2->getX()>vTerrain->GetMax()) {
                if (!vMenu.size()) {
                  vMenu.push_back(&EndRaceScreen);
                  vRace->EndRace();
                  view.Lock(1);
                }
              }

              if (GetAsyncKeyState(68)) vVehicle2->Drive(50);
              if (GetAsyncKeyState(65)) vVehicle2->Drive(-50);
              if (GetAsyncKeyState(87)) {
                vPowerbar[1]->AddValue(.5);
              } else {
                if (vPowerbar[1]->GetValue()>0) {
                  vVehicle2->Jump(dir,vPowerbar[1]->GetValue());
                  vPowerbar[1]->Reset();
                }
              }
            }
          }

          //-----------------------------------------------------------------
          //CONTROL ALL MENUS
          //-----------------------------------------------------------------
          if (vMenu.size()) {
            int opt=vMenu[0]->GetPressed();
            //Title Screen
            if (vMenu[0]==&TitleScreen) {
              if (opt!=-1) {
                if (opt==0) {
                  play_2=0;
                  vMenu.clear();
                  vMenu.push_back(&LevelSelect);
                  vMenu[0]->Reset();
                }

                if (opt==1) {
                  play_2=1;
                  vMenu.clear();
                  vMenu.push_back(&LevelSelect);
                  vMenu[0]->Reset();
                }
                if (opt==2)bQuit=1;
              }
            }

            else if (vMenu[0]==&LevelSelect) {
              if (opt!=-1) {
                char buffer[20];
                sprintf(buffer,"GameData/terrain%u.ter",opt);
                delete vTerrain;
                vTerrain = new Terrain(buffer);
                view.SetMaxMin(vTerrain->GetMin(),vTerrain->GetMax());

                if (!play_2) {
                  //Create Player 1 Vehicle
                  vVehicle = new Vehicle(vTerrain->GetStart().x,vTerrain->GetStart().y-256,poly,&textures,8,1);
                  //Create Race Controller
                  vRace = new Race(hDC);

                  vMenu.clear();
                  view.Lock(0);
                } else {
                  //Create Player 1 Vehicle
                  vVehicle = new Vehicle(vTerrain->GetStart().x,vTerrain->GetStart().y-256,poly,&textures,8,1);
                  vVehicle2 = new Vehicle(vTerrain->GetStart().x,vTerrain->GetStart().y-256,poly,&textures,8,1);
                  vVehicle->NoCollide(vVehicle2);

                  //Create Race Controller
                  vRace = new Race(hDC);

                  vMenu.clear();
                  view.Lock(0);
                  view.SetSplitScreen(1);
                  vProgress[0]->NumCars(1);
                }
              }
            }

            //Ending Race Screen
            else if (vMenu[0]==&EndRaceScreen) {
              if (opt!=-1) {
                if (opt==0) {
                  delete vVehicle;
                  if (vVehicle2!=NULL) delete vVehicle2;
                  delete vRace;
                  
                  vMenu.clear();

                  //Create Player 1 Vehicle
                  vVehicle = new Vehicle(vTerrain->GetStart().x,vTerrain->GetStart().y-256,poly,&textures,8,1);
                  if (view.isSplitScreen()) {
                    vVehicle2 = new Vehicle(vTerrain->GetStart().x,vTerrain->GetStart().y-256,poly,&textures,8,1);
                    vVehicle->NoCollide(vVehicle2);
                    vProgress[0]->NumCars(1);
                  }

                  //Create Race Controller
                  vRace = new Race(hDC);

                  //Kill ALL MENUS ^_^
                  vMenu.clear();
                  view.Lock(0);
                }

                if (opt==1) {
                  delete vVehicle;
                  if (vVehicle2!=NULL) delete vVehicle2;
                  delete vRace;

                  vVehicle=NULL;
                  vVehicle2=NULL;
                  vRace=NULL;

                  //Return Menu
                  view.SetSplitScreen(0);
                  vMenu.clear();
                  TitleScreen.Reset();
                  vMenu.push_back(&TitleScreen);
                }
              }
            }
          }

          //-----------------------------------------------------------------
          //CONTROL GLOBAL KEY PRESSES
          //-----------------------------------------------------------------
          if (GetAsyncKeyState(VK_ESCAPE)) {
            break;
          }

          //-----------------------------------------------------------------
          //CONTROL THE VIEW
          //-----------------------------------------------------------------
          if (vVehicle!=NULL) {
            view.KeepInView(0,vVehicle->getX(),vVehicle->getY());
            if (vVehicle2!=NULL)
              view.KeepInView(1,vVehicle2->getX(),vVehicle2->getY());
          } else {
            view.view_x[0]=0; view.view_y[0]=0;
          }

          //-----------------------------------------------------------------
          //CONTROL THE RACE CONTROLLER
          //-----------------------------------------------------------------
          if (vRace!=NULL) {
            vRace->SetTime(630,10);
            vRace->SetRSG(view.view_w[0]/2,view.view_h[0]/2-128);
          }

          //-----------------------------------------------------------------
          //CONTROL PROGRESS BAR
          //-----------------------------------------------------------------
          if (vProgress.size()) {
            float vpos=0,vpos2=0;
            if (vVehicle!=NULL)vpos=vVehicle->getX();
            if (vVehicle2!=NULL)vpos2=vVehicle2->getX();

            if (vpos2<=0)vProgress[0]->SetPos(5, 470, vTerrain->GetMin(), vTerrain->GetMax(), vpos);
            else vProgress[0]->SetPos(5, 470, vTerrain->GetMin(), vTerrain->GetMax(), vpos, vpos2);
          }

          //-----------------------------------------------------------------
          //CONTROL ALL POWERBARS
          //-----------------------------------------------------------------
          if (vPowerbar.size()) {
            if (view.isSplitScreen()) {
              vPowerbar[0]->SetPos(250,5,240,32);
              vPowerbar[1]->SetPos(5,5,240,32);
            } else {
              vPowerbar[0]->SetPos(5,5,240,32);
              vPowerbar[1]->SetPos(-2,-2,1,1);
            }
          }

          //-----------------------------------------------------------------
          //CONTROL GRAVITY
          //-----------------------------------------------------------------
          SetGravity(cos((pi/180)*-dir)*10,sin((pi/180)*-dir)*10);

          //-----------------------------------------------------------------
          // EVERYTHING IS DRAWN HERE
          //-----------------------------------------------------------------
          glClearColor (0.0f, 0.0f, 0.0f, 1.0f);
          glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          glLoadIdentity();

          int w=window.right-window.left==0 ? 2:(window.right-window.left);
          int h=window.bottom-window.left==0 ? 2:(window.bottom-window.left);
          glViewport(0,0,w,h);

          view.SetViewPort(-1,0,0,w,h);         //Regular View Port
          view.SetViewPort(0,0,h/4,w/2,h/2);    //Used For Split Screen
          view.SetViewPort(1,w/2,h/4,w/2,h/2);  //Used For Split Screen

          for (int i=0;i<view.isSplitScreen()+1;i++) {
            view.Update();

            if (view.isSplitScreen() && view.getCurrent()==0)
            if (vVehicle2!=NULL) {
              glColor3f(1.0,0.75,0.75);
              vVehicle2->Draw();
            }

            if (view.isSplitScreen()) glColor3f(0.75,1.0,0.75);
            if (vVehicle!=NULL)vVehicle->Draw();

            if (view.isSplitScreen() && view.getCurrent()==1)
            if (vVehicle2!=NULL) {
              glColor3f(1.0,0.75,0.75);
              vVehicle2->Draw();
            }

            if (vTerrain!=NULL)vTerrain->Draw();
            if (view.UpdateHUD()) {
              for (int i=0;i<(signed)vPowerbar.size();i++)vPowerbar[i]->Draw();
              for (int i=0;i<(signed)vProgress.size();i++)vProgress[i]->Draw();
              for (int i=0;i<(signed)vMenu.size();i++)vMenu[i]->Draw(0,0);
              if (vRace!=NULL)vRace->Draw();
              if (view.isSplitScreen()) {
                glColor3f(1.0,1.0,1.0);
                DrawLine(0,128,640,128);
                DrawLine(0,368,640,368);
                DrawLine(320,128,320,368);
              }
            }
          }

          SwapBuffers(hDC);
          glFlush();
        }
      }
    }

    //Terrain
    delete vVehicle;
    delete vTerrain;

    // shutdown OpenGL
    DisableOpenGL (hWnd, hDC, hRC);

    // free libraries
    g.ReleasePhysics();
    FreeLibrary(physx);
    //FreeLibrary(n39);

    // destroy the window explicitly
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


