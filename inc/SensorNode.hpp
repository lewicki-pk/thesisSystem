
#ifndef SENSORNODE_H
#define SENSORNODE_H

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <cstdint>

#include <CommonInterfaces.hpp>

/******************************* Abstract Class ****************************
SensorNode does not have any pure virtual methods, but its author
  defined it as an abstract class, so you should not use it directly.
  Inherit from it instead and create only objects from the derived classes
*****************************************************************************/

class SensorNode
{
public:

    SensorNode();
    virtual ~SensorNode();
    virtual SensorNode& operator= (const SensorNode& copySource) =0;

    bool operator< (const SensorNode& toCompare);

    virtual std::map<uint8_t, Item> getNodeParametersMap() =0;

    virtual uint8_t getNodeId() =0;
    virtual void setNodeId(uint8_t newVal) =0;

    virtual uint8_t getNodeType() =0;
    virtual void setNodeType(uint8_t newVal) =0;

    virtual uint8_t getLocation() =0;
    virtual void setLocation(uint8_t newVal) =0;

    void getSensorValues ()
    {
    }

protected:

    uint8_t nodeId;
    uint8_t nodeType;
    uint8_t location;

private:
};

#endif // SENSORNODE_H
