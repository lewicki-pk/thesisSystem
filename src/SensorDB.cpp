#include <SensorDB.hpp>

SensorDB::SensorDB()
{
    sensorNodeContainer.clear();
}

SensorDB::~SensorDB()
{
    if (NULL != _instance)
        delete _instance;
}

SensorDB* SensorDB::_instance = NULL;

SensorDB* SensorDB::getInstance()
{
    if (NULL == _instance) {
        _instance = new SensorDB;
    }
    return _instance;
}

std::map<uint8_t, SensorNode*>::iterator SensorDB::begin()
{
    return sensorNodeContainer.begin(); 
}

std::map<uint8_t, SensorNode*>::iterator SensorDB::end()
{
    return sensorNodeContainer.end(); 
}

bool SensorDB::addSensorNode(SensorNode& newNode)
{
    std::pair<uint8_t, SensorNode*> pairToAdd = std::make_pair(*newNode.getNodeId(), &newNode);
    std::pair<std::map<uint8_t, SensorNode*>::iterator, bool> result =  sensorNodeContainer.insert(pairToAdd);
    return result.second;
}

void SensorDB::clearDatabase()
{
    sensorNodeContainer.clear();
}

size_t SensorDB::getSize()
{
    return sensorNodeContainer.size();
}

bool SensorDB::isNodeInDB(uint8_t id)
{
    auto iterator = sensorNodeContainer.find(id);
    return iterator != sensorNodeContainer.end() ? true : false;
}

uint8_t SensorDB::getAvailableNodeId()
{
    uint8_t newId = 1;
    auto mapEnd = sensorNodeContainer.end();

    while (sensorNodeContainer.find(newId) != mapEnd)
        newId++;

    return newId;
}

void SensorDB::updateReadings(Message msg)
{
    auto iterator = sensorNodeContainer.find(msg.header.nodeId);
    if (iterator != sensorNodeContainer.end())
    {
        iterator->second->updateValues(msg.msgData);
    }
}
