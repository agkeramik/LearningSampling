#ifndef FINEALIGNMENT_H
#define FINEALIGNMENT_H

#include "cost.h"

class FineAlignment:public Cost
{
    std::vector<int> blocks02;
    std::vector<int> blocks13;
    void assignFurnToBlock(const Room &room);
public:
    FineAlignment(double weight,const Room &room);
    virtual double calculate(const Room &room) const;
};

#endif // FINEALIGNMENT_H
