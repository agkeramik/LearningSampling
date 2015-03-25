#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <pugixml/pugixml.hpp>
#include "Model/furniturecatalog.h"

using namespace pugi;
using namespace std;

enum MessageType{
    FurnishMessageType,
    ReplyFurnishMessageType
};

class Message
{
protected:
    static const char * MessageTypeString[];
    MessageType type;
public:
    Message(MessageType _type);
    MessageType getType();
    string toXML() const;
    virtual string parametersToXML() const =0;
    virtual void parseParameters(xml_node parameters_node, FurnitureCatalog *catalog)=0;
    static Message *parse(const char *message_node, FurnitureCatalog *catalog);
    virtual ~Message();
};

#endif // MESSAGE_H
