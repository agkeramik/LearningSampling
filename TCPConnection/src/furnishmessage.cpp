#include "TCPConnection/furnishmessage.h"
#include <pugixml/pugixml.hpp>

using namespace pugi;

FurnishMessage::FurnishMessage():
    Message(FurnishMessageType)
{

}

void FurnishMessage::setRoom(Room _roomProperties)
{
    roomProperties=_roomProperties;
}

string FurnishMessage::parametersToXML() const
{
    return roomProperties.toXML();

}

void FurnishMessage::parseParameters(xml_node parameters_node, FurnitureCatalog *catalog)
{
    xml_node room_node=parameters_node.child("Room");
    if(room_node!=NULL)
        roomProperties=Room::getNewRoom(room_node,*catalog);
}

Room FurnishMessage::getRoom()
{
    return roomProperties;
}
