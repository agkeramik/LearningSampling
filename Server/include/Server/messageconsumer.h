#ifndef MESSAGECONSUMER_H
#define MESSAGECONSUMER_H

#include "Thread/thread.h"
#include "Thread/wqueue.h"
#include "Server/workitem.h"

class MessageConsumer:public Thread
{
    WQueue<WorkItem *> &queue;
public:
    MessageConsumer(WQueue<WorkItem *> &_queue);
    virtual void *run();
    virtual ~MessageConsumer();
};

#endif // MESSAGECONSUMER_H
