#ifndef COST_FUNCTION_H
#define COST_FUNCTION_H
#include <vector>
#include "room.h"
class CostCalculator;

class CostFunction{
    std::vector<CostCalculator *> components;
public:
    void addComponent(CostCalculator *cc);
    void clearComponents();
    void removeComponent(CostCalculator *c);
    void print();
    double calculateCost(Room &room);
    virtual ~CostFunction();
};

#endif
