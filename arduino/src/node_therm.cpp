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

void setup(void)
{
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(0x4c);

  // open pipe for writing
  radio.openWritingPipe(RASPI_READ_ADDR);

  radio.enableDynamicPayloads();
  radio.setAutoAck(true);
  radio.powerUp();
}

void loop(void)
{
    digitalWrite(13, HIGH);
    Header header = {1, 0, 0, Status::ok};

    TempSensorData dhtData;
    dhtData.result = DHT.read11(DHT11_PIN);
    dhtData.humidity = (int)DHT.humidity;
    dhtData.temperature = (int)DHT.temperature;


    Message message = {0};
    message.header = header;
    message.msgData.tempSensorData = (dhtData);

    radio.write(&message, sizeof(message));

    {
        Serial.println(dhtData.result);
        Serial.println(dhtData.temperature);
        Serial.println(dhtData.humidity);
        Serial.println("--------------");
    }

    // pause a second
    delay(1000);
    digitalWrite(13, LOW);
    delay(1000);
}
