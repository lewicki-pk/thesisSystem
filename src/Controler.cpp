#include <iostream>

#include "Controler.hpp"
#include "TemperatureNode.hpp"
#include "PirNode.hpp"
#include "MQTTProxy.hpp"

#include <DebugLog.hpp>

#define OPENHAB_RUNTIME_PATH "/home/pi/openHAB/configurations"; //TODO parse it from some other config file

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

        switch (static_cast<MsgType>(receivedData.header.msgType))
        {
        case MsgType::ACK_NACK : //AckNack
            break;
        case MsgType::TEMP_SENSOR_DATA : //TemperatureNodeData
            DEBUG_LOG("Received message of type TEMP_SENSOR_DATA with values: temperature=" +
                    std::to_string(receivedData.msgData.tempSensorData.temperature) + ", humidity=" +
                    std::to_string(receivedData.msgData.tempSensorData.humidity) + ", last reading status=" +
                    std::to_string(receivedData.msgData.tempSensorData.result));
            readingsContainer.push(receivedData);
            break;
        case MsgType::PIR_SENSOR_VALUE : //PirSensorData
            DEBUG_LOG("Received message of type PIR_SENSOR_DATA with value=" +
                    std::to_string(receivedData.msgData.pirSensorData.result));
            readingsContainer.push(receivedData);
            break;
        case MsgType::INITIALIZATION : //Initialization
            DEBUG_LOG("Received message of type INITIALIZATION");
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
    bool recreateConfigFiles = false;
    while (!initsContainer.empty())
    {
        DEBUG_LOG("Handling INITIALIZATION messages");
        Message msg = initsContainer.front();
        registerNode(msg);
        recreateConfigFiles = true;
        initsContainer.pop();
    }
    if (recreateConfigFiles)
    {
        std::string openHabConfigRoot = OPENHAB_RUNTIME_PATH;
        generateConfigFiles(openHabConfigRoot);
    }
}

void Controler::handleMessages()
{
    if (!readingsContainer.empty())
    {
        DEBUG_LOG("Handling received Update Messages");
        Message msg = readingsContainer.front();
        sensorDB->updateReadings(msg);
        readingsContainer.pop();
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
    radio.openReadingPipe(1, RASPI_READ_ADDR);
    radio.openWritingPipe(RASPI_WRITE_ADDR);

    radio.enableDynamicPayloads();
    radio.setAutoAck(true);
    radio.powerUp();
    radio.startListening();
#endif
    sensorDB = SensorDB::getInstance();
}

void Controler::registerNode(Message msg)
{
    Header hdr = msg.header;

    if (0 == hdr.nodeId) {
        hdr.nodeId = sensorDB->getAvailableNodeId();
    }
    else if (!sensorDB->isNodeInDB(hdr.nodeId)) 
    {
        DEBUG_LOG("This node has Id of " + std::to_string(hdr.nodeId) + " but was not found in DB. Replying with reset request");
        return replyWithResetRequest(hdr);
    }
    else
    {
        DEBUG_LOG("This node is already in DB. Replying with ACK"); //TODO add proper node type check
        return replyWithAck(msg.header);
    }

    DEBUG_LOG("Adding new node to DB");
    createAndAddNode(hdr);
}

void Controler::replyWithResetRequest(Header hdr)
{
    Message msg;
    msg.header = hdr;
    msg.header.msgType = static_cast<uint8_t>(MsgType::RESET_REQUEST);

    repliesContainer.push(msg);
}

void Controler::replyWithAck(Header hdr)
{
    Message msg;
    msg.header = hdr;
    msg.header.msgType = static_cast<uint8_t>(MsgType::ACK_NACK);
    AckNack response = AckNack::ACK;
    msg.msgData.ackNack = response;

    repliesContainer.push(msg);
}

void Controler::sendResponses()
{
    if (!repliesContainer.empty())
    {
        DEBUG_LOG("Sending RESPONSE messages");
        Message msg = repliesContainer.front();
#ifndef UNIT_TEST
        radio.stopListening();
        radio.write(&msg, sizeof(msg));
        radio.startListening();
#endif
        repliesContainer.pop();
    }
}

void Controler::createAndAddNode(Header hdr)
{
    SensorNode* nodeToRegister = nullptr;
    switch (hdr.nodeType)
    {
    case 1 : // temperatureNode
        DEBUG_LOG("Added new temperature node with id=" + std::to_string(hdr.nodeId));
        nodeToRegister = new TemperatureNode(MQTTProxy::getInstance());
        break;
    case 2 : // pirNode
        DEBUG_LOG("Added new pir node with id=" + std::to_string(hdr.nodeId));
        nodeToRegister = new PirNode(MQTTProxy::getInstance());
        break;
    default :
        DEBUG_LOG("Unknown node type. Returning.");
        return;
    }
    
    nodeToRegister->setNodeId(hdr.nodeId);
    nodeToRegister->setNodeType(hdr.nodeType);
    nodeToRegister->setLocation(hdr.location);

    sensorDB->addSensorNode(nodeToRegister);
    replyWithAck(hdr);
}

void Controler::generateConfigFiles(std::string filepath)
{
    DEBUG_LOG("Generating config files in openHAB path:" + filepath);
    sitemapGenerator.generateSitemap();
    sitemapGenerator.saveSitemapToFile(filepath);

    itemsGenerator.generateItems();
    itemsGenerator.saveItemsToFile(filepath);
}
