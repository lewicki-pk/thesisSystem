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
