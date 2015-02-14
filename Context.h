#ifndef CONTEXT_H
#define CONTEXT_H

#include "room.h"
#include "furniturecatalog.h"
#include "properties.h"
#include "mgmm.h"
#include <vector>
#include <string>

using namespace std;

class Context
{
public:
    Room room;
    FurnitureCatalog catalog;
    MGMM mixtures;
    vector<Furniture> toAdd;

    Context(Properties &p);
    Context(Room &_room, FurnitureCatalog &_catalog, MGMM &_mixtures);
    void addFurnitureToList(const char* catalogId);
    void printLibrary() const;
	virtual ~Context();
};

#endif
