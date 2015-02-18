#ifndef COLLISION_COST_CALCULATOR_H
#define COLLISION_COST_CALCULATOR_H

#include "CostCalculator.h"

class CollisionCostCalculator : public CostCalculator {
public:
    CollisionCostCalculator(Room &_room);
    virtual double calculateCost(Furniture &furniture);
    virtual ~CollisionCostCalculator();
};

#endif
