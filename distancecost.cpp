#include "distancecost.h"

double DistanceCost::basicEval(double distance, double m, double M) const
{
    //TODO check if distance is positive
    if(distance<m)
        return -distance*distance/(m*m);
    else if(distance>M)
        return -M*M/(distance*distance);
    return -1;
}

DistanceCost::DistanceCost(double weight):Cost(weight)
{
}

double DistanceCost::minCornerDistance(const ClipperLib::Path &p1, const ClipperLib::Path &p2) const
{
    double minDist=std::numeric_limits<double>::max();
    for(unsigned int i=0;i<p1.size();++i){
        for(unsigned int j=0;j<p2.size();++j){
            minDist=std::min(minDist,ClipperLib::DistanceSqrd(p1[i],p2[j]));
        }
    }
    return minDist;
}

double DistanceCost::calculate(const Room &room) const
{
    //give a weight for the pairwise relationship
    double cost = 0;
    const vector<Furniture> &furnitures = room.getFurnitures();
    for(unsigned int i=0;i<furnitures.size()-1;++i){
        if(furnitures[i].catalogId!="Renouzate#sofa2")
            continue;
        ClipperLib::Path pi = furnitures[i].getGlobalGeometry();
        for(unsigned int j=i+1;j<furnitures.size();++j){
            if(furnitures[j].catalogId!="Renouzate#sofa2")
                continue;
            ClipperLib::Path pj = furnitures[j].getGlobalGeometry();
//            cost += basicEval(std::sqrt(Global::distanceSqrd(pi, pj)),15,30);
             cost += basicEval(std::sqrt(minCornerDistance(pi, pj)),15,25);
        }
    }
    return weight*cost;
}
