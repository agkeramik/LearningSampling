#ifndef DISTANCE_COST_CALCULATOR_H
#define DISTANCE_COST_CALCULATOR_H

#include "CostCalculator.h"

class DistanceCostCalculator : public CostCalculator{
    double startRange, endRange, severtiy;
public:
    DistanceCostCalculator(Room &_room);
    virtual double calculateCost(Furniture &furniture);
    double getSeverity();
    void setSeverity(double severtiy);
    double getStartRange();
    void setStartRange(double startRange);
    double getEndRange();
    void setEndRange(double endRange);
    virtual ~DistanceCostCalculator();
};

#endif
