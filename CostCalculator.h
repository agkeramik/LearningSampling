#ifndef COST_CALCULATOR_H
#define COST_CALCULATOR_H

#include "Global.h"
#include "room.h"
#include "Furniture.h"

class CostCalculator {
    double weight;
    Room &room;
public:
    CostCalculator(Room &_room);
    virtual double calculateCost(Furniture &furniture)=0;
    double calculateWeightedCost(Furniture &furniture);
    Room &getRoom();
    double getWeight();
    void setWeight(double weight);
    virtual ~CostCalculator();
};

#endif
