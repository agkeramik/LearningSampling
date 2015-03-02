#include "CostFunction.h"

<<<<<<< HEAD
void CostFunction::addComponent(CostCalculator &cc) {this->components.push_back(&cc);}

void CostFunction::clearComponents() {this->components.clear();}

double CostFunction::calculateCost(Furniture &furniture){
    double cost = 0;
    for (int i = 0; i < components.size(); ++i)
        cost += components[i]->calculateWeightedCost(furniture);
    return cost;
}

CostFunction::~CostFunction() {}
=======
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
    for(unsigned int i=0;i<components.size();++i){
        double c=components[i]->calculateCost(room);
        cost+=components[i]->getWeight()*c;
        components[i]->print(std::cout);
        std::cout<<"cost= "<<c<<" weight="<<components[i]->getWeight()<<std::endl;
    }
    return cost;
}

CostFunction::~CostFunction()
{

}
>>>>>>> a72f23e06656d0772e86b68f5022f4cbc03f84d8
