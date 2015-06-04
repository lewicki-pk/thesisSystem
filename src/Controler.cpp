#include <iostream>

#include <Controler.hpp>
#include <TemperatureNode.hpp>

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

        switch (static_cast<MsgType>(receivedData.header.msgType))
        {
        case MsgType::ACK_NACK : //AckNack
            break;
        case MsgType::TEMP_SENSOR_DATA : //TemperatureNodeData
            std::cout << "DBG: Received TEMP_SENSOR_DATA" << std::endl;
            readingsContainer.push(receivedData);
            break;
        case MsgType::INITIALIZATION : //Initialization
            std::cout << "DBG: Received INITIALIZATION message" << std::endl;
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
        std::cout << "DBG: handling Initializations" << std::endl;
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
        std::cout << "DBG: handling messages" << std::endl;
        Message msg = readingsContainer.front();
        TempSensorData data = msg.msgData.tempSensorData;
        std::cout << "received: status: " << data.result << ", temperature: " <<
            data.temperature << " degrees, humidity: " << data.humidity << "%" << std::endl;
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
        std::cout << "DBG: registerNode: this node is not in Database" << std::endl;
        return replyWithResetRequest(hdr);
    }

    std::cout << "DBG: adding node to DB" << std::endl;
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
        std::cout << "DBG: replying to some message" << std::endl;
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
