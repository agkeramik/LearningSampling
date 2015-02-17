#include "room.h"

Room::Room()
{
}

const std::vector<Furniture*> &Room::getFurnitures() const
{
    return furnitures;
}

void Room::addFurniture(Furniture &f)
{
    furnitures.push_back(&f);
}


void Room::print(std::ostream &out) const
{
    out<<"<Room>\n";
    out<<"<Furnitures>\n";
    for (int i=0;i<furnitures.size();++i){
        furnitures[i]->print(out);
    }
    out<<"</Furnitures>\n";
    out<<"</Room>\n";
}

void Room::print(std::ostream &out, double xo, double yo){

    for (int i=0;i<furnitures.size();++i){
        Furniture f = *(furnitures[i]);
        f.setX(f.getX()+xo);
        f.setY(f.getY()+yo);
        f.print(out);
    }

}

Room::~Room()
{
}
