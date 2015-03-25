#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <string>
class Properties
{
    std::string furnCount;
    std::string gmmsFolder;
    std::string dataFolder;
    std::string furnInfo;
    std::string XMLDatabase;
    std::string conversationProp;

public:
    Properties(const char* fileName);
    const std::string &getFurnitureCount() const;
    const std::string &getDataFolder() const;
    const std::string &getGMMsFolder() const;
    const std::string &getFurnitureInfo() const;
    const std::string &getXMLDatabase() const;
    const std::string &getConversationProp() const;
};

#endif // PROPERTIES_H
