#include "Context.h"

Context::Context(Properties &p) :
    catalog(p.getFurnitureInfo().c_str()),
    mixtures(MGMM::loadMGMM(p.getFurnitureCount().c_str(), p.getGMMsFolder().c_str()))
{

}

Context::Context(Room &_room, FurnitureCatalog &_catalog, MGMM &_mixtures) :
    room(_room),
    catalog(_catalog),
    mixtures(_mixtures)
{
}

void Context::addFurnitureToList(const char* catalogId){
    this->toAdd.push_back(this->catalog.getNewFurniture(catalogId));
}

Context::~Context()
{
}

void Context::printLibrary() const
{
    catalog.print();
}
