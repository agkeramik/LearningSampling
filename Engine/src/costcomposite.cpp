#include "Engine/costcomposite.h"
#include <iostream>
using namespace std;

CostComposite::CostComposite():Cost(1.0)
{

}

double CostComposite::calculate(const Room &room) const
{
    double sum=0;
    for(unsigned int i=0;i<children.size();++i)
        sum+=children[i]->calculate(room);
    return weight*sum;
}

void CostComposite::addComponent(Cost *cost)
{
    children.push_back(cost);
}

void CostComposite::removeComponent(Cost *cost)
{
    std::vector<Cost*>::iterator it;
    for(it=children.begin();it!=children.end();){
        if(*it==cost)
            it = children.erase(it);
        else{
            CostComposite *v=dynamic_cast<CostComposite*>(*it);
            if(v!=0)
                v->removeComponent(cost);
            ++it;
        }
    }
}

void CostComposite::cleanMemory()
{
    std::vector<Cost*>::iterator it=children.begin();
    while (it != children.end()) {
        Cost *s=*it;
        it = children.erase(it);
        s->cleanMemory();

        delete s;
    }
}

CostComposite::~CostComposite()
{

}
