#ifndef FINEALIGNMENT_H
#define FINEALIGNMENT_H

#include "cost.h"

#define FACGM

class FineAlignment:public Cost
{
#ifdef FACGM
    std::vector<int> block0;
    std::vector<int> block1;
    std::vector<int> block2;
    std::vector<int> block3;
#else
    std::vector<int> blocks02;
    std::vector<int> blocks13;
#endif
    void assignFurnToBlock(const Room &room);
public:
    FineAlignment(double weight,const Room &room);
    virtual double calculate(const Room &room) const;
};

#endif // FINEALIGNMENT_H
