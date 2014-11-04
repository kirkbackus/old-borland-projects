/********************************************
 * Playground Unltd. by KIRK BACKUS         *
 *------------------------------------------*
 * "gmphysics.dll" created by Chris Giles   *
 ********************************************/

#define QMessage(a) MessageBox(NULL,a,"Playground Unlimited",MB_OK);
#define MAX(a,b) (a>b)? a:b
#define MIN(a,b) (a<b)? a:b

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
bool pause=1;
#include "classes.h"

bool trigger=0;
bool play_2=0;
bool pcurrent=0;

/**************************
 * Function Declarations
 *
 **************************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void DrawHelp(glFont* fnt);
bool SavePlayground();
bool LoadPlayground(char fname[128]="savetmp.plg");
void DeleteDynamicObject(int id);
void RestartPlayground();

/**************************
 * Deletable Objects
 *
 **************************/

vector<Dynamic*> vDynamic;
vector<Joint*> vJoint;
vector<Spring*> vSpring;
vector<Water*> vWater;
vector<Blob*> vBlob;

//FOR HELP
vector<char*> vShapes;
vector<char*> vTools;
vector<char*> vExtras;

/**************************
 * Other Vars
 *
 **************************/

int t1id = -1;
int t2id = -1;
int ct1id = -1;
int ct2id = -1;

int keyid[2] = {-1,-1};
int settingkey = 0;
int ckeyid = 0;

int viewid = -1;
int toolx = -1000;
int tooly = -1000;

bool zoompress = 0;

/********************
 * Saving/Loading Structures
 *
 ********************/
struct SaveDynamic {
  float type;
  float x,y,a1,a2,a3;
  float hsp,vsp,rot,rotsp;
  float autospin;
  float mass;
  bool hidden;
  float magnet;
  float bounciness;
  float r,g,b,a;
};

struct SaveJoint {
  float type;
  int b1,b2;
  int bodyid;
  float x,y;
  float r,g,b;
};

struct SaveSpring {
  int b1,b2;
  int bodyid;
  float x1,y1,x2,y2;
  float minf,maxf;
  float len;
  float r,g,b;
};

struct SaveWater {
  int bodyid;
  float x,y,width,height;
  float r,g,b;
};

struct SaveBlob {
  int bodyid;
  float x,y,rad,res;
  float r,g,b,r2,g2,b2;
  int numobj;
};

/**************************
 * Point In Object
 *
 **************************/
int PointInObject(POINT m, int classid) {
  int i=classid;
  if (vDynamic[i]->type==SHAPE_SPHERE || vDynamic[i]->type==SHAPE_FLUID || vDynamic[i]->type==SHAPE_LINE) {
    POINT o;
    o.x = vDynamic[i]->getX(); o.y = vDynamic[i]->getY();
    if (PointCircleCollide(m,o,(vDynamic[i]->getWidth()+vDynamic[i]->getHeight())/2)) return(i);
  }
  if (vDynamic[i]->type==SHAPE_BOX || vDynamic[i]->type==SHAPE_CAPSULE) {
    RECT o;
    o.left = vDynamic[i]->getX();
    o.right = vDynamic[i]->getWidth();
    o.top = vDynamic[i]->getY();
    o.bottom = vDynamic[i]->getHeight();
    if (PointBoxCollide(m,o,vDynamic[i]->getRot())) return(i);
  }
  if (vDynamic[i]->type==SHAPE_CAPSULE) {
    RECT o;
    POINT e;
    o.left = vDynamic[i]->getX();
    o.right = vDynamic[i]->getWidth()*2;
    o.top = vDynamic[i]->getY();
    o.bottom = vDynamic[i]->getHeight();
    if (PointBoxCollide(m,o,vDynamic[i]->getRot()))  return(i);
    e.x = o.left-LengthDirX(vDynamic[i]->getHeight()/2,vDynamic[i]->getRot()+90);
    e.y = o.top+LengthDirY(vDynamic[i]->getHeight()/2,vDynamic[i]->getRot()+90);
    if (PointCircleCollide(m,e,vDynamic[i]->getWidth())) return(i);
    e.x = o.left-LengthDirX(vDynamic[i]->getHeight()/2,vDynamic[i]->getRot()-90);
    e.y = o.top+LengthDirY(vDynamic[i]->getHeight()/2,vDynamic[i]->getRot()-90);
    if (PointCircleCollide(m,e,vDynamic[i]->getWidth())) return(i);
  }

  if (vDynamic[i]->type==SHAPE_TRIANGLE) {
    float tdist,tdir;
    POINT a,b,c;

    a.x = vDynamic[i]->getX()-vDynamic[i]->getWidth()/2;
    a.y = vDynamic[i]->getY()+vDynamic[i]->getHeight()/2;
    tdist = PointDistance(a.x,a.y,vDynamic[i]->getX(),vDynamic[i]->getY());
    tdir = PointDirection(vDynamic[i]->getX(),vDynamic[i]->getY(),a.x,a.y)-vDynamic[i]->getRot();
    a.x = vDynamic[i]->getX()+LengthDirX(tdist,tdir);
    a.y = vDynamic[i]->getY()+LengthDirY(tdist,tdir);

    b.x = vDynamic[i]->getX()+vDynamic[i]->getWidth()/2;
    b.y = vDynamic[i]->getY()+vDynamic[i]->getHeight()/2;
    tdist = PointDistance(b.x,b.y,vDynamic[i]->getX(),vDynamic[i]->getY());
    tdir = PointDirection(vDynamic[i]->getX(),vDynamic[i]->getY(),b.x,b.y)-vDynamic[i]->getRot();
    b.x = vDynamic[i]->getX()+LengthDirX(tdist,tdir);
    b.y = vDynamic[i]->getY()+LengthDirY(tdist,tdir);

    c.x = vDynamic[i]->getX();
    c.y = vDynamic[i]->getY()-vDynamic[i]->getHeight()/2;
    tdist = PointDistance(c.x,c.y,vDynamic[i]->getX(),vDynamic[i]->getY());
    tdir = PointDirection(vDynamic[i]->getX(),vDynamic[i]->getY(),c.x,c.y)-vDynamic[i]->getRot();
    c.x = vDynamic[i]->getX()+LengthDirX(tdist,tdir);
    c.y = vDynamic[i]->getY()+LengthDirY(tdist,tdir);
    if (PointTriangleCollide(m,a,b,c)) return(i);
  }
  return(WORLD);
}

/**************************
 * Body Exists
 *
 **************************/
bool BodyExists(int bodyid) {
  for (unsigned int i=0;i<vDynamic.size();i++) {
    if (vDynamic[i]->id==bodyid)return 1;
  }
  return 0;
}


/**************************
 * Nearest Object
 *
 **************************/
float NearestObject(double x, double y, int* id, bool ignore_hidden) {
  float dist;
  POINT m;
  m.x = x;
  m.y = y;
  for (int i=vDynamic.size()-1;i>=3;i--) {
    if (vDynamic[i]->hidden && ignore_hidden) continue;
    float tdist=sqrt(pow(x-vDynamic[i]->getX(),2)+pow(y-vDynamic[i]->getY(),2));
    if (tdist<(vDynamic[i]->getWidth()+vDynamic[i]->getHeight())) {
      *id=PointInObject(m,i);
      if (*id!=WORLD)return(dist);
    }
  }
  *id = WORLD;
  return(WORLD);
}

inline int GetBodyObject(int classid) {
  if (classid==WORLD) return (WORLD);
  return (vDynamic[classid]->id);
}

int GetClassObject(int bodyid) {
  for (int i=0;i<(signed)vDynamic.size();i++) {
    if (vDynamic[i]->id==bodyid)return(i);
  }
  return(-1);
}

void CreateRope(int b1, int b2, float x1, float y1, float x2, float y2) {
  int numobj = ceil(PointDistance(x1,y1,x2,y2)/16);
  float dir = (int)PointDirection(x1,y1,x2,y2);

  vDynamic.push_back(new Dynamic(x1-LengthDirX(8,dir),y1+LengthDirY(8,dir),1,SHAPE_SPHERE,15));
  vDynamic[vDynamic.size()-1]->setColor((rand()%128+128)/255.0,(rand()%128+128)/255.0,(rand()%128+128)/255.0,1);

  vJoint.push_back(new Joint(vDynamic[vDynamic.size()-1]->id,b1, 1));
  if (b1 != WORLD) SetBodyCollide(vDynamic[vDynamic.size()-1]->id, b1, false);

  int i;
  for (i=1;i<numobj-1;i++) {
    vDynamic.push_back(new Dynamic(x1-LengthDirX(8+16*i,dir),y1+LengthDirY(8+16*i,dir),1,SHAPE_SPHERE,15));
    vDynamic[vDynamic.size()-1]->setColor((rand()%128+128)/255.0,(rand()%128+128)/255.0,(rand()%128+128)/255.0,1);
    vJoint.push_back(new Joint(vDynamic[vDynamic.size()-1]->id, GetAsyncKeyState(VK_SHIFT) ? WORLD : vDynamic[vDynamic.size()-2]->id, 1));
    vJoint[vJoint.size()-1]->setColor((rand()%128+128)/255.0,(rand()%128+128)/255.0,(rand()%128+128)/255.0,1);
    vSpring.push_back(new Spring(vDynamic[vDynamic.size()-2]->id,vDynamic[vDynamic.size()-1]->id));
    vSpring[vSpring.size()-1]->setColor((rand()%128+128)/255.0,(rand()%128+128)/255.0,(rand()%128+128)/255.0,1);
    SetBodyCollide(vDynamic[vDynamic.size()-2]->id, vDynamic[vDynamic.size()-1]->id, false);
  }

  vDynamic.push_back(new Dynamic(x1-LengthDirX(8+16*i,dir),y1+LengthDirY(8+16*i,dir),ACTOR,SHAPE_SPHERE,15));
  vDynamic[vDynamic.size()-1]->setColor((rand()%128+128)/255.0,(rand()%128+128)/255.0,(rand()%128+128)/255.0,1);
  vJoint.push_back(new Joint(vDynamic[vDynamic.size()-1]->id, vDynamic[vDynamic.size()-2]->id, 1));
  vJoint[vJoint.size()-1]->setColor((rand()%128+128)/255.0,(rand()%128+128)/255.0,(rand()%128+128)/255.0,1);
  vSpring.push_back(new Spring(vDynamic[vDynamic.size()-2]->id,vDynamic[vDynamic.size()-1]->id));
  vSpring[vSpring.size()-1]->setColor((rand()%128+128)/255.0,(rand()%128+128)/255.0,(rand()%128+128)/255.0,1);
  SetBodyCollide(vDynamic[vDynamic.size()-2]->id, vDynamic[vDynamic.size()-1]->id, false);
  vJoint.push_back(new Joint(vDynamic[vDynamic.size()-1]->id,b2, 1));
  if (b2 != WORLD) SetBodyCollide(vDynamic[vDynamic.size()-1]->id, b2, false);
}

