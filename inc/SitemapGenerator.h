
#ifndef SITEMAPGENERATOR_H
#define SITEMAPGENERATOR_H

#include <cstdint>
#include <map>
#include <sstream>
#include <string>
#include <utility>

#include <SensorNode.h>
#include <SensorDB.h>

typedef std::pair<const std::string, uint8_t> sensorParametersPair;
typedef std::map<std::string, uint8_t> sensorParametersMap;

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
    void addSitemapText(sensorParametersPair& paramPair);

    SensorDB *sensorDBPtr;
    std::stringstream sitemapConfigFile;

};

#endif // SITEMAPGENERATOR_H
