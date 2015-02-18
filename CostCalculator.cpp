#include "CostCalculator.h"

CostCalculator::CostCalculator(Room &_room) : room(_room) {}

double CostCalculator::calculateWeightedCost(Furniture &furniture){ return this->getWeight() * this->calculateCost(furniture); }

Room &CostCalculator::getRoom() { return this->room; }

double CostCalculator::getWeight() { return this->weight; }

void CostCalculator::setWeight(double weight) { this->weight = weight; }

CostCalculator::~CostCalculator(){}
