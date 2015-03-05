#include "balancecostcalculator.h"
#include "Furniture.h"
#include "Global.h"
#include <cmath>

BalanceCostCalculator::BalanceCostCalculator()
{
}

double BalanceCostCalculator::calculateCost(const Room &room)
{
    const std::vector<Furniture> &furnitures=room.getFurnitures();
    Vec2 cm;
    double total=0;
    for(unsigned int i=0;i<furnitures.size();++i){
        double surface=furnitures[i].width*furnitures[i].depth;
        total+=surface;
        cm=cm+Vec2(furnitures[i].getX()*surface,furnitures[i].getY()*surface);
    }
    cm=Vec2(cm.x/total,cm.y/total);
    cm=cm-room.getCentroid();
    return sqrt(cm.lengthSqrd());
}

void BalanceCostCalculator::print(std::ostream &out)
{
    out<<"Balance Cost Calculator: ";
}

BalanceCostCalculator::~BalanceCostCalculator()
{

}
