#ifndef __BLACKBOX_H
#define __BLACKBOX_H

#include <math.h>

//-----------------------------------------------------------------------------
//Definitions
//-----------------------------------------------------------------------------

#define PI 3.141592653589793
#define DEGTORAD PI/180
#define RADTODEG 180/PI
#define FLT_MAX 340000000000000000000000000000000000

//-----------------------------------------------------------------------------
//Define Necessary Structures
//-----------------------------------------------------------------------------
namespace BlackBox {
  class Point;
  class Vector;

  class Point {
    public:
    float p[3];

    Point() { p[0] = 0; p[1] = 0; p[2] = 0; }
    Point(float x, float y, float z) { p[0] = x; p[1] = y; p[2] = z; }
    Point(Vector v);

    void operator+= (Point pt) { p[0] += pt.p[0]; p[1] += pt.p[1]; p[2] += pt.p[2]; }
    void operator-= (Point pt) { p[0] -= pt.p[0]; p[1] -= pt.p[1]; p[2] -= pt.p[2]; }
    void operator*= (float i) { p[0]*=i; p[1]*=i; p[2]*=i; }
    void operator/= (float i) { p[0]/=i; p[1]/=i; p[2]/=i; }

    Point operator+ (Point pt) { Point np; np.p[0] = p[0]+pt.p[0]; np.p[1] = p[1]+pt.p[1]; np.p[2] = p[2]+pt.p[2]; return np; }
    Point operator- (Point pt) { Point np; np.p[0] = p[0]-pt.p[0]; np.p[1] = p[1]-pt.p[1]; np.p[2] = p[2]-pt.p[2]; return np; }
    Point operator* (float i) { Point np; np.p[0] = p[0]*i; np.p[1] = p[1]*i; np.p[2] = p[2]*i; return np; }
    Point operator/ (float i) { Point np; np.p[0] = p[0]/i; np.p[1] = p[1]/i; np.p[2] = p[2]/i; return np; }
    Point operator= (Point pt) { p[0] = pt.p[0]; p[1] = pt.p[1]; p[2] = pt.p[2]; return *this;}

    Point operator= (Vector v);
    Point operator+ (Vector v);
    Point operator- (Vector v);

    bool operator== (Point pt) { if (p[0]==pt.p[0] && p[1]==pt.p[1] && p[2]==pt.p[2]) return 1; return 0; }
    bool operator!= (Point pt) { if (p[0]==pt.p[0] && p[1]==pt.p[1] && p[2]==pt.p[2]) return 0; return 1; }
  };

  class Vector {
    public:
    float d[3];

    Vector() { d[0] = 0; d[1] = 0; d[2] = 0; }
    Vector(float x, float y, float z) { d[0] = x; d[1] = y; d[2] = z; }
    Vector(Point p) { d[0] = p.p[0]; d[1] = p.p[1]; d[2] = p.p[2]; }

    float Length() { return(sqrt(pow(d[0],2)+pow(d[1],2)+pow(d[2],2))); }
    Vector Normalize() { Vector nv; float l=Length(); nv.d[0]=d[0]/l; nv.d[1]=d[1]/l; nv.d[2]=d[2]/l; return nv; }

    void operator+= (Vector v) { d[0] += v.d[0]; d[1] += v.d[1]; d[2] += v.d[2]; }
    void operator-= (Vector v) { d[0] -= v.d[0]; d[1] -= v.d[1]; d[2] -= v.d[2]; }
    void operator*= (float i) { d[0]*=i; d[1]*=i; d[2]*=i; }
    void operator/= (float i) { d[0]/=i; d[1]/=i; d[2]/=i; }

    Vector operator+ (Vector v) { Vector vn; vn.d[0] = d[0]+v.d[0]; vn.d[1] = d[1]+v.d[1]; vn.d[2] = d[2]+v.d[2]; return vn; }
    Vector operator- (Vector v) { Vector vn; vn.d[0] = d[0]-v.d[0]; vn.d[1] = d[1]-v.d[1]; vn.d[2] = d[2]-v.d[2]; return vn; }
    Vector operator* (float i) { Vector vn; vn.d[0] = d[0]*i; vn.d[1] = d[1]*i; vn.d[2] = d[2]*i; return vn; }
    Vector operator/ (float i) { Vector vn; vn.d[0] = d[0]/i; vn.d[1] = d[1]/i; vn.d[2] = d[2]/i; return vn; }

