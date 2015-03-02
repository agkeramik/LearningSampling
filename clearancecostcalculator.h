#ifndef CLEARANCECOSTCALCULATOR_H
#define CLEARANCECOSTCALCULATOR_H
#include "CostCalculator.h"

class ClearanceCostCalculator : public CostCalculator
{
public:
    ClearanceCostCalculator();
    virtual double calculateCost(Room &room);
    virtual void print(std::ostream &out);
    virtual ~ClearanceCostCalculator();
};

#endif // CLEARANCECOSTCALCULATOR_H
