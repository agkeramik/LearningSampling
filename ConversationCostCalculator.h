#ifndef CONVERSATION_COST_CALCULATOR_H
#define CONVERSATION_COST_CALCULATOR_H

#include "CostCalculator.h"
#include <vector>
#include <string>

class ConversationCostCalculator : public CostCalculator{
    std::vector<std::string> furConv;
public:
    double costFunction(const Furniture &f1, const Furniture &f2);
    double cosineDeltaAngle(const Furniture &f1, const Furniture &f2);
    bool goesInConvCost(const Furniture &f);

    ConversationCostCalculator(const char *fileName);
    virtual double calculateCost(const Room &room);
    virtual void print(std::ostream &out);
    virtual ~ConversationCostCalculator();
};

#endif
