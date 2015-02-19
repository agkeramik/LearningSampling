#include "Context.h"

Context::Context(Room &_room, const FurnitureCatalog &_catalog, const MGMM &_mixtures) :
    room(_room),
    catalog(_catalog),
    mixtures(_mixtures)
{
}

void Context::addFurnitureToList(const char* catalogId){
    this->toAdd.push_back(this->catalog.getNewFurniture(catalogId));
}

void Context::addFurnituresFromFile(const char *filePath){
    ifstream file;
    file.open(filePath);
    string line;
    while (getline(file, line) > 0)
        this->addFurnitureToList(line.c_str());
    file.close();
}

Context::~Context()
{
}

void Context::printLibrary() const
{
    catalog.print();
}
