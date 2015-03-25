#ifndef FURNITURECATALOG_H
#define FURNITURECATALOG_H

#include <map>
#include <string>
#include "Model/Furniture.h"
#include <pugixml/pugixml.hpp>

class Furniture;

class FurnitureCatalog
{
    std::map<std::string,Furniture> catalog;
public:
    FurnitureCatalog(const char *catalogFileName);
    Furniture getNewFurniture(const std::string &catalogId) const;
    Furniture getNewFurniture(pugi::xml_node furniture_node) const;
    void print() const;
    ~FurnitureCatalog();
};

#endif // FURNITURECATALOG_H
