#ifndef COST_CALCULATOR_H
#define COST_CALCULATOR_H

#include "Global.h"
#include "room.h"
#include "Furniture.h"
<<<<<<< HEAD

class CostCalculator {
    double weight;
    Room &room;
public:
    CostCalculator(Room &_room);
    virtual double calculateCost(Furniture &furniture)=0;
    double calculateWeightedCost(Furniture &furniture);
    Room &getRoom();
=======
#include <ostream>


class CostCalculator {
protected:
    double weight;
public:
    CostCalculator();
    virtual void print(std::ostream &out)=0;
    virtual double calculateCost(Room &room)=0;
    double calculateWeightedCost(Room &room);
>>>>>>> a72f23e06656d0772e86b68f5022f4cbc03f84d8
    double getWeight();
    void setWeight(double weight);
    virtual ~CostCalculator();
};

#endif
