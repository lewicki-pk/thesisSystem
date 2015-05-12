#include "SitemapGenerator.h"
#include <string>
#include <map>
#include <utility>

SitemapGenerator::SitemapGenerator () {
}

SitemapGenerator::~SitemapGenerator () { }

//  
// Methods
//  

typedef std::pair<string, uint8_t> sensorParametersPair;
typedef std::map<sensorParametersPair> sensorParametersMap;

void SitemapGenerator::generateFullSitemap()
{
    openSitemapHead();
    for (SensorNode* sensorItr = sensorDBPtr->begin(); sensorItr < sensorDBPtr->end(); sensorItr++) {
        openSitemapFrame(sensorItr);
        sensorParametersMap sensorParameters = sensorItr->getNodeParametersMap();
        uint8_t mapSize = sensorParameters.size();
        for (uint8_t i = 0; i < mapSize; i++) {
            addSitemapText(sensorParameters[i]);
        }
        closeTag();
    }
    closeTag();
}

void SitemapGenerator::openSitemapHead()
{
    sitemapConfigFile << "sitemap thesisSystem label=\"Main Menu\" \n{";
}

void SitemapGenerator::openSitemapFrame(SensorNode* sensorNode)
{
    sitemapConfigFile << "Frame {\n";
}

void SitemapGenerator::closeTag()
{
    sitemapConfigFile << "}\n";
}

void SitemapGenerator::addSitemapText(sensorParametersPair* paramPair)
{
    sitemapConfigFile << "Text item=" << std::get<0>(paramPair) << "\n";

}

// Accessor methods
//  


// Other methods
//  


