//Terrain Points
struct TerPoints {
  float x,y;
};

struct TerCData {
  char name[20];
  char pass[20];
  int difficulty;
  int r;
  int g;
  int b;
};

class Terrain {
  public:

  Terrain(const char* fname);
  ~Terrain();

  void Load(const char* fname);
  float GetMin();
  float GetMax();
  void Draw();
  TerPoints GetStart();
  void Terrain::GetData(const char* fname, TerCData* terdata);

  private:

  TerPoints start,end;
  vector<Dynamic*> terrain;
  Dynamic* limit;
  Model* terrainmod;
  char fname[100];
  TerCData terdata;
};

Terrain::Terrain(const char* fname) {
  //Starting And Ending Point's Positions
  start.x=0;
  start.y=0;
  end.x=0;
  end.y=0;

  //Load The Terrain
  Load(fname);

  //Create Model for terrain
  terrainmod=new Model();

  terrainmod->StartModel();

  for (int i=terrain.size()-1;i>=0;i--) {
    terrain[i]->DrawQuad(640,terdata.r,terdata.g,terdata.b);
  }

  terrainmod->EndModel();
}

Terrain::~Terrain() {
  for (int i=0;(unsigned)i<terrain.size();i++) {
    delete terrain[i];
  }
  terrain.clear();
  delete terrainmod;
  delete limit;
}

inline void Terrain::GetData(const char* fname, TerCData* terdata) {
  ifstream topen(fname, ios_base::out | ios_base::binary);
  topen.read((char*)terdata,sizeof(TerCData)); //General Terrain Info
  topen.close();
}

void Terrain::Load(const char* fname)
{
  ifstream topen(fname, ios_base::out | ios_base::binary);
  if (topen.is_open()) {
    TerPoints tmp1;
    TerPoints tmp2;
    topen.read((char*)&terdata,sizeof(TerCData)); //General Terrain Info
    topen.read((char*)&start,sizeof(TerPoints)); //Starting Point
    topen.read((char*)&end,sizeof(TerPoints));   //Ending Point
    topen.read((char*)&tmp2,sizeof(TerPoints));  //First point

    while(!topen.eof()) {
      tmp1.x=tmp2.x;
      tmp1.y=tmp2.y;
      topen.read((char*)&tmp2,sizeof(TerPoints));
      if (tmp1.x==tmp2.x && tmp1.y==tmp2.y)continue;
      if (topen.eof())break;
      terrain.push_back(new Dynamic(tmp1.x,tmp1.y,STATIC,SHAPE_LINE,tmp2.x,tmp2.y));
    }

    limit = new Dynamic(terrain[0]->getX(),terrain[0]->getY(),STATIC,SHAPE_PLANE,0);
  }
}


inline float Terrain::GetMin() {
  return(terrain[0]->getX());
}

inline float Terrain::GetMax() {
  return(terrain[terrain.size()-1]->getX());
}

inline void Terrain::Draw()
{
  terrainmod->Draw();
}

inline TerPoints Terrain::GetStart() {
  return(start);
}
