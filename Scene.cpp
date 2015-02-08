#include "Scene.h"


Scene::Scene()
{
}

void Scene::print(std::ostream &out)
{
    out<<"<Room>\n";
    out<<"<Furnitures>\n";
    for (int i=0;i<furnitures.size();++i){
        furnitures[i]->print(out);
    }
    out<<"</Furnitures>\n";
    out<<"</Room>\n";
}


Scene::~Scene()
{
}
