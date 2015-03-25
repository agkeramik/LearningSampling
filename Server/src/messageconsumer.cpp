#include "Server/messageconsumer.h"
#include <iostream>

MessageConsumer::MessageConsumer(WQueue<WorkItem *> &_queue):
    queue(_queue)
{
}

void *MessageConsumer::run()
{
    while(1){
        cout<<"Thread"<<self()<<" taking from queue\n";
        WorkItem* item=queue.dequeue();
        item->processMessage();
        delete item;
    }
    return NULL;
}

MessageConsumer::~MessageConsumer()
{

}
