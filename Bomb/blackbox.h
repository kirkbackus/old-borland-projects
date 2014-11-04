#ifndef BLACKBOX_ENGINE_H
#define BLACKBOX_ENGINE_H

#include <math.h>
#include <vector>

///-----------------------------------------------------------------------------
///Definitions
///-----------------------------------------------------------------------------

#define PI 3.141592653589793
#define DEGTORAD PI/180
#define RADTODEG 180/PI
#define FLT_MAX 340000000000000000000000000000000000
#define sign(a) a < 0 ? -1:1

///-----------------------------------------------------------------------------
///BlackBox
///-----------------------------------------------------------------------------

namespace Blackbox {
    #include "BlackBox/bbvector.h"          //Vector Class
    #include "BlackBox/bbmatrix.h"          //Matrix Class
    #include "BlackBox/bbcollision.h"       //Collision Code
    #include "BlackBox/bbpolygon.h"         //Polygon Class
}

#endif
