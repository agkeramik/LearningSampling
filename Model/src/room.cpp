#include "Model/room.h"
#include "Geometry/clipper.hpp"
#include <sstream>

using namespace std;
using namespace pugi;
void Room::updateGeometry()
{
    geometry.clear();
    geometry<<ClipperLib::IntPoint(tlX,tlY)
           <<ClipperLib::IntPoint(tlX,brY)
          <<ClipperLib::IntPoint(brX,brY)
         <<ClipperLib::IntPoint(brX,tlY);
}

Room::Room()
{
}

Vec2 Room::getCentroid() const
{
    return Vec2(0.5*(tlX+brX),0.5*(tlY+brY));
}

std::vector<Furniture> &Room::getFurnitures()
{
    return furnitures;
}

const std::vector<Furniture> &Room::getFurnitures() const
{
    return furnitures;
}

const std::vector<Furniture> &Room::getDoors() const
{
    return doors;
}

const std::vector<Furniture> &Room::getWindows() const
{
    return windows;
}



void Room::addFurniture(Furniture &f)
{
    furnitures.push_back(f);
}

void Room::addDoor(Furniture &f)
{
    doors.push_back(f);
}
void Room::addWindow(Furniture &f)
{
    windows.push_back(f);
}

void Room::print(std::ostream &out) const
{
    out<<"<Room tlX=\""<<tlX<<"\" tlY=\""<<tlY<<"\" brX=\""<<brX<<"\" brY=\""<<brY<<"\">";
    out<<"<Furnitures>\n";
    for (unsigned int i=0;i<furnitures.size();++i){
        furnitures[i].print(out);
    }
    out<<"</Furnitures>\n";
    out<<"<DoorsOrWindows>\n";
    for (unsigned int i=0;i<doors.size();++i){
        doors[i].print(out);
    }
    for (unsigned int i=0;i<windows.size();++i){
        windows[i].print(out);
    }
    out<<"</DoorsOrWindows>\n";

    out<<"</Room>\n";
}

void Room::setBottomRightCorner(double X, double Y)
{
    //we are not checking any constraint
    brX=X;
    brY=Y;
    updateGeometry();
}

void Room::setTopLeftCorner(double X, double Y)
{
    //we are not checking any constraint
    tlX=X;
    tlY=Y;
    updateGeometry();
}

double Room::getTopLeftCornerX() const
{
    return tlX;
}

double Room::getTopLeftCornerY() const
{
    return tlY;
}

double Room::getBottomRightCornerX() const
{
    return brX;
}

double Room::getBottomRightCornerY() const
{
    return brY;
}

const ClipperLib::Path &Room::getGeometry() const
{
    return geometry;
}

void Room::print(std::ostream &out, double xo, double yo) const
{
    for (unsigned int i=0;i<furnitures.size();++i){
        Furniture f = furnitures[i];
        f.setX(f.getX()+xo);
        f.setY(f.getY()+yo);
        f.print(out);
    }
    for (unsigned int i=0;i<doors.size();++i){
        Furniture f = doors[i];
        f.setX(f.getX()+xo);
        f.setY(f.getY()+yo);
        f.print(out);
    }
    for (unsigned int i=0;i<windows.size();++i){
        Furniture f = windows[i];
        f.setX(f.getX()+xo);
        f.setY(f.getY()+yo);
        f.print(out);
    }
}

string Room::toXML() const
{
    stringstream ss;
    ss<<"<Room tlX=\""<<tlX<<"\" tlY=\""<<tlY<<"\" brX=\""<<brX<<"\" brY=\""<<brY<<"\">";
    ss<<"<Furnitures>\n";
    for (unsigned int i=0;i<furnitures.size();++i){
        ss<<furnitures[i].toXML();
    }
    ss<<"</Furnitures>\n";
    ss<<"<Doors>\n";
    for (unsigned int i=0;i<doors.size();++i){
        ss<<doors[i].toXML();
    }
    for (unsigned int i=0;i<windows.size();++i){
        ss<<windows[i].toXML();
    }
    ss<<"</Doors>\n";
    ss<<"</Room>\n";
    return ss.str();
}

Room Room::getNewRoom(pugi::xml_node room_node,FurnitureCatalog &catalog)
{
    Room room;
    if(room_node==NULL){
        cout<<"Error parsing room\n";
        return room;
    }
    room.setTopLeftCorner(room_node.attribute("tlX").as_double(),room_node.attribute("tlY").as_double());
    room.setBottomRightCorner(room_node.attribute("brX").as_double(),room_node.attribute("brY").as_double());

    xml_node furs=room_node.child("Furnitures");
    if(furs!=NULL){
        for(xml_node furniture_node=furs.child("Furniture");furniture_node;furniture_node=furniture_node.next_sibling("Furniture")){
            Furniture furniture=catalog.getNewFurniture(furniture_node);
            room.addFurniture(furniture);
        }
    }
    xml_node doors_node=room_node.child("Doors");
    if(doors_node!=NULL){
        for(xml_node furniture_node=doors_node.child("Furniture");furniture_node;furniture_node=furniture_node.next_sibling("Furniture")){
            Furniture door=catalog.getNewFurniture(furniture_node);
            room.addDoor(door);
        }
    }
    return room;
}


Room::~Room()
{
}
