#ifndef DISTANCE_COST_CALCULATOR_H
#define DISTANCE_COST_CALCULATOR_H

#include "CostCalculator.h"

class DistanceCostCalculator : public CostCalculator{
    double startRange, endRange, severtiy;
    double basicEval(double distance, double m, double M);

public:
    DistanceCostCalculator();
    virtual double calculateCost(Room &room);
    double getSeverity();
    void setSeverity(double severtiy);
    double getStartRange();
    void setStartRange(double startRange);
    double getEndRange();
    void setEndRange(double endRange);
    virtual void print(std::ostream &out);
    virtual ~DistanceCostCalculator();
};

#endif
