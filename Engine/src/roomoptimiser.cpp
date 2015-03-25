#include "Engine/roomoptimiser.h"

RoomOptimiser::RoomOptimiser(Cost *_eval):
    eval(_eval)
{

}

Cost *RoomOptimiser::getEvaluationFunction() const
{
    return eval;
}

double RoomOptimiser::optimise(Room &room, int cycles)
{
    vector<Furniture> &f = room.getFurnitures();
    double lastCost = eval->calculate(room);
    for (int i = 0; i < cycles; ++i){
        for (unsigned int count = 0; count < f.size(); ++count){
            unsigned int j=rand()%f.size();
            Furniture &furniture = f[j];
            if (!furniture.isMovable())
                continue;
            double ox = furniture.getX();
            double oy = furniture.getY();
            double ot = furniture.getTheta();
            walkFurniture(furniture);
            double cost = eval->calculate(room);
            if (cost < lastCost){
                lastCost = cost;
            }else{
                furniture.setX(ox);
                furniture.setY(oy);
                furniture.setTheta(ot);
            }
        }
    }
    return lastCost;
}

void RoomOptimiser::walkFurniture(Furniture &f){
    if(rand()%2==0)
        f.setX(f.getX() + 4.0*rand()/RAND_MAX - 2.0);
    else
        f.setY(f.getY() + 4.0*rand()/RAND_MAX - 2.0);
    if(rand()%10<3)
        f.setTheta((f.getTheta() + 3.14/90*rand()/RAND_MAX - 3.14/180));
}
