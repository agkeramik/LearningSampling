#ifndef DATABASE_H
#define DATABASE_H
#include <vector>
#include "Furniture.h"
#include "room.h"

class Database
{
    Room* currentRoom;
    Furniture* currentFurniture;
    std::vector<Room> rooms;
public:
    Database(const char *xmlFileName);
    unsigned int nb_rooms() const;
    const Room &room(int i) const;
    void print() const;
};

#endif // DATABASE_H
