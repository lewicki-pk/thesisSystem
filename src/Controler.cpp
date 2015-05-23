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

        switch (receivedData.header.msgType)
        {
        case MsgType::ACK_NACK : //AckNack
            break;
        case MsgType::TEMP_SENSOR_DATA : //TemperatureNodeData
            readingsContainer.push(receivedData);
            break;
        case MsgType::INITIALIZATION : //Initialization
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
    if (!initsContainer.empty())
    {
        Message msg = initsContainer.front();
        registerNode(msg);
    }
}

void Controler::handleMessages()
{
    if (!readingsContainer.empty())
    {
        Message msg = readingsContainer.front();
        Header msgHeader = msg.header;
    //TODO here handle sensor readings
    //TODO rework
        if (msgHeader.msgType == 1) {
            TempSensorData data = msg.msgData.tempSensorData;
            printf("1111 retVal: %d, temperature: %d deg. Celsius, humidity %d %% \n", data.result, 
                    data.temperature, 
                    data.humidity );
        }
        if (msgHeader.nodeId == 2) {
            TempSensorData data = msg.msgData.tempSensorData;
            printf("2222 with counter value: %d\n", data.result);
        }
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

    if (!hdr.nodeId)
        hdr.nodeId = sensorDB->getAvailableNodeId();
    else if (!sensorDB->isNodeInDB(hdr.nodeId))
        return replyWithResetRequest(hdr);

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
        Message msg = repliesContainer.front();
#ifndef UNIT_TEST
        radio.write(&msg, sizeof(msg));
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

    sensorDB->addSensorNode(*nodeToRegister);
}
