#ifndef REQUESTSTREAMWRAPPER_H
#define REQUESTSTREAMWRAPPER_H

#include "streamwrapper.h"
#include "Model/furniturecatalog.h"
#include "TCPConnection/message.h"


class MessageStreamWrapper:public StreamWrapper
{
    int parseHeader(const char* h);
    FurnitureCatalog *_catalog;
public:
    /**
     * @brief MessageStreamWrapper
     *  Constructs a wrapper of the stream
     * @param stream
     *  The stream will be saved as a field in the class
     *  The class is responsible of managing memory
     * @param catalog
     *  The class will store a pointer to the catalog
     *  Note the class will not manage the memory corresponding to catalog
     */
    MessageStreamWrapper(Stream *stream,FurnitureCatalog *catalog);


    /**
     * @brief getRequest
     *  will parse the xml request taken from the stream
     * @return
     *  A Message pointer, or NULL in case the message has bad format
     *  Note that the user is responsibe of managing memory
     *  of the returned value
     */
    Message *pullMessage();

    /**
     * @brief sendMessage
     * @param message
     */
    void sendMessage(Message* message);


    /**
     * @brief ~MessageStreamWrapper
     *  The destructor closes the stream
     *  and deletes the pointer to the stream
     */
    virtual ~MessageStreamWrapper();
};

#endif // REQUESTSTREAMWRAPPER_H
