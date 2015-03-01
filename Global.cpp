#include "Global.h"
#include <cmath>

double Global::intersectionArea(ClipperLib::Path &p1, ClipperLib::Path &p2)
{
    ClipperLib::Clipper clipper;
    clipper.AddPath(p1,ClipperLib::ptSubject,true);
    clipper.AddPath(p2,ClipperLib::ptClip,true);
    ClipperLib::Paths solution;
    clipper.Execute(ClipperLib::ctIntersection,solution);
    if(solution.size()>0){
        return abs(ClipperLib::Area(solution[0]));
    }
    return 0;
}

double Global::distanceSqrd(const ClipperLib::Path &p1, const ClipperLib::Path &p2)
{
    return ClipperLib::MinimumDistanceCalipersSqrd(p1,p2);
}

Vec2::Vec2(double _x,double _y):x(_x),y(_y)
{

}

double Vec2::lengthSqrd()
{
    return x*x+y*y;
}

double Vec2::dot(const Vec2 &v)
{
    return x*v.x+y*v.y;
}

Vec2 operator+(const Vec2 &v1,const Vec2 &v2){
    return Vec2(v1.x+v2.x,v1.y+v2.y);
}

Vec2 operator-(const Vec2 &v1,const Vec2 &v2){
    return Vec2(v1.x-v2.x,v1.y-v2.y);
}
