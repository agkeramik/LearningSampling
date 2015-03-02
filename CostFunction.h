#ifndef COST_FUNCTION_H
#define COST_FUNCTION_H

#include "CostCalculator.h"

class CostFunction{
    vector<CostCalculator *> components;
public:
    void addComponent(CostCalculator &cc);
    void clearComponents();
<<<<<<< HEAD
    double calculateCost(Furniture &furniture);
=======
    double calculateCost(Room &room);
>>>>>>> a72f23e06656d0772e86b68f5022f4cbc03f84d8
    virtual ~CostFunction();
};

#endif
