#include "Global.h"

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
}
