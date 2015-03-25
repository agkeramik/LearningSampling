#include "Server/dispatcher.h"
#include "TCPConnection/message.h"
#include "TCPConnection/furnishmessage.h"
#include "TCPConnection/replyfurnishmessage.h"

#include <iostream>
#include <vector>

Dispatcher::Dispatcher(RoomFurnisher *_roomFurnisher):
    roomFurnisher(_roomFurnisher)
{
}

Message *Dispatcher::dispatch(Message *message)
{
    if(message->getType()==FurnishMessageType){
        FurnishMessage *fm=(FurnishMessage *)message;
        std::cout<<"Furnishing room\n";
        std::vector<Room> rooms=roomFurnisher->furnish(fm->getRoom());
        ReplyFurnishMessage *mm= new ReplyFurnishMessage();
        mm->setRooms(rooms);
        return mm;
    }
    return NULL;
}
