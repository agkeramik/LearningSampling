#include "ConversationCostCalculator.h"

double ConversationCostCalculator::costFunction(double delta){
    return exp(delta / 30.0) - 1.0;
}

double ConversationCostCalculator::deltaAngle(Furniture &f1, Furniture &f2){

    Polygon f1g = f1.getTransformedGeometry();
    Point centroid1 = Global::centroid(f1g);
    Polygon f2g = f2.getTransformedGeometry();
    Point centroid2 = Global::centroid(f2g);
    Vector v(centroid1, centroid2);
    Vector xaxis(1,0);
    double a = (f1.getTheta() - Global::angle(v, xaxis)) * 180.0 / 3.14;
    if (360.0 - a < a)
        a = 360 - a;
    return a;
}

double ConversationCostCalculator::calculateCost(Furniture &furniture){
    double cost = 0;
    const vector<Furniture *> alreadyPlaced = getRoom().getFurnitures();\
    for (int i = 0; i < alreadyPlaced.size(); ++i){
        cost += costFunction(deltaAngle(*(alreadyPlaced[i]), furniture)) + costFunction(deltaAngle(furniture, *(alreadyPlaced[i])));
    }

    return cost;
}

ConversationCostCalculator::~ConversationCostCalculator() {}
