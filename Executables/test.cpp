#include "Model/furniturecatalog.h"
#include "Model/Furniture.h"
#include "Utils/properties.h"
#include <iostream>
#include <vector>

#include "Model/room.h"
#include <pugixml/pugixml.hpp>
#include "TCPConnection/message.h"
#include "TCPConnection/furnishmessage.h"
#include "TCPConnection/replyfurnishmessage.h"

using namespace pugi;
using namespace std;

int main(){
    Properties props("properties.txt");
    FurnitureCatalog furnCat(props.getFurnitureInfo().c_str());
    Furniture f=furnCat.getNewFurniture("Renouzate#sofa2");
    f.setX(100);
    f.setY(40);
    f.setTheta(10);
    Room room;
    room.setBottomRightCorner(111,123);
    room.setTopLeftCorner(1,2);
    room.addFurniture(f);

    vector<Room> rooms;
    rooms.push_back(room);
    rooms.push_back(room);
    ReplyFurnishMessage *message=new ReplyFurnishMessage();
    message->setRooms(rooms);
    cout<<message->toXML()<<endl<<endl;

    Message* message1=Message::parse(message->toXML().c_str(),&furnCat);

    cout<<message1->toXML()<<endl;
    delete message;
    delete message1;
}
