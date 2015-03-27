#include "Geometry/Global.h"
#include <limits>
#include <iostream>
#include <cmath>

double Global::intersectionArea(const ClipperLib::Path &p1, const ClipperLib::Path &p2)
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

double Global::differenceArea(const ClipperLib::Path &clip, const ClipperLib::Path &p)
{
    ClipperLib::Clipper clipper;
    clipper.AddPath(p,ClipperLib::ptSubject,true);
    clipper.AddPath(clip,ClipperLib::ptClip,true);
    ClipperLib::Paths solution;
    clipper.Execute(ClipperLib::ctDifference,solution);
    if(solution.size()>0){
        return abs(ClipperLib::Area(solution[0]));
    }
    return 0;
}

double Global::freeArea(const ClipperLib::Path &p1, const ClipperLib::Path &p2,
                      ClipperLib::Paths &sol)
{
    double minDist=std::numeric_limits<double>::max();
    int p1Ind;
    int p2Ind;
    for(unsigned int i=0;i<p1.size();++i){
        for(unsigned int j=0;j<p2.size();++j){
            double tempDist=ClipperLib::DistanceSqrd(p1[i],p2[j]);
            if(tempDist<minDist){
                minDist=tempDist;
                p1Ind=i;
                p2Ind=j;
            }
        }
    }
    sol.clear();
    //construct the two solutions
    ClipperLib::Path sol1,sol2;
    sol1<< p1[p1Ind]<<p2[p2Ind]
           << p2[(p2Ind-1+p2.size())%p2.size()]
           << p1[(p1Ind+1)%p1.size()];

    ClipperLib::Paths simpl1,simpl2;
    ClipperLib::SimplifyPolygon(sol1,simpl1);
    if(simpl1.size()==1 && sol1.size()==simpl1[0].size()){
        if(!ClipperLib::Orientation(sol1))
            ClipperLib::ReversePath(sol1);
        sol.push_back(sol1);
    }

    sol2<< p2[p2Ind]<<p1[p1Ind]
           << p1[(p1Ind-1+p1.size())%p1.size()]
           << p2[(p2Ind+1)%p2.size()];

    ClipperLib::SimplifyPolygon(sol2,simpl2);
    if(simpl2.size()==1 && sol2.size()==simpl2[0].size()){
        if(!ClipperLib::Orientation(sol2))
            ClipperLib::ReversePath(sol2);
        sol.push_back(sol2);
    }
    return minDist;
}

Vec2 Global::centroid(const ClipperLib::Path &p)
{
    double cx=0,cy=0,A=0;
    for(unsigned int i=0;i<p.size();++i){
        double j=(i+1)%p.size();
        double alpha=p[i].X*p[j].Y-p[j].X*p[i].Y;
        cx+=(p[i].X+p[j].X)*alpha;
        cy+=(p[i].Y+p[j].Y)*alpha;
        A+=alpha;
    }
    A=0.5*A;
    std::cout<<A<<std::endl;
    cx=1.0/(6.0*A)*cx;
    cy=1.0/(6.0*A)*cy;
    return Vec2(cx,cy);
}

Vec2::Vec2(double _x,double _y):x(_x),y(_y)
{

}

double Vec2::lengthSqrd() const
{
    return x*x+y*y;
}

double Vec2::dot(const Vec2 &v) const
{
    return x*v.x+y*v.y;
}

Vec2 operator+(const Vec2 &v1,const Vec2 &v2){
    return Vec2(v1.x+v2.x,v1.y+v2.y);
}

Vec2 operator-(const Vec2 &v1,const Vec2 &v2){
    return Vec2(v1.x-v2.x,v1.y-v2.y);
}


Vec2 intersection(const Vec2 &p1, const Vec2 &d1, const Vec2 &p2, const Vec2 &d2)
{
    //check if parallel
    //sin^2=1-cos^2 with cos=dot/(norm*norm)
    double s_sqrd=1-(d1.dot(d2))*(d1.dot(d2))/(d1.lengthSqrd()*d2.lengthSqrd());
    if(s_sqrd<0.001)
        return Vec2(0.5*(p1.x+p2.x),0.5*(p1.y+p2.y));
    double alpha=d1.x*d2.y-d1.y*d2.x;
    double beta=d2.y*(p2.x-p1.x)+d2.x*(p1.y-p2.y);
    double t=beta/alpha;
    return Vec2(d1.x*t+p1.x,d1.y*t+p1.y);

}



