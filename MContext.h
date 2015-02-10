#include <map>
#include <vector>
#include <string>
#include "Furniture.h"
#include "mgmm.h"
#include "Scene.h"

using namespace std;

class MContext{
public:
    map<string, Furniture> library;
    MGMM* mixtures;
    Scene* scene;
    vector<Furniture*> toAdd;

    MContext(const string &path);
    Furniture* getInstanceOf(string catalogId);

    void printLibrary() const;

};
