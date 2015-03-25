#include "TCPConnection/replyfurnishmessage.h"

ReplyFurnishMessage::ReplyFurnishMessage():
    Message(ReplyFurnishMessageType)
{

}

string ReplyFurnishMessage::parametersToXML() const
{
    string s="<Rooms>\n";
    for(unsigned int i=0;i<rooms.size();++i){
           s+=rooms[i].toXML();
           s+="\n";
    }
    s+="</Rooms>\n";
    return s;
}

void ReplyFurnishMessage::parseParameters(xml_node parameters_node, FurnitureCatalog *catalog)
{
    rooms.clear();
    xml_node rooms_node=parameters_node.child("Rooms");
    if(rooms_node==NULL)
        return;
    for(xml_node room_node=rooms_node.child("Room");
        room_node;
        room_node=room_node.next_sibling("Room")){
        Room room=Room::getNewRoom(room_node,*catalog);
        rooms.push_back(room);
    }
}

std::vector<Room> &ReplyFurnishMessage::getRooms()
{
    return rooms;
}

void ReplyFurnishMessage::setRooms(std::vector<Room> &rooms)
{
    this->rooms=rooms;
}



