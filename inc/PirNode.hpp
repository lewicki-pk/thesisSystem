#pragma once

#include "SensorNode.hpp"
#include "MQTTProxy.hpp"

class PirNode : public SensorNode
{
public:

    PirNode();
    PirNode(IMQTTProxy* proxy);
    PirNode(uint8_t nodeId, uint8_t nodeType, uint8_t location, uint8_t nodeStatus, uint8_t presenceVal);
    PirNode(const PirNode&) = default;
    PirNode(PirNode&&) = default;
    PirNode& operator=(const PirNode&) & = default;
    PirNode& operator=(PirNode&&) & = default;
    virtual ~PirNode();

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

    uint8_t getPresenceStatus();
    void setPresenceStatus(uint8_t newVal);

    void updateValues(MsgData msgData);

    std::string generateItems();

protected:

    IMQTTProxy* updater;

private:

};

