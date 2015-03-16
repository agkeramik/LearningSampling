#ifndef EXPANSIONCOSTCALCULATOR_H
#define EXPANSIONCOSTCALCULATOR_H
#include "CostCalculator.h"
class ExpansionCostCalculator:public CostCalculator
{
public:
    ExpansionCostCalculator();
    virtual double calculateCost(const Room &room);
    virtual void print(std::ostream &out);
    virtual ~ExpansionCostCalculator();
};

#endif // EXPANSIONCOSTCALCULATOR_H
