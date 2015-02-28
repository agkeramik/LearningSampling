#include "CollisionCostCalculator.h"

CollisionCostCalculator::CollisionCostCalculator()
{

}

double CollisionCostCalculator::calculateCost(Room &room)
{
    double violationArea = 0;

    //todo add lost area, area outside room

    vector<Furniture> &furnitures = room.getFurnitures();
    for (unsigned int i=0;i<furnitures.size()-1;++i){
        Polygon pi=furnitures[i].getTransformedGeometry();
        for (unsigned int j=i+1;j<furnitures.size();++j){
            Polygon pj=furnitures[j].getTransformedGeometry();
            violationArea+=Global::intersectionArea(pi,pj);
        }
    }
//    Polygon f = furniture.getTransformedGeometry();
//    for (unsigned int i = 0; i < alreadyPlaced.size(); ++i){
//        Polygon p = alreadyPlaced[i].getTransformedGeometry();
//        violationArea += Global::intersectionArea(p, f);
//    }

    return violationArea;
}

CollisionCostCalculator::~CollisionCostCalculator()
{

}
