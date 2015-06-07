#include <IMQTTProxy.hpp>
#include <string>

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "MQTTClient.h"
#include <iostream>

class MQTTProxy : public IMQTTProxy
{
public:
    bool publish(std::string topic, std::string payload);
    
};
