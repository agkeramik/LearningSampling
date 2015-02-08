#include <map>
#include <vector>
#include <string>
#include "Furniture.h"
#include "MGMM.h"
#include "Scene.h"

using namespace std;

class MContext{
public:
    map<string, Furniture> library;
    MGMM mixtures;
    Scene scene;
    vector<Furniture*> toAdd;

    MContext(string path);
    Furniture getInstanceOf(string catalogId);

};
