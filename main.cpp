#include <iostream>
#include "Global.h"
#include <cmath>

#include <sstream>
#include <fstream>

#include "mgmm.h"
#include "properties.h"
#include "Sampler.h"
#include "MGSampler.h"
#include "furniturecatalog.h"
#include "database.h"


#include "Context.h"

#include "CollisionCostCalculator.h"
#include "ConversationCostCalculator.h"
#include "DistanceCostCalculator.h"
#include "CostCalculator.h"
#include "CostFunction.h"
#include "clearancecostcalculator.h"
#include "balancecostcalculator.h"
#include "expansioncostcalculator.h"
#include "manhattancostcalculator.h"

#include <stdlib.h>

#include "clipper.hpp"

using namespace std;
using namespace ClipperLib;

//void start_element_callback(void *user_data, const xmlChar *name, const xmlChar **attrs) {
//  printf("Beginning of element : %s \n", name);
//  while (NULL != attrs && NULL != attrs[0]) {
//    printf("attribute: %s=%s\n",attrs[0],attrs[1]);
//    attrs = &attrs[2];
//  }
//}


//void xmlTest(){
//    const char* xml_path = "lala.xml";

//    xmlSAXHandler sh = {0};
//    sh.startElement = start_element_callback;
//    xmlParserCtxtPtr ctxt;

//    if ((ctxt = xmlCreateFileParserCtxt(xml_path)) == NULL) {
//        fprintf(stderr, "Erreur lors de la création du contexte\n");
//        return;
//      }
//      // register sax handler with the context
//      ctxt->sax = &sh;

//      // parse the doc
//      xmlParseDocument(ctxt);
//}


void parseTest(){
    ifstream infile("/home/ubuntumachine/ContributedFurnitureCatalog.properties");

    string line;
    while (getline(infile, line))
    {
        istringstream iss(line);
        unsigned int p = line.find("=");
        if (p>0 && p < line.size() - 1){
            string key = line.substr(0, p-1);
            string value = line.substr(p+1, line.size()-1);
            cout << key << "," << value << endl;
        }

    }
    infile.close();
}



int pickFromCDF(vector<double> &cdf){
    double total = cdf[cdf.size()-1];
    double choice = total * (double)std::rand() / RAND_MAX;

    for (unsigned int i = 0; i < cdf.size(); ++i)
        if (choice <= cdf[i])
            return i;
    return -1;
}

void cdfTest(){
    vector<double> dist;
    dist.push_back(50);
    dist.push_back(dist[dist.size()-1] + 20);
    dist.push_back(dist[dist.size()-1] + 20);

    int v[]={0,0,0};

    for (unsigned int i = 0; i < 1000; ++i){
        ++v[pickFromCDF(dist)];
    }

    cout << v[0] << ", " << v[1] << ", " << v[2] << endl;

    exit(0);
}



void walkFurniture1(Furniture &f){
    if(rand()%2==0)
        f.setX(f.getX() + 4.0*rand()/RAND_MAX - 2.0);
    else
        f.setY(f.getY() + 4.0*rand()/RAND_MAX - 2.0);
    if(rand()%10<3)
        f.setTheta((f.getTheta() + 3.14/90*rand()/RAND_MAX - 3.14/180));
}


void walkFurnitureX(Furniture &f){
    f.setX(f.getX() + 4.0*rand()/RAND_MAX - 2.0);
}

void walkFurnitureY(Furniture &f){
    f.setY(f.getY() + 4.0*rand()/RAND_MAX - 2.0);
}

