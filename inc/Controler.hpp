#ifndef CONTROLER_H
#define CONTROLER_H

#include <string>
#include <queue>

#include <SensorDB.hpp>
#include <CommonMessages.hpp>

#ifndef UNIT_TEST

#include <RF24.h>

#endif

class Controler
{
public:

    Controler();

    virtual ~Controler();

    void receiveMessages();

    void handleInitializations();

    void handleMessages();

protected:

private:

    void initSensorDB()   {
        sensorDB = SensorDB::getInstance();
    }

    void setupConnection();
    std::queue<Message>readingsContainer;
    std::queue<Message>initsContainer;


#ifndef UNIT_TEST
    RF24 radio;
#endif
    SensorDB* sensorDB;
};

#endif // CONTROLER_H
