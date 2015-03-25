#ifndef DATABASE_H
#define DATABASE_H
#include <vector>
#include "Model/room.h"
#include "Model/furniturecatalog.h"

class Database
{
    std::vector<Room> rooms;
public:
    Database(const char *xmlFileName, FurnitureCatalog &cat);
    unsigned int nb_rooms() const;
    const Room &room(unsigned int i) const;
    void print() const;
};

#endif // DATABASE_H
