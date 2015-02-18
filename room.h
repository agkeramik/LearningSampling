#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <ostream>

#include "Furniture.h"
class Room
{
    double tlX,tlY;//Top Left X. Top Left Y
    double brX,brY;
    std::vector<Furniture> furnitures;

public:
    Room();
    const std::vector<Furniture>  &getFurnitures() const;
    void addFurniture(Furniture &f);
    void print(std::ostream &out) const;
    void setBottomRightCorner(double X,double Y);
    void setTopLeftCorner(double X,double Y);
    double getTopLeftCornerX() const;
    double getTopLeftCornerY() const;
    double getBottomRightCornerX() const;
    double getBottomRightCornerY() const;
    virtual ~Room();
};

#endif // ROOM_H