    void operator= (Vector v) { d[0] = v.d[0]; d[1] = v.d[1]; d[2] = v.d[2]; }
    void operator= (Point pt) { d[0] = pt.p[0]; d[1] = pt.p[1]; d[2] = pt.p[2]; }

    bool operator== (Vector v) { if (d[0]==v.d[0] && d[1]==v.d[1] && d[2]==v.d[2]) return 1; return 0; }
    bool operator!= (Vector v) { if (d[0]==v.d[0] && d[1]==v.d[1] && d[2]==v.d[2]) return 0; return 1; }
  };

  Point Point::operator= (Vector v) { p[0] = v.d[0]; p[1] = v.d[1]; p[2] = v.d[2]; return *this;}
  Point::Point(Vector v) { p[0] = v.d[0]; p[1] = v.d[1]; p[2] = v.d[2]; }
  Point Point::operator+ (Vector v) { Point pn; pn.p[0] = p[0]+v.d[0]; pn.p[1] = p[1]+v.d[1]; pn.p[2] = p[2]+v.d[2]; return pn; }
  Point Point::operator- (Vector v) { Point pn; pn.p[0] = p[0]-v.d[0]; pn.p[1] = p[1]-v.d[1]; pn.p[2] = p[2]-v.d[2]; return pn; }

  class Plane {
    public:
    Vector n;
    float d;
  };

  class AABB {
    public:
    Point c;
    float r[3];
  };

  class Sphere {
    public:
    Point c;
    float r;
  };

  class Capsule {
    public:
    Point a;
    Point b;
    float r;
  };

  class Lozenge {
    public:
    Point a;
    Vector u[2];
    float r;
  };

  //-----------------------------------------------------------------------------
  //Functions
  //-----------------------------------------------------------------------------

  inline float Dot(Vector v1, Vector v2) { return(v1.d[0]*v2.d[0]+v1.d[1]*v2.d[1]+v1.d[2]*v2.d[2]); }
  inline float SmallestAngle(Vector v1, Vector v2) { return(RADTODEG*acos(Dot(v1,v2)/(v1.Length()*v2.Length()))); }
  inline float TriArea2D(float x1, float y1, float x2, float y2, float x3, float y3) { return((x1-x2)*(y2-y3)-(x2-x3)*(y1-y2)); }

  inline Vector Normalize(Vector v) {
    float l=v.Length();
    v.d[0]=v.d[0]/l;
    v.d[1]=v.d[1]/l;
    v.d[2]=v.d[2]/l;
    return(v);
  }

  inline Vector Cross(Vector v1, Vector v2) {
    Vector r;
    r.d[0]=v1.d[1]*v2.d[2]-v1.d[2]*v2.d[1];
    r.d[1]=-v1.d[0]*v2.d[2]+v1.d[2]*v2.d[0];
    r.d[2]=v1.d[0]*v2.d[1]-v1.d[1]*v2.d[0];
    return(r);
  }

  inline Vector Cross(Point v1, Point v2) {
    Vector r;
    r.d[0]=v1.p[1]*v2.p[2]-v1.p[2]*v2.p[1];
    r.d[1]=-(v1.p[0]*v2.p[2]-v1.p[2]*v2.p[0]);
    r.d[2]=v1.p[0]*v2.p[1]-v1.p[1]*v2.p[0];
    return(r);
  }

  //Functions to Calculate/Create


  inline Plane CreatePlane(Point p1, Point p2, Point p3) {
    Plane p;
    Vector v;
    v.d[0]=p1.p[0]; v.d[1]=p1.p[1]; v.d[2]=p1.p[2];
    p.n = Normalize(Cross(p2-p1,p3-p1));
    p.d = Dot(p.n,v);
    return(p);
  }

