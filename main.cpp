#include <iostream>
#include "Global.h"


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



void walkFurniture(Furniture &f){
    if(rand()%2==0)
        f.setX(f.getX() + 4.0*rand()/RAND_MAX - 2.0);
    else
        f.setY(f.getY() + 4.0*rand()/RAND_MAX - 2.0);
    if(rand()%10<3)
        f.setTheta((f.getTheta() + 3.14/90*rand()/RAND_MAX - 3.14/180));
}

void optimize(Room &room, CostFunction &costFunction){
    int cycles = 200;
    vector<Furniture> &f = room.getFurnitures();

    double lastCost = std::numeric_limits<double>::max();
    for (int i = 0; i < cycles; ++i){

        for (int j = 0; j < f.size(); ++j){
            Furniture &furniture = f[j];
            double ox = furniture.getX();
            double oy = furniture.getY();
            double ot = furniture.getTheta();
            if (!furniture.isMovable())
                continue;
            walkFurniture(furniture);
            double cost = costFunction.calculateCost(room);
            if (cost < lastCost){
                lastCost = cost;
            }else{
                furniture.setX(ox);
                furniture.setY(oy);
                furniture.setTheta(ot);
            }

            //std::cout << "cost = " << lastCost << std::endl;
        }

    }
}


int mainOld(){
    //TODO test the difference algorithm
    Room room;
    room.setTopLeftCorner(0,0);
    room.setBottomRightCorner(355,410);
    cout<<room.getGeometry()<<endl;
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

    FurnitureCatalog furnCat(prop.getFurnitureInfo().c_str());
    MGMM mixutures=MGMM::loadMGMM(prop.getFurnitureCount().c_str(),prop.getGMMsFolder().c_str());
    Room room;
    room.setTopLeftCorner(0,0);
    room.setBottomRightCorner(355,410);
    std::cout<<"before Door 1\n";
    Furniture door1=furnCat.getNewFurniture("eTeks#door");
    std::cout<<"after Door 1\n";
    door1.setX(0);
    door1.setY(325);
    door1.setTheta(4.71);
    room.addDoor(door1);

//    Furniture door2=furnCat.getNewFurniture("eTeks#doubleFrenchWindow126x200");
//    door2.setX(360);
//    door2.setY(330);
//    door2.setTheta(1.57);
//    room.addDoor(door2);


    CostCalculator *conv=new ConversationCostCalculator(prop.getConversationProp().c_str());
    conv->setWeight(25.0);

    CostCalculator *dist=new DistanceCostCalculator();
    dist->setWeight(0.0);

    CostCalculator *clearance=new ClearanceCostCalculator();
    clearance->setWeight(200);

    CostCalculator *collision = new CollisionCostCalculator();
    collision->setWeight(100000);

    CostCalculator *balance=new BalanceCostCalculator();
    balance->setWeight(1);

    CostFunction evalFunction;
    evalFunction.addComponent(*balance);
    evalFunction.addComponent(*clearance);
    //    evalFunction.addComponent(*dist);
    evalFunction.addComponent(*conv);
    evalFunction.addComponent(*collision);

    std::vector<Room> roomSamples;
    int *permIndex=new int[samples];
    double *convCost=new double[samples];

    for (int i = 0; i < samples; ++i){

        Context ctx(room,furnCat,mixutures);
        if (argc < 3){
            ctx.addFurnitureToList("Renouzate#Table3x2");
            ctx.addFurnitureToList("Renouzate#sofa2");
            ctx.addFurnitureToList("Renouzate#sofa1");
            ctx.addFurnitureToList("Renouzate#sofa1");
            ctx.addFurnitureToList("Renouzate#armchair");
            //            ctx.addFurnitureToList("Renouzate#Table1x1");
            //            ctx.addFurnitureToList("Renouzate#Table1x1");
        }else{
            ctx.addFurnituresFromFile(argv[2]);
        }

        Furniture prex = ctx.catalog.getNewFurniture("Renouzate#TVTable");
        prex.setX(175);
        prex.setY(365);
        prex.setTheta(1.57);
        prex.isMovable(false);
        ctx.room.addFurniture(prex);

        Sampler *sampler = new MGSampler(&ctx);
        sampler->furnish();
        delete sampler;


        optimize(ctx.room, evalFunction);

        int w = sqrt(samples);
        int x = i % w;
        int y = i / w;

        //ctx.room.print(outputFile, x * 700, y * 700);

        permIndex[i]=i;
        std::cout<<"Room "<<i<<std::endl;
        convCost[i]=evalFunction.calculateCost(ctx.room);
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
        roomSamples[permIndex[i]].print(outputFile, x * 700, y * 700);
    }

    outputFile<<"</Furnitures>\n";
    outputFile<<"</Room>\n";
    outputFile.close();

    delete convCost;
    delete conv;
    delete dist;
    delete balance;
    delete collision;
    delete permIndex;
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
