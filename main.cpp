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

#include "ConversationCostCalculator.h"
#include "DistanceCostCalculator.h"
#include "CostCalculator.h"
#include "CostFunction.h"

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

<<<<<<< HEAD

void old(){
    //    Properties prop("properties.txt");
    //    FurnitureCatalog cat(prop.getFurnitureInfo().c_str());
    //   // cat.print();
    //    Furniture f =cat.getNewFurniture("Renouzate#sofa2");
    //    f.print(std::cout);
    //    Database db(prop.getXMLDatabase().c_str());
    //    db.print();

        //Before
    //    MGMM model=MGMM::learnMGMM(prop.getFurnitureCount().c_str(),prop.getDataFolder().c_str());
    //    model.save(prop.getGMMsFolder().c_str());

    //    MGMM model=MGMM::loadMGMM(prop.getFurnitureCount().c_str(),prop.getGMMsFolder().c_str());

    //    Scene scene;
    //    MContext ctx(prop.getFurnitureInfo().c_str());
    //    std::cout<<"Context has benn built\n";
    //    ctx.printLibrary();

    //    ctx.mixtures = &model;
    //    ctx.scene = &scene;


    //    ctx.toAdd.push_back(ctx.getInstanceOf("Renouzate#sofa2"));
    //    ctx.toAdd.push_back(ctx.getInstanceOf("Renouzate#Table2x2"));


    //    ctx.toAdd.push_back(ctx.getInstanceOf("Renouzate#armchair"));
    //    ctx.toAdd.push_back(ctx.getInstanceOf("Renouzate#armchair"));

    //    ctx.toAdd.push_back(ctx.getInstanceOf("Renouzate#Table1x1"));
    //    ctx.toAdd.push_back(ctx.getInstanceOf("Renouzate#Table1x1"));

    //    Furniture *prex = ctx.getInstanceOf("Renouzate#sofa2");
    //    prex->setX(0);
    //    prex->setY(0);
    //    prex->setTheta(0);
    //    ctx.scene->furnitures.push_back(prex);

    //    Sampler sampler(&ctx);
    //    sampler.furnish();

    //    ofstream outfile("lala.xml");
    //    ctx.scene->print(outfile);
    //    outfile.close();
}

void furnish(int argc, char* argv[]){
    srand(time(NULL));


=======
int main(int argc, char* argv[])
{
    srand(time(NULL));
>>>>>>> a72f23e06656d0772e86b68f5022f4cbc03f84d8
    int samples = 1;
    if (argc > 1)
        samples = atoi(argv[1]);

    Properties prop("properties.txt");

    ofstream outputFile("output_all.xml");

    outputFile<<"<Room>\n";
    outputFile<<"<Furnitures>\n";

<<<<<<< HEAD
    for (int i = 0; i < samples; ++i){

        Context ctx(prop);

        if (argc < 3){
            ctx.addFurnitureToList("Renouzate#sofa2");
            ctx.addFurnitureToList("Renouzate#Table2x2");
            ctx.addFurnitureToList("Renouzate#armchair");
            ctx.addFurnitureToList("Renouzate#armchair");
            ctx.addFurnitureToList("Renouzate#Table1x1");
        }else{
            ctx.addFurnituresFromFile(argv[2]);
        }

        Furniture prex = ctx.catalog.getNewFurniture("Renouzate#sofa2");
        prex.setX(0);
        prex.setY(0);
        prex.setTheta(0);
        ctx.room.addFurniture(prex);

        Sampler *sampler = new MGSampler(&ctx);
        sampler->furnish();
        delete sampler;

        stringstream fileName;
        fileName << "output/layout_" << i << ".xml";

          int w = sqrt(samples);
          int x = i % w;
          int y = i / w;

        //ofstream outputFile(fileName.str().c_str());
        ctx.room.print(outputFile, x * 700, y * 700);
        //outputFile.close();

    }
    outputFile<<"</Furnitures>\n";
    outputFile<<"</Room>\n";

    outputFile.close();

}




void experiment(){
        Point points[] = { Point(0,0), Point(0,1), Point(-1,1), Point(-1,0)};
        Polygon pgn(points, points+4);

        Point points2[] = { Point(-0.5,0),  Point(10,0), Point(10,1), Point(-0.5,10)};
        Polygon pgn2(points2, points2+4);

        std::cout << "Intersection area is: " << Global::intersectionArea(pgn, pgn2) << " when it should be " << 0.5 << std::endl;


        Point points3[] = { Point(0,0), Point(0,1), Point(-1,1), Point(-1,0)};
        Polygon pg3(points3, points3+4);

        Point points4[] = { Point(5,0),  Point(10,0), Point(10,1), Point(5,1)};
        Polygon pgn4(points4, points4+4);

        std::cout << "Distance is: " << Global::distance(pg3, pgn4) << " when it should be " << 5 << std::endl;

        Vector v(0,1);
        Vector w(0.5,0.5);

        std::cout << "Angle is : " << Global::angle(v,w) << " when it should be " << 3.14/4.0 << std::endl;
}

int main(int argc, char* argv[])
{
    experiment();
    return 0;
}

=======
    FurnitureCatalog furnCat(prop.getFurnitureInfo().c_str());
    MGMM mixutures=MGMM::loadMGMM(prop.getFurnitureCount().c_str(),prop.getGMMsFolder().c_str());
    Room room;
    std::cout<<"before Door 1\n";
    Furniture door1=furnCat.getNewFurniture("eTeks#door");
    std::cout<<"after Door 1\n";
    door1.setX(0);
    door1.setY(325);
    door1.setTheta(4.71);
    room.addDoor(door1);
    CostFunction evalFunction;
    CostCalculator *conv=new ConversationCostCalculator(prop.getConversationProp().c_str());
    evalFunction.addComponent(*conv);
    CostCalculator *dist=new DistanceCostCalculator();
    evalFunction.addComponent(*dist);

    for (int i = 0; i < samples; ++i){

        Context ctx(room,furnCat,mixutures);
        if (argc < 3){
            ctx.addFurnitureToList("Renouzate#Table3x2");
            ctx.addFurnitureToList("Renouzate#sofa2");
            ctx.addFurnitureToList("Renouzate#sofa2");
            ctx.addFurnitureToList("Renouzate#armchair");
            ctx.addFurnitureToList("Renouzate#armchair");
            ctx.addFurnitureToList("Renouzate#Table1x1");
            ctx.addFurnitureToList("Renouzate#Table1x1");
        }else{
            ctx.addFurnituresFromFile(argv[2]);
        }

        Furniture prex = ctx.catalog.getNewFurniture("Renouzate#TVTable");
        prex.setX(175);
        prex.setY(365);
        prex.setTheta(1.57);
        ctx.room.addFurniture(prex);

        Sampler *sampler = new MGSampler(&ctx);
        sampler->furnish();
        delete sampler;

        int w = sqrt(samples);
        int x = i % w;
        int y = i / w;

        ctx.room.print(outputFile, x * 700, y * 700);

        std::cout<<"Room "<<i<<std::endl;
        evalFunction.calculateCost(ctx.room);
        std::cout<<std::endl;
    }
    outputFile<<"</Furnitures>\n";
    outputFile<<"</Room>\n";

    outputFile.close();
    delete conv;
    delete dist;
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
>>>>>>> a72f23e06656d0772e86b68f5022f4cbc03f84d8