void optimize(Room &room, CostFunction &costFunction,void (*walkFurniture)(Furniture &),int cycles){
    vector<Furniture> &f = room.getFurnitures();

    double lastCost = std::numeric_limits<double>::max();
    for (int i = 0; i < cycles; ++i){
        for (int count = 0; count < f.size(); ++count){
            int j=rand()%f.size();
            Furniture &furniture = f[j];

            if (!furniture.isMovable())
                continue;

            double ox = furniture.getX();
            double oy = furniture.getY();
            double ot = furniture.getTheta();
            walkFurniture(furniture);

            //            int j1;
            //            do{
            //                j1=rand()%f.size();
            //            }while(j!=j1 && !f[j1].isMovable());
            //            Furniture &furniture1 = f[j1];
            //            double ox1 = furniture1.getX();
            //            double oy1 = furniture1.getY();
            //            double ot1 = furniture1.getTheta();
            //            walkFurniture(furniture1);

            double cost = costFunction.calculateCost(room);

            if (cost < lastCost){
                lastCost = cost;
            }else{
                furniture.setX(ox);
                furniture.setY(oy);
                furniture.setTheta(ot);

                //                furniture1.setX(ox1);
                //                furniture1.setY(oy1);
                //                furniture1.setTheta(ot1);
            }

            //std::cout << "cost = " << lastCost << std::endl;
        }

    }
}
//theta in degrees between 0-360
bool shouldSnap(int theta){
    //range_2=range/2
    const int range_2=8;
    theta=theta%45;
    if(theta<range_2 || theta>45-range_2)
        return true;
    return false;
}

//snap theta to values multiple of 45
void snapTheta(Room &room){
    vector<Furniture> &furnitures=room.getFurnitures();
    for(unsigned int i=0;i<furnitures.size();++i){
        int theta=(int)(furnitures[i].getTheta()*180./M_PI);
        theta=(theta+360)%360;
        if(shouldSnap(theta)){
            //    cout<<"round"<<round(theta/15.);
            theta=round(theta/45.);
            theta=theta*45;
            //   cout<<"theta after"<<theta<<endl;
            theta=(theta+360)%360;
            furnitures[i].setTheta(theta*M_PI/180.);
        }
    }
}

int mainOld(){
    //DONE test the difference algorithm
    Room room;
    room.setTopLeftCorner(0,0);
    room.setBottomRightCorner(355,410);
    cout<<room.getGeometry()<<endl;
}

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


std::vector<std::vector<int> > assignFurnToBlock(const Room &room){
    std::vector<std::vector<int> > blocks;
    std::vector<ClipperLib::Path> blockPath;

    double tlx=room.getTopLeftCornerX();
    double tly=room.getTopLeftCornerY();
    double brx=room.getBottomRightCornerX();
    double bry=room.getBottomRightCornerY();
    double s=95;
    double sc=80;
    ClipperLib::Path p;
    p<<ClipperLib::IntPoint(tlx,tly+sc)<<ClipperLib::IntPoint(tlx+s,tly+sc)
    <<ClipperLib::IntPoint(tlx+s,bry-sc)<<ClipperLib::IntPoint(tlx,bry-sc)
    <<ClipperLib::IntPoint(tlx,tly+sc);
    blockPath.push_back(p);
    p.clear();

    p<<ClipperLib::IntPoint(tlx+sc,tly+s)<<ClipperLib::IntPoint(tlx+sc,tly)
    <<ClipperLib::IntPoint(brx-sc,tly)<<ClipperLib::IntPoint(brx-sc,tly+s)
    <<ClipperLib::IntPoint(tlx+sc,tly+s);
    blockPath.push_back(p);
    p.clear();

    p<<ClipperLib::IntPoint(brx,tly+sc)<<ClipperLib::IntPoint(brx,bry-sc)
    <<ClipperLib::IntPoint(brx-s,bry-sc)<<ClipperLib::IntPoint(brx-s,tly+sc)
    <<ClipperLib::IntPoint(brx,tly+sc);
    blockPath.push_back(p);
    p.clear();

    p<<ClipperLib::IntPoint(tlx+sc,bry)<<ClipperLib::IntPoint(tlx+sc,bry-s)
    <<ClipperLib::IntPoint(brx-sc,bry-s)<<ClipperLib::IntPoint(brx-sc,bry)
    <<ClipperLib::IntPoint(tlx+sc,bry);
    blockPath.push_back(p);
    p.clear();

    blocks.push_back(std::vector<int> ());
    blocks.push_back(std::vector<int> ());
    blocks.push_back(std::vector<int> ());
    blocks.push_back(std::vector<int> ());
    const vector<Furniture> &furnitures=room.getFurnitures();
    for(unsigned int i=0;i<furnitures.size();++i){
        double interArea=0;
        int ind=0;
        ClipperLib::Path pf=furnitures[i].getGlobalGeometry();
        for(unsigned int j=0;j<blockPath.size();++j){
            double tempArea=Global::intersectionArea(blockPath[j],pf);
            //cout<<"block "<<j<<" Furniture "<<i<<":\n"<<tempArea<<endl;
            if(tempArea>interArea){
                interArea=tempArea;
                ind=j;
            }
        }
        if(interArea>0.35*furnitures[i].width*furnitures[i].depth){
            blocks[ind].push_back(i);
        }
    }
    //    for(unsigned int i=0;i<blocks.size();++i){
    //        cout<<"Block "<<i<<" \n";
    //        for(unsigned int j=0;j<blocks[i].size();++j){
    //            furnitures[blocks[i][j]].print(cout);
    //        }
    //    }
    return blocks;
}

