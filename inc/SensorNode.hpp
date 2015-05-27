#pragma once

#include <ISensorNode.hpp>

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <cstdint>
#include <memory>

#include <CommonInterfaces.hpp>
#include <CommonMessages.hpp>

/******************************* Abstract Class ****************************/

class SensorNode: public ISensorNode
{
public:

    SensorNode();
    SensorNode(uint8_t nodeId, uint8_t nodeType, uint8_t location, uint8_t nodeStatus);
    virtual ~SensorNode();

    virtual SensorNode* clone() =0;
    SensorNode(const SensorNode& copySource);

    bool operator< (const SensorNode& toCompare);

    bool isEqualTo(const SensorNode& sn);

protected:

    std::unique_ptr<uint8_t> nodeId;
    std::unique_ptr<uint8_t> nodeType;
    std::unique_ptr<uint8_t> location;
    std::unique_ptr<uint8_t> nodeStatus;
    std::map<uint8_t, Item> nodeParametersMap;

private:

};
