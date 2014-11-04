/* Replace "dll.h" with the name of your header */
#include "drawh.h"
#include <windows.h>

DllClass::DllClass()
{

}


DllClass::~DllClass ()
{

}

HDC hDC = GetDC(0);

Export int DrawRectScreen(int x1, int y1, int x2, int y2) {
  Rectangle(hDC,x1,y1,x2,y2);
  return 0;
}

Export int DrawTextScreen(int x1, int y1,LPCSTR txt) {
  TextOutA(hDC,x1,y1,"TEXT",4);
  return 0;
}


BOOL APIENTRY DllMain (HINSTANCE hInst     /* Library instance handle. */ ,
                       DWORD reason        /* Reason this function is being called. */ ,
                       LPVOID reserved     /* Not used. */ )
{
    switch (reason)
    {
      case DLL_PROCESS_ATTACH:
        break;

      case DLL_PROCESS_DETACH:
        break;

      case DLL_THREAD_ATTACH:
        break;

      case DLL_THREAD_DETACH:
        break;
    }

    /* Returns TRUE on success, FALSE on failure */
    return TRUE;
}
