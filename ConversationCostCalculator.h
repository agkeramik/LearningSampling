#ifndef CONVERSATION_COST_CALCULATOR_H
#define CONVERSATION_COST_CALCULATOR_H

#include "CostCalculator.h"

class ConversationCostCalculator : public CostCalculator{
    double costFunction(double delta);
    double deltaAngle(Furniture &f1, Furniture &f2);
public:
    ConversationCostCalculator(Room &_room);
    virtual double calculateCost(Furniture &furniture);
    virtual ~ConversationCostCalculator();
};

#endif
