#include "Global.h"
<<<<<<< HEAD

double Global::intersectionArea(Polygon &p1, Polygon &p2){
        double area = 0;
        std::list<Intersection> intersections;
        CGAL::intersection(p1, p2, std::back_inserter(intersections));
        for (std::list<Intersection>::iterator intIt = intersections.begin(); intIt != intersections.end(); ++intIt)
            area += intIt->outer_boundary().area();
        return area;
}

double Global::distance(Polygon &p1, Polygon &p2){
    Polytope_distance pd(p1.vertices_begin(), p1.vertices_end(), p2.vertices_begin(), p2.vertices_end());
    return sqrt(pd.squared_distance());
}

double Global::distanceCost(double distance, double startRange, double endRange, double severtiy){
    if (distance < startRange)
        return -severtiy * log(distance / startRange);
    else if (distance > endRange)
        return -severtiy * log(endRange / distance);
    return 0;
}

double Global::angle(Vector &v1, Vector &v2){
    Vector v(v1 / std::sqrt(v1*v1));
    Vector w(v2 / std::sqrt(v2*v2));
    return std::acos(v*w);
}

Point Global::centroid(Polygon &p){
    return CGAL::centroid(p.vertices_begin(), p.vertices_end(), Dim2());
=======
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
>>>>>>> a72f23e06656d0772e86b68f5022f4cbc03f84d8
}
