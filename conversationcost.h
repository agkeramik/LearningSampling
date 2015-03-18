#ifndef CONVERSATIONCOST_H
#define CONVERSATIONCOST_H

#include "cost.h"

class ConversationCost:public Cost
{
    std::vector<std::string> furConv;

    double costFunction(const Furniture &f1, const Furniture &f2) const;
    double cosineDeltaAngle(const Furniture &f1, const Furniture &f2) const;
    bool goesInConvCost(const Furniture &f) const;
public:
    ConversationCost(double weight,const char *fileName);
    virtual double calculate(const Room &room) const;
};

#endif // CONVERSATIONCOST_H
