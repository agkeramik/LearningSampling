#ifndef BALANCECOST_H
#define BALANCECOST_H

#include "cost.h"

class BalanceCost:public Cost
{
public:
    BalanceCost(double weight);
    virtual double calculate(const Room &room) const;
    virtual ~BalanceCost();
};

#endif // BALANCECOST_H
