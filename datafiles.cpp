#include "datafiles.h"
#include <iostream>
#include <map>
#include <string>
#include <stdlib.h>
#include <fstream>

DataFiles::DataFiles(const DataFiles &d)
{

}


DataFiles::DataFiles()
{

}

DataFiles::~DataFiles()
{

}

std::map<std::string, double> DataFiles::readF1F2WeightFile(const char *fileName)
{

    std::ifstream fin;
    fin.open(fileName);
    std::string line;
    if (!fin.is_open()){
        std::cout<<"unable to open file "<<fileName;
    }
     std::map<std::string,double> furnDB;
    int i=0;
    std::string file;
    while(std::getline(fin,line)){
       if (i==0){
           if(line.find('-')!=std::string::npos){
               file=line;
               i=1;
           }
       }else{
           //not checking if line is empty
           double weight=atof(line.c_str());
           furnDB.insert(std::pair<std::string,double>(file,weight));
           i=0;
       }
    }
    fin.close();
    std::cout<<furnDB.size()<<std::endl;
    return furnDB;
}


