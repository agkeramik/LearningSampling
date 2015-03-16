#ifndef MANHATTANCOSTCALCULATOR_H
#define MANHATTANCOSTCALCULATOR_H
#include "CostCalculator.h"


class ManhattanCostCalculator:public CostCalculator
{
    std::vector<int> blocks02;
    std::vector<int> blocks13;
public:
    ManhattanCostCalculator(std::vector<std::vector<int> > _blocks);
    virtual void print(std::ostream &out);
    virtual double calculateCost(const Room &room);
    virtual ~ManhattanCostCalculator();
};

#endif // MANHATTANCOSTCALCULATOR_H
