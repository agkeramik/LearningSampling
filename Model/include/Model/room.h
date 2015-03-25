#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <ostream>
#include "Geometry/Global.h"
#include "Furniture.h"
#include <pugixml/pugixml.hpp>
#include <string>


class Room
{
    double tlX,tlY;//Top Left X. Top Left Y
    double brX,brY;
    ClipperLib::Path geometry;
    std::vector<Furniture> furnitures;
    std::vector<Furniture> doors;
    std::vector<Furniture> windows;
    void updateGeometry();

public:
    Room();
    Vec2 getCentroid() const;
    std::vector<Furniture> &getFurnitures();
    const std::vector<Furniture> &getFurnitures() const;
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
    const ClipperLib::Path &getGeometry() const;
    void print(std::ostream &out, double xo, double yo) const;
    std::string toXML() const;
    static Room getNewRoom(pugi::xml_node room_node, FurnitureCatalog &catalog);
    virtual ~Room();
};

#endif // ROOM_H
