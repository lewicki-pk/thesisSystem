#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>
#include <dht.h>

#include <CommonMessages.hpp>

#define DHT11_PIN 5

// ce,csn pins
RF24 radio(9, 10);

//temperature and humidity sensor
dht DHT;

uint8_t thisNodeId = 0;
uint8_t thisNodeType = 1;

void initialize()
{
    Serial.begin(9600);
    radio.begin();
    radio.setPALevel(RF24_PA_LOW);
    radio.setChannel(0x4c);

    // open pipe for writing
    radio.openWritingPipe(RASPI_READ_ADDR);
    radio.openReadingPipe(1, RASPI_WRITE_ADDR);

    radio.enableDynamicPayloads();
    radio.setAutoAck(true);
    radio.powerUp();
    radio.startListening();
}

void sendRegisterNodeReq()
{
    Message message = {0};
    Header header = {thisNodeId, thisNodeType, 0, static_cast<uint8_t>(MsgType::INITIALIZATION), 1234, Status::ok};

    message.header = header;
    message.msgData = {0};

    radio.stopListening();
    radio.write(&message, sizeof(message));
    radio.startListening();
}

void waitForRegisterNodeResp()
{
    if (radio.available())
    {
        // dump the payloads until we've got everything
        Message receivedData = {0};
        radio.read(&receivedData, sizeof(Message));
        if ((receivedData.header.checksum == 1234) && (receivedData.header.msgType == static_cast<uint8_t>(MsgType::ACK_NACK)) && (receivedData.header.nodeId != 0))
        {
            thisNodeId = receivedData.header.nodeId;
        } else
        {
            sendRegisterNodeReq();
        }
    }

}

void readAndSendValues()
{
    Header header = {thisNodeId, thisNodeType, 0, static_cast<uint8_t>(MsgType::TEMP_SENSOR_DATA), 12345, Status::ok};

    TempSensorData dhtData;
    dhtData.result = DHT.read11(DHT11_PIN);
    dhtData.humidity = (int)DHT.humidity;
    dhtData.temperature = (int)DHT.temperature;


    Message message = {0};
    message.header = header;
    message.msgData.tempSensorData = (dhtData);

    radio.stopListening();
    radio.write(&message, sizeof(message));
    radio.startListening();

    {
        Serial.println(dhtData.result);
        Serial.println(dhtData.temperature);
        Serial.println(dhtData.humidity);
        Serial.println("--------------");
    }
}

void setup(void)
{
    initialize();
    sendRegisterNodeReq();
    while (thisNodeId == 0)
    {
        waitForRegisterNodeResp();
    }
}

void loop(void)
{
    digitalWrite(13, HIGH);

    readAndSendValues();

    // pause a second
    delay(1000);
    digitalWrite(13, LOW);
    delay(1000);
}
