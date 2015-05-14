
#ifndef SENSORNODE_H
#define SENSORNODE_H

#include <string>
#include <vector>
#include <map>
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

    virtual std::map<uint8_t, Item> getNodeParametersMap();

    virtual void getNodeId() =0;
    virtual void setNodeId() =0;

    virtual void getNodeType() =0;
    virtual void setNodeType() =0;

    virtual void getLocation() =0;
    virtual void setLocation() =0;

    void getSensorValues ()
    {
    }

protected:

private:

    uint8_t nodeId;
    uint8_t nodeType;
    uint8_t location;
};

#endif // SENSORNODE_H