void CreateTerrain(float x1, float y1, float x2, float y2) {
  if (x1>x2) { float tmp=x2; x2=x1; x1=tmp;}
  if (y1>y2) { float tmp=y2; y2=y1; y1=tmp;}
  float angle=0.0f;
  float height = y2-y1;
  float width = x2-x1;
  float cangle = 24.0f;
  float dist = 16.0f;
  float xp=x1,yp;
  float xn,yn;
  yp = y1+rand()%(int)height;
  while(xp-x1<width-dist) {
    angle += (float)(rand()%360)/360.0*cangle-cangle/2;
    xn = xp+LengthDirX(dist,angle);
    yn = yp+LengthDirY(dist,angle);
    if (angle>45)angle=45;
    if (angle<-45)angle=-45;
    if (yn >= y2) {
      angle = 0;
      yn = y2;
    }
    if (yn <= y1) {
      angle = 0;
      yn = y1;
    }
    vDynamic.push_back(new Dynamic((int)xp,(int)yp,1,SHAPE_LINE,(int)xn,(int)yn));
    vDynamic[vDynamic.size()-1]->setColor((rand()%128+128)/255.0,(rand()%128+128)/255.0,(rand()%128+128)/255.0,1);
    xp = xn; yp = yn;
  }

  if (xp!=x2) {
    vDynamic.push_back(new Dynamic((int)xp,(int)yp,1,SHAPE_LINE,(int)x2,(int)yn));
    vDynamic[vDynamic.size()-1]->setColor((rand()%128+128)/255.0,(rand()%128+128)/255.0,(rand()%128+128)/255.0,1);
  }
}

