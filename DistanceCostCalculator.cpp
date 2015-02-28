#include "DistanceCostCalculator.h"

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


double DistanceCostCalculator::calculateCost(Room &room){
    //give a weight for the pairwise relationship
    double cost = 0;
    vector<Furniture> &furnitures = room.getFurnitures();
    for(unsigned int i=0;i<furnitures.size()-1;++i){
        Polygon pi = furnitures[i].getTransformedGeometry();
        for(unsigned int j=i+1;j<furnitures.size();++j){
            Polygon pj = furnitures[j].getTransformedGeometry();
            cost += basicEval(Global::distance(pi, pj),30,50);
        }
    }
    return cost;
}

DistanceCostCalculator::~DistanceCostCalculator()
{

}