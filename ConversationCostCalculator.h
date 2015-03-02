#ifndef CONVERSATION_COST_CALCULATOR_H
#define CONVERSATION_COST_CALCULATOR_H

#include "CostCalculator.h"
<<<<<<< HEAD

class ConversationCostCalculator : public CostCalculator{
    double costFunction(double delta);
    double deltaAngle(Furniture &f1, Furniture &f2);
public:
    ConversationCostCalculator(Room &_room);
    virtual double calculateCost(Furniture &furniture);
=======
#include <vector>
#include <string>

class ConversationCostCalculator : public CostCalculator{
    std::vector<std::string> furConv;
public:
    double costFunction(Furniture &f1, Furniture &f2);
    double cosineDeltaAngle(Furniture &f1, Furniture &f2);
    bool goesInConvCost(Furniture &f);

    ConversationCostCalculator(const char *fileName);
    virtual double calculateCost(Room &room);
    virtual void print(std::ostream &out);
>>>>>>> a72f23e06656d0772e86b68f5022f4cbc03f84d8
    virtual ~ConversationCostCalculator();
};

#endif
