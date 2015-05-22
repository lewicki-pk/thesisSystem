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

bool SensorNode::operator< (const SensorNode& toCompare) {
    if (this->nodeId < toCompare.nodeId)
        return true;
    else
        return false;
}

bool SensorNode::isEqualTo(const SensorNode& sn)
{
    if ((*this->nodeId.get() == *sn.nodeId.get()) &&
        (*this->nodeType.get() == *sn.nodeType.get()) &&
        (*this->location.get() == *sn.location.get()))
        return true;
    else
        return false;
}
