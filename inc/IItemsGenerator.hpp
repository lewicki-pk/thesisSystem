#pragma once

#include <string>

class IItemsGenerator
{
public:
    IItemsGenerator() { }

    virtual ~IItemsGenerator() { }

    virtual void generateFullItems() =0;

    virtual std::string getItemsConfigFile() =0;
};
