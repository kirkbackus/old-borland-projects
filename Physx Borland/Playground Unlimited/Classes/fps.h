class FPSCounter {
  public:

  FPSCounter();
  void UpdateFPS();
  int GetFPS();

  private:

  int fps;
  int tick;
  int ntick;
};

inline FPSCounter::FPSCounter() {
  fps=0;
  ntick=GetTickCount();
}

inline void FPSCounter::UpdateFPS() {
  tick=GetTickCount();
  fps++;
  if (tick>ntick) {
    //char wnd[20];
    //sprintf(wnd,"FPS: %u",fps);
    //SetWindowText(hWnd,wnd);
    fps=0;
    ntick=tick+1000;
  }
}

inline int FPSCounter::GetFPS() {
  return(fps);
}
