#ifndef CONTROLER_H
#define CONTROLER_H

#include <string>

#include <SensorDB.h>
#include <CommonMessages.h>

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
    RF24 radio;
#endif
    SensorDB* sensorDB;
};

#endif // CONTROLER_H
