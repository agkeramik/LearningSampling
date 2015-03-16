#include "CostCalculator.h"
#include "CostFunction.h"

CostCalculator::CostCalculator()
{

}

double CostCalculator::calculateWeightedCost(const Room &room)
{
    return weight*calculateCost(room);
}


double CostCalculator::getWeight()
{
    return this->weight;
}

void CostCalculator::addFunction(CostFunction *f)
{
    functions.push_back(f);
}

void CostCalculator::removeFunction(CostFunction *f)
{
    for(unsigned int i=0;i<functions.size();++i)
        if(functions[i]==f)
            functions.erase(functions.begin()+i);
}


void CostCalculator::setWeight(double weight)
{
    this->weight = weight;
}

CostCalculator::~CostCalculator()
{
    for(unsigned int i=0;i<functions.size();++i)
        functions[i]->removeComponent(this);
}
