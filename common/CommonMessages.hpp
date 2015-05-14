#pragma once

#include <stdint.h>

struct TempSensorData
{
    uint32_t result;
    uint32_t temperature;
    uint32_t humidity;
};

enum class AckNack : uint8_t
{
    Nack,
    Ack
};

enum class Status : uint8_t
{
    ok,
    error,
    fail
};

struct Header
{
    uint8_t nodeId;
    uint8_t nodeType;
    uint8_t location;
    Status status;
    
};

struct Message
{
    Header header;
    union MsgData
    {
        AckNack ackNack;
        TempSensorData tempSensorData;
    } msgData;
};
