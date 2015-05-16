#include "SitemapGenerator.hpp"

SitemapGenerator::SitemapGenerator() : sensorDBPtr(SensorDB::getInstance())
{
}

SitemapGenerator::~SitemapGenerator() {}

void SitemapGenerator::generateFullSitemap()
{
    openSitemapHead();
    for (std::set<SensorNode*>::iterator sensorItr = sensorDBPtr->begin();
            sensorItr != sensorDBPtr->end();
            sensorItr++) {
        openSitemapFrame();

        std::map<uint8_t, Item>* sensorParameters = (*sensorItr)->getNodeParametersMap();
        for (auto it = sensorParameters->begin(); it != sensorParameters->end(); it++) {
            addSitemapText(*it);
        }
        closeTag();
    }
    closeTag();
}

void SitemapGenerator::openSitemapHead()
{
    sitemapConfigFile << "sitemap thesisSystem label=\"Main Menu\" \n{\n";
}

void SitemapGenerator::openSitemapFrame()
{
    sitemapConfigFile << "Frame {\n";
}

void SitemapGenerator::closeTag()
{
    sitemapConfigFile << "}\n";
}

void SitemapGenerator::addSitemapText(std::pair<uint8_t, Item> paramPair)
{
    Item* item = &(std::get<1>(paramPair));
    sitemapConfigFile << elementTypeToString(item->elementType) << " item=" << item->itemName << "\n";
}

std::string SitemapGenerator::elementTypeToString(ElementType& typeToConvert) {
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
    
