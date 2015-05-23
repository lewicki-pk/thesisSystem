#pragma once

#include <stdint.h>

#define RASPI_WRITE_ADDR 0xF0F0F0F0F0LL
#define RASPI_READ_ADDR 0xF0F0F0F0E1LL

struct InitMsgData
{
    uint32_t retryCounter;
};

struct TempSensorData
{
    uint32_t result;
    uint32_t temperature;
    uint32_t humidity;
};

enum class AckNack : uint8_t
{
    NACK,
    ACK
};

enum class Status : uint8_t
{
    ok,
    error,
    fail
};

enum class MsgType : uint8_t
{
    INITIALIZATION,
    RESET_REQUEST,
    ACK_NACK,
    TEMP_SENSOR_DATA,
};

struct Header
{
    uint8_t nodeId;
    uint8_t nodeType;
    uint8_t location;
    uint8_t msgType;
    uint16_t checksum;
    Status status;
};

struct Message
{
    Header header;
    union MsgData
    {
        InitMsgData initMsgData;
        AckNack ackNack;
        TempSensorData tempSensorData;
    } msgData;
};
