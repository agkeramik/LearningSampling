#ifndef COSTCOMPOSITE_H
#define COSTCOMPOSITE_H

#include "cost.h"
#include <vector>

class CostComposite:public Cost
{
    std::vector<Cost*> children;
public:
    CostComposite();
    virtual double calculate(const Room &room) const;
    void addComponent(Cost *cost);
    void removeComponent(Cost *cost);
    virtual void cleanMemory();
    virtual ~CostComposite();

};

#endif // COSTCOMPOSITE_H
