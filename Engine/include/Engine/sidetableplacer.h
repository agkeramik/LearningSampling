#ifndef SIDETABLEPLACER_H
#define SIDETABLEPLACER_H

#include "Model/furniturecatalog.h"
#include "Model/room.h"

class SideTablePlacer
{
    FurnitureCatalog *catalog;
    void addTable1x1(Room &room);
    bool collisionCheck(const Furniture &f,const Room &room);
public:
    SideTablePlacer(FurnitureCatalog *_catalog);
    int placeSideTable(Room &room,int count=2);
};

#endif // SIDETABLEPLACER_H
