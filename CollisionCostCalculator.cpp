#include "CollisionCostCalculator.h"
#include "clipper.hpp"

CollisionCostCalculator::CollisionCostCalculator()
{

}

double CollisionCostCalculator::calculateCost(Room &room)
{
    double violationArea = 0;
    vector<Furniture> &furnitures = room.getFurnitures();
    for (unsigned int i=0;i<furnitures.size()-1;++i){
        ClipperLib::Path pi=furnitures[i].getGlobalGeometry();
        for (unsigned int j=i+1;j<furnitures.size();++j){
            ClipperLib::Path pj=furnitures[j].getGlobalGeometry();
            violationArea+=Global::intersectionArea(pi,pj);
        }
    }
    return violationArea;
}

void CollisionCostCalculator::print(std::ostream &out)
{
    out<<"Collision Cost Calc: ";
}

CollisionCostCalculator::~CollisionCostCalculator()
{

}
