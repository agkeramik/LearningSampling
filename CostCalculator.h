#ifndef COST_CALCULATOR_H
#define COST_CALCULATOR_H

#include "Global.h"
#include "room.h"
#include "Furniture.h"

class CostCalculator {
protected:
    double weight;
public:
    CostCalculator();
    virtual double calculateCost(Room &room)=0;
    double calculateWeightedCost(Room &room);
    double getWeight();
    void setWeight(double weight);
    virtual ~CostCalculator();
};

#endif
