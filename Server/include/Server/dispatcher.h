#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "TCPConnection/message.h"
#include "Engine/roomfurnisher.h"

class Dispatcher
{
    RoomFurnisher *roomFurnisher;
public:


    /**
     * @brief Dispatcher
     *  The dispatcher is responsible of dispatching a message to the correct
     *  manager
     * @param _roomFurnisher
     *  The class will store a pointer towards _roomFurnisher
     *  Note that the class is not responsible of managing the corresponding memory
     */
    Dispatcher(RoomFurnisher *_roomFurnisher);


    /**
     * @brief dispatch
     *  Method that will deliver the message to the handler calling the specific method
     * with the correct parameters extracted from the message object
     * @param message
     *  The message to be dispatched
     * @return
     *  The Message pointer reply to the call
     *  Note that the user is responsible of managing the memory of the returned value
     */
    Message *dispatch(Message *message);
};

#endif // DISPATCHER_H
