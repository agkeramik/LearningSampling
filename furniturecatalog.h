#ifndef FURNITURECATALOG_H
#define FURNITURECATALOG_H

#include <map>
#include <string>
#include "Furniture.h"

class FurnitureCatalog
{
    std::map<std::string,Furniture> catalog;
public:
    FurnitureCatalog(const char *catalogFileName);
    Furniture getNewFurniture(const std::string &catalogId) const;
    void print() const;
};

#endif // FURNITURECATALOG_H
