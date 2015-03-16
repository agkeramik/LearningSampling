#ifndef COST_CALCULATOR_H
#define COST_CALCULATOR_H

#include "Global.h"
#include "room.h"
#include "Furniture.h"
#include <ostream>

class CostFunction;

class CostCalculator {
    std::vector<CostFunction*> functions;
protected:
    double weight;
public:
    CostCalculator();
    virtual void print(std::ostream &out)=0;
    virtual double calculateCost(const Room &room)=0;
    double calculateWeightedCost(const Room &room);
    double getWeight();
    void addFunction(CostFunction *f);
    void removeFunction(CostFunction *f);
    void setWeight(double weight);
    virtual ~CostCalculator();
};

#endif
