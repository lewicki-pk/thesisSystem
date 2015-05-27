#pragma once

#include <string>

class ISitemapGenerator
{
public:
    ISitemapGenerator() { }

    virtual ~ISitemapGenerator() { }

    virtual void generateFullSitemap() =0;

    virtual std::string getSitemapConfigFile() =0;
};
