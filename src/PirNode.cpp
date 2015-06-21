#include "PirNode.hpp"
#include <cstring>

PirNode::PirNode(IMQTTProxy* proxy) :
    PirNode()
{
    updater = proxy;
}

PirNode::PirNode() :
    SensorNode(), updater(NULL)
{
    Item emptyItem = {ElementType::TEXT, "", 0};
    nodeParametersMap.insert(std::pair<uint8_t, Item>(0, emptyItem));
    nodeParametersMap.insert(std::pair<uint8_t, Item>(1, emptyItem));
}

PirNode::PirNode(uint8_t nodeId, uint8_t nodeType, uint8_t location, uint8_t nodeStatus, uint8_t presenceVal) :
    SensorNode(nodeId, nodeType, location, nodeStatus), updater(NULL)
{
    Item insertedItem = {ElementType::TEXT,  + "Status_" + std::to_string(nodeId), nodeStatus};
    nodeParametersMap.insert(std::pair<uint8_t, Item>(0, insertedItem));

    insertedItem.itemName = "Presence_" + std::to_string(nodeId);
    insertedItem.itemValue = presenceVal;
    nodeParametersMap.insert(std::pair<uint8_t, Item>(1, insertedItem));
}

PirNode::~PirNode() { }

std::map<uint8_t, Item> PirNode::getNodeParametersMap()
{
    return nodeParametersMap;
}

void PirNode::setNodeStatus(uint8_t newVal)
{
    std::map<const uint8_t, Item>::iterator pair = nodeParametersMap.find(0);
    Item item = {ElementType::TEXT, "Status_" + std::to_string(getNodeId()), newVal};
    if (pair != nodeParametersMap.end())
        pair->second = item;
    else
        nodeParametersMap.insert(std::pair<uint8_t, Item>(0, item));
}

uint8_t PirNode::getPresenceStatus()
{
    return nodeParametersMap.find(1)->second.itemValue;
}

void PirNode::setPresenceStatus(uint8_t newVal)
{
    std::map<const uint8_t, Item>::iterator pair = nodeParametersMap.find(1);
    Item item = {ElementType::TEXT, "Presence_" + std::to_string(getNodeId()), newVal};
    if (pair != nodeParametersMap.end())
        pair->second = item;
    else
        nodeParametersMap.insert(std::pair<uint8_t, Item>(1, item));

    if (updater)
        updater->publish("/Presence/" + std::to_string(nodeId), std::to_string(newVal));
}

uint8_t PirNode::getNodeId()
{
    return nodeId;
}

void PirNode::setNodeId(uint8_t newVal)
{
    nodeId = newVal;
    nodeParametersMap.find(0)->second.itemName = "Status_" + std::to_string(getNodeId());
    nodeParametersMap.find(1)->second.itemName = "Presence_" + std::to_string(getNodeId());
}

uint8_t PirNode::getNodeType()
{
    return nodeType;
}

void PirNode::setNodeType(uint8_t newVal)
{
    nodeType = newVal;
}

uint8_t PirNode::getLocation()
{
    return location;
}

void PirNode::setLocation(uint8_t newVal)
{
    location = newVal;
}

uint8_t PirNode::getNodeStatus()
{
    return nodeParametersMap.find(0)->second.itemValue;
}

void PirNode::updateValues(MsgData msgData)
{
    if (msgData.pirSensorData.result != getPresenceStatus())
        setPresenceStatus(msgData.pirSensorData.result);
}

std::string PirNode::generateItems()
{
    std::string itemsString = "Number " + nodeParametersMap.find(0)->second.itemName + " \"Status [%.1f]\" <sofa> { mqtt=\"<[thesisSystem:/Status/" + std::to_string(nodeId) + ":state:default\" }\n";
    itemsString += "Number " + nodeParametersMap.find(1)->second.itemName + " \"Pir Sensor Result [%.1f]\" <smartheaterhigh-off> { mqtt=\"<[thesisSystem:/Presence/" + std::to_string(nodeId) + ":state:default\" }\n";

    return itemsString;
}

