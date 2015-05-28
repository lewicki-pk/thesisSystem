#pragma once

#include <IItemsGenerator.hpp>

#include <cstdint>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <memory>

#include <SensorNode.hpp>
#include <SensorDB.hpp>
#include <CommonInterfaces.hpp>

class ItemsGenerator: public IItemsGenerator
{
public:

    ItemsGenerator(std::shared_ptr<ISensorDB> sensorDBPtr);

    virtual ~ItemsGenerator();

    bool generateFullItems();

    std::string getItemsConfigFile() {
        return itemsConfigFile.str();
    }

protected:

private:

    std::string elementTypeToString(ElementType& typeToConvert);

    std::shared_ptr<ISensorDB> sensorDBPtr;
    std::stringstream itemsConfigFile;

};
