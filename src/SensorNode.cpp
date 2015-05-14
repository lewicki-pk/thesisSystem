#include "SensorNode.hpp"
#include <cstdint>

SensorNode::SensorNode() {
}

SensorNode::~SensorNode() { }

bool SensorNode::operator< (const SensorNode& toCompare) {
    if (this->nodeId < toCompare.nodeId)
        return true;
    else
        return false;
}
