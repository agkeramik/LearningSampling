#ifndef BALANCECOSTCALCULATOR_H
#define BALANCECOSTCALCULATOR_H
#include "CostCalculator.h"
#include <ostream>
class BalanceCostCalculator: public CostCalculator
{
public:
    BalanceCostCalculator();
    virtual double calculateCost(const Room &room);
    virtual void print(std::ostream &out);
    virtual ~BalanceCostCalculator();

};

#endif // BALANCECOSTCALCULATOR_H
