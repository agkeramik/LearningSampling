#ifndef REPLYFURNISHMESSAGE_H
#define REPLYFURNISHMESSAGE_H

#include "TCPConnection/message.h"
#include <vector>
#include "Model/room.h"

class ReplyFurnishMessage:public Message
{
    std::vector<Room> rooms;
public:
    ReplyFurnishMessage();
    virtual string parametersToXML() const;
    virtual void parseParameters(xml_node parameters_node, FurnitureCatalog *catalog);
    std::vector<Room> &getRooms();
    void setRooms(std::vector<Room> &rooms);
};

#endif // REPLYFURNISHMESSAGE_H
