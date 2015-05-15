
#ifndef TEMPERATURENODE_H
#define TEMPERATURENODE_H
#include "SensorNode.hpp"

#include <string>
#include <vector>
#include <CommonMessages.hpp>
#include <CommonInterfaces.hpp>

class TemperatureNode : public SensorNode
{
public:

    TemperatureNode();

    virtual ~TemperatureNode();

    TemperatureNode& operator= (const TemperatureNode& copySource);

    std::map<uint8_t, Item> getNodeParametersMap();

    uint8_t* getNodeId();
    void setNodeId(uint8_t newVal);

    uint8_t* getNodeType();
    void setNodeType(uint8_t newVal);

    uint8_t* getLocation();
    void setLocation(uint8_t newVal);

    void setTemperatureValue(uint8_t new_var);

    void setHumidityValue(uint8_t new_var);

    void setLastReadingStatus(uint8_t new_var);

    uint8_t* getLastReadingStatus();

    void setNodeStatus(uint8_t new_var);

    uint8_t* getNodeStatus();

protected:

private:

    void initAttributes() ;

    uint8_t* lastReadingStatus;
    uint8_t* nodeStatus;
    std::map<uint8_t, Item> nodeParametersMap;

};

#endif // TEMPERATURENODE_H
