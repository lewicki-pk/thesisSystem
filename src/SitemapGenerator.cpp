#include "SitemapGenerator.hpp"

SitemapGenerator::SitemapGenerator() {
}

SitemapGenerator::~SitemapGenerator() {}

void SitemapGenerator::generateFullSitemap()
{
    openSitemapHead();
    for (SensorNode* sensorItr = sensorDBPtr->begin(); sensorItr < sensorDBPtr->end(); sensorItr++) {
        openSitemapFrame();
        sensorParametersMap sensorParameters = sensorItr->getNodeParametersMap();
        for (auto it = sensorParameters.begin(); it != sensorParameters.end(); it++) {
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

void SitemapGenerator::addSitemapText(sensorParametersPair& paramPair)
{
    sitemapConfigFile << "Text item=" << std::get<0>(paramPair) << "\n";
}
