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
    Furniture f1=furnCat.getNewFurniture("Renouzate#sofa1");
    f1.setX(0);
    f1.setY(0);
    f1.setTheta(0);

    Vec2 p=Global::centroid(f1.getGlobalGeometry());
    cout<<p.x<<" "<<p.y<<endl;


}
