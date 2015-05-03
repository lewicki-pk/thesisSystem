#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>
#include <dht.h>

#define DHT11_PIN 5

// ce,csn pins
RF24 radio(9, 10);

//temperature and humidity sensor
dht DHT;

struct data_to_send
{
  long int result;
  long int temperature;
  long int humidity;
};

struct message
{
  long int node;
  data_to_send data;
};

void setup(void)
{
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(0x4c);

  // open pipe for writing
  radio.openWritingPipe(0xF0F0F0F0E1LL);

  radio.enableDynamicPayloads();
  radio.setAutoAck(true);
  radio.powerUp();
  //  Serial.begin(9600);
}

void loop(void)
{
  digitalWrite(13, HIGH);
  message readings ={0};
  readings.node = 1;
  readings.data.result = DHT.read11(DHT11_PIN);
  readings.data.humidity = (int)DHT.humidity;
  readings.data.temperature = (int)DHT.temperature;
  
  radio.write(&readings, sizeof(message));
  Serial.println(readings.data.result);
  Serial.println(readings.data.temperature);
  Serial.println(readings.data.humidity);
  Serial.println("--------------");

  // pause a second
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
}
