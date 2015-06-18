#pragma once

#include "RF24.h"
#include "CommonMessages.hpp"

class UniRadio
{
public:

    UniRadio(uint8_t, uint8_t);

    virtual ~UniRadio();

    void setup();

    bool isAvailable();

    void sendMessage(Message &message);

    Message getMessage();

protected:

    RF24 *radio;
};
