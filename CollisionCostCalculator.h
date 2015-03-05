#ifndef COLLISION_COST_CALCULATOR_H
#define COLLISION_COST_CALCULATOR_H

#include "CostCalculator.h"

class CollisionCostCalculator : public CostCalculator{
public:
    CollisionCostCalculator();
    virtual double calculateCost(const Room &room);
    virtual void print(std::ostream &out);
    virtual ~CollisionCostCalculator();
};

#endif
