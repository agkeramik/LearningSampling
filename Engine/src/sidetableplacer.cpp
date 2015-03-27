#include "Engine/sidetableplacer.h"
#include <vector>
#include "Geometry/Global.h"

using namespace std;

SideTablePlacer::SideTablePlacer(FurnitureCatalog *_catalog):
    catalog(_catalog)
{

}

int SideTablePlacer::placeSideTable(Room &room, int count)
{
    std::vector<int> sofa2s;
    std::vector<int> armchairs;
    vector<Furniture> &furnitures=room.getFurnitures();

    for(unsigned i=0;i<furnitures.size();++i){
        if(furnitures[i].catalogId.compare("Renouzate#sofa2")==0){
            sofa2s.push_back(i);
        }else if(furnitures[i].catalogId.compare("Renouzate#sofa1")==0 ||
                 furnitures[i].catalogId.compare("Renouzate#armchair")==0){
            armchairs.push_back(i);
        }else {
            cout<<furnitures[i].catalogId<<endl;
        }
    }


    if(sofa2s.size()>0){
        int ran=rand()%sofa2s.size();
        for(int w=0;w<=1;++w){
            Furniture table=catalog->getNewFurniture("Renouzate#Table1x1");
            table.setDepth(60);
            table.setWidth(60);
            const Furniture &rela=furnitures[sofa2s[ran]];
            table.setTheta(rela.getTheta());
            double relX=rela.getX()+(2*w-1)*(1*rela.width*0.5+0.6*table.width)*cos(rela.getTheta());
            double relY=rela.getY()+(2*w-1)*(1*rela.width*0.5+0.6*table.width)*sin(rela.getTheta());
            table.setX(relX);
            table.setY(relY);
            if(!collisionCheck(table,room))
                room.addFurniture(table);
        }
    }

    //place between two armchairs table 1x1
    for(unsigned int i=0;i<armchairs.size()-1;++i){
        ClipperLib::Path pi=furnitures[armchairs[i]].getGlobalGeometry();
        for(unsigned int j=i+1;j<armchairs.size();++j){
            ClipperLib::Path pj=furnitures[armchairs[j]].getGlobalGeometry();
            ClipperLib::Paths sol;
            double distance=Global::freeArea(pi,pj,sol);
            Furniture table =catalog->getNewFurniture("Renouzate#Table1x1");
            double width,area;
            if(distance<6400){
                if(sol.size()==1){
                    Vec2 center1=Global::centroid(sol[0]);
                    table.setX(center1.x);
                    table.setY(center1.y);
                    area=ClipperLib::Area(sol[0]);
                }
                else if(sol.size()==2){
                    Vec2 roomCenter=room.getCentroid();
                    Vec2 center1=Global::centroid(sol[0]);
                    Vec2 center2=Global::centroid(sol[1]);
                    if((center1-roomCenter).lengthSqrd()>(center2-roomCenter).lengthSqrd()){
                        table.setX(center1.x);
                        table.setY(center1.y);
                        area=ClipperLib::Area(sol[0]);
                    }else{
                        table.setX(center2.x);
                        table.setY(center2.y);
                        area=ClipperLib::Area(sol[1]);
                    }

                }
                width=sqrt(area*0.4);
                if(width>40){
                    table.setTheta(0);
                    table.setDepth(width);
                    table.setWidth(width);
                    room.addFurniture(table);
                }
            }
        }
    }


    cout<<"\n\n\n\n\n";
    return 0;
}



bool SideTablePlacer::collisionCheck(const Furniture &f,const Room &room){
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

void SideTablePlacer::addTable1x1(Room &room){
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
    Furniture table=catalog->getNewFurniture("Renouzate#Table1x1");
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
