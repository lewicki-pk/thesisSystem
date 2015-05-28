#include "ItemsGenerator.hpp"

ItemsGenerator::ItemsGenerator(std::shared_ptr<ISensorDB> sensorDBPtr) : sensorDBPtr(sensorDBPtr)
{
}

ItemsGenerator::~ItemsGenerator() {}

bool ItemsGenerator::generateFullItems()
{
    return true;
}

std::string ItemsGenerator::elementTypeToString(ElementType& typeToConvert) {
    std::string returnString;
    switch (typeToConvert)
    {
    case ElementType::TEXT :
        returnString = "Number";
        break;
    case ElementType::SWITCH :
        returnString = "Switch";
        break;
    default :
        break;
    }
    return returnString;
}
    
