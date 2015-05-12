#ifndef CONTROLER_H
#define CONTROLER_H

#include <string>

#include <SensorDB.h>

#ifndef UNIT_TEST

#include <RF24.h>

#endif

class Controler
{
public:

    Controler ();

    virtual ~Controler ();


    void receiveMessages();

protected:

private:

    void initSensorDB ()   {
        sensorDB = new SensorDB();
    }

    void setupConnection();

#ifndef UNIT_TEST
    RF24 radio(RPI_BPLUS_GPIO_J8_15,RPI_BPLUS_GPIO_J8_24, BCM2835_SPI_SPEED_8MHZ);
#endif
    SensorDB* sensorDB;
};

#endif // CONTROLER_H
