#ifndef COST_FUNCTION_H
#define COST_FUNCTION_H

#include "CostCalculator.h"

class CostFunction{
    vector<CostCalculator *> components;
public:
    void addComponent(CostCalculator &cc);
    void clearComponents();
    double calculateCost(Room &room);
    virtual ~CostFunction();
};

#endif
