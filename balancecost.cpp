#include "balancecost.h"
#include "Furniture.h"
#include "Global.h"
#include <cmath>

BalanceCost::BalanceCost(double weight):Cost(weight)
{
}

double BalanceCost::calculate(const Room &room) const
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
    return weight*sqrt(cm.lengthSqrd());
}

BalanceCost::~BalanceCost()
{

}
