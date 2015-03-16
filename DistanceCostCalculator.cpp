#include "DistanceCostCalculator.h"
#include <math.h>
#include <limits>

void DistanceCostCalculator::setSeverity(double severtiy)
{
    this->severtiy = severtiy;
}

double DistanceCostCalculator::getSeverity()
{
    return severtiy;
}

void DistanceCostCalculator::setStartRange(double startRange)
{
    this->startRange = startRange;
}

double DistanceCostCalculator::getStartRange()
{
    return startRange;
}


void DistanceCostCalculator::setEndRange(double endRange)
{
    this->endRange = endRange;
}

void DistanceCostCalculator::print(std::ostream &out)
{
    out<<"Distance Cost Calc: ";
}

double DistanceCostCalculator::getEndRange()
{
    return endRange;
}

double DistanceCostCalculator::basicEval(double distance, double m, double M)
{
    //TODO check if distance is positive
    if(distance<m)
        return -distance*distance/(m*m);
    else if(distance>M)
        return -M*M/(distance*distance);
    return -1;
}

DistanceCostCalculator::DistanceCostCalculator() : CostCalculator() {
    this->setSeverity(5.0);
    this->setStartRange(100.0);
    this->setEndRange(300.0);
}

double minCornerDistance(const ClipperLib::Path &p1,const ClipperLib::Path &p2){
    double minDist=std::numeric_limits<double>::max();
    for(unsigned int i=0;i<p1.size();++i){
        for(unsigned int j=0;j<p2.size();++j){
            minDist=std::min(minDist,ClipperLib::DistanceSqrd(p1[i],p2[j]));
        }
    }
    return minDist;
}

double DistanceCostCalculator::calculateCost(const Room &room){
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
    return cost;
}

DistanceCostCalculator::~DistanceCostCalculator()
{

}
