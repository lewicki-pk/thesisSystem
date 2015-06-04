#include <iostream>

#include <Controler.hpp>
#include <TemperatureNode.hpp>

#include <DebugLog.hpp>


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
            DEBUG_LOG("Received message of type TEMP_SENSOR_DATA");
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
        initsContainer.pop();
        recreateConfigFiles = true;
    }
    if (recreateConfigFiles)
    {
        std::string openHabConfigRoot = "/home/lewiatan/openHAB-runtime/configurations"; //TODO filepaths in one place
        generateConfigFiles(openHabConfigRoot);
    }
}

void Controler::handleMessages()
{
    if (!readingsContainer.empty())
    {
        DEBUG_LOG("Handling received Update Messages");
        Message msg = readingsContainer.front();
        {
            TempSensorData data = msg.msgData.tempSensorData;
            std::cout << "received: status: " << data.result << ", temperature: " <<
                data.temperature << " degrees, humidity: " << data.humidity << "%" << std::endl;
        }
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

    if (!hdr.nodeId) {
        hdr.nodeId = sensorDB->getAvailableNodeId();
    }
    else if (!sensorDB->isNodeInDB(hdr.nodeId)) {
        DEBUG_LOG("This node has Id of " + std::to_string(hdr.nodeId) + "but was not found in DB. Replying with reset request");
        return replyWithResetRequest(hdr);
    }

    DEBUG_LOG("Adding new node to DB");
    createAndAddNode(hdr);
    replyWithAck(hdr);
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
    case 1 :
        nodeToRegister = new TemperatureNode;
    }
    
    nodeToRegister->setNodeId(hdr.nodeId);
    nodeToRegister->setNodeType(hdr.nodeType);
    nodeToRegister->setLocation(hdr.location);

    sensorDB->addSensorNode(nodeToRegister);
}

void Controler::generateConfigFiles(std::string filepath)
{
    sitemapGenerator.generateSitemap();
    sitemapGenerator.saveSitemapToFile(filepath);

    itemsGenerator.generateItems();
    itemsGenerator.saveItemsToFile(filepath);
}
