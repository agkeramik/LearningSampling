#include "TCPConnection/messagestreamwrapper.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <pugixml/pugixml.hpp>
#include "Model/room.h"
#include "TCPConnection/furnishmessage.h"
#include "TCPConnection/message.h"
#include "TCPConnection/replyfurnishmessage.h"


using namespace std;
using namespace pugi;

int MessageStreamWrapper::parseHeader(const char *h)
{
    int len;
    if(sscanf (h,"<message len=\"%d\">",&len)==1)//successfully filled
        return len;
    return -1;
}

MessageStreamWrapper::MessageStreamWrapper(Stream *stream, FurnitureCatalog *catalog):
    StreamWrapper(stream),
    _catalog(catalog)
{
}

void MessageStreamWrapper::sendMessage(Message *message)
{
    string s=message->toXML();
    send(s.c_str(),s.length());
}

Message* MessageStreamWrapper::pullMessage()
{
    //read the header
    const int footerSize=10;
    char header[128];
    int recievedLen=receive(header,128);
    //TODO
    //check if receivedlen<0

    //parse header
    int messageLen=parseHeader(header);
    if(messageLen==-1)
        return NULL;

    int dataOffset=0;
    for(int i=0;i<recievedLen;++i)
        if(header[i]=='>'){
            dataOffset=i+1;
            break;
        }
    //taking into account the \0 that we should set
    const int totalLen=dataOffset+messageLen+footerSize+1;
    char *message=new char[totalLen];

    //    get the rest of the request
    memcpy((void*) (message),(void*) header,recievedLen);
    while(recievedLen<totalLen-1){
        int r=receive(message+recievedLen,totalLen-1-recievedLen);
        recievedLen+=r;
    }
    message[totalLen-1]='\0';

    Message *mes=Message::parse(message,_catalog);
    delete message;
    return mes;
}

MessageStreamWrapper::~MessageStreamWrapper()
{

}
