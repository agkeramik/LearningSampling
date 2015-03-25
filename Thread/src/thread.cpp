#include "Thread/thread.h"

Thread::Thread():
    tid(0),
    running(false),
    detached(false)
{
}
static void *runThread(void *args){
    return ((Thread*) args)->run();
}

int Thread::start()
{
    if(!running){
        int result=pthread_create(&tid,NULL,runThread,this);
        if(result==0)
            running=true;
        return result;
    }
    return -1;

}

int Thread::join()
{
    int result=-1;
    if(running){
        result=pthread_join(tid,NULL);
        if(result==0)
            detached=true;
    }
    return result;
}

int Thread::detach()
{
    int result=-1;
    if(running && !detached){
        result=pthread_detach(tid);
        if (result==0)
            detached = true;
    }
    return result;
}

pthread_t Thread::self()
{
    return tid;
}

Thread::~Thread()
{
    if(running && !detached) {
        pthread_detach(tid);
    }
    if (running) {
        pthread_cancel(tid);
    }
}

