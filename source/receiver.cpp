//#include <spi.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <iostream>
#include <RF24/RF24.h>

// ce,csn pins
RF24 radio(RPI_BPLUS_GPIO_J8_15,RPI_BPLUS_GPIO_J8_24, BCM2835_SPI_SPEED_8MHZ);

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
        unsigned long count;
        radio.read(&count, sizeof(unsigned long));
        char text[13] = {0};
        radio.read(&text, sizeof(char)*13);
        if (count <=255)
        {
            printf("Odebralem %lu \n", count);
        }
        else
        {

            // print the payload
            std::string message(text);
            printf("Wiadomosc: %s \n", message.c_str());
        }
    }
}

int main()
{
    setup();
    while (1)
        loop();
}
