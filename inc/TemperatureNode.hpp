#pragma once

#include "SensorNode.hpp"

class TemperatureNode : public SensorNode
{
public:

    TemperatureNode();
    TemperatureNode(uint8_t nodeId, uint8_t nodeType, uint8_t location, uint8_t nodeStatus, uint8_t temperatureVal, uint8_t humidityVal, uint8_t lastReadingVal);
    TemperatureNode(const TemperatureNode&) = default;
    TemperatureNode(TemperatureNode&&) = default;
    TemperatureNode& operator=(const TemperatureNode&) & = default;
    TemperatureNode& operator=(TemperatureNode&&) & = default;
    virtual ~TemperatureNode();

    bool operator< (const SensorNode& toCompare);

    std::map<uint8_t, Item> getNodeParametersMap();

    uint8_t getNodeId();
    void setNodeId(uint8_t newVal);

    uint8_t getNodeType();
    void setNodeType(uint8_t newVal);

    uint8_t getLocation();
    void setLocation(uint8_t newVal);

    uint8_t getNodeStatus();
    void setNodeStatus(uint8_t newVal);

    uint8_t getLastReadingStatus();

    void setLastReadingStatus(uint8_t newVal);

    void setTemperatureValue(uint8_t newVal);

    void setHumidityValue(uint8_t newVal);

    void updateValues(MsgData msgData);

    std::string generateItems();

protected:

    uint8_t lastReadingStatus;

private:

};

