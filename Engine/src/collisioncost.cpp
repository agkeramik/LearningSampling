#include "Engine/collisioncost.h"
#include "Geometry/clipper.hpp"

CollisionCost::CollisionCost(double weight):Cost(weight)
{
}

double CollisionCost::calculate(const Room &room) const
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

    //check if there is any collision with the doors
    const vector<Furniture> &doors=room.getDoors();
    for(unsigned int i=0;i<furnitures.size();++i){
        ClipperLib::Path pi=furnitures[i].getGlobalGeometry();
        for(unsigned int j=0;j<doors.size();++j){
            ClipperLib::Path pj=doors[j].getGlobalGeometry();
            violationArea+=Global::intersectionArea(pi,pj);
        }
    }

    //Check if furniture is outside the room
    const ClipperLib::Path &roomGeo=room.getGeometry();
    for (unsigned int i=0;i<furnitures.size();++i){
        ClipperLib::Path pi=furnitures[i].getGlobalGeometry();
        double area=Global::differenceArea(roomGeo,pi);
//        std::cout<<"Area difference "<<furnitures[i].catalogId<<"= "<<area<<std::endl;
        violationArea+=area;
    }
    return weight*violationArea/10000;
}
