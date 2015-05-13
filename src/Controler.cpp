#include "Controler.h"

// Constructors/Destructors
//  

Controler::Controler()
#ifndef UNIT_TEST
: radio(RPI_BPLUS_GPIO_J8_15, RPI_BPLUS_GPIO_J8_24, BCM2835_SPI_SPEED_8MHZ)
#endif
{
    setupConnection();
}

Controler::~Controler() { }

void Controler::receiveMessages()
{
#ifndef UNIT_TEST
    // if there is data ready
    if (radio.available())
    {
        // dump the payloads until we've got everything
        Message receivedData = {0};
        radio.read(&receivedData, sizeof(Message));
        if (receivedData.header.nodeId == 1) {
            TempSensorData data = receivedData.msgData.tempSensorData;
            printf("1111 retVal: %d, temperature: %d deg. Celsius, humidity %d %% \n", data.result, 
                    data.temperature, 
                    data.humidity );
        }
        if (receivedData.header.nodeId == 2) {
            TempSensorData data = receivedData.msgData.tempSensorData;
            printf("2222 with counter value: %d\n", data.result);
        }
    }
#endif
}

void Controler::setupConnection()
{
#ifndef UNIT_TEST
    // init serial monitor and radio
    radio.begin();

    radio.setPALevel(RF24_PA_LOW);
    radio.setChannel(0x4c);

    // open pipe for reading
    radio.openReadingPipe(1,0xF0F0F0F0E1LL);

    radio.enableDynamicPayloads();
    radio.setAutoAck(true);
    radio.powerUp();
    radio.startListening();
#endif
    sensorDB = NULL;
}