/**************************
 * WinMain
 *
 **************************/

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow) {
    WNDCLASS wc;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = 0;
    DWORD dwExStyle;
    DWORD dwStyle;

    /* register window class */
    wc.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW | CS_BYTEALIGNCLIENT;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (hInstance, "MAINICON");
    wc.hCursor = LoadCursor (hInstance, "IDC_CURSOR");
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "PlaygroundUnlimited";
    RegisterClass (&wc);        

    dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;    // Window extended style
    dwStyle=WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_MAXIMIZEBOX |
    WS_MINIMIZEBOX | WS_CAPTION | WS_SIZEBOX;

    /* create main window */
    hWnd = CreateWindowEx (dwExStyle,
      "PlaygroundUnlimited", "Playground Unlimited",
      dwStyle,
      CW_USEDEFAULT , CW_USEDEFAULT, 800, 600,
      NULL, NULL, hInstance, NULL);

    //Activate Random Number Generator
    randomize();

    //For Window Dimensions
    RECT window;
    POINT mouse;
    POINT scr_mouse;

    /* Enable OpenGL for the window */
    EnableOpenGL (hWnd, &hDC, &hRC);

    /** INITIALIZE PHYSICS */
    SetSolverAccuracy(1/60,8); //Run @ 60 fps / quite accurate
    SetFriction(1,1);

    //View
    View view(0,0,640,480,240,180);
    view.SetSplitScreen(0);

    view.SetMaxMin(0, 64000);

    view.SetView(0,0,5920,640,480);
    view.SetBorder(256,216);

    //Create Boundries
    vDynamic.push_back(new Dynamic(0,6399,STATIC,SHAPE_PLANE,90));
    vDynamic.push_back(new Dynamic(0,0,STATIC,SHAPE_PLANE,0));
    vDynamic.push_back(new Dynamic(64000,0,STATIC,SHAPE_PLANE,180));

    //Room Speed (fps)
    int roomsp=60;
    int spint=1000/roomsp+1;
    int nctick=GetTickCount()+spint;
    int ctick=GetTickCount();

    //Gravity Direction
    float dir=90.0f;
    float gpow=10;

    //Drawing / Creating
    int shapeid=0;
    int toolid=0;

    float tsx,tsy;
    tsx=-1000;
    tsy=-1000;

    //Fonts
    glFont fnt(hDC,"Comic Sans MS",16);

    //SET LINE
    SetLineSize(8);

    //ADD HELP
    vShapes.push_back("SHAPES (HOLD SHIFT TO MAKE IT STATIC)");
    vShapes.push_back("USE THE RIGHT MOUSE BUTTON");
    vShapes.push_back("1 - Rectangle");
    vShapes.push_back("2 - Circle (Hold Ctrl for blob)");
    vShapes.push_back("3 - Triangle");
    vShapes.push_back("4 - Static Line");
    vShapes.push_back("5 - Capsule");
    vShapes.push_back("6 - Terrain");
    vShapes.push_back("7 - Rope Bridge");
    vShapes.push_back("8 - Fluid Particle");
    vShapes.push_back("9 - Water (HOLD SHIFT FOR PLANE)");

    vExtras.push_back("Extra Stuff");
    vExtras.push_back("F1 - Show Help");
    vExtras.push_back("F2 - Save Current State (Unstable)");
    vExtras.push_back("F3 - Load Saved State (Unstable)");

    vTools.push_back("TOOLS");
    vTools.push_back("USE LEFT MOUSE BUTTON TO USE");
    vTools.push_back("A - Magnetize (Hold Shift to Repel)");
    vTools.push_back("B - Set Bounciness");
    vTools.push_back("C - Copy");
    vTools.push_back("D - Destroy (Hold Shift for Multiple)");
    vTools.push_back("E - Wheel Creator");
    vTools.push_back("F - Follow Object");
    vTools.push_back("G - Set Gravity (Doesn't Save)");
    vTools.push_back("H - Hinge (Static to Dynamic)");
    vTools.push_back("K - Key Control (Use Arrow Keys to Move)");
    vTools.push_back("L - Liquify");
    vTools.push_back("M - Move Object (Use Arrow Keys to Rotate)");
    vTools.push_back("N - No Collide (Doesn't Save)");
    vTools.push_back("O - Rocket Creator");
    vTools.push_back("P - Freeze Playground");
    vTools.push_back("R - Reset Playground");
    vTools.push_back("S - Spring Creator");
    vTools.push_back("T - Auto Spin (Hold Shift to Spin Opposite Way)");
    vTools.push_back("V - Reset View");
    vTools.push_back("W - Weld Objects");
    vTools.push_back("Z - Zoom");

    char intro[21];
    sprintf(intro,"Gamedata/intro%i.plg",(int)rand()%6+1);
    LoadPlayground(intro);

    //************************************************************************
    //
    // MAIN LOOP OF THE PROGRAM STARTS HERE
    //
    //************************************************************************
    while (!bQuit) {
      /* check for messages */
      if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) && ctick<nctick) {
        /* handle or dispatch messages */
        if (msg.message==WM_QUIT) {
          bQuit = 1;
        } else {
          TranslateMessage (&msg);
          DispatchMessage (&msg);
        }
        ctick=GetTickCount();
      } else {
          //-----------------------------------------------------------------
          //UPDATE THE PHYSICS ENGINE
          //-----------------------------------------------------------------
          if (pause)g.UpdateBodies(0);

          //-----------------------------------------------------------------
          //CONTROL THE NEXT ITERATION TIME
          //-----------------------------------------------------------------
          nctick+=(spint);

          //-----------------------------------------------------------------
          //GET THE WINDOW INFORMATION
          //-----------------------------------------------------------------
          GetClientRect(hWnd,&window);
          RECT tmp;

          GetWindowRect(hWnd,&tmp);
          GetCursorPos(&mouse);
          ScreenToClient(hWnd,&mouse);

          mouse.x/=((float)window.right/view.view_w[0]>0)?(float)window.right/view.view_w[0]:1;
          mouse.y/=((float)window.bottom/view.view_h[0]>0)?(float)window.bottom/view.view_h[0]:1;

          scr_mouse.x = mouse.x+view.view_x[0];
          scr_mouse.y = mouse.y+view.view_y[0];

          //-----------------------------------------------------------------
          //CONTROL GLOBAL KEY PRESSES
          //-----------------------------------------------------------------
          if (GetAsyncKeyState(VK_ESCAPE)) {
            break;
          }

          if (GetAsyncKeyState('1')) shapeid=1; //RECTANGLE
          if (GetAsyncKeyState('2')) shapeid=0; //CIRCLE
          if (GetAsyncKeyState('3')) shapeid=3; //TRIANGLE
          if (GetAsyncKeyState('4')) shapeid=2; //LINE (STATIC)
          if (GetAsyncKeyState('5')) shapeid=6; //CAPSULE
          if (GetAsyncKeyState('6')) shapeid=5; //TERRAIN
          if (GetAsyncKeyState('7')) shapeid=4; //ROPE BRIDGE
          if (GetAsyncKeyState('8')) shapeid=7; //PARTICLE
          if (GetAsyncKeyState('9')) shapeid=8; //WATER

          if (GetAsyncKeyState('M')) toolid = 0;  //MOVE
          if (GetAsyncKeyState('W')) toolid = 1;  //WELD
          if (GetAsyncKeyState('H')) toolid = 2;  //HINGE
          if (GetAsyncKeyState('D')) toolid = 3;  //DESTROY
          if (GetAsyncKeyState('E')) toolid = 4;  //WHEEL CREATOR
          if (GetAsyncKeyState('K')) toolid = 5;  //KEY CONTROL
          if (GetAsyncKeyState('F')) toolid = 6;  //FOLLOW VIEW
          if (GetAsyncKeyState('A')) toolid = 7;  //MAGNETIZE
          if (GetAsyncKeyState('G')) toolid = 8;  //SET GRAVITY
          if (GetAsyncKeyState('C')) toolid = 9;  //COPY
          if (GetAsyncKeyState('N')) toolid = 10; //NO COLLIDE
          if (GetAsyncKeyState('T')) toolid = 11; //AUTOSPIN
          if (GetAsyncKeyState('S')) toolid = 12; //SPRING CREATOR
          if (GetAsyncKeyState('B')) toolid = 13; //BOUNCYNESS
          if (GetAsyncKeyState('L')) toolid = 14; //LIQUIFY
          if (GetAsyncKeyState('O')) toolid = 15; //ROCKET CREATOR

          if (GetAsyncKeyState('P')) { //PASUE PLAYGROUND
            if (pcurrent==0) {
              SetPause(pause);
              pause=!pause;
              pcurrent=1;
            }
          } else {
            pcurrent=0;
          }

          if (GetAsyncKeyState('R')) { //RESTART PLAYGROUND
            RestartPlayground();
          }

          if (GetAsyncKeyState('V')) { //RESET VIEW
            view.SetView(0,0,5920,view.view_w[0],view.view_h[0]);
          }

          if (GetAsyncKeyState('Z')) { //ZOOM VIEW CONTROLLER
            if (zoompress==0) {
              if (view.view_w[0]<=1440) {
                view.view_w[0]*=1.5;
                view.view_h[0]*=1.5;
              } else {
                //view.view_x[0]-=view.view_w[0]+640;
                view.view_y[0]+=view.view_h[0]-480;
                view.view_w[0]=640;
                view.view_h[0]=480;
              }
              zoompress=1;
            }
          } else zoompress = 0;


          //-----------------------------------------------------------------
          //CONTROL MOUSE EVENTS
          //-----------------------------------------------------------------
          if (GetAsyncKeyState(VK_LBUTTON)) {
            if (toolid==0) {
              if (t1id==WORLD) {
                NearestObject(scr_mouse.x,scr_mouse.y,&t1id,1);
                if (t1id!=WORLD) SetBodyActor(vDynamic[t1id]->id, 1);
              } else {
                if (pause) {
                  if (vDynamic[t1id]->mass!=ACTOR)
                    MoveActorPosition(vDynamic[t1id]->id,scr_mouse.x,scr_mouse.y);
                  else SetBodyPosition(vDynamic[t1id]->id,scr_mouse.x,scr_mouse.y);
                }else SetBodyPosition(vDynamic[t1id]->id,scr_mouse.x,scr_mouse.y);
                if (GetAsyncKeyState(VK_RIGHT)) SetBodyRotation(vDynamic[t1id]->id,GetBodyRotation(vDynamic[t1id]->id)-1);
                if (GetAsyncKeyState(VK_LEFT)) SetBodyRotation(vDynamic[t1id]->id,GetBodyRotation(vDynamic[t1id]->id)+1);
              }
            }
            if (toolid==1 || toolid==2) {  //JOINT TOOL
              if (toolx==-1000 && tooly==-1000) {
                toolx=scr_mouse.x; tooly=scr_mouse.y;
              }
              if (t1id==WORLD) {
                NearestObject(scr_mouse.x,scr_mouse.y,&t1id,1);
                ct1id=GetBodyObject(t1id);
              }
            }
            if (toolid==12) {  //SPRING TOOL
              if (toolx==-1000 && tooly==-1000) {
                toolx=scr_mouse.x; tooly=scr_mouse.y;
              }
            }
            if (toolid==3) {  //DESTROYING TOOL
              if (toolx==-1000 && tooly==-1000) {
                toolx=scr_mouse.x; tooly=scr_mouse.y;
              }
              NearestObject(scr_mouse.x,scr_mouse.y,&t1id,0);
              ct1id=GetBodyObject(t1id);
            }

            if (toolid==4) {  //WHEEL TOOL
              if (t1id==WORLD) {
                NearestObject(scr_mouse.x,scr_mouse.y,&t1id,1);
                ct1id=GetBodyObject(t1id);
              }
            }

            if (toolid==5) {  //KEY CONTROL
              if (settingkey==0) {
                NearestObject(scr_mouse.x,scr_mouse.y,&keyid[ckeyid],1);
                keyid[ckeyid] = GetBodyObject(keyid[ckeyid]);
                settingkey=1;
              }
            }

            if (toolid==6) {  //FOLLOW VIEW
              NearestObject(scr_mouse.x,scr_mouse.y,&viewid,1);
              viewid = GetBodyObject(viewid);
            }

            if (toolid==7) {  //MAGNETIZE
              if (t1id==WORLD) {
                NearestObject(scr_mouse.x,scr_mouse.y,&t1id,1);
                if (t1id!=WORLD)ct1id=GetBodyObject(t1id);
              }
            }

            if (toolid==8) {  //GRAVITY CONTROLLER
              if (toolx==-1000 && tooly==-1000) {
                toolx=scr_mouse.x; tooly=scr_mouse.y;
              }
            }

            if (toolid==9) {  //COPYING TOOL
              if (t1id==WORLD) {
                NearestObject(scr_mouse.x,scr_mouse.y,&t1id,1);
                if (t1id!=WORLD)ct1id=GetBodyObject(t1id);
              }
            }

            if (toolid==10) {  //NO COLLIDE TOOL
              if (t1id==WORLD) {
                NearestObject(scr_mouse.x,scr_mouse.y,&t1id,1);
                ct1id=GetBodyObject(t1id);
              }
            }

            if (toolid==11) {  //AUTOSPIN
              if (t1id==WORLD) {
                NearestObject(scr_mouse.x,scr_mouse.y,&t1id,1);
                if (t1id!=WORLD)ct1id=GetBodyObject(t1id);
              }
            }

            if (toolid==13) {  //BOUNCYNESS
              if (t1id==WORLD) {
                NearestObject(scr_mouse.x,scr_mouse.y,&t1id,1);
                if (t1id!=WORLD)ct1id=GetBodyObject(t1id);
              }
            }

            if (toolid==14) { //LIQUIFY
              if (t1id==WORLD) {
                NearestObject(scr_mouse.x,scr_mouse.y,&t1id,1);
                if (t1id!=WORLD)ct1id=GetBodyObject(t1id);
              }
            }

            if (toolid==15) {  //ROCKET CREATOR
              if (toolx==-1000 && tooly==-1000) {
                toolx=scr_mouse.x; tooly=scr_mouse.y;
              }
            }
          } else {
            if (toolid==0) {
              if (t1id!=WORLD) { //MOVING TOOL
                if (vDynamic[t1id]->mass!=ACTOR)SetBodyActor(vDynamic[t1id]->id, 0);
              }
            }
            if (toolid==1) { //WELDING TOOL
              if (ct1id!=WORLD) {
                NearestObject(scr_mouse.x,scr_mouse.y,&t2id,1);
                ct2id = GetBodyObject(t2id);
                if (ct2id!=WORLD && ct1id!=ct2id && (vDynamic[t1id]->mass != STATIC || vDynamic[t2id]->mass != STATIC)) {
                  vJoint.push_back(new Joint(ct1id,ct2id,0));
                  vJoint[vJoint.size()-1]->setColor((rand()%128+128)/255.0,(rand()%128+128)/255.0,(rand()%128+128)/255.0,1);
                  SetBodyCollide(ct1id,ct2id,0);

                  vDynamic.push_back(new Dynamic(-1000,-1000,ACTOR,SHAPE_SPHERE,5));
                  vDynamic[vDynamic.size()-1]->setColor(vJoint[vJoint.size()-1]->getColR(),vJoint[vJoint.size()-1]->getColG(),vJoint[vJoint.size()-1]->getColB(),1);
                  vDynamic[vDynamic.size()-1]->hidden = true;
                  SetBodyResponseEnabled(vDynamic[vDynamic.size()-1]->id,0);
                  vJoint[vJoint.size()-1]->bodyid = vDynamic[vDynamic.size()-1]->id;
                }
              }
            }
            if (toolid==2) { //HINGE TOOL
              if (ct1id!=WORLD) {
                NearestObject(scr_mouse.x,scr_mouse.y,&t2id,1);
                ct2id = GetBodyObject(t2id);
                if (ct2id!=WORLD && ct1id!=ct2id  && (vDynamic[t1id]->mass != STATIC || vDynamic[t2id]->mass != STATIC)) {
                  vJoint.push_back(new Joint(ct1id,ct2id,1));
                  vJoint[vJoint.size()-1]->setColor((rand()%128+128)/255.0,(rand()%128+128)/255.0,(rand()%128+128)/255.0,1);

                  vDynamic.push_back(new Dynamic(-1000,-1000,ACTOR,SHAPE_SPHERE,5));
                  vDynamic[vDynamic.size()-1]->setColor(vJoint[vJoint.size()-1]->getColR(),vJoint[vJoint.size()-1]->getColG(),vJoint[vJoint.size()-1]->getColB(),1);
                  vDynamic[vDynamic.size()-1]->hidden = true;
                  SetBodyResponseEnabled(vDynamic[vDynamic.size()-1]->id,0);
                  vJoint[vJoint.size()-1]->bodyid = vDynamic[vDynamic.size()-1]->id;
                }
              }
            }

            if (toolid==3) { //DESTROYING TOOL ^_^
              if (GetAsyncKeyState(VK_SHIFT)) {
                if (toolx!=-1000 && tooly!=-1000) {
                  RECT r;
                  r.left = MIN(toolx,scr_mouse.x);
                  r.right = MAX(toolx,scr_mouse.x);
                  r.top = MIN(tooly,scr_mouse.y);
                  r.bottom = MAX(tooly,scr_mouse.y);
                  POINT p;
                  for (int i=3;i<(signed)vDynamic.size();i++) {
                    p.x = vDynamic[i]->getX();
                    p.y = vDynamic[i]->getY();
                    if (PointRectCollide(p,r)) {
                      DeleteDynamicObject(i);
                      i-=1;
                    }
                  }
                }
              } else {
                if (t1id!=WORLD) {
                  int tid=t1id;
                  DeleteDynamicObject(tid);
                }
              }
            }

            if (toolid==4) { //WHEEL TOOL
              if (ct1id!=WORLD) {
                NearestObject(scr_mouse.x,scr_mouse.y,&t2id,1);
                ct2id = GetBodyObject(t2id);
                if (ct2id!=WORLD && ct1id!=ct2id) {
                  SetBodyPosition(ct1id,scr_mouse.x,scr_mouse.y);
                  SetBodyCollide(ct1id,ct2id,0);
                  vJoint.push_back(new Joint(ct1id,ct2id,1));
                  vJoint[vJoint.size()-1]->setColor((rand()%128+128)/255.0,(rand()%128+128)/255.0,(rand()%128+128)/255.0,1);
                }
              }
            }

            if (toolid==5) {  //KEY CONTROL TOOL
              if (settingkey==1) {
                settingkey=0;
                ckeyid=!ckeyid;
              }
            }

            if (toolid==7) {  //MAGNETIZE TOOL
              if (ct1id!=WORLD)vDynamic[t1id]->SetMagnet((GetAsyncKeyState(VK_SHIFT) ? -1.0:1.0) * (int)PointDistance(GetBodyX(ct1id),GetBodyY(ct1id),scr_mouse.x,scr_mouse.y)*10);
            }

            if (toolid==8) {  //GRAVITY CONTROL TOOL
              if (toolx!=-1000 && tooly!=-1000) {
                int tgdir = PointDirection(toolx,tooly,scr_mouse.x,scr_mouse.y);
                int tgpow = PointDistance(toolx,tooly,scr_mouse.x,scr_mouse.y);
                tgdir = PointDirection(0,0,(int)-LengthDirX(tgpow,tgdir)/24,(int)LengthDirY(tgpow,tgdir)/24);
                dir = tgdir;
                gpow = (int)tgpow/24;
              }
            }

          if (toolid==9) //COPYING TOOL
            if (ct1id!=WORLD) {
              if (vDynamic[t1id]->type==SHAPE_SPHERE) vDynamic.push_back(new Dynamic(scr_mouse.x,scr_mouse.y,vDynamic[t1id]->mass,vDynamic[t1id]->type,vDynamic[t1id]->getWidth())); else
              if (vDynamic[t1id]->type==SHAPE_LINE || vDynamic[t1id]->type==SHAPE_BOX)vDynamic.push_back(new Dynamic(scr_mouse.x,scr_mouse.y,vDynamic[t1id]->mass,vDynamic[t1id]->type,vDynamic[t1id]->getWidth(),vDynamic[t1id]->getHeight())); else
              if (vDynamic[t1id]->type==SHAPE_CAPSULE) vDynamic.push_back(new Dynamic(scr_mouse.x,scr_mouse.y,vDynamic[t1id]->mass,vDynamic[t1id]->type,vDynamic[t1id]->getHeight(),vDynamic[t1id]->getWidth())); else
              if (vDynamic[t1id]->type==SHAPE_TRIANGLE) vDynamic.push_back(new Dynamic(scr_mouse.x,scr_mouse.y,vDynamic[t1id]->mass,vDynamic[t1id]->type,vDynamic[t1id]->getWidth(),vDynamic[t1id]->getHeight(),vDynamic[t1id]->getRadius()));
              vDynamic[vDynamic.size()-1]->setColor((rand()%128+128)/255.0,(rand()%128+128)/255.0,(rand()%128+128)/255.0,1);
              SetBodyRotation(vDynamic[vDynamic.size()-1]->id,GetBodyRotation(ct1id));
            }

          if (toolid==10)  //NO COLLIDE TOOL
            if (ct1id!=WORLD) {
              NearestObject(scr_mouse.x,scr_mouse.y,&t2id,1);
              ct2id = GetBodyObject(t2id);
              if (ct2id!=WORLD && ct1id!=ct2id) {
                SetBodyCollide(ct1id,ct2id,0);
              }
            }

          if (toolid==11) {  //AUTOPSIN
              if (ct1id!=WORLD)vDynamic[t1id]->autospin = (int)(GetAsyncKeyState(VK_SHIFT)? -1: 1)*PointDistance(GetBodyX(ct1id),GetBodyY(ct1id),scr_mouse.x,scr_mouse.y)*10;
          }

            if (toolid==12) { //SPRING TOOL
              if (toolx!=-1000 || tooly!=-1000) {
                NearestObject(toolx,tooly,&t1id,1);
                ct1id = GetBodyObject(t1id);
                NearestObject(scr_mouse.x,scr_mouse.y,&t2id,1);
                ct2id = GetBodyObject(t2id);
                if (!(ct1id==WORLD && ct2id==WORLD) && ct1id!=ct2id) {
                  vSpring.push_back(new Spring(ct1id,ct2id,toolx,tooly,scr_mouse.x,scr_mouse.y));
                  vSpring[vSpring.size()-1]->setColor((rand()%128+128)/255.0,(rand()%128+128)/255.0,(rand()%128+128)/255.0,1);

                  vDynamic.push_back(new Dynamic((toolx+scr_mouse.x)/2,(tooly+scr_mouse.y)/2,ACTOR,SHAPE_SPHERE,5));
                  vDynamic[vDynamic.size()-1]->setColor(vSpring[vSpring.size()-1]->getColR(),vSpring[vSpring.size()-1]->getColG(),vSpring[vSpring.size()-1]->getColB(),1);
                  vDynamic[vDynamic.size()-1]->hidden = true;
                  SetBodyResponseEnabled(vDynamic[vDynamic.size()-1]->id,0);
                  vSpring[vSpring.size()-1]->bodyid = vDynamic[vDynamic.size()-1]->id;
                }
              }
            }

            if (toolid==13) {  //BONCIENESS
              if (ct1id!=WORLD)vDynamic[t1id]->SetBounciness((int)(GetAsyncKeyState(VK_SHIFT)? -1: 1)*PointDistance(GetBodyX(ct1id),GetBodyY(ct1id),scr_mouse.x,scr_mouse.y)/100);
            }

            if (toolid==14) {  //LIQUIFY
              if (ct1id!=WORLD && vDynamic[t1id]->type!=SHAPE_LINE) {
                int ax = vDynamic[t1id]->getWidth()+vDynamic[t1id]->getHeight();
                int ay = ax;
                for (int x=vDynamic[t1id]->getX()-ax;x<vDynamic[t1id]->getX()+ax;x+=16) {
                  for (int y=vDynamic[t1id]->getY()-ay;y<vDynamic[t1id]->getY()+ay;y+=16) {
                    POINT p; p.x=x; p.y=y;
                    if (PointInObject(p,t1id)!=WORLD) {
                      vDynamic.push_back(new Dynamic(x,y,.01,SHAPE_FLUID, 6));
                      vDynamic[vDynamic.size()-1]->setColor((rand()%128+128)/255.0,(rand()%128+128)/255.0,(rand()%128+128)/255.0,1);
                      SetBodySolverCount(vDynamic[vDynamic.size()-1]->id,1);
                      SetBodyMaterial(vDynamic[vDynamic.size()-1]->id,100,100,0);
                    }
                  }
                }
                DeleteDynamicObject(t1id);
              }
            }

            if (toolid==15) { //ROCKET CREATOR
              if (toolx!=-1000 && tooly!=-1000) {
                NearestObject(toolx,tooly,&t1id,1);
                ct1id=GetBodyObject(t1id);
                if (ct1id!=WORLD) {
                  vDynamic.push_back(new Dynamic(toolx,tooly,1,SHAPE_SPHERE,16));
                  vDynamic[vDynamic.size()-1]->setColor(1.0,1.0,1.0,1.0);
                  vDynamic[vDynamic.size()-1]->SetAutoForce(toolx-scr_mouse.x,tooly-scr_mouse.y);
                  SetBodyCollide(ct1id,vDynamic[vDynamic.size()-1]->id,0);
                  vJoint.push_back(new Joint(vDynamic[vDynamic.size()-1]->id,ct1id,1));
                  vJoint[vJoint.size()-1]->setColor(0,0,0,0);
                }
              }
            }

            ct1id=WORLD; ct2id=WORLD; t1id=WORLD; t2id=WORLD;
            toolx = -1000;
            tooly = -1000;
          }

          if (GetAsyncKeyState(VK_RBUTTON)) {  //DRAWING ALL THE SHAPES
            if (tsx==-1000 && tsy==-1000) {
              tsx=scr_mouse.x; tsy=scr_mouse.y;
            }
            if (shapeid==7) { //FLUID PARTICLE
              vDynamic.push_back(new Dynamic(scr_mouse.x,scr_mouse.y,.01,SHAPE_FLUID, 6));
              vDynamic[vDynamic.size()-1]->setColor((rand()%128+128)/255.0,(rand()%128+128)/255.0,(rand()%128+128)/255.0,1);
              SetBodySolverCount(vDynamic[vDynamic.size()-1]->id,1);
              SetBodyMaterial(vDynamic[vDynamic.size()-1]->id,100,100,0);
            }
          } else {
            if (tsx!=-1000 && tsy!=-1000) {
              if (shapeid==0) //CIRCLE
                if ((fabs(tsx-scr_mouse.x)>fabs(tsy-scr_mouse.y)) ? fabs(tsx-scr_mouse.x)/2:fabs(tsy-scr_mouse.y)/2>4) {
                  if (!GetAsyncKeyState(VK_CONTROL)) {
                    vDynamic.push_back(new Dynamic(tsx+(scr_mouse.x-tsx)/2.0,tsy+(scr_mouse.y-tsy)/2.0,GetAsyncKeyState(VK_SHIFT) ? ACTOR : 1,SHAPE_SPHERE,fabs(tsx-scr_mouse.x)>fabs(tsy-scr_mouse.y) ? fabs(tsx-scr_mouse.x)/2:fabs(tsy-scr_mouse.y)/2));
                    vDynamic[vDynamic.size()-1]->setColor((rand()%128+128)/255.0,(rand()%128+128)/255.0,(rand()%128+128)/255.0,1);
                  } else {
                    float r = (fabs(tsx-scr_mouse.x)>fabs(tsy-scr_mouse.y)) ? fabs(tsx-scr_mouse.x)/2:fabs(tsy-scr_mouse.y)/2;
                    vBlob.push_back(new Blob(tsx+(scr_mouse.x-tsx)/2.0,tsy+(scr_mouse.y-tsy)/2.0,r,r/1.5));

                    vDynamic.push_back(new Dynamic(tsx+(scr_mouse.x-tsx)/2.0,tsy+(scr_mouse.y-tsy)/2.0,1,SHAPE_SPHERE,r));
                    SetBodyGravityEnabled(vDynamic[vDynamic.size()-1]->id,0);
                    SetBodyResponseEnabled(vDynamic[vDynamic.size()-1]->id,0);
                    vDynamic[vDynamic.size()-1]->setColor(0,0,0,0);

                    vBlob[vBlob.size()-1]->bodyid=vDynamic[vDynamic.size()-1]->id;
                  }
                }

              if (shapeid==1) //RECTANGLE
                if (scr_mouse.x-tsx!=0 && scr_mouse.y-tsy!=0) {
                  int minx,miny;
                  minx = min(tsx,scr_mouse.x);
                  miny = min(tsy,scr_mouse.y);
                  vDynamic.push_back(new Dynamic(minx+fabs(scr_mouse.x-tsx)/2,miny+fabs(scr_mouse.y-tsy)/2,GetAsyncKeyState(VK_SHIFT) ? ACTOR : 1,SHAPE_BOX,fabs(scr_mouse.x-tsx),fabs(scr_mouse.y-tsy)));
                  vDynamic[vDynamic.size()-1]->setColor((rand()%128+128)/255.0,(rand()%128+128)/255.0,(rand()%128+128)/255.0,1);
                }

              if (shapeid==2) //STATIC LINE
                if (scr_mouse.x-tsx!=0 || scr_mouse.y-tsy!=0) {
                  vDynamic.push_back(new Dynamic(tsx,tsy,STATIC, SHAPE_LINE, scr_mouse.x, scr_mouse.y));
                  vDynamic[vDynamic.size()-1]->setColor((rand()%128+128)/255.0,(rand()%128+128)/255.0,(rand()%128+128)/255.0,1);
                }

              if (shapeid==3) //TRIANGLE
                if (scr_mouse.x-tsx!=0 || scr_mouse.y-tsy!=0) {
                  int minx,miny;
                  minx = min(tsx,scr_mouse.x);
                  miny = min(tsy,scr_mouse.y);
                  vDynamic.push_back(new Dynamic(minx+fabs(scr_mouse.x-tsx)/2,miny+fabs(scr_mouse.y-tsy)/2,GetAsyncKeyState(VK_SHIFT) ? ACTOR : 1,SHAPE_TRIANGLE,fabs(scr_mouse.x-tsx),fabs(scr_mouse.y-tsy),0));
                  vDynamic[vDynamic.size()-1]->setColor((rand()%128+128)/255.0,(rand()%128+128)/255.0,(rand()%128+128)/255.0,1);
                }

              if (shapeid==4) //ROPE
                if (scr_mouse.x-tsx!=0 || scr_mouse.y-tsy!=0) {
                  CreateRope(WORLD,WORLD,tsx,tsy,scr_mouse.x,scr_mouse.y);
                }

              if (shapeid==5) //TERRAIN
                if (fabs((float)(int)scr_mouse.x-tsx)>5 && fabs((float)(int)scr_mouse.y-tsy)>5) {
                  CreateTerrain(tsx,tsy,scr_mouse.x,scr_mouse.y);
                }

              if (shapeid==6) //CAPSULE
                if (fabs(tsx-scr_mouse.x)>fabs(tsy-scr_mouse.y) ? fabs(tsx-scr_mouse.x)/2:fabs(tsy-scr_mouse.y)/2>16) {
                  vDynamic.push_back(new Dynamic(tsx+(scr_mouse.x-tsx)/2.0,tsy+(scr_mouse.y-tsy)/2.0,GetAsyncKeyState(VK_SHIFT) ? ACTOR : 1, SHAPE_CAPSULE, fabs(scr_mouse.y-tsy),fabs(scr_mouse.x-tsx)));
                  vDynamic[vDynamic.size()-1]->setColor((rand()%128+128)/255.0,(rand()%128+128)/255.0,(rand()%128+128)/255.0,1);
                }

              if (shapeid==8) //Water
                if (scr_mouse.x-tsx!=0 || scr_mouse.y-tsy!=0 || GetAsyncKeyState(VK_SHIFT)) {
                  int minx,miny;
                  minx = min(tsx,scr_mouse.x);
                  miny = min(tsy,scr_mouse.y);
                  if (GetAsyncKeyState(VK_SHIFT)) {
                    minx = 0; miny = scr_mouse.y; tsx=64000; tsy=6400-miny;
                    vWater.push_back(new Water(0,scr_mouse.y,64000,6400));
                  } else vWater.push_back(new Water(minx,miny,minx+fabs(scr_mouse.x-tsx),miny+fabs(scr_mouse.y-tsy)));
                  vWater[vWater.size()-1]->setColor((rand()%128+128)/255.0,(rand()%128+128)/255.0,(rand()%128+128)/255.0,.25);

                  vDynamic.push_back(new Dynamic(minx+fabs(scr_mouse.x-tsx)/2,miny+fabs(scr_mouse.y-tsy)/2,STATIC,SHAPE_BOX,fabs(scr_mouse.x-tsx),fabs(scr_mouse.y-tsy)));
                  vDynamic[vDynamic.size()-1]->setColor(0,0,0,0);
                  vDynamic[vDynamic.size()-1]->hidden = true;
                  SetBodyResponseEnabled(vDynamic[vDynamic.size()-1]->id,0);

                  vWater[vWater.size()-1]->bodyid=vDynamic[vDynamic.size()-1]->id;
                }

              tsx = -1000;
              tsy = -1000;
            }
          }

          if (GetAsyncKeyState(VK_RIGHT)) {
            if (keyid[0]!=WORLD)AddTorque(keyid[0], 400, 0);
            if (keyid[1]!=WORLD)AddTorque(keyid[1], 400, 0);
          }

          if (GetAsyncKeyState(VK_LEFT)) {
            if (keyid[0]!=WORLD)AddTorque(keyid[0], -400, 0);
            if (keyid[1]!=WORLD)AddTorque(keyid[1], -400, 0);
          }

          //-----------------------------------------------------------------
          //CONTROL GRAVITY
          //-----------------------------------------------------------------
          SetGravity(-cos((pi/180)*-dir)*gpow,-sin((pi/180)*-dir)*gpow);

          //-----------------------------------------------------------------
          //CONTROL VIEW
          //-----------------------------------------------------------------
          float spd = 5;
          if (GetAsyncKeyState(VK_CONTROL)) spd += 10;
          if (GetAsyncKeyState(VK_SHIFT)) spd += 5;
          if (mouse.x>view.view_w[0]-8)view.SetView(0,view.view_x[0]+spd*view.view_w[0]/640,view.view_y[0],view.view_w[0],view.view_h[0]);
          if (mouse.x<+8)view.SetView(0,view.view_x[0]-spd*view.view_w[0]/640,view.view_y[0],view.view_w[0],view.view_h[0]);
          if (mouse.y>+view.view_h[0]-8)view.SetView(0,view.view_x[0],view.view_y[0]+spd*view.view_h[0]/480,view.view_w[0],view.view_h[0]);
          if (mouse.y<+8)view.SetView(0,view.view_x[0],view.view_y[0]-spd*view.view_h[0]/480,view.view_w[0],view.view_h[0]);
          if (viewid!=WORLD)view.KeepInView(0,GetBodyX(viewid),GetBodyY(viewid));
          if (view.view_y[0]>6400-view.view_h[0])view.view_y[0]=6400-view.view_h[0];
          if (view.view_y[0]<0)view.view_y[0]=0;
          if (view.view_x[0]<0)view.view_x[0]=0;
          if (view.view_x[0]>64000-view.view_w[0])view.view_x[0]=64000-view.view_w[0];

          //-----------------------------------------------------------------
          // EVERYTHING IS DRAWN HERE
          //-----------------------------------------------------------------
          glClearColor (0.0f, 0.0f, 0.0f, 1.0f);
          glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          glLoadIdentity();

          int w=window.right-window.left==0 ? 2:(window.right-window.left);
          int h=window.bottom-window.left==0 ? 2:(window.bottom-window.left);

          view.SetViewPort(-1,0,0,w,h);  //Regular View Port
          view.Update();

          int vx = ceil(view.view_x[0]/64)*64,vy = ceil(view.view_y[0]/64)*64;

          for (int x=vx;x<=vx+view.view_w[0];x+=64) {
            if (x%64==0)glColor3f(0.1,0.1,0.1);
            if (x%128==0)glColor3f(0.3,0.3,0.3);
            if (x%256==0)glColor3f(0.5,0.5,0.5);
            DrawLine(x,vy-64,x,vy+view.view_h[0]+64);
          }

          for (int y=vy;y<=vy+view.view_h[0];y+=64) {
            if (y%64==0)glColor3f(0.1,0.1,0.1);
            if (y%128==0)glColor3f(0.3,0.3,0.3);
            if (y%256==0)glColor3f(0.5,0.5,0.5);
            DrawLine(vx-64,y,vx+view.view_w[0]+64,y);
          }

          for (int i=0;i<(signed)vBlob.size();i++) {
            if (vBlob[i]->popped) {
              int blobid = GetClassObject(vBlob[i]->bodyid);
              int ax = vDynamic[blobid]->getWidth()+vDynamic[blobid]->getHeight();
              int ay = ax;
              float hsp,vsp;
              hsp = GetBodyHspeed(vBlob[i]->vDynamic[0]->id);
              vsp = GetBodyVspeed(vBlob[i]->vDynamic[0]->id);
              for (int x=vDynamic[blobid]->getX()-ax;x<vDynamic[blobid]->getX()+ax;x+=16) {
                for (int y=vDynamic[blobid]->getY()-ay;y<vDynamic[blobid]->getY()+ay;y+=16) {
                  POINT p; p.x=x; p.y=y;
                  if (PointInObject(p,blobid)!=WORLD) {
                    vDynamic.push_back(new Dynamic(x,y,.01,SHAPE_FLUID, 6));
                    vDynamic[vDynamic.size()-1]->setColor((rand()%128+128)/255.0,(rand()%128+128)/255.0,(rand()%128+128)/255.0,1);
                    SetBodyHspeed(vDynamic[vDynamic.size()-1]->id,hsp);
                    SetBodyVspeed(vDynamic[vDynamic.size()-1]->id,vsp);
                    SetBodySolverCount(vDynamic[vDynamic.size()-1]->id,1);
                    SetBodyMaterial(vDynamic[vDynamic.size()-1]->id,100,100,0);
                  }
                }
              }
              DeleteDynamicObject(blobid);
            }
            if (!BodyExists(vBlob[i]->bodyid)) {
              delete vBlob[i];
              vBlob.erase(vBlob.begin()+i);
              i--;
            } else vBlob[i]->Draw();
          }
          for (int i=0;i<(signed)vJoint.size();i++) {
            if (!BodyExists(vJoint[i]->bodyid) && vJoint[i]->bodyid!=WORLD) {
              delete vJoint[i];
              vJoint.erase(vJoint.begin()+i);
              i--;
            } else vJoint[i]->Draw();
          }
          for (int i=0;i<(signed)vSpring.size();i++) {
            if (!BodyExists(vSpring[i]->bodyid) && vSpring[i]->bodyid!=WORLD) {
              delete vSpring[i];
              vSpring.erase(vSpring.begin()+i);
              i--;
            } else vSpring[i]->Draw();
          }
          for (int i=0;i<(signed)vDynamic.size();i++) vDynamic[i]->Draw();
          for (int i=0;i<(signed)vWater.size();i++) {
            if (!BodyExists(vWater[i]->bodyid)) {
              delete vWater[i];
              vWater.erase(vWater.begin()+i);
              i--;
            } else vWater[i]->Draw();
          }

          glColor4f(1.0,1.0,1.0,1.0);

          if (GetAsyncKeyState(VK_RBUTTON) && tsx>-1000 && tsy>-1000) {
            glColor4f(1.0,1.0,1.0,0.5);
            if (shapeid==0)DrawCircle(tsx+(scr_mouse.x-tsx)/2,tsy+(scr_mouse.y-tsy)/2,fabs(tsx-scr_mouse.x)>fabs(tsy-scr_mouse.y) ? fabs(tsx-scr_mouse.x)/2:fabs(tsy-scr_mouse.y)/2,0);
            if (shapeid==1)DrawRect(tsx,tsy,scr_mouse.x-tsx,scr_mouse.y-tsy,0);
            if (shapeid==2 || shapeid==4)DrawLine(tsx,tsy,scr_mouse.x,scr_mouse.y);
            if (shapeid==3)DrawTriangle(tsx+(scr_mouse.x-tsx)/2,tsy+(scr_mouse.y-tsy)/2,scr_mouse.x-tsx,fabs(scr_mouse.y-tsy),0);
            if (shapeid==5)DrawRect(tsx,tsy,scr_mouse.x-tsx,scr_mouse.y-tsy,0);
            if (shapeid==8)GetAsyncKeyState(VK_SHIFT) ? DrawRect(0,scr_mouse.y,64000,6400,0) : DrawRect(tsx,tsy,scr_mouse.x-tsx,scr_mouse.y-tsy,0);
            if (shapeid==6)DrawCapsule(tsx+(scr_mouse.x-tsx)/2,tsy+(scr_mouse.y-tsy)/2,scr_mouse.x-tsx,scr_mouse.y-tsy,0);
          }

          if (keyid[0]!=WORLD) {
            glColor4f(0,1,0,0.5); DrawCircle(GetBodyX(keyid[0]),GetBodyY(keyid[0]),8,0);
            glColor4f(0,1,0,1.0); DrawCircleOut(GetBodyX(keyid[0]),GetBodyY(keyid[0]),8,0);
          }

          if (keyid[1]!=WORLD) {
            glColor4f(0,1,0,0.5); DrawCircle(GetBodyX(keyid[1]),GetBodyY(keyid[1]),8,0);
            glColor4f(0,1,0,1.0); DrawCircleOut(GetBodyX(keyid[1]),GetBodyY(keyid[1]),8,0);
          }

          if (viewid!=WORLD) {
            glColor4f(0,0,1,0.5);
            DrawCircle(GetBodyX(viewid),GetBodyY(viewid),8,0);
            glColor4f(0,0,1,1.0);
            DrawCircleOut(GetBodyX(viewid),GetBodyY(viewid),8,0);
          }

          if (GetAsyncKeyState(VK_LBUTTON)) {
            if (toolid==1 || toolid==2 || toolid==4 || toolid==10) {
              if (ct1id!=WORLD)DrawLine(GetBodyX(ct1id),GetBodyY(ct1id),scr_mouse.x,scr_mouse.y);
            }

            if (toolid==12)DrawLine(toolx,tooly,scr_mouse.x,scr_mouse.y);

            if (toolid==15) {
              DrawLine(toolx,tooly,scr_mouse.x,scr_mouse.y);
              DrawCircle(toolx,tooly,16,0);
            }

            if (toolid==3) {
              if (GetAsyncKeyState(VK_SHIFT)) {
                glColor4f(1.0,0.25,0.25,0.25);
                DrawRect(toolx,tooly,scr_mouse.x-toolx,scr_mouse.y-tooly,0);
              } else {
                if (ct1id!=WORLD) {
                  glColor4f(1.0,0,0,0.5);
                  DrawCircle(GetBodyX(ct1id),GetBodyY(ct1id),5,0);
                  glColor4f(1.0,0,0,1.0);
                  DrawCircleOut(GetBodyX(ct1id),GetBodyY(ct1id),5,0);
                }
              }
            }
            if (toolid==7 || toolid==13) {
              if (ct1id!=WORLD) {
                DrawLine(GetBodyX(ct1id),GetBodyY(ct1id),scr_mouse.x,scr_mouse.y);
                fnt.glPrint(scr_mouse.x+10,scr_mouse.y,FA_LEFT,"POWER: %.0f",(GetAsyncKeyState(VK_SHIFT) ? -1.0:1.0) * PointDistance(GetBodyX(ct1id),GetBodyY(ct1id),scr_mouse.x,scr_mouse.y)*10);
              }
            }
            if (toolid==8) {
              DrawLine(toolx,tooly,scr_mouse.x,scr_mouse.y);
              int tgdir = PointDirection(toolx,tooly,scr_mouse.x,scr_mouse.y);
              int tgpow = PointDistance(toolx,tooly,scr_mouse.x,scr_mouse.y);
              glColor4f(1.0,1.0,1.0,1.0);
              fnt.glPrint(scr_mouse.x+10,scr_mouse.y,FA_LEFT,"(%i,%i)",(int)-LengthDirX(tgpow,tgdir)/24,(int)LengthDirY(tgpow,tgdir)/24);
            }

            if (toolid==9) {
              if (t1id!=WORLD) {
                float t = vDynamic[t1id]->type;
                glColor4f(1.0,1.0,1.0,0.25);
                if (t==SHAPE_SPHERE) DrawCircle(scr_mouse.x,scr_mouse.y,vDynamic[t1id]->getWidth(),vDynamic[t1id]->getRot());
                if (t==SHAPE_BOX) DrawBox(scr_mouse.x,scr_mouse.y,vDynamic[t1id]->getWidth(),vDynamic[t1id]->getHeight(),vDynamic[t1id]->getRot());
                if (t==SHAPE_LINE) DrawLine(scr_mouse.x-vDynamic[t1id]->getWidth()/2,scr_mouse.y-vDynamic[t1id]->getHeight()/2,scr_mouse.x+vDynamic[t1id]->getWidth()/2,scr_mouse.y+vDynamic[t1id]->getHeight()/2);
                if (t==SHAPE_CAPSULE) DrawCapsule(scr_mouse.x,scr_mouse.y,vDynamic[t1id]->getWidth(),vDynamic[t1id]->getHeight(),vDynamic[t1id]->getRot());
                if (t==SHAPE_TRIANGLE) DrawTriangle(scr_mouse.x,scr_mouse.y,vDynamic[t1id]->getWidth(),vDynamic[t1id]->getHeight(),vDynamic[t1id]->getRot());
              }
            }

            if (toolid==11) {
              if (ct1id!=WORLD) {
                DrawLine(GetBodyX(ct1id),GetBodyY(ct1id),scr_mouse.x,scr_mouse.y);
                fnt.glPrint(scr_mouse.x+10,scr_mouse.y,FA_LEFT,"TORQUE: %.0f",(GetAsyncKeyState(VK_SHIFT) ? -1.0:1.0) * PointDistance(GetBodyX(ct1id),GetBodyY(ct1id),scr_mouse.x,scr_mouse.y)*10);
              }
            }
          }

          char tmpshape[16];
          if (shapeid == 0) sprintf(tmpshape,"Circle");
          if (shapeid == 1) sprintf(tmpshape,"Rectangle");
          if (shapeid == 2) sprintf(tmpshape,"Line (Static)");
          if (shapeid == 3) sprintf(tmpshape,"Triangle");
          if (shapeid == 4) sprintf(tmpshape,"Rope Bridge");
          if (shapeid == 5) sprintf(tmpshape,"Terrain");
          if (shapeid == 6) sprintf(tmpshape,"Capsule");
          if (shapeid == 7) sprintf(tmpshape,"Fluid Particle");
          if (shapeid == 8) sprintf(tmpshape,"Water");

          char tmptool[16];
          if (toolid == 0) sprintf(tmptool,"Move");
          if (toolid == 1) sprintf(tmptool,"Weld");
          if (toolid == 2) sprintf(tmptool,"Hinge");
          if (toolid == 3) sprintf(tmptool,"Destroy");
          if (toolid == 4) sprintf(tmptool,"Make Wheel");
          if (toolid == 5) sprintf(tmptool,"Key Control");
          if (toolid == 6) sprintf(tmptool,"Follow Object");
          if (toolid == 7) sprintf(tmptool,"Magnetize");
          if (toolid == 8) sprintf(tmptool,"Set Gravity");
          if (toolid == 9) sprintf(tmptool,"Copy");
          if (toolid == 10) sprintf(tmptool,"No Collide");
          if (toolid == 11) sprintf(tmptool,"Auto Spin");
          if (toolid == 12) sprintf(tmptool,"Spring Creator");
          if (toolid == 13) sprintf(tmptool,"Set Bounciness");
          if (toolid == 14) sprintf(tmptool,"Liquify");
          if (toolid == 15) sprintf(tmptool,"Rocket Creator");

          char nobj[16];
          char njnt[16];
          sprintf(nobj,"%u",vDynamic.size()-3);
          sprintf(njnt,"%u",vJoint.size());

          view.UpdateHUD();

          glColor3f(0.0,1.0,1.0);
          if (!pause)fnt.glPrint(320,5,FA_CENTER,"X_X -- PLAYGROUND FROZEN -- X_X",tmpshape);

          if (GetAsyncKeyState(VK_F1)) {
            DrawHelp(&fnt);
          }

          if (GetAsyncKeyState(VK_F2)) {
            SavePlayground();
          }

          if (GetAsyncKeyState(VK_F3)) {
            LoadPlayground();
          }

          glColor3f(1.0,1.0,1.0);
          fnt.glPrint(5,5,FA_LEFT,"Shape: %s",tmpshape);
          fnt.glPrint(5,25,FA_LEFT,"Instances: %s",nobj);
          fnt.glPrint(635,5,FA_RIGHT,"Tool: %s",tmptool);

          SwapBuffers(hDC);

          glFlush();

          for (int i=0;i<255;i++) GetAsyncKeyState(i);

          SleepEx(5,false);
        }
      }

    keyid[0] = -1;
    keyid[1] = -1;
    viewid = -1;
    for (int i=3;(unsigned)i<vDynamic.size();i++) {
      delete vDynamic[i];
      vDynamic.erase(vDynamic.begin()+i);
      i-=1;
    }
    for (int i=0;(unsigned)i<vJoint.size();i++) {
      delete vJoint[i];
      vJoint.erase(vJoint.begin()+i);
      i-=1;
    }
    for (int i=0;(unsigned)i<vSpring.size();i++) {
      delete vSpring[i];
      vSpring.erase(vSpring.begin()+i);
      i-=1;
    }

    // shutdown OpenGL
    DisableOpenGL (hWnd, hDC, hRC);

    // free libraries
    g.ReleasePhysics();
    FreeLibrary(physx);

    // destroy the window explicitly
    DestroyWindow (hWnd);

    // say that all went well and shut 'er down
    return msg.wParam;
}

