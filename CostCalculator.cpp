#include "CostCalculator.h"

<<<<<<< HEAD
CostCalculator::CostCalculator(Room &_room) : room(_room) {}

double CostCalculator::calculateWeightedCost(Furniture &furniture){ return this->getWeight() * this->calculateCost(furniture); }

Room &CostCalculator::getRoom() { return this->room; }

double CostCalculator::getWeight() { return this->weight; }

void CostCalculator::setWeight(double weight) { this->weight = weight; }

CostCalculator::~CostCalculator(){}
=======
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
>>>>>>> a72f23e06656d0772e86b68f5022f4cbc03f84d8
