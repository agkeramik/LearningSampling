#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <sstream>

#include "TCPConnection/tcpconnector.h"
#include "TCPConnection/furnishmessage.h"
#include "TCPConnection/messagestreamwrapper.h"
#include "TCPConnection/message.h"
#include "Utils/properties.h"
#include "Model/room.h"
#include "Model/furniturecatalog.h"
#include "Model/Furniture.h"

using namespace std;

int main(int argc, char** argv)
{
    if (argc != 3) {
        printf("usage: %s <port> <ip>\n", argv[0]);
        exit(1);
    }

    TCPConnector* connector = new TCPConnector();
    Properties props("properties.txt");
    FurnitureCatalog furnCat(props.getFurnitureInfo().c_str());
    TCPStream* stream = connector->connect(atoi(argv[1]),argv[2]);
    if (stream) {
        MessageStreamWrapper msw(stream,&furnCat);
        Room room;
        room.setTopLeftCorner(0,0);
        room.setBottomRightCorner(353,409);

        FurnishMessage *furnishmessage=new FurnishMessage();

        Furniture door1=furnCat.getNewFurniture("eTeks#door");
        door1.setX(0);
        door1.setY(360);
        door1.setTheta(4.712);
        room.addDoor(door1);

        Furniture tv = furnCat.getNewFurniture("Renouzate#TVTable");
        tv.setX(175);
        tv.setY(380);
        tv.setTheta(1.57);
        tv.isMovable(false);
        room.addFurniture(tv);

        furnishmessage->setRoom(room);

        cout<<furnishmessage->toXML()<<endl;

        msw.sendMessage(furnishmessage);
        delete furnishmessage;
        Message *reply=msw.pullMessage();

        cout<<reply->toXML()<<endl;

        delete reply;
    }
    exit(0);
}
