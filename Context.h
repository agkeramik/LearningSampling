#ifndef CONTEXT_H
#define CONTEXT_H

#include "room.h"
#include "furniturecatalog.h"
#include "properties.h"
#include "mgmm.h"
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Context
{
public:
    Room room;
    const FurnitureCatalog &catalog;
    const MGMM &mixtures;
    vector<Furniture> toAdd;

    Context(Room &_room, const FurnitureCatalog &_catalog,const MGMM &_mixtures);
    void addFurnitureToList(const char *catalogId);
    void addFurnituresFromFile(const char *filePath);
    void printLibrary() const;
	virtual ~Context();
};

#endif
