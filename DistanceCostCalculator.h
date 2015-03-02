#ifndef DISTANCE_COST_CALCULATOR_H
#define DISTANCE_COST_CALCULATOR_H

#include "CostCalculator.h"

class DistanceCostCalculator : public CostCalculator{
    double startRange, endRange, severtiy;
<<<<<<< HEAD
public:
    DistanceCostCalculator(Room &_room);
    virtual double calculateCost(Furniture &furniture);
=======
    double basicEval(double distance, double m, double M);

public:
    DistanceCostCalculator();
    virtual double calculateCost(Room &room);
>>>>>>> a72f23e06656d0772e86b68f5022f4cbc03f84d8
    double getSeverity();
    void setSeverity(double severtiy);
    double getStartRange();
    void setStartRange(double startRange);
    double getEndRange();
    void setEndRange(double endRange);
<<<<<<< HEAD
=======
    virtual void print(std::ostream &out);
>>>>>>> a72f23e06656d0772e86b68f5022f4cbc03f84d8
    virtual ~DistanceCostCalculator();
};

#endif
