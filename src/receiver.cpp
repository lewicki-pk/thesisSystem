//#include <spi.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <iostream>
#include <RF24/RF24.h>

// ce,csn pins
RF24 radio(RPI_BPLUS_GPIO_J8_15,RPI_BPLUS_GPIO_J8_24, BCM2835_SPI_SPEED_8MHZ);

struct data_to_send
{
    int result;
    int temperature;
    int humidity;
};

struct message
{
    int node;
    data_to_send data;
};

void setup(void)
{
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
}

int i = 0;

void loop(void)
{
    // if there is data ready
    if (radio.available())
    {
        // dump the payloads until we've got everything
        message receivedData = {0};
        radio.read(&receivedData, sizeof(message));
        if (receivedData.node == 1)
            printf("111111111111111 retVal: %d, temperature: %d deg. Celsius, humidity %d %% \n", receivedData.data.result, 
                                                                                                  receivedData.data.temperature, 
                                                                                                  receivedData.data.humidity );
        if (receivedData.node == 2)
            printf("222222222222222 with counter value: %d\n", receivedData.data.result);
    }
}

int main()
{
    setup();
    while (1)
        loop();
}
