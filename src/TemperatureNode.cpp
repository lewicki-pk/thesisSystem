#include "TemperatureNode.hpp"
#include <cstring>

TemperatureNode::TemperatureNode() :
    SensorNode(), lastReadingStatus(0)
{
    Item emptyItem = {ElementType::TEXT, "", 0};
    nodeParametersMap.insert(std::pair<uint8_t, Item>(0, emptyItem));
    nodeParametersMap.insert(std::pair<uint8_t, Item>(1, emptyItem));
    nodeParametersMap.insert(std::pair<uint8_t, Item>(2, emptyItem));
}

TemperatureNode::TemperatureNode(uint8_t nodeId, uint8_t nodeType, uint8_t location, uint8_t nodeStatus, uint8_t temperatureVal, uint8_t humidityVal, uint8_t lastReadingVal) :
    SensorNode(nodeId, nodeType, location, nodeStatus), lastReadingStatus(lastReadingVal)
{
    Item insertedItem = {ElementType::TEXT,  + "Status_" + std::to_string(nodeId), nodeStatus};
    nodeParametersMap.insert(std::pair<uint8_t, Item>(0, insertedItem));

    insertedItem.itemName = "Temperature_" + std::to_string(nodeId);
    insertedItem.itemValue = temperatureVal;
    nodeParametersMap.insert(std::pair<uint8_t, Item>(1, insertedItem));

    insertedItem.itemName = "Humidity_" + std::to_string(nodeId);
    insertedItem.itemValue = humidityVal;
    nodeParametersMap.insert(std::pair<uint8_t, Item>(2, insertedItem));
}

TemperatureNode::~TemperatureNode() { }

std::map<uint8_t, Item> TemperatureNode::getNodeParametersMap()
{
    return nodeParametersMap;
}

void TemperatureNode::setNodeStatus(uint8_t newVal) {
    std::map<const uint8_t, Item>::iterator pair = nodeParametersMap.find(0);
    Item item = {ElementType::TEXT, "Status_" + std::to_string(getNodeId()), newVal};
    if (pair != nodeParametersMap.end())
        pair->second = item;
    else
        nodeParametersMap.insert(std::pair<uint8_t, Item>(0, item));
}

void TemperatureNode::setTemperatureValue(uint8_t newVal) {
    std::map<const uint8_t, Item>::iterator pair = nodeParametersMap.find(1);
    Item item = {ElementType::TEXT, "Temperature_" + std::to_string(getNodeId()), newVal};
    if (pair != nodeParametersMap.end())
        pair->second = item;
    else
        nodeParametersMap.insert(std::pair<uint8_t, Item>(1, item));
}

void TemperatureNode::setHumidityValue(uint8_t newVal) {
    std::map<const uint8_t, Item>::iterator pair = nodeParametersMap.find(2);
    Item item = {ElementType::TEXT, "Humidity_" + std::to_string(getNodeId()) , newVal};
    if (pair != nodeParametersMap.end())
        pair->second = item;
    else
        nodeParametersMap.insert(std::pair<uint8_t, Item>(2, item));
}

uint8_t TemperatureNode::getLastReadingStatus() {
    return lastReadingStatus;
}

void TemperatureNode::setLastReadingStatus(uint8_t newVal) {
    lastReadingStatus = newVal;
}

uint8_t TemperatureNode::getNodeId()
{
    return nodeId;
}

void TemperatureNode::setNodeId(uint8_t newVal)
{
    nodeId = newVal;
    nodeParametersMap.find(0)->second.itemName = "Status_" + std::to_string(getNodeId());
    nodeParametersMap.find(1)->second.itemName = "Temperature_" + std::to_string(getNodeId());
    nodeParametersMap.find(2)->second.itemName = "Humidity_" + std::to_string(getNodeId());
}

uint8_t TemperatureNode::getNodeType()
{
    return nodeType;
}

void TemperatureNode::setNodeType(uint8_t newVal)
{
    nodeType = newVal;
}

uint8_t TemperatureNode::getLocation()
{
    return location;
}

void TemperatureNode::setLocation(uint8_t newVal)
{
    location = newVal;
}

uint8_t TemperatureNode::getNodeStatus()
{
    return nodeParametersMap.find(0)->second.itemValue;
}

void TemperatureNode::updateValues(MsgData msgData)
{
    if (0 == msgData.tempSensorData.result) {
        setTemperatureValue(msgData.tempSensorData.temperature);
        setHumidityValue(msgData.tempSensorData.humidity);
    }
    lastReadingStatus = msgData.tempSensorData.result;
}

std::string TemperatureNode::generateItems()
{
    std::string itemsString = "Number " + nodeParametersMap.find(0)->second.itemName + " \"Status [%.1f]\" <temperature> {}\n";
    itemsString += "Number " + nodeParametersMap.find(1)->second.itemName + " \"Temperature [%.1f °C]\" <temperature> {}\n";
    itemsString += "Number " + nodeParametersMap.find(2)->second.itemName + " \"Humidity [%.1f %%]\" <temperature> {}\n";

    return itemsString;
}

