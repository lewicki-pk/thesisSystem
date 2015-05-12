#include "SensorNode.h"
#include <cstdint>

// Constructors/Destructors
//  

SensorNode::SensorNode () {
}

SensorNode::~SensorNode () { }

std::map<std::string, uint8_t> SensorNode::getNodeParametersMap()
{
    std::map<std::string, uint8_t> retValue;

    retValue["string"]=5;
    return retValue;
}


//  
// Methods
//  


// Accessor methods
//  


// Other methods
//  


