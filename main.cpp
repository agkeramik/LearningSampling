#include <iostream>
#include "Global.h"

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/parserInternals.h>

#include <sstream>
#include <fstream>

#include "MContext.h"
#include "mgmm.h"
#include "properties.h"

using namespace std;


void start_element_callback(void *user_data, const xmlChar *name, const xmlChar **attrs) {
  printf("Beginning of element : %s \n", name);
  while (NULL != attrs && NULL != attrs[0]) {
    printf("attribute: %s=%s\n",attrs[0],attrs[1]);
    attrs = &attrs[2];
  }
}


void xmlTest(){
    const char* xml_path = "/home/ubuntumachine/hello_world.xml";

    xmlSAXHandler sh = {0};
    sh.startElement = start_element_callback;
    xmlParserCtxtPtr ctxt;

    if ((ctxt = xmlCreateFileParserCtxt(xml_path)) == NULL) {
        fprintf(stderr, "Erreur lors de la création du contexte\n");
        return;
      }
      // register sax handler with the context
      ctxt->sax = &sh;

      // parse the doc
      xmlParseDocument(ctxt);
}

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
        int p = line.find("=");
        if (p>0 && p < line.size() - 1){
            string key = line.substr(0, p-1);
            string value = line.substr(p+1, line.size()-1);
            int s = key.find("#");
            cout << key << "," << value << endl;
        }

    }

    infile.close();
}

int main(int argc, char* argv[])
{
//    MContext ctx("/home/ubuntumachine/ContributedFurnitureCatalog.properties");
//    Furniture f = ctx.getInstanceOf("Renouzate#Table2x1");
    Properties prop("properties.txt");
    MGMM model=MGMM::loadMGMM(prop.getFurnitureCount().c_str(),prop.getGMMsFolder().c_str());
    model.print();
//    cout << f.id << endl;
    return 0;
}

