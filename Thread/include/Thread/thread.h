#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

class Thread
{
    pthread_t tid;
    bool running;
    bool detached;
public:
    Thread();
    int start();
    int join();
    int detach();
    pthread_t self();
    virtual void *run()=0;
    virtual ~Thread();
};


#endif // THREAD_H
