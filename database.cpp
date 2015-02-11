#include "database.h"
#include <pugixml.hpp>

using namespace pugi;

Database::Database(const char *xmlFileName)
{
    xml_document doc;
    if(!doc.load_file(xmlFileName)){
        std::cout<<"Error Loading XML File:"<<*xmlFileName;
        return;
    }
    xml_node root=doc.child("root");
    for(xml_node room_node=root.child("Room");room_node;room_node=room_node.next_sibling("Room")){
        Room room;
        xml_node furs=room_node.child("Furnitures");
        if (furs==NULL)
            continue;
        for(xml_node furniture_node=furs.child("Furniture");furniture_node;furniture_node=furniture_node.next_sibling("Furniture")){
            Furniture furniture;
            furniture.setDepth(furniture_node.attribute("depth").as_double());
            furniture.setWidth(furniture_node.attribute("width").as_double());
            furniture.setHeight(furniture_node.attribute("height").as_double());
            furniture.setTheta(furniture_node.attribute("rotation").as_double());
            furniture.catalogId=std::string(furniture_node.child("CatalogId").text().as_string());
            xml_node pos_node=furniture_node.child("Position");
            furniture.setX(pos_node.attribute("posX").as_double());
            furniture.setY(pos_node.attribute("posY").as_double());
            room.addFurniture(furniture);
        }
        rooms.push_back(room);
    }
}

unsigned int Database::nb_rooms() const
{
    return rooms.size();
}

const Room &Database::room(int i) const
{
    if(i<rooms.size())
        return rooms[i];
    throw "Index out Of bounds";
}

void Database::print() const
{
    for (int i=0;i<rooms.size();++i){
        rooms[i].print(std::cout);
    }
}
