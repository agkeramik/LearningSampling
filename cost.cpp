#include "cost.h"
#include "costcomposite.h"

Cost::Cost(double weight)
{
    this->weight=weight;
}

void Cost::setWeight(double weight)
{
    this->weight=weight;
}

void Cost::cleanMemory()
{

}

Cost::~Cost()
{

}
