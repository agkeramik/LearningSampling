#ifndef FURNISHMESSAGE_H
#define FURNISHMESSAGE_H

#include "TCPConnection/message.h"
#include "Model/room.h"

class FurnishMessage:public Message
{
    Room roomProperties;
public:
    FurnishMessage();
    void setRoom(Room _roomProperties);
    virtual string parametersToXML() const;
    virtual void parseParameters(xml_node parameters_node, FurnitureCatalog *catalog);
    Room getRoom();
};

#endif // FURNISHMESSAGE_H
