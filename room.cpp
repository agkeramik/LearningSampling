#include "room.h"

Room::Room()
{
}

std::vector<Furniture> &Room::getFurnitures()
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
    out<<"</Room>\n";
}

void Room::setBottomRightCorner(double X, double Y)
{
    //we are not checking any constraint
    brX=X;
    brY=Y;
}

void Room::setTopLeftCorner(double X, double Y)
{
    //we are not checking any constraint
    tlX=X;
    tlY=Y;
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

void Room::print(std::ostream &out, double xo, double yo) const
{

    for (unsigned int i=0;i<furnitures.size();++i){
        Furniture f = furnitures[i];
        f.setX(f.getX()+xo);
        f.setY(f.getY()+yo);
        f.print(out);
    }
}

Room::~Room()
{
}
