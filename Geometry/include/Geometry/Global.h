#ifndef GLOBAL_H
#define GLOBAL_H

#include "Geometry/clipper.hpp"

using namespace std;

class Vec2;

class Global
{
public:
    static double intersectionArea(const ClipperLib::Path &p1, const ClipperLib::Path &p2);
    static double distanceSqrd(const ClipperLib::Path &p1, const ClipperLib::Path &p2);
    static double differenceArea(const ClipperLib::Path &clip,const ClipperLib::Path &p);
    /**
     * @brief freeArea
     * Find the two polygons that will complete the free area between two furnitures
     * assuming that the furniture are polygons of four points
     * @param p1
     * @param p2
     * @param sol1
     * @param sol2
     * @return
     * returns the minimum distance sqrd
     */
    static double freeArea(const ClipperLib::Path &p1, const ClipperLib::Path &p2,
                           ClipperLib::Paths &sol);

    static Vec2 centroid(const ClipperLib::Path &p);
};

class Vec2
{
public:
    double x;
    double y;
    Vec2(double _x=0, double _y=0);
    double lengthSqrd() const;
    double dot(const Vec2 &v) const;
};
Vec2 operator+(const Vec2 &v1,const Vec2 &v2);
Vec2 operator-(const Vec2 &v1,const Vec2 &v2);



/**
 * @brief intersection
 * Find the intersection of two lines
 * @param p1
 * First line passes through p1
 * @param d1
 * Direction of first line
 * @param p2
 * Second line passes through p2
 * @param d2
 * Direction of d2
 * @return
 * Will return the intersection point
 * In case the two lines are parallel, the function return the mid point
 * between p1 and p2
 */
Vec2 intersection(const Vec2 &p1,const Vec2 &d1,const Vec2 &p2,const Vec2 &d2);


//#define DEBUG_ON

#ifdef DEBUG_ON
#define DEBUG(x) std::cout<<x
#define DEBUG_LINE(x) std::cout<<x<<std::endl
#else
#define DEBUG(x)
#define DEBUG_LINE(x)
#endif

#endif
