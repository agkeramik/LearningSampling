#include "furniturecatalog.h"
#include <fstream>

FurnitureCatalog::FurnitureCatalog(const char *catalogFileName)
{
    //todo load shit
    std::ifstream infile(catalogFileName);
    if(!infile.is_open())
        std::cout<<"File not Opened:"+std::string(catalogFileName)<<std::endl;
    std::string line;
    Furniture furniture;
    while (getline(infile, line))
    {
        int p = line.find("=");
        if (p > 0 && p < line.size() - 1){
            std::string key = line.substr(0, p);
            std::string value = line.substr(p+1, line.size()-1);

            int s = key.find("#");
            if (s > 0 && s < key.size()-1){
                std::string keyType = key.substr(0, s);
                int keyId = atoi(key.substr(s+1, key.size()).c_str());

                if (keyType.compare("id")==0){
                    if (furniture.id!=-1)
                        this->catalog[furniture.catalogId]=furniture;
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
        this->catalog[furniture.catalogId]=furniture;
    infile.close();
}

void FurnitureCatalog::print() const
{
    for(std::map<std::string,Furniture>::const_iterator it=catalog.begin();it!=catalog.end();++it){
        std::cout<<it->first<<std::endl;
        it->second.print(std::cout);
    }
}

