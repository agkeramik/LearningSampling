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
    std::vector<Furniture> doors;
    std::vector<Furniture> windows;

public:
    Room();
    std::vector<Furniture> &getFurnitures();
    void addFurniture(Furniture &f);
    const std::vector<Furniture> &getDoors() const;
    void addDoor(Furniture &f);
    const std::vector<Furniture> &getWindows() const;
    void addWindow(Furniture &f);
    void print(std::ostream &out) const;
    void setBottomRightCorner(double X,double Y);
    void setTopLeftCorner(double X,double Y);
    double getTopLeftCornerX() const;
    double getTopLeftCornerY() const;
    double getBottomRightCornerX() const;
    double getBottomRightCornerY() const;
    void print(std::ostream &out, double xo, double yo) const;
    virtual ~Room();
};

#endif // ROOM_H
