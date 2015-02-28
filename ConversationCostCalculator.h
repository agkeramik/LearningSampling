#ifndef CONVERSATION_COST_CALCULATOR_H
#define CONVERSATION_COST_CALCULATOR_H

#include "CostCalculator.h"
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
    virtual ~ConversationCostCalculator();
};

#endif
