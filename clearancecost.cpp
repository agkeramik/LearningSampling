#include "clearancecost.h"
#include "clipper.hpp"

ClearanceCost::ClearanceCost(double weight):Cost(weight)
{
}

double ClearanceCost::calculate(const Room &room) const
{
    double violationArea = 0;
    const vector<Furniture> &furnitures = room.getFurnitures();
    for (unsigned int i=0;i<furnitures.size()-1;++i){
        ClipperLib::Path pi=furnitures[i].getClearanceGeometry();
        for (unsigned int j=i+1;j<furnitures.size();++j){
            ClipperLib::Path pj=furnitures[j].getClearanceGeometry();
            violationArea+=Global::intersectionArea(pi,pj);
        }
    }
    const vector<Furniture> &doors=room.getDoors();
    for(unsigned int i=0;i<furnitures.size();++i){
        ClipperLib::Path pi=furnitures[i].getClearanceGeometry();
        for(unsigned int j=0;j<doors.size();++j){
            ClipperLib::Path pj=doors[j].getClearanceGeometry();
            violationArea+=Global::intersectionArea(pi,pj);
        }
    }
    return weight*violationArea/10000;//conversion from cm2 to m2
}
