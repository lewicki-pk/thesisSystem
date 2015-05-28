#pragma once

#include <IItemsGenerator.hpp>

#include <cstdint>
#include <map>
#include <sstream>
#include <string>
#include <utility>

#include <SensorNode.hpp>
#include <SensorDB.hpp>
#include <CommonInterfaces.hpp>

typedef std::pair<uint8_t, Item> sensorParametersPair;
typedef std::map<uint8_t, Item> sensorParametersMap;

class ItemsGenerator: public IItemsGenerator
{
public:

    ItemsGenerator();

    virtual ~ItemsGenerator();

    void generateFullItems();

    std::string getItemsConfigFile() {
        return itemsConfigFile.str();
    }

protected:

private:

    void openItemsHead();
    void openItemsFrame();
    void closeTag();
    void addItemsText(std::pair<uint8_t, Item> paramPair);
    std::string elementTypeToString(ElementType& typeToConvert);

    SensorDB *sensorDBPtr;
    std::stringstream itemsConfigFile;

};
