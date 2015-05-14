
#ifndef SITEMAPGENERATOR_H
#define SITEMAPGENERATOR_H

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

class SitemapGenerator
{
public:

    SitemapGenerator ();

    virtual ~SitemapGenerator ();

    void generateFullSitemap();

    std::string getSitemapConfigFile() {
        return sitemapConfigFile.str();
    }

protected:

private:

    void openSitemapHead();
    void openSitemapFrame();
    void closeTag();
    void addSitemapText(std::pair<uint8_t, Item> paramPair);
    std::string elementTypeToString(ElementType& typeToConvert);

    SensorDB *sensorDBPtr;
    std::stringstream sitemapConfigFile;

};

#endif // SITEMAPGENERATOR_H
