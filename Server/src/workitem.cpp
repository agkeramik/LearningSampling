#include "Server/workitem.h"
#include "TCPConnection/messagestreamwrapper.h"

#include <iostream>

using namespace std;
WorkItem::WorkItem(MessageStreamWrapper *_stream, Dispatcher *_dispatcher):
    stream(_stream),
    dispatcher(_dispatcher)
{

}

void WorkItem::processMessage()
{
    Message* message=stream->pullMessage();
    if(message!=NULL){
        Message* result=dispatcher->dispatch(message);
        if(result!=NULL){
            stream->sendMessage(result);
            delete result;
        }
        delete message;
    }

}

WorkItem::~WorkItem()
{
    delete stream;
}