/********************
 * Draw Help
 *
 ********************/
void DrawHelp(glFont* fnt) {
  glColor4f(0.0,0.0,0.0,0.75);
  DrawRect(0,0,640,480,0);
  glColor4f(1.0,1.0,1.0,1.0);
  int sx = 20, sy = 76;
  int tx = 320, ty = 76;
  int ex = 20, ey;

  fnt->glPrint(320,16,FA_CENTER,"- HELP MENU -");

  for (int i=0;i<(signed)vShapes.size();i++) {
    fnt->glPrint(sx+5,sy+i*16,FA_LEFT,vShapes[i]);
  }

  ey = 76+vShapes.size()*16+16;

  for (int i=0;i<(signed)vExtras.size();i++) {
    fnt->glPrint(ex+5,ey+i*16,FA_LEFT,vExtras[i]);
  }

  for (int i=0;i<(signed)vTools.size();i++) {
    fnt->glPrint(tx+5,ty+i*16,FA_LEFT,vTools[i]);
  }
}

/********************
 * Save Playground
 *
 ********************/
bool SavePlayground() {
  fstream tsave("savetmp.plg", ios_base::out | ios_base::binary);

  if (tsave.is_open()) {
    SaveDynamic sdyn;
    SaveJoint sjnt;
    SaveSpring sspr;
    SaveWater swtr;
    SaveBlob sblb;
    int numdyn=vDynamic.size();
    int numjnt=vJoint.size();
    int numspr=vSpring.size();
    int numwtr=vWater.size();
    int numblb=vBlob.size();
    int tmp;

    tsave.write((const char*)&numdyn,sizeof(int));
    tsave.write((const char*)&numjnt,sizeof(int));
    tsave.write((const char*)&numspr,sizeof(int));
    tsave.write((const char*)&numwtr,sizeof(int));
    tsave.write((const char*)&numblb,sizeof(int));
    tmp = GetClassObject(keyid[0]);
    tsave.write((const char*)&tmp,sizeof(int));
    tmp = GetClassObject(keyid[1]);
    tsave.write((const char*)&tmp,sizeof(int));
    tmp = GetClassObject(viewid);
    tsave.write((const char*)&tmp,sizeof(int));

    for (int i=0;i<(signed)vDynamic.size();i++) {
      sdyn.type = vDynamic[i]->type;
      sdyn.x = vDynamic[i]->getX();
      sdyn.y = vDynamic[i]->getY();
      sdyn.a1 = vDynamic[i]->getWidth();
      sdyn.a2 = vDynamic[i]->getHeight();
      sdyn.a3 = vDynamic[i]->getRadius();
      sdyn.hsp = vDynamic[i]->getHsp();
      sdyn.vsp = vDynamic[i]->getVsp();
      sdyn.rotsp = vDynamic[i]->getRsp();
      sdyn.rot = vDynamic[i]->getRot();
      sdyn.mass = vDynamic[i]->mass;
      sdyn.r = vDynamic[i]->getColR();
      sdyn.g = vDynamic[i]->getColG();
      sdyn.b = vDynamic[i]->getColB();
      sdyn.a = vDynamic[i]->getColA();
      sdyn.autospin = vDynamic[i]->autospin;
      sdyn.hidden = vDynamic[i]->hidden;
      sdyn.magnet = vDynamic[i]->magnet;
      sdyn.bounciness = vDynamic[i]->restitution;
      
      tsave.write((const char*)&sdyn, sizeof(SaveDynamic));
    }

    for (int i=0;i<(signed)vJoint.size();i++) {
      sjnt.type = vJoint[i]->type;
      sjnt.b1 = (int)GetClassObject(vJoint[i]->b1);
      sjnt.b2 = (int)GetClassObject(vJoint[i]->b2);
      sjnt.x = vJoint[i]->x;
      sjnt.y = vJoint[i]->y;
      sjnt.r = vJoint[i]->getColR();
      sjnt.g = vJoint[i]->getColG();
      sjnt.b = vJoint[i]->getColB();
      sjnt.bodyid = GetClassObject(vJoint[i]->bodyid);
      tsave.write((const char*)&sjnt, sizeof(SaveJoint));
    }

    for (int i=0;i<(signed)vSpring.size();i++) {
      sspr.b1 = (int)GetClassObject(vSpring[i]->b1);
      sspr.b2 = (int)GetClassObject(vSpring[i]->b2);
      sspr.len = (int)vSpring[i]->len;
      sspr.x1 = GetSpringX(vSpring[i]->id,0);
      sspr.x2 = GetSpringX(vSpring[i]->id,1);
      sspr.y1 = GetSpringY(vSpring[i]->id,0);
      sspr.y2 = GetSpringY(vSpring[i]->id,1);
      sspr.r = vSpring[i]->getColR();
      sspr.g = vSpring[i]->getColG();
      sspr.b = vSpring[i]->getColB();
      sspr.minf = vSpring[i]->minforce;
      sspr.maxf = vSpring[i]->maxforce;
      sspr.bodyid = GetClassObject(vSpring[i]->bodyid);
      tsave.write((const char*)&sspr, sizeof(SaveSpring));
    }

    for (int i=0;i<(signed)vWater.size();i++) {
      swtr.x = vWater[i]->x;
      swtr.y = vWater[i]->y;
      swtr.width = vWater[i]->width;
      swtr.height = vWater[i]->height;
      swtr.r = vWater[i]->_r;
      swtr.g = vWater[i]->_g;
      swtr.b = vWater[i]->_b;
      swtr.bodyid = GetClassObject(vWater[i]->bodyid);
      tsave.write((const char*)&swtr, sizeof(SaveWater));
    }

    for (int i=0;i<(signed)vBlob.size();i++) {
      sblb.bodyid = vBlob[i]->bodyid;
      sblb.x = vBlob[i]->x;
      sblb.y = vBlob[i]->y;
      sblb.rad = vBlob[i]->rad;
      sblb.res = vBlob[i]->res;
      sblb.r = vBlob[i]->r;
      sblb.g = vBlob[i]->g;
      sblb.b = vBlob[i]->b;
      sblb.r2 = vBlob[i]->r2;
      sblb.g2 = vBlob[i]->g2;
      sblb.b2 = vBlob[i]->b2;
      sblb.bodyid = GetClassObject(vBlob[i]->bodyid);
      sblb.numobj = vBlob[i]->vDynamic.size();

      tsave.write((const char*)&sblb, sizeof(SaveBlob));

      for (int j=0;j<(signed)sblb.numobj;j++) {
        sdyn.type = vBlob[i]->vDynamic[j]->type;
        sdyn.x = vBlob[i]->vDynamic[j]->getX();
        sdyn.y = vBlob[i]->vDynamic[j]->getY();
        sdyn.a1 = vBlob[i]->vDynamic[j]->getWidth();
        sdyn.a2 = vBlob[i]->vDynamic[j]->getHeight();
        sdyn.a3 = vBlob[i]->vDynamic[j]->getRadius();
        sdyn.hsp = vBlob[i]->vDynamic[j]->getHsp();
        sdyn.vsp = vBlob[i]->vDynamic[j]->getVsp();
        sdyn.rotsp = vBlob[i]->vDynamic[j]->getRsp();
        sdyn.rot = vBlob[i]->vDynamic[j]->getRot();
        sdyn.mass = vBlob[i]->vDynamic[j]->mass;
        sdyn.r = vBlob[i]->vDynamic[j]->getColR();
        sdyn.g = vBlob[i]->vDynamic[j]->getColG();
        sdyn.b = vBlob[i]->vDynamic[j]->getColB();
        sdyn.a = (vBlob[i]->vDynamic[j]->hidden) ? 0 : 1;
        sdyn.autospin = vBlob[i]->vDynamic[j]->autospin;
        sdyn.hidden = vBlob[i]->vDynamic[j]->hidden;
        sdyn.magnet = vBlob[i]->vDynamic[j]->magnet;
        sdyn.bounciness = vBlob[i]->vDynamic[j]->restitution;

        tsave.write((const char*)&sdyn, sizeof(SaveDynamic));
      }
    }

    tsave.close();
  } else return 0;
  return 1;
}

