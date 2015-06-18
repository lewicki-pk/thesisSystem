#include "UniRadio.hpp"

UniRadio::UniRadio(uint8_t cePin, uint8_t csnPin)
{
    radio = new RF24(cePin, csnPin);
}

UniRadio::~UniRadio()
{
    delete radio;
}

void UniRadio::setup()
{
    radio->begin();
    radio->setPALevel(RF24_PA_LOW);
    radio->setChannel(0x4c);

    // open pipe for writing
    radio->openWritingPipe(RASPI_READ_ADDR);
    radio->openReadingPipe(1, RASPI_WRITE_ADDR);

    radio->enableDynamicPayloads();
    radio->setAutoAck(true);
    radio->powerUp();
    radio->startListening();
}

void UniRadio::sendMessage(Message &message)
{
    radio->stopListening();
    radio->write(&message, sizeof(message));
    radio->startListening();
}

bool UniRadio::isAvailable()
{
    return radio->available();
}


Message UniRadio::getMessage()
{
    Message receivedMsg;
    radio->read(&receivedMsg, sizeof(Message));
    return receivedMsg;
}
