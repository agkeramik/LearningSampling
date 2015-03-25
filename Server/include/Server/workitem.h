#ifndef WORKITEM_H
#define WORKITEM_H

#include "TCPConnection/messagestreamwrapper.h"
#include "Server/dispatcher.h"

class WorkItem
{

    MessageStreamWrapper *stream;
    Dispatcher *dispatcher;

public:

    /**
     * @brief WorkItem
     * @param _stream
     *  Note the _stream's memory will be handled by the class
     * @param _dispatcher
     *  Note the dispatcher's memory will not be handled by the class
     */
    WorkItem(MessageStreamWrapper *_stream, Dispatcher *_dispatcher);

    /**
     * @brief processMessage
     *  Process the request
     */
    void processMessage();

    /**
     * @brief ~WorkItem
     *  Frees the memory corresponding to the stream
     *  Note that the dispatcher'memory is not handled by the class
     */
    virtual ~WorkItem();
};

#endif // WORKITEM_H
