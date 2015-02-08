#ifndef DATAFILES_H
#define DATAFILES_H

#include <map>
#include <string>

class DataFiles
{
    DataFiles(const DataFiles & d);
    DataFiles();
    virtual ~DataFiles();
public:
    static std::map<std::string,double> readF1F2WeightFile(const char * fileName);


};

#endif // DATAFILES_H