/********************
 * Load Playground
 *
 ********************/
bool LoadPlayground(char fname[128]) {
  RestartPlayground();

  ifstream topen(fname, ios_base::out | ios_base::binary);

  if (topen.is_open()) {
    SaveDynamic sdyn;
    SaveJoint sjnt;
    SaveSpring sspr;
    SaveWater swtr;
    SaveBlob sblb;
    int numdyn;
    int numjnt;
    int numspr;
    int numwtr;
    int numblb;
    int tmp0,tmp1;

    topen.read((char*)&numdyn,sizeof(int));
    topen.read((char*)&numjnt,sizeof(int));
    topen.read((char*)&numspr,sizeof(int));
    topen.read((char*)&numwtr,sizeof(int));
    topen.read((char*)&numblb,sizeof(int));
    topen.read((char*)&tmp0,sizeof(int));
    topen.read((char*)&tmp1,sizeof(int));
    topen.read((char*)&viewid,sizeof(int));

    g.UpdateBodies(0);

    for(int i=0;i<numdyn;i++) {
      topen.read((char*)&sdyn,sizeof(SaveDynamic));
      if (topen.eof())break;
      if (sdyn.type==SHAPE_SPHERE  || sdyn.type==SHAPE_FLUID)vDynamic.push_back(new Dynamic(sdyn.x,sdyn.y,sdyn.mass,sdyn.type,sdyn.a1)); else
      if (sdyn.type==SHAPE_LINE)vDynamic.push_back(new Dynamic(sdyn.x-sdyn.a1/2,sdyn.y-sdyn.a2/2,sdyn.mass,sdyn.type,sdyn.x+sdyn.a1/2,sdyn.y+sdyn.a2/2)); else
      if (sdyn.type==SHAPE_BOX)vDynamic.push_back(new Dynamic(sdyn.x,sdyn.y,sdyn.mass,sdyn.type,sdyn.a1,sdyn.a2)); else
      if (sdyn.type==SHAPE_CAPSULE) vDynamic.push_back(new Dynamic(sdyn.x,sdyn.y,sdyn.mass,sdyn.type,sdyn.a2,sdyn.a1)); else
      if (sdyn.type==SHAPE_TRIANGLE) vDynamic.push_back(new Dynamic(sdyn.x,sdyn.y,sdyn.mass,sdyn.type,sdyn.a1,sdyn.a2,sdyn.a3));
      vDynamic[i]->setColor(sdyn.r,sdyn.g,sdyn.b,sdyn.a);
      vDynamic[i]->SetMagnet(sdyn.magnet);
      vDynamic[i]->SetHidden(sdyn.hidden);
      vDynamic[i]->SetBounciness(sdyn.bounciness);
      SetBodyRotation(vDynamic[vDynamic.size()-1]->id,sdyn.rot);
      SetBodyHspeed(vDynamic[vDynamic.size()-1]->id,sdyn.hsp);
      SetBodyVspeed(vDynamic[vDynamic.size()-1]->id,sdyn.vsp);
      SetBodyRotSpeed(vDynamic[vDynamic.size()-1]->id,sdyn.rotsp);
      vDynamic[i]->autospin = sdyn.autospin;
    }

    keyid[0]=GetBodyObject(tmp0);
    keyid[1]=GetBodyObject(tmp1);
    viewid=GetBodyObject(viewid);

    for (int i=0;i<numjnt;i++) {
      topen.read((char*)&sjnt,sizeof(SaveJoint));
      if (topen.eof())break;
      vJoint.push_back(new Joint(GetBodyObject(sjnt.b1),GetBodyObject(sjnt.b2),sjnt.type,sjnt.x,sjnt.y));
      if (sjnt.b1 != WORLD && sjnt.b2 !=WORLD) SetBodyCollide(GetBodyObject(sjnt.b1), GetBodyObject(sjnt.b2), false);
      vJoint[vJoint.size()-1]->setColor(sjnt.r,sjnt.g,sjnt.b,1);
      vJoint[vJoint.size()-1]->bodyid=GetBodyObject(sjnt.bodyid);
      if (vJoint[i]->bodyid!=WORLD)SetBodyResponseEnabled(vJoint[i]->bodyid,0);
    }

    for (int i=0;i<numspr;i++) {
      topen.read((char*)&sspr,sizeof(SaveSpring));
      vSpring.push_back(new Spring(GetBodyObject(sspr.b1),GetBodyObject(sspr.b2),sspr.len,sspr.x1,sspr.y1,sspr.x2,sspr.y2,sspr.minf,sspr.maxf));
      vSpring[vSpring.size()-1]->setColor(sspr.r,sspr.g,sspr.b,1);
      vSpring[vSpring.size()-1]->bodyid=GetBodyObject(sspr.bodyid);
      if (vSpring[i]->bodyid!=WORLD)SetBodyResponseEnabled(vSpring[i]->bodyid,0);
    }

    for (int i=0;i<numwtr;i++) {
      topen.read((char*)&swtr,sizeof(SaveWater));
      vWater.push_back(new Water(swtr.x,swtr.y,swtr.x+swtr.width,swtr.y+swtr.height));
      vWater[i]->setColor(swtr.r,swtr.g,swtr.b,0.25);
      vWater[i]->bodyid = GetBodyObject(swtr.bodyid);
      if (vWater[i]->bodyid!=WORLD)SetBodyResponseEnabled(vWater[i]->bodyid,0);
    }

    for (int i=0;i<numblb;i++) {
      topen.read((char*)&sblb,sizeof(SaveBlob));

      vBlob.push_back(new Blob(sblb.x,sblb.y,sblb.rad,sblb.res));
      vBlob[i]->bodyid = GetBodyObject(sblb.bodyid);

      SetBodyGravityEnabled(vBlob[i]->bodyid,0);
      SetBodyResponseEnabled(vBlob[i]->bodyid,0);
      vDynamic[GetClassObject(vBlob[i]->bodyid)]->setColor(0,0,0,0);

      vBlob[i]->gbxp = GetBodyX(vBlob[i]->bodyid);
      vBlob[i]->gbyp = GetBodyY(vBlob[i]->bodyid);
      vBlob[i]->r = sblb.r; vBlob[i]->g = sblb.g; vBlob[i]->b = sblb.b;
      vBlob[i]->r2 = sblb.r2; vBlob[i]->g2 = sblb.g2; vBlob[i]->b2 = sblb.b2;

      for (int j=0;j<sblb.numobj;j++) {
        topen.read((char*)&sdyn,sizeof(SaveDynamic));

        SetBodyX(vBlob[i]->vDynamic[j]->id,sdyn.x);
        SetBodyY(vBlob[i]->vDynamic[j]->id,sdyn.y);

        vBlob[i]->vDynamic[j]->setColor(sdyn.r,sdyn.g,sdyn.b,sdyn.a);
        vBlob[i]->vDynamic[j]->SetMagnet(sdyn.magnet);
        vBlob[i]->vDynamic[j]->SetHidden(sdyn.hidden);
        vBlob[i]->vDynamic[j]->SetBounciness(sdyn.bounciness);

        SetBodyRotation(vBlob[i]->vDynamic[j]->id,sdyn.rot);
        SetBodyHspeed(vBlob[i]->vDynamic[j]->id,sdyn.hsp);
        SetBodyVspeed(vBlob[i]->vDynamic[j]->id,sdyn.vsp);
        SetBodyRotSpeed(vBlob[i]->vDynamic[j]->id,sdyn.rotsp);
        vBlob[i]->vDynamic[j]->autospin = sdyn.autospin;
      }
    }

    topen.close();
  } else return 0;
  return 1;
}

