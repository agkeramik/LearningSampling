#ifndef COST_H
#define COST_H

#include "room.h"

class Cost
{
protected:
    double weight;
public:
    Cost(double weight);
    virtual double calculate(const Room &room) const =0;
    void setWeight(double weight);
    virtual void cleanMemory();
    virtual ~Cost();
};

#endif // COST_H
