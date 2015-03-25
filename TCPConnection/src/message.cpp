#include "TCPConnection/message.h"
#include <sstream>
#include <Model/room.h>
#include "TCPConnection/furnishmessage.h"
#include "TCPConnection/replyfurnishmessage.h"

using namespace std;
using namespace pugi;

const char *Message::MessageTypeString[]= {
    "Furnish","ReplyFurnish"
};

Message::Message(MessageType _type):
    type(_type)
{

}

MessageType Message::getType()
{
    return type;
}

std::string Message::toXML() const
{

    string message="<type name=\"";
    message+=MessageTypeString[type];
    message+="\"/>";
    message+="<parameters>\n";
    message+=parametersToXML();
    message+="</parameters>\n";

    string header="<message len=\"";
    ostringstream ss;
    ss<<message.length();
    header+=ss.str();
    header+="\">";
    string footer="</message>";
    string total=header+message+footer;
    return total;
}

Message *Message::parse(const char *message,FurnitureCatalog *catalog)
{
    size_t len=strlen(message);
    xml_document doc;
    if(!doc.load_buffer((void*)message,len)){
        return NULL;
    }
    xml_node message_node=doc.child("message");
    if(message_node==NULL)
        return NULL;
    xml_node type_node=message_node.child("type");
    if (type_node==NULL)
        return NULL;
    xml_node parameters_node=message_node.child("parameters");
    if(parameters_node==NULL)
        return NULL;
    Message *messageObject=NULL;
    if(strcmp(type_node.attribute("name").as_string(),
              MessageTypeString[FurnishMessageType])==0){
        messageObject=new FurnishMessage();
    }else if(strcmp(type_node.attribute("name").as_string(),
                     MessageTypeString[ReplyFurnishMessageType])==0){
        messageObject=new ReplyFurnishMessage();
    }
    messageObject->parseParameters(parameters_node,catalog);
    return messageObject;
}

Message::~Message()
{

}
