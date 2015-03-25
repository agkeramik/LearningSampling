#include "Engine/database.h"
#include <pugixml/pugixml.hpp>

using namespace pugi;

Database::Database(const char *xmlFileName,FurnitureCatalog &cat)
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
        if(furs==NULL)
            continue;
        for(xml_node furniture_node=furs.child("Furniture");furniture_node;furniture_node=furniture_node.next_sibling("Furniture")){
            Furniture furniture=cat.getNewFurniture(furniture_node);
            room.addFurniture(furniture);
        }
        xml_node walls=room_node.child("Walls");
        double minX=std::numeric_limits<double>::max(),
                minY=std::numeric_limits<double>::max(),
                maxX=std::numeric_limits<double>::min(),
                maxY=std::numeric_limits<double>::min();
        for(xml_node wall_node=walls.child("Wall");wall_node;wall_node=wall_node.next_sibling("Wall")){
            xml_node start_node=wall_node.child("Start");
            double X=start_node.attribute("x").as_double();
            double Y=start_node.attribute("y").as_double();
            if(X<minX)
                minX=X;
            if(Y<minY)
                minY=Y;
            if(X>maxX)
                maxX=X;
            if(Y>maxY)
                maxY=Y;
            xml_node end_node=wall_node.child("End");
            X=end_node.attribute("x").as_double();
            Y=end_node.attribute("y").as_double();
            if(X<minX)
                minX=X;
            if(Y<minY)
                minY=Y;
            if(X>maxX)
                maxX=X;
            if(Y>maxY)
                maxY=Y;
        }
        room.setBottomRightCorner(maxX,maxY);
        room.setTopLeftCorner(minX,minY);
        rooms.push_back(room);
    }
}

unsigned int Database::nb_rooms() const
{
    return rooms.size();
}

const Room &Database::room(unsigned int i) const
{
    if(i<rooms.size())
        return rooms[i];
    throw "Index out Of bounds";
}

void Database::print() const
{
    for(unsigned int i=0;i<rooms.size();++i){
        rooms[i].print(std::cout);
    }
}