  inline void Barycentric(Point a, Point b, Point c, Point p, float &u, float &v, float &w) {
    Vector m = Cross(b-a,c-a);

    float nu, nv, ood;

    float x=abs(m.d[0]), y=abs(m.d[1]), z=abs(m.d[2]);

    if (x>=y && x>=z) {
      nu=TriArea2D(p.p[1],p.p[2],b.p[1],b.p[2],c.p[1],c.p[2]);
      nv=TriArea2D(p.p[1],p.p[2],c.p[1],c.p[2],a.p[1],a.p[2]);
      ood=1.0/m.d[0];
    } else if (y>=x && y>=z) {
      nu=TriArea2D(p.p[0],p.p[2],b.p[0],b.p[2],c.p[0],c.p[2]);
      nv=TriArea2D(p.p[0],p.p[2],c.p[0],c.p[2],a.p[0],a.p[2]);
      ood=1.0/-m.d[1];
    } else {
      nu=TriArea2D(p.p[0],p.p[1],b.p[0],b.p[1],c.p[0],c.p[1]);
      nv=TriArea2D(p.p[0],p.p[1],c.p[0],c.p[1],a.p[0],a.p[1]);
      ood=1.0/m.d[2];
    }
    u=nu*ood;
    v=nv*ood;
    w=1.0-u-v;
  }

  int PointFarthestFromEdge(Point a, Point b, Point p[], int n) {
    Vector e = b-a;
    Vector eperp; eperp.d[0]=-e.d[1]; eperp.d[1]=e.d[0];
    e.d[2]=0; eperp.d[2];
    int bestIndex=-1;
    float maxVal=-FLT_MAX, rightMostVal=-FLT_MAX;

    for (int i=1;i<n;i++) {
      float d=Dot(p[i]-a, eperp);
      float r=Dot(p[i]-a, e);
      if (d>maxVal || (d==maxVal && r>rightMostVal)) {
        bestIndex=i;
        maxVal=d;
        rightMostVal=r;
      }
    }

    return bestIndex;
  }

  //---------------------------------------------------------------------------
  //BOUNDING VOLUMES
  //---------------------------------------------------------------------------
  int TestAABBAABB(AABB a, AABB b) {
    int r;
    r=a.r[0]+b.r[0]; if ((int)(a.c.p[0]-b.c.p[0]+r) > r + r) return 0;
    r=a.r[1]+b.r[1]; if ((int)(a.c.p[1]-b.c.p[1]+r) > r + r) return 0;
    r=a.r[2]+b.r[2]; if ((int)(a.c.p[2]-b.c.p[2]+r) > r + r) return 0;
    return(1);
  }

  void ExtremePointsAlongDirection(Vector dir, Point pt[], int n, int *imin, int *imax) {
    float minproj = FLT_MAX, maxproj=-FLT_MAX;
    Point origin; origin.p[0]=0; origin.p[1]=0; origin.p[2]=0;
    for (int i=0;i<n;i++) {
      float proj=Dot(Vector((pt[i]-origin)),dir);
      if (proj<minproj) {
        minproj = proj;
        *imin = i;
      }

      if (proj > maxproj) {
        maxproj = proj;
        *imax = i;
      }
    }
  }

  bool TestSphereSphere(Sphere a, Sphere b) {
    Vector d = b.c-a.c;
    float dist2=Dot(d,d);
    float radiusSum = a.r+b.r;
    return(dist2<=radiusSum*radiusSum);
  }

  int IntersectRaySphere(Point p, Vector d, Sphere s, float* t, Point* q) {
    Vector m = s.c-p;
    float b = Dot(m,d);
    float c = Dot(m,m)-s.r*s.r;

    if (c>0.0f && b>0.0f) return 2;
    float discr = b*b-c;
    if (discr<0.0f) return 3;
    *t=-b-sqrt(discr);
    if (t<0)t=0;
    *q = p+d**t;
    return 1;
  }

  float ScalarTriple(Vector v1, Vector v2, Vector v3) {
    return(Dot(Cross(v1,v2),v3));
  }

  int IntersectLineTriangle(Point p, Point q, Point a, Point b, Point c, float& u, float& v, float& w) {
    Vector pq = q-p;
    Vector pa = a-p;
    Vector pb = b-p;
    Vector pc = c-p;

    if (pq!=q) return -1;
    if (pa!=a) return -1;
    if (pb!=b) return -1;
    if (pc!=c) return -1;

    u=ScalarTriple(pq, pc, pb);
    if (u<0) return 0;
    v=ScalarTriple(pq, pa, pc);
    if (v<0) return 0;
    w=ScalarTriple(pq, pb, pa);
    if (w<0) return 0;

    if (u==0 && v==0 && w==0) return 5;

    float denom = 1.0/(u+v+w);
    u*=denom;
    v*=denom;
    w*=denom;
    return 1;
  }

}

#endif
