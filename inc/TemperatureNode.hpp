#ifndef TEMPERATURENODE_H
#define TEMPERATURENODE_H
#include "SensorNode.hpp"

class TemperatureNode : public SensorNode
{
public:

    TemperatureNode();
    TemperatureNode(uint8_t nodeId, uint8_t nodeType, uint8_t location, uint8_t nodeStatus, uint8_t temperatureVal, uint8_t humidityVal, uint8_t lastReadingVal);
    virtual ~TemperatureNode();

    virtual TemperatureNode* clone();
    TemperatureNode(const TemperatureNode& copySource);

    bool operator< (const SensorNode& toCompare);

    std::map<uint8_t, Item>* getNodeParametersMap();

    uint8_t* getNodeId();
    void setNodeId(uint8_t newVal);

    uint8_t* getNodeType();
    void setNodeType(uint8_t newVal);

    uint8_t* getLocation();
    void setLocation(uint8_t newVal);

    uint8_t* getNodeStatus();
    void setNodeStatus(uint8_t newVal);

    uint8_t* getLastReadingStatus();
    void setLastReadingStatus(uint8_t newVal);

    void setTemperatureValue(uint8_t newVal);

    void setHumidityValue(uint8_t newVal);

protected:

    std::unique_ptr<uint8_t> lastReadingStatus;

private:

};

#endif // TEMPERATURENODE_H
