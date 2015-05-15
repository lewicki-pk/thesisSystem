#include "TemperatureNode.hpp"

TemperatureNode::TemperatureNode() {
    initAttributes();
}

TemperatureNode::~TemperatureNode() { }

TemperatureNode& TemperatureNode::operator= (const TemperatureNode& copySource)
{
    if (this != &copySource)
    {
        this->nodeId = copySource.nodeId;
        this->nodeType = copySource.nodeType;
        this->location = copySource.location;
        this->lastReadingStatus = copySource.lastReadingStatus;
        this->nodeStatus = copySource.nodeStatus;
        this->nodeParametersMap = copySource.nodeParametersMap;
    }
    return *this;
}

void TemperatureNode::initAttributes()
{
        nodeId = new uint8_t;
        nodeType = new uint8_t;
        location = new uint8_t;
        lastReadingStatus = new uint8_t;
        nodeStatus = new uint8_t;
        Item emptyItem = {ElementType::TEXT, "", 0};
        nodeParametersMap.insert(std::pair<uint8_t, Item>(0, emptyItem));
        nodeParametersMap.insert(std::pair<uint8_t, Item>(1, emptyItem));
        nodeParametersMap.insert(std::pair<uint8_t, Item>(2, emptyItem));
}

std::map<uint8_t, Item> TemperatureNode::getNodeParametersMap()
{
    return nodeParametersMap;
}

void TemperatureNode::setTemperatureValue(uint8_t new_var) {
    //TODO fix this option when item is not set
    std::pair<const uint8_t, Item> pair = *(nodeParametersMap.find(1));
    if (&pair != &*nodeParametersMap.end())
    {
        Item* item = &(pair.second);
        item->elementType = ElementType::TEXT;
        item->itemName = *getNodeId() + "_Temperature";
        item->itemValue = new_var;
    }
}

void TemperatureNode::setHumidityValue(uint8_t new_var) {
    std::pair<const uint8_t, Item> pair = *(nodeParametersMap.find(2));
    if (&pair != &*nodeParametersMap.end())
    {
        Item* item = &(pair.second);
        item->elementType = ElementType::TEXT;
        item->itemName = *getNodeId() + "_Humidity";
        item->itemValue = new_var;
    }
}

void TemperatureNode::setLastReadingStatus(uint8_t new_var) {
    *lastReadingStatus = new_var;
}

uint8_t* TemperatureNode::getLastReadingStatus() {
    return lastReadingStatus;
}

void TemperatureNode::setNodeStatus(uint8_t new_var) {
    std::pair<const uint8_t, Item> pair = *(nodeParametersMap.find(0));
    if (&pair != &*nodeParametersMap.end())
    {
        Item* item = &(pair.second);
        item->elementType = ElementType::TEXT;
        item->itemName = *getNodeId() + "_Status";
        item->itemValue = new_var;
    }
}

uint8_t* TemperatureNode::getNodeId()
{
    return nodeId;
}

void TemperatureNode::setNodeId(uint8_t newVal)
{
    *nodeId = newVal;
}

uint8_t* TemperatureNode::getNodeType()
{
    return nodeType;
}

void TemperatureNode::setNodeType(uint8_t newVal)
{
    *nodeType = newVal;
}

uint8_t* TemperatureNode::getLocation()
{
    return location;
}

void TemperatureNode::setLocation(uint8_t newVal)
{
    *location = newVal;
}

