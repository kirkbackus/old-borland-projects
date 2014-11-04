//---------------------------------------------------------------------------

#ifndef platformH
#define platformH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

//---------------------------------------------------------------------------

class World {
  public:

  void AddShape(TControl *_add);
  TControl* GetShape(int id);
  TControl* GetShape(String name);
  bool Collided(TControl *col);
  bool Collided(TControl *col, int x, int y);

  private:

  vector<TControl*> cworld;
};

void World::AddShape(TControl *_add) {
  cworld.push_back(_add);
}

TControl* World::GetShape(int id) {
  if (id>0 && id<cworld.size()) return(cworld[id]);
  return (NULL);
}

TControl* World::GetShape(String name) {
  for (int i=0;i<cworld.size();i++) {
    if (cworld[i]->Name==name) return (cworld[i]);
  }
  return (NULL);
}

bool World::Collided(TControl *col) {
  for (int i=0;i<(signed)cworld.size();i++) {
    if (col->Left+col->Width>cworld[i]->Left &&
      col->Top+col->Height>cworld[i]->Top &&
      col->Left<cworld[i]->Left+cworld[i]->Width &&
      col->Top<cworld[i]->Top+cworld[i]->Height) return 1;
  }

  return 0;
}

bool World::Collided(TControl *col, int x, int y) {
  for (int i=0;i<(signed)cworld.size();i++) {
    if (col->Left+col->Width+x>cworld[i]->Left &&
      col->Top+col->Height+y>cworld[i]->Top &&
      col->Left+x<cworld[i]->Left+cworld[i]->Width &&
      col->Top+y<cworld[i]->Top+cworld[i]->Height) return 1;
  }

  return 0;
}


//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TShape *Shape1;
        TShape *Shape2;
        TShape *Shape3;
        TShape *Shape4;
        TShape *Shape5;
        TShape *Shape6;
        TShape *Shape7;
        TShape *Shape8;
        TShape *Shape9;
        TShape *Shape10;
        TShape *MPlayer;
        TTimer *Timer1;
        void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
