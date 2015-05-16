#include "SensorNode.hpp"
#include <cstdint>
#include <cstring>

SensorNode::SensorNode() :
    nodeId(nullptr), nodeType(nullptr), location(nullptr), nodeStatus(nullptr)
{ }

SensorNode::SensorNode(uint8_t nodeId, uint8_t nodeType, uint8_t location, uint8_t nodeStatus) :
    nodeId(new uint8_t(nodeId)), nodeType(new uint8_t(nodeType)),
    location(new uint8_t(location)), nodeStatus(new uint8_t(nodeStatus))
{ }

SensorNode::~SensorNode()
{ }

SensorNode::SensorNode(const SensorNode& copySource) :
    nodeId(new uint8_t(*copySource.nodeId)), nodeType(new uint8_t(*copySource.nodeType)),
    location(new uint8_t(*copySource.location)), nodeStatus(new uint8_t(*copySource.nodeStatus))
{ }

SensorNode& SensorNode::operator= (const SensorNode& copySource)
{
//TODO implement this but for now I leave it empty
//    this->nodeId(new uint8_t(*copySource.nodeId));
//    this->nodeType(new uint8_t(*copySource.nodeType));
//    this->location(new uint8_t(*copySource.location));
//    this->nodeStatus(new uint8_t(*copySource.nodeStatus));
    return *this;
}

bool SensorNode::operator< (const SensorNode& toCompare) {
    if (this->nodeId < toCompare.nodeId)
        return true;
    else
        return false;
}
