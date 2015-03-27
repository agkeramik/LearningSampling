#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "TCPConnection/tcpacceptor.h"
#include "TCPConnection/messagestreamwrapper.h"
#include "Thread/wqueue.h"
#include "Server/workitem.h"
#include "Server/messageconsumer.h"
#include "Server/dispatcher.h"
#include "Utils/properties.h"
#include "Model/furniturecatalog.h"
#include "Engine/roomfurnisher.h"
#include "Engine/roomsampler.h"
#include "Engine/mgmm.h"

using namespace std;

int main(int argc, char** argv)
{
    if (argc < 2 || argc > 4) {
        printf("usage: ServerEx <port> [<ip>]\n");
        exit(1);
    }
    //memory not handled because these will persist until the server is dead
    WQueue<WorkItem *> wqueue;
    for(int i=0;i<10;++i){
        MessageConsumer *thread=new MessageConsumer(wqueue);
        thread->start();
    }

    Properties props("properties.txt");
    FurnitureCatalog* catalog=new FurnitureCatalog(props.getFurnitureInfo().c_str());

    MGMM mixtures=MGMM::loadMGMM(props.getFurnitureCount().c_str(),
                                props.getGMMsFolder().c_str());

    RoomSampler *roomSampler=new RoomSampler(mixtures,*catalog);
    RoomFurnisher *roomFurnisher=new RoomFurnisher(roomSampler,props,catalog);

    Dispatcher *dispatcher=new Dispatcher(roomFurnisher);

    TCPAcceptor* acceptor = NULL;
    if (argc == 3) {
        acceptor = new TCPAcceptor(atoi(argv[1]), argv[2]);
    }
    else {
        acceptor = new TCPAcceptor(atoi(argv[1]));
    }
    if (acceptor->start() == 0) {
        while (1) {
            TCPStream* stream = NULL;
            stream = acceptor->accept();
            MessageStreamWrapper *msw=new MessageStreamWrapper(stream,catalog);
            if (stream != NULL) {
                wqueue.enqueue(new WorkItem(msw,dispatcher));
            }
        }
    }
    perror("Could not start the server");
    exit(-1);
}
