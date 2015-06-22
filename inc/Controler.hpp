#pragma once
#include <IControler.hpp>

#include <string>
#include <queue>

#include <CommonMessages.hpp>
#include <SensorDB.hpp>
#include <SitemapGenerator.hpp>
#include <ItemsGenerator.hpp>

#ifndef UNIT_TEST

#include <RF24.h>

#endif

class Controler: public IControler
{
public:

    Controler();

    virtual ~Controler();

    void receiveMessages();

    void sendResponses();

    void handleInitializations();

    void handleMessages();

    // TODO make private and rewrite the test
    bool registerNode(Message msg);

    void replyWithResetRequest(Header hdr);

    void replyWithAck(Header hdr);

    void generateConfigFiles(std::string filepath);

protected:

private:

    void initSensorDB()   {
        sensorDB = SensorDB::getInstance();
    }

    void createAndAddNode(Header hdr);

    void setupConnection();

#ifndef UNIT_TEST
    RF24 radio;
#endif

    std::queue<Message>readingsContainer;

    std::queue<Message>initsContainer;

    std::queue<Message>repliesContainer;

    SitemapGenerator sitemapGenerator;

    ItemsGenerator itemsGenerator;

    SensorDB* sensorDB;
};

