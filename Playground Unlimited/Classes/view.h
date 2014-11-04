class View {
  public:

  float view_x[2];
  float view_y[2];
  float view_w[2];
  float view_h[2];

  View(float x, float y, float w, float h, float hb, float vb);

  //View Altering Functions
  void SetView(int id, float x, float y, float w, float h);
  void SetBorder(float hb, float vb);
  void SetMaxMin(float min, float max);
  void SetSplitScreen(bool splitscreen) {split=splitscreen;}
  void SetViewPort(int view, int x, int y, int width, int height);

  //Automatic Updating Functions
  void KeepInView(int id, float x, float y);
  void Update();
  bool UpdateHUD();
  void Lock(bool lock_view) { locked=lock_view; }

  //Get Information about View
  float getX() {return(view_x[0]);}
  float getY() {return(view_y[0]);}
  bool isSplitScreen() {return(split);}
  bool getCurrent() { return(_view); }

  private:

  float vp_x[2],vp_y[2],vp_w[2],vp_h[2];
  float vpx, vpy, vpw, vph;

  float view_hmin;
  float view_hmax;
  bool locked;

  float hborder;
  float vborder;

  bool split;
  bool _view;
};

inline View::View(float x, float y, float w, float h, float hb, float vb) {
  _view=0;
  locked=0;
  SetView(0,x,y,w,h);
  SetView(1,x,y,w,h);
  SetBorder(hb,vb);
  view_hmin=10000;
  view_hmax=-10000;
}

inline void View::SetViewPort(int view, int xpos, int ypos, int width, int height) {
  if (view==-1) {
    vpx=xpos;
    vpy=ypos;
    vpw=width;
    vph=height;
    return;
  }
  
  if (height==0)height=1;
  vp_x[view]=xpos;
  vp_y[view]=ypos;
  vp_w[view]=width;
  vp_h[view]=height;
}

inline void View::SetView(int id, float x, float y, float w, float h) {
  view_x[id]=x;
  view_y[id]=y;
  view_w[id]=w;
  view_h[id]=(h==0 ? 1:h);
}

inline void View::SetBorder(float hb, float vb) {
  hborder=hb;
  vborder=vb;
}

inline void View::KeepInView(int id, float x, float y) {
  if (!locked) {
    if(x>view_x[id]+view_w[id]-hborder)view_x[id]=x-view_w[id]+hborder;
    if(y>view_y[id]+view_h[id]-vborder)view_y[id]=y-view_h[id]+vborder;
    if(x<view_x[id]+hborder)view_x[id]=x-hborder;
    if(y<view_y[id]+vborder)view_y[id]=y-vborder;

    if (view_x[id]<view_hmin && view_hmin!=10000)view_x[id]=view_hmin;
    if (view_x[id]>view_hmax-view_w[id] && view_hmax!=-10000)view_x[id]=view_hmax-view_w[id];
  }
}

inline void View::SetMaxMin(float min, float max) {
  view_hmin=min;
  view_hmax=max;
}

inline void View::Update() {
  if (split) {
    glViewport(vp_x[_view],vp_y[_view],vp_w[_view],vp_h[_view]);
    _view=!_view;
  } else {
    glViewport(vpx,vpy,vpw,vph);
    _view=0;
  }

  SetViewOrtho(view_x[_view],view_y[_view],view_x[_view]+view_w[_view],view_y[_view]+view_h[_view],0);
}

inline bool View::UpdateHUD() {
  if (split && _view==1) return 0;
  glViewport(vpx,vpy,vpw,vph);
  SetViewOrtho(0,0,640,480,0);
  return 1;
}
