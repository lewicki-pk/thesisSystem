#include <Arduino.h>
#include <EEPROM.h>

#include "UniRadio.hpp"
#include "CommonMessages.hpp"

#define DHT11_PIN 5

// ce,csn pins
UniRadio radio(9, 10);


uint8_t thisNodeId = 0;
uint8_t thisNodeType = 2; // nodeType 1 = tempSensor, 2 = PIR sensor

bool isInitialized = false;


void initialize()
{
    Serial.begin(9600);

    radio.setup();

    uint8_t eepromId = EEPROM.read(1);
    if (eepromId == 255)
        thisNodeId = 0;
    else
        thisNodeId = eepromId;
}

void sendRegisterNodeReq()
{
    Message message = {0};
    Header header = {thisNodeId, thisNodeType, 0, static_cast<uint8_t>(MsgType::INITIALIZATION), 1234, Status::ok};

    message.header = header;
    message.msgData = {0};

    radio.sendMessage(message);
}

void waitForRegisterNodeResp()
{
    if (radio.isAvailable())
    {
        Message receivedData = radio.getMessage();
        if ((receivedData.header.msgType == static_cast<uint8_t>(MsgType::RESET_REQUEST)) && (receivedData.header.checksum == 1234))
        {
            thisNodeId = 0;
            EEPROM.update(1, thisNodeId);
            sendRegisterNodeReq();
        }
        else if ((receivedData.header.checksum == 1234) && (receivedData.header.msgType == static_cast<uint8_t>(MsgType::ACK_NACK)) && (receivedData.header.nodeId != 0))
        {
            thisNodeId = receivedData.header.nodeId;
            EEPROM.update(1, thisNodeId);
            isInitialized = true;
        }
        else
        {
            sendRegisterNodeReq();
        }
    }

}

void readAndSendValues()
{
    Header header = {thisNodeId, thisNodeType, 0, static_cast<uint8_t>(MsgType::PIR_VALUE), 12345, Status::ok};

    PirSensorData pirData;
    pirData.result = digitalRead(5);

    Message message = {0};
    message.header = header;
    message.msgData.pirSensorData = (pirData);

    radio.sendMessage(message);
}

void setup(void)
{
    initialize();
    sendRegisterNodeReq();
    while (!isInitialized)
    {
        waitForRegisterNodeResp();
    }
}

void loop(void)
{
    digitalWrite(13, HIGH);

    readAndSendValues();

    // pause a few seconds
    delay(4000);
    digitalWrite(13, LOW);
    delay(4000);
}

