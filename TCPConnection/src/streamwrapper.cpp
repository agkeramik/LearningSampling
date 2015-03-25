#include "TCPConnection/streamwrapper.h"

StreamWrapper::StreamWrapper(Stream *stream)
{
    if(stream==NULL)
        throw "Stream NULL Pointer";
    s=stream;
}

ssize_t StreamWrapper::send(const char *buffer, size_t len)
{
    return s->send(buffer,len);
}

ssize_t StreamWrapper::receive(char *buffer, size_t len)
{
    return s->receive(buffer,len);
}

StreamWrapper::~StreamWrapper()
{
    if(s!=NULL)
        delete s;
}
