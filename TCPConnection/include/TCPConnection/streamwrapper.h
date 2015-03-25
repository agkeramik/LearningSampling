#ifndef STREAMWRAPPER_H
#define STREAMWRAPPER_H

#include "stream.h"

class StreamWrapper:public Stream
{
protected:
    Stream *s;
public:
    StreamWrapper(Stream *stream);
    virtual ssize_t send(const char* buffer, size_t len);
    virtual ssize_t receive(char* buffer, size_t len);
    virtual ~StreamWrapper();
};

#endif // STREAMWRAPPER_H
