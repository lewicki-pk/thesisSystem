
#ifndef SITEMAPGENERATOR_H
#define SITEMAPGENERATOR_H

#include <string>

/**
  * class SitemapGenerator
  * 
  */

class SitemapGenerator
{
public:

    SitemapGenerator ();

    virtual ~SitemapGenerator ();

    void generateFullSitemap();

protected:

private:

    void openSitemapHead();
    void openSitemapFrame(SensorNode* sensorNode);
    void closeTag();
    void addSitemapText(sensorParametersPair* paramPair);

    SensorDB *sensorDBPtr;

};

#endif // SITEMAPGENERATOR_H
