
#ifndef TEMPERATURENODE_H
#define TEMPERATURENODE_H
#include "SensorNode.hpp"

#include <string>
#include <vector>
#include <CommonMessages.hpp>
#include <CommonInterfaces.hpp>

class TemperatureNode : virtual public SensorNode
{
public:

    TemperatureNode();

    virtual ~TemperatureNode();

    TemperatureNode& operator= (const TemperatureNode& copySource);

    std::map<uint8_t, Item> getNodeParametersMap();

    void getNodeId();
    void setNodeId();

    void getNodeType();
    void setNodeType();

    void getLocation();
    void setLocation();

    void setTemperatureValue(uint8_t new_var);

    void setHumidityValue(uint8_t new_var);

    void setLastReadingStatus(uint8_t new_var);

    uint8_t getLastReadingStatus();

    void setNodeStatus(uint8_t new_var);

    uint8_t getNodeStatus();

    std::map<uint8_t, Item> getNodeParametersMap();

protected:

private:

    void initAttributes() ;

    uint8_t lastReadingStatus;
    uint8_t nodeStatus;
    std::map<uint8_t, Item> nodeParametersMap;

};

#endif // TEMPERATURENODE_H
