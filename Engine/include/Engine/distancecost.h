#ifndef DISTANCECOST_H
#define DISTANCECOST_H

#include "cost.h"

class DistanceCost:public Cost
{
    double basicEval(double distance, double m, double M) const;
    double minCornerDistance(const ClipperLib::Path &p1,const ClipperLib::Path &p2) const;
public:
    DistanceCost(double weight);
    virtual double calculate(const Room &room) const;
};

#endif // DISTANCECOST_H
