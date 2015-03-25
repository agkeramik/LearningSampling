#ifndef WQUEUE_H
#define WQUEUE_H

#include <queue>
#include <pthread.h>
#include <iostream>

using namespace std;

template <typename T>
class WQueue
{
    queue<T> _queue;
    pthread_mutex_t _mutex;
    pthread_cond_t _cond;
public:
    WQueue()
    {
        pthread_mutex_init(&_mutex,NULL);
        pthread_cond_init(&_cond,NULL);
    }

    void enqueue(T item)
    {
        pthread_mutex_lock(&_mutex);
        _queue.push(item);
        pthread_cond_signal(&_cond);
        pthread_mutex_unlock(&_mutex);
    }

    T dequeue()
    {
        pthread_mutex_lock(&_mutex);
        while(_queue.size()==0)
            pthread_cond_wait(&_cond,&_mutex);
        cout<<_queue.size()<<endl;
        T t=_queue.front();
        _queue.pop();
        pthread_mutex_unlock(&_mutex);
        return t;
    }

    virtual ~WQueue()
    {
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_cond);
    }
};

#endif // WQUEUE_H
