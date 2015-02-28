#ifndef COLLISION_COST_CALCULATOR_H
#define COLLISION_COST_CALCULATOR_H

#include "CostCalculator.h"

class CollisionCostCalculator : public CostCalculator{
public:
    CollisionCostCalculator();
    virtual double calculateCost(Room &room);
    virtual ~CollisionCostCalculator();
};

#endif
