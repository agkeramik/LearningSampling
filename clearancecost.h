#ifndef CLEARANCECOST_H
#define CLEARANCECOST_H

#include "cost.h"

class ClearanceCost:public Cost
{
public:
    ClearanceCost(double weight);
    virtual double calculate(const Room &room) const;
};

#endif // CLEARANCECOST_H
