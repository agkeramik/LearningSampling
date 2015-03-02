#ifndef GLOBAL_H
#define GLOBAL_H
<<<<<<< HEAD

#include <CGAL/Polygon_2.h>
#include <CGAL/Point_2.h>
#include <CGAL/Aff_transformation_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/Polygon_with_holes_2.h>
#include <CGAL/Polygon_2_algorithms.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polytope_distance_d.h>
#include <CGAL/Polytope_distance_d_traits_2.h>
#include <CGAL/centroid.h>
#include <CGAL/Dimension.h>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point;
typedef CGAL::Vector_2<Kernel> Vector;
typedef CGAL::Polygon_2<Kernel> Polygon;
typedef CGAL::Aff_transformation_2<Kernel> Transform;
typedef CGAL::Polygon_with_holes_2<Kernel> Intersection;
typedef CGAL::Polytope_distance_d_traits_2<Kernel> Traits;
typedef CGAL::Polytope_distance_d<Traits> Polytope_distance;
typedef CGAL::Dimension_tag<0> Dim2;

using namespace std;

class Global {
public:
    static double intersectionArea(Polygon &p1, Polygon &p2);
    static double distance(Polygon &p1, Polygon &p2);
    static double distanceCost(double distance, double startRange, double endRange, double severtiy);
    static double angle(Vector &v1, Vector &v2);
    static Point centroid(Polygon &p);
};
=======

#include "clipper.hpp"
>>>>>>> a72f23e06656d0772e86b68f5022f4cbc03f84d8

using namespace std;

class Global {
public:
    static double intersectionArea(ClipperLib::Path &p1, ClipperLib::Path &p2);
    static double distanceSqrd(const ClipperLib::Path &p1, const ClipperLib::Path &p2);
};

class Vec2{
public:
    double x;
    double y;
    Vec2(double _x, double _y);
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
