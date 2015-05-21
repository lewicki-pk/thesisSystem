#include "Controler.hpp"

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
        Header msgHeader = receivedData.header;
        switch (msgHeader.msgType)
        {
        case 1 : //AckNack
            break;
        case 2 : //TemperatureNodeData
            readingsContainer.push(receivedData);
            break;
        case 3 : //Initialization //TODO for now lets leave it empty
            initsContainer.push(receivedData);
            break;
        default :
            break;
        }
    }
#endif
}

void Controler::handleInitializations()
{
    if (!initsContainer.empty())
    {
        Message tmp = initsContainer.front();
        //tmp.
        //TODO procedura inicjalizacji
    }
}

void Controler::handleMessages()
{
    if (!readingsContainer.empty())
    {
        Message msg = readingsContainer.front();
        Header msgHeader = msg.header;
    //TODO here handle sensor readings
    //TODO rework
        if (msgHeader.msgType == 1) {
            TempSensorData data = msg.msgData.tempSensorData;
            printf("1111 retVal: %d, temperature: %d deg. Celsius, humidity %d %% \n", data.result, 
                    data.temperature, 
                    data.humidity );
        }
        if (msgHeader.nodeId == 2) {
            TempSensorData data = msg.msgData.tempSensorData;
            printf("2222 with counter value: %d\n", data.result);
        }
    }
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
    sensorDB = SensorDB::getInstance();
}

