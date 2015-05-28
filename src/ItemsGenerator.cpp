#include "ItemsGenerator.hpp"

ItemsGenerator::ItemsGenerator() : sensorDBPtr(SensorDB::getInstance())
{
}

ItemsGenerator::~ItemsGenerator() {}

void ItemsGenerator::generateFullItems()
{
    itemsConfigFile.str(std::string());
    openItemsHead();
    for (auto sensorItr = sensorDBPtr->begin();
            sensorItr != sensorDBPtr->end();
            sensorItr++) {
        openItemsFrame();

        std::map<uint8_t, Item>* sensorParameters = (*sensorItr).second->getNodeParametersMap();
        for (auto it = sensorParameters->begin(); it != sensorParameters->end(); it++) {
            addItemsText(*it);
        }
        closeTag();
    }
    closeTag();
}

void ItemsGenerator::openItemsHead()
{
    itemsConfigFile << "items thesisSystem label=\"Main Menu\" \n{\n";
}

void ItemsGenerator::openItemsFrame()
{
    itemsConfigFile << "Frame {\n";
}

void ItemsGenerator::closeTag()
{
    itemsConfigFile << "}\n";
}

void ItemsGenerator::addItemsText(std::pair<uint8_t, Item> paramPair)
{
    Item* item = &(std::get<1>(paramPair));
    itemsConfigFile << elementTypeToString(item->elementType) << " item=" << item->itemName << "\n";
}

std::string ItemsGenerator::elementTypeToString(ElementType& typeToConvert) {
    std::string returnString;
    switch (typeToConvert)
    {
    case ElementType::TEXT :
        returnString = "Text";
        break;
    case ElementType::SWITCH :
        returnString = "Switch";
        break;
    default :
        break;
    }
    return returnString;
}
    