int main(int argc, char* argv[])
{
    srand(time(NULL));
    int samples = 1;
    if (argc > 1)
        samples = atoi(argv[1]);

    Properties prop("properties.txt");

    ofstream outputFile("output_all.xml");
    outputFile<<"<Room>\n";
    outputFile<<"<Furnitures>\n";

    ofstream outputFile1("output_all_before.xml");
    outputFile1<<"<Room>\n";
    outputFile1<<"<Furnitures>\n";

    FurnitureCatalog furnCat(prop.getFurnitureInfo().c_str());

    MGMM mixutures=MGMM::loadMGMM(prop.getFurnitureCount().c_str(),prop.getGMMsFolder().c_str());
    Room room;
    room.setTopLeftCorner(0,0);
    room.setBottomRightCorner(355,410);
    std::cout<<"before Door 1\n";
    Furniture door1=furnCat.getNewFurniture("eTeks#door");
    std::cout<<"after Door 1\n";
    door1.setX(0);
    door1.setY(360);
    door1.setTheta(4.712);
    room.addDoor(door1);

    //    Furniture door2=furnCat.getNewFurniture("eTeks#doubleFrenchWindow126x200");
    //    door2.setX(160);
    //    door2.setY(0);
    //    door2.setTheta(0);
    //    room.addDoor(door2);


    CostCalculator *conv=new ConversationCostCalculator(prop.getConversationProp().c_str());
    conv->setWeight(0.5);

    CostCalculator *dist=new DistanceCostCalculator();
    dist->setWeight(10.0);

    CostCalculator *clearance=new ClearanceCostCalculator();
    clearance->setWeight(400);

    CostCalculator *collision = new CollisionCostCalculator();
    collision->setWeight(10000000);

    CostCalculator *balance=new BalanceCostCalculator();
    balance->setWeight(0.4);

    CostCalculator *expansion=new ExpansionCostCalculator();
    expansion->setWeight(40);

    CostFunction evalFunction;
    evalFunction.addComponent(balance);
    evalFunction.addComponent(clearance);
    evalFunction.addComponent(dist);
    evalFunction.addComponent(conv);
    evalFunction.addComponent(collision);
    evalFunction.addComponent(expansion);

    std::vector<Room> roomSamples;
    std::vector<Room> roomSamplesBefore;
    int *permIndex=new int[samples];
    double *convCost=new double[samples];

    for (int i = 0; i < samples; ++i){
        Context ctx(room,furnCat,mixutures);
        if (argc < 3){
            ctx.addFurnitureToList("Renouzate#Table3x2");
            ctx.addFurnitureToList("Renouzate#sofa2");
            //            ctx.addFurnitureToList("Renouzate#sofa2");
            ctx.addFurnitureToList("Renouzate#sofa1");
            ctx.addFurnitureToList("Renouzate#sofa1");
            ctx.addFurnitureToList("Renouzate#armchair");
            //            ctx.addFurnitureToList("Renouzate#armchair");
            //            ctx.addFurnitureToList("Renouzate#Table1x1");
            //            ctx.addFurnitureToList("Renouzate#Table1x1");
        }else{
            ctx.addFurnituresFromFile(argv[2]);
        }

        Furniture prex = ctx.catalog.getNewFurniture("Renouzate#TVTable");
        //        prex.setX(22);
        //        prex.setY(175);
        //        prex.setTheta(3.141592);
        prex.setX(175);
        prex.setY(380);
        prex.setTheta(1.57);
        prex.isMovable(false);
        ctx.room.addFurniture(prex);

        //        Furniture prex1 = ctx.catalog.getNewFurniture("Renouzate#fireplaceInWall");
        //        prex1.setX(0);
        //        prex1.setY(150);
        //        prex1.setTheta(4.7123);
        //        prex1.isMovable(false);
        //        ctx.room.addFurniture(prex1);

        Sampler *sampler = new MGSampler(&ctx);
        sampler->furnish();
        delete sampler;
       // evalFunction.print();
        roomSamplesBefore.push_back(ctx.room);
        optimize(ctx.room, evalFunction,walkFurniture1,100);
        CostCalculator *aligBlocks=new ManhattanCostCalculator(assignFurnToBlock(ctx.room));
        aligBlocks->setWeight(10);
        evalFunction.addComponent(aligBlocks);

        optimize(ctx.room, evalFunction,walkFurniture1,100);;
        delete aligBlocks;

        snapTheta(ctx.room);

        int w = sqrt(samples);
        int x = i % w;
        int y = i / w;

        //ctx.room.print(outputFile, x * 700, y * 700);

        permIndex[i]=i;
        std::cout<<"Room "<<i<<std::endl;
        convCost[i]=evalFunction.calculateCost(ctx.room);
        addTable1x1(ctx.room,furnCat);
        addTable1x1(ctx.room,furnCat);
        roomSamples.push_back(ctx.room);

    }

    for(int i=0;i<samples-1;++i){
        for(int j=i+1;j<samples;++j){
            if(convCost[permIndex[i]]>convCost[permIndex[j]]){
                int temp=permIndex[i];
                permIndex[i]=permIndex[j];
                permIndex[j]=temp;
            }
        }
    }
    for(int i=0;i<samples;++i){
        std::cout<<"Room "<<i<<std::endl;
        std::cout<<convCost[permIndex[i]];
        std::cout<<std::endl;
        int w = sqrt(samples);
        int x = i % w;
        int y = i / w;
        //        evalFunction.calculateCost(roomSamples[permIndex[i]]);
        roomSamples[permIndex[i]].print(outputFile, x * 700, y * 700);
        roomSamplesBefore[permIndex[i]].print(outputFile1, x * 700, y * 700);
    }

    outputFile<<"</Furnitures>\n";
    outputFile<<"</Room>\n";
    outputFile.close();

    outputFile1<<"</Furnitures>\n";
    outputFile1<<"</Room>\n";
    outputFile1.close();

    delete convCost;
    delete conv;
    delete dist;
    delete balance;
    delete collision;
    delete permIndex;
    delete expansion;
    return 0;
}

int mainTest()
{
    Properties prop("properties.txt");
    FurnitureCatalog furCat(prop.getFurnitureInfo().c_str());
    Furniture f1=furCat.getNewFurniture("Renouzate#sofa2");
    Furniture f2=furCat.getNewFurniture("Renouzate#sofa2");
    f1.setX(0);
    f1.setY(0);
    f1.setTheta(0);
    f2.setX(0);
    f2.setY(300);
    f2.setTheta(M_PI_4);
    Room room;
    room.addFurniture(f1);
    room.addFurniture(f2);
    CostCalculator *convCos=new DistanceCostCalculator();
    std::cout<<convCos->calculateCost(room)<<std::endl;
    delete convCos;
    return 0;
}
