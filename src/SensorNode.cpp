#include "SensorNode.hpp"
#include <cstdint>

SensorNode::SensorNode() {
}

SensorNode::~SensorNode() { }

std::multimap<std::string, uint8_t> SensorNode::getNodeParametersMap()
{
#ifndef UNIT_TEST
    std::map<std::string, uint8_t> retValue;

    retValue["string"]=5;
    return retValue;
#endif
}

