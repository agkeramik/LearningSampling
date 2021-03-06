#include "Utils/properties.h"
#include <fstream>
#include <iostream>
//no spaces are allowed around the equal operator
Properties::Properties(const char *fileName)
{
    std::ifstream fin;
    fin.open(fileName);
    if(!fin.is_open()){
        std::cout<<"File Not Open: "<<fileName<<std::endl;
    }
    std::string line;
    while(std::getline(fin,line)>0){
        unsigned int pos=line.find('=');
        if(pos!=std::string::npos){
            std::string type=line.substr(0,pos);
            if(type.compare("DataFolder")==0)
                dataFolder=line.substr(pos+1);
            else if(type.compare("GMMsFolder")==0)
                gmmsFolder=line.substr(pos+1);
            else if(type.compare("FurnitureCount")==0)
                furnCount=line.substr(pos+1);
            else if(type.compare("FurnitureInfo")==0)
                furnInfo=line.substr(pos+1);
            else if(type.compare("XMLDatabase")==0)
                XMLDatabase=line.substr(pos+1);
            else if(type.compare("ConversationProp")==0)
                conversationProp=line.substr(pos+1);
        }
    }
    fin.close();

}

const std::string &Properties::getFurnitureInfo() const
{
    return furnInfo;
}

const std::string &Properties::getXMLDatabase() const
{
    return XMLDatabase;
}

const std::string &Properties::getConversationProp() const
{
    return conversationProp;
}

const std::string &Properties::getFurnitureCount() const
{
    return furnCount;
}

const std::string &Properties::getDataFolder() const
{
    return dataFolder;
}

const std::string &Properties::getGMMsFolder() const
{
    return gmmsFolder;
}
