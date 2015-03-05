#ifndef GLOBAL_H
#define GLOBAL_H

#include "clipper.hpp"

using namespace std;

class Global
{
public:
    static double intersectionArea(ClipperLib::Path &p1, ClipperLib::Path &p2);
    static double distanceSqrd(const ClipperLib::Path &p1, const ClipperLib::Path &p2);
    static double differenceArea(const ClipperLib::Path &clip,const ClipperLib::Path &p);
};

class Vec2
{
public:
    double x;
    double y;
    Vec2(double _x=0, double _y=0);
    double lengthSqrd();
    double dot(const Vec2 &v);
};
Vec2 operator+(const Vec2 &v1,const Vec2 &v2);
Vec2 operator-(const Vec2 &v1,const Vec2 &v2);

//#define DEBUG_ON

#ifdef DEBUG_ON
#define DEBUG(x) std::cout<<x
#define DEBUG_LINE(x) std::cout<<x<<std::endl
#else
#define DEBUG(x)
#define DEBUG_LINE(x)
#endif

#endif
