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

    void sendResponses();

    void handleInitializations();

    void handleMessages();

    // TODO make private and rewrite the test
    void registerNode(Message msg);

    void replyWithResetRequest(Header hdr);

    void replyWithAck(Header hdr);

protected:

private:

    std::queue<Message>readingsContainer;

    std::queue<Message>initsContainer;

    std::queue<Message>repliesContainer;

    void initSensorDB()   {
        sensorDB = SensorDB::getInstance();
    }

    void createAndAddNode(Header hdr);

    void setupConnection();

#ifndef UNIT_TEST
    RF24 radio;
#endif
    SensorDB* sensorDB;
};

#endif // CONTROLER_H
