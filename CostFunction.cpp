#include "CostFunction.h"

void CostFunction::addComponent(CostCalculator &cc)
{
    this->components.push_back(&cc);
}

void CostFunction::clearComponents()
{
    this->components.clear();
}

double CostFunction::calculateCost(Room &room)
{
    double cost = 0;
    for (unsigned int i = 0; i < components.size(); ++i)
        cost += components[i]->calculateWeightedCost(room);
    return cost;
}

CostFunction::~CostFunction()
{

}
