#include "CollisionCostCalculator.h"

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