/********************
 * Delete Object
 *
 ********************/
void DeleteDynamicObject(int id) {
  for (int i=0;(unsigned)i<vJoint.size();i++) {
    if (vJoint[i]->b1==vDynamic[id]->id || vJoint[i]->b2==vDynamic[id]->id) {
      if (vJoint[i]->bodyid!=WORLD) {
        delete vDynamic[GetClassObject(vJoint[i]->bodyid)];
        vDynamic.erase(vDynamic.begin()+GetClassObject(vJoint[i]->bodyid));
      }
      delete vJoint[i];
      vJoint.erase(vJoint.begin()+i);
      i-=1;
    }
  }

  for (int i=0;(unsigned)i<vSpring.size();i++) {
    if (vSpring[i]->b1==vDynamic[id]->id || vSpring[i]->b2==vDynamic[id]->id) {
      if (vSpring[i]->bodyid!=WORLD) {
        delete vDynamic[GetClassObject(vSpring[i]->bodyid)];
        vDynamic.erase(vDynamic.begin()+GetClassObject(vSpring[i]->bodyid));
      }
      delete vSpring[i];
      vSpring.erase(vSpring.begin()+i);
      i-=1;
    }
  }

  if (vDynamic[id]->id==keyid[0]) keyid[0]=-1;
  if (vDynamic[id]->id==keyid[1]) keyid[1]=-1;
  if (vDynamic[id]->id==viewid) viewid=-1;
  delete vDynamic[id];
  vDynamic.erase(vDynamic.begin()+id);
}

void RestartPlayground() {
  keyid[0] = -1;
  keyid[1] = -1;
  viewid = -1;
  ct1id = -1;
  ct2id = -1;
  t1id = -1;
  t2id = -1;
  for (int i=3;(unsigned)i<vDynamic.size();i++) {
    delete vDynamic[i];
    vDynamic.erase(vDynamic.begin()+i);
    i-=1;
  }
  for (int i=0;(unsigned)i<vJoint.size();i++) {
    delete vJoint[i];
    vJoint.erase(vJoint.begin()+i);
    i-=1;
  }
  for (int i=0;(unsigned)i<vSpring.size();i++) {
    delete vSpring[i];
    vSpring.erase(vSpring.begin()+i);
    i-=1;
  }
  for (int i=0;(unsigned)i<vWater.size();i++) {
    delete vWater[i];
    vWater.erase(vWater.begin()+i);
    i-=1;
  }
  for (int i=0;(unsigned)i<vBlob.size();i++) {
    delete vBlob[i];
    vBlob.erase(vBlob.begin()+i);
    i-=1;
  }
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
