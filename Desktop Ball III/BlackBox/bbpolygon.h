#ifndef BLACKBOX_POLYGON_H
#define BLACKBOX_POLYGON_H

///-----------------------------------------------------------------------------
///Polygon Class
///-----------------------------------------------------------------------------
class Polygon {
    private:

    vector<Vector*> points;

    float t;
    Vector rvector;
    Vector Zero;

    Matrix rotation;
    float rotvalue;

    public:

    Vector position;
    Vector velocity;
    Vector* tpoints;

    Polygon() { tpoints = NULL; position; rotation = Matrix(0); Zero = Vector(0,0); rotvalue = 0;}
    ~Polygon() { delete tpoints; for (int i=0;i<points.size();i++) { delete points[i]; points.erase(points.begin()+i); }}

    void AddPoint(float x, float y);

    float GetPointX(int id) { return (points[id]->x); }
    float GetPointY(int id) { return (points[id]->y); }
    float GetAPointX(int id) { return(((*points[id] ^ (Matrix(-rotvalue))) + position).x); }
    float GetAPointY(int id) { return(((*points[id] ^ (Matrix(-rotvalue))) + position).y); }

    void SetRotation(float angle) { rotation = Matrix(angle); rotvalue = angle; }

    int NumPoints();

    bool Collided(Polygon* p) { return (Collide(tpoints,NumPoints(),position,velocity,rotation,p->tpoints,p->NumPoints(),p->position,Zero,p->rotation,Vector(0,0),0));
    }

    bool Collided(Polygon* p, Vector* v) {
      bool ret;
      ret = Collide(tpoints,NumPoints(),position,velocity,rotation,p->tpoints,p->NumPoints(),p->position,p->velocity,p->rotation,*v,t);
      *v*=t;
      rvector = *v;
      return ret;
    }

    bool Collided(Polygon* p, float xoffset, float yoffset) {
      return (Collide(tpoints,NumPoints(),position+Vector(xoffset,yoffset),velocity,rotation,p->tpoints,p->NumPoints(),p->position,p->velocity,p->rotation,Vector(0,0),0));
    }
};

///-----------------------------------------------------------------------------
///Polygon Class Function Declarations
///-----------------------------------------------------------------------------
inline void Polygon::AddPoint(float x, float y) {
    points.push_back(new Vector(x,y));

    if (tpoints!=NULL) delete[] tpoints;
    tpoints = new Vector[points.size()];
    for (unsigned int i=0;i<points.size();i++) {
        tpoints[i] = Vector(points[i]->x, points[i]->y);
    }
}

inline int Polygon::NumPoints() { return (points.size()); }

#endif