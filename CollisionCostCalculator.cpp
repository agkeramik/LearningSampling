#include "CollisionCostCalculator.h"
<<<<<<< HEAD

CollisionCostCalculator::CollisionCostCalculator(Room &_room) : CostCalculator(_room) {}

double CollisionCostCalculator::calculateCost(Furniture &furniture){
    double violationArea = 0;

    //todo add lost area, area outside room

    const vector<Furniture *> alreadyPlaced = getRoom().getFurnitures();
    Polygon f = furniture.getTransformedGeometry();
    for (int i = 0; i < alreadyPlaced.size(); ++i){
        Polygon p = alreadyPlaced[i]->getTransformedGeometry();
        violationArea += Global::intersectionArea(p, f);
    }

    return violationArea;
}

CollisionCostCalculator::~CollisionCostCalculator() {}
=======
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
>>>>>>> a72f23e06656d0772e86b68f5022f4cbc03f84d8
