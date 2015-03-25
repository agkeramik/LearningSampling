#include <iostream>
#include "Geometry/Global.h"
#include <cmath>

#include <sstream>
#include <fstream>

#include "Engine/mgmm.h"
#include "Utils/properties.h"
#include "Model/furniturecatalog.h"


#include <stdlib.h>

#include "Geometry/clipper.hpp"

#include "Engine/roomfurnisher.h"
#include "Engine/roomsampler.h"
#include "Engine/roomoptimiser.h"


using namespace std;
using namespace ClipperLib;


bool collisionCheck(const Furniture &f,const Room &room){
    const std::vector<Furniture> &furnitures=room.getFurnitures();
    for(unsigned int j=0;j<furnitures.size();++j){
        if(f.collision(furnitures[j]))
            return true;
    }
    const std::vector<Furniture> &doors=room.getDoors();
    for(unsigned int j=0;j<doors.size();++j){
        if(f.collision(doors[j]))
            return true;
    }

    const ClipperLib::Path &roomGeo=room.getGeometry();
    ClipperLib::Path pi=f.getGlobalGeometry();
    if(Global::differenceArea(roomGeo,pi)>0)
        return true;

    return false;
}

void addTable1x1(Room &room,FurnitureCatalog &furnCat){
    const std::vector<Furniture> &furnitures=room.getFurnitures();
    unsigned int *seats=new unsigned int[furnitures.size()];
    unsigned int C=0;
    unsigned int *tables=new unsigned int[furnitures.size()];
    unsigned TC=0;
    for(unsigned int i=0;i<furnitures.size();++i){
        std::string cat=furnitures[i].catalogId;
        if(cat.find("sofa2")!=std::string::npos || cat.find("armchsair")!=std::string::npos)
            seats[C++]=i;
        if(cat.find("Table1x1")!=std::string::npos)
            tables[TC++]=i;
    }


    const unsigned int NBTRIES=45;
    Furniture table=furnCat.getNewFurniture("Renouzate#Table1x1");
    for(unsigned i=0;i<NBTRIES;++i){
        int f=rand()%C;
        int w=rand()%2;
        const Furniture &rela=furnitures[seats[f]];
        table.setTheta(rela.getTheta());
        double relX=rela.getX()+(2*w-1)*(1.03*rela.width*0.5+1*table.width)*cos(rela.getTheta());
        double relY=rela.getY()+(2*w-1)*(1.03*rela.width*0.5+1*table.width)*sin(rela.getTheta());
        table.setX(relX);
        table.setY(relY);

        if(!collisionCheck(table,room)){
            double minLen=std::numeric_limits<double>::max();
            for(unsigned int j=0;j<TC;++j){
                Vec2 v(relX-furnitures[tables[j]].getX(),relY-furnitures[tables[j]].getY());
                minLen=std::min(v.lengthSqrd(),minLen);
            }
            if(minLen>20000 || (minLen<20000 && rand()%10<3)){
                room.addFurniture(table);
                cout<<"added "<<i<<endl;
                break;
            }
        }
    }
    delete seats;
    delete tables;
}



int main(){
    srand(time(NULL));
    //initialising
    Properties prop("properties.txt");
    FurnitureCatalog furnCat(prop.getFurnitureInfo().c_str());
    MGMM mixutures=MGMM::loadMGMM(prop.getFurnitureCount().c_str(),prop.getGMMsFolder().c_str());
    RoomSampler rs(mixutures,furnCat);
    RoomFurnisher f(&rs,prop);

    //Building the room Properties
    Room room;
    room.setTopLeftCorner(0,0);
    room.setBottomRightCorner(355,410);

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

    //Furnishing
    std::vector<Room> roomSamples=f.furnish(room);

    //Exporting to xml the furnished rooms
    ofstream outputFile("output_all.xml");
    outputFile<<"<Room>\n";
    outputFile<<"<Furnitures>\n";
    int w = sqrt(roomSamples.size());
    for(unsigned int i=0;i<roomSamples.size();++i){
        int x = i % w;
        int y = i / w;
        roomSamples[i].print(outputFile, x * 700, y * 700);
    }
    outputFile<<"</Furnitures>\n";
    outputFile<<"</Room>\n";
    outputFile.close();
}
