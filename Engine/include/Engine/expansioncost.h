#ifndef EXPANSIONCOST_H
#define EXPANSIONCOST_H

#include "cost.h"

class ExpansionCost:public Cost
{
public:
    ExpansionCost(double weight);
    virtual double calculate(const Room &room) const;
};

#endif // EXPANSIONCOST_H
