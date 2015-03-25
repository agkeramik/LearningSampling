#ifndef ANGLESNAPPER_H
#define ANGLESNAPPER_H
#include "Model/room.h"

class AngleSnapper
{
    double range_2;
    double period;
    bool shouldSnap(int theta);
public:
    AngleSnapper(double period, double range_2);
    void snapFurntiureAngles(Room &room);
};

#endif // ANGLESNAPPER_H
