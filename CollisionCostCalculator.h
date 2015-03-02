#ifndef COLLISION_COST_CALCULATOR_H
#define COLLISION_COST_CALCULATOR_H

#include "CostCalculator.h"

<<<<<<< HEAD
class CollisionCostCalculator : public CostCalculator {
public:
    CollisionCostCalculator(Room &_room);
    virtual double calculateCost(Furniture &furniture);
=======
class CollisionCostCalculator : public CostCalculator{
public:
    CollisionCostCalculator();
    virtual double calculateCost(Room &room);
    virtual void print(std::ostream &out);
>>>>>>> a72f23e06656d0772e86b68f5022f4cbc03f84d8
    virtual ~CollisionCostCalculator();
};

#endif
