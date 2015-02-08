#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <string>
class Properties
{
    std::string furnCount;
    std::string gmmsFolder;
    std::string dataFolder;

public:
    Properties(const char* fileName);
    const std::string &getFurnitureCount() const;
    const std::string &getDataFolder() const;
    const std::string &getGMMsFolder() const;
};

#endif // PROPERTIES_H
