#include "ItemsGenerator.hpp"

ItemsGenerator::ItemsGenerator(std::shared_ptr<ISensorDB> sensorDBPtr) : sensorDBPtr(sensorDBPtr)
{
}

ItemsGenerator::~ItemsGenerator() {}

bool ItemsGenerator::generateFullItems()
{
    return false;
    //genItemName();
    //genItemType();
}

//void ItemsGenerator::openItemsHead()
//{
//}
//
//void ItemsGenerator::openItemsFrame()
//{
//}
//
//void ItemsGenerator::closeTag()
//{
//}
//
//void ItemsGenerator::addItemsText(std::pair<uint8_t, Item> paramPair)
//{
//}

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
    
