#ifndef BLACKBOX_ENGINE_H
#define BLACKBOX_ENGINE_H

#include <math.h>
#include <vector.h>

///-----------------------------------------------------------------------------
///Definitions
///-----------------------------------------------------------------------------

#ifndef PI
#define PI 3.141592653589793
#endif

#define DEGTORAD PI/180
#define RADTODEG 180/PI
#define sign(a) (a < 0 ? -1:1) 

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