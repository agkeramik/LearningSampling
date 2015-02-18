#include "DistanceCostCalculator.h"

void DistanceCostCalculator::setSeverity(double severtiy) {this->severtiy = severtiy;}

double DistanceCostCalculator::getSeverity() {return severtiy;}

void DistanceCostCalculator::setStartRange(double startRange) {this->startRange = startRange;}

double DistanceCostCalculator::getStartRange() {return startRange;}

void DistanceCostCalculator::setEndRange(double endRange) {this->endRange = endRange;}

double DistanceCostCalculator::getEndRange() {return endRange;}

DistanceCostCalculator::DistanceCostCalculator(Room &_room) : CostCalculator(_room) {
    this->setSeverity(5.0);
    this->setStartRange(100.0);
    this->setEndRange(300.0);
}

double DistanceCostCalculator::calculateCost(Furniture &furniture){
    double cost = 0;

    const vector<Furniture *> alreadyPlaced = getRoom().getFurnitures();
    Polygon f = furniture.getTransformedGeometry();
    for (int i = 0; i < alreadyPlaced.size(); ++i){
        Polygon p = alreadyPlaced[i]->getTransformedGeometry();
        cost += Global::distanceCost(
                                Global::distance(f, p),
                                this->getStartRange(),
                                this->getEndRange(),
                                this->getSeverity());
    }

    return cost;
}

DistanceCostCalculator::~DistanceCostCalculator() {}
