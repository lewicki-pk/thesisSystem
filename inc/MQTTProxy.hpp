#pragma once

#include <IMQTTProxy.hpp>
#include <string>

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#ifndef UNIT_TEST
#include "MQTTClient.h"
#endif
#include <iostream>

class MQTTProxy : public IMQTTProxy
{
public:

    bool publish(std::string topic, std::string payload);

    virtual ~MQTTProxy();

    static MQTTProxy* getInstance();

protected:

    MQTTProxy();

    static MQTTProxy* _instance;

};
