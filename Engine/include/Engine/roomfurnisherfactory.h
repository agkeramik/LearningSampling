#ifndef ROOMFURNISHERFACTORY_H
#define ROOMFURNISHERFACTORY_H

#include "Utils/properties.h"

class RoomFurnisher;
class RoomSampler;
class FurnitureCatalog;

//not yet working
class RoomFurnisherFactory
{
    RoomSampler *roomSampler;
    FurnitureCatalog *catalog;
public:
    RoomFurnisherFactory(FurnitureCatalog *catalog);

};

#endif // ROOMFURNISHERFACTORY_H
