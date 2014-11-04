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
  class Point {
    float p[3];
  };

  struct Vector {
    float d[3];
  };

  struct Plane {
    Vector n;
    float d;
  };

  struct AABB {
    Point c;
    float r[3];
  };

  struct Sphere {
    Point c;
    float r;
  };

  struct Capsule {
    Point a;
    Point b;
    float r;
  };

  struct Lozenge {
    Point a;
    Vector u[2];
    float r;
  };

  //-----------------------------------------------------------------------------
  //Functions
  //-----------------------------------------------------------------------------

  inline float GetLength(Vector v) { return(sqrt(pow(v.d[0],2)+pow(v.d[1],2)+pow(v.d[2],2))); }
  inline float Dot(Vector v1, Vector v2) { return(v1.d[0]*v2.d[0]+v1.d[1]*v2.d[1]+v1.d[2]*v2.d[2]); }
  inline float SmallestAngle(Vector v1, Vector v2) { return(RADTODEG*acos(Dot(v1,v2)/(GetLength(v1)*GetLength(v2)))); }
  inline float TriArea2D(float x1, float y1, float x2, float y2, float x3, float y3) { return((x1-x2)*(y2-y3)-(x2-x3)*(y1-y2)); }

  inline Vector Normalize(Vector v) {
    float l=GetLength(v);
    v.d[0]=v.d[0]/l;
    v.d[1]=v.d[1]/l;
    v.d[2]=v.d[2]/l;
    return(v);
  }

  inline Vector Cross(Vector v1, Vector v2) {
    Vector r;
    r.d[0]=v1.d[1]*v2.d[2]-v1.d[2]*v2.d[1];
    r.d[1]=-(v1.d[0]*v2.d[2]-v1.d[2]*v2.d[0]);
    r.d[2]=v1.d[0]*v2.d[1]-v1.d[1]*v2.d[0];
    return(r);
  }

  //Functions to Calculate/Create
  inline Vector CreateVector(Point p1, Point p2) {
    Vector r;
    r.d[0]=p2.p[0]-p1.p[0];
    r.d[1]=p2.p[1]-p1.p[1];
    r.d[2]=p2.p[2]-p1.p[2];
    return(r);
  }

  inline Plane CreatePlane(Point p1, Point p2, Point p3) {
    Plane p;
    Vector v;
    v.d[0]=p1.p[0]; v.d[1]=p1.p[1]; v.d[2]=p1.p[2];
    p.n = Normalize(Cross(CreateVector(p1,p2),CreateVector(p1,p2)));
    p.d = Dot(p.n,v);
    return(p);
  }

  inline void Barycentric(Point a, Point b, Point c, Point p, float &u, float &v, float &w) {
    Vector m = Cross(CreateVector(a,b),CreateVector(a,c));

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
    Vector e = CreateVector(a,b);
    Vector eperp; eperp.d[0]=-e.d[1]; eperp.d[1]=e.d[0];
    e.d[2]=0; eperp.d[2];
    int bestIndex=-1;
    float maxVal=-FLT_MAX, rightMostVal=-FLT_MAX;

    for (int i=1;i<n;i++) {
      float d=Dot(CreateVector(a,p[i]), eperp);
      float r=Dot(CreateVector(a,p[i]), e);
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
    r=a.r[0]+b.r[0]; if ((unsigned int)(a.c.p[0]-b.c.p[0]+r) > r + r) return 0;
    r=a.r[1]+b.r[1]; if ((unsigned int)(a.c.p[1]-b.c.p[1]+r) > r + r) return 0;
    r=a.r[2]+b.r[2]; if ((unsigned int)(a.c.p[2]-b.c.p[2]+r) > r + r) return 0;
    return(1);
  }

  void ExtremePointsAlongDirection(Vector dir, Point pt[], int n, int *imin, int *imax) {
    float minproj = FLT_MAX, maxproj=-FLT_MAX;
    Point origin; origin.p[0]=0; origin.p[1]=0; origin.p[2]=0;
    for (int i=0;i<n;i++) {
      float proj=Dot(CreateVector(pt[i],origin),dir);
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
    Vector d = CreateVector(a.c,b.c);
    float dist2=Dot(d,d);
    float radiusSum = a.r+b.r;
    return(dist2<=radiusSum*radiusSum);
  }

  bool IntersectRaySphere(Point p, Vector d, Sphere s, float &t, Point &q) {
    Vector m = CreateVector(p,s.c);
    float b = Dot(m,d);
    float c = Dot(m,m)-s.r*s.r;

    if (c>0 && b>0) return 0;
    float discr = b*b-c;
    if (discr<0) return 0;
    t=-b-sqrt(discr);
    if (t<0)t=0;
    //q = p+t*d;
    return 1;
  }

  float ScalarTriple(Vector v1, Vector v2, Vector v3) {
    return(Dot(Cross(v1,v2),v3));
  }

  bool IntersectLineTriangle(Point p, Point q, Point a, Point b, Point c, float& u, float& v, float& w) {
    Vector pq = CreateVector(p,q);
    Vector pa = CreateVector(p,a);
    Vector pb = CreateVector(p,b);
    Vector pc = CreateVector(p,c);
    u=ScalarTriple(pq, pc, pb);
    if (u<0) return 0;
    v=ScalarTriple(pq, pa, pc);
    if (v<0) return 0;
    w=ScalarTriple(pq, pb, pa);
    if (w<0) return 0;

    if (u==0 && v==0 && w==0) return 0;

    float denom = 1.0/(u+v+w);
    u*=denom;
    v*=denom;
    w*=denom;
    return 1;
  }

}

#endif
