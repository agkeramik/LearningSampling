#ifndef DATABASE_H
#define DATABASE_H
#include <vector>
#include "Furniture.h"
#include "room.h"

class Database
{
    std::vector<Room> rooms;
public:
    Database(const char *xmlFileName);
};

#endif // DATABASE_H
