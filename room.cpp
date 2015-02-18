#include "room.h"

Room::Room()
{
}

const std::vector<Furniture> &Room::getFurnitures() const
{
    return furnitures;
}

void Room::addFurniture(Furniture &f)
{
    furnitures.push_back(f);
}


void Room::print(std::ostream &out) const
{
    out<<"<Room tlX=\""<<tlX<<"\" tlY=\""<<tlY<<"\" brX=\""<<brX<<"\" brY=\""<<brY<<"\">";
    out<<"<Furnitures>\n";
    for (int i=0;i<furnitures.size();++i){
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

Room::~Room()
{

}
