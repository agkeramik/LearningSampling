#ifndef ROOMOPTIMISER_H
#define ROOMOPTIMISER_H

#include "cost.h"
#include "Model/Furniture.h"
#include "Model/room.h"

class RoomOptimiser
{
    Cost *eval;
    void walkFurniture(Furniture &f);
public:
    RoomOptimiser(Cost *_eval);
    Cost *getEvaluationFunction() const;
    double optimise(Room &room,int cycles=100);

};

#endif // ROOMOPTIMISER_H
