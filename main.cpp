#include <iostream>
#include "Global.h"

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/parserInternals.h>

#include <sstream>
#include <fstream>

#include "mgmm.h"
#include "properties.h"
#include "Sampler.h"
#include "MGSampler.h"
#include "furniturecatalog.h"
#include "database.h"


#include "Context.h"
using namespace std;


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

void geoTest(){
    Point points[] = { Point(0,0), Point(5.1,0), Point(1,1), Point(0.5,6)};
    Polygon pgn(points, points+4);

    Point points2[] = { Point(-2,-2),  Point(2,-2), Point(2,2), Point(-2,2)};
    Polygon pgn2(points2, points2+4);

    if (CGAL::do_intersect(pgn, pgn2)) cout << "Intersection"<<endl; else cout << "No Intersection"  << endl;

    Transform transformRot(CGAL::ROTATION, cos(3.14/4.0), sin(3.14/4.0));
    Transform transformTrans(CGAL::TRANSLATION, Vector(0, 10));
    Polygon trPg(CGAL::transform(transformTrans, CGAL::transform(transformRot, pgn2)));

    cout << trPg;
}

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
    std::cout<<"before Door 1\n";
    Furniture door1=furnCat.getNewFurniture("eTeks#door");
    std::cout<<"after Door 1\n";
    door1.setX(0);
    door1.setY(200);
    door1.setTheta(4.71);
        door1.print(std::cout);
        std::cout<<std::endl;
    room.addDoor(door1);
    for (int i = 0; i < samples; ++i){

        Context ctx(room,furnCat,mixutures);
        if (argc < 3){
            ctx.addFurnitureToList("Renouzate#Table3x2");
            ctx.addFurnitureToList("Renouzate#sofa2");
            ctx.addFurnitureToList("Renouzate#sofa2");
            ctx.addFurnitureToList("Renouzate#armchair");
            //ctx.addFurnitureToList("Renouzate#armchair");
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

    return 0;
}
