#include "CollisionCostCalculator.h"
#include "clipper.hpp"

CollisionCostCalculator::CollisionCostCalculator()
{

}

double CollisionCostCalculator::calculateCost(const Room &room)
{
    double violationArea = 0;
    //check if there is any two furnitures collide
    const vector<Furniture> &furnitures = room.getFurnitures();
    for (unsigned int i=0;i<furnitures.size()-1;++i){
        ClipperLib::Path pi=furnitures[i].getGlobalGeometry();
        for (unsigned int j=i+1;j<furnitures.size();++j){
            ClipperLib::Path pj=furnitures[j].getGlobalGeometry();
            violationArea+=Global::intersectionArea(pi,pj);
        }
    }

    if(violationArea!=0){
        std::cout<<"COLLISION!!!!\n";
    }
    //check if there is any collision with the doors
    const vector<Furniture> &doors=room.getDoors();
    for(unsigned int i=0;i<furnitures.size();++i){
        ClipperLib::Path pi=furnitures[i].getGlobalGeometry();
        for(unsigned int j=0;j<doors.size();++j){
            ClipperLib::Path pj=doors[j].getGlobalGeometry();
            violationArea+=Global::intersectionArea(pi,pj);
        }
    }
    //Checking if furniture is outside the room
    const ClipperLib::Path &roomGeo=room.getGeometry();
    for (unsigned int i=0;i<furnitures.size();++i){
        ClipperLib::Path pi=furnitures[i].getGlobalGeometry();
        violationArea+=Global::differenceArea(roomGeo,pi);
    }
    return violationArea/10000;
}

void CollisionCostCalculator::print(std::ostream &out)
{
    out<<"Collision Cost Calc: ";
}

CollisionCostCalculator::~CollisionCostCalculator()
{

}
