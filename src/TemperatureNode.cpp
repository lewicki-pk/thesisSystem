#include "TemperatureNode.hpp"

TemperatureNode::TemperatureNode() {
    initAttributes();
}

TemperatureNode::~TemperatureNode() { }

TemperatureNode& operator= (const TemperatureNode& copySource)
{
    if (this != &copySource)
    {
        this.nodeId = copySource.nodeId;
        this.nodeType = copySource.nodeType;
        this.location = copySource.location;
        this.lastReadingStatus = copySource.lastReadingStatus;
        this.nodeStatus = copySource.nodeStatus;
        this.nodeParametersMap = copySource.nodeParametersMap;
    }
}

void TemperatureNode::initAttributes() {
}

std::map<uint8_t, Item> TemperatureNode::getNodeParametersMap()
{
    return nodeParametersMap;
}

void setTemperatureValue(uint8_t new_var) {
    //TODO this option when item is not set
    Item* item = &nodeParametersMap[1].second;
    item->elementType = ElementType::Text;
    item->itemName = getNodeId + "_Temperature";
    item->itemValue = new_var;
}

void setHumidityValue(uint8_t new_var) {
    Item* item = &nodeParametersMap[2].second;
    item->elementType = ElementType::Text;
    item->itemName = getNodeId + "_Humidity";
    item->itemValue = new_var;
}

void setLastReadingStatus(uint8_t new_var) {
    lastReadingStatus = new_var;
}

uint8_t getLastReadingStatus() {
    return lastReadingStatus;
}

void setNodeStatus(uint8_t new_var) {
    Item* item = &nodeParametersMap[0].second;
    item->elementType = ElementType::Text;
    item->itemName = getNodeId + "_Status";
    item->itemValue = new_var;
}

uint8_t getNodeStatus() {
    return nodeStatus;
}
