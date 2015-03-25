#ifndef STREAM_H
#define STREAM_H

#include "unistd.h"

class Stream
{
public:
    Stream();
    virtual ssize_t send(const char* buffer, size_t len)=0;
    virtual ssize_t receive(char* buffer, size_t len)=0;
    virtual ~Stream();
};

#endif // STREAM_H
