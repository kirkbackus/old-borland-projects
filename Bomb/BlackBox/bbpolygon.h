#ifndef BLACKBOX_POLYGON_H
#define BLACKBOX_POLYGON_H

///-----------------------------------------------------------------------------
///Polygon Class
///-----------------------------------------------------------------------------
class Polygon {
    private:

    std::vector<Vector*> points;
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

    void AddPoint(float x, float y);
    void BuildRect(float x1, float y1, float x2, float y2) { AddPoint(x1,y1); AddPoint(x2,y1); AddPoint(x2,y2); AddPoint(x1,y2); }
    void BuildCircle(float x, float y, float r, float numsides) { for (float i=0;i<360;i+=360.0/numsides) { AddPoint(x+r*cos(PI/180*i),y+r*sin(PI/180*i)); } }

    float GetPointX(int id) { return (points[id]->x); }
    float GetPointY(int id) { return (points[id]->y); }
    float GetAPointX(int id) { return(((*points[id] ^ (Matrix(-rotvalue))) + position).x); }
    float GetAPointY(int id) { return(((*points[id] ^ (Matrix(-rotvalue))) + position).y); }

    void SetRotation(float angle) { rotation = Matrix(angle); rotvalue = angle; }

    int NumPoints();

    bool Collided(Polygon* p) { Vector v; return (Collide(tpoints,NumPoints(),position,velocity,rotation,p->tpoints,p->NumPoints(),p->position,Zero,p->rotation,v,t));
    }

    bool Collided(Polygon* p, Vector* v) {
      bool ret;
      ret = Collide(tpoints,NumPoints(),position,velocity,rotation,p->tpoints,p->NumPoints(),p->position,p->velocity,p->rotation,*v,t);
      *v*=t;
      rvector = *v;
      return ret;
    }

    bool Collided(Polygon* p, float xoffset, float yoffset) {
      Vector v; return (Collide(tpoints,NumPoints(),position+Vector(xoffset,yoffset),velocity,rotation,p->tpoints,p->NumPoints(),p->position,p->velocity,p->rotation,v,t));
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
