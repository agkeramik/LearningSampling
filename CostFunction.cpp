#include "CostFunction.h"
#include "CostCalculator.h"

void CostFunction::addComponent(CostCalculator *cc)
{
    cc->addFunction(this);
    this->components.push_back(cc);
}

void CostFunction::clearComponents()
{
    for(unsigned int i=0; i<components.size();++i){
        components[i]->removeFunction(this);
    }
    this->components.clear();
}

void CostFunction::removeComponent(CostCalculator *c)
{
    for(unsigned int i=0;i<components.size();++i){
        if(components[i]==c){
            c->removeFunction(this);
            components.erase(components.begin()+i);
            return;
        }
    }
}

void CostFunction::print()
{
    std::cout<<"Cost Function:\n";
    for(unsigned int i=0;i<components.size();++i){
        components[i]->print(std::cout);
        std::cout<<endl;
    }
}

double CostFunction::calculateCost(Room &room)
{
    double cost = 0;
    for(unsigned int i=0;i<components.size();++i){
        double c=components[i]->calculateCost(room);
        cost+=components[i]->getWeight()*c;
//        components[i]->print(std::cout);
//        std::cout<<"cost= "<<c<<" weight="<<components[i]->getWeight()<<" total="<<c*(components[i]->getWeight())<<std::endl;
    }
    return cost;
}

CostFunction::~CostFunction()
{
    for(unsigned int i=0; i<components.size();++i){
        components[i]->removeFunction(this);
    }
}
