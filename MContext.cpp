#include "MContext.h"
#include <fstream>

Furniture* MContext::getInstanceOf(string catalogId){
    return new Furniture(this->library[catalogId]);
}

MContext::MContext(string path){
    //todo load shit
    ifstream infile(path.c_str());

    string line;
    Furniture furniture;
    while (getline(infile, line))
    {
        int p = line.find("=");
        if (p > 0 && p < line.size() - 1){
            string key = line.substr(0, p);
            string value = line.substr(p+1, line.size()-1);

            int s = key.find("#");
            if (s > 0 && s < key.size()-1){
                string keyType = key.substr(0, s);
                int keyId = atoi(key.substr(s+1, key.size()).c_str());

                if (keyType.compare("id")==0){
                    if (furniture.id!=-1)
                        this->library[furniture.catalogId]=furniture;
                    furniture = Furniture(keyId, value);
                }else if (keyType.compare("name")==0){
                    furniture.name = value;
                }else if (keyType.compare("width")==0){
                    furniture.setWidth(atof(value.c_str()));
                }else if (keyType.compare("height")==0){
                    furniture.setHeight(atof(value.c_str()));
                }else if (keyType.compare("depth")==0){
                    furniture.setDepth(atof(value.c_str()));
                }
            }
        }
    }

    //add last one
    if (furniture.id!=-1)
        this->library[furniture.catalogId]=furniture;

    infile.close();
}

