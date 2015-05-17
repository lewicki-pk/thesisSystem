#ifndef SENSORNODE_H
#define SENSORNODE_H

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <cstdint>
#include <memory>

#include <CommonInterfaces.hpp>
#include <CommonInterfaces.hpp>

/******************************* Abstract Class ****************************/

class SensorNode
{
public:

    SensorNode();
    SensorNode(uint8_t nodeId, uint8_t nodeType, uint8_t location, uint8_t nodeStatus);
    virtual ~SensorNode();

    virtual SensorNode* clone() =0;
    SensorNode(const SensorNode& copySource);

    bool operator< (const SensorNode& toCompare);


    virtual std::map<uint8_t, Item>* getNodeParametersMap() =0;

    virtual uint8_t* getNodeId() =0;
    virtual void setNodeId(uint8_t newVal) =0;

    virtual uint8_t* getNodeType() =0;
    virtual void setNodeType(uint8_t newVal) =0;

    virtual uint8_t* getLocation() =0;
    virtual void setLocation(uint8_t newVal) =0;

    virtual uint8_t* getNodeStatus() =0;
    virtual void setNodeStatus(uint8_t newVal) =0;

protected:

    std::unique_ptr<uint8_t> nodeId;
    std::unique_ptr<uint8_t> nodeType;
    std::unique_ptr<uint8_t> location;
    std::unique_ptr<uint8_t> nodeStatus;
    std::map<uint8_t, Item> nodeParametersMap;

private:

};

#endif // SENSORNODE_H
