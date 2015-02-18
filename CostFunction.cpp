#include "CostFunction.h"

void CostFunction::addComponent(CostCalculator &cc) {this->components.push_back(&cc);}

void CostFunction::clearComponents() {this->components.clear();}

double CostFunction::calculateCost(Furniture &furniture){
    double cost = 0;
    for (int i = 0; i < components.size(); ++i)
        cost += components[i]->calculateWeightedCost(furniture);
    return cost;
}

CostFunction::~CostFunction() {}
