#include "CostCalculator.h"

CostCalculator::CostCalculator()
{

}

double CostCalculator::calculateWeightedCost(Room &room)
{
    return weight*calculateCost(room);
}


double CostCalculator::getWeight()
{
    return this->weight;
}

void CostCalculator::setWeight(double weight)
{
    this->weight = weight;
}

CostCalculator::~CostCalculator()
{

}
