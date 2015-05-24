#include "TemperatureNode.hpp"
#include <cstring>

TemperatureNode::TemperatureNode() :
    SensorNode(), lastReadingStatus(nullptr)
{
    Item emptyItem = {ElementType::TEXT, "", 0};
    nodeParametersMap.insert(std::pair<uint8_t, Item>(0, emptyItem));
    nodeParametersMap.insert(std::pair<uint8_t, Item>(1, emptyItem));
    nodeParametersMap.insert(std::pair<uint8_t, Item>(2, emptyItem));
}

TemperatureNode::TemperatureNode(uint8_t nodeId, uint8_t nodeType, uint8_t location, uint8_t nodeStatus, uint8_t temperatureVal, uint8_t humidityVal, uint8_t lastReadingVal) :
    SensorNode(nodeId, nodeType, location, nodeStatus), lastReadingStatus(new uint8_t(lastReadingVal))
{
    std::string nodeIdStr = std::to_string(nodeId) + "_";
    Item insertedItem = {ElementType::TEXT, nodeIdStr + "Status", nodeStatus};
    nodeParametersMap.insert(std::pair<uint8_t, Item>(0, insertedItem));

    insertedItem.itemName = nodeIdStr + "Temperature";
    insertedItem.itemValue = temperatureVal;
    nodeParametersMap.insert(std::pair<uint8_t, Item>(1, insertedItem));

    insertedItem.itemName = nodeIdStr + "Humidity";
    insertedItem.itemValue = humidityVal;
    nodeParametersMap.insert(std::pair<uint8_t, Item>(2, insertedItem));
}

TemperatureNode::~TemperatureNode() { }

TemperatureNode* TemperatureNode::clone()
{
    return (new TemperatureNode(*this));
}

TemperatureNode::TemperatureNode(const TemperatureNode& copySource) : SensorNode()
{
    if (this != &copySource) {
        this->nodeId.reset(new uint8_t(*copySource.nodeId.get()));
        this->nodeType.reset(new uint8_t(*copySource.nodeType.get()));
        this->location.reset(new uint8_t(*copySource.location.get()));
        this->nodeStatus.reset(new uint8_t(*copySource.nodeStatus.get()));
        this->lastReadingStatus.reset(new uint8_t(*copySource.lastReadingStatus.get()));
        this->nodeParametersMap = copySource.nodeParametersMap;
    }
}

std::map<uint8_t, Item>* TemperatureNode::getNodeParametersMap()
{
    return &nodeParametersMap;
}

void TemperatureNode::setNodeStatus(uint8_t newVal) {
    std::map<const uint8_t, Item>::iterator pair = nodeParametersMap.find(0);
    Item item = {ElementType::TEXT, std::to_string(*getNodeId()) + "_Status", newVal};
    if (pair != nodeParametersMap.end())
        pair->second = item;
    else
        nodeParametersMap.insert(std::pair<uint8_t, Item>(0, item));
}

void TemperatureNode::setTemperatureValue(uint8_t newVal) {
    std::map<const uint8_t, Item>::iterator pair = nodeParametersMap.find(1);
    Item item = {ElementType::TEXT, std::to_string(*getNodeId()) + "_Temperature", newVal};
    if (pair != nodeParametersMap.end())
        pair->second = item;
    else
        nodeParametersMap.insert(std::pair<uint8_t, Item>(0, item));
}

void TemperatureNode::setHumidityValue(uint8_t newVal) {
    std::map<const uint8_t, Item>::iterator pair = nodeParametersMap.find(2);
    Item item = {ElementType::TEXT, std::to_string(*getNodeId()) + "_Humidity", newVal};
    if (pair != nodeParametersMap.end())
        pair->second = item;
    else
        nodeParametersMap.insert(std::pair<uint8_t, Item>(0, item));
}

uint8_t* TemperatureNode::getLastReadingStatus() {
    return lastReadingStatus.get();
}

void TemperatureNode::setLastReadingStatus(uint8_t newVal) {
    lastReadingStatus.reset(new uint8_t(newVal));
}

uint8_t* TemperatureNode::getNodeId()
{
    return nodeId.get();
}

void TemperatureNode::setNodeId(uint8_t newVal)
{
    nodeId.reset(new uint8_t(newVal));
    this->setNodeStatus((*nodeParametersMap.find(0)).second.itemValue);
    this->setTemperatureValue((*nodeParametersMap.find(1)).second.itemValue);
    this->setHumidityValue((*nodeParametersMap.find(2)).second.itemValue);
}

uint8_t* TemperatureNode::getNodeType()
{
    return nodeType.get();
}

void TemperatureNode::setNodeType(uint8_t newVal)
{
    nodeType.reset(new uint8_t(newVal));
}

uint8_t* TemperatureNode::getLocation()
{
    return location.get();
}

void TemperatureNode::setLocation(uint8_t newVal)
{
    location.reset(new uint8_t(newVal));
}

uint8_t* TemperatureNode::getNodeStatus()
{
    return &((*nodeParametersMap.find(0)).second.itemValue);
}

void TemperatureNode::updateValues(MsgData msgData)
{
    if (0 == msgData.tempSensorData.result) {
        setTemperatureValue(msgData.tempSensorData.temperature);
        setHumidityValue(msgData.tempSensorData.humidity);
    }
}

