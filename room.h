#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <ostream>

#include "Furniture.h"
class Room
{
    std::vector<Furniture*> furnitures;

public:
    Room();
    const std::vector<Furniture*>  &getFurnitures() const;
    void addFurniture(Furniture &f);
    void print(std::ostream &out) const;
    virtual ~Room();
};

#endif // ROOM_H
