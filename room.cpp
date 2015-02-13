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

Room::~Room()
{
//    for (int i = 0; i < this->furnitures.size(); ++i)
//        delete this->furnitures[i];
//    std::cout << "room delete" << std::endl;
}
