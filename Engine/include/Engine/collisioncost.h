#ifndef COLLISIONCOST_H
#define COLLISIONCOST_H

#include "cost.h"

class CollisionCost:public Cost
{
public:
    CollisionCost(double weight);
    virtual double calculate(const Room &room) const;
};

#endif // COLLISIONCOST_H
